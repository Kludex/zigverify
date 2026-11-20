#include <stdint.h>
#include "verifier.h"

void verifier_fail(uint32_t kind, size_t a, size_t b) {
    __CPROVER_assert(0, "zig safety check or verifier.assert");
    __CPROVER_assume(0);
}

void verifier_check(_Bool ok) {
    if (!ok) verifier_fail(0, 0, 0);
}

void verifier_assume(_Bool ok) { __CPROVER_assume(ok); }

void verifier_any(void *out, size_t len) { __CPROVER_havoc_slice(out, len); }

/* Stands in for glibc's `__assert_fail`. 29 is `Kind.c_assert` in failure.zig. */
void verifier_assert_fail(const char *assertion, const char *file, unsigned int line, const char *function) {
    verifier_fail(29, line, 0);
}
