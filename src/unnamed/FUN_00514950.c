/* FUN_00514950 - 0x00514950 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_00514950(undefined4 param_1,undefined4 param_2,byte *param_3,int *param_4)

{
  int iVar1;
  int iVar2;
  
  *param_4 = 0;
  iVar1 = FUN_005146c0(param_1,param_2,param_3);
  if (iVar1 == 0) {
    return 0;
  }
  if (*(int *)(param_3 + 8) == 1) {
    if (*(int *)(param_3 + 0x10) < 1) {
      if (*(int *)(param_3 + 4) == 0) {
        if ((*param_3 & 1) == 0) {
          iVar2 = *(int *)(&DAT_00563bcc + *(int *)(param_3 + 0x14) * 4) * iVar1 * 500;
        }
        else {
          iVar2 = *(int *)(&DAT_00563bcc + *(int *)(param_3 + 0x14) * 4) * iVar1 * 1000;
        }
        iVar2 = iVar2 / 0x5a0 + (iVar2 >> 0x1f);
      }
      else {
        iVar2 = *(int *)(&DAT_00563bcc + (*(int *)(param_3 + 0x14) + *(int *)(param_3 + 4) * 4) * 4)
                * iVar1 * 1000;
        iVar2 = iVar2 / 0xb40 + (iVar2 >> 0x1f);
      }
      *param_4 = iVar2 - (iVar2 >> 0x1f);
    }
    else {
      *param_4 = *(int *)(&DAT_00563c6c +
                         (*(int *)(param_3 + 4) * 0x10 + *(int *)(param_3 + 0x10)) * 4) * 1000;
    }
  }
  if (*(int *)(param_3 + 8) == 2) {
    if (*(int *)(param_3 + 0x10) < 1) {
      iVar2 = (*(int *)(&DAT_00563bcc + (*(int *)(param_3 + 0x14) + *(int *)(param_3 + 4) * 4) * 4)
               * iVar1 * 1000) / 0xb40;
    }
    else {
      iVar2 = *(int *)(&DAT_00563b4c + (*(int *)(param_3 + 4) * 0x10 + *(int *)(param_3 + 0x10)) * 4
                      ) * 1000;
    }
    *param_4 = iVar2;
  }
  if (*(int *)(param_3 + 8) == 3) {
    if (0 < *(int *)(param_3 + 0x10)) {
      *param_4 = *(int *)(&DAT_00563bec +
                         (*(int *)(param_3 + 4) * 0x10 + *(int *)(param_3 + 0x10)) * 4) * 1000;
      return iVar1;
    }
    *param_4 = (*(int *)(&DAT_00563bcc + (*(int *)(param_3 + 0x14) + *(int *)(param_3 + 4) * 4) * 4)
                * iVar1 * 1000) / 0x3c0;
  }
  return iVar1;
}

