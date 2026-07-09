/* FUN_0050a8f0 - 0x0050a8f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0050a8f0(int param_1)

{
  uint uVar1;
  
  if (((*(char *)(param_1 + 0x90) != '\0') && (*(int *)(param_1 + 0x94) != -1)) &&
     (uVar1 = Widget_FindChildIndex(), uVar1 != 0xffffffff)) {
    if (*(uint *)(param_1 + 0x10) <= uVar1) goto LAB_0050a945;
    FUN_0050f840();
  }
  uVar1 = 0;
  if (*(int *)(param_1 + 0x10) != 0) {
    if (*(int *)(param_1 + 0x10) == 0) {
LAB_0050a945:
                    /* WARNING: Subroutine does not return */
      FUN_004010c0(0x80070057);
    }
    do {
      (**(code **)(**(int **)(*(int *)(param_1 + 0xc) + uVar1 * 4) + 0x20))();
      uVar1 = uVar1 + 1;
    } while (uVar1 < *(uint *)(param_1 + 0x10));
  }
  return;
}

