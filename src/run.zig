//! Runs CBMC on one harness in a generated C file and exits zero only if the verdict is the
//! expected one. With `prepare <in.c> <out.c>` it instead rewrites the generated C for the
//! checker. Invoked by the build step; see `build.zig` for the argument order.

const std = @import("std");
const bounds = @import("bounds.zig");
const prepare = @import("prepare.zig");
const report = @import("report.zig");

pub fn main(init: std.process.Init) !void {
    const arena = init.arena.allocator();
    const args = try init.minimal.args.toSlice(arena);
    if (args.len == 4 and std.mem.eql(u8, args[1], "prepare")) {
        const c_source = try std.Io.Dir.cwd().readFileAlloc(init.io, args[2], arena, .unlimited);
        const prepared = try prepare.forChecker(arena, c_source);
        return std.Io.Dir.cwd().writeFile(init.io, .{ .sub_path = args[3], .data = prepared });
    }
    if (args.len < 9) {
        std.debug.print(
            "usage: {s} <harness.c> <zig-lib-dir> <shim.c> <function> <proved|refuted> <unwind> <docker-image or \"\">" ++
                " <harness.zig or \"\"> [function=unwind ...]\n",
            .{args[0]},
        );
        std.process.exit(2);
    }
    const cwd = try std.process.currentPathAlloc(init.io, arena);
    const c_file = try std.fs.path.resolve(arena, &.{ cwd, args[1] });
    const lib_dir = try std.fs.path.resolve(arena, &.{ cwd, args[2] });
    const shim = try std.fs.path.resolve(arena, &.{ cwd, args[3] });
    const function = args[4];
    const expect_refuted = std.mem.eql(u8, args[5], "refuted");
    const unwind = args[6];

    var argv: std.ArrayList([]const u8) = .empty;
    if (args[7].len != 0) {
        try argv.appendSlice(arena, &.{ "docker", "run", "--rm" });
        for ([_][]const u8{ std.fs.path.dirname(c_file).?, lib_dir, std.fs.path.dirname(shim).? }) |dir| {
            try argv.appendSlice(arena, &.{ "-v", try std.fmt.allocPrint(arena, "{s}:{s}:ro", .{ dir, dir }) });
        }
        try argv.append(arena, args[7]);
    }
    // `zig.h` for generated C, and `verifier.h`, which sits beside the shim, for harnesses written in C.
    try argv.appendSlice(arena, &.{ "cbmc", c_file, shim, "-I", lib_dir, "-I", std.fs.path.dirname(shim).? });
    try argv.appendSlice(arena, &.{ "--function", function });
    const c_source = try std.Io.Dir.cwd().readFileAlloc(init.io, c_file, arena, .unlimited);
    const source: ?report.Source = if (args[8].len == 0) null else .{
        // Reports read better with the path as it is typed from the build root.
        .path = if (std.mem.startsWith(u8, args[8], cwd)) std.mem.trimStart(u8, args[8][cwd.len..], "/") else args[8],
        .text = try std.Io.Dir.cwd().readFileAlloc(init.io, args[8], arena, .unlimited),
    };
    if (args.len > 9) {
        const base = argv.items.len;
        try argv.appendSlice(arena, &.{ "--show-loops", "--json-ui" });
        const loops = try std.process.run(arena, init.io, .{ .argv = argv.items });
        argv.shrinkRetainingCapacity(base);
        const unwindset = bounds.unwindset(arena, c_source, loops.stdout, args[9..]) catch |err| switch (err) {
            error.OutOfMemory => return err,
            error.InvalidBound, error.UnknownFunction => {
                std.debug.print("error: {s}\n  {s}\n", .{ function, switch (err) {
                    error.InvalidBound => "a bound is not of the form function=count",
                    else => "a bound names a function that is not in the generated C; use the name reports print",
                } });
                std.process.exit(2);
            },
        };
        try argv.appendSlice(arena, &.{ "--unwindset", unwindset });
    }
    try argv.appendSlice(arena, &.{ "--unwind", unwind, "--unwinding-assertions", "--trace", "--json-ui" });
    // The default of 256 addressable objects is too few for any real harness.
    try argv.appendSlice(arena, &.{ "--object-bits", "12" });
    // Zig has no safety check for memory reached through a pointer cast, so the checker's own
    // checks on the generated C are what catch a read or write outside an object.
    try argv.appendSlice(arena, &.{ "--bounds-check", "--pointer-check" });
    const started: std.Io.Timestamp = .now(init.io, .awake);
    const result = try std.process.run(arena, init.io, .{ .argv = argv.items });
    const elapsed_ms = started.untilNow(init.io, .awake).toMilliseconds();

    var outcome = try report.read(arena, result.stdout, c_source);
    if (outcome == .tool_error and result.stderr.len != 0) outcome = .{ .tool_error = result.stderr };
    const killed = switch (result.term) {
        // 137 is how a container reports SIGKILL.
        .exited => |code| code == 137,
        .signal => true,
        .stopped, .unknown => false,
    };
    if (outcome == .tool_error and killed) {
        outcome = .{ .tool_error = "cbmc was killed before it finished, most likely for running out of memory" };
    }

    var buffer: [4096]u8 = undefined;
    var stderr = std.Io.File.stderr().writer(init.io, &buffer);
    const w = &stderr.interface;
    const as_expected = switch (outcome) {
        .proved => !expect_refuted,
        .refuted => expect_refuted,
        .unwind_exceeded, .unmodelled, .tool_error => false,
    };
    try w.print("[{d}.{d}s] ", .{ @divTrunc(elapsed_ms, 1000), @divTrunc(@rem(elapsed_ms, 1000), 100) });
    if (as_expected and expect_refuted) {
        // A seeded bug only needs its reason shown, to confirm it failed for the intended one.
        var full: std.Io.Writer.Allocating = .init(arena);
        try report.render(&full.writer, function, unwind, outcome, source);
        var lines = std.mem.splitScalar(u8, full.written(), '\n');
        try w.print("as expected, {s}\n{s}\n", .{ lines.first(), lines.next() orelse "" });
    } else {
        try report.render(w, function, unwind, outcome, source);
        if (outcome == .proved and expect_refuted) {
            try w.writeAll("  expected a counterexample, but the proof went through\n");
        }
    }
    try w.flush();
    std.process.exit(if (as_expected) 0 else 1);
}

test {
    _ = bounds;
    _ = prepare;
    _ = report;
}
