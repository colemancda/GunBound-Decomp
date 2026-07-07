/* FUN_0051ad70 - 0x0051ad70 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0051ad70(float *param_1,undefined4 param_2)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  float *pfVar5;
  float *pfVar6;
  float *pfVar7;
  int iVar8;
  float local_40 [16];
  
  fVar1 = (param_1[1] + *param_1) * _DAT_00544b00;
  fVar2 = (param_1[0xf] + param_1[0xe]) * _DAT_00544b00;
  local_40[0] = fVar2 + fVar1;
  local_40[4] = (fVar1 - fVar2) * DAT_00f25aa0;
  iVar8 = 0;
  pfVar5 = param_1 + 0xc;
  do {
    iVar3 = iVar8 + 4;
    fVar1 = (param_1[3] + param_1[2]) * _DAT_00544b00;
    fVar2 = (pfVar5[1] + *pfVar5) * _DAT_00544b00;
    *(float *)((int)local_40 + iVar8 + 4) = fVar2 + fVar1;
    *(float *)((int)local_40 + iVar8 + 0x14) =
         (fVar1 - fVar2) * *(float *)((int)&DAT_00f25aa4 + iVar8);
    iVar8 = iVar3;
    pfVar5 = pfVar5 + -2;
    param_1 = param_1 + 2;
  } while (iVar3 < 0xc);
  iVar8 = 0;
  iVar3 = 2;
  do {
    iVar4 = iVar8;
    pfVar5 = (float *)((int)local_40 + iVar8 + 0xc);
    pfVar6 = (float *)&DAT_00f25ab0;
    do {
      pfVar7 = pfVar6 + 1;
      *(float *)((int)local_40 + iVar4 + 0x20) = *(float *)((int)local_40 + iVar4) + *pfVar5;
      *(float *)((int)local_40 + iVar4 + 0x28) =
           (*(float *)((int)local_40 + iVar4) - *pfVar5) * *pfVar6;
      iVar4 = iVar4 + 4;
      pfVar5 = pfVar5 + -1;
      pfVar6 = pfVar7;
    } while ((int)pfVar7 < 0xf25ab8);
    iVar8 = iVar8 + 0x10;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar3 = 4;
  iVar8 = 0;
  do {
    iVar3 = iVar3 + -1;
    *(float *)((int)local_40 + iVar8) =
         *(float *)((int)local_40 + iVar8 + 0x20) + *(float *)((int)local_40 + iVar8 + 0x24);
    *(float *)((int)local_40 + iVar8 + 4) =
         (*(float *)((int)local_40 + iVar8 + 0x20) - *(float *)((int)local_40 + iVar8 + 0x24)) *
         _DAT_00f25ab8;
    iVar8 = iVar8 + 8;
  } while (iVar3 != 0);
  FUN_0051a650(2,4,local_40,local_40 + 8);
  FUN_0051a650(1,8,local_40 + 8,param_2);
  return;
}

