/* FUN_00404330 - 0x00404330 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_00404330(int param_1,char *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  char cVar3;
  char *pcVar4;
  int iVar5;
  undefined1 local_38;
  char local_37 [23];
  undefined1 local_20 [32];
  
  cVar3 = FUN_00426090(local_20);
  if (cVar3 == '\x01') {
    FUN_00401ee0(param_1 + -8);
    return;
  }
  local_38 = 0x69;
  pcVar4 = param_2;
  do {
    cVar3 = *pcVar4;
    pcVar4[(int)(local_37 + -(int)param_2)] = cVar3;
    pcVar4 = pcVar4 + 1;
  } while (cVar3 != '\0');
  iVar5 = FUN_00404b00(&local_38);
  iVar2 = DAT_007934e8;
  if (iVar5 == 0) {
    *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
    *(undefined2 *)(iVar2 + 0x4d4) = 0x1022;
    *(undefined2 *)(iVar2 + 0x4d6) = 1;
    iVar5 = *(int *)(iVar2 + 0x44d0);
    *(int *)(iVar2 + 0x44d0) = iVar5 + 2;
    puVar1 = (undefined4 *)(iVar5 + 0x4d2 + iVar2);
    *puVar1 = *(undefined4 *)param_2;
    puVar1[1] = *(undefined4 *)(param_2 + 4);
    puVar1[2] = *(undefined4 *)(param_2 + 8);
    puVar1[3] = *(undefined4 *)(param_2 + 0xc);
    *(int *)(iVar2 + 0x44d0) = *(int *)(iVar2 + 0x44d0) + 0x10;
    SendOutgoingPacket(iVar2);
  }
  FUN_004026a0(0x1002,param_2,0);
  return;
}

