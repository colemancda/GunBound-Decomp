/* CloseEnterRoomNumberDialog - 0x00429f90 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00429f90 mean this function.)
 *
 * NAMED (2026-11-05), CERTAIN. Evidence from outside the body:
 * PanelManager_Unregister(&g_uiPanelManager, 0, 1): key 1.
 * BuildEnterRoomNumberDialog (Panel.cpp) is a singleton on (m_typeId 0,
 * m_id 1) and stamps p->m_id = 1. Caller: State03_GameRoomList_OnCommand
 * case 0x20, immediately before case 0x21 SendJoinRoomByNumber.
 */
#include "ghidra_types.h"


void CloseEnterRoomNumberDialog(void)

{
  PanelManager_Unregister(&g_uiPanelManager,0,1);
  return;
}

