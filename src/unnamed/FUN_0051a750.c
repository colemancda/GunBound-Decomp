/* FUN_0051a750 - 0x0051a750 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0051a750(float *param_1,undefined4 param_2)

{
  float *pfVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  float *pfVar5;
  int iVar6;
  float local_80 [7];
  float local_64 [9];
  float local_40 [16];
  
  local_64[1] = DAT_00f25a80 * *param_1;
  local_80[0] = *param_1;
  iVar4 = 7;
  pfVar1 = param_1 + 1;
  pfVar5 = param_1 + 0xe;
  do {
    pfVar2 = pfVar1 + 1;
    iVar4 = iVar4 + -1;
    *(float *)((int)local_64 + (-0x20 - (int)param_1) + (int)pfVar2) = *pfVar1 + *pfVar5;
    *(float *)(((int)local_64 - (int)param_1) + (int)pfVar2) =
         (*pfVar1 - *pfVar5) * *(float *)(((int)&DAT_00f25a7c - (int)param_1) + (int)pfVar2);
    pfVar1 = pfVar2;
    pfVar5 = pfVar5 + -1;
  } while (iVar4 != 0);
  iVar4 = 0;
  iVar6 = 2;
  do {
    iVar3 = iVar4;
    pfVar1 = (float *)((int)local_64 + iVar4);
    pfVar5 = (float *)&DAT_00f25aa0;
    do {
      pfVar2 = pfVar5 + 1;
      *(float *)((int)local_40 + iVar3) = *pfVar1 + *(float *)((int)local_80 + iVar3);
      *(float *)((int)local_40 + iVar3 + 0x10) =
           (*(float *)((int)local_80 + iVar3) - *pfVar1) * *pfVar5;
      iVar3 = iVar3 + 4;
      pfVar1 = pfVar1 + -1;
      pfVar5 = pfVar2;
    } while ((int)pfVar2 < 0xf25ab0);
    iVar4 = iVar4 + 0x20;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  iVar4 = 0;
  iVar6 = 4;
  do {
    iVar3 = iVar4;
    pfVar1 = (float *)((int)local_40 + iVar4 + 0xc);
    pfVar5 = (float *)&DAT_00f25ab0;
    do {
      pfVar2 = pfVar5 + 1;
      *(float *)((int)local_80 + iVar3) = *pfVar1 + *(float *)((int)local_40 + iVar3);
      *(float *)((int)local_80 + iVar3 + 8) =
           (*(float *)((int)local_40 + iVar3) - *pfVar1) * *pfVar5;
      iVar3 = iVar3 + 4;
      pfVar1 = pfVar1 + -1;
      pfVar5 = pfVar2;
    } while ((int)pfVar2 < 0xf25ab8);
    iVar4 = iVar4 + 0x10;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  iVar6 = 8;
  iVar4 = 0;
  do {
    iVar6 = iVar6 + -1;
    *(float *)((int)local_40 + iVar4) =
         *(float *)((int)local_80 + iVar4 + 4) + *(float *)((int)local_80 + iVar4);
    *(float *)((int)local_40 + iVar4 + 4) =
         (*(float *)((int)local_80 + iVar4) - *(float *)((int)local_80 + iVar4 + 4)) * _DAT_00f25ab8
    ;
    iVar4 = iVar4 + 8;
  } while (iVar6 != 0);
  FUN_0051a650(4,4,local_40,local_80);
  FUN_0051a650(2,8,local_80,local_40);
  FUN_0051a650(1,0x10,local_40,param_2);
  return;
}

