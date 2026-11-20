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
    // The queued write runs the protocol's callbacks. With those also free to fail, the proof
    // takes over half an hour, so this one scenario assumes Python calls succeed.
    if (scenario == .write_is_queued) cpython.failures = false;
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

/// The transport `write()` and `close()` act on, where a callback can reach it.
var registered: [1024]u8 align(16) = @splat(0);
var loop_state: zuvloop.loop.State = undefined;
var loop_instance: zuvloop.loop.LoopObject = undefined;
var loop_handles: [6]usize = undefined;

/// `UV_EPIPE` and `UV_ECANCELED` on every platform but Windows.
const epipe: c_int = -32;
const ecanceled: c_int = -125;

fn closeFromCallback() void {
    _ = cpython.method("close").?(@ptrCast(&registered), null);
}

/// An open transport inside a running loop, on a socket that takes nothing, with a healthy
/// interpreter and a libuv that accepts every request: one path, so many calls stay cheap.
fn openTransport() *zuvloop.transport.Transport {
    cpython.reset();
    stream.reset();
    cpython.failures = false;
    stream.failures = false;
    stream.socket = .would_block;
    // `asyncio.Transport` is an object header and one slot, which the transport checks.
    cpython.attribute.tp_basicsize = @offsetOf(zuvloop.transport.Transport, "loop");
    zuvloop.py.initConstants() catch unreachable;
    zuvloop.handle.register(cpython.anyValue()) catch unreachable;
    zuvloop.transport.register(cpython.anyValue()) catch unreachable;

    loop_state = .{
        .uvloop = @ptrCast(&loop_handles[0]),
        .idle = @ptrCast(&loop_handles[1]),
        .timer = @ptrCast(&loop_handles[2]),
        .sampler = @ptrCast(&loop_handles[3]),
        .waker = @ptrCast(&loop_handles[4]),
        .flusher = @ptrCast(&loop_handles[5]),
        .block = &.{},
        // Inside a running loop, writes are batched until the end of the iteration.
        .running = true,
        // The transport's own handle, which creating a real transport counts.
        .external_handles = 1,
    };
    loop_instance = std.mem.zeroes(zuvloop.loop.LoopObject);
    loop_instance.st = &loop_state;
    registered = @splat(0);
    const transport: *zuvloop.transport.Transport = @ptrCast(&registered);
    // The loop holds one reference to a live transport, which the close callback gives up.
    @as(*usize, @ptrCast(transport)).* = 2;
    transport.loop = @ptrCast(&loop_instance);
    transport.state = &loop_state;
    transport.flags = open;
    transport.cb_pause_writing = @ptrCast(cpython.anyValue());
    transport.cb_connection_lost = @ptrCast(cpython.anyValue());
    // libuv handles carry a pointer back to their owner, which creating a transport sets.
    const handle_offset = std.mem.alignForward(usize, @sizeOf(zuvloop.transport.Transport), 16);
    zuvloop.uv.setData(&registered[handle_offset], transport);
    return transport;
}

fn writeFiveBytes(transport: *zuvloop.transport.Transport) void {
    const write = cpython.method("write").?;
    inline for (0..5) |_| {
        verifier.assert(write(@ptrCast(transport), cpython.anyBytes(1)) != null);
    }
}

/// Five one-byte writes in one loop iteration. The batch holds four, so the fifth flushes
/// it, which queues four bytes and pauses the protocol.
///
/// asyncio sends every byte passed to `write()` before a `close()` that came later. So
/// after the fifth `write()` returns, all five bytes must be either with libuv or pending.
export fn fifth_write_is_kept() void {
    const transport = openTransport();
    writeFiveBytes(transport);
    verifier.assert(stream.queuedBytes() + transport.pending_size == 5);
}

