/* FUN_0051ab80 - 0x0051ab80 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0051ab80(float *param_1,undefined4 param_2)

{
  float *pfVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  float *pfVar5;
  int iVar6;
  float local_40 [8];
  float local_20 [8];
  
  local_40[0] = *param_1 + param_1[7];
  iVar4 = 3;
  local_40[4] = (*param_1 - param_1[7]) * DAT_00f25aa0;
  pfVar1 = param_1 + 1;
  pfVar5 = param_1 + 6;
  do {
    pfVar2 = pfVar1 + 1;
    iVar4 = iVar4 + -1;
    *(float *)((int)local_40 + (-4 - (int)param_1) + (int)pfVar2) = *pfVar5 + *pfVar1;
    *(float *)((int)local_40 + (0xc - (int)param_1) + (int)pfVar2) =
         (*pfVar1 - *pfVar5) * *(float *)(((int)&DAT_00f25a9c - (int)param_1) + (int)pfVar2);
    pfVar1 = pfVar2;
    pfVar5 = pfVar5 + -1;
  } while (iVar4 != 0);
  iVar4 = 0;
  iVar6 = 2;
  do {
    iVar3 = iVar4;
    pfVar1 = (float *)((int)local_40 + iVar4 + 0xc);
    pfVar5 = (float *)&DAT_00f25ab0;
    do {
      pfVar2 = pfVar5 + 1;
      *(float *)((int)local_20 + iVar3) = *pfVar1 + *(float *)((int)local_40 + iVar3);
      *(float *)((int)local_20 + iVar3 + 8) =
           (*(float *)((int)local_40 + iVar3) - *pfVar1) * *pfVar5;
      iVar3 = iVar3 + 4;
      pfVar1 = pfVar1 + -1;
      pfVar5 = pfVar2;
    } while ((int)pfVar2 < 0xf25ab8);
    iVar4 = iVar4 + 0x10;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  iVar6 = 4;
  iVar4 = 0;
  do {
    iVar6 = iVar6 + -1;
    *(float *)((int)local_40 + iVar4) =
         *(float *)((int)local_20 + iVar4 + 4) + *(float *)((int)local_20 + iVar4);
    *(float *)((int)local_40 + iVar4 + 4) =
         (*(float *)((int)local_20 + iVar4) - *(float *)((int)local_20 + iVar4 + 4)) * _DAT_00f25ab8
    ;
    iVar4 = iVar4 + 8;
  } while (iVar6 != 0);
  FUN_0051a650(2,4,local_40,local_20);
  FUN_0051a650(1,8,local_20,param_2);
  return;
}

