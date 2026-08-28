/* SendJoinRoomSelected - 0x00429fd0 in the original binary.
 *
 * Sends a "join room" request (opcode 0x2110) for the room currently
 * selected in the room list. The room-number field (+0x4d6) is looked up
 * from the client's room-id table (g_clientContext + 0x44664 + sel*4) using
 * the selected list entry (in_EAX+4); the u32 payload (+0x4d2) is copied
 * from the selected list node's field +0x50. Wire layout is fixed 8 bytes:
 *   [u16 opcode=0x2110][u16 roomNumber][u32 payload]
 *
 * Raw/near-verbatim port of Ghidra's decompiler output. Calls to unnamed
 * FUN_<address> helpers and DAT_<address> globals are left as-is - this
 * file won't link standalone yet. See src/README.md's "Raw/verbatim ports"
 * section for status. *
 * DROPPED-REG FIX (2026-08-28): EAX is the room-list state object the
 * body indexes throughout - +4 is the selected room's index into the
 * room-id table at g_clientContext+0x44664, and +0x8f the outgoing
 * payload field. It is read before written.
 *
 * All 2 call sites pass the caller's own `this`. In
 * State03_GameRoomList_OnCommand that is EDI (`mov edi,ecx` at 0x4285ca,
 * its only write to EDI inside the function apart from the
 * 0x428aaf block, which returns before reaching any of these calls); in
 * State03_GameRoomList_ProcessPacket it is EBX (`mov ebx,ecx` at
 * 0x426afc - the earlier EBX writes a disassembly sweep turns up at
 * 0x426912 and 0x426989 lie BELOW that function's 0x426ad0 entry and
 * belong to its neighbour).
 */
#include "ghidra_types.h"


void SendJoinRoomSelected(int regEax)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int in_EAX = regEax;
  char *pcVar5;
  char *pcVar6;
  
  puVar3 = DAT_00e53c44;
  do {
    if (puVar3 == (undefined4 *)0x0) goto LAB_0042a00d;
    iVar2 = puVar3[2];
    puVar3 = (undefined4 *)*puVar3;
  } while ((*(int *)(iVar2 + 0x20) != 0) || (*(int *)(iVar2 + 0x24) != 2));
  pcVar5 = *(char **)(iVar2 + 0x50);
  pcVar6 = (char *)(in_EAX + 0x8f);
  do {
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    *pcVar6 = cVar1;
    pcVar6 = pcVar6 + 1;
  } while (cVar1 != '\0');
LAB_0042a00d:
  RefreshGameRoomListControls(0,(int)g_gameStateVTableArray[3]);
  iVar4 = g_connectionContextA;
  iVar2 = g_clientContext;
  *(undefined4 *)(g_connectionContextA + 0x44d0) = 6;
  *(undefined2 *)(iVar4 + 0x4d4) = 0x2110;
  *(undefined2 *)(iVar4 + 0x4d6) = *(undefined2 *)(iVar2 + 0x44664 + *(int *)(in_EAX + 4) * 4);
  iVar2 = *(int *)(iVar4 + 0x44d0);
  *(int *)(iVar4 + 0x44d0) = iVar2 + 2;
  *(undefined4 *)(iVar2 + 0x4d2 + iVar4) = *(undefined4 *)(in_EAX + 0x8f);
  *(int *)(iVar4 + 0x44d0) = *(int *)(iVar4 + 0x44d0) + 4;
  SendOutgoingPacket(iVar4);
  PanelManager_Unregister(&g_uiPanelManager,0,2);
  return;
}

