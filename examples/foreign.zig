//! Code that calls into a C library. The checker cannot read the library, so the harness
//! supplies a model: a Zig function exported under the C name that says what the call may do.

const verifier = @import("verifier");

pub const panic = verifier.panic;

const resolver = struct {
    extern fn inet_pton(family: c_int, text: [*:0]const u8, out: *anyopaque) c_int;

    const ipv4 = 2;

    fn parse(text: [*:0]const u8) ?[4]u8 {
        var address: [4]u8 = @splat(0);
        if (inet_pton(ipv4, text, &address) != 1) return null;
        return address;
    }

    /// Hands back `0.0.0.0`, the address that means "every interface", for text that is not
    /// an address at all.
    fn parseIgnoringFailure(text: [*:0]const u8) ?[4]u8 {
        var address: [4]u8 = @splat(0);
        _ = inet_pton(ipv4, text, &address);
        return address;
    }
};

var conversion_failed = false;

/// The model. `inet_pton` either fails and leaves `out` alone, or succeeds and fills four
/// bytes. Which one, and with what, is arbitrary: the proof covers every text at once.
fn inetPtonModel(family: c_int, text: [*:0]const u8, out: *anyopaque) callconv(.c) c_int {
    _ = text;
    if (family != resolver.ipv4 or verifier.any(bool)) {
        conversion_failed = true;
        return 0;
    }
    const address: *[4]u8 = @ptrCast(out);
    address.* = verifier.any([4]u8);
    return 1;
}

comptime {
    // When the `extern fn` lives in another file, `export fn inet_pton` does the same.
    @export(&inetPtonModel, .{ .name = "inet_pton" });
}

/// Text the library rejects never becomes an address.
export fn rejected_text_is_not_an_address() void {
    const address = resolver.parse("not an address");
    if (conversion_failed) verifier.assert(address == null);
}

/// Refuted: the return value is ignored, so rejected text becomes `0.0.0.0`.
export fn rejected_text_is_not_an_address_when_failure_is_ignored() void {
    const address = resolver.parseIgnoringFailure("not an address");
    if (conversion_failed) verifier.assert(address == null);
}
