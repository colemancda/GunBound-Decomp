/* State03_GameRoomList_OnEnter - 0x00428d00 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
/* RECOVERED (2026-07-19): all 43 LoadSpriteSet calls here dropped their
 * third argument - the ".img" sprite-set NAME, which the original passes in
 * EAX (`mov eax,<string>` before each `call 0x4f1790`). Same class as the 60
 * dropped names already fixed in InitGame. Left unfixed, LoadSpriteSet
 * forwarded a stale register (observed as the literal 3) to FindXFSEntry,
 * which faulted inside CompareXFSEntryName the moment the join->lobby path
 * first reached this OnEnter. Names extracted from the original's .data at
 * 0x5537ac-0x553b4c and matched to each call by its sprite-set id. */
/* RECOVERED (2026-07-19): the 12 AppendPersistentButtonName calls below all
 * dropped their second argument - the button NAME, which the original passes
 * in EAX (`mov eax,<string>` before each `call 0x401740`). That call is what
 * enters a button into the texture/descriptor table at g_clientContext+0x67ec70
 * (it allocates the entry and fills it via LoadButtonDefinitionFromXFS), so
 * with the names dropped NONE of the lobby's buttons were registered:
 * FindPreloadedTextureByName then returned NULL for every b_gamelist_* texture
 * inside CreateButtonWidget (probed live: State02's b_server_exitgame resolved
 * to a real descriptor, State03's b_gamelist_exit resolved to 0), which is what
 * derailed State03_GameRoomList_CreateButtons. State02's equivalent calls were
 * already recovered; these are the same class. Names extracted from the
 * original's .data and matched to the existing s_b_gamelist_* string globals
 * (same pointers CreateButtons uses). */
#include "ghidra_types.h"
#include <windows.h>


