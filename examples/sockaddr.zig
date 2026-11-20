//! Comparing two socket addresses, taken from a real event loop. The kernel reports each
//! address with a length, and nothing guarantees the length matches the contents.

const std = @import("std");
const verifier = @import("verifier");
const posix = std.posix;

pub const panic = verifier.panic;

const Storage = extern struct { bytes: [128]u8 align(8) };
const un_base = @offsetOf(posix.sockaddr.un, "path");

fn unixName(sa: *const posix.sockaddr, len: c_int) []const u8 {
    const un: *const posix.sockaddr.un = @ptrCast(@alignCast(sa));
    if (len <= un_base) return un.path[0..0];
    const n = @min(@as(usize, @intCast(len)) - un_base, un.path.len);
    if (un.path[0] == 0) return un.path[0..n];
    return un.path[0 .. std.mem.indexOfScalar(u8, un.path[0..n], 0) orelse n];
}

fn unixNameUnclamped(sa: *const posix.sockaddr, len: c_int) []const u8 {
    const un: *const posix.sockaddr.un = @ptrCast(@alignCast(sa));
    if (len <= un_base) return un.path[0..0];
    return un.path[0 .. @as(usize, @intCast(len)) - un_base];
}

fn same(a: *const posix.sockaddr, a_len: c_int, b: *const posix.sockaddr, b_len: c_int) bool {
    if (a.family != b.family) return false;
    if (a.family == posix.AF.UNIX) return std.mem.eql(u8, unixName(a, a_len), unixName(b, b_len));
    if (a.family == posix.AF.INET) {
        const x: *const posix.sockaddr.in = @ptrCast(@alignCast(a));
        const y: *const posix.sockaddr.in = @ptrCast(@alignCast(b));
        return x.port == y.port and x.addr == y.addr;
    }
    if (a.family == posix.AF.INET6) {
        const x: *const posix.sockaddr.in6 = @ptrCast(@alignCast(a));
        const y: *const posix.sockaddr.in6 = @ptrCast(@alignCast(b));
        if (x.port != y.port or !std.mem.eql(u8, &x.addr, &y.addr)) return false;
        return x.flowinfo == y.flowinfo and x.scope_id == y.scope_id;
    }
    return false;
}

/// No pair of addresses and lengths makes the comparison panic.
export fn same_never_panics() void {
    const a = verifier.any(Storage);
    const b = verifier.any(Storage);
    _ = same(@ptrCast(&a), verifier.any(c_int), @ptrCast(&b), verifier.any(c_int));
}

/// An address of a supported family is the same as itself, and the answer does not depend
/// on argument order.
export fn same_is_reflexive_and_symmetric() void {
    const a = verifier.any(Storage);
    const b = verifier.any(Storage);
    const a_len = verifier.any(c_int);
    const b_len = verifier.any(c_int);
    const family = @as(*const posix.sockaddr, @ptrCast(&a)).family;
    verifier.assume(family == posix.AF.UNIX or family == posix.AF.INET or family == posix.AF.INET6);
    verifier.assert(same(@ptrCast(&a), a_len, @ptrCast(&a), a_len));
    verifier.assert(same(@ptrCast(&a), a_len, @ptrCast(&b), b_len) == same(@ptrCast(&b), b_len, @ptrCast(&a), a_len));
}

/// Refuted: the length is trusted, so a large one indexes past `path`.
export fn unclamped_length_never_panics() void {
    const a = verifier.any(Storage);
    _ = unixNameUnclamped(@ptrCast(&a), verifier.any(c_int));
}

/// Refuted: an address of a family the comparison does not know is not even the same as itself.
export fn same_is_reflexive_for_every_family() void {
    const a = verifier.any(Storage);
    const len = verifier.any(c_int);
    verifier.assert(same(@ptrCast(&a), len, @ptrCast(&a), len));
}

/// Refuted: sixteen bytes hold an IPv4 address, but the family field can say IPv6, and the
/// comparison then reads past the end of the buffer. Zig has no safety check for memory
/// reached through a pointer cast; the checker's own bounds check finds it.
export fn short_buffer_is_never_read_past() void {
    const a: [16]u8 align(8) = verifier.any([16]u8);
    _ = same(@ptrCast(&a), a.len, @ptrCast(&a), a.len);
}
