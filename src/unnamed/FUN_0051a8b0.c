/* FUN_0051a8b0 - 0x0051a8b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0051a8b0(float *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  float *pfVar3;
  float *pfVar4;
  float *pfVar5;
  int iVar6;
  float local_80 [16];
  float local_40 [16];
  
  local_80[0] = *param_1;
  local_80[8] = DAT_00f25a80 * *param_1;
  iVar6 = 0;
  pfVar3 = param_1 + 0x1c;
  do {
    param_1 = param_1 + 2;
    iVar1 = iVar6 + 4;
    *(float *)((int)local_80 + iVar6 + 4) = *param_1 + *pfVar3;
    *(float *)((int)local_80 + iVar6 + 0x24) =
         (*param_1 - *pfVar3) * *(float *)((int)&DAT_00f25a84 + iVar6);
    iVar6 = iVar1;
    pfVar3 = pfVar3 + -2;
  } while (iVar1 < 0x1c);
  iVar6 = 0;
  iVar1 = 2;
  do {
    iVar2 = iVar6;
    pfVar3 = (float *)((int)local_80 + iVar6 + 0x1c);
    pfVar5 = (float *)&DAT_00f25aa0;
    do {
      pfVar4 = pfVar5 + 1;
      *(float *)((int)local_40 + iVar2) = *pfVar3 + *(float *)((int)local_80 + iVar2);
      *(float *)((int)local_40 + iVar2 + 0x10) =
           (*(float *)((int)local_80 + iVar2) - *pfVar3) * *pfVar5;
      iVar2 = iVar2 + 4;
      pfVar3 = pfVar3 + -1;
      pfVar5 = pfVar4;
    } while ((int)pfVar4 < 0xf25ab0);
    iVar6 = iVar6 + 0x20;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  iVar6 = 0;
  iVar1 = 4;
  do {
    iVar2 = iVar6;
    pfVar3 = (float *)((int)local_40 + iVar6 + 0xc);
    pfVar5 = (float *)&DAT_00f25ab0;
    do {
      pfVar4 = pfVar5 + 1;
      *(float *)((int)local_80 + iVar2) = *(float *)((int)local_40 + iVar2) + *pfVar3;
      *(float *)((int)local_80 + iVar2 + 8) =
           (*(float *)((int)local_40 + iVar2) - *pfVar3) * *pfVar5;
      iVar2 = iVar2 + 4;
      pfVar3 = pfVar3 + -1;
      pfVar5 = pfVar4;
    } while ((int)pfVar4 < 0xf25ab8);
    iVar6 = iVar6 + 0x10;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  iVar1 = 8;
  iVar6 = 0;
  do {
    iVar1 = iVar1 + -1;
    *(float *)((int)local_40 + iVar6) =
         *(float *)((int)local_80 + iVar6) + *(float *)((int)local_80 + iVar6 + 4);
    *(float *)((int)local_40 + iVar6 + 4) =
         (*(float *)((int)local_80 + iVar6) - *(float *)((int)local_80 + iVar6 + 4)) * _DAT_00f25ab8
    ;
    iVar6 = iVar6 + 8;
  } while (iVar1 != 0);
  FUN_0051a650(4,4,local_40,local_80);
  FUN_0051a650(2,8,local_80,local_40);
  FUN_0051a650(1,0x10,local_40,param_2);
  return;
}

