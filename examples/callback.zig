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

fn skip(counter: *u32) callconv(.c) void {
    _ = counter;
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

/// Refuted: the build names `skip` as the only function the call may reach, which is wrong,
/// and the checker says so. A target list is checked, not taken on trust.
export fn a_wrong_target_list_is_caught() void {
    register(count);
    var counter: u32 = 0;
    fire(&counter);
    skip(&counter);
}
