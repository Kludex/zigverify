//! A state machine that calls itself to move between states, where one unwind bound does not
//! fit: the scanning loop is as long as the input, while the recursion is two calls deep.

const verifier = @import("verifier");

pub const panic = verifier.panic;

fn indexOfOrEnd(input: []const u8, start: usize, wanted: u8) usize {
    var at = start;
    while (at < input.len and input[at] != wanted) at += 1;
    return at;
}

const Parser = struct {
    state: enum { key, value, done } = .key,
    pos: usize = 0,

    /// The value of a `key=value;` field, or null if the input does not hold one.
    fn next(self: *Parser, input: []const u8) ?[]const u8 {
        switch (self.state) {
            .key => {
                self.pos = indexOfOrEnd(input, self.pos, '=');
                if (self.pos == input.len) return null;
                self.pos += 1;
                self.state = .value;
                return self.next(input);
            },
            .value => {
                const start = self.pos;
                self.pos = indexOfOrEnd(input, start, ';');
                self.state = .done;
                return input[start..self.pos];
            },
            .done => return null,
        }
    }
};

/// For every input of up to 32 bytes, the parser never panics and a value it returns has no `;`.
export fn value_has_no_terminator() void {
    var buffer: [32]u8 = undefined;
    const input = verifier.prefix(u8, &buffer);
    var parser: Parser = .{};
    const value = parser.next(input) orelse return;
    for (value) |byte| verifier.assert(byte != ';');
}
