//! Out-of-memory paths: the code that runs least and leaks most. One proof covers every
//! combination of allocations failing.

const std = @import("std");
const verifier = @import("verifier");

pub const panic = verifier.panic;

const Pair = struct { first: []u8, second: []u8 };

fn dupePair(gpa: std.mem.Allocator, first: []const u8, second: []const u8) !Pair {
    const first_copy = try gpa.dupe(u8, first);
    errdefer gpa.free(first_copy);
    return .{ .first = first_copy, .second = try gpa.dupe(u8, second) };
}

fn dupePairWithoutErrdefer(gpa: std.mem.Allocator, first: []const u8, second: []const u8) !Pair {
    const first_copy = try gpa.dupe(u8, first);
    return .{ .first = first_copy, .second = try gpa.dupe(u8, second) };
}

fn freeTwice(gpa: std.mem.Allocator, pair: Pair) void {
    gpa.free(pair.first);
    gpa.free(pair.second);
    gpa.free(pair.first);
}

/// Whichever allocation fails, nothing is left allocated, and the copies equal the originals.
export fn dupe_pair_never_leaks() void {
    var failing: verifier.FailingAllocator(32, 2) = .{};
    const gpa = failing.allocator();
    var first_buffer: [8]u8 = undefined;
    var second_buffer: [8]u8 = undefined;
    const first = verifier.prefix(u8, &first_buffer);
    const second = verifier.prefix(u8, &second_buffer);
    if (dupePair(gpa, first, second)) |pair| {
        verifier.assert(std.mem.eql(u8, pair.first, first));
        verifier.assert(std.mem.eql(u8, pair.second, second));
        gpa.free(pair.first);
        gpa.free(pair.second);
    } else |_| {}
    failing.assertNoLeaks();
}

/// Refuted: when the second allocation fails, the first copy is never freed.
export fn dupe_pair_without_errdefer_never_leaks() void {
    var failing: verifier.FailingAllocator(32, 2) = .{};
    const gpa = failing.allocator();
    var first_buffer: [8]u8 = undefined;
    var second_buffer: [8]u8 = undefined;
    const first = verifier.prefix(u8, &first_buffer);
    const second = verifier.prefix(u8, &second_buffer);
    if (dupePairWithoutErrdefer(gpa, first, second)) |pair| {
        gpa.free(pair.first);
        gpa.free(pair.second);
    } else |_| {}
    failing.assertNoLeaks();
}

/// Refuted: the first copy is freed twice.
export fn free_twice_is_caught() void {
    var failing: verifier.FailingAllocator(32, 2) = .{};
    const gpa = failing.allocator();
    const pair = dupePair(gpa, "ab", "cd") catch return;
    freeTwice(gpa, pair);
}
