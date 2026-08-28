/* Vector_FillN_8 - 0x00503f30 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-08-28): the fill member of the 8-byte {CStringA,
 * CStringA} pair vector - assign the value pair at *param_3 into every
 * element of [param_1, param_2), stepping 8 (`param_1 + 2` on int*),
 * with the copy-on-write CString assignment (refcount at -4, header
 * compare, AssignStringBuffer fallback) applied to both members. Fills
 * the same slot in Vector_InsertN_8's append-overlap and shift arms
 * that Vector_FillN_34 fills in Vector_InsertN_34's; unlike the
 * memcpy-shaped _34/_1e fills it is 209 bytes because the element's
 * members are refcounted handles, not raw bytes. Both binary callers
 * sit inside Vector_InsertN_8 (0x503323, 0x503378).
 */
#include "ghidra_types.h"


void Vector_FillN_8(int *param_1,int *param_2,int *param_3)

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
        AssignStringBuffer(param_1,*param_3);
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
        AssignStringBuffer(param_1 + 1,param_3[1]);
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

