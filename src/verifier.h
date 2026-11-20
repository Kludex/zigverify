/* The harness API for C. It is the same three calls the Zig module is built on. */
#ifndef VERIFIER_H
#define VERIFIER_H

#include <stddef.h>

/* Fills `len` bytes at `out` with arbitrary values: the proof covers all of them. */
void verifier_any(void *out, size_t len);

/* Discards every input for which `ok` is false. */
void verifier_assume(_Bool ok);

/* Fails the proof if any remaining input makes `ok` false. */
void verifier_check(_Bool ok);

#endif
