# zigverify

Prove properties of Zig code for every input, instead of testing a few.

```zig
const verifier = @import("verifier");

pub const panic = verifier.panic;

fn midpointNaive(low: u32, high: u32) u32 {
    return (low + high) / 2;
}

export fn naive_midpoint_never_panics() void {
    _ = midpointNaive(verifier.any(u32), verifier.any(u32));
}
```

```
$ zig build verify
refuted: naive_midpoint_never_panics
  integer overflow
  in midpoint_midpointNaive (examples/midpoint.zig:9:17)
  called from naive_midpoint_never_panics (examples/midpoint.zig:18:22)
  inputs, in the order the harness asked for them:
    1: 4 bytes  00 00 00 80  = 2147483648
    2: 4 bytes  01 00 00 80  = 2147483649
```

A harness is an `export fn`. It builds arbitrary inputs, calls your code, and states what
must hold. zigverify compiles it to C with Zig's own C backend and hands it to
[CBMC](https://www.cprover.org/cbmc/), a bounded model checker, which either proves that no
input fails or returns one that does.

## What is checked

| Check | How you ask for it |
| --- | --- |
| No safety check fires: bounds, overflow, bad casts, `unreachable`, null unwraps | `pub const panic = verifier.panic;` in the harness file |
| A property of the result | `verifier.assert(condition)` |
| No read or write lands outside an object, even through a pointer cast | always on |
| No leak, double free, or unhandled allocation failure | `verifier.FailingAllocator` |

Zig's safety checks become proof obligations for free, because the harness is built in
`ReleaseSafe` and every check that would panic is reported to the checker instead.

Zig has no safety check for memory reached through `@ptrCast`. The checker's own bounds
checks on the generated C cover that gap:

```
refuted: short_buffer_is_never_read_past
  dereference failure: pointer outside object bounds in *t18
  in sockaddr_same (examples/sockaddr.zig:39:46)
  called from short_buffer_is_never_read_past (examples/sockaddr.zig:82:13)
  inputs, in the order the harness asked for them:
    1: 16 bytes  0a 00 40 40 02 10 80 10 80 04 80 20 20 04 02 04
```

The first two bytes are the address family, 10, which is IPv6. The code trusted it and read
an IPv6 address out of a 16-byte buffer.

## Harness API

| Function | Meaning |
| --- | --- |
| `verifier.any(T)` | Every value of `T`. Integers, floats, bools, enums, optionals, arrays, structs. |
| `verifier.prefix(T, buffer)` | Every slice from empty up to `buffer.len` arbitrary items. |
| `verifier.fill(bytes)` | Overwrite a buffer with arbitrary bytes. |
| `verifier.assume(condition)` | Discard the inputs where `condition` is false. |
| `verifier.assert(condition)` | Fail the proof if any remaining input makes `condition` false. |

| `verifier.FailingAllocator(capacity, max_live)` | An allocator whose every allocation may fail, and that knows what is live. |

`any` rejects pointers and slices at compile time. An arbitrary address proves nothing, so
point into a buffer the harness owns and use `prefix`.

## Out-of-memory paths

```zig
fn dupePair(gpa: std.mem.Allocator, first: []const u8, second: []const u8) !Pair {
    const first_copy = try gpa.dupe(u8, first);
    return .{ .first = first_copy, .second = try gpa.dupe(u8, second) };
}

export fn dupe_pair_never_leaks() void {
    var failing: verifier.FailingAllocator(32, 2) = .{};
    const gpa = failing.allocator();
    if (dupePair(gpa, "ab", "cd")) |pair| {
        gpa.free(pair.first);
        gpa.free(pair.second);
    } else |_| {}
    failing.assertNoLeaks();
}
```

```
refuted: dupe_pair_never_leaks
  an allocation is still live at the end: a leak
  in dupe_pair_never_leaks
```

Each allocation fails or succeeds independently, so one proof covers every combination of
failures. This is the case tests reach least: the second allocation failing after the first
succeeded. A free of memory that is not live fails the proof too, which catches double frees.

## Calls into C

```zig
extern fn inet_pton(family: c_int, text: [*:0]const u8, out: *anyopaque) c_int;

export fn inet_pton(family: c_int, text: [*:0]const u8, out: *anyopaque) c_int {
    _ = text;
    if (family != 2 or verifier.any(bool)) return 0;
    const address: *[4]u8 = @ptrCast(out);
    address.* = verifier.any([4]u8);
    return 1;
}
```

The first line is in the code under test, the function below it in the harness file. The
checker cannot read a C library, so the harness exports a model under the C name: a Zig
function that says what the call may do. This one either fails and leaves `out` alone, or
succeeds and fills four arbitrary bytes, so the proof covers every text at once.

A model is where you state what you trust about the library. Keep it as loose as the
library's documentation: a model that never fails proves nothing about your error paths.

### Ready-made models

| File | Covers |
| --- | --- |
| `models/cpython.zig` | Taking arguments apart and reporting errors: tuples, text, bytes, integers, the constants, `PyErr_*`, and the calls that return a new reference. |
| `models/libuv.zig` | Converting between text and socket addresses, and error strings. |
| `models/libuv_stream.zig` | Stream writes and the handle lifecycle: `uv_try_write`, `uv_write`, `uv_shutdown`, `uv_close`. |

The CPython model also keeps the books on references. Releasing a reference the code only
borrowed fails the proof, and `assertNoLeakedReferences` fails it when a reference the code
was given is never released. It is instantiated with the code's own translation of
`Python.h`, so both sides agree on every type:

```zig
const cpython = @import("cpython").Model(zuvloop.py.c, 16);
```

`models/libuv_stream.zig` is instantiated the same way, with the code's own declarations of
libuv, and takes each parameter type from them. Its callbacks run when the harness calls
`completeWrite`, `deliverRead` or `deliverClose`: the harness plays the loop, and decides
the order.

A call into Python runs no code by default. Set `cpython.on_call` to a function and every
modelled call runs it first, which is how a harness has a protocol callback reenter the
code under test. `cpython.method("write")` returns the C function behind a method of the
type the code registered, so the harness calls it the way the interpreter would.

Both models have a `failures` switch. Turned off, every call that can fail succeeds, the
checker follows one path, and a scenario of many calls finishes in seconds.

Letting every call fail at once is rarely affordable: a scenario that takes 30 seconds on
one path ran out of memory after 20 minutes that way. Set `cpython.fail_at` to an index
instead and exactly that call fails, counted among the calls that can. One proof per index
covers every single-failure path, each about as cheap as the path where nothing fails:

```zig
fn eofWhenCallFails(comptime failing: usize) void {
    const transport = openTransport();
    cpython.fail_at = cpython.fallibleCalls() + failing;
    stream.deliverRead(stream.eof);
    verifier.assert(stream.handleCloses() <= 1);
}
```

Set `cpython.second_failure` as well and at most one later call may fail too, whichever
it is. The same number of proofs then covers every pair of failures, at about the same
cost, because the second failure is left open only on the short path after the first.

The `integration` directory uses the models on a real extension, zuvloop. Run it with
`zig build verify-zuvloop -Dzuvloop=<checkout> -Dpython-include=<dir>`.

| Proof | Time |
| --- | --- |
| A kernel address becomes a Python address without panicking or reading out of bounds | 112s |
| A Unix path or name, as text or bytes, becomes a socket address safely | 18s |
| A `(host, port[, flowinfo, scope_id])` tuple of any contents becomes a socket address safely | 7.5 min |
| An object that is not a tuple is rejected with a Python error | 21s |
| Flushing writes releases every buffer when the socket takes everything | 11s |
| ... when the socket fails | 11s |
| ... when the transport is closing | 11s |
| ... when the write is queued, and Python calls succeed | 3.7 min |
| Five writes in one iteration are all kept | 11s |
| A completed write releases the buffers pinned for it | 16s |
| `close()` sends what is outstanding, then closes the handle exactly once | 35s |
| A failed write closes exactly once and releases every buffer | 35s |
| `abort()` drops what is pending and closes exactly once | 35s |
| `write_eof()` half-closes only after the data, once, and later writes are refused | 30s |
| `writelines()` batches every buffer | 14s |
| `set_write_buffer_limits()` defaults to 64 KiB and 16 KiB | 15s |
| A read reaches the protocol in one call, and EOF closes exactly once | 37s |
| `pause_reading()` stops reads and `resume_reading()` restarts them | 22s |
| A buffered protocol's buffer is filled, reported and released once | 19s |
| Creating a TCP transport opens it and queues `connection_made` and the start of reading | 7.6 min |
| Five sixteen-byte writes are all kept | 25s |
| A thousand-byte read reaches the protocol in one call | 29s |
| A refused write request closes exactly once and releases every buffer | 27s |
| `write()` with any one call failing: it batches or raises, and pins nothing if it raises | 4 x 25s |
| EOF with any one call failing: reading stops and the handle closes at most once | 4 x 30s |
| `abort()` with any one call failing: still closes exactly once and releases every buffer | 4 x 30s |
| `write_eof()` with any one call failing: every buffer is released, at most one close | 4 x 34s |
| `writelines()` with any one call failing: it batches both or releases every view it took | 4 x 25s |
| A buffered read with any one call failing: every view is released, at most one close | 4 x 40s |
| Each of the seven scenarios above with any two calls failing | 28 x 30-70s |
| `close()` with any one call failing: still drains, closes exactly once, releases every buffer | 4 x 60s |
| ... and still kept when `pause_writing` calls `close()` | refuted in 15s |

The last one is a real bug. The fifth `write()` flushes a full batch, the flush pauses the
protocol, and if the protocol closes the transport from `pause_writing`, the byte of that
fifth write is released without being sent, although `write()` reported success.

Pass `-j1` to run them one at a time, which takes about two hours: run together they
need more memory than most machines have.

Each flush proof fixes what the socket answers. One proof over every answer at once does
not fit in memory, and neither does one over every Python object: split a proof by case
when the cases take different paths through the code.

The proofs are bounded by the models: text and bytes of up to 16 bytes, tuples of up to
four items, writes of up to sixteen bytes, and reads of up to a thousand. The scenario
proofs cover the path where nothing fails and, for `write()`, `writelines()`, `write_eof()`,
`close()`, `abort()`, EOF and buffered reads, each path where one call fails and each
where two do. The proof with the highest index asserts that it failed nothing, which is
what shows the indices below it reached every call. Creating a transport is proved only
when it succeeds: the proof of it failing gave no verdict in 40 minutes.

An `assert()` in a translated C header is checked too. A failing one is reported as
`assert() failed in C code`, with its line.

> [!WARNING]
> **A call with no model makes the proof inconclusive.** The checker would treat the return
> value as arbitrary but the memory behind pointer arguments as untouched, and report
> success for code that reads a buffer the library was supposed to fill.

## Harnesses in C

```c
#include <stdint.h>
#include "verifier.h"

void terminator_stays_in_bounds(void) {
    char buffer[8];
    size_t length;
    verifier_any(&length, sizeof length);
    verifier_assume(length <= sizeof buffer);
    buffer[length] = 0;
}
```

```
refuted: terminator_stays_in_bounds
  array 'buffer' upper bound in buffer[(signed long int)length]
```

The checker and the reports do not depend on Zig. A harness written in C includes
`verifier.h` and is added with `prover.addC`. Any language that can produce C and call
`verifier_any`, `verifier_assume` and `verifier_check` can be checked the same way.

## Add it to a build

```zig
const zigverify = @import("zigverify");

pub fn build(b: *std.Build) void {
    const prover: zigverify.Prover = .init(b, b.dependency("zigverify", .{}).builder, null);
    const verify_step = b.step("verify", "Run the proofs");
    prover.add(verify_step, .{
        .root_source_file = b.path("src/proofs.zig"),
        .proofs = &.{
            .{ .function = "midpoint_never_panics" },
            .{ .function = "parse_never_panics", .unwind = 130 },
        },
    });
}
```

The third argument of `init` is a Docker image to run `cbmc` from. Pass `null` to use the
`cbmc` on `PATH`. The `Dockerfile` in this repository builds a suitable image:

```
docker build -t zigverify-cbmc .
zig build verify -Dcbmc-docker-image=zigverify-cbmc
```

## Unwind bounds

The checker unrolls every loop a fixed number of times. `unwind` sets that number for the
whole proof, and it must exceed the longest loop: an input of up to 64 bytes needs 65.

A function can have its own bound, which applies to its loops and to its recursion:

```zig
.{
    .function = "decoder_never_panics",
    .unwind = 65,
    .bounds = &.{.{ .function = "chunked_Decoder_next", .unwind = 4 }},
},
```

Use this when a short recursion sits next to a long loop. A state machine that calls
itself to change state is two or three calls deep, but under one global bound the checker
unrolls it as deep as the input is long. On a real chunked-transfer decoder this took a
proof from 182 seconds to 9.

The function is named as reports print it: the file name, then the path to the
declaration, joined by underscores. A name that matches nothing is an error.

## Verdicts

| Verdict | Meaning |
| --- | --- |
| `proved` | No input reaches a failing check, with every loop run to completion. |
| `refuted` | An input fails. The report names the check, the source line of each frame, and the input bytes. |
| `inconclusive` | A loop needs more iterations than the proof's `unwind` bound. Raise it. |

A proof is never silently partial. If a loop can run more times than `unwind` allows, the
verdict is `inconclusive`, not `proved`.

A frame in the harness file is printed as `file:line:column`. A frame in another file is
printed as a line and column counted from that function's `fn`, because the generated C
records positions per function and not per file.

Mark a proof `.expect = .refuted` when it is a seeded bug. That step passes only if the
checker finds the counterexample, which shows the harness can fail at all.

## What makes a proof slow

The checker turns the program into one formula. Its size depends on a few constructs far
more than on line count. Measured on real HTTP/1 parsers, by input size:

| Proof | 16 bytes | 32 bytes | 64 bytes |
| --- | --- | --- | --- |
| Line splitting: find LF, check CR | 0.8s | 0.9s | 1.3s |
| Status line: byte loops and a fixed-size compare | 1.3s | 2.3s | 9.5s |
| Request line: one hand-written `@Vector` scan | 1.9s | 4.7s | out of memory |
| Header line: a `@Vector` scan over the value | 8.1s | 45s | out of memory |

| Construct | Cost | What to do |
| --- | --- | --- |
| A loop that reads one byte per iteration | Cheap | Nothing. |
| `std.mem.eql` and friends on slices of unknown length | Cheap, because of `-ffuzz` | Nothing. Without the flag it does not finish. |
| A multi-byte or `@Vector` load at an offset that depends on the input | Grows fast, then runs out of memory | Gate the fast path on `!builtin.fuzz`, as std does, so the harness takes the byte loop. |
| A state machine that calls itself, next to a long input loop | Minutes | Give the function its own bound. See [Unwind bounds](#unwind-bounds). |
| A loop whose body makes a recursive call | Exponential | Shrink the input. |

The third row is the one to remember. A wide load at an input-dependent offset makes the
checker consider every offset for every lane. Compiling for a CPU without vector registers
does not help: code that falls back to narrower blocks does more loads, and gets slower.

## Limits

> [!WARNING]
> **The proof is about the C that Zig generates.** The harness is compiled with Zig's C
> backend, not the LLVM backend that builds your release binary. A miscompilation in either
> backend is outside the proof.

> [!WARNING]
> **`std.mem` is verified in its byte-by-byte form.** Harnesses are compiled with `-ffuzz`,
> which makes `std.mem.eql` compare one byte at a time. Without the flag, comparing two
> slices of unknown length produces a problem the solver does not finish. The chunked
> comparison that release builds use is proved separately, in `examples/std_mem.zig`, to
> agree with a byte loop at every length up to 64, for the CPU the proof runs on. Other
> std fast paths are still trusted.

> [!WARNING]
> **Ordered pointer comparisons are rewritten.** Zig compares pointers by address. C leaves
> `<` between pointers into different objects undefined, and the checker lets it come out
> either way, which would make every `@memcpy` between two buffers look like an overlap. The
> generated C is rewritten to compare the addresses as integers before it is checked.

- Proofs are bounded. A parser proved for inputs up to 64 bytes says nothing about byte 65.
- A proof about code that calls C is only as good as the models the harness gives it.
- Languages other than Zig and C need their own front end. Rust already has
  [Kani](https://github.com/model-checking/kani), which uses the same checker.
- A proof that needs too much memory ends with an error saying cbmc was killed. There is no timeout yet.
- CBMC 5.95 and Zig 0.16.0 are the tested versions.
