//! The smallest useful proofs: the midpoint of two indices, the bug that sat in binary
//! searches for decades, and its fix.

const verifier = @import("verifier");

pub const panic = verifier.panic;

fn midpointNaive(low: u32, high: u32) u32 {
    return (low + high) / 2;
}

fn midpoint(low: u32, high: u32) u32 {
    return low + (high - low) / 2;
}

/// Refuted: the sum overflows when both indices are large.
export fn naive_midpoint_never_panics() void {
    _ = midpointNaive(verifier.any(u32), verifier.any(u32));
}

/// For every ordered pair, the midpoint lies between the two.
export fn midpoint_is_between() void {
    const low = verifier.any(u32);
    const high = verifier.any(u32);
    verifier.assume(low <= high);
    const mid = midpoint(low, high);
    verifier.assert(low <= mid);
    verifier.assert(mid <= high);
}

/// Refuted: the midpoint is only strictly below `high` when the two differ.
export fn midpoint_is_below_high() void {
    const low = verifier.any(u32);
    const high = verifier.any(u32);
    verifier.assume(low <= high);
    verifier.assert(low <= midpoint(low, high));
    verifier.assert(midpoint(low, high) < high);
}

/// Counting the zero bytes of any input up to 16 bytes never panics. The loop runs up to 16
/// times, so the proof needs an unwind bound above that.
export fn count_zeros_never_panics() void {
    var buffer: [16]u8 = undefined;
    var zeros: u8 = 0;
    for (verifier.prefix(u8, &buffer)) |byte| {
        if (byte == 0) zeros += 1;
    }
    verifier.assert(zeros <= 16);
}
