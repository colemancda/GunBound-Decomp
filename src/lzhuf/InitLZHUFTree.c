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
 * anywhere. Confirmed empirically that this logic is nonetheless real
 * and necessary (30 random graphics.xfs entries: 10/30 mismatches
 * without it, 0/30 with it, against the validated Python reference
 * decoder) - and now confirmed exactly where it really lives: inline
 * in the real DecodeLZHUFBlock (0x4eaba0), immediately after its own
 * call to InitLZHUFTree() -
 *
 *   InitLZHUFTree();
 *   *param_1 = param_5;
 *   puVar11 = param_1 + 2;
 *   for (iVar5 = 0x3f1; iVar5 != 0; iVar5 = iVar5 + -1) {
 *       *puVar11 = 0x20202020;    // 1009 * 4 bytes = 0xfc4, all spaces
 *       puVar11 = puVar11 + 1;
 *   }
 *   uVar12 = 0xfc4;               // ring-buffer cursor = LZHUF_N - LZHUF_F
 *
 * i.e. this project's `lzhuf_decode_block()` (src/lzhuf/
 * DecodeLZHUFBlock.c) is the function that should own this logic, not
 * `lzhuf_init_tree()` here - left in place in this function rather than
 * moved, since this project's API deliberately splits state-struct
 * setup (InitLZHUFTree + this fill) from the decode loop itself in a
 * way the original binary doesn't, and moving it would only matter for
 * exact per-function matching, not behavior (see src/README.md's
 * scope note). InitLZHUFTree's *other* caller, EncodeLZHUFBlock (the LZHUF
 * encoder/compressor - out of scope for this project, which only ever
 * needs to decompress), independently repeats this exact same fill
 * inline after its own call to InitLZHUFTree() - so this pattern isn't
 * centralized in one shared constructor as first guessed; every caller
 * duplicates it. Found via a real-MSVC-vs-Ghidra byte-comparison
 * exercise - see src/README.md.
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
