/* FUN_00403ae0 - 0x00403ae0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_00403ae0(int param_1,char *param_2)

{
  undefined4 *puVar1;
  char cVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  undefined *puVar6;
  byte bVar7;
  undefined1 local_38;
  char local_37 [23];
  undefined1 local_20 [32];
  
  cVar2 = FUN_00426090(local_20);
  if (cVar2 == '\x01') {
    iVar3 = FUN_00401bb0(param_1 + -8);
    if ((iVar3 != 0) &&
       (bVar7 = (param_2[0x12] == '\0') - 1U & 0x12, *(byte *)(iVar3 + 0x30) = bVar7, bVar7 == 0x12)
       ) {
      FUN_00404700(param_1 + -8);
      return;
    }
  }
  else {
    local_38 = 0x69;
    pcVar4 = param_2;
    do {
      cVar2 = *pcVar4;
      pcVar4[(int)(local_37 + -(int)param_2)] = cVar2;
      pcVar4 = pcVar4 + 1;
    } while (cVar2 != '\0');
    iVar5 = FUN_00404b00(&local_38);
    iVar3 = DAT_007934e8;
    if (iVar5 == 0) {
      *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
      *(undefined2 *)(iVar3 + 0x4d4) = 0x1022;
      *(undefined2 *)(iVar3 + 0x4d6) = 1;
      iVar5 = *(int *)(iVar3 + 0x44d0);
      *(int *)(iVar3 + 0x44d0) = iVar5 + 2;
      puVar1 = (undefined4 *)(iVar5 + 0x4d2 + iVar3);
      *puVar1 = *(undefined4 *)param_2;
      puVar1[1] = *(undefined4 *)(param_2 + 4);
      puVar1[2] = *(undefined4 *)(param_2 + 8);
      puVar1[3] = *(undefined4 *)(param_2 + 0xc);
      *(int *)(iVar3 + 0x44d0) = *(int *)(iVar3 + 0x44d0) + 0x10;
      FUN_004d2680();
    }
    puVar6 = &DAT_00551e30;
    if (param_2[0x12] == '\0') {
      puVar6 = &DAT_00551e2c;
    }
    FUN_004026a0(0x1004,puVar6,1);
  }
  return;
}

