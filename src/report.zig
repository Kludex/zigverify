//! Reads CBMC's JSON output and decides what it means for one harness, then prints the
//! verdict in terms of the Zig program instead of the generated C.

const std = @import("std");
const Kind = @import("failure.zig").Kind;

const Allocator = std.mem.Allocator;
const Value = std.json.Value;
const Writer = std.Io.Writer;

pub const Outcome = union(enum) {
    /// No input reaches a failing check, within the unwind bound.
    proved,
    refuted: Counterexample,
    /// A loop or recursion ran past the unwind bound, so nothing was shown either way.
    /// The payload names the CBMC property, which carries the function.
    unwind_exceeded: []const u8,
    /// The code calls C functions the checker has no body for. It would treat their results
    /// as arbitrary but their writes through pointer arguments as never happening, so neither
    /// a proof nor a counterexample could be trusted. The payload names the functions.
    unmodelled: []const []const u8,
    /// CBMC gave no verdict. The payload is whatever it printed.
    tool_error: []const u8,
};

pub const Counterexample = struct {
    /// Set when the failure is one of CBMC's own checks on the generated C, such as a read
    /// outside an object, instead of a Zig safety check or an assert. It replaces `kind`.
    c_check: ?[]const u8 = null,
    kind: Kind,
    a: u64,
    b: u64,
    /// How many `verifier.assert` calls had run when the failure happened, the failing one included.
    asserts_reached: usize,
    /// The functions on the stack at the failure, outermost first.
    stack: []const Frame,
    /// The bytes each `verifier.any` call produced, in the order the harness asked.
    inputs: []const []const u8,
};

pub const Frame = struct {
    /// The function's name in the C, without the `__<id>` suffix Zig's C backend appends.
    function: []const u8,
    /// The line of the C file where this frame called the next one, or where the check failed.
    c_line: usize,
    /// The same place in the Zig function, when the C was generated from Zig.
    position: ?Position,
};

/// A place in a Zig function. `line` counts from the line holding `fn`, which is 1.
pub const Position = struct { line: usize, column: usize };

/// The Zig file the harnesses were compiled from, used to turn positions into file lines.
pub const Source = struct { path: []const u8, text: []const u8 };

/// `c_source` is the C file CBMC was given. Everything returned lives in `arena`.
pub fn read(arena: Allocator, cbmc_json: []const u8, c_source: []const u8) Allocator.Error!Outcome {
    const root = std.json.parseFromSliceLeaky(Value, arena, cbmc_json, .{}) catch |err| switch (err) {
        error.OutOfMemory => return error.OutOfMemory,
        else => return .{ .tool_error = cbmc_json },
    };
    if (root != .array) return .{ .tool_error = cbmc_json };

    const no_body = "**** WARNING: no body for function ";
    var unmodelled: std.ArrayList([]const u8) = .empty;
    var errors: std.ArrayList(u8) = .empty;
    var saw_result = false;
    var refuted: ?Counterexample = null;
    var unwind_exceeded: ?[]const u8 = null;

    for (root.array.items) |entry| {
        if (entry != .object) continue;
        if (string(entry, "messageType")) |message_type| {
            const text = string(entry, "messageText") orelse "";
            if (std.mem.eql(u8, message_type, "ERROR")) {
                try errors.appendSlice(arena, text);
                try errors.append(arena, '\n');
            } else if (std.mem.startsWith(u8, text, no_body)) {
                const name = text[no_body.len..];
                // Compiler builtins such as `__builtin_return_address` write through no pointer.
                if (!std.mem.startsWith(u8, name, "__builtin_")) try unmodelled.append(arena, name);
            }
        }
        const results = entry.object.get("result") orelse continue;
        if (results != .array) continue;
        saw_result = true;
        for (results.array.items) |property| {
            const status = string(property, "status") orelse continue;
            if (!std.mem.eql(u8, status, "FAILURE")) continue;
            const name = string(property, "property") orelse "";
            if (std.mem.indexOf(u8, name, ".unwind.") != null or std.mem.indexOf(u8, name, ".recursion") != null) {
                unwind_exceeded = name;
                continue;
            }
            const trace = property.object.get("trace") orelse continue;
            if (trace != .array) continue;
            const is_zig_check = std.mem.startsWith(u8, name, "verifier_fail.");
            // A Zig-level failure says more than a C-level one, so it is the one reported.
            if (refuted != null and !is_zig_check) continue;
            refuted = try counterexample(arena, trace.array.items, c_source);
            if (!is_zig_check) refuted.?.c_check = string(property, "description") orelse name;
        }
    }

    if (!saw_result) return .{ .tool_error = if (errors.items.len != 0) errors.items else cbmc_json };
    if (unmodelled.items.len != 0) return .{ .unmodelled = unmodelled.items };
    // A counterexample is real however far the loops were unwound, so it wins.
    if (refuted) |found| return .{ .refuted = found };
    if (unwind_exceeded) |name| return .{ .unwind_exceeded = name };
    return .proved;
}

