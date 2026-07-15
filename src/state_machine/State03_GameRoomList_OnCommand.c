/* State03_GameRoomList_OnCommand - 0x004285c0 in the original binary.
 *
 * The lobby command/action dispatcher (vtable slot 5): every button, menu item, and list event funnels here; eventType 0 dispatches on button id. See docs/screens/03_game_room_list.md for the full button map. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall State03_GameRoomList_OnCommand(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;

  iVar2 = DAT_007934e8;
  iVar4 = g_clientContext;
  if (param_2 != 0) {
    if (param_2 == 10) {
      if (*(char *)(param_1 + 0xc) != '\0') {
        SendCreateRoom(param_1);
      }
      if (*(char *)(param_1 + 0xd) != '\0') {
        SendJoinRoomSelected();
      }
      if (*(char *)(param_1 + 0xe) == '\0') {
        return;
      }
      SendJoinRoomByNumber(param_1);
      return;
    }
    if (param_2 != 0xb) {
      return;
    }
    if (*(char *)(param_1 + 0xd) != '\0') {
      PanelManager_Unregister(&g_uiPanelManager);
    }
    if (*(char *)(param_1 + 0xe) == '\0') {
      return;
    }
    PanelManager_Unregister(&g_uiPanelManager);
    return;
  }
  switch(param_4) {
  case 0:
    g_pendingGameState = 2;
    g_stateChangeRequested = 1;
    ChangeGameState(2);
    SetGuardedBool(0);
    *(undefined4 *)(param_1 + 0x11c) = 0;
    return;
  case 1:
    BuildBuddyPanel();
    return;
  case 2:
  case 6:
  case 7:
  case 8:
  case 9:
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x13:
  case 0x14:
  case 0x15:
  case 0x16:
  case 0x17:
  case 0x18:
  case 0x19:
  case 0x1a:
  case 0x1b:
  case 0x1c:
  case 0x1d:
  case 0x22:
  case 0x23:
  case 0x24:
  case 0x25:
  case 0x26:
  case 0x27:
    return;
  case 3:
    cVar3 = PacketChecksumEquals(g_clientContext + 0x449c4,2);
    if (cVar3 == '\0') {
      RefreshGameRoomListControls();
      iVar2 = DAT_007934e8;
      iVar4 = g_clientContext;
      *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
      *(undefined2 *)(iVar2 + 0x4d4) = 0x6000;
      *(bool *)(iVar2 + 0x4d6) = *(char *)(iVar4 + 0x44bf8) == '\0';
      *(int *)(iVar2 + 0x44d0) = *(int *)(iVar2 + 0x44d0) + 1;
      SendOutgoingPacket(iVar2);
      return;
    }
    FUN_00509780();
    return;
  case 4:
    OpenCreateRoomDialog();
    return;
  case 5:
    SendJoinRoomChecked();
    return;
  case 10:
    *(undefined1 *)(param_1 + 0x115) = 1;
    *(undefined1 *)(param_1 + 0x116) = 0;
    *(undefined4 *)(param_1 + 0x118) = 0;
    *(undefined4 *)(iVar2 + 0x44d0) = 6;
    *(undefined2 *)(iVar2 + 0x4d4) = 0x2100;
    *(undefined1 *)(iVar2 + 0x4d6) = *(undefined1 *)(param_1 + 0x115);
    iVar4 = *(int *)(iVar2 + 0x44d0);
    *(int *)(iVar2 + 0x44d0) = iVar4 + 1;
    *(undefined1 *)(iVar4 + 0x4d1 + iVar2) = *(undefined1 *)(param_1 + 0x116);
    *(int *)(iVar2 + 0x44d0) = *(int *)(iVar2 + 0x44d0) + 1;
    *(undefined4 *)(param_1 + 0x118) = 0;
    *(undefined4 *)(param_1 + 0x11c) = 0;
    *(undefined2 *)(*(int *)(iVar2 + 0x44d0) + 0x4d0 + iVar2) = 0;
    goto LAB_0042879e;
  case 0xb:
    *(undefined1 *)(param_1 + 0x116) = 0;
    *(undefined4 *)(param_1 + 0x118) = 0;
    *(undefined1 *)(param_1 + 0x115) = 2;
    *(undefined4 *)(iVar2 + 0x44d0) = 6;
    *(undefined2 *)(iVar2 + 0x4d4) = 0x2100;
    *(undefined1 *)(iVar2 + 0x4d6) = *(undefined1 *)(param_1 + 0x115);
    iVar4 = *(int *)(iVar2 + 0x44d0);
    *(int *)(iVar2 + 0x44d0) = iVar4 + 1;
    *(undefined1 *)(iVar4 + 0x4d1 + iVar2) = *(undefined1 *)(param_1 + 0x116);
    *(int *)(iVar2 + 0x44d0) = *(int *)(iVar2 + 0x44d0) + 1;
    *(undefined4 *)(param_1 + 0x118) = 0;
    *(undefined4 *)(param_1 + 0x11c) = 0;
    *(undefined2 *)(*(int *)(iVar2 + 0x44d0) + 0x4d0 + iVar2) = 0;
    *(int *)(iVar2 + 0x44d0) = *(int *)(iVar2 + 0x44d0) + 2;
    SendOutgoingPacket(iVar2);
    *(undefined4 *)(param_1 + 4) = 0xffffffff;
    RefreshGameRoomListControls();
    return;
  case 0xc:
    cVar3 = *(char *)(param_1 + 0x115);
    *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
    if (cVar3 == '\x06') {
      *(undefined2 *)(iVar2 + 0x4d4) = 0x2101;
      iVar4 = *(int *)(param_1 + 0x118) + -1;
      *(int *)(param_1 + 0x11c) = iVar4;
      iVar4 = iVar4 * 0xc;
      puVar1 = (undefined4 *)(*(int *)(iVar2 + 0x44d0) + 0x4d0 + iVar2);
      *puVar1 = *(undefined4 *)(g_serverSelectRecords + iVar4);
      puVar1[1] = *(undefined4 *)(g_serverSelectRecords + iVar4 + 4);
      puVar1[2] = *(undefined4 *)(g_serverSelectRecords + iVar4 + 8);
      iVar4 = *(int *)(iVar2 + 0x44d0) + 0xc;
    }
    else {
      *(undefined2 *)(iVar2 + 0x4d4) = 0x2100;
      *(undefined1 *)(iVar2 + 0x4d6) = *(undefined1 *)(param_1 + 0x115);
      iVar4 = *(int *)(iVar2 + 0x44d0);
      *(int *)(iVar2 + 0x44d0) = iVar4 + 1;
      *(undefined1 *)(iVar4 + 0x4d1 + iVar2) = *(undefined1 *)(param_1 + 0x116);
      *(int *)(iVar2 + 0x44d0) = *(int *)(iVar2 + 0x44d0) + 1;
      iVar4 = *(int *)(param_1 + 0x118) + -1;
      *(int *)(param_1 + 0x11c) = iVar4;
      *(short *)(*(int *)(iVar2 + 0x44d0) + 0x4d0 + iVar2) = (short)iVar4;
      iVar4 = *(int *)(iVar2 + 0x44d0) + 2;
    }
    *(int *)(iVar2 + 0x44d0) = iVar4;
    SendOutgoingPacket(iVar2);
    *(undefined4 *)(param_1 + 4) = 0xffffffff;
    RefreshGameRoomListControls();
    return;
  case 0xd:
    if (*(char *)(param_1 + 0x115) == '\x06') {
      *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x2101;
      *(undefined4 *)(iVar2 + 0x44d0) = 6;
      iVar4 = *(int *)(param_1 + 0x118) + 1;
      *(int *)(param_1 + 0x11c) = iVar4;
      /* 0x4289a7-0x4289fb: this whole bounded-count computation was
       * entirely dropped by Ghidra. Real disasm: iVar6 starts as
       * g_serverSelectRecordCount (0xe54ca4); if iVar4*6+6 <= iVar6,
       * iVar6 becomes the remaining-record count (iVar6-iVar4*6),
       * otherwise it's clamped to 6; the byte count passed to
       * AppendPacketBytes is iVar6*2. self=iVar2 (DAT_007934e8, still
       * live from the top of this function). */
      iVar6 = g_serverSelectRecordCount;
      if (iVar4 * 6 + 6 <= iVar6) {
        iVar6 = iVar6 - iVar4 * 6;
      }
      else {
        iVar6 = 6;
      }
      AppendPacketBytes(0,iVar2,(uint)(iVar6 * 2),g_serverSelectRecords + iVar4 * 0xc);
      goto LAB_004287a5;
    }
    *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
    *(undefined2 *)(iVar2 + 0x4d4) = 0x2100;
    *(undefined1 *)(iVar2 + 0x4d6) = *(undefined1 *)(param_1 + 0x115);
    iVar4 = *(int *)(iVar2 + 0x44d0);
    *(int *)(iVar2 + 0x44d0) = iVar4 + 1;
    *(undefined1 *)(iVar4 + 0x4d1 + iVar2) = *(undefined1 *)(param_1 + 0x116);
    *(int *)(iVar2 + 0x44d0) = *(int *)(iVar2 + 0x44d0) + 1;
    iVar4 = *(int *)(param_1 + 0x118) + 1;
    *(int *)(param_1 + 0x11c) = iVar4;
    *(short *)(*(int *)(iVar2 + 0x44d0) + 0x4d0 + iVar2) = (short)iVar4;
