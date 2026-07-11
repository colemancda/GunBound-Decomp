/* FUN_00402e60 - 0x00402e60 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00402e60(int param_1,undefined4 param_2)

{
  undefined2 *puVar1;
  char cVar2;
  char *in_EAX;
  char *pcVar3;
  int iVar4;
  int iVar5;
  undefined1 local_38;
  char local_37 [23];
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  cVar2 = FUN_00426030(&local_20);
  puVar1 = DAT_007934f4;
  if (cVar2 == '\x01') {
    if (DAT_007934f4 == (undefined2 *)0x0) {
      if (*(int **)(param_1 + 0x1bdc) != (int *)0x0) {
        (**(code **)(**(int **)(param_1 + 0x1bdc) + 0x24))(&local_20,param_2);
      }
    }
    else {
      *(undefined4 *)(DAT_007934f4 + 0x1000) = 4;
      puVar1[1] = 0xa251;
      *(undefined4 *)(puVar1 + 2) = local_20;
      *(undefined4 *)(puVar1 + 4) = local_1c;
      *(undefined4 *)(puVar1 + 6) = local_18;
      *(undefined4 *)(puVar1 + 8) = local_14;
      iVar5 = *(int *)(puVar1 + 0x1000);
      *(int *)(puVar1 + 0x1000) = iVar5 + 0x10;
      *(bool *)(iVar5 + 0x10 + (int)puVar1) = (char)param_2 != '\0';
      iVar5 = *(int *)(puVar1 + 0x1000) + 1;
      *(int *)(puVar1 + 0x1000) = iVar5;
      *puVar1 = (short)iVar5;
      FUN_004e5ac0(*(undefined4 *)(puVar1 + 0x1002),iVar5);
    }
  }
  else {
    local_38 = 0x6e;
    pcVar3 = in_EAX;
    do {
      cVar2 = *pcVar3;
      pcVar3[(int)(local_37 + -(int)in_EAX)] = cVar2;
      pcVar3 = pcVar3 + 1;
    } while (cVar2 != '\0');
    iVar4 = FUN_00404b00(&local_38);
    iVar5 = DAT_007934e8;
    if (iVar4 == 0) {
      *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
      *(undefined2 *)(iVar5 + 0x4d4) = 0x1020;
      *(undefined4 *)(iVar5 + 0x4d6) = *(undefined4 *)in_EAX;
      *(undefined4 *)(iVar5 + 0x4da) = *(undefined4 *)(in_EAX + 4);
      *(undefined4 *)(iVar5 + 0x4de) = *(undefined4 *)(in_EAX + 8);
      iVar4 = *(int *)(iVar5 + 0x44d0);
      *(int *)(iVar5 + 0x44d0) = iVar4 + 0xc;
      *(undefined1 *)(iVar4 + 0x4dc + iVar5) = 0;
      *(int *)(iVar5 + 0x44d0) = *(int *)(iVar5 + 0x44d0) + 1;
      FUN_004d25e0();
      SendOutgoingPacket();
    }
    FUN_004026a0(((char)param_2 != '\x01') + 0x2002,&DAT_0054b460,0);
  }
  if ((char)param_2 == '\x01') {
    FUN_00404700(param_1);
  }
  return;
}

