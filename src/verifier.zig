//! Harness support for proving Zig code with a C bounded model checker.
//!
//! A harness is an `export fn` that builds arbitrary inputs with `any`, narrows them with
//! `assume`, calls the code under test, and states what must hold with `assert`. The
//! checker then considers every input at once.

const std = @import("std");

/// Assign to `pub const panic` in the harness root so every safety check becomes a proof failure.
pub const panic = @import("panic.zig");

extern fn verifier_any(out: *anyopaque, len: usize) void;
extern fn verifier_assume(ok: bool) void;
extern fn verifier_check(ok: bool) void;

/// Discards every input for which `ok` is false.
pub fn assume(ok: bool) void {
    verifier_assume(ok);
}

/// Fails the proof if any remaining input makes `ok` false.
pub fn assert(ok: bool) void {
    verifier_check(ok);
}

/// An arbitrary value of `T`: the proof covers every value the type can hold.
///
/// Pointers and slices are rejected, because an arbitrary address proves nothing.
/// Point into a buffer the harness owns instead; see `prefix`.
pub fn any(comptime T: type) T {
    switch (@typeInfo(T)) {
        .void => return {},
        .bool => return any(u8) & 1 == 1,
        .int => |int| {
            const Backing = std.meta.Int(.unsigned, @sizeOf(T) * 8);
            var backing: Backing = undefined;
            verifier_any(&backing, @sizeOf(Backing));
            const Unsigned = std.meta.Int(.unsigned, int.bits);
            return @bitCast(@as(Unsigned, @truncate(backing)));
        },
        .float => return @bitCast(any(std.meta.Int(.unsigned, @bitSizeOf(T)))),
        .array => |array| {
            var value: T = undefined;
            if (array.child == u8) {
                verifier_any(&value, value.len);
            } else {
                for (&value) |*item| item.* = any(array.child);
            }
            return value;
        },
        .@"enum" => |info| {
            if (!info.is_exhaustive) return @enumFromInt(any(info.tag_type));
            const tag = any(info.tag_type);
            inline for (info.fields) |field| {
                if (tag == field.value) return @enumFromInt(tag);
            }
            assume(false);
            unreachable;
        },
        .optional => |optional| return if (any(bool)) any(optional.child) else null,
        .@"struct" => |info| {
            if (info.backing_integer) |Backing| return @bitCast(any(Backing));
            var value: T = undefined;
            inline for (info.fields) |field| {
                if (!field.is_comptime) @field(value, field.name) = any(field.type);
            }
            return value;
        },
        else => @compileError("verifier.any does not support " ++ @typeName(T)),
    }
}

/// Fills `buffer` with arbitrary items and returns an arbitrary-length prefix of it, so one
/// proof covers every input from empty up to `buffer.len` items.
pub fn prefix(comptime T: type, buffer: []T) []T {
    for (buffer) |*item| item.* = any(T);
    const len = any(usize);
    assume(len <= buffer.len);
    return buffer[0..len];
}

/// An allocator whose every allocation may fail, so one proof covers every out-of-memory
/// path at once, and which knows what is live, so the proof can rule out leaks and double frees.
///
/// It serves up to `max_live` simultaneous allocations out of `capacity` bytes and never
/// reuses memory. Running out of either is reported to the caller as one more allocation
/// failure. Freed memory is overwritten with arbitrary bytes, so a read after free cannot
/// be relied on by any property that still has to hold.
pub fn FailingAllocator(comptime capacity: usize, comptime max_live: usize) type {
    return struct {
        buffer: [capacity]u8 align(16) = undefined,
        used: usize = 0,
        live: [max_live]?[*]u8 = @splat(null),

        const Self = @This();

        pub fn allocator(self: *Self) std.mem.Allocator {
            return .{ .ptr = self, .vtable = &.{ .alloc = alloc, .resize = resize, .remap = remap, .free = free } };
        }

        /// Fails the proof if anything allocated has not been freed.
        pub fn assertNoLeaks(self: *const Self) void {
            // Unrolled at comptime, like every loop here, so the allocator needs no unwind bound.
            inline for (0..max_live) |slot| {
                if (self.live[slot] != null) panic.fail(.leak, 0, 0);
            }
        }

        fn alloc(context: *anyopaque, len: usize, alignment: std.mem.Alignment, _: usize) ?[*]u8 {
            const self: *Self = @ptrCast(@alignCast(context));
            if (any(bool)) return null;
            if (alignment.toByteUnits() > 16) return null;
            const start = alignment.forward(self.used);
            if (start > capacity or len > capacity - start) return null;
            inline for (0..max_live) |slot| {
                if (self.live[slot] == null) {
                    const memory = self.buffer[start..][0..len];
                    verifier_any(memory.ptr, len);
                    self.live[slot] = memory.ptr;
                    self.used = start + len;
                    return memory.ptr;
                }
            }
            return null;
        }

        fn resize(_: *anyopaque, _: []u8, _: std.mem.Alignment, _: usize, _: usize) bool {
            return false;
        }

        fn remap(_: *anyopaque, _: []u8, _: std.mem.Alignment, _: usize, _: usize) ?[*]u8 {
            return null;
        }

        fn free(context: *anyopaque, memory: []u8, _: std.mem.Alignment, _: usize) void {
            const self: *Self = @ptrCast(@alignCast(context));
            inline for (0..max_live) |slot| {
                if (self.live[slot] == memory.ptr) {
                    self.live[slot] = null;
                    verifier_any(memory.ptr, memory.len);
                    return;
                }
            }
            panic.fail(.invalid_free, 0, 0);
        }
    };
}