LAB_0042879e:
    *(int *)(iVar2 + 0x44d0) = *(int *)(iVar2 + 0x44d0) + 2;
LAB_004287a5:
    SendOutgoingPacket(iVar2);
    *(undefined4 *)(param_1 + 4) = 0xffffffff;
    RefreshGameRoomListControls();
    return;
  case 0xe:
    *(undefined1 *)(param_1 + 0x115) = 6;
    *(undefined4 *)(param_1 + 0x118) = 0;
    FindBuddyRoomsForServer(*(undefined4 *)(iVar4 + 0x3f804));
    iVar2 = DAT_007934e8;
    if (g_serverSelectRecordCount != 0) {
      *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x2101;
      *(undefined4 *)(iVar2 + 0x44d0) = 6;
      *(undefined4 *)(param_1 + 0x118) = 0;
      *(undefined4 *)(param_1 + 0x11c) = 0;
      /* 0x428a53-0x428a8f: another dropped bounded-count computation.
       * Real disasm: iVar6 = min(g_serverSelectRecordCount, 6); the byte
       * count passed to AppendPacketBytes is iVar6*2. self=iVar2
       * (DAT_007934e8, reloaded just above at the top of this case). */
      iVar6 = g_serverSelectRecordCount;
      if (6 <= iVar6) {
        iVar6 = 6;
      }
      AppendPacketBytes(0,iVar2,(uint)(iVar6 * 2),g_serverSelectRecords);
      SendOutgoingPacket(iVar2);
      RefreshGameRoomListControls();
      *(undefined4 *)(param_1 + 4) = 0xffffffff;
      return;
    }
    *(undefined1 *)(iVar4 + 0x44648) = 0;
    *(undefined1 *)(param_1 + 0x120) = 0;
    RefreshGameRoomListControls();
    *(undefined4 *)(param_1 + 4) = 0xffffffff;
    return;
  case 0xf:
    BuildEnterRoomNumberDialog();
    uVar5 = 0;
    break;
  case 0x1e:
    FUN_00429fb0();
    return;
  case 0x1f:
    SendJoinRoomSelected();
    return;
  case 0x20:
    FUN_00429f90();
    uVar5 = 1;
    break;
  case 0x21:
    RefreshGameRoomListControls();
    SendJoinRoomByNumber(param_1);
    uVar5 = 1;
    break;
  case 0x28:
    FUN_00429dc0();
    return;
  case 0x29:
    SendCreateRoom(param_1);
    return;
  default:
    return;
  }
  InvokeWidget(13,uVar5);
  return;
}

