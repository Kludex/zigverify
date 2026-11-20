//! A panic namespace that reports every Zig safety check to the verifier as one failed
//! assertion, instead of formatting a message the solver would have to step through.

const Kind = @import("failure.zig").Kind;

extern fn verifier_fail(kind: u32, a: usize, b: usize) noreturn;

pub fn fail(kind: Kind, a: usize, b: usize) noreturn {
    @branchHint(.cold);
    verifier_fail(@intFromEnum(kind), a, b);
}

pub fn call(_: []const u8, _: ?usize) noreturn {
    fail(.panic, 0, 0);
}

pub fn sentinelMismatch(_: anytype, _: anytype) noreturn {
    fail(.sentinel_mismatch, 0, 0);
}

pub fn unwrapError(_: anyerror) noreturn {
    fail(.unwrap_error, 0, 0);
}

pub fn outOfBounds(index: usize, len: usize) noreturn {
    fail(.out_of_bounds, index, len);
}

pub fn startGreaterThanEnd(start: usize, end: usize) noreturn {
    fail(.start_greater_than_end, start, end);
}

pub fn inactiveUnionField(_: anytype, _: anytype) noreturn {
    fail(.inactive_union_field, 0, 0);
}

pub fn sliceCastLenRemainder(src_len: usize) noreturn {
    fail(.slice_cast_len_remainder, src_len, 0);
}

pub fn reachedUnreachable() noreturn {
    fail(.reached_unreachable, 0, 0);
}

pub fn unwrapNull() noreturn {
    fail(.unwrap_null, 0, 0);
}

pub fn castToNull() noreturn {
    fail(.cast_to_null, 0, 0);
}

pub fn incorrectAlignment() noreturn {
    fail(.incorrect_alignment, 0, 0);
}

pub fn invalidErrorCode() noreturn {
    fail(.invalid_error_code, 0, 0);
}

pub fn integerOutOfBounds() noreturn {
    fail(.integer_out_of_bounds, 0, 0);
}

pub fn integerOverflow() noreturn {
    fail(.integer_overflow, 0, 0);
}

pub fn shlOverflow() noreturn {
    fail(.shl_overflow, 0, 0);
}

pub fn shrOverflow() noreturn {
    fail(.shr_overflow, 0, 0);
}

pub fn divideByZero() noreturn {
    fail(.divide_by_zero, 0, 0);
}

pub fn exactDivisionRemainder() noreturn {
    fail(.exact_division_remainder, 0, 0);
}

pub fn integerPartOutOfBounds() noreturn {
    fail(.integer_part_out_of_bounds, 0, 0);
}

pub fn corruptSwitch() noreturn {
    fail(.corrupt_switch, 0, 0);
}

pub fn shiftRhsTooBig() noreturn {
    fail(.shift_rhs_too_big, 0, 0);
}

pub fn invalidEnumValue() noreturn {
    fail(.invalid_enum_value, 0, 0);
}

pub fn forLenMismatch() noreturn {
    fail(.for_len_mismatch, 0, 0);
}

pub fn copyLenMismatch() noreturn {
    fail(.copy_len_mismatch, 0, 0);
}

pub fn memcpyAlias() noreturn {
    fail(.memcpy_alias, 0, 0);
}

pub fn noreturnReturned() noreturn {
    fail(.noreturn_returned, 0, 0);
}