/// Prints one harness's verdict. `unwind` is the global bound the run used, quoted when a loop
/// outran a bound. With `source`, positions in functions it declares are printed as file lines.
pub fn render(
    w: *Writer,
    function: []const u8,
    unwind: []const u8,
    outcome: Outcome,
    source: ?Source,
) Writer.Error!void {
    switch (outcome) {
        .proved => try w.print("proved: {s}\n", .{function}),
        .unwind_exceeded => |name| try w.print(
            "inconclusive: {s}\n  {s} ran past its unwind bound; raise the proof's `unwind` ({s}) or that function's bound\n",
            .{ function, name, unwind },
        ),
        .unmodelled => |functions| {
            try w.print("inconclusive: {s}\n  the code calls C functions the checker has no body for:", .{function});
            for (functions) |name| try w.print(" {s}", .{name});
            try w.writeAll("\n  export a model of each from the harness, under the C name\n");
        },
        .tool_error => |output| try w.print("error: {s}\n  cbmc gave no verdict:\n{s}\n", .{ function, output }),
        .refuted => |found| {
            try w.print("refuted: {s}\n  ", .{function});
            // Only the fixed sentences of `Kind` carry operand placeholders.
            var rest = if (found.c_check != null) "" else found.kind.describe();
            if (found.c_check) |description| try w.writeAll(description);
            while (std.mem.indexOfScalar(u8, rest, '{')) |open| {
                try w.writeAll(rest[0..open]);
                try w.print("{d}", .{if (rest[open + 1] == 'a') found.a else found.b});
                rest = rest[open + 3 ..];
            }
            try w.writeAll(rest);
            if (found.c_check == null and found.kind == .assert) try w.print(" (assert number {d} to run)", .{found.asserts_reached});
            try w.writeAll("\n");
            var depth = found.stack.len;
            while (depth > 0) : (depth -= 1) {
                const frame = found.stack[depth - 1];
                const lead = if (depth == found.stack.len) "in" else "called from";
                try w.print("  {s} {s}", .{ lead, frame.function });
                if (frame.position) |position| {
                    if (declarationLine(source, frame.function)) |declared| {
                        try w.print(" ({s}:{d}:{d})", .{ source.?.path, declared + position.line - 1, position.column });
                    } else {
                        try w.print(" (line {d}, column {d} of the function)", .{ position.line, position.column });
                    }
                } else if (frame.c_line != 0) {
                    try w.print(" (line {d} of the C)", .{frame.c_line});
                }
                try w.writeAll("\n");
            }
            if (found.inputs.len != 0) try w.writeAll("  inputs, in the order the harness asked for them:\n");
            for (found.inputs, 1..) |input, number| {
                try w.print("    {d}: {d} bytes ", .{ number, input.len });
                for (input) |byte| try w.print(" {x:0>2}", .{byte});
                if (input.len <= 8) {
                    var little_endian: u64 = 0;
                    for (input, 0..) |byte, i| little_endian |= @as(u64, byte) << @intCast(i * 8);
                    try w.print("  = {d}", .{little_endian});
                }
                try w.writeAll("\n");
            }
        },
    }
}