/// Refuted, a bug in zuvloop: the protocol calls `close()` from inside `pause_writing`, which
/// the fifth `write()` triggered, and the transport then drops that write's byte.
export fn fifth_write_is_kept_when_pause_writing_closes() void {
    const transport = openTransport();
    cpython.on_call = closeFromCallback;
    writeFiveBytes(transport);
    verifier.assert(stream.queuedBytes() + transport.pending_size == 5);
}

/// When libuv finishes the queued write, the transport releases the four buffers it pinned
/// for it, and keeps the fifth, which is still waiting to be flushed.
export fn completed_write_releases_its_buffers() void {
    const transport = openTransport();
    writeFiveBytes(transport);
    stream.completeWrite(0);
    verifier.assert(cpython.releasedBuffers() == 4);
    verifier.assert(transport.write_buffer_size == 0);
    verifier.assert(transport.pending_size == 1);
    verifier.assert(stream.handleCloses() == 0);
}

/// `close()` with data outstanding sends all of it first: the pending byte is flushed, the
/// handle stays open until both requests finish, is then closed exactly once, and the
/// close callback marks the connection lost. Every buffer is released.
export fn close_drains_then_closes_once() void {
    const transport = openTransport();
    writeFiveBytes(transport);
    closeFromCallback();
    verifier.assert(stream.acceptedBytes() == 5);
    verifier.assert(stream.handleCloses() == 0);
    stream.completeWrite(0);
    verifier.assert(stream.handleCloses() == 0);
    stream.completeWrite(0);
    verifier.assert(stream.handleCloses() == 1);
    verifier.assert(cpython.releasedBuffers() == 5);
    stream.deliverClose();
    verifier.assert(loop_state.closing_handles == 0);
}

/// A write that fails closes the transport at once, exactly once, and drops what was still
/// pending without leaking its buffer.
export fn failed_write_closes_once_and_releases_everything() void {
    const transport = openTransport();
    writeFiveBytes(transport);
    stream.completeWrite(epipe);
    verifier.assert(stream.handleCloses() == 1);
    verifier.assert(cpython.releasedBuffers() == 5);
    verifier.assert(transport.pending_count == 0);
    stream.deliverClose();
    verifier.assert(loop_state.closing_handles == 0);
}

/// `abort()` drops what was still pending and closes the handle at once, exactly once. The
/// queued write that libuv then cancels releases its buffers without closing again.
export fn abort_discards_pending_and_closes_once() void {
    const transport = openTransport();
    writeFiveBytes(transport);
    verifier.assert(cpython.method("abort").?(@ptrCast(transport), null) != null);
    verifier.assert(stream.handleCloses() == 1);
    verifier.assert(transport.pending_count == 0);
    verifier.assert(cpython.releasedBuffers() == 1);
    stream.completeWrite(ecanceled);
    verifier.assert(stream.handleCloses() == 1);
    verifier.assert(cpython.releasedBuffers() == 5);
    stream.deliverClose();
}

/// `write_eof()` half-closes only after everything written before it has gone out, does so
/// exactly once, and a `write()` after it is refused with an error.
export fn write_eof_shuts_down_after_the_data() void {
    const transport = openTransport();
    writeFiveBytes(transport);
    verifier.assert(cpython.method("write_eof").?(@ptrCast(transport), null) != null);
    verifier.assert(stream.acceptedBytes() == 5);
    verifier.assert(stream.shutdownRequests() == 0);
    stream.completeWrite(0);
    verifier.assert(stream.shutdownRequests() == 0);
    stream.completeWrite(0);
    verifier.assert(stream.shutdownRequests() == 1);
    verifier.assert(cpython.method("write").?(@ptrCast(transport), cpython.anyBytes(1)) == null);
    verifier.assert(cpython.errorIsSet());
    verifier.assert(stream.handleCloses() == 0);
}

/// `writelines()` of two buffers batches both, and releases the references it took on the way.
export fn writelines_batches_every_buffer() void {
    const transport = openTransport();
    const lines = cpython.tupleOf(&.{ cpython.anyBytes(1), cpython.anyBytes(1) });
    verifier.assert(cpython.method("writelines").?(@ptrCast(transport), lines) != null);
    verifier.assert(transport.pending_count == 2);
    verifier.assert(transport.pending_size == 2);
    verifier.assert(cpython.releasedBuffers() == 0);
}

