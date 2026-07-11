/* Widget_HitTest - 0x0050e9c0 in the original binary.
 *
 * Base widget hit-test (vtable slot 4): tests the point against the widget rect (+0x28/+0x2c/+0x30/+0x34) then broadcasts to children (composite pattern). See docs/widgets.md. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined1 __thiscall Widget_HitTest(int param_1,int param_2,int param_3)

{
  int iVar1;
  char cVar2;
  undefined1 uVar3;
  uint uVar4;
  
  iVar1 = param_2;
  if (*(char *)(param_1 + 0x1e) != '\0') {
    return 0;
  }
  uVar3 = 0;
  if ((((*(int *)(param_1 + 0x28) < param_2) &&
       (param_2 < *(int *)(param_1 + 0x30) + *(int *)(param_1 + 0x28))) &&
      (*(int *)(param_1 + 0x2c) < param_3)) &&
     (param_3 < *(int *)(param_1 + 0x34) + *(int *)(param_1 + 0x2c))) {
    uVar3 = 1;
  }
  uVar4 = 0;
  SUBFIELD(param_2,0,undefined1) = uVar3;
  if (*(int *)(param_1 + 0x10) != 0) {
    if (*(int *)(param_1 + 0x10) == 0) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    do {
      cVar2 = (**(code **)(**(int **)(*(int *)(param_1 + 0xc) + uVar4 * 4) + 0x10))(iVar1,param_3);
      if (cVar2 != '\0') {
        SUBFIELD(param_2,0,undefined1) = 1;
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < *(uint *)(param_1 + 0x10));
  }
  return (undefined1)param_2;
}