/// The line of `source` that declares `function`, if exactly one declaration there can be it.
fn declarationLine(source: ?Source, function: []const u8) ?usize {
    const file = source orelse return null;
    const stem = std.fs.path.stem(file.path);
    // An exported function keeps its name. Any other is named `<file>_<path to it>`, and the
    // last segment is searched for: a method `Parser.next` is found as `fn next(`.
    const qualified = function.len > stem.len and std.mem.startsWith(u8, function, stem) and function[stem.len] == '_';
    const last_segment = function[if (std.mem.lastIndexOfScalar(u8, function, '_')) |at| at + 1 else 0..];
    var exported_buffer: [256]u8 = undefined;
    var member_buffer: [256]u8 = undefined;
    for ([_]?[]const u8{
        std.fmt.bufPrint(&exported_buffer, "export fn {s}(", .{function}) catch null,
        if (qualified) std.fmt.bufPrint(&member_buffer, "fn {s}(", .{last_segment}) catch null else null,
    }) |candidate| {
        const needle = candidate orelse continue;
        const at = std.mem.indexOf(u8, file.text, needle) orelse continue;
        if (std.mem.indexOfPos(u8, file.text, at + 1, needle) != null) continue;
        return std.mem.count(u8, file.text[0..at], "\n") + 1;
    }
    return null;
}

/// The Zig position that the C backend's `/* file:<line>:<column> */` comment gives for `c_line`.
fn zigPosition(c_source: []const u8, c_line: usize) ?Position {
    var position: ?Position = null;
    var lines = std.mem.splitScalar(u8, c_source, '\n');
    var number: usize = 1;
    while (lines.next()) |line| : (number += 1) {
        if (number > c_line) break;
        // A function's comments say nothing about the next function.
        if (line.len != 0 and line[0] != ' ' and std.mem.endsWith(u8, line, ") {")) position = null;
        const comment = std.mem.trimStart(u8, line, " ");
        if (!std.mem.startsWith(u8, comment, "/* file:")) continue;
        var fields = std.mem.tokenizeAny(u8, comment["/* file:".len..], ": */");
        position = .{
            .line = std.fmt.parseInt(usize, fields.next() orelse continue, 10) catch continue,
            .column = std.fmt.parseInt(usize, fields.next() orelse continue, 10) catch continue,
        };
    }
    return position;
}

fn counterexample(arena: Allocator, trace: []const Value, c_source: []const u8) Allocator.Error!Counterexample {
    const Call = struct { name: []const u8, c_line: usize = 0 };
    var stack: std.ArrayList(Call) = .empty;
    var inputs: std.ArrayList([]const u8) = .empty;
    var found: Counterexample = .{ .kind = .panic, .a = 0, .b = 0, .asserts_reached = 0, .stack = &.{}, .inputs = &.{} };

    for (trace) |step| {
        if (step != .object) continue;
        const step_type = string(step, "stepType") orelse continue;
        if (std.mem.eql(u8, step_type, "function-call")) {
            const function = step.object.get("function") orelse continue;
            const name = string(function, "displayName") orelse continue;
            if (std.mem.eql(u8, name, "verifier_check")) found.asserts_reached += 1;
            located(stack.items, step);
            try stack.append(arena, .{ .name = name });
        } else if (std.mem.eql(u8, step_type, "function-return")) {
            _ = stack.pop();
        } else if (std.mem.eql(u8, step_type, "failure")) {
            located(stack.items, step);
        } else if (std.mem.eql(u8, step_type, "assignment")) {
            const top = (stack.getLastOrNull() orelse continue).name;
            const lhs = string(step, "lhs") orelse continue;
            const value = step.object.get("value") orelse continue;
            if (std.mem.eql(u8, top, "verifier_fail")) {
                if (std.mem.eql(u8, lhs, "kind")) {
                    found.kind = std.enums.fromInt(Kind, bits(value)) orelse .panic;
                } else if (std.mem.eql(u8, lhs, "a")) {
                    found.a = bits(value);
                } else if (std.mem.eql(u8, lhs, "b")) {
                    found.b = bits(value);
                }
            } else if (std.mem.eql(u8, top, "verifier_any") and std.mem.eql(u8, lhs, "tmp_nondet_contents")) {
                try inputs.append(arena, try bytes(arena, value));
            }
        }
    }

    // Everything from the verifier's own entry points inward is plumbing, not the user's code.
    var user_frames: std.ArrayList(Frame) = .empty;
    for (stack.items) |call| {
        if (std.mem.startsWith(u8, call.name, "verifier_") or std.mem.startsWith(u8, call.name, "panic_")) break;
        const suffix = std.mem.lastIndexOf(u8, call.name, "__") orelse call.name.len;
        try user_frames.append(arena, .{
            .function = call.name[0..suffix],
            .c_line = call.c_line,
            .position = zigPosition(c_source, call.c_line),
        });
    }
    found.stack = user_frames.items;
    found.inputs = inputs.items;
    return found;
}

