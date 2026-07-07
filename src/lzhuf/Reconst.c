/* Reconst - 0x4ea3b0 in the original binary.
 *
 * Periodic full tree rebuild, triggered by Update() whenever the root
 * frequency (+0xde28) reaches the 32768 (MAX_FREQ) overflow threshold.
 * Halves every leaf frequency (integer average with its sibling, per
 * the reference LZHUF.C), then rebuilds all internal nodes bottom-up
 * in frequency order to keep the tree weight-balanced.
 */
#include "lzhuf_internal.h"

#include <string.h>

void lzhuf_reconst(lzhuf_state *s) {
    int i, j, k, f, k2;

    j = 0;
    for (i = 0; i < LZHUF_T; i++) {
        if (s->son[i] >= LZHUF_T) {
            s->freq[j] = (s->freq[i] + 1) / 2;
            s->son[j] = s->son[i];
            j++;
        }
    }
    i = 0;
    for (j = LZHUF_N_CHAR; j < LZHUF_T; j++) {
        k = i + 1;
        f = s->freq[i] + s->freq[k];
        s->freq[j] = (uint16_t)f;
        k2 = j - 1;
        while (f < s->freq[k2]) {
            k2--;
        }
        k2++;
        memmove(&s->freq[k2 + 1], &s->freq[k2], (size_t)(j - k2) * sizeof(s->freq[0]));
        s->freq[k2] = (uint16_t)f;
        memmove(&s->son[k2 + 1], &s->son[k2], (size_t)(j - k2) * sizeof(s->son[0]));
        s->son[k2] = i;
        i += 2;
    }
    for (i = 0; i < LZHUF_T; i++) {
        k = s->son[i];
        if (k >= LZHUF_T) {
            s->prnt[k] = i;
        } else {
            s->prnt[k] = i;
            s->prnt[k + 1] = i;
        }
    }
}
