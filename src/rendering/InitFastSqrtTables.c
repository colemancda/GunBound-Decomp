/* InitFastSqrtTables - 0x004f1eb0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (batch 40). Fills the two 0x8000-entry lookup tables of a float
 * square-root-by-bit-manipulation scheme. Index i supplies the top 15
 * mantissa bits (bits 8..22) of a float whose exponent is fixed: for
 * DAT_006990c0 the float is 0x3f800000 | i << 8 (range [1,2)), for
 * DAT_006790c0 it is 0x40000000 | i << 8 (range [2,4)); each entry is the
 * mantissa field (& 0x7fffff) of the square root of that float (the binary
 * reads the bit pattern with fld dword and uses fsqrt, so the port's
 * (float) integer conversion is a decompiler artefact).
 *
 * External evidence: the consumer FUN_004ed300 (0x4ed358-0x4ed38d) does
 * the matching half of the trick on a float result - it halves the exponent
 * (add 0xc0800000, shr 1, add 0x3f800000, and 0x7f800000), indexes
 * DAT_006790c0 with a 16-bit index (float bits 8..23) and ORs the table
 * mantissa in. Bit 23 is the exponent LSB, so the two 0x8000-entry tables
 * (DAT_006990c0 sits exactly 0x20000 bytes above DAT_006790c0) are the two
 * halves of one 0x10000-entry table: even exponent -> [2,4), odd -> [1,2).
 * Sole caller InitGame.
 */
#include "ghidra_types.h"
#include <math.h>

/* The binary stores the integer bit pattern to the stack, loads it with fld
 * dword (a reinterpretation, not an int-to-float conversion), fsqrts it and
 * stores the float back with fstp dword, then masks the stored BITS with
 * 0x7fffff. Both directions are bit reinterpretations. */
typedef union {
  float f;
  unsigned int u;
} SqrtBits;

static unsigned int SqrtMantissaBits(unsigned int bits)
{
  SqrtBits v;
  v.u = bits;
  v.f = (float)sqrt((double)v.f);
  return v.u & 0x7fffff;
}

void InitFastSqrtTables(void)

{
  uint uVar1;
  
  uVar1 = 0;
  do {
    DAT_006990c0[uVar1] = SqrtMantissaBits((uVar1 | 0x3f8000) << 8);
    DAT_006790c0[uVar1] = SqrtMantissaBits((uVar1 | 0x400000) << 8);
    uVar1 = uVar1 + 1;
  } while (uVar1 < 0x8000);
  return;
}
