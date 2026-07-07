/* FUN_004f3440 - 0x004f3440 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_004f3440(undefined4 param_1)

{
  undefined4 *puVar1;
  float *extraout_EDX;
  int unaff_ESI;
  
  puVar1 = (undefined4 *)FUN_004f3a60(param_1);
  _DAT_005a93e0 = *puVar1;
  _DAT_005a93e4 = puVar1[1];
  _DAT_005a93e8 = puVar1[2];
  _DAT_005a93ec = puVar1[3];
  FUN_004f3ba0();
  extraout_EDX[0xc] = *(float *)(unaff_ESI + 0x98);
  extraout_EDX[0xd] = *(float *)(unaff_ESI + 0x9c);
  extraout_EDX[0xe] = *(float *)(unaff_ESI + 0xa0);
  if (_DAT_0054c870 <= ABS(*(float *)(unaff_ESI + 0xb8) - _DAT_00557fb0)) {
    *extraout_EDX = *(float *)(unaff_ESI + 0xb8) * *extraout_EDX;
    extraout_EDX[1] = extraout_EDX[1] * *(float *)(unaff_ESI + 0xb8);
    extraout_EDX[2] = extraout_EDX[2] * *(float *)(unaff_ESI + 0xb8);
    extraout_EDX[4] = extraout_EDX[4] * *(float *)(unaff_ESI + 0xb8);
    extraout_EDX[5] = extraout_EDX[5] * *(float *)(unaff_ESI + 0xb8);
    extraout_EDX[6] = extraout_EDX[6] * *(float *)(unaff_ESI + 0xb8);
    extraout_EDX[8] = extraout_EDX[8] * *(float *)(unaff_ESI + 0xb8);
    extraout_EDX[9] = extraout_EDX[9] * *(float *)(unaff_ESI + 0xb8);
    extraout_EDX[10] = extraout_EDX[10] * *(float *)(unaff_ESI + 0xb8);
  }
  return;
}

