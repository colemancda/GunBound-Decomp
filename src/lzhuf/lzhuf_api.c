/* Public API wrapper for the LZHUF module (include/lzhuf.h).
 *
 * Not itself a decompiled function - the original binary's callers
 * each manage their own state-struct storage and output buffer
 * inline (see FILEFORMATS.md), rather than going through one shared
 * allocate-init-decode-free entry point. This wrapper exists purely
 * to give the reconstructed code a normal malloc/free-based C API.
 */
#include "lzhuf.h"
#include "lzhuf_internal.h"

#include <stdlib.h>

uint8_t *lzhuf_decode(const uint8_t *compressed, size_t compressed_size,
                       size_t outsize) {
    lzhuf_state *s;
    uint8_t *out;

    s = calloc(1, sizeof(lzhuf_state));
    if (!s) {
        return NULL;
    }
    out = malloc(outsize > 0 ? outsize : 1);
    if (!out) {
        free(s);
        return NULL;
    }

    s->data = compressed;
    s->data_len = compressed_size;
    lzhuf_init_tree(s);
    lzhuf_decode_block(s, out, outsize);

    free(s);
    return out;
}
