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
 * context. The port returns a constant 0 because Ghidra lost the real
 * result, which the binary leaves in EAX, so the callers' compare is
 * against 0 here (a known gap, not touched by this rename). LIKELY rather
 * than CERTAIN: the only outside evidence for the direction is the
 * sentinel/layout mirror of the named
 * left scan, not a caller that names the result.
 */
#include "ghidra_types.h"


undefined4 __fastcall ScanTerrainRightForSolid(int param_1,int param_2)

{
  int in_EAX;
  
  if ((-1 < param_1) && (param_1 < *(int *)(param_2 + 0x1c))) {
    if (in_EAX < 0) {
      in_EAX = 0;
    }
    if (in_EAX < *(int *)(param_2 + 0x18)) {
      for (; *(char *)(*(int *)(param_2 + 0x18) * param_1 + *(int *)(param_2 + 0x34) + in_EAX) ==
             '\0'; in_EAX = in_EAX + 1) {
      }
    }
  }
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

