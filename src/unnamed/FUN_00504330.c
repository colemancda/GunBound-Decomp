/* FUN_00504330 - 0x00504330 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int * FUN_00504330(int param_1,int param_2,int *param_3)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  int *piVar8;
  
  while (param_1 != param_2) {
    iVar3 = param_3[-2];
    iVar5 = param_2 + -8;
    piVar6 = param_3 + -2;
    piVar1 = (int *)(*(int *)(param_2 + -8) + -0x10);
    piVar7 = (int *)(iVar3 + -0x10);
    if (piVar1 != piVar7) {
      piVar2 = (int *)(iVar3 + -4);
      if ((*(int *)(iVar3 + -4) < 0) || (*piVar1 != *piVar7)) {
        FUN_004056c0(piVar6,*(int *)(param_2 + -8));
      }
      else {
        iVar4 = FUN_0043de10();
        LOCK();
        iVar3 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar3 == 1 || iVar3 + -1 < 0) {
          (**(code **)(*(int *)*piVar7 + 4))(piVar7);
        }
        *piVar6 = iVar4 + 0x10;
      }
    }
    piVar1 = (int *)(param_2 + -4);
    iVar3 = param_3[-1];
    piVar7 = param_3 + -1;
    piVar2 = (int *)(*piVar1 + -0x10);
    piVar8 = (int *)(iVar3 + -0x10);
    param_2 = iVar5;
    param_3 = piVar6;
    if (piVar2 != piVar8) {
      if ((*(int *)(iVar3 + -4) < 0) || (*piVar2 != *piVar8)) {
        FUN_004056c0(piVar7,*piVar1);
      }
      else {
        iVar5 = FUN_0043de10();
        piVar1 = (int *)(iVar3 + -4);
        LOCK();
        iVar3 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar3 == 1 || iVar3 + -1 < 0) {
          (**(code **)(*(int *)*piVar8 + 4))(piVar8);
        }
        *piVar7 = iVar5 + 0x10;
      }
    }
  }
  return param_3;
}

