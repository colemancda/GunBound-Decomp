/* Widget_MouseUpChildren - 0x0050e950 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined1 __thiscall Widget_MouseUpChildren(int param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  uint uVar2;
  undefined1 local_1;
  
  if (*(char *)(param_1 + 0x1e) != '\0') {
    return 0;
  }
  uVar2 = 0;
  local_1 = 0;
  if (*(int *)(param_1 + 0x10) != 0) {
    local_1 = 0;
    if (*(int *)(param_1 + 0x10) == 0) {
                    /* WARNING: Subroutine does not return */
      FUN_004010c0(0x80070057);
    }
    do {
      cVar1 = (**(code **)(**(int **)(*(int *)(param_1 + 0xc) + uVar2 * 4) + 0xc))(param_2,param_3);
      if (cVar1 != '\0') {
        local_1 = 1;
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < *(uint *)(param_1 + 0x10));
  }
  return local_1;
}

