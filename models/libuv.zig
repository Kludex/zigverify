//! A model of the libuv calls that convert between text and socket addresses.
//!
//! Each function may fail, and on success writes an address whose contents are arbitrary
//! apart from the fields libuv documents. Importing this file is enough to install the
//! models: they are exported under libuv's own names.

const std = @import("std");
const verifier = @import("verifier");

const posix = std.posix;

/// `UV_EINVAL` and `UV_ENOSPC` on every platform but Windows.
const einval: c_int = -22;
const enospc: c_int = -28;

export fn uv_ip4_addr(ip: [*:0]const u8, port: c_int, addr: *posix.sockaddr.in) c_int {
    // libuv reads the text up to its terminator, so text without one is a read out of bounds.
    _ = std.mem.len(ip);
    addr.* = verifier.any(posix.sockaddr.in);
    if (verifier.any(bool)) return einval;
    addr.family = posix.AF.INET;
    addr.port = std.mem.nativeToBig(u16, @truncate(@as(c_uint, @bitCast(port))));
    return 0;
}

export fn uv_ip6_addr(ip: [*:0]const u8, port: c_int, addr: *posix.sockaddr.in6) c_int {
    _ = std.mem.len(ip);
    addr.* = verifier.any(posix.sockaddr.in6);
    if (verifier.any(bool)) return einval;
    addr.family = posix.AF.INET6;
    addr.port = std.mem.nativeToBig(u16, @truncate(@as(c_uint, @bitCast(port))));
    return 0;
}

/// Writes a terminated name into `dst`, or fails when it does not fit.
export fn uv_ip_name(src: *const posix.sockaddr, dst: [*]u8, size: usize) c_int {
    _ = src;
    if (size == 0 or verifier.any(bool)) return enospc;
    terminated(dst[0..size]);
    return 0;
}

export fn uv_strerror_r(err: c_int, buf: [*]u8, buflen: usize) [*:0]u8 {
    _ = err;
    verifier.assert(buflen != 0);
    terminated(buf[0..buflen]);
    return @ptrCast(buf);
}

fn terminated(buffer: []u8) void {
    for (buffer) |*byte| byte.* = verifier.any(u8);
    const end = verifier.any(usize);
    verifier.assume(end < buffer.len);
    buffer[end] = 0;
}
