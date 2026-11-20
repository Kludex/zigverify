//! Proofs about zuvloop's stream transport: the write path between `transport.write()` and
//! libuv. Every step calls libuv or CPython, so it is only reachable through the models.

const std = @import("std");
const verifier = @import("verifier");
const zuvloop = @import("zuvloop");
const cpython = @import("cpython").Model(zuvloop.py.c, 4);
const stream = @import("libuv_stream").Model(zuvloop.uv);

comptime {
    _ = @import("libuv");
}

pub const panic = verifier.panic;

/// The transport's `OPEN` and `CLOSING` flags, which are private to it.
const open: u32 = 1 << 6;
const closing: u32 = 1 << 1;

/// One proof per thing that can happen to a flush. Each fixes what the socket answers, so
/// the checker follows one branch of the write path instead of carrying all of them.
const Scenario = enum { socket_takes_everything, write_is_queued, socket_fails, closing };

/// zuvloop's own C helper for the slow-callback monitor.
export fn zuvloop_thread_cpu_time() i64 {
    return verifier.any(i64);
}

/// Flushing `count` pending writes, whatever the allocator and the protocol's callbacks do:
/// nothing panics or touches memory out of bounds, the handle is closed at most once, and
/// every buffer view the transport pinned is either released or handed to exactly one
/// queued libuv request, which releases it on completion.
fn flushReleasesEveryBuffer(comptime count: usize, comptime scenario: Scenario) void {
    cpython.reset();
    stream.reset();
    stream.socket = switch (scenario) {
        .socket_takes_everything => .takes_everything,
        .write_is_queued => .would_block,
        .socket_fails => .fails,
        .closing => .anything,
    };
    // zuvloop's cached exception types stay unset: the models never look at which exception
    // is raised, and fetching them would add ten more calls that can each fail.

    var handles: [6]usize = undefined;
    var state: zuvloop.loop.State = .{
        .uvloop = @ptrCast(&handles[0]),
        .idle = @ptrCast(&handles[1]),
        .timer = @ptrCast(&handles[2]),
        .sampler = @ptrCast(&handles[3]),
        .waker = @ptrCast(&handles[4]),
        .flusher = @ptrCast(&handles[5]),
        .block = &.{},
    };
    var loop_object = std.mem.zeroes(zuvloop.loop.LoopObject);
    loop_object.st = &state;
    var data: [4][2]u8 = undefined;
    var transport = std.mem.zeroes(zuvloop.transport.Transport);
    transport.loop = @ptrCast(&loop_object);
    transport.state = &state;
    transport.flags = if (scenario == .closing) open | closing else open;
    transport.high_water = verifier.any(usize);
    transport.low_water = verifier.any(usize);
    verifier.assume(transport.low_water <= transport.high_water);
    transport.cb_pause_writing = @ptrCast(cpython.anyValue());
    transport.cb_resume_writing = @ptrCast(cpython.anyValue());
    transport.pending_count = count;
    inline for (0..count) |index| {
        // Fixed lengths: how much of a write the socket takes then decides, without the
        // checker's help, how many buffers are left over, which fixes the request's layout.
        transport.pending_bufs[index] = .{ .base = &data[index], .len = data[index].len };
        transport.pending_views[index].obj = @ptrCast(cpython.anyValue());
        transport.pending_size += data[index].len;
    }

    zuvloop.transport.flushPending(&transport);

    verifier.assert(transport.pending_count == 0);
    const released = cpython.releasedBuffers();
    verifier.assert(released == count or (released == 0 and stream.queuedWrites() == 1));
}

export fn flush_releases_buffers_when_the_socket_takes_everything() void {
    flushReleasesEveryBuffer(2, .socket_takes_everything);
}

export fn flush_releases_buffers_when_the_write_is_queued() void {
    flushReleasesEveryBuffer(2, .write_is_queued);
}

export fn flush_releases_buffers_when_the_socket_fails() void {
    flushReleasesEveryBuffer(2, .socket_fails);
}

export fn flush_releases_buffers_when_the_transport_is_closing() void {
    flushReleasesEveryBuffer(2, .closing);
}
