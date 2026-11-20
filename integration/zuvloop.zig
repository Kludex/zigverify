//! Proofs about zuvloop's address conversion, the code between Python tuples and
//! `struct sockaddr`. It calls CPython and libuv on every path, so it is only reachable
//! through the models.

const std = @import("std");
const verifier = @import("verifier");
const zuvloop = @import("zuvloop");
const cpython = @import("cpython").Model(zuvloop.py.c, 16);

comptime {
    _ = @import("libuv");
}

pub const panic = verifier.panic;

/// Building a socket address never panics, never reads or writes outside a buffer, raises a
/// Python error exactly when it fails, and on success reports a length that fits the storage.
fn fromPythonIsSafe(family: c_int, address: *zuvloop.py.c.PyObject) void {
    var storage: zuvloop.addr.Storage = .{};
    if (zuvloop.addr.fromPython(family, @ptrCast(address), &storage)) |len| {
        verifier.assert(len > 0);
        verifier.assert(len <= @sizeOf(zuvloop.addr.Storage));
        verifier.assert(!cpython.errorIsSet());
    } else |_| {
        verifier.assert(cpython.errorIsSet());
    }
}

/// A filesystem path or abstract name, as text or bytes, or any other single object.
export fn unix_address_from_python_is_safe() void {
    cpython.reset();
    zuvloop.py.initConstants() catch return;
    fromPythonIsSafe(zuvloop.addr.AF_UNIX, cpython.anyValue());
}

/// A `(host, port[, flowinfo, scope_id])` tuple of any length and contents, for any other family.
export fn ip_address_from_python_is_safe() void {
    cpython.reset();
    zuvloop.py.initConstants() catch return;
    const family = verifier.any(c_int);
    verifier.assume(family != zuvloop.addr.AF_UNIX);
    fromPythonIsSafe(family, cpython.anyTuple());
}

/// An object that is not a tuple, for any family that needs one.
export fn non_tuple_from_python_is_safe() void {
    cpython.reset();
    zuvloop.py.initConstants() catch return;
    const family = verifier.any(c_int);
    verifier.assume(family != zuvloop.addr.AF_UNIX);
    fromPythonIsSafe(family, cpython.anyValue());
}

/// Whatever the kernel hands back, turning it into a Python address never panics and never
/// reads outside the storage, and a failure always leaves a Python error set.
export fn to_python_is_safe() void {
    cpython.reset();
    zuvloop.py.initConstants() catch return;
    const storage = verifier.any(zuvloop.addr.Storage);
    const len = verifier.any(c_int);
    verifier.assume(len >= 0 and len <= @sizeOf(zuvloop.addr.Storage));
    if (zuvloop.addr.toPython(storage.constPtr(), len)) |_| {} else |_| {
        verifier.assert(cpython.errorIsSet());
    }
}
