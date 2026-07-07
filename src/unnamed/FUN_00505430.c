/* FUN_00505430 - 0x00505430 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


char __thiscall FUN_00505430(int param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  
  cVar1 = FUN_0050e420(param_2,param_3);
  if (cVar1 != '\0') {
    uVar3 = 0xffffffff;
    uVar2 = 0;
    if (*(uint *)(param_1 + 0x10) != 0) {
      do {
        if (*(uint *)(param_1 + 0x10) <= uVar2) goto LAB_00505492;
        if (*(int *)(*(int *)(*(int *)(param_1 + 0xc) + uVar2 * 4) + 0x20) == 2) {
          if (uVar3 == 0xffffffff) {
            uVar3 = uVar2;
          }
          if (*(uint *)(param_1 + 0x10) <= uVar2) goto LAB_00505492;
          if (*(char *)(*(int *)(*(int *)(param_1 + 0xc) + uVar2 * 4) + 4) != '\0') {
            return cVar1;
          }
        }
        uVar2 = uVar2 + 1;
      } while (uVar2 < *(uint *)(param_1 + 0x10));
      if (uVar3 != 0xffffffff) {
        if (*(uint *)(param_1 + 0x10) <= uVar3) {
LAB_00505492:
                    /* WARNING: Subroutine does not return */
          FUN_004010c0(0x80070057);
        }
        (**(code **)**(undefined4 **)(*(int *)(param_1 + 0xc) + uVar3 * 4))(1);
      }
    }
  }
  return cVar1;
}

