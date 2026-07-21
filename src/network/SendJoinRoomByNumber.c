/* SendJoinRoomByNumber - 0x00429de0 in the original binary.
 *
 * Sends a "join room" request (opcode 0x2110) for a room number the user
 * typed into a text field. The number string is parsed with _atol and
 * clamped to 1..1000 (local_84), then divided by 6 for the slot index. This
 * is preceded by a 0x2100 packet (the same fixed 8-byte 0x2110 layout as
 * SendJoinRoomSelected follows):
 *   [u16 opcode=0x2110][u16 roomNumber][u32 payload]
 * The u32 payload (+0x4d2) is copied from the node field +0x54 via +0x8f.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output. Calls to unnamed
 * FUN_<address> helpers and DAT_<address> globals are left as-is - this
 * file won't link standalone yet. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void SendJoinRoomByNumber(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  long lVar5;
  char *pcVar6;
  char *pcVar7;
  int local_84;
  char local_80 [128];
  
  puVar3 = DAT_00e53c44;
  do {
    if (puVar3 == (undefined4 *)0x0) goto LAB_00429e3e;
    iVar2 = puVar3[2];
    puVar3 = (undefined4 *)*puVar3;
  } while ((*(int *)(iVar2 + 0x20) != 0) || (*(int *)(iVar2 + 0x24) != 1));
  pcVar6 = *(char **)(iVar2 + 0x50);
  pcVar7 = local_80;
  do {
    cVar1 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    *pcVar7 = cVar1;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  pcVar6 = *(char **)(iVar2 + 0x54);
  pcVar7 = (char *)(param_1 + 0x8f);
  do {
    cVar1 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    *pcVar7 = cVar1;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
LAB_00429e3e:
  lVar5 = _atol(local_80);
  if ((lVar5 + -1 < 1000) && (lVar5 = _atol(local_80), lVar5 + -1 < 0)) {
    local_84 = 0;
  }
  else {
    lVar5 = _atol(local_80);
    if (lVar5 + -1 < 1000) {
      lVar5 = _atol(local_80);
      local_84 = lVar5 + -1;
    }
    else {
      local_84 = 1000;
    }
  }
  RefreshGameRoomListControls(0,(int)g_gameStateVTableArray[3]);
  iVar4 = DAT_007934e8;
  *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
  *(undefined2 *)(iVar4 + 0x4d4) = 0x2100;
  *(undefined1 *)(iVar4 + 0x4d6) = 1;
  iVar2 = *(int *)(iVar4 + 0x44d0);
  *(int *)(iVar4 + 0x44d0) = iVar2 + 1;
  *(undefined1 *)(iVar2 + 0x4d1 + iVar4) = 0;
  iVar2 = *(int *)(iVar4 + 0x44d0);
  *(int *)(iVar4 + 0x44d0) = iVar2 + 1;
  *(short *)(iVar2 + 0x4d1 + iVar4) = (short)(local_84 / 6);
  *(int *)(iVar4 + 0x44d0) = *(int *)(iVar4 + 0x44d0) + 2;
  SendOutgoingPacket(iVar4);
  iVar4 = DAT_007934e8;
  *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
  *(undefined2 *)(iVar4 + 0x4d4) = 0x2110;
  *(short *)(iVar4 + 0x4d6) = (short)local_84;
  iVar2 = *(int *)(iVar4 + 0x44d0);
  *(int *)(iVar4 + 0x44d0) = iVar2 + 2;
  *(undefined4 *)(iVar2 + 0x4d2 + iVar4) = *(undefined4 *)(param_1 + 0x8f);
  *(int *)(iVar4 + 0x44d0) = *(int *)(iVar4 + 0x44d0) + 4;
  SendOutgoingPacket(iVar4);
  *(undefined1 *)(param_1 + 0x115) = 1;
  *(undefined1 *)(param_1 + 0x116) = 0;
  *(int *)(param_1 + 0x11c) = local_84 / 6;
  PanelManager_Unregister(&g_uiPanelManager);
  return;
}

