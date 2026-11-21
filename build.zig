const std = @import("std");

/// One Zig file of harnesses, and what the checker is expected to say about each.
pub const Harness = struct {
    /// The file whose `export fn`s are the harnesses. It is compiled once for all `proofs`.
    root_source_file: std.Build.LazyPath,
    /// Modules the harness imports, besides `verifier`.
    imports: []const std.Build.Module.Import = &.{},
    /// Whether std takes its simple code paths, as it does for fuzzers. `std.mem.eql` then
    /// compares byte by byte; its chunked comparison at an unknown length is a problem the
    /// solver does not finish. Turn it off only to prove something about the fast paths.
    simple_std: bool = true,
    proofs: []const Proof,
};

/// One C file of harnesses: functions that take no arguments and include `verifier.h`.
pub const CHarness = struct {
    c_source_file: std.Build.LazyPath,
    proofs: []const Proof,
};

pub const Proof = struct {
    function: []const u8,
    /// `.refuted` is for seeded bugs: the step passes only if a counterexample is found.
    expect: enum { proved, refuted } = .proved,
    /// How many times any loop may run. A loop that needs more makes the proof inconclusive,
    /// never silently partial.
    unwind: u32 = 64,
    /// Bounds for single functions, overriding `unwind` for their loops and their recursion.
    bounds: []const Bound = &.{},
};

pub const Bound = struct {
    /// The Zig function as reports print it: the file, then the declaration path, joined by
    /// underscores, such as `chunked_Decoder_next`.
    function: []const u8,
    unwind: u32,
};

pub const Prover = struct {
    b: *std.Build,
    verifier: *std.Build.Module,
    runner: *std.Build.Step.Compile,
    shim: std.Build.LazyPath,
    docker_image: ?[]const u8,

    /// `zigverify` is this package's builder: `b` here, `b.dependency("zigverify", .{}).builder` elsewhere.
    /// With a `docker_image`, CBMC runs in that image instead of from `PATH`.
    pub fn init(b: *std.Build, zigverify: *std.Build, docker_image: ?[]const u8) Prover {
        return .{
            .b = b,
            .verifier = zigverify.createModule(.{ .root_source_file = zigverify.path("src/verifier.zig") }),
            .runner = zigverify.addExecutable(.{
                .name = "zigverify-run",
                .root_module = zigverify.createModule(.{
                    .root_source_file = zigverify.path("src/run.zig"),
                    .target = b.graph.host,
                }),
            }),
            .shim = zigverify.path("src/shim.c"),
            .docker_image = docker_image,
        };
    }

    /// Makes `step` depend on one checker run per proof.
    pub fn add(prover: Prover, step: *std.Build.Step, harness: Harness) void {
        const b = prover.b;
        const object = b.addObject(.{
            .name = "harness",
            .root_module = b.createModule(.{
                .root_source_file = harness.root_source_file,
                // The checker reads C, and Zig's C backend keeps every safety check.
                .target = b.resolveTargetQuery(.{ .ofmt = .c }),
                .optimize = .ReleaseSafe,
                .fuzz = harness.simple_std,
                .imports = harness.imports,
            }),
        });
        object.root_module.addImport("verifier", prover.verifier);
        const prepare = b.addRunArtifact(prover.runner);
        prepare.addArg("prepare");
        prepare.addFileArg(object.getEmittedBin());
        const prepared = prepare.addOutputFileArg("harness.c");
        prover.addRuns(step, prepared, harness.root_source_file, harness.proofs);
    }

    /// Makes `step` depend on one checker run per proof of a harness written in C.
    pub fn addC(prover: Prover, step: *std.Build.Step, harness: CHarness) void {
        prover.addRuns(step, harness.c_source_file, null, harness.proofs);
    }

    fn addRuns(
        prover: Prover,
        step: *std.Build.Step,
        c_file: std.Build.LazyPath,
        zig_source: ?std.Build.LazyPath,
        proofs: []const Proof,
    ) void {
        const b = prover.b;
        for (proofs) |proof| {
            const run = b.addRunArtifact(prover.runner);
            run.addFileArg(c_file);
            run.addDirectoryArg(.{ .cwd_relative = b.graph.zig_lib_directory.path.? });
            run.addFileArg(prover.shim);
            run.addArgs(&.{ proof.function, @tagName(proof.expect), b.fmt("{d}", .{proof.unwind}) });
            run.addArg(prover.docker_image orelse "");
            if (zig_source) |file| run.addFileArg(file) else run.addArg("");
            for (proof.bounds) |bound| run.addArg(b.fmt("{s}={d}", .{ bound.function, bound.unwind }));
            step.dependOn(&run.step);
        }
    }
};

