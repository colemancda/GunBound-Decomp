/* ScanTerrainRightForSolid - 0x004e4410 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004e4410 mean this function.)
 *
 * NAMED (batch 48), LIKELY. The rightward twin of ScanTerrainLeftForSolid
 * (0x4e43d0), same terrain context (+0x18 width, +0x1c height, +0x34 one-
 * byte-per-pixel buffer, non-zero = solid; all five callers pass
 * &DAT_006a7708 + g_clientContext) and the mirror-image sentinel: it
 * returns the first column at or after the start column whose pixel is
 * non-zero, or 10000 (0x2710) where the left scan returns -10000, when the
 * row is out of range or the start column is past the width. The callers
 * compare the result against a Peeked value and queue result - 1 only
 * when it is not the 10000 sentinel (the left scan's callers use -10000
 * and result + 1). Register shape differs from the left scan: ECX = row
 * (range-checked against +0x1c), EAX = start column, EDX = terrain
 * context. RESULT RECOVERED (bug round 22): the original
 * returns the column in EAX (the 0x4e4446 inc eax / 0x4e444e exit) or
 * loads 0x2710 at 0x4e4449; the port returned a constant 0, so every
 * caller compared against 0 and the 10000 sentinel never fired. EAX (the
 * start column) is the SECOND Peek at each of the five call sites and ECX
 * (the row) the first, as in the left scan: all five callers now capture
 * them as peekRow/peekCol and the result. LIKELY rather
 * than CERTAIN: the only outside evidence for the direction is the
 * sentinel/layout mirror of the named
 * left scan, not a caller that names the result.
 */
#include "ghidra_types.h"


int __fastcall ScanTerrainRightForSolid(int param_1,int param_2,int regEax)

{
  if ((-1 < param_1) && (param_1 < *(int *)(param_2 + 0x1c))) {
    if (regEax < 0) {
      regEax = 0;
    }
    if (regEax < *(int *)(param_2 + 0x18)) {
      for (; *(char *)(*(int *)(param_2 + 0x18) * param_1 + *(int *)(param_2 + 0x34) + regEax) ==
             '\0'; regEax = regEax + 1) {
      }
      return regEax;
    }
  }
  return 10000;
}
