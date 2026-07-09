/* FUN_00507cc0 - 0x00507cc0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00507cc0(undefined4 param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int unaff_EBX;
  int iVar3;
  
  iVar3 = 0;
  while( true ) {
    uVar2 = Widget_FindChildIndex();
    if ((*(uint *)(unaff_EBX + 0x10) <= uVar2) ||
       (*(bool *)(*(int *)(*(int *)(unaff_EBX + 0xc) + uVar2 * 4) + 0x3a) = param_2 == iVar3,
       *(uint *)(unaff_EBX + 0x10) <= uVar2)) break;
    iVar1 = *(int *)(*(int *)(unaff_EBX + 0xc) + uVar2 * 4);
    *(undefined1 *)(iVar1 + 0x1c) = (undefined1)param_1;
    if (*(char *)(iVar1 + 4) != '\0') {
      *(undefined1 *)(iVar1 + 4) = 0;
    }
    uVar2 = 0;
    if (*(int *)(iVar1 + 0x10) != 0) {
      if (*(int *)(iVar1 + 0x10) == 0) break;
      do {
        Widget_SetEnabled(param_1);
        uVar2 = uVar2 + 1;
      } while (uVar2 < *(uint *)(iVar1 + 0x10));
    }
    iVar3 = iVar3 + 1;
    if (7 < iVar3) {
      return;
    }
  }
                    /* WARNING: Subroutine does not return */
  FUN_004010c0(0x80070057);
}

