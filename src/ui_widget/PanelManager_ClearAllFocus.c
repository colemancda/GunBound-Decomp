/* PanelManager_ClearAllFocus - 0x0050efa0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void PanelManager_ClearAllFocus(int *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  
  puVar1 = (undefined4 *)param_1[1];
  DAT_00793664 = 0;
  while( true ) {
    do {
      if (puVar1 == (undefined4 *)0x0) {
        (**(code **)(*param_1 + 0x18))();
        return;
      }
      iVar2 = puVar1[2];
      puVar1 = (undefined4 *)*puVar1;
      uVar3 = 0;
      *(undefined1 *)(iVar2 + 4) = 0;
    } while (*(int *)(iVar2 + 0x10) == 0);
    if (*(int *)(iVar2 + 0x10) == 0) break;
    do {
      FUN_0050e790();
      uVar3 = uVar3 + 1;
    } while (uVar3 < *(uint *)(iVar2 + 0x10));
  }
                    /* WARNING: Subroutine does not return */
  ThrowCxxException(0x80070057);
}

