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
 * section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void SendJoinRoomChecked(void)

{
  int iVar1;
  int in_EAX;
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
    iVar1 = DAT_007934e8;
    iVar3 = g_clientContext;
    *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
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
  FUN_00508910();
  return;
}