pub fn build(b: *std.Build) void {
    const test_step = b.step("test", "Run the unit tests");
    const tests = b.addTest(.{
        .root_module = b.createModule(.{ .root_source_file = b.path("src/run.zig"), .target = b.graph.host }),
    });
    test_step.dependOn(&b.addRunArtifact(tests).step);

    const docker_image = b.option([]const u8, "cbmc-docker-image", "Run cbmc from this Docker image instead of PATH");
    const prover: Prover = .init(b, b, docker_image);
    const verify_step = b.step("verify", "Prove the examples, and check that their seeded bugs are found");
    prover.add(verify_step, .{
        .root_source_file = b.path("examples/midpoint.zig"),
        .proofs = &.{
            .{ .function = "naive_midpoint_never_panics", .expect = .refuted },
            .{ .function = "midpoint_is_between" },
            .{ .function = "midpoint_is_below_high", .expect = .refuted },
            .{ .function = "count_zeros_never_panics", .unwind = 17 },
        },
    });
    prover.add(verify_step, .{
        .root_source_file = b.path("examples/key_value.zig"),
        .proofs = &.{.{
            .function = "value_has_no_terminator",
            .unwind = 33,
            .bounds = &.{.{ .function = "key_value_Parser_next", .unwind = 3 }},
        }},
    });
    prover.add(verify_step, .{
        .root_source_file = b.path("examples/allocation.zig"),
        .proofs = &.{
            .{ .function = "dupe_pair_never_leaks", .unwind = 9 },
            .{ .function = "dupe_pair_without_errdefer_never_leaks", .unwind = 9, .expect = .refuted },
            .{ .function = "free_twice_is_caught", .unwind = 9, .expect = .refuted },
        },
    });
    // Proofs about a real consumer, against the CPython and libuv models. They need that
    // project's sources and CPython's headers, so the step exists only when both are given.
    const zuvloop_source = b.option([]const u8, "zuvloop", "Path to a zuvloop checkout, for verify-zuvloop");
    const python_include = b.option([]const u8, "python-include", "CPython include directory, for verify-zuvloop");
    if (zuvloop_source != null and python_include != null) {
        // The harness needs two of zuvloop's files that its own root does not expose, and a
        // module can only import files beneath its root, so the sources are copied under one.
        const sources = b.addWriteFiles();
        _ = sources.addCopyDirectory(.{ .cwd_relative = b.pathJoin(&.{ zuvloop_source.?, "zig" }) }, "zig", .{});
        const root = sources.add(
            "zuvloop.zig",
            "pub const py = @import(\"zig/py.zig\");\n" ++
                "pub const addr = @import(\"zig/addr.zig\");\n" ++
                "pub const uv = @import(\"zig/uv.zig\");\n" ++
                "pub const loop = @import(\"zig/loop.zig\");\n" ++
                "pub const handle = @import(\"zig/handle.zig\");\n" ++
                "pub const transport = @import(\"zig/transport.zig\");\n",
        );
        const zuvloop = b.createModule(.{ .root_source_file = root, .link_libc = true });
        zuvloop.addIncludePath(.{ .cwd_relative = python_include.? });
        zuvloop.addIncludePath(sources.getDirectory().path(b, "zig"));
        const cpython = b.createModule(.{ .root_source_file = b.path("models/cpython.zig") });
        cpython.addImport("verifier", prover.verifier);
        const libuv = b.createModule(.{ .root_source_file = b.path("models/libuv.zig") });
        libuv.addImport("verifier", prover.verifier);
        const libuv_stream = b.createModule(.{ .root_source_file = b.path("models/libuv_stream.zig") });
        libuv_stream.addImport("verifier", prover.verifier);
        const zuvloop_imports: []const std.Build.Module.Import = &.{
            .{ .name = "libuv_stream", .module = libuv_stream },
            .{ .name = "zuvloop", .module = zuvloop },
            .{ .name = "cpython", .module = cpython },
            .{ .name = "libuv", .module = libuv },
        };
        const ready_queue_bounds: []const Bound = &.{
            .{ .function = "zig_collections_Ready_ensureUnusedCapacity", .unwind = 2 },
            .{ .function = "zig_collections_Ready_grow", .unwind = 2 },
        };
        const zuvloop_step = b.step("verify-zuvloop", "Prove properties of zuvloop against the CPython and libuv models");
        prover.add(zuvloop_step, .{
            .root_source_file = b.path("integration/zuvloop_transport.zig"),
            .imports = zuvloop_imports,
            .proofs = &.{
                .{ .function = "flush_releases_buffers_when_the_socket_takes_everything", .unwind = 20 },
                .{ .function = "flush_releases_buffers_when_the_write_is_queued", .unwind = 20 },
                .{ .function = "flush_releases_buffers_when_the_socket_fails", .unwind = 20 },
                .{ .function = "flush_releases_buffers_when_the_transport_is_closing", .unwind = 20 },
                .{ .function = "fifth_write_is_kept", .unwind = 40 },
                .{ .function = "completed_write_releases_its_buffers", .unwind = 40 },
                .{ .function = "close_drains_then_closes_once", .unwind = 40 },
                .{ .function = "failed_write_closes_once_and_releases_everything", .unwind = 40 },
                .{ .function = "abort_discards_pending_and_closes_once", .unwind = 40 },
                .{ .function = "write_eof_shuts_down_after_the_data", .unwind = 40 },
                .{ .function = "writelines_batches_every_buffer", .unwind = 40 },
                .{ .function = "write_buffer_limits_default_to_64k_and_16k", .unwind = 40 },
                .{ .function = "read_delivers_data_and_eof_closes_once", .unwind = 40 },
                .{ .function = "pause_and_resume_reading_stop_and_restart_reads", .unwind = 40 },
                .{ .function = "buffered_read_fills_the_protocols_buffer", .unwind = 40 },
                // The loop's ready queue grows by doubling. Under the proof's own bound the checker
                // would unroll that forty times over a size it cannot fix; these loops run once.
                .{ .function = "make_transport_opens_and_schedules_the_connection", .unwind = 40, .bounds = ready_queue_bounds },
                .{ .function = "sixteen_byte_writes_are_all_kept", .unwind = 40 },
                .{ .function = "large_read_reaches_the_protocol", .unwind = 40 },
                .{ .function = "refused_write_request_closes_once_and_releases_everything", .unwind = 40 },
                // A bug in zuvloop at the time of writing. Drop `.expect` once it is fixed there.
                .{ .function = "fifth_write_is_kept_when_pause_writing_closes", .unwind = 40, .expect = .refuted },
            },
        });
        // For each scenario, one proof per call that can fail, alone and with a later failure.
        var failure_proofs: std.ArrayList(Proof) = .empty;
        for ([_][]const u8{
            "write_pins_nothing",
            "eof_closes_at_most_once",
            "close_drains_and_closes_once",
            "abort_closes_once",
            "write_eof_releases_buffers",
            "writelines_pins_nothing",
            "buffered_read_releases_views",
        }) |scenario| {
            for (0..4) |failing| {
                for ([_][]const u8{ "_fails", "_and_a_later_one_fail" }) |ending| {
                    failure_proofs.append(b.allocator, .{
                        .function = b.fmt("{s}_when_call_{d}{s}", .{ scenario, failing, ending }),
                        .unwind = 40,
                    }) catch @panic("OOM");
                }
            }
        }
        prover.add(zuvloop_step, .{
            .root_source_file = b.path("integration/zuvloop_transport.zig"),
            .imports = zuvloop_imports,
            .proofs = failure_proofs.items,
        });
        prover.add(zuvloop_step, .{
            .root_source_file = b.path("integration/zuvloop.zig"),
            .imports = zuvloop_imports,
            .proofs = &.{
                .{ .function = "unix_address_from_python_is_safe", .unwind = 20 },
                .{ .function = "ip_address_from_python_is_safe", .unwind = 20 },
                .{ .function = "non_tuple_from_python_is_safe", .unwind = 20 },
                .{ .function = "to_python_is_safe", .unwind = 130 },
            },
        });
    }

    prover.addC(verify_step, .{
        .c_source_file = b.path("examples/midpoint.c"),
        .proofs = &.{
            .{ .function = "c_midpoint_is_between" },
            .{ .function = "c_naive_midpoint_is_between", .expect = .refuted },
            .{ .function = "c_terminator_stays_in_bounds", .expect = .refuted },
        },
    });
    prover.add(verify_step, .{
        .root_source_file = b.path("examples/std_mem.zig"),
        .simple_std = false,
        .proofs = &.{.{ .function = "eql_agrees_with_a_byte_loop", .unwind = 65 }},
    });
    prover.add(verify_step, .{
        .root_source_file = b.path("examples/foreign.zig"),
        .proofs = &.{
            .{ .function = "rejected_text_is_not_an_address" },
            .{ .function = "rejected_text_is_not_an_address_when_failure_is_ignored", .expect = .refuted },
        },
    });
    prover.add(verify_step, .{
        .root_source_file = b.path("examples/sockaddr.zig"),
        .proofs = &.{
            .{ .function = "same_never_panics", .unwind = 130 },
            .{ .function = "same_is_reflexive_and_symmetric", .unwind = 130 },
            .{ .function = "unclamped_length_never_panics", .expect = .refuted },
            .{ .function = "same_is_reflexive_for_every_family", .expect = .refuted },
            .{ .function = "short_buffer_is_never_read_past", .expect = .refuted, .unwind = 130 },
        },
    });
}
