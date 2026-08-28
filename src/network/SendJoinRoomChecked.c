/* SendJoinRoomChecked - 0x00429b50 in the original binary.
 *
 * Sends a "join room" request (opcode 0x2110) for the selected room, but
 * first scans the client's room list for an entry matching (myUserId,
 * roomId) and returns early if the client is already in that room. If a
 * per-room flag (+0x449ae) is clear it emits the fixed 8-byte 0x2110 packet
 * (room number from the room-id table, u32 payload from _DAT_00551cb1);
 * otherwise it routes to FUN_00508910 (an "already joined"/error path):
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


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void SendJoinRoomChecked(int regEax)

{
  int iVar1;
  int in_EAX = regEax;
  int *piVar2;
  int iVar3;
  
  iVar3 = 0;
  if (0 < *(int *)(&DAT_005f3258 + g_clientContext)) {
    piVar2 = (int *)(&DAT_005f3058 + g_clientContext);
    do {
      if ((piVar2[-0x40] == *(int *)(g_clientContext + 0x3f804)) &&
         (*piVar2 == *(int *)(g_clientContext + 0x44664 + *(int *)(in_EAX + 4) * 4))) {
        return;
      }
      iVar3 = iVar3 + 1;
      piVar2 = piVar2 + 1;
    } while (iVar3 < *(int *)(&DAT_005f3258 + g_clientContext));
  }
  if (*(char *)(*(int *)(in_EAX + 4) + 0x449ae + g_clientContext) == '\0') {
    RefreshGameRoomListControls(0,(int)g_gameStateVTableArray[3]);
    iVar1 = g_connectionContextA;
    iVar3 = g_clientContext;
    *(undefined4 *)(g_connectionContextA + 0x44d0) = 6;
    *(undefined2 *)(iVar1 + 0x4d4) = 0x2110;
    *(undefined2 *)(iVar1 + 0x4d6) = *(undefined2 *)(iVar3 + 0x44664 + *(int *)(in_EAX + 4) * 4);
    iVar3 = *(int *)(iVar1 + 0x44d0);
    *(int *)(iVar1 + 0x44d0) = iVar3 + 2;
    *(undefined4 *)(iVar3 + 0x4d2 + iVar1) = _DAT_00551cb1;
    *(int *)(iVar1 + 0x44d0) = *(int *)(iVar1 + 0x44d0) + 4;
    *(undefined1 *)(in_EAX + 0x8f) = 0;
    SendOutgoingPacket(iVar1);
    return;
  }
  FUN_00508910((int)&g_uiPanelManager);
  return;
}

