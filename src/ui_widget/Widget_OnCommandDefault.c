/* Widget_OnCommandDefault - 0x0050eb10 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall Widget_OnCommandDefault(int *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  
  uVar1 = param_1[4];
  if (param_2 == 0x1100) {
    uVar2 = Widget_FindChildIndex();
    uVar3 = uVar2 + 1;
    if ((int)uVar3 < (int)uVar1) {
      do {
        if ((uint)param_1[4] <= uVar3) goto LAB_0050ecad;
        if ((*(int *)(*(int *)(param_1[3] + uVar3 * 4) + 0x20) == 2) && (uVar3 != uVar2)) {
          if ((uint)param_1[4] <= uVar2) {
                    /* WARNING: Subroutine does not return */
            ThrowCxxException(0x80070057);
          }
          (**(code **)**(undefined4 **)(param_1[3] + uVar2 * 4))(0);
          if ((uint)param_1[4] <= uVar3) goto LAB_0050ecad;
          (**(code **)**(undefined4 **)(param_1[3] + uVar3 * 4))(1);
          break;
        }
        uVar3 = uVar3 + 1;
      } while ((int)uVar3 < (int)uVar1);
    }
    if (uVar3 == uVar1) {
      (**(code **)(*param_1 + 0x1c))(0x1000,param_3,0);
    }
  }
  else if (param_2 == 0x1101) {
    uVar3 = Widget_FindChildIndex();
    iVar6 = 0;
    if (0 < (int)uVar1) {
      iVar4 = uVar3 + uVar1;
      while (uVar2 = iVar4 % (int)uVar1, uVar2 < (uint)param_1[4]) {
        if ((*(int *)(*(int *)(param_1[3] + uVar2 * 4) + 0x20) == 2) && (uVar2 != uVar3)) {
          if ((uint)param_1[4] <= uVar3) {
                    /* WARNING: Subroutine does not return */
            ThrowCxxException(0x80070057);
          }
          (**(code **)**(undefined4 **)(param_1[3] + uVar3 * 4))(0);
          iVar6 = (uVar3 - iVar6) + uVar1;
          goto LAB_0050ec3c;
        }
        iVar6 = iVar6 + 1;
        iVar4 = iVar4 + -1;
        if ((int)uVar1 <= iVar6) {
          return;
        }
      }
LAB_0050ecad:
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
  }
  else if (param_2 == 0x1102) {
    uVar2 = Widget_FindChildIndex();
    iVar6 = 0;
    uVar3 = uVar2;
    if (0 < (int)uVar1) {
      while (uVar5 = (int)uVar3 % (int)uVar1, uVar5 < (uint)param_1[4]) {
        if ((*(int *)(*(int *)(param_1[3] + uVar5 * 4) + 0x20) == 2) && (uVar5 != uVar2)) {
          if (uVar2 < (uint)param_1[4]) {
            (**(code **)**(undefined4 **)(param_1[3] + uVar2 * 4))(0);
            iVar6 = iVar6 + uVar2;
LAB_0050ec3c:
            if ((uint)(iVar6 % (int)uVar1) < (uint)param_1[4]) {
              (**(code **)**(undefined4 **)(param_1[3] + (iVar6 % (int)uVar1) * 4))(1);
              return;
            }
          }
                    /* WARNING: Subroutine does not return */
          ThrowCxxException(0x80070057);
        }
        iVar6 = iVar6 + 1;
        uVar3 = uVar3 + 1;
        if ((int)uVar1 <= iVar6) {
          return;
        }
      }
      goto LAB_0050ecad;
    }
  }
  else if ((int *)param_1[2] != (int *)0x0) {
    (**(code **)(*(int *)param_1[2] + 0x1c))(param_2,param_3,param_4);
    return;
  }
  return;
}

