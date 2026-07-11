/* FUN_00507d50 - 0x00507d50 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00507d50(int param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = 0xffffffff;
  uVar1 = 0;
  if (*(uint *)(param_1 + 0x10) != 0) {
    do {
      if (*(uint *)(param_1 + 0x10) <= uVar1) goto LAB_00507d98;
      if (*(int *)(*(int *)(*(int *)(param_1 + 0xc) + uVar1 * 4) + 0x20) == 2) {
        if (uVar2 == 0xffffffff) {
          uVar2 = uVar1;
        }
        if (*(uint *)(param_1 + 0x10) <= uVar1) goto LAB_00507d98;
        if (*(char *)(*(int *)(*(int *)(param_1 + 0xc) + uVar1 * 4) + 4) != '\0') {
          return;
        }
      }
      uVar1 = uVar1 + 1;
    } while (uVar1 < *(uint *)(param_1 + 0x10));
    if (uVar2 != 0xffffffff) {
      if (*(uint *)(param_1 + 0x10) <= uVar2) {
LAB_00507d98:
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x80070057);
      }
      (**(code **)**(undefined4 **)(*(int *)(param_1 + 0xc) + uVar2 * 4))(1);
    }
  }
  return;
}

