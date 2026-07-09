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
  LoadSpriteSet(&DAT_00ea0e18,10000);
  LoadSpriteSet(&DAT_00ea0e18,0x2711);
  LoadSpriteSet(&DAT_00ea0e18,0x2712);
  LoadSpriteSet(&DAT_00ea0e18,0x2713);
  LoadSpriteSet(&DAT_00ea0e18,0x2714);
  LoadSpriteSet(&DAT_00ea0e18,0x2715);
  LoadSpriteSet(&DAT_00ea0e18,0x2716);
  LoadSpriteSet(&DAT_00ea0e18,1000);
  LoadSpriteSet(&DAT_00ea0e18,0x3e9);
  LoadSpriteSet(&DAT_00ea0e18,0x3ea);
  LoadSpriteSet(&DAT_00ea0e18,0x3eb);
  LoadSpriteSet(&DAT_00ea0e18,0x3ec);
  LoadSpriteSet(&DAT_00ea0e18,0x3ed);
  LoadSpriteSet(&DAT_00ea0e18,0x44c);
  LoadSpriteSet(&DAT_00ea0e18,0x44d);
  LoadSpriteSet(&DAT_00ea0e18,0x44e);
  LoadSpriteSet(&DAT_00ea0e18,0x44f);
  LoadSpriteSet(&DAT_00ea0e18,0x450);
  LoadSpriteSet(&DAT_00ea0e18,0x451);
  LoadSpriteSet(&DAT_00ea0e18,0x4b0);
  LoadSpriteSet(&DAT_00ea0e18,0x4b1);
  LoadSpriteSet(&DAT_00ea0e18,0x4b2);
  LoadSpriteSet(&DAT_00ea0e18,0x4b3);
  LoadSpriteSet(&DAT_00ea0e18,0x4b4);
  LoadSpriteSet(&DAT_00ea0e18,0x4b5);
  LoadSpriteSet(&DAT_00ea0e18,0x4b6);
  LoadSpriteSet(&DAT_00ea0e18,0x4b7);
  LoadSpriteSet(&DAT_00ea0e18,0x514);
  LoadSpriteSet(&DAT_00ea0e18,0x515);
  LoadSpriteSet(&DAT_00ea0e18,0x516);
  LoadSpriteSet(&DAT_00ea0e18,0x517);
  LoadSpriteSet(&DAT_00ea0e18,0x518);
  LoadSpriteSet(&DAT_00ea0e18,0x519);
  LoadSpriteSet(&DAT_00ea0e18,0x51a);
  LoadSpriteSet(&DAT_00ea0e18,0x51b);
  LoadSpriteSet(&DAT_00ea0e18,0x51c);
  LoadSpriteSet(&DAT_00ea0e18,0x51d);
  LoadSpriteSet(&DAT_00ea0e18,0x578);
  LoadSpriteSet(&DAT_00ea0e18,0x579);
  LoadSpriteSet(&DAT_00ea0e18,0x5dc);
  LoadSpriteSet(&DAT_00ea0e18,0x5dd);
  LoadSpriteSet(&DAT_00ea0e18,0x640);
  LoadSpriteSet(&DAT_00ea0e18,0x641);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
  State03_GameRoomList_CreateButtons();
  iVar4 = BuildLobbyChatPanel(&g_uiPanelManager,*(undefined4 *)(g_clientContext + 0x41340));
  param_1[0xa3] = iVar4;
  iVar4 = BuildChannelUserListPanel(&g_uiPanelManager);
  param_1[0xa4] = iVar4;
  cVar3 = FUN_004065a0();
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
  cVar3 = FUN_004065a0();
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
  FUN_004d2680();
  puVar1 = (undefined4 *)(DAT_007934e4 + 4);
  *(undefined1 *)(DAT_007934e4 + 8) = 1;
  SetWindowTextA((HWND)*puVar1,&DAT_00551cb1);
  param_1[1] = -1;
  *(undefined1 *)(param_1 + 3) = 0;
  *(undefined1 *)((int)param_1 + 0xd) = 0;
  *(undefined1 *)((int)param_1 + 0xe) = 0;
  PlayMusicTrack(1);
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
    uVar6 = GetLocalizedString(&DAT_00796eec,0xc351);
    (**(code **)(iVar4 + 0x28))(uVar6,uVar7,uVar8);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((uVar5 & 0x200000) != 0) {
    iVar4 = *param_1;
    uVar8 = 6;
    uVar7 = 2;
    uVar6 = GetLocalizedString(&DAT_00796eec,0xc352);
    (**(code **)(iVar4 + 0x28))(uVar6,uVar7,uVar8);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((uVar5 & 0x400000) != 0) {
    iVar4 = *param_1;
    uVar8 = 6;
    uVar7 = 2;
    uVar6 = GetLocalizedString(&DAT_00796eec,0xc353);
    (**(code **)(iVar4 + 0x28))(uVar6,uVar7,uVar8);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((uVar5 & 0x800000) != 0) {
    iVar4 = *param_1;
    uVar8 = 6;
    uVar7 = 2;
    uVar6 = GetLocalizedString(&DAT_00796eec,0xc354);
    (**(code **)(iVar4 + 0x28))(uVar6,uVar7,uVar8);
  }
  return;
}

