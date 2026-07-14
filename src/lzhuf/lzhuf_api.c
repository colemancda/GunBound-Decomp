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
#include <string.h>

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

/* DecodeLZHUFBlock(state, output, compressedInput, compressedSize,
 * outputSize) - the raw-port calling convention every caller under
 * src/fileformat/ (OpenXFSArchive.c x3, LoadGameDataFiles.c x3,
 * DecodeXFSEntryBlock.c x1) already uses, with real, correct arguments
 * at every one of those 7 call sites (independently confirmed against
 * the original binary's own disassembly at 0x4eaba0: the real function
 * reads exactly 5 stack args in this order, storing param2/3/4 into its
 * per-call state's "compressed-data cursor fields" - i.e. the caller-
 * side arguments were never the bug).
 *
 * The actual bug: this symbol name was never DEFINED anywhere in the
 * reconstructed tree - the real decoder was reimplemented under the
 * different name lzhuf_decode_block/lzhuf_decode (see above and
 * lzhuf_internal.h). Every one of those 7 call sites therefore linked
 * against gen_bringup_stubs.py's auto-generated `return 0` no-op stub
 * silently, instead of failing to link - the output buffer was simply
 * never written, so every archive's decoded header/entry data read back
 * as all-zero. This wrapper closes that gap: `state` is unused (the real
 * function reinitializes its tree/ring-buffer state fresh on every call
 * via InitLZHUFTree - confirmed in DecodeLZHUFBlock.c's own header - so
 * nothing persists across calls that this needs to replicate). */
void DecodeLZHUFBlock(void *state, void *output, const void *compressedInput,
                       size_t compressedSize, size_t outputSize) {
    uint8_t *decoded;

    (void)state;
    decoded = lzhuf_decode((const uint8_t *)compressedInput, compressedSize, outputSize);
    if (decoded != NULL) {
        memcpy(output, decoded, outputSize);
        free(decoded);
    }
}
