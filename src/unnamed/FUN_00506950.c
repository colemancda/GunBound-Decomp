/* FUN_00506950 - 0x00506950 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00506950(undefined4 *param_1)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  char *pcVar4;
  long lVar5;
  int iVar6;
  char *pcVar7;
  int *piVar8;
  int iVar9;
  
  uVar3 = Widget_FindChildIndex();
  if (uVar3 != 0xffffffff) {
    if ((uint)param_1[4] <= uVar3) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    pcVar7 = (char *)(*(int *)(param_1[3] + uVar3 * 4) + 0x38);
    pcVar4 = pcVar7;
    if (pcVar7 != (char *)0x0) {
      do {
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
    }
    FUN_004056c0(param_1 + 0x14,pcVar7);
  }
  uVar3 = Widget_FindChildIndex();
  if (uVar3 != 0xffffffff) {
    if ((uint)param_1[4] <= uVar3) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    pcVar7 = (char *)(*(int *)(param_1[3] + uVar3 * 4) + 0x38);
    pcVar4 = pcVar7;
    if (pcVar7 != (char *)0x0) {
      do {
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
    }
    FUN_004056c0(param_1 + 0x15,pcVar7);
  }
  lVar5 = _atol((char *)param_1[0x14]);
  if ((lVar5 + -1 < 499) && (lVar5 = _atol((char *)param_1[0x14]), lVar5 + -1 < 0)) {
    iVar6 = 0;
  }
  else {
    lVar5 = _atol((char *)param_1[0x14]);
    if (lVar5 + -1 < 499) {
      lVar5 = _atol((char *)param_1[0x14]);
      iVar6 = lVar5 + -1;
    }
    else {
      iVar6 = 499;
    }
  }
  if (*(int *)(param_1[0x14] + -0xc) == 0) {
LAB_00506add:
    uVar3 = Widget_FindChildIndex();
    if (uVar3 != 0xffffffff) {
      if ((uint)param_1[4] <= uVar3) {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x80070057);
      }
      (**(code **)**(undefined4 **)(param_1[3] + uVar3 * 4))(1);
    }
    return 1;
  }
  iVar9 = 0;
  if (0 < *(int *)(&DAT_005f3258 + g_clientContext)) {
    piVar8 = (int *)(&DAT_005f3058 + g_clientContext);
    do {
      if ((piVar8[-0x40] == *(int *)(g_clientContext + 0x3f804)) && (*piVar8 == iVar6))
      goto LAB_00506add;
      iVar9 = iVar9 + 1;
      piVar8 = piVar8 + 1;
    } while (iVar9 < *(int *)(&DAT_005f3258 + g_clientContext));
  }
  uVar2 = *param_1;
  uVar3 = DAT_00795070 + 1 & 0x800001ff;
  if ((int)uVar3 < 0) {
    uVar3 = (uVar3 - 1 | 0xfffffe00) + 1;
  }
  if (uVar3 != DAT_00795074) {
    *(undefined4 *)(DAT_00795078 + DAT_00795070 * 4) = 0;
    *(undefined4 *)(DAT_00795878 + DAT_00795070 * 4) = uVar2;
    *(undefined4 *)(DAT_00796078 + DAT_00795070 * 4) = 0x21;
    DAT_00795070 = uVar3;
  }
  return 0;
}

