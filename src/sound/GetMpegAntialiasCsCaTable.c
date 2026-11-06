/* GetMpegAntialiasCsCaTable - 0x005180d0 in the original binary.
 *
 * Return the address of the Layer III antialias cs/ca coefficient table
 * (0xf25ac0).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * Disassembly of 0x5180d0: mov eax,0xf25ac0; ret. The sole caller,
 * InitMpegLayerIIITables, fills the table with eight cs/ca pairs
 * (1/sqrt(1+ci^2) and ci/sqrt(1+ci^2) from the ISO ci coefficients at
 * 0x544a88); MpegAntialias then reads the same 0xf25ac0 pairs directly
 * (fmul [0xf25ac0] at 0x51c6c0), so the table identity is corroborated
 * from both the producer and the consumer side.
 */
#include "ghidra_types.h"


undefined * GetMpegAntialiasCsCaTable(void)

{
  return &DAT_00f25ac0;
}

