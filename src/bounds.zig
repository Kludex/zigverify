//! Turns per-function unwind bounds, given by Zig function name, into CBMC's `--unwindset`
//! argument, which wants the C backend's mangled loop and function identifiers.
//!
//! One global bound is the wrong tool once a harness mixes a long input loop with a short
//! recursion: unwinding the recursion as deep as the loop is long multiplies the problem.

const std = @import("std");

const Allocator = std.mem.Allocator;

pub const Error = error{
    /// A bound is not of the form `function=count`.
    InvalidBound,
    /// No function of that name is in the generated C, so the bound would silently do nothing.
    UnknownFunction,
} || Allocator.Error;

/// `bounds` are `function=count` strings. `c_source` is the generated C and `loops_json` is
/// what `cbmc --show-loops --json-ui` printed for it. The result lives in `arena`.
pub fn unwindset(
    arena: Allocator,
    c_source: []const u8,
    loops_json: []const u8,
    bounds: []const []const u8,
) Error![]const u8 {
    var entries: std.ArrayList(u8) = .empty;
    for (bounds) |bound| {
        const equals = std.mem.lastIndexOfScalar(u8, bound, '=') orelse return error.InvalidBound;
        const count = bound[equals + 1 ..];
        _ = std.fmt.parseInt(u32, count, 10) catch return error.InvalidBound;
        // The C backend names a function `<zig name>__<id>`, so the separator ends the match.
        const prefix = try std.fmt.allocPrint(arena, "{s}__", .{bound[0..equals]});

        // A recursion is bounded under the function's own identifier, which only the source lists.
        var symbols: std.ArrayList([]const u8) = .empty;
        var at: usize = 0;
        while (std.mem.indexOfPos(u8, c_source, at, prefix)) |start| {
            at = start + prefix.len;
            if (start > 0 and isIdentifier(c_source[start - 1])) continue;
            // `<name>__<id>` or `<name>__anon_<n>__<id>` is a function; `<name>__enum_...` is a type.
            const tail = c_source[at..];
            if (!std.mem.startsWith(u8, tail, "anon_") and (tail.len == 0 or !std.ascii.isDigit(tail[0]))) continue;
            while (at < c_source.len and isIdentifier(c_source[at])) at += 1;
            const symbol = c_source[start..at];
            for (symbols.items) |known| {
                if (std.mem.eql(u8, known, symbol)) break;
            } else {
                try symbols.append(arena, symbol);
                try entries.print(arena, "{s}:{s},", .{ symbol, count });
            }
        }
        if (symbols.items.len == 0) return error.UnknownFunction;

        var rest = loops_json;
        while (std.mem.indexOf(u8, rest, prefix)) |start| {
            const end = std.mem.indexOfScalarPos(u8, rest, start, '"') orelse break;
            const loop = rest[start..end];
            // Loop names are `<function>.<n>`; the same text also appears as a bare function name.
            if (std.mem.indexOfScalar(u8, loop, '.') != null and (start == 0 or rest[start - 1] == '"')) {
                try entries.print(arena, "{s}:{s},", .{ loop, count });
            }
            rest = rest[end..];
        }
    }
    return std.mem.trimEnd(u8, entries.items, ",");
}

fn isIdentifier(byte: u8) bool {
    return std.ascii.isAlphanumeric(byte) or byte == '_';
}

const key_value_c = @embedFile("testdata/key_value.c");
const key_value_loops = @embedFile("testdata/key_value_loops.json");

test "a function's bound covers its recursion and each of its loops" {
    var arena: std.heap.ArenaAllocator = .init(std.testing.allocator);
    defer arena.deinit();
    try std.testing.expectEqualStrings(
        "key_value_Parser_next__295:3,key_value_indexOfOrEnd__213:40,key_value_indexOfOrEnd__213.0:40",
        try unwindset(arena.allocator(), key_value_c, key_value_loops, &.{
            "key_value_Parser_next=3",
            "key_value_indexOfOrEnd=40",
        }),
    );
}

test "a generic function is matched without its instantiation suffix" {
    var arena: std.heap.ArenaAllocator = .init(std.testing.allocator);
    defer arena.deinit();
    try std.testing.expectEqualStrings(
        "verifier_prefix__anon_190__294:9,verifier_prefix__anon_190__294.0:9",
        try unwindset(arena.allocator(), key_value_c, key_value_loops, &.{"verifier_prefix=9"}),
    );
}

test "a function that is not in the harness is an error, not a bound that does nothing" {
    var arena: std.heap.ArenaAllocator = .init(std.testing.allocator);
    defer arena.deinit();
    try std.testing.expectError(
        error.UnknownFunction,
        unwindset(arena.allocator(), key_value_c, key_value_loops, &.{"key_value_Parser=3"}),
    );
}

test "a bound without a count is rejected" {
    var arena: std.heap.ArenaAllocator = .init(std.testing.allocator);
    defer arena.deinit();
    try std.testing.expectError(
        error.InvalidBound,
        unwindset(arena.allocator(), key_value_c, key_value_loops, &.{"key_value_Parser_next"}),
    );
    try std.testing.expectError(
        error.InvalidBound,
        unwindset(arena.allocator(), key_value_c, key_value_loops, &.{"key_value_Parser_next=many"}),
    );
}
