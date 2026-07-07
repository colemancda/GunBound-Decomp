/* FUN_0051aa00 - 0x0051aa00 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0051aa00(float *param_1,undefined4 param_2)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  float *pfVar5;
  float *pfVar6;
  float *pfVar7;
  int iVar8;
  float local_80 [16];
  float local_40 [16];
  
  local_80[0] = (param_1[1] + *param_1) * _DAT_00544b00;
  local_80[8] = DAT_00f25a80 * local_80[0];
  iVar8 = 0;
  pfVar5 = param_1 + 0x1c;
  do {
    iVar3 = iVar8 + 4;
    fVar1 = (param_1[3] + param_1[2]) * _DAT_00544b00;
    fVar2 = (pfVar5[1] + *pfVar5) * _DAT_00544b00;
    *(float *)((int)local_80 + iVar8 + 4) = fVar2 + fVar1;
    *(float *)((int)local_80 + iVar8 + 0x24) =
         (fVar1 - fVar2) * *(float *)((int)&DAT_00f25a84 + iVar8);
    iVar8 = iVar3;
    pfVar5 = pfVar5 + -2;
    param_1 = param_1 + 2;
  } while (iVar3 < 0x1c);
  iVar8 = 0;
  iVar3 = 2;
  do {
    iVar4 = iVar8;
    pfVar5 = (float *)((int)local_80 + iVar8 + 0x1c);
    pfVar7 = (float *)&DAT_00f25aa0;
    do {
      pfVar6 = pfVar7 + 1;
      *(float *)((int)local_40 + iVar4) = *pfVar5 + *(float *)((int)local_80 + iVar4);
      *(float *)((int)local_40 + iVar4 + 0x10) =
           (*(float *)((int)local_80 + iVar4) - *pfVar5) * *pfVar7;
      iVar4 = iVar4 + 4;
      pfVar5 = pfVar5 + -1;
      pfVar7 = pfVar6;
    } while ((int)pfVar6 < 0xf25ab0);
    iVar8 = iVar8 + 0x20;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar8 = 0;
  iVar3 = 4;
  do {
    iVar4 = iVar8;
    pfVar5 = (float *)((int)local_40 + iVar8 + 0xc);
    pfVar7 = (float *)&DAT_00f25ab0;
    do {
      pfVar6 = pfVar7 + 1;
      *(float *)((int)local_80 + iVar4) = *(float *)((int)local_40 + iVar4) + *pfVar5;
      *(float *)((int)local_80 + iVar4 + 8) =
           (*(float *)((int)local_40 + iVar4) - *pfVar5) * *pfVar7;
      iVar4 = iVar4 + 4;
      pfVar5 = pfVar5 + -1;
      pfVar7 = pfVar6;
    } while ((int)pfVar6 < 0xf25ab8);
    iVar8 = iVar8 + 0x10;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar3 = 8;
  iVar8 = 0;
  do {
    iVar3 = iVar3 + -1;
    *(float *)((int)local_40 + iVar8) =
         *(float *)((int)local_80 + iVar8) + *(float *)((int)local_80 + iVar8 + 4);
    *(float *)((int)local_40 + iVar8 + 4) =
         (*(float *)((int)local_80 + iVar8) - *(float *)((int)local_80 + iVar8 + 4)) * _DAT_00f25ab8
    ;
    iVar8 = iVar8 + 8;
  } while (iVar3 != 0);
  FUN_0051a650(4,4,local_40,local_80);
  FUN_0051a650(2,8,local_80,local_40);
  FUN_0051a650(1,0x10,local_40,param_2);
  return;
}

