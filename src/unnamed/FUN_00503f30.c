/* FUN_00503f30 - 0x00503f30 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00503f30(int *param_1,int *param_2,int *param_3)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  
  for (; param_1 != param_2; param_1 = param_1 + 2) {
    iVar3 = *param_1;
    piVar1 = (int *)(*param_3 + -0x10);
    piVar5 = (int *)(iVar3 + -0x10);
    if (piVar1 != piVar5) {
      piVar2 = (int *)(iVar3 + -4);
      if ((*(int *)(iVar3 + -4) < 0) || (*piVar1 != *piVar5)) {
        FUN_004056c0(param_1,*param_3);
      }
      else {
        iVar4 = FUN_0043de10();
        LOCK();
        iVar3 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar3 == 1 || iVar3 + -1 < 0) {
          (**(code **)(*(int *)*piVar5 + 4))(piVar5);
        }
        *param_1 = iVar4 + 0x10;
      }
    }
    iVar3 = param_1[1];
    piVar1 = (int *)(param_3[1] + -0x10);
    piVar5 = (int *)(iVar3 + -0x10);
    if (piVar1 != piVar5) {
      piVar2 = (int *)(iVar3 + -4);
      if ((*(int *)(iVar3 + -4) < 0) || (*piVar1 != *piVar5)) {
        FUN_004056c0(param_1 + 1,param_3[1]);
      }
      else {
        iVar4 = FUN_0043de10();
        LOCK();
        iVar3 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar3 == 1 || iVar3 + -1 < 0) {
          (**(code **)(*(int *)*piVar5 + 4))(piVar5);
        }
        param_1[1] = iVar4 + 0x10;
      }
    }
  }
  return;
}

