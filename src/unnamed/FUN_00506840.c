/* FUN_00506840 - 0x00506840 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00506840(int param_1)

{
  uint uVar1;
  int unaff_EBX;
  int iVar2;
  
  iVar2 = 0;
  do {
    uVar1 = Widget_FindChildIndex();
    if (uVar1 != 0xffffffff) {
      if (*(uint *)(unaff_EBX + 0x10) <= uVar1) {
                    /* WARNING: Subroutine does not return */
        FUN_004010c0(0x80070057);
      }
      *(bool *)(*(int *)(*(int *)(unaff_EBX + 0xc) + uVar1 * 4) + 0x3a) = iVar2 == param_1;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 4);
  return;
}

