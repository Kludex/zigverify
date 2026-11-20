//! A model of the part of the CPython C API that takes arguments apart and reports errors.
//!
//! Objects are tuples, text, bytes, integers, the three constants, or opaque. A harness builds
//! its arguments with `anyValue` and `anyTuple`, one proof per shape of argument. The functions
//! behave as CPython documents, and wherever the real one can fail, the model may fail too.
//! The model also keeps the books a reviewer would: a reference the code did not own must
//! not be released, and a reference it was given must not be dropped.
//!
//! `Model(c, max_text)` takes the code under test's own translation of `Python.h`, so both
//! sides agree on every type. Referencing the returned type installs the models under
//! CPython's names.

const std = @import("std");
const verifier = @import("verifier");

/// `max_text` is the longest text or bytes object, and tuples hold up to four items.
pub fn Model(comptime c: type, comptime max_text: usize) type {
    return struct {
        const Kind = enum(u8) { none, false, true, tuple, text, bytes, int, other };

        const Object = extern struct {
            head: c.PyObject,
            kind: Kind,
            /// Whether the code under test owns a reference to this object.
            owned: bool,
            len: usize,
            int: isize,
            items: [4]?*Object,
            text: [max_text + 1]u8,
        };

        var types: [@typeInfo(Kind).@"enum".fields.len]c.PyTypeObject = undefined;
        var pool: [24]Object = undefined;
        var used: usize = 0;
        var error_set = false;
        var owned_references: usize = 0;
        var buffer_releases: usize = 0;
        /// What `PyType_GenericAlloc` hands out: zeroed memory for one instance of an extension type.
        var instance: [1024]u8 align(16) = undefined;
        var thread_state: [64]u8 align(16) = undefined;

        /// Call first. Starts from an interpreter with no objects and no error set.
        pub fn reset() void {
            for (&types, 0..) |*object_type, kind| {
                object_type.* = std.mem.zeroes(c.PyTypeObject);
                object_type.tp_flags = switch (@as(Kind, @enumFromInt(kind))) {
                    .tuple => c.Py_TPFLAGS_TUPLE_SUBCLASS,
                    .text => c.Py_TPFLAGS_UNICODE_SUBCLASS,
                    .bytes => c.Py_TPFLAGS_BYTES_SUBCLASS,
                    .int => c.Py_TPFLAGS_LONG_SUBCLASS,
                    .none, .false, .true, .other => 0,
                };
            }
            used = 0;
            error_set = false;
            owned_references = 0;
            buffer_releases = 0;
            // The constants take the first three slots, so `Py_GetConstantBorrowed` can index them.
            _ = create(.none, false);
            _ = create(.false, false);
            _ = create(.true, false);
        }

        /// An arbitrary text, bytes, integer or opaque object, with arbitrary contents. The code
        /// under test borrows it and must not release it.
        pub fn anyValue() *c.PyObject {
            const kind = verifier.any(Kind);
            verifier.assume(kind == .text or kind == .bytes or kind == .int or kind == .other);
            const object = create(kind, false);
            object.int = verifier.any(isize);
            object.len = verifier.any(usize);
            verifier.assume(object.len <= max_text);
            object.text = verifier.any([max_text + 1]u8);
            // CPython terminates the buffer of every text and bytes object.
            object.text[object.len] = 0;
            return @ptrCast(object);
        }

        /// An arbitrary tuple of up to four items, each `None` or an arbitrary value.
        pub fn anyTuple() *c.PyObject {
            const tuple = create(.tuple, false);
            tuple.len = verifier.any(usize);
            verifier.assume(tuple.len <= tuple.items.len);
            // Every slot gets an item, used or not: an object taken from the pool only on some
            // inputs would make every later pool index depend on the input, which is costly.
            inline for (0..tuple.items.len) |index| {
                const value = anyValue();
                tuple.items[index] = if (verifier.any(bool)) &pool[@intFromEnum(Kind.none)] else @ptrCast(@alignCast(value));
            }
            return @ptrCast(tuple);
        }

        /// How many buffer views with an owner the code has released.
        pub fn releasedBuffers() usize {
            return buffer_releases;
        }

        pub fn errorIsSet() bool {
            return error_set;
        }

        /// Fails the proof if the code under test still holds a reference it was given.
        pub fn assertNoLeakedReferences() void {
            verifier.assert(owned_references == 0);
        }

        fn create(kind: Kind, owned: bool) *Object {
            // Running out is a limit of the model, and must not pass for a proof.
            verifier.assert(used < pool.len);
            const object = &pool[used];
            used += 1;
            object.head = std.mem.zeroes(c.PyObject);
            // The reference count is the first word of every object. The constants are
            // immortal, which CPython marks with the top bits of the low half.
            const count: *usize = @ptrCast(&object.head);
            count.* = if (used <= 3) 0xC0000000 else 1;
            object.head.ob_type = &types[@intFromEnum(kind)];
            object.kind = kind;
            object.owned = owned;
            object.len = 0;
            object.int = 0;
            object.items = @splat(null);
            if (owned) owned_references += 1;
            return object;
        }

        /// A call that returns a new reference: it may fail for lack of memory.
        fn newReference() ?*c.PyObject {
            // Taken from the pool before deciding, for the reason given in `anyObject`.
            const object = create(.other, false);
            if (verifier.any(bool)) {
                error_set = true;
                return null;
            }
            object.owned = true;
            owned_references += 1;
            return @ptrCast(object);
        }

        fn cast(object: ?*c.PyObject) *Object {
            return @ptrCast(@alignCast(object.?));
        }

        /// A call that may fail, reporting it as -1 with an error set.
        fn status() c_int {
            if (verifier.any(bool)) return 0;
            error_set = true;
            return -1;
        }

        fn typeOf(object: ?*c.PyObject) callconv(.c) ?*c.PyTypeObject {
            return object.?.ob_type;
        }

        fn dealloc(object: ?*c.PyObject) callconv(.c) void {
            // An instance from `PyType_GenericAlloc` is the code's own to release.
            if (@intFromPtr(object.?) == @intFromPtr(&instance)) return;
            const released = cast(object);
            // Reaching zero on a borrowed object means the code released a reference it never had.
            verifier.assert(released.owned);
            released.owned = false;
            owned_references -= 1;
        }

        fn getConstantBorrowed(id: c_uint) callconv(.c) ?*c.PyObject {
            verifier.assert(id <= c.Py_CONSTANT_TRUE);
            const kind: Kind = switch (id) {
                c.Py_CONSTANT_NONE => .none,
                c.Py_CONSTANT_FALSE => .false,
                else => .true,
            };
            return @ptrCast(&pool[@intFromEnum(kind)]);
        }

        fn importModule(name: ?[*:0]const u8) callconv(.c) ?*c.PyObject {
            _ = name;
            return newReference();
        }

        fn getAttrString(object: ?*c.PyObject, name: ?[*:0]const u8) callconv(.c) ?*c.PyObject {
            _ = object;
            _ = name;
            return newReference();
        }

        fn bytesFromStringAndSize(bytes: ?[*]const u8, size: c.Py_ssize_t) callconv(.c) ?*c.PyObject {
            return copyOf(bytes, size);
        }

        fn unicodeDecodeFsDefaultAndSize(bytes: ?[*]const u8, size: c.Py_ssize_t) callconv(.c) ?*c.PyObject {
            return copyOf(bytes, size);
        }

        /// CPython copies `size` bytes out of the caller's buffer, so a wrong size is a read out of bounds.
        fn copyOf(bytes: ?[*]const u8, size: c.Py_ssize_t) ?*c.PyObject {
            verifier.assert(size >= 0);
            // Touching both ends checks the whole range without a loop over it.
            if (size != 0) _ = bytes.?[0] +% bytes.?[@intCast(size - 1)];
            return newReference();
        }

        fn buildValue(format: ?[*:0]const u8, ...) callconv(.c) ?*c.PyObject {
            _ = format;
            return newReference();
        }

        fn errOccurred() callconv(.c) ?*c.PyObject {
            return if (error_set) @ptrCast(&types[@intFromEnum(Kind.other)]) else null;
        }

        fn errSetString(exception: ?*c.PyObject, message: ?[*:0]const u8) callconv(.c) void {
            _ = exception;
            _ = message;
            error_set = true;
        }

        fn errSetObject(exception: ?*c.PyObject, value: ?*c.PyObject) callconv(.c) void {
            _ = exception;
            _ = value;
            error_set = true;
        }

        fn tupleSize(object: ?*c.PyObject) callconv(.c) c.Py_ssize_t {
            const tuple = cast(object);
            if (tuple.kind != .tuple) {
                error_set = true;
                return -1;
            }
            return @intCast(tuple.len);
        }

        fn tupleGetItem(object: ?*c.PyObject, index: c.Py_ssize_t) callconv(.c) ?*c.PyObject {
            const tuple = cast(object);
            if (tuple.kind != .tuple or index < 0 or index >= tuple.len) {
                error_set = true;
                return null;
            }
            return @ptrCast(tuple.items[@intCast(index)]);
        }

        fn unicodeAsUtf8AndSize(object: ?*c.PyObject, size: ?*c.Py_ssize_t) callconv(.c) ?[*:0]const u8 {
            const text = cast(object);
            // Encoding can fail even for text, for a lone surrogate or for lack of memory.
            if (text.kind != .text or verifier.any(bool)) {
                error_set = true;
                return null;
            }
            if (size) |out| out.* = @intCast(text.len);
            return @ptrCast(&text.text);
        }

        fn bytesAsString(object: ?*c.PyObject) callconv(.c) ?[*:0]u8 {
            const bytes = cast(object);
            if (bytes.kind != .bytes) {
                error_set = true;
                return null;
            }
            return @ptrCast(&bytes.text);
        }

        fn bytesSize(object: ?*c.PyObject) callconv(.c) c.Py_ssize_t {
            const bytes = cast(object);
            if (bytes.kind != .bytes) {
                error_set = true;
                return -1;
            }
            return @intCast(bytes.len);
        }

        fn numberAsSsize(object: ?*c.PyObject, exception: ?*c.PyObject) callconv(.c) c.Py_ssize_t {
            _ = exception;
            const number = cast(object);
            // `__index__` is arbitrary code: any object may answer, and any answer may raise.
            if (number.kind == .text or number.kind == .bytes or number.kind == .tuple or verifier.any(bool)) {
                error_set = true;
                return -1;
            }
            return number.int;
        }

        fn bufferRelease(view: ?*c.Py_buffer) callconv(.c) void {
            if (view.?.obj == null) return;
            view.?.obj = null;
            buffer_releases += 1;
        }

        /// Any call into Python. It runs arbitrary code, but the model does not have that code
        /// call back into the code under test.
        fn call() ?*c.PyObject {
            return newReference();
        }

        fn callNoArgs(callable: ?*c.PyObject) callconv(.c) ?*c.PyObject {
            _ = callable;
            return call();
        }

        fn callOneArg(callable: ?*c.PyObject, argument: ?*c.PyObject) callconv(.c) ?*c.PyObject {
            _ = callable;
            _ = argument;
            return call();
        }

        fn vectorcall(
            callable: ?*c.PyObject,
            arguments: ?[*]const ?*c.PyObject,
            count: usize,
            names: ?*c.PyObject,
        ) callconv(.c) ?*c.PyObject {
            _ = callable;
            _ = arguments;
            _ = count;
            _ = names;
            return call();
        }

        fn vectorcallMethod(
            name: ?*c.PyObject,
            arguments: ?[*]const ?*c.PyObject,
            count: usize,
            names: ?*c.PyObject,
        ) callconv(.c) ?*c.PyObject {
            _ = name;
            _ = arguments;
            _ = count;
            _ = names;
            return call();
        }

        fn contextNew() callconv(.c) ?*c.PyObject {
            return newReference();
        }

        fn contextEnter(context: ?*c.PyObject) callconv(.c) c_int {
            _ = context;
            return status();
        }

        fn dictNew() callconv(.c) ?*c.PyObject {
            return newReference();
        }

        fn dictSetItem(dict: ?*c.PyObject, key: ?*c.PyObject, value: ?*c.PyObject) callconv(.c) c_int {
            _ = dict;
            _ = key;
            _ = value;
            return status();
        }

        fn floatFromDouble(value: f64) callconv(.c) ?*c.PyObject {
            _ = value;
            return newReference();
        }

        fn objectSize(object: ?*c.PyObject) callconv(.c) c.Py_ssize_t {
            _ = object;
            if (status() != 0) return -1;
            const size = verifier.any(c.Py_ssize_t);
            verifier.assume(size >= 0);
            return size;
        }

        fn objectGetItemData(object: ?*c.PyObject) callconv(.c) ?*anyopaque {
            _ = object;
            return &instance;
        }

        fn typeGenericAlloc(object_type: ?*c.PyTypeObject, count: c.Py_ssize_t) callconv(.c) ?*c.PyObject {
            _ = count;
            if (verifier.any(bool)) {
                error_set = true;
                return null;
            }
            instance = @splat(0);
            const object: *c.PyObject = @ptrCast(&instance);
            const reference_count: *usize = @ptrCast(object);
            reference_count.* = 1;
            object.ob_type = object_type;
            return object;
        }

        fn errClear() callconv(.c) void {
            error_set = false;
        }

        fn errExceptionMatches(exception: ?*c.PyObject) callconv(.c) c_int {
            _ = exception;
            return @intFromBool(verifier.any(bool));
        }

        fn errGetRaisedException() callconv(.c) ?*c.PyObject {
            if (!error_set) return null;
            error_set = false;
            const exception = create(.other, true);
            return @ptrCast(exception);
        }

        /// Steals the reference to `exception`.
        fn errSetRaisedException(exception: ?*c.PyObject) callconv(.c) void {
            error_set = true;
            const stolen = cast(exception);
            verifier.assert(stolen.owned);
            stolen.owned = false;
            owned_references -= 1;
        }

        fn errNoMemory() callconv(.c) ?*c.PyObject {
            error_set = true;
            return null;
        }

        fn errWriteUnraisable(object: ?*c.PyObject) callconv(.c) void {
            _ = object;
            error_set = false;
        }

        fn evalSaveThread() callconv(.c) ?*c.PyThreadState {
            return @ptrCast(&thread_state);
        }

        fn evalRestoreThread(state: ?*c.PyThreadState) callconv(.c) void {
            _ = state;
        }

        fn threadGetIdent() callconv(.c) c_ulong {
            return verifier.any(c_ulong);
        }

        fn threadReleaseLock(lock: ?*anyopaque) callconv(.c) void {
            _ = lock;
        }

        comptime {
            @export(&bufferRelease, .{ .name = "PyBuffer_Release" });
            @export(&callNoArgs, .{ .name = "PyObject_CallNoArgs" });
            @export(&callOneArg, .{ .name = "PyObject_CallOneArg" });
            @export(&vectorcall, .{ .name = "PyObject_Vectorcall" });
            @export(&vectorcallMethod, .{ .name = "PyObject_VectorcallMethod" });
            @export(&contextNew, .{ .name = "PyContext_New" });
            @export(&contextNew, .{ .name = "PyContext_CopyCurrent" });
            @export(&contextEnter, .{ .name = "PyContext_Enter" });
            @export(&contextEnter, .{ .name = "PyContext_Exit" });
            @export(&dictNew, .{ .name = "PyDict_New" });
            @export(&dictSetItem, .{ .name = "PyDict_SetItem" });
            @export(&floatFromDouble, .{ .name = "PyFloat_FromDouble" });
            @export(&objectSize, .{ .name = "PyObject_Size" });
            @export(&objectGetItemData, .{ .name = "PyObject_GetItemData" });
            @export(&typeGenericAlloc, .{ .name = "PyType_GenericAlloc" });
            @export(&errClear, .{ .name = "PyErr_Clear" });
            @export(&errExceptionMatches, .{ .name = "PyErr_ExceptionMatches" });
            @export(&errGetRaisedException, .{ .name = "PyErr_GetRaisedException" });
            @export(&errSetRaisedException, .{ .name = "PyErr_SetRaisedException" });
            @export(&errNoMemory, .{ .name = "PyErr_NoMemory" });
            @export(&errWriteUnraisable, .{ .name = "PyErr_WriteUnraisable" });
            @export(&evalSaveThread, .{ .name = "PyEval_SaveThread" });
            @export(&evalSaveThread, .{ .name = "PyThreadState_Get" });
            @export(&evalRestoreThread, .{ .name = "PyEval_RestoreThread" });
            @export(&threadGetIdent, .{ .name = "PyThread_get_thread_ident" });
            @export(&threadReleaseLock, .{ .name = "PyThread_release_lock" });
            @export(&bytesFromStringAndSize, .{ .name = "PyUnicode_FromStringAndSize" });
            @export(&typeOf, .{ .name = "Py_TYPE" });
            @export(&dealloc, .{ .name = "_Py_Dealloc" });
            @export(&getConstantBorrowed, .{ .name = "Py_GetConstantBorrowed" });
            @export(&importModule, .{ .name = "PyImport_ImportModule" });
            @export(&getAttrString, .{ .name = "PyObject_GetAttrString" });
            @export(&buildValue, .{ .name = "Py_BuildValue" });
            @export(&bytesFromStringAndSize, .{ .name = "PyBytes_FromStringAndSize" });
            @export(&unicodeDecodeFsDefaultAndSize, .{ .name = "PyUnicode_DecodeFSDefaultAndSize" });
            @export(&errOccurred, .{ .name = "PyErr_Occurred" });
            @export(&errSetString, .{ .name = "PyErr_SetString" });
            @export(&errSetObject, .{ .name = "PyErr_SetObject" });
            @export(&tupleSize, .{ .name = "PyTuple_Size" });
            @export(&tupleGetItem, .{ .name = "PyTuple_GetItem" });
            @export(&unicodeAsUtf8AndSize, .{ .name = "PyUnicode_AsUTF8AndSize" });
            @export(&bytesAsString, .{ .name = "PyBytes_AsString" });
            @export(&bytesSize, .{ .name = "PyBytes_Size" });
            @export(&numberAsSsize, .{ .name = "PyNumber_AsSsize_t" });
        }
    };
}
