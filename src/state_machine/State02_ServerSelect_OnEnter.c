/* State02_ServerSelect_OnEnter - 0x004e14b0 in the original binary.
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


void __fastcall State02_ServerSelect_OnEnter(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  bool bVar5;
  
  LoadSpriteSet(&DAT_00ea0e18,10000);
  LoadSpriteSet(&DAT_00ea0e18,0x2711);
  LoadSpriteSet(&DAT_00ea0e18,1000);
  LoadSpriteSet(&DAT_00ea0e18,0x3e9);
  LoadSpriteSet(&DAT_00ea0e18,0x3ea);
  LoadSpriteSet(&DAT_00ea0e18,0x44c);
  LoadSpriteSet(&DAT_00ea0e18,0x44d);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
  AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
  CreateButtonWidget(&DAT_00e9be90,0,0,1000,s_b_server_exitgame_00557144,0x28,0x227,0x6b,0x2d,1,0);
  CreateButtonWidget(&DAT_00e9be90,0,1,0x3e9,s_b_server_buddygame_00557170,0xa3,0x227,0x6b,0x2d,1,0)
  ;
  CreateButtonWidget(&DAT_00e9be90,0,2,0x3ea,s_b_server_choiceserver_00557158,0x199,0x227,0x6b,0x2d,
                     0,0);
  iVar1 = g_clientContext;
  *(undefined4 *)(param_1 + 8) = 0xffffffff;
  *(undefined1 *)(iVar1 + 0x3f808) = 0;
  *(undefined4 *)(iVar1 + 0x3f809) = 0;
  *(undefined4 *)(iVar1 + 0x3f80d) = 0;
  *(undefined4 *)(iVar1 + 0x3f811) = 0;
  *(undefined4 *)(iVar1 + 0x3f815) = 0;
  *(undefined4 *)(iVar1 + 0x3f81a) = 0;
  *(undefined4 *)(iVar1 + 0x3f81e) = 0;
  *(undefined4 *)(iVar1 + 0x3f822) = 0;
  *(undefined4 *)(iVar1 + 0x3f826) = 0;
  *(undefined4 *)(iVar1 + 0x3f82a) = 0;
  *(undefined4 *)(iVar1 + 0x3f82e) = 0;
  *(undefined4 *)(iVar1 + 0x3f832) = 0;
  *(undefined4 *)(iVar1 + 0x3f836) = 0;
  puVar4 = (undefined4 *)(iVar1 + 0x3f84a);
  for (iVar3 = 0x200; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  puVar4 = (undefined4 *)(iVar1 + 0x4004a);
  for (iVar3 = 0x400; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  puVar4 = (undefined4 *)(iVar1 + 0x4104a);
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  *(undefined4 *)(iVar1 + 0x4108a) = 0;
  *(undefined4 *)(iVar1 + 0x4108e) = 0;
  *(undefined4 *)(iVar1 + 0x41092) = 0;
  *(undefined4 *)(iVar1 + 0x41096) = 0;
  *(undefined4 *)(iVar1 + 0x4109a) = 0;
  *(undefined4 *)(iVar1 + 0x4109e) = 0;
  *(undefined4 *)(iVar1 + 0x410a2) = 0;
  *(undefined4 *)(iVar1 + 0x410a6) = 0;
  *(undefined4 *)(iVar1 + 0x410aa) = 0;
  *(undefined4 *)(iVar1 + 0x410ae) = 0;
  *(undefined4 *)(iVar1 + 0x410b2) = 0;
  *(undefined4 *)(iVar1 + 0x410b6) = 0;
  *(undefined4 *)(iVar1 + 0x410ba) = 0;
  *(undefined4 *)(iVar1 + 0x410be) = 0;
  *(undefined4 *)(iVar1 + 0x410c2) = 0;
  *(undefined4 *)(iVar1 + 0x410c6) = 0;
  *(undefined4 *)(iVar1 + 0x410ca) = 0;
  *(undefined4 *)(iVar1 + 0x410ce) = 0;
  *(undefined4 *)(iVar1 + 0x410d2) = 0;
  *(undefined4 *)(iVar1 + 0x410d6) = 0;
  *(undefined4 *)(iVar1 + 0x410da) = 0;
  *(undefined4 *)(iVar1 + 0x410de) = 0;
  *(undefined4 *)(iVar1 + 0x410e2) = 0;
  *(undefined4 *)(iVar1 + 0x410e6) = 0;
  *(undefined4 *)(iVar1 + 0x410ea) = 0;
  *(undefined4 *)(iVar1 + 0x410ee) = 0;
  *(undefined4 *)(iVar1 + 0x410f2) = 0;
  *(undefined4 *)(iVar1 + 0x410f6) = 0;
  *(undefined4 *)(iVar1 + 0x410fa) = 0;
  *(undefined4 *)(iVar1 + 0x410fe) = 0;
  *(undefined4 *)(iVar1 + 0x41102) = 0;
  *(undefined4 *)(iVar1 + 0x41106) = 0;
  *(undefined4 *)(iVar1 + 0x4110a) = 0;
  *(undefined4 *)(iVar1 + 0x4110e) = 0;
  *(undefined4 *)(iVar1 + 0x41112) = 0;
  *(undefined4 *)(iVar1 + 0x41116) = 0;
  *(undefined1 *)(param_1 + 4) = 0;
  *(undefined1 *)(param_1 + 5) = 0;
  *(undefined1 *)(param_1 + 6) = 1;
  *(undefined4 *)(param_1 + 0xc) = 0xffffffff;
  *(undefined1 *)(param_1 + 0x10) = 0;
  if ((int)DAT_005b2b64 < 1) {
    iVar1 = *(int *)(iVar1 + 0x3f804);
    if (iVar1 < 1) {
      uVar2 = 0;
    }
    else {
      uVar2 = (int)(iVar1 + (iVar1 >> 0x1f & 0xfU)) >> 4;
    }
  }
  else {
    uVar2 = DAT_005b2b64 >> 4;
  }
  *(uint *)(param_1 + 0x14) = uVar2;
  *(uint *)(param_1 + 0x18) = uVar2;
  *(undefined1 *)(param_1 + 0x1c) = 0;
  BuildWorldListPanel(&g_uiPanelManager);
  BeginServerConnect(&DAT_005b2ad0,DAT_005b33e8,DAT_007934f0);
  iVar1 = DAT_007934e4;
  *(undefined1 *)(param_1 + 7) = 1;
  *(undefined1 *)(iVar1 + 8) = 1;
  iVar1 = DAT_007934e8;
  if (*(char *)(DAT_007934e8 + 0x84e5) != '\0') {
    iVar3 = *(int *)(DAT_007934e8 + 0x84e0);
    if (iVar3 != 0) {
      *(undefined4 *)(iVar3 + 0x22c) = 1;
      if (*(SOCKET *)(iVar3 + 0x24) != 0xffffffff) {
        closesocket(*(SOCKET *)(iVar3 + 0x24));
      }
      *(undefined4 *)(iVar3 + 0x24) = 0xffffffff;
      *(undefined1 *)(iVar3 + 0x22a) = 0;
      *(undefined1 *)(iVar1 + 0x84e5) = 0;
    }
  }
  *(undefined4 *)(param_1 + 0x20) = 0;
  PlayMusicTrack(1);
  iVar1 = g_clientContext;
  bVar5 = DAT_007934f4 != 0;
  *(undefined1 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(iVar1 + 0x3f804) = 0xffffffff;
  if (bVar5) {
    FUN_00405ba0();
    return;
  }
  FUN_00404410(&DAT_00e53e88);
  return;
}

