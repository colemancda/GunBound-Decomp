/* LZHUF decoder for GunBound's .xfs/.dat blocks.
 *
 * Classic Okumura/Yoshizaki LZHUF algorithm (public domain reference),
 * confirmed against the decompiled GunBound.gme binary: N_CHAR=314,
 * T=627 (2*N_CHAR-1), ring buffer N=4096, F=60, THRESHOLD=2. See
 * tools/lzhuf/lzhuf.py (the reference this was ported from) and
 * FILEFORMATS.md for the full validation writeup.
 *
 * This is a behavioral-parity port, not a byte-matching one: no MSVC
 * 7.10 toolchain was available to verify identical compiled output
 * against the original binary (see PROGRESS.csv / project README for
 * status). Correctness here is instead verified by decoding real
 * archive data and diffing against the already-validated Python
 * decoder and the game's own embedded checksums.
 */
#ifndef GB_LZHUF_H
#define GB_LZHUF_H

#include <stddef.h>
#include <stdint.h>

/* Decodes `compressed_size` bytes at `compressed` into a newly
 * malloc'd buffer of exactly `outsize` bytes. Returns NULL on
 * allocation failure. Caller owns the returned buffer (free() it). */
uint8_t *lzhuf_decode(const uint8_t *compressed, size_t compressed_size,
                       size_t outsize);

#endif
