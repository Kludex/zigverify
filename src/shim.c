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
