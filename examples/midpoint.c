/* The midpoint proofs again, in C. The checker and the reports are shared, so a language
   only needs a way to produce C and to call these three functions. */

#include <stdint.h>
#include "verifier.h"

static uint32_t midpoint_naive(uint32_t low, uint32_t high) { return (low + high) / 2; }

static uint32_t midpoint(uint32_t low, uint32_t high) { return low + (high - low) / 2; }

/* For every ordered pair, the midpoint lies between the two. */
void c_midpoint_is_between(void) {
    uint32_t low, high;
    verifier_any(&low, sizeof low);
    verifier_any(&high, sizeof high);
    verifier_assume(low <= high);
    uint32_t mid = midpoint(low, high);
    verifier_check(low <= mid);
    verifier_check(mid <= high);
}

/* Refuted: unsigned addition wraps in C instead of trapping, so the result is simply wrong. */
void c_naive_midpoint_is_between(void) {
    uint32_t low, high;
    verifier_any(&low, sizeof low);
    verifier_any(&high, sizeof high);
    verifier_assume(low <= high);
    verifier_check(low <= midpoint_naive(low, high));
}

/* Refuted: `length` may equal the buffer's size, so the terminator lands one past the end. */
void c_terminator_stays_in_bounds(void) {
    char buffer[8];
    size_t length;
    verifier_any(&length, sizeof length);
    verifier_assume(length <= sizeof buffer);
    buffer[length] = 0;
}
