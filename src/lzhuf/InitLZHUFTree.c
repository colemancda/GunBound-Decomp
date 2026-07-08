/* InitLZHUFTree - 0x4ea300 in the original binary.
 *
 * Initializes the adaptive Huffman tree: N_CHAR (314) leaf symbols each
 * start with frequency 1, then internal nodes are built bottom-up
 * pairing adjacent frequencies, up to the root at index R (626).
 *
 * The memset()/`s->r = LZHUF_N - LZHUF_F` lines below do NOT correspond
 * to anything in the real 162-byte function at 0x4ea300 - confirmed via
 * both raw disassembly and a fresh Ghidra decompile of that exact
 * address range: the real function only zeroes six small state fields
 * (offsets +0/+4/+0xf6b0/+0xf6b2/+0xf6b4/+0xf6b6), never touches a
 * 4KB+ region, and never writes the constant 0xfc4 (LZHUF_N-LZHUF_F)
 * anywhere. Yet removing them breaks real decoding: tested against 30
 * random archive entries from graphics.xfs, the version without this
 * ring-buffer fill/cursor-init produced 10/30 mismatches against the
 * validated Python reference decoder, while the version with it (as
 * below) produced 0/30. So this logic is real and necessary, but must
 * actually live in a different, not-yet-identified function - most
 * likely a one-time setup/constructor that runs once before
 * InitLZHUFTree is ever called (rather than something InitLZHUFTree
 * itself repeats on every call), left in place here as the pragmatic
 * behavioral-parity fix until that real function is found. See
 * src/README.md for how this was discovered (a real-MSVC-vs-Ghidra
 * byte-comparison exercise).
 */
#include "lzhuf_internal.h"

#include <string.h>

void lzhuf_init_tree(lzhuf_state *s) {
    int i, j;

    memset(s->text_buf, 0x20, sizeof(s->text_buf));
    s->r = LZHUF_N - LZHUF_F;

    for (i = 0; i < LZHUF_N_CHAR; i++) {
        s->freq[i] = 1;
        s->son[i] = i + LZHUF_T;
        s->prnt[i + LZHUF_T] = i;
    }
    i = 0;
    j = LZHUF_N_CHAR;
    while (j <= LZHUF_R) {
        s->freq[j] = s->freq[i] + s->freq[i + 1];
        s->son[j] = i;
        s->prnt[i] = j;
        s->prnt[i + 1] = j;
        i += 2;
        j++;
    }
    s->freq[LZHUF_T] = 0xffff;
    s->prnt[LZHUF_R] = 0;
}