void __fastcall State03_GameRoomList_OnEnter(int *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uStack_4;
  
  uStack_4 = param_1;
  LoadSpriteSet(&DAT_00ea0e18,10000,"gamelist_back.img");
  LoadSpriteSet(&DAT_00ea0e18,0x2711,"gamelist_chat.img");
  LoadSpriteSet(&DAT_00ea0e18,0x2712,"gamelist_channel.img");
  LoadSpriteSet(&DAT_00ea0e18,0x2713,"gamelist_create.img");
  LoadSpriteSet(&DAT_00ea0e18,0x2714,"gamelist_password.img");
  LoadSpriteSet(&DAT_00ea0e18,0x2715,"gamelist_directgo.img");
  LoadSpriteSet(&DAT_00ea0e18,0x2716,"gameliststage.img");
  LoadSpriteSet(&DAT_00ea0e18,1000,"b_gamelist_exit.img");
  LoadSpriteSet(&DAT_00ea0e18,0x3e9,"b_gamelist_buddy.img");
  LoadSpriteSet(&DAT_00ea0e18,0x3ea,"b_gamelist_ranking.img");
  LoadSpriteSet(&DAT_00ea0e18,0x3eb,"b_gamelist_avatar.img");
  LoadSpriteSet(&DAT_00ea0e18,0x3ec,"b_gamelist_create.img");
  LoadSpriteSet(&DAT_00ea0e18,0x3ed,"b_gamelist_join.img");
  LoadSpriteSet(&DAT_00ea0e18,0x44c,"b_gamelist_viewall.img");
  LoadSpriteSet(&DAT_00ea0e18,0x44d,"b_gamelist_wait.img");
  LoadSpriteSet(&DAT_00ea0e18,0x44e,"b_gamelist_prev.img");
  LoadSpriteSet(&DAT_00ea0e18,0x44f,"b_gamelist_next.img");
  LoadSpriteSet(&DAT_00ea0e18,0x450,"b_gamelist_friend.img");
  LoadSpriteSet(&DAT_00ea0e18,0x451,"b_gamelist_directgo.img");
  LoadSpriteSet(&DAT_00ea0e18,0x4b0,"b_gamechat_ch1.img");
  LoadSpriteSet(&DAT_00ea0e18,0x4b1,"b_gamechat_ch2.img");
  LoadSpriteSet(&DAT_00ea0e18,0x4b2,"b_gamechat_ch3.img");
  LoadSpriteSet(&DAT_00ea0e18,0x4b3,"b_gamechat_ch4.img");
  LoadSpriteSet(&DAT_00ea0e18,0x4b4,"b_gamechat_ch5.img");
  LoadSpriteSet(&DAT_00ea0e18,0x4b5,"b_gamechat_ch6.img");
  LoadSpriteSet(&DAT_00ea0e18,0x4b6,"b_gamechat_ch7.img");
  LoadSpriteSet(&DAT_00ea0e18,0x4b7,"b_gamechat_ch8.img");
  LoadSpriteSet(&DAT_00ea0e18,0x514,"b_gamecreate_solo.img");
  LoadSpriteSet(&DAT_00ea0e18,0x515,"b_gamecreate_tag.img");
  LoadSpriteSet(&DAT_00ea0e18,0x516,"b_gamecreate_score.img");
  LoadSpriteSet(&DAT_00ea0e18,0x517,"b_gamecreate_jewel.img");
  LoadSpriteSet(&DAT_00ea0e18,0x518,"b_gamecreate_1vs1.img");
  LoadSpriteSet(&DAT_00ea0e18,0x519,"b_gamecreate_2vs2.img");
  LoadSpriteSet(&DAT_00ea0e18,0x51a,"b_gamecreate_3vs3.img");
  LoadSpriteSet(&DAT_00ea0e18,0x51b,"b_gamecreate_4vs4.img");
  LoadSpriteSet(&DAT_00ea0e18,0x51c,"b_gamecreate_create.img");
  LoadSpriteSet(&DAT_00ea0e18,0x51d,"b_gamecreate_cancel.img");
  LoadSpriteSet(&DAT_00ea0e18,0x578,"b_password_ok.img");
  LoadSpriteSet(&DAT_00ea0e18,0x579,"b_password_cancel.img");
  LoadSpriteSet(&DAT_00ea0e18,0x5dc,"b_directgo_ok.img");
  LoadSpriteSet(&DAT_00ea0e18,0x5dd,"b_directgo_cancel.img");
  LoadSpriteSet(&DAT_00ea0e18,0x640,"b_gamelist_yes.img");
  LoadSpriteSet(&DAT_00ea0e18,0x641,"b_gamelist_no.img");
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_gamelist_exit_0055379c);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_gamelist_buddy_00553788);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_gamelist_ranking_00553774);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_gamelist_avatar_00553760);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_gamelist_create_0055374c);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_gamelist_join_0055373c);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_gamelist_viewall_00553728);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_gamelist_wait_00553718);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_gamelist_prev_00553708);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_gamelist_next_005536f8);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_gamelist_friend_005536e4);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_gamelist_directgo_005536d0);
  State03_GameRoomList_CreateButtons();
  iVar4 = BuildLobbyChatPanel(&g_uiPanelManager,*(undefined4 *)(g_clientContext + 0x41340));
  param_1[0xa3] = iVar4;
  iVar4 = BuildChannelUserListPanel(&g_uiPanelManager);
  param_1[0xa4] = iVar4;
  cVar3 = PeekPacketChecksumBool();
  if ((cVar3 == '\x01') && (*(short *)(g_clientContext + 0x3b96f) != -1)) {
    *(undefined1 *)((int)param_1 + 0x115) = 1;
  }
  else {
    *(undefined1 *)((int)param_1 + 0x115) = 2;
  }
  iVar2 = DAT_007934e8;
  *(undefined1 *)((int)param_1 + 0x116) = 0;
  param_1[0x46] = 0;
  *(undefined1 *)(param_1 + 0x48) = 0;
  *(undefined4 *)(iVar2 + 0x44d0) = 6;
  *(undefined2 *)(iVar2 + 0x4d4) = 0x2100;
  *(undefined1 *)(iVar2 + 0x4d6) = *(undefined1 *)((int)param_1 + 0x115);
  iVar4 = *(int *)(iVar2 + 0x44d0);
  *(int *)(iVar2 + 0x44d0) = iVar4 + 1;
  *(undefined1 *)(iVar4 + 0x4d1 + iVar2) = *(undefined1 *)((int)param_1 + 0x116);
  *(int *)(iVar2 + 0x44d0) = *(int *)(iVar2 + 0x44d0) + 1;
  cVar3 = PeekPacketChecksumBool();
  iVar4 = DAT_007934e8;
  if ((cVar3 == '\x01') && (*(ushort *)(g_clientContext + 0x3b96f) != 0xffff)) {
    *(short *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) =
         (short)((ulonglong)((longlong)(int)(uint)*(ushort *)(g_clientContext + 0x3b96f) * 0x2aaaaaab)
                >> 0x20);
  }
  else {
    *(short *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = (short)param_1[0x47];
  }
  *(int *)(iVar4 + 0x44d0) = *(int *)(iVar4 + 0x44d0) + 2;
  SendOutgoingPacket(iVar4);
  puVar1 = (undefined4 *)(DAT_007934e4 + 4);
  *(undefined1 *)(DAT_007934e4 + 8) = 1;
  SetWindowTextA((HWND)*puVar1,&DAT_00551cb1);
  param_1[1] = -1;
  *(undefined1 *)(param_1 + 3) = 0;
  *(undefined1 *)((int)param_1 + 0xd) = 0;
  *(undefined1 *)((int)param_1 + 0xe) = 0;
  PlayMusicTrack(1,(byte *)"channel.mp3");
  iVar4 = g_clientContext;
  *(undefined4 *)(&DAT_0067e3c8 + g_clientContext) = 0;
  if (*(FILE **)(&g_replayFileHandle + iVar4) != (FILE *)0x0) {
    uStack_4 = (int *)CONCAT13(3,(undefined3)uStack_4);
    _fwrite((void *)((int)&uStack_4 + 3),1,1,*(FILE **)(&g_replayFileHandle + iVar4));
    _fclose(*(FILE **)(&g_replayFileHandle + g_clientContext));
    *(undefined4 *)(&g_replayFileHandle + g_clientContext) = 0;
  }
  param_1[0x49] = -1;
  FUN_005093e0();
  FUN_0050f290();
  BuildBuddyPanel();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((uVar5 & 0x100000) != 0) {
    iVar4 = *param_1;
    uVar8 = 6;
    uVar7 = 2;
    uVar6 = GetLocalizedString(&g_localizedStringTable,0xc351);
    (**(code **)(iVar4 + 0x28))(uVar6,uVar7,uVar8);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((uVar5 & 0x200000) != 0) {
    iVar4 = *param_1;
    uVar8 = 6;
    uVar7 = 2;
    uVar6 = GetLocalizedString(&g_localizedStringTable,0xc352);
    (**(code **)(iVar4 + 0x28))(uVar6,uVar7,uVar8);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((uVar5 & 0x400000) != 0) {
    iVar4 = *param_1;
    uVar8 = 6;
    uVar7 = 2;
    uVar6 = GetLocalizedString(&g_localizedStringTable,0xc353);
    (**(code **)(iVar4 + 0x28))(uVar6,uVar7,uVar8);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((uVar5 & 0x800000) != 0) {
    iVar4 = *param_1;
    uVar8 = 6;
    uVar7 = 2;
    uVar6 = GetLocalizedString(&g_localizedStringTable,0xc354);
    (**(code **)(iVar4 + 0x28))(uVar6,uVar7,uVar8);
  }
  return;
}

