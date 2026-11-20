//! The other harnesses are compiled so that `std.mem.eql` compares one byte at a time, which
//! leaves the chunked comparison that release builds use unproved. This harness is compiled
//! without that switch and proves the two agree at every length up to 64.
//!
//! Each length is a separate, fixed-size comparison. That is what keeps it cheap: the
//! chunked code only becomes expensive when the length is unknown.

const std = @import("std");
const verifier = @import("verifier");

pub const panic = verifier.panic;

fn eqlByteByByte(a: []const u8, b: []const u8) bool {
    for (a, b) |x, y| {
        if (x != y) return false;
    }
    return true;
}

export fn eql_agrees_with_a_byte_loop() void {
    const a = verifier.any([64]u8);
    const b = verifier.any([64]u8);
    inline for (0..65) |len| {
        verifier.assert(std.mem.eql(u8, a[0..len], b[0..len]) == eqlByteByByte(a[0..len], b[0..len]));
    }
}