/// Records on the innermost frame the line a step happened at, if the step is in that function.
fn located(stack: anytype, step: Value) void {
    if (stack.len == 0) return;
    const location = step.object.get("sourceLocation") orelse return;
    const function = string(location, "function") orelse return;
    if (!std.mem.eql(u8, function, stack[stack.len - 1].name)) return;
    stack[stack.len - 1].c_line = std.fmt.parseInt(usize, string(location, "line") orelse return, 10) catch return;
}

fn string(value: Value, key: []const u8) ?[]const u8 {
    if (value != .object) return null;
    const found = value.object.get(key) orelse return null;
    return if (found == .string) found.string else null;
}

fn bits(value: Value) u64 {
    return std.fmt.parseInt(u64, string(value, "binary") orelse return 0, 2) catch 0;
}

fn bytes(arena: Allocator, value: Value) Allocator.Error![]const u8 {
    if (value != .object) return &.{};
    const elements = value.object.get("elements") orelse return arena.dupe(u8, &.{@truncate(bits(value))});
    if (elements != .array) return &.{};
    const out = try arena.alloc(u8, elements.array.items.len);
    for (out, elements.array.items) |*byte, element| {
        byte.* = if (element == .object) @truncate(bits(element.object.get("value") orelse .null)) else 0;
    }
    return out;
}

const midpoint: Fixture = .{
    .c = @embedFile("testdata/midpoint.c"),
    .source = .{ .path = "examples/midpoint.zig", .text = @embedFile("testdata/midpoint.zig") },
};
const sockaddr: Fixture = .{
    .c = @embedFile("testdata/sockaddr.c"),
    .source = .{ .path = "examples/sockaddr.zig", .text = @embedFile("testdata/sockaddr.zig") },
};

const Fixture = struct { c: []const u8 = "", source: ?Source = null };

fn renderFixture(arena: Allocator, comptime cbmc_json: []const u8, fixture: Fixture) ![]const u8 {
    var out: Writer.Allocating = .init(arena);
    const outcome = try read(arena, @embedFile("testdata/" ++ cbmc_json), fixture.c);
    try render(&out.writer, "harness", "4", outcome, fixture.source);
    return out.written();
}

test "a proof that goes through is reported as proved" {
    var arena: std.heap.ArenaAllocator = .init(std.testing.allocator);
    defer arena.deinit();
    try std.testing.expectEqualStrings(
        \\proved: harness
        \\
    , try renderFixture(arena.allocator(), "proved.json", midpoint));
}

test "a failed safety check names the check, the source line of each frame and the inputs" {
    var arena: std.heap.ArenaAllocator = .init(std.testing.allocator);
    defer arena.deinit();
    try std.testing.expectEqualStrings(
        \\refuted: harness
        \\  integer overflow
        \\  in midpoint_midpointNaive (examples/midpoint.zig:9:17)
        \\  called from naive_midpoint_never_panics (examples/midpoint.zig:18:22)
        \\  inputs, in the order the harness asked for them:
        \\    1: 4 bytes  00 00 00 80  = 2147483648
        \\    2: 4 bytes  01 00 00 80  = 2147483649
        \\
    , try renderFixture(arena.allocator(), "refuted_overflow.json", midpoint));
}

