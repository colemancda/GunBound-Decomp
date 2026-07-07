/* InitLZHUFTree - 0x4ea300 in the original binary.
 *
 * Initializes the adaptive Huffman tree: N_CHAR (314) leaf symbols each
 * start with frequency 1, then internal nodes are built bottom-up
 * pairing adjacent frequencies, up to the root at index R (626). Also
 * seeds the ring buffer with ASCII spaces (0x20) per the reference
 * LZHUF.C convention, and sets the initial ring-buffer write cursor.
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