/// `set_write_buffer_limits()` with no arguments sets the documented defaults.
export fn write_buffer_limits_default_to_64k_and_16k() void {
    const transport = openTransport();
    const Fastcall = *const fn (
        ?*zuvloop.py.c.PyObject,
        [*c]?*zuvloop.py.c.PyObject,
        zuvloop.py.c.Py_ssize_t,
        ?*zuvloop.py.c.PyObject,
    ) callconv(.c) ?*zuvloop.py.c.PyObject;
    const set_limits: Fastcall = @ptrCast(cpython.method("set_write_buffer_limits").?);
    // The interpreter passes a valid array even for no arguments.
    var no_arguments: [1]?*zuvloop.py.c.PyObject = .{null};
    verifier.assert(set_limits(@ptrCast(transport), &no_arguments, 0, null) != null);
    verifier.assert(transport.high_water == 64 * 1024);
    verifier.assert(transport.low_water == 16 * 1024);
}

/// A readable event hands the protocol its data with one call, and the peer closing its
/// side, when the protocol does not ask to keep the connection, closes the handle once.
export fn read_delivers_data_and_eof_closes_once() void {
    const transport = openTransport();
    transport.cb_data_received = @ptrCast(cpython.anyValue());
    transport.cb_eof_received = @ptrCast(cpython.anyValue());
    // The smallest read size the transport uses.
    transport.read_size = 16 * 1024;
    verifier.assert(cpython.method("_start_reading").?(@ptrCast(transport), null) != null);
    verifier.assert(stream.reading());

    const before = cpython.calls();
    stream.deliverRead(3);
    verifier.assert(cpython.calls() == before + 1);
    verifier.assert(stream.handleCloses() == 0);

    stream.deliverRead(stream.eof);
    verifier.assert(cpython.calls() == before + 2);
    verifier.assert(!stream.reading());
    verifier.assert(stream.handleCloses() == 1);
    stream.deliverClose();
}

/// `pause_reading()` stops libuv reading and `resume_reading()` starts it again, after which
/// data still reaches the protocol.
export fn pause_and_resume_reading_stop_and_restart_reads() void {
    const transport = openTransport();
    transport.cb_data_received = @ptrCast(cpython.anyValue());
    transport.read_size = 16 * 1024;
    verifier.assert(cpython.method("_start_reading").?(@ptrCast(transport), null) != null);
    verifier.assert(cpython.method("pause_reading").?(@ptrCast(transport), null) != null);
    verifier.assert(!stream.reading());
    verifier.assert(cpython.method("resume_reading").?(@ptrCast(transport), null) != null);
    verifier.assert(stream.reading());
    const before = cpython.calls();
    stream.deliverRead(3);
    verifier.assert(cpython.calls() == before + 1);
}

/// For a buffered protocol, a read asks `get_buffer` for memory, lets libuv fill it, reports
/// the count through `buffer_updated`, and releases the view of the buffer exactly once.
export fn buffered_read_fills_the_protocols_buffer() void {
    const transport = openTransport();
    // The transport's `BUFFERED` flag, which is private to it.
    transport.flags |= 1 << 4;
    transport.cb_get_buffer = @ptrCast(cpython.anyValue());
    transport.cb_buffer_updated = @ptrCast(cpython.anyValue());
    cpython.call_result = cpython.anyBytes(4);
    verifier.assert(cpython.method("_start_reading").?(@ptrCast(transport), null) != null);
    const before = cpython.calls();
    stream.deliverRead(2);
    verifier.assert(cpython.calls() == before + 2);
    verifier.assert(cpython.releasedBuffers() == 1);
    verifier.assert(stream.handleCloses() == 0);
}
