/* FUN_00505520 - 0x00505520 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00505520(int param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  int unaff_EBX;
  
  uVar2 = Widget_FindChildIndex();
  if (uVar2 != 0xffffffff) {
    if (*(uint *)(unaff_EBX + 0x10) <= uVar2) {
                    /* WARNING: Subroutine does not return */
      FUN_004010c0(0x80070057);
    }
    iVar1 = *(int *)(*(int *)(unaff_EBX + 0xc) + uVar2 * 4);
    *(int *)(iVar1 + 0x38) = param_1;
    *(undefined4 *)(iVar1 + 0x3c) = param_2;
    if (param_1 < 1) {
      FUN_0050e7d0(0);
      return;
    }
    FUN_0050e7d0(1);
  }
  return;
}

