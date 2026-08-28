/* Vector_CopyBackward_8 - 0x00504330 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-08-28): the copy-backward member of the 8-byte
 * {CStringA, CStringA} pair vector - walk [param_1, param_2) from the
 * top down (`sub ebx,8` / `sub ebp,8` at 0x504356/0x504359), assigning
 * both CString members with the copy-on-write assignment - the stride-8
 * sibling of Vector_CopyBackward_34 (0x503f10) and _1e (0x504030),
 * assignment-based rather than rep-movs because the members are
 * refcounted handles. Fills the same slot in Vector_InsertN_8's shift
 * arm (its one binary caller, 0x503368) that Vector_CopyBackward_34
 * fills in Vector_InsertN_34's.
 */
#include "ghidra_types.h"


int * Vector_CopyBackward_8(int param_1,int param_2,int *param_3)

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
        AssignStringBuffer(piVar6,*(int *)(param_2 + -8));
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
        AssignStringBuffer(piVar7,*piVar1);
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

