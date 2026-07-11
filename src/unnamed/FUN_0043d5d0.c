/* FUN_0043d5d0 - 0x0043d5d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_0043d5d0(int param_1,int param_2,int param_3)

{
  undefined4 *puVar1;
  uint uVar2;
  char in_AL;
  char cVar3;
  undefined4 local_8;
  
  if (in_AL != 'd') {
    local_8 = in_AL;
    uVar2 = *(uint *)(param_1 + 0xc);
    local_8 = CONCAT22(param_2,(undefined2)local_8);
    if (*(uint *)(param_1 + 0x10) <= uVar2) {
      cVar3 = FUN_0043d840();
      if (cVar3 == '\0') {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x8007000e);
      }
    }
    puVar1 = (undefined4 *)(*(int *)(param_1 + 8) + uVar2 * 6);
    if (puVar1 != (undefined4 *)0x0) {
      *puVar1 = local_8;
      *(undefined2 *)(puVar1 + 1) = param_3;
    }
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
  }
  return;
}

