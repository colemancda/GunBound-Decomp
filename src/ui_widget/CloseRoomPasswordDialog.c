/* CloseRoomPasswordDialog - 0x00429fb0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00429fb0 mean this function.)
 *
 * NAMED (2026-11-05), CERTAIN. Evidence from outside the body:
 * PanelManager_Unregister(&g_uiPanelManager, 0, 2): key 2.
 * BuildRoomPasswordDialog (Panel.cpp) is a singleton on (m_typeId 0, m_id
 * 2) and stamps p->m_id = 2; RoomPasswordDialog_SubmitPassword's header
 * says event 0x1e is routed here by State03_GameRoomList_OnCommand.
 */
#include "ghidra_types.h"


void CloseRoomPasswordDialog(void)

{
  PanelManager_Unregister(&g_uiPanelManager,0,2);
  return;
}

