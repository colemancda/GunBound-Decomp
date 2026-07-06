/*
 * Classic Okumura/Yoshizaki LZHUF decoder, public-domain reference,
 * adapted minimally to decode a single in-memory block to a fixed
 * output size (matching GunBound's DecodeLZHUFBlock usage).
 *
 * Usage: lzhuf_ref <infile_compressed_bytes> <outsize> <outfile>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned short ushort;

#define N 4096
#define F 60
#define THRESHOLD 2
#define N_CHAR (256 - THRESHOLD + F)
#define T (N_CHAR * 2 - 1)
#define R (T - 1)
#define MAX_FREQ 0x8000

unsigned char *indata;
long insize, inpos;
ushort getbuf = 0;
uchar getlen = 0;

uint freq[T + 1];
int prnt[T + N_CHAR];
int son[T];

uchar text_buf[N + F - 1];

int GetBit(void)
{
    while (getlen <= 8) {
        int c = (inpos < insize) ? indata[inpos++] : 0;
        getbuf |= c << (8 - getlen);
        getlen += 8;
    }
    int i = (getbuf >> 15) & 1;
    getbuf = (getbuf << 1) & 0xffff;
    getlen--;
    return i;
}

int GetByte(void)
{
    while (getlen <= 8) {
        int c = (inpos < insize) ? indata[inpos++] : 0;
        getbuf |= c << (8 - getlen);
        getlen += 8;
    }
    int i = getbuf;
    getbuf <<= 8;
    getlen -= 8;
    return (i >> 8) & 0xff;
}

void StartHuff(void)
{
    int i, j;
    for (i = 0; i < N_CHAR; i++) {
        freq[i] = 1;
        son[i] = i + T;
        prnt[i + T] = i;
    }
    i = 0; j = N_CHAR;
    while (j <= R) {
        freq[j] = freq[i] + freq[i + 1];
        son[j] = i;
        prnt[i] = prnt[i + 1] = j;
        i += 2; j++;
    }
    freq[T] = 0xffff;
    prnt[R] = 0;
}

void reconst(void)
{
    int i, j, k;
    unsigned f, l;
    j = 0;
    for (i = 0; i < T; i++) {
        if (son[i] >= T) {
            freq[j] = (freq[i] + 1) / 2;
            son[j] = son[i];
            j++;
        }
    }
    for (i = 0, j = N_CHAR; j < T; i += 2, j++) {
        k = i + 1;
        f = freq[j] = freq[i] + freq[k];
        for (k = j - 1; f < freq[k]; k--);
        k++;
        l = (j - k) * 2;
        (void)l;
        memmove(&freq[k + 1], &freq[k], (j - k) * sizeof(freq[0]));
        freq[k] = f;
        memmove(&son[k + 1], &son[k], (j - k) * sizeof(son[0]));
        son[k] = i;
    }
    for (i = 0; i < T; i++) {
        if ((k = son[i]) >= T) {
            prnt[k] = i;
        } else {
            prnt[k] = prnt[k + 1] = i;
        }
    }
}

void update(int c)
{
    int i, j, k, l;
    if (freq[R] == MAX_FREQ) {
        reconst();
    }
    c = prnt[c + T];
    do {
        k = ++freq[c];
        if (k > freq[l = c + 1]) {
            while (k > freq[++l]);
            l--;
            freq[c] = freq[l];
            freq[l] = k;

            i = son[c];
            prnt[i] = l;
            if (i < T) prnt[i + 1] = l;

            j = son[l];
            son[l] = i;

            prnt[j] = c;
            if (j < T) prnt[j + 1] = c;
            son[c] = j;

            c = l;
        }
    } while ((c = prnt[c]) != 0);
}

int DecodeChar(void)
{
    int c = son[R];
    while (c < T) {
        c += GetBit();
        c = son[c];
    }
    c -= T;
    update(c);
    return c;
}

uchar d_code[256];
uchar d_len[256];

void init_dcode_tables(void)
{
    int i;
    /* d_code / d_len as published in the reference source */
    static const uchar dc[256] = {
    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
    0x08,0x08,0x09,0x09,0x0a,0x0a,0x0b,0x0b,
    0x0c,0x0c,0x0c,0x0c,0x0d,0x0d,0x0d,0x0d,
    0x0e,0x0e,0x0e,0x0e,0x0f,0x0f,0x0f,0x0f,
    0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
    0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,
    0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x12,
    0x13,0x13,0x13,0x13,0x13,0x13,0x13,0x13,
    0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,
    0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
    0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
    0x17,0x17,0x17,0x17,0x17,0x17,0x17,0x17,
    0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
    0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
    0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,
    0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19,
    0x1a,0x1a,0x1a,0x1a,0x1a,0x1a,0x1a,0x1a,
    0x1a,0x1a,0x1a,0x1a,0x1a,0x1a,0x1a,0x1a,
    0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,
    0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,
    0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,
    0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,
    0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,
    0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,
    0x1e,0x1e,0x1e,0x1e,0x1e,0x1e,0x1e,0x1e,
    0x1e,0x1e,0x1e,0x1e,0x1e,0x1e,0x1e,0x1e,
    0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,
    0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x21,0x21,0x21,0x21,0x21,0x21,0x21,0x21,
    0x21,0x21,0x21,0x21,0x21,0x21,0x21,0x21,
    };
    static const uchar dl[256] = {
    3,3,3,3,3,3,3,3, 3,3,3,3,3,3,3,3,
    4,4,4,4,4,4,4,4, 4,4,4,4,4,4,4,4,
    4,4,4,4,4,4,4,4, 4,4,4,4,4,4,4,4,
    4,4,4,4,4,4,4,4, 4,4,4,4,4,4,4,4,
    5,5,5,5,5,5,5,5, 5,5,5,5,5,5,5,5,
    5,5,5,5,5,5,5,5, 5,5,5,5,5,5,5,5,
    5,5,5,5,5,5,5,5, 5,5,5,5,5,5,5,5,
    5,5,5,5,5,5,5,5, 5,5,5,5,5,5,5,5,
    6,6,6,6,6,6,6,6, 6,6,6,6,6,6,6,6,
    6,6,6,6,6,6,6,6, 6,6,6,6,6,6,6,6,
    6,6,6,6,6,6,6,6, 6,6,6,6,6,6,6,6,
    6,6,6,6,6,6,6,6, 6,6,6,6,6,6,6,6,
    6,6,6,6,6,6,6,6, 6,6,6,6,6,6,6,6,
    6,6,6,6,6,6,6,6, 6,6,6,6,6,6,6,6,
    6,6,6,6,6,6,6,6, 6,6,6,6,6,6,6,6,
    6,6,6,6,6,6,6,6, 6,6,6,6,6,6,6,6,
    };
    for (i = 0; i < 256; i++) { d_code[i] = dc[i]; d_len[i] = dl[i]; }
}

