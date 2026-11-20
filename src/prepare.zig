//! Rewrites the C that Zig generates so the checker reads it the way Zig means it. Mostly
//! that is about pointer comparisons:
//!
//! Zig compares pointers by address. C leaves `<` and `>=` between pointers into different
//! objects undefined, and CBMC models that by letting each such comparison come out either
//! way. The check `@memcpy` makes for overlapping arguments is exactly such a comparison, so
//! unprepared code reports an overlap between any two separate buffers. Comparing the
//! addresses as integers is defined, and CBMC evaluates it exactly.

const std = @import("std");

const Allocator = std.mem.Allocator;

/// Returns `c_source` with every ordered comparison of two pointers made on their addresses,
/// and with C assertion failures routed to the verifier. The result lives in `arena`.
pub fn forChecker(arena: Allocator, c_source: []const u8) Allocator.Error![]const u8 {
    var out: std.ArrayList(u8) = .empty;
    try out.ensureTotalCapacity(arena, c_source.len + c_source.len / 64);
    // Names of the pointer-typed parameters and temporaries of the function being read.
    var pointers: std.ArrayList([]const u8) = .empty;

    var lines = std.mem.splitScalar(u8, c_source, '\n');
    while (lines.next()) |line| {
        const defines_function = line.len != 0 and line[0] != ' ' and std.mem.endsWith(u8, line, ") {");
        if (defines_function) pointers.clearRetainingCapacity();
        const declares = line.len != 0 and line[0] == ' ' and std.mem.endsWith(u8, line, ";") and
            std.mem.indexOfAny(u8, line, "=(") == null;
        if (defines_function or declares) {
            var rest = line;
            while (std.mem.indexOfScalar(u8, rest, '*')) |star| {
                rest = rest[star + 1 ..];
                var name = rest;
                if (std.mem.startsWith(u8, name, "const ")) name = name["const ".len..];
                var end: usize = 0;
                while (end < name.len and (std.ascii.isAlphanumeric(name[end]) or name[end] == '_')) end += 1;
                if (end != 0) try pointers.append(arena, name[0..end]);
            }
        }

        if (!try compareLine(arena, &out, pointers.items, line)) try out.appendSlice(arena, line);
        if (lines.peek() != null) try out.append(arena, '\n');
    }
    // A failed `assert()` in translated C headers calls glibc's `__assert_fail`. CBMC gives that
    // name a meaning of its own and crashes on the call Zig generates, so the call is sent to
    // the shim instead, where it fails the proof like any other check.
    return std.mem.replaceOwned(u8, arena, out.items, "\"__assert_fail\"", "\"verifier_assert_fail\"");
}

/// Writes the rewritten form of `line` if it is `<target> = <pointer> <op> <pointer>;`.
fn compareLine(arena: Allocator, out: *std.ArrayList(u8), pointers: []const []const u8, line: []const u8) !bool {
    var tokens = std.mem.tokenizeScalar(u8, line, ' ');
    const target = tokens.next() orelse return false;
    if (!std.mem.eql(u8, tokens.next() orelse return false, "=")) return false;
    const left = tokens.next() orelse return false;
    const operator = tokens.next() orelse return false;
    const last = tokens.next() orelse return false;
    if (tokens.next() != null or !std.mem.endsWith(u8, last, ";")) return false;
    const right = last[0 .. last.len - 1];

    const ordered = for ([_][]const u8{ "<", "<=", ">", ">=" }) |candidate| {
        if (std.mem.eql(u8, operator, candidate)) break true;
    } else false;
    if (!ordered) return false;
    for ([_][]const u8{ left, right }) |operand| {
        for (pointers) |pointer| {
            if (std.mem.eql(u8, pointer, operand)) break;
        } else return false;
    }

    const indent = line[0 .. line.len - std.mem.trimStart(u8, line, " ").len];
    try out.print(arena, "{s}{s} = (uintptr_t){s} {s} (uintptr_t){s};", .{ indent, target, left, operator, right });
    return true;
}

const allocation_c = @embedFile("testdata/allocation.c");

test "the overlap check of a memcpy compares addresses" {
    var arena: std.heap.ArenaAllocator = .init(std.testing.allocator);
    defer arena.deinit();
    const prepared = try forChecker(arena.allocator(), allocation_c);
    try std.testing.expect(std.mem.indexOf(u8, allocation_c, "\n t11 = t13 >= t14;\n t16 = t12 >= t15;\n") != null);
    try std.testing.expect(std.mem.indexOf(
        u8,
        prepared,
        "\n t11 = (uintptr_t)t13 >= (uintptr_t)t14;\n t16 = (uintptr_t)t12 >= (uintptr_t)t15;\n",
    ) != null);
}

test "comparisons of integers are left as they are" {
    var arena: std.heap.ArenaAllocator = .init(std.testing.allocator);
    defer arena.deinit();
    const prepared = try forChecker(arena.allocator(), allocation_c);
    try std.testing.expect(std.mem.indexOf(u8, prepared, "\n t3 = t8 > t15;\n") != null);
    try std.testing.expect(std.mem.indexOf(u8, prepared, "\n t7 = t5 < t6;\n") != null);
}

test "nothing else in the file changes" {
    var arena: std.heap.ArenaAllocator = .init(std.testing.allocator);
    defer arena.deinit();
    const prepared = try forChecker(arena.allocator(), allocation_c);
    try std.testing.expectEqual(allocation_c.len + 4 * "(uintptr_t)".len, prepared.len);
}

test "a C assertion failure is sent to the verifier" {
    var arena: std.heap.ArenaAllocator = .init(std.testing.allocator);
    defer arena.deinit();
    const declaration = "zig_extern zig_noreturn void zig_e___assert_fail(void) zig_mangled(zig_e___assert_fail, \"__assert_fail\");";
    try std.testing.expectEqualStrings(
        "zig_extern zig_noreturn void zig_e___assert_fail(void) zig_mangled(zig_e___assert_fail, \"verifier_assert_fail\");",
        try forChecker(arena.allocator(), declaration),
    );
}
