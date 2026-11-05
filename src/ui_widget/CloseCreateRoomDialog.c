/* CloseCreateRoomDialog - 0x00429dc0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00429dc0 mean this function.)
 *
 * NAMED (2026-11-05), CERTAIN. Evidence from outside the body:
 * PanelManager_Unregister(&g_uiPanelManager, 0, 0): typeId 0, key 0.
 * BuildCreateRoomDialog (Panel.cpp) is a singleton that scans for
 * (m_typeId 0, m_id 0) and stamps p->m_id = 0, so key 0 is the Create Room
 * dialog. Callers: State03_GameRoomList_OnCommand case 0x28 (the dialog's
 * OK/command event, which then goes to SendCreateRoom on 0x29) and
 * State03_GameRoomList_ProcessPacket's create-room response path.
 */
#include "ghidra_types.h"


void CloseCreateRoomDialog(void)

{
  PanelManager_Unregister(&g_uiPanelManager,0,0);
  return;
}

