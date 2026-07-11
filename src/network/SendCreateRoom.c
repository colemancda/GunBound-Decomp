/* SendCreateRoom - 0x00429c60 in the original binary.
 *
 * Create Room dialog submit handler: copies the room-name and password text fields and sends outgoing opcode 0x2120. See PROTOCOL.md. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void SendCreateRoom(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  char *pcVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  char *pcVar9;
  
  FUN_0042a090();
  puVar3 = DAT_00e53c44;
  do {
    if (puVar3 == (undefined4 *)0x0) goto LAB_00429cbe;
    iVar2 = puVar3[2];
    puVar3 = (undefined4 *)*puVar3;
  } while ((*(int *)(iVar2 + 0x20) != 0) || (*(int *)(iVar2 + 0x24) != 0));
  pcVar4 = *(char **)(iVar2 + 0x50);
  pcVar9 = (char *)(param_1 + 0xf);
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    *pcVar9 = cVar1;
    pcVar9 = pcVar9 + 1;
  } while (cVar1 != '\0');
  pcVar4 = *(char **)(iVar2 + 0x54);
  pcVar9 = (char *)(param_1 + 0x8f);
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    *pcVar9 = cVar1;
    pcVar9 = pcVar9 + 1;
  } while (cVar1 != '\0');
LAB_00429cbe:
  iVar2 = DAT_007934e8;
  pcVar9 = (char *)(param_1 + 0xf);
  *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x2120;
  *(undefined4 *)(iVar2 + 0x44d0) = 6;
  pcVar4 = pcVar9;
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  *(char *)(iVar2 + 0x4d6) = (char)pcVar4 - ((char)param_1 + '\x10');
  iVar8 = *(int *)(iVar2 + 0x44d0);
  *(int *)(iVar2 + 0x44d0) = iVar8 + 1;
  pcVar4 = pcVar9;
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  uVar5 = (int)pcVar4 - (param_1 + 0x10);
  uVar6 = ((int)uVar5 < 0) - 1 & uVar5;
  pcVar4 = (char *)(iVar8 + 0x4d1 + iVar2);
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar4 = *(undefined4 *)pcVar9;
    pcVar9 = pcVar9 + 4;
    pcVar4 = pcVar4 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar4 = *pcVar9;
    pcVar9 = pcVar9 + 1;
    pcVar4 = pcVar4 + 1;
  }
  iVar8 = *(int *)(iVar2 + 0x44d0) + uVar5;
  *(int *)(iVar2 + 0x44d0) = iVar8;
  *(undefined4 *)(iVar8 + 0x4d0 + iVar2) = *(undefined4 *)(param_1 + 0x110);
  iVar8 = *(int *)(iVar2 + 0x44d0);
  *(int *)(iVar2 + 0x44d0) = iVar8 + 4;
  *(undefined4 *)(iVar8 + 0x4d4 + iVar2) = *(undefined4 *)(param_1 + 0x8f);
  iVar8 = *(int *)(iVar2 + 0x44d0);
  *(int *)(iVar2 + 0x44d0) = iVar8 + 4;
  *(undefined1 *)(iVar8 + 0x4d4 + iVar2) = *(undefined1 *)(param_1 + 0x114);
  *(int *)(iVar2 + 0x44d0) = *(int *)(iVar2 + 0x44d0) + 1;
  SendOutgoingPacket();
  PanelManager_Unregister(&g_uiPanelManager);
  return;
}

