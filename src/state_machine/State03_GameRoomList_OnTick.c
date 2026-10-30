/* State03_GameRoomList_OnTick - 0x00429730 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-30, CERTAIN (was FUN_00429730).  Slot 9 (+0x24) of
 * State03's vtable 0x553670, read from the original's .rdata (slots
 * 1/5/6/7/8 of the same table are the named State03_GameRoomList_*
 * methods).  GameTick calls that slot on the current state once per
 * tick (src/entry/GameTick.c), and the named siblings fill it with
 * their OnTick: State01_Title_OnTick, State02_ServerSelect_OnTick,
 * State06_Logo2_OnTick, State09_ReadyRoom_OnTick,
 * State11_InBattle_OnTick.  Each tick it re-runs RoomCardHitTest at the
 * cursor anchor and stores the hovered room card at this+8.
 */
#include "ghidra_types.h"


void __fastcall State03_GameRoomList_OnTick(int param_1)

{
  int iVar1;
  undefined1 uVar2;
  undefined4 uVar3;
  int iVar4;
  
  uVar3 = RoomCardHitTest(g_cursorAnchorY,0,g_cursorAnchorX);
  iVar1 = g_clientContext;
  *(undefined4 *)(param_1 + 8) = uVar3;
  iVar4 = 0;
  if (*(char *)(iVar1 + 0x44648) != '\0') {
    do {
      uVar2 = FUN_00402160(*(undefined4 *)(iVar1 + 0x3f804));
      *(undefined1 *)(iVar1 + 0x449b4 + iVar4) = uVar2;
      iVar4 = iVar4 + 1;
    } while (iVar4 < (int)(uint)*(byte *)(iVar1 + 0x44648));
  }
  if (g_stateChangeInProgress != 0) {
    if (*(char *)(param_1 + 0xc) != '\0') {
      PanelManager_Unregister(&g_uiPanelManager,0,0);
    }
    if (*(char *)(param_1 + 0xe) != '\0') {
      PanelManager_Unregister(&g_uiPanelManager,0,1);
    }
    if (*(char *)(param_1 + 0xd) != '\0') {
      PanelManager_Unregister(&g_uiPanelManager,0,2);
    }
  }
  return;
}

