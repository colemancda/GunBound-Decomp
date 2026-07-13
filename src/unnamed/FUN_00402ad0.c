/* FUN_00402ad0 - 0x00402ad0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00402ad0(int param_1,char *param_2)

{
  undefined2 *puVar1;
  char cVar2;
  char *in_EAX;
  undefined4 *puVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  undefined4 local_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined1 uStack_a8;
  undefined2 local_a7;
  undefined1 local_a5;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  char acStack_8c [140];
  
  cVar2 = FUN_00426030(&local_a0);
  puVar1 = DAT_007934f4;
  if (cVar2 == '\x01') {
    if (DAT_007934f4 != (undefined2 *)0x0) {
      uStack_b4 = 0;
      uStack_b0 = 0;
      *(undefined4 *)(DAT_007934f4 + 0x1000) = 4;
      uStack_ac = 0;
      uStack_a8 = 0;
      local_a7 = 0;
      puVar1[1] = 0xa200;
      local_a5 = 0;
      *(undefined4 *)(puVar1 + 2) = local_a0;
      *(undefined4 *)(puVar1 + 4) = local_9c;
      *(undefined4 *)(puVar1 + 6) = local_98;
      *(undefined4 *)(puVar1 + 8) = local_94;
      iVar6 = *(int *)(puVar1 + 0x1000);
      *(int *)(puVar1 + 0x1000) = iVar6 + 0x10;
      puVar3 = (undefined4 *)(iVar6 + 0x10 + (int)puVar1);
      local_b8 = 0;
      *puVar3 = 0;
      puVar3[1] = 0;
      puVar3[2] = 0;
      puVar3[3] = 0;
      puVar3[4] = 0;
      iVar6 = *(int *)(puVar1 + 0x1000) + 0x14;
      *(int *)(puVar1 + 0x1000) = iVar6;
      *puVar1 = (short)iVar6;
      SendSocketData(*(undefined4 *)(puVar1 + 0x1002),iVar6);
      return;
    }
    if (*(int **)(param_1 + 0x1bdc) != (int *)0x0) {
      (**(code **)(**(int **)(param_1 + 0x1bdc) + 0x20))(&local_a0,g_clientContext + 0x23313,param_2);
      pcVar4 = (char *)GetLocalizedString(&g_localizedStringTable,0xfa6);
      _sprintf(acStack_8c,pcVar4);
      BuildItemTooltipPanel(&g_uiPanelManager,acStack_8c);
      return;
    }
  }
  else {
    local_b8 = 0x6e;
    pcVar4 = in_EAX;
    do {
      cVar2 = *pcVar4;
      pcVar4[(int)&local_b8 + (1 - (int)in_EAX)] = cVar2;
      pcVar4 = pcVar4 + 1;
    } while (cVar2 != '\0');
    iVar5 = FUN_00404b00(&local_b8);
    iVar6 = DAT_007934e8;
    if (iVar5 == 0) {
      *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
      *(undefined2 *)(iVar6 + 0x4d4) = 0x1020;
      *(undefined4 *)(iVar6 + 0x4d6) = *(undefined4 *)in_EAX;
      *(undefined4 *)(iVar6 + 0x4da) = *(undefined4 *)(in_EAX + 4);
      *(undefined4 *)(iVar6 + 0x4de) = *(undefined4 *)(in_EAX + 8);
      iVar5 = *(int *)(iVar6 + 0x44d0);
      *(int *)(iVar6 + 0x44d0) = iVar5 + 0xc;
      *(undefined1 *)(iVar5 + 0x4dc + iVar6) = 0;
      *(int *)(iVar6 + 0x44d0) = *(int *)(iVar6 + 0x44d0) + 1;
      EncodePacketBody(0,iVar6);
      SendOutgoingPacket(iVar6);
    }
    pcVar4 = param_2;
    do {
      cVar2 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar2 != '\0');
    FUN_004026a0(1,param_2,pcVar4 + (1 - (int)(param_2 + 1)));
  }
  return;
}

