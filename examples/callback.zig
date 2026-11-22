//! A callback stored on one path and called later, the way an event loop holds the function
//! to run when a handle closes. Whether it was stored depends on the input, so the checker
//! cannot tell which function the pointer holds, and the proof names the possibilities.

const verifier = @import("verifier");

pub const panic = verifier.panic;

var registered: ?*const fn (*u32) callconv(.c) void = null;

fn register(callback: *const fn (*u32) callconv(.c) void) void {
    registered = callback;
}

fn fire(counter: *u32) void {
    if (registered) |callback| callback(counter);
}

fn count(counter: *u32) callconv(.c) void {
    counter.* += 1;
}

/// Whether or not the callback was registered, firing counts at most once, and exactly once
/// when it was.
export fn the_registered_callback_counts_once() void {
    const registers = verifier.any(bool);
    if (registers) register(count);
    var counter: u32 = 0;
    fire(&counter);
    verifier.assert(counter == @intFromBool(registers));
}
