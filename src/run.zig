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
                " <harness.zig or \"\"> [function=unwind ...] [caller>target,... ...] [--work=<dir>]\n",
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

    var unwind_bounds: std.ArrayList([]const u8) = .empty;
    var callbacks: std.ArrayList([]const u8) = .empty;
    var work_dir: ?[]const u8 = null;
    for (args[9..]) |argument| {
        if (std.mem.startsWith(u8, argument, "--work=")) {
            work_dir = try std.fs.path.resolve(arena, &.{ cwd, argument["--work=".len..] });
        } else if (std.mem.indexOfScalar(u8, argument, '>') != null) {
            try callbacks.append(arena, argument);
        } else try unwind_bounds.append(arena, argument);
    }
    const c_source = try std.Io.Dir.cwd().readFileAlloc(init.io, c_file, arena, .unlimited);

    // Every tool runs the same way: directly, or inside the image with the inputs mounted.
    var tool: std.ArrayList([]const u8) = .empty;
    if (args[7].len != 0) {
        try tool.appendSlice(arena, &.{ "docker", "run", "--rm", "--memory=16g", "--memory-swap=16g" });
        for ([_][]const u8{ std.fs.path.dirname(c_file).?, lib_dir, std.fs.path.dirname(shim).? }) |dir| {
            try tool.appendSlice(arena, &.{ "-v", try std.fmt.allocPrint(arena, "{s}:{s}:ro", .{ dir, dir }) });
        }
        if (work_dir) |dir| try tool.appendSlice(arena, &.{ "-v", try std.fmt.allocPrint(arena, "{s}:{s}", .{ dir, dir }) });
        try tool.append(arena, args[7]);
    }
    // `zig.h` for generated C, and `verifier.h`, which sits beside the shim, for harnesses written in C.
    var program: []const []const u8 = &.{ c_file, shim, "-I", lib_dir, "-I", std.fs.path.dirname(shim).? };

    // An indirect call whose target the checker cannot pin down is tried against every
    // function of that shape. Naming its targets needs the program compiled and rewritten
    // by CBMC's own tools first, and the checker then reads the rewritten program.
    if (callbacks.items.len != 0) {
        const dir = work_dir orelse {
            std.debug.print("error: {s}\n  callbacks need a --work directory\n", .{function});
            std.process.exit(2);
        };
        const compiled = try std.fs.path.join(arena, &.{ dir, "compiled.gb" });
        const restricted = try std.fs.path.join(arena, &.{ dir, "restricted.gb" });
        var compile = try tool.clone(arena);
        try compile.append(arena, "goto-cc");
        try compile.appendSlice(arena, program);
        try compile.appendSlice(arena, &.{ "-o", compiled });
        var restrict = try tool.clone(arena);
        try restrict.append(arena, "goto-instrument");
        for (callbacks.items) |callback| {
            const value = bounds.restriction(arena, c_source, callback) catch |err| switch (err) {
                error.OutOfMemory => return err,
                error.InvalidBound, error.InvalidCallback, error.UnknownFunction => {
                    std.debug.print("error: {s}\n  callback `{s}`: {s}\n", .{ function, callback, @errorName(err) });
                    std.process.exit(2);
                },
            };
            try restrict.appendSlice(arena, &.{ "--restrict-function-pointer", value });
        }
        try restrict.appendSlice(arena, &.{ compiled, restricted });
        for ([_][]const []const u8{ compile.items, restrict.items }) |command| {
            const step = try std.process.run(arena, init.io, .{ .argv = command });
            if (step.term != .exited or step.term.exited != 0) {
                std.debug.print("error: {s}\n  {s} failed:\n{s}{s}\n", .{ function, command[tool.items.len], step.stdout, step.stderr });
                std.process.exit(2);
            }
        }
        program = &.{restricted};
    }

    var argv = try tool.clone(arena);
    try argv.append(arena, "cbmc");
    try argv.appendSlice(arena, program);
    try argv.appendSlice(arena, &.{ "--function", function });
    const source: ?report.Source = if (args[8].len == 0) null else .{
        // Reports read better with the path as it is typed from the build root.
        .path = if (std.mem.startsWith(u8, args[8], cwd)) std.mem.trimStart(u8, args[8][cwd.len..], "/") else args[8],
        .text = try std.Io.Dir.cwd().readFileAlloc(init.io, args[8], arena, .unlimited),
    };
    if (unwind_bounds.items.len != 0) {
        const base = argv.items.len;
        try argv.appendSlice(arena, &.{ "--show-loops", "--json-ui" });
        const loops = try std.process.run(arena, init.io, .{ .argv = argv.items });
        argv.shrinkRetainingCapacity(base);
        const unwindset = bounds.unwindset(arena, c_source, loops.stdout, unwind_bounds.items) catch |err| switch (err) {
            error.OutOfMemory => return err,
            error.InvalidBound, error.InvalidCallback, error.UnknownFunction => {
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