test "without the Zig source, a frame is located within its function" {
    var arena: std.heap.ArenaAllocator = .init(std.testing.allocator);
    defer arena.deinit();
    try std.testing.expectEqualStrings(
        \\refuted: harness
        \\  integer overflow
        \\  in midpoint_midpointNaive (line 2, column 17 of the function)
        \\  called from naive_midpoint_never_panics (line 2, column 22 of the function)
        \\  inputs, in the order the harness asked for them:
        \\    1: 4 bytes  00 00 00 80  = 2147483648
        \\    2: 4 bytes  01 00 00 80  = 2147483649
        \\
    , try renderFixture(arena.allocator(), "refuted_overflow.json", .{ .c = midpoint.c }));
}

test "a failed assert says which assert it was" {
    var arena: std.heap.ArenaAllocator = .init(std.testing.allocator);
    defer arena.deinit();
    try std.testing.expectEqualStrings(
        \\refuted: harness
        \\  verifier.assert failed (assert number 2 to run)
        \\  in midpoint_is_below_high (examples/midpoint.zig:37:20)
        \\  inputs, in the order the harness asked for them:
        \\    1: 4 bytes  f9 cd 24 03  = 52743673
        \\    2: 4 bytes  f9 cd 24 03  = 52743673
        \\
    , try renderFixture(arena.allocator(), "refuted_assert.json", midpoint));
}

test "a loop past the unwind bound is inconclusive, not proved" {
    var arena: std.heap.ArenaAllocator = .init(std.testing.allocator);
    defer arena.deinit();
    try std.testing.expectEqualStrings(
        \\inconclusive: harness
        \\  verifier_prefix__anon_191__298.unwind.0 ran past its unwind bound; raise the proof's `unwind` (4) or that function's bound
        \\
    , try renderFixture(arena.allocator(), "unwind_exceeded.json", midpoint));
}

test "cbmc's own error is passed on when it gives no verdict" {
    var arena: std.heap.ArenaAllocator = .init(std.testing.allocator);
    defer arena.deinit();
    try std.testing.expectEqualStrings(
        \\error: harness
        \\  cbmc gave no verdict:
        \\Invalid User Input
        \\Option: --function
        \\Reason: couldn't find entry with name 'no_such_function' in symbol table
        \\
        \\
    , try renderFixture(arena.allocator(), "tool_error.json", .{}));
}

test "output that is not json is a tool error" {
    var arena: std.heap.ArenaAllocator = .init(std.testing.allocator);
    defer arena.deinit();
    const outcome = try read(arena.allocator(), "cbmc: command not found", "");
    try std.testing.expectEqualStrings("cbmc: command not found", outcome.tool_error);
}

test "a read outside an object is reported with the checker's own description" {
    var arena: std.heap.ArenaAllocator = .init(std.testing.allocator);
    defer arena.deinit();
    try std.testing.expectEqualStrings(
        \\refuted: harness
        \\  dereference failure: pointer outside object bounds in *t18
        \\  in sockaddr_same (examples/sockaddr.zig:39:46)
        \\  called from short_buffer_is_never_read_past (examples/sockaddr.zig:82:13)
        \\  inputs, in the order the harness asked for them:
        \\    1: 16 bytes  0a 00 00 04 20 04 10 40 10 20 01 10 04 02 02 04
        \\
    , try renderFixture(arena.allocator(), "refuted_c_check.json", sockaddr));
}

test "a call into C without a model is inconclusive, even though the checker reports success" {
    var arena: std.heap.ArenaAllocator = .init(std.testing.allocator);
    defer arena.deinit();
    try std.testing.expect(std.mem.indexOf(u8, @embedFile("testdata/unmodelled.json"), "\"cProverStatus\":\"success\"") != null);
    try std.testing.expectEqualStrings(
        \\inconclusive: harness
        \\  the code calls C functions the checker has no body for: inet_pton
        \\  export a model of each from the harness, under the C name
        \\
    , try renderFixture(arena.allocator(), "unmodelled.json", .{}));
}
