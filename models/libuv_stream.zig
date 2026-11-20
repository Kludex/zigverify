//! A model of libuv's stream writes and handle lifecycle: `uv_try_write`, `uv_write`,
//! `uv_shutdown`, `uv_close` and the calls around them.
//!
//! `Model(uv)` takes the code under test's own declarations of libuv, and gives each model
//! the parameter types that binding declares. The socket takes any number of bytes or
//! refuses, and a queued write is accepted or refused. Callbacks are recorded and run only
//! when the harness says so, with `completeWrite` and `deliverClose`: the harness plays the
//! loop, and so decides the order things happen in.

const std = @import("std");
const verifier = @import("verifier");

pub fn Model(comptime uv: type) type {
    return struct {
        /// `UV_EAGAIN` and `UV_EPIPE` on every platform but Windows.
        const eagain: c_int = -11;
        const epipe: c_int = -32;

        /// What the socket does with an immediate write. Narrowing it splits one proof about
        /// every outcome into a cheaper proof per outcome.
        pub const Socket = enum { anything, takes_everything, takes_part, would_block, fails };

        pub var socket: Socket = .anything;
        /// Whether a queued write, a shutdown or the queue size may come out more than one way.
        /// Turning it off accepts every request and reports the queue exactly.
        pub var failures = true;

        const Queued = struct {
            request: Parameter(uv.uv_write, 0),
            callback: Parameter(uv.uv_write, 4),
            bytes: usize,
        };

        /// Accepted write requests, oldest first. libuv completes them in order.
        var queue: [4]Queued = undefined;
        var completed_writes: usize = 0;
        var accepted_bytes: usize = 0;
        var close_handle: Parameter(uv.uv_close, 0) = undefined;
        var close_callback: Parameter(uv.uv_close, 1) = undefined;
        var queued_writes: usize = 0;
        var queued_bytes: usize = 0;
        var closes: usize = 0;
        var shutdowns: usize = 0;

        /// Call first. Starts from a stream with nothing queued and an open handle.
        pub fn reset() void {
            socket = .anything;
            failures = true;
            queued_writes = 0;
            queued_bytes = 0;
            completed_writes = 0;
            accepted_bytes = 0;
            closes = 0;
            shutdowns = 0;
        }

        /// How many write requests libuv accepted and has not completed.
        pub fn queuedWrites() usize {
            return queued_writes;
        }

        /// How many bytes libuv has taken in all, written at once or in accepted requests.
        pub fn acceptedBytes() usize {
            return accepted_bytes;
        }

        /// Finishes the oldest queued write with `status`, as the loop would, by running its callback.
        pub fn completeWrite(status: c_int) void {
            verifier.assert(queued_writes != 0);
            const oldest = queue[completed_writes];
            completed_writes += 1;
            queued_writes -= 1;
            queued_bytes -= oldest.bytes;
            oldest.callback(oldest.request, status);
        }

        /// Runs the close callback. libuv does so only after every request has completed.
        pub fn deliverClose() void {
            verifier.assert(closes == 1 and queued_writes == 0);
            if (close_callback) |callback| callback(close_handle);
        }

        /// How many bytes libuv holds in accepted write requests.
        pub fn queuedBytes() usize {
            return queued_bytes;
        }

        /// How many times a handle was closed. Closing one twice aborts the real libuv.
        pub fn handleCloses() usize {
            return closes;
        }

        fn Parameter(comptime function: anytype, comptime index: usize) type {
            return @typeInfo(@TypeOf(function)).@"fn".params[index].type.?;
        }

        fn total(buffers: anytype, count: c_uint) usize {
            var sum: usize = 0;
            for (buffers[0..count]) |buffer| {
                // libuv reads every byte it is handed, so a wrong length is a read out of bounds.
                if (buffer.len != 0) _ = buffer.base[buffer.len - 1];
                sum += buffer.len;
            }
            return sum;
        }

        fn tryWrite(
            stream: Parameter(uv.uv_try_write, 0),
            buffers: Parameter(uv.uv_try_write, 1),
            count: c_uint,
        ) callconv(.c) c_int {
            _ = stream;
            verifier.assert(closes == 0);
            const available = total(buffers, count);
            // Each narrowed outcome returns directly: a fixed return value lets the checker drop
            // the branches it rules out, where an assumption about an arbitrary one would not.
            switch (socket) {
                .takes_everything => {
                    accepted_bytes += available;
                    return @intCast(available);
                },
                .would_block => return eagain,
                .fails => return epipe,
                .anything, .takes_part => {},
            }
            const written = verifier.any(c_int);
            verifier.assume(written > 0 and written <= available);
            if (socket == .takes_part) {
                verifier.assume(written < available);
                accepted_bytes += @intCast(written);
                return written;
            }
            if (verifier.any(bool)) return eagain;
            if (verifier.any(bool)) return epipe;
            accepted_bytes += @intCast(written);
            return written;
        }

        fn write(
            request: Parameter(uv.uv_write, 0),
            stream: Parameter(uv.uv_write, 1),
            buffers: Parameter(uv.uv_write, 2),
            count: c_uint,
            callback: Parameter(uv.uv_write, 4),
        ) callconv(.c) c_int {
            _ = stream;
            verifier.assert(closes == 0);
            const bytes = total(buffers, count);
            if (failures and verifier.any(bool)) return epipe;
            verifier.assert(completed_writes + queued_writes < queue.len);
            queue[completed_writes + queued_writes] = .{ .request = request, .callback = callback, .bytes = bytes };
            queued_writes += 1;
            queued_bytes += bytes;
            accepted_bytes += bytes;
            return 0;
        }

        fn streamGetWriteQueueSize(stream: Parameter(uv.uv_stream_get_write_queue_size, 0)) callconv(.c) usize {
            _ = stream;
            if (!failures) return queued_bytes;
            const size = verifier.any(usize);
            verifier.assume(size <= queued_bytes);
            return size;
        }

        fn shutdown(
            request: Parameter(uv.uv_shutdown, 0),
            stream: Parameter(uv.uv_shutdown, 1),
            callback: Parameter(uv.uv_shutdown, 2),
        ) callconv(.c) c_int {
            _ = request;
            _ = stream;
            _ = callback;
            if (closes != 0 or shutdowns != 0 or (failures and verifier.any(bool))) return epipe;
            shutdowns += 1;
            return 0;
        }

        fn close(handle: Parameter(uv.uv_close, 0), callback: Parameter(uv.uv_close, 1)) callconv(.c) void {
            // libuv aborts the process when a handle is closed twice.
            verifier.assert(closes == 0);
            closes += 1;
            close_handle = handle;
            close_callback = callback;
            // Closing cancels what is still queued; the harness completes those with an error.
        }

        fn isClosing(handle: Parameter(uv.uv_is_closing, 0)) callconv(.c) c_int {
            _ = handle;
            return @intFromBool(closes != 0);
        }

        fn readStop(stream: Parameter(uv.uv_read_stop, 0)) callconv(.c) c_int {
            _ = stream;
            return 0;
        }

        fn reqSize(kind: Parameter(uv.uv_req_size, 0)) callconv(.c) usize {
            _ = kind;
            return 192;
        }

        fn handleSize(kind: Parameter(uv.uv_handle_size, 0)) callconv(.c) usize {
            _ = kind;
            return 256;
        }

        fn prepareStart(
            prepare: Parameter(uv.uv_prepare_start, 0),
            callback: Parameter(uv.uv_prepare_start, 1),
        ) callconv(.c) c_int {
            _ = prepare;
            _ = callback;
            return 0;
        }

        fn unref(handle: Parameter(uv.uv_unref, 0)) callconv(.c) void {
            _ = handle;
        }

        fn stop(loop: Parameter(uv.uv_stop, 0)) callconv(.c) void {
            _ = loop;
        }

        fn hrtime() callconv(.c) u64 {
            return verifier.any(u64);
        }

        fn idleStart(idle: Parameter(uv.uv_idle_start, 0), callback: Parameter(uv.uv_idle_start, 1)) callconv(.c) c_int {
            _ = idle;
            _ = callback;
            return 0;
        }

        fn idleStop(idle: Parameter(uv.uv_idle_stop, 0)) callconv(.c) c_int {
            _ = idle;
            return 0;
        }

        comptime {
            @export(&tryWrite, .{ .name = "uv_try_write" });
            @export(&write, .{ .name = "uv_write" });
            @export(&streamGetWriteQueueSize, .{ .name = "uv_stream_get_write_queue_size" });
            @export(&shutdown, .{ .name = "uv_shutdown" });
            @export(&close, .{ .name = "uv_close" });
            @export(&isClosing, .{ .name = "uv_is_closing" });
            @export(&readStop, .{ .name = "uv_read_stop" });
            @export(&reqSize, .{ .name = "uv_req_size" });
            @export(&handleSize, .{ .name = "uv_handle_size" });
            @export(&prepareStart, .{ .name = "uv_prepare_start" });
            @export(&unref, .{ .name = "uv_unref" });
            @export(&stop, .{ .name = "uv_stop" });
            @export(&hrtime, .{ .name = "uv_hrtime" });
            @export(&idleStart, .{ .name = "uv_idle_start" });
            @export(&idleStop, .{ .name = "uv_idle_stop" });
        }
    };
}
