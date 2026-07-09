/* State03_GameRoomList_CreateButtons - 0x0042aba0 in the original binary.
 *
 * Creates the lobby's 12 bottom-bar buttons (exit/buddy/ranking/avatar/create/join/viewall/wait/prev/next/friend/directgo). See docs/screens/03_game_room_list.md. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void State03_GameRoomList_CreateButtons(void)

{
  CreateButtonWidget(&DAT_00e9be90,0,0,1000,s_b_gamelist_exit_0055379c,0x28,0x227,0x6b,0x2d,0,0);
  CreateButtonWidget(&DAT_00e9be90,0,1,0x3e9,s_b_gamelist_buddy_00553788,0xa3,0x227,0x6b,0x2d,0,0);
  CreateButtonWidget(&DAT_00e9be90,0,2,0x3ea,s_b_gamelist_ranking_00553774,0x11e,0x227,0x6b,0x2d,0,0
                    );
  CreateButtonWidget(&DAT_00e9be90,0,3,0x3eb,s_b_gamelist_avatar_00553760,0x199,0x227,0x6b,0x2d,0,0)
  ;
  CreateButtonWidget(&DAT_00e9be90,0,4,0x3ec,s_b_gamelist_create_0055374c,0x214,0x227,0x6b,0x2d,0,0)
  ;
  CreateButtonWidget(&DAT_00e9be90,0,5,0x3ed,s_b_gamelist_join_0055373c,0x28f,0x227,0x6b,0x2d,0,0);
  CreateButtonWidget(&DAT_00e9be90,0,10,0x44c,s_b_gamelist_viewall_00553728,0x2a,0xf6,0x51,0x21,0,0)
  ;
  CreateButtonWidget(&DAT_00e9be90,0,0xb,0x44d,s_b_gamelist_wait_00553718,0x83,0xf6,0x51,0x21,0,0);
  CreateButtonWidget(&DAT_00e9be90,0,0xc,0x44e,s_b_gamelist_prev_00553708,0xf2,0xf6,0x31,0x21,0,0);
  CreateButtonWidget(&DAT_00e9be90,0,0xd,0x44f,s_b_gamelist_next_005536f8,0x124,0xf6,0x31,0x21,0,0);
  CreateButtonWidget(&DAT_00e9be90,0,0xe,0x450,s_b_gamelist_friend_005536e4,0x173,0xf6,0x51,0x21,0,0
                    );
  CreateButtonWidget(&DAT_00e9be90,0,0xf,0x451,s_b_gamelist_directgo_005536d0,0x1cc,0xf6,0x51,0x21,0
                     ,0);
  FUN_0042a090();
  return;
}

