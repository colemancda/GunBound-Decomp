/* Update - 0x4ea580 in the original binary.
 *
 * Called at the end of every DecodeChar() with the just-decoded symbol.
 * Increments that symbol's frequency and, if it now exceeds a
 * neighboring node's frequency, promotes it (swapping the node's
 * position in the tree, reordering both the frequency array and the
 * parent/child index arrays) - the textbook adaptive-Huffman
 * "promote on frequency increase" step. Triggers a full Reconst()
 * rebuild first if the root frequency has hit the overflow threshold.
 */
#include "lzhuf_internal.h"

void lzhuf_update(lzhuf_state *s, int c) {
    if (s->freq[LZHUF_R] == LZHUF_MAX_FREQ) {
        lzhuf_reconst(s);
    }
    c = s->prnt[c + LZHUF_T];
    for (;;) {
        int k, l;
        s->freq[c]++;
        k = s->freq[c];
        l = c + 1;
        if (l < LZHUF_T && s->freq[l] < (uint16_t)k) {
            int i, jj;
            while (l + 1 < LZHUF_T && s->freq[l + 1] < (uint16_t)k) {
                l++;
            }
            s->freq[c] = s->freq[l];
            s->freq[l] = (uint16_t)k;

            i = s->son[c];
            s->prnt[i] = l;
            if (i < LZHUF_T) {
                s->prnt[i + 1] = l;
            }
            jj = s->son[l];
            s->son[l] = i;
            s->prnt[jj] = c;
            if (jj < LZHUF_T) {
                s->prnt[jj + 1] = c;
            }
            s->son[c] = jj;
            c = l;
        }
        c = s->prnt[c];
        if (c == 0) {
            break;
        }
    }
}
