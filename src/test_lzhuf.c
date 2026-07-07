/* Standalone test driver for lzhuf_decode(): reads a raw compressed
 * blob from argv[1], decodes to argv[3] bytes, writes to argv[2].
 * Used to diff against the already-validated Python reference decoder
 * on real GunBound archive data (see tools/lzhuf/lzhuf.py).
 *
 * Usage: test_lzhuf <compressed_in> <decoded_out> <decompressed_size>
 */
#include "lzhuf.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    FILE *in;
    FILE *out;
    long insize;
    uint8_t *compressed;
    uint8_t *decoded;
    size_t outsize;

    if (argc != 4) {
        fprintf(stderr, "usage: %s <compressed_in> <decoded_out> <decompressed_size>\n", argv[0]);
        return 2;
    }

    in = fopen(argv[1], "rb");
    if (!in) {
        perror("fopen input");
        return 1;
    }
    fseek(in, 0, SEEK_END);
    insize = ftell(in);
    fseek(in, 0, SEEK_SET);
    compressed = malloc((size_t)insize);
    if (fread(compressed, 1, (size_t)insize, in) != (size_t)insize) {
        fprintf(stderr, "short read\n");
        return 1;
    }
    fclose(in);

    outsize = (size_t)strtoul(argv[3], NULL, 10);
    decoded = lzhuf_decode(compressed, (size_t)insize, outsize);
    if (!decoded) {
        fprintf(stderr, "lzhuf_decode failed\n");
        return 1;
    }

    out = fopen(argv[2], "wb");
    if (!out) {
        perror("fopen output");
        return 1;
    }
    fwrite(decoded, 1, outsize, out);
    fclose(out);

    free(compressed);
    free(decoded);
    return 0;
}
