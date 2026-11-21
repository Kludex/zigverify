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
        var pool: [48]Object = undefined;
        var used: usize = 0;
        var error_set = false;
        var owned_references: usize = 0;
        var buffer_releases: usize = 0;
        var calls_made: usize = 0;
        var spec: ?*c.PyType_Spec = null;
        /// The type of every bytes object, exported as CPython's own `PyBytes_Type` so that
        /// `PyBytes_CheckExact` holds for them.
        var bytes_type: c.PyTypeObject = undefined;
        var created_type: c.PyTypeObject = undefined;

        /// Whether calls that can fail may do so. Turning it off follows one path, the one
        /// where the interpreter is healthy, and is what makes a long scenario affordable.
        pub var failures = true;
        /// Fails exactly one call: the one with this index among the calls that can fail,
        /// counted from `reset`. Every other call succeeds, whatever `failures` says. One proof
        /// per index walks every single-failure path, each as cheap as the path where nothing
        /// fails, where letting all of them fail at once is not affordable.
        pub var fail_at: ?usize = null;
        var fallible_calls: usize = 0;
        /// Runs inside every modelled call into Python, standing in for the Python code that
        /// call would run. This is how a harness has a protocol callback reenter the code.
        pub var on_call: ?*const fn () void = null;
        /// What every modelled call into Python returns, as a new reference. Null means a fresh
        /// opaque object.
        pub var call_result: ?*c.PyObject = null;
        /// What `isinstance` answers when `failures` is off.
        pub var is_instance = false;
        /// What every attribute lookup returns: an immortal object laid out as a type, whose
        /// fields the harness may set to what the code under test expects of the attribute.
        pub var attribute: c.PyTypeObject = undefined;
        /// What `PyType_GenericAlloc` hands out: zeroed memory for instances of extension types.
        var instances: [4][2048]u8 align(16) = undefined;
        var instances_used: usize = 0;
        /// The current thread's state, with no context entered. Code that reads its fields
        /// directly, as some does for speed, finds them all zero. The struct does not survive
        /// translation from C, so this is a block larger than any version of it.
        var thread_state: [4096]u8 align(16) = undefined;

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
            bytes_type = std.mem.zeroes(c.PyTypeObject);
            bytes_type.tp_flags = c.Py_TPFLAGS_BYTES_SUBCLASS;
            inline for (.{ &attribute, &created_type }) |immortal| {
                immortal.* = std.mem.zeroes(c.PyTypeObject);
                const count: *usize = @ptrCast(immortal);
                count.* = 0xC0000000;
            }
            thread_state = @splat(0);
            spec = null;
            failures = true;
            fail_at = null;
            fallible_calls = 0;
            on_call = null;
            used = 0;
            error_set = false;
            owned_references = 0;
            buffer_releases = 0;
            calls_made = 0;
            instances_used = 0;
            call_result = null;
            is_instance = false;
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

        /// A bytes object of exactly `len` arbitrary bytes.
        pub fn anyBytes(comptime len: usize) *c.PyObject {
            const object = create(.bytes, false);
            object.len = len;
            object.text = verifier.any([max_text + 1]u8);
            object.text[len] = 0;
            return @ptrCast(object);
        }

        /// The C function behind the method `name` of the type the code under test registered.
        pub fn method(comptime name: []const u8) c.PyCFunction {
            var slot = spec.?.slots;
            while (slot[0].slot != c.Py_tp_methods) slot += 1;
            var definition: [*]c.PyMethodDef = @ptrCast(@alignCast(slot[0].pfunc.?));
            while (!std.mem.eql(u8, std.mem.span(definition[0].ml_name.?), name)) definition += 1;
            return definition[0].ml_meth;
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

        /// How many calls that can fail the code has made since `reset`.
        pub fn fallibleCalls() usize {
            return fallible_calls;
        }

        /// How many times the code has called into Python: callbacks, methods, any callable.
        pub fn calls() usize {
            return calls_made;
        }

        /// An integer object holding `value`.
        pub fn intOf(value: isize) *c.PyObject {
            const object = create(.int, false);
            object.int = value;
            return @ptrCast(object);
        }

        /// A tuple of exactly these items.
        pub fn tupleOf(items: []const *c.PyObject) *c.PyObject {
            const tuple = create(.tuple, false);
            tuple.len = items.len;
            for (items, 0..) |item, index| tuple.items[index] = @ptrCast(@alignCast(item));
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
            object.head.ob_type = if (kind == .bytes) &bytes_type else &types[@intFromEnum(kind)];
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
            if (fails()) {
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

        /// Whether the call being modelled, one that can fail, does.
        fn fails() bool {
            defer fallible_calls += 1;
            if (fail_at) |index| return fallible_calls == index;
            return failures and verifier.any(bool);
        }

        /// A call that may fail, reporting it as -1 with an error set.
        fn status() c_int {
            if (!fails()) return 0;
            error_set = true;
            return -1;
        }

        fn typeOf(object: ?*c.PyObject) callconv(.c) ?*c.PyTypeObject {
            return object.?.ob_type;
        }

        fn dealloc(object: ?*c.PyObject) callconv(.c) void {
            // An instance from `PyType_GenericAlloc` is the code's own to release.
            const address = @intFromPtr(object.?);
            if (address >= @intFromPtr(&instances) and address < @intFromPtr(&instances) + @sizeOf(@TypeOf(instances))) return;
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
            if (status() != 0) return null;
            return @ptrCast(&attribute);
        }

        fn getAttr(object: ?*c.PyObject, name: ?*c.PyObject) callconv(.c) ?*c.PyObject {
            _ = object;
            _ = name;
            if (status() != 0) return null;
            return @ptrCast(&attribute);
        }

        fn isInstance(object: ?*c.PyObject, class: ?*c.PyObject) callconv(.c) c_int {
            _ = object;
            _ = class;
            if (!failures) return @intFromBool(is_instance);
            const answer = verifier.any(c_int);
            verifier.assume(answer >= -1 and answer <= 1);
            if (answer < 0) error_set = true;
            return answer;
        }

        fn longAsLong(object: ?*c.PyObject) callconv(.c) c_long {
            const number = cast(object);
            if (number.kind != .int or status() != 0) {
                error_set = true;
                return -1;
            }
            return number.int;
        }

        fn longFromLongLong(value: c_longlong) callconv(.c) ?*c.PyObject {
            const object = newReference() orelse return null;
            cast(object).kind = .int;
            cast(object).int = @intCast(value);
            return object;
        }

        fn internFromString(text: ?[*:0]const u8) callconv(.c) ?*c.PyObject {
            _ = text;
            return newReference();
        }

        fn tuplePack(count: c.Py_ssize_t, ...) callconv(.c) ?*c.PyObject {
            _ = count;
            return newReference();
        }

        fn typeFromModuleAndSpec(
            module: ?*c.PyObject,
            type_spec: ?*c.PyType_Spec,
            bases: ?*c.PyObject,
        ) callconv(.c) ?*c.PyObject {
            _ = module;
            _ = bases;
            if (status() != 0) return null;
            spec = type_spec;
            created_type.tp_basicsize = type_spec.?.basicsize;
            return @ptrCast(&created_type);
        }

        fn moduleAddObjectRef(module: ?*c.PyObject, name: ?[*:0]const u8, value: ?*c.PyObject) callconv(.c) c_int {
            _ = module;
            _ = name;
            _ = value;
            return status();
        }

        fn moduleAddIntConstant(module: ?*c.PyObject, name: ?[*:0]const u8, value: c_long) callconv(.c) c_int {
            _ = module;
            _ = name;
            _ = value;
            return status();
        }

        /// A view of a bytes or text object's contents. The view pins its owner until released.
        fn getBuffer(object: ?*c.PyObject, view: ?*c.Py_buffer, flags: c_int) callconv(.c) c_int {
            _ = flags;
            const exporter = cast(object);
            if ((exporter.kind != .bytes and exporter.kind != .text) or status() != 0) {
                error_set = true;
                view.?.obj = null;
                return -1;
            }
            view.?.* = std.mem.zeroes(c.Py_buffer);
            view.?.buf = &exporter.text;
            view.?.len = @intCast(exporter.len);
            view.?.obj = object;
            return 0;
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
            calls_made += 1;
            if (on_call) |callback| callback();
            if (call_result) |result| {
                // Taken from the pool all the same, to keep later pool positions fixed.
                _ = create(.other, false);
                return again(cast(result));
            }
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

        /// With `failures` off, every object is falsy: a callback that returns nothing.
        fn objectIsTrue(object: ?*c.PyObject) callconv(.c) c_int {
            _ = object;
            if (!failures) return 0;
            const truth = verifier.any(c_int);
            verifier.assume(truth >= -1 and truth <= 1);
            if (truth < 0) error_set = true;
            return truth;
        }

        /// A new reference to an object the code already had: the count goes up, so the
        /// release that follows does not look like releasing a borrowed reference.
        fn again(object: *Object) ?*c.PyObject {
            const count: *usize = @ptrCast(&object.head);
            count.* += 1;
            return @ptrCast(object);
        }

        fn sequenceFast(object: ?*c.PyObject, message: ?[*:0]const u8) callconv(.c) ?*c.PyObject {
            _ = message;
            const sequence = cast(object);
            if (sequence.kind != .tuple or status() != 0) {
                error_set = true;
                return null;
            }
            return again(sequence);
        }

        fn sequenceGetItem(object: ?*c.PyObject, index: c.Py_ssize_t) callconv(.c) ?*c.PyObject {
            const sequence = cast(object);
            if (sequence.kind != .tuple or index < 0 or index >= sequence.len) {
                error_set = true;
                return null;
            }
            return again(sequence.items[@intCast(index)].?);
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
            return object;
        }

        fn typeGenericAlloc(object_type: ?*c.PyTypeObject, count: c.Py_ssize_t) callconv(.c) ?*c.PyObject {
            _ = count;
            verifier.assert(instances_used < instances.len);
            const instance = &instances[instances_used];
            instances_used += 1;
            if (fails()) {
                error_set = true;
                return null;
            }
            instance.* = @splat(0);
            const object: *c.PyObject = @ptrCast(instance);
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
            @export(&longFromLongLong, .{ .name = "PyLong_FromLongLong" });
            @export(&getAttr, .{ .name = "PyObject_GetAttr" });
            @export(&isInstance, .{ .name = "PyObject_IsInstance" });
            @export(&longAsLong, .{ .name = "PyLong_AsLong" });
            @export(&objectIsTrue, .{ .name = "PyObject_IsTrue" });
            @export(&sequenceFast, .{ .name = "PySequence_Fast" });
            @export(&sequenceGetItem, .{ .name = "PySequence_GetItem" });
            @export(&tupleSize, .{ .name = "PySequence_Size" });
            @export(&bytes_type, .{ .name = "PyBytes_Type" });
            @export(&internFromString, .{ .name = "PyUnicode_InternFromString" });
            @export(&tuplePack, .{ .name = "PyTuple_Pack" });
            @export(&typeFromModuleAndSpec, .{ .name = "PyType_FromModuleAndSpec" });
            @export(&moduleAddObjectRef, .{ .name = "PyModule_AddObjectRef" });
            @export(&moduleAddIntConstant, .{ .name = "PyModule_AddIntConstant" });
            @export(&getBuffer, .{ .name = "PyObject_GetBuffer" });
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
