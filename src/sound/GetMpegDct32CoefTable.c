/* GetMpegDct32CoefTable - 0x0051a420 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section. (Previously FUN_0051a420.)
 *
 * Evidence for the name (all from outside the body):
 * Disassembly of 0x51a420: mov eax,0xf25a40; ret. Its sole caller,
 * InitMpegSynthesisTables, uses the returned pointer as the destination of
 * the table fill: five rows of 16, 8, 4, 2 and 1 values, each
 * 0.5 / cos((2k+1) * pi / (4 * rowsize)), the factors of the 32-point DCT
 * recursion. The consumers are the MpegDct32, MpegDct16 and MpegDct8
 * families, which read the same 0xf25a40 region directly (first row at
 * 0xf25a40, second at 0xf25a80, third at 0xf25aa0, then 0xf25ab0 and
 * 0xf25ab8), so the table identity is corroborated from the producer and
 * the consumer side. The name says Dct32 because the full table is the
 * 32-point one; the 16 and 8 point variants use its later rows.
 * Same accessor shape as GetMpegAntialiasCsCaTable.
 */
#include "ghidra_types.h"


undefined4 * GetMpegDct32CoefTable(void)

{
  return (undefined4 *)&DAT_00f25a40;
}

