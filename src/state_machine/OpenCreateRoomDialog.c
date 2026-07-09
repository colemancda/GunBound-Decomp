/* OpenCreateRoomDialog - 0x00429c30 in the original binary.
 *
 * Lobby 'Create' button handler: opens the Create Room dialog (message id 0x62b2) via BuildCreateRoomDialog. See docs/screens/03_game_room_list.md. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall OpenCreateRoomDialog(int param_1)

{
  *(undefined4 *)(param_1 + 0x110) = 0x62b2;
  *(undefined1 *)(param_1 + 0x114) = 8;
  BuildCreateRoomDialog(&g_uiPanelManager,(undefined4 *)(param_1 + 0x110),(undefined1 *)(param_1 + 0x114),
               &DAT_005b3368);
  return;
}