int DecodePosition(void)
{
    uint i, j, c;
    i = GetByte();
    c = (uint)d_code[i] << 6;
    j = d_len[i] - 2;
    while (j--) {
        i = (i << 1) + GetBit();
    }
    return c | (i & 0x3f);
}

int main(int argc, char **argv)
{
    if (argc < 4) { fprintf(stderr, "usage: %s infile outsize outfile\n", argv[0]); return 1; }
    FILE *fi = fopen(argv[1], "rb");
    fseek(fi, 0, SEEK_END);
    insize = ftell(fi);
    fseek(fi, 0, SEEK_SET);
    indata = malloc(insize);
    fread(indata, 1, insize, fi);
    fclose(fi);

    long outsize = atol(argv[2]);
    unsigned char *outbuf = malloc(outsize);

    init_dcode_tables();
    StartHuff();
    inpos = 0; getbuf = 0; getlen = 0;

    int r = N - F;
    memset(text_buf, ' ', sizeof(text_buf));
    long count = 0;
    while (count < outsize) {
        int c = DecodeChar();
        if (c < 256) {
            outbuf[count++] = c;
            text_buf[r++] = c;
            r &= (N - 1);
        } else {
            int i = (r - DecodePosition() - 1) & (N - 1);
            int j = c - 255 + THRESHOLD;
            for (int k = 0; k < j; k++) {
                if (count >= outsize) break;
                int cc = text_buf[i & (N - 1)];
                outbuf[count++] = cc;
                text_buf[r++] = cc;
                r &= (N - 1);
                i++;
            }
        }
    }

    FILE *fo = fopen(argv[3], "wb");
    fwrite(outbuf, 1, outsize, fo);
    fclose(fo);
    return 0;
}
