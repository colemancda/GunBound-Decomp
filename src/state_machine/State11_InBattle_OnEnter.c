/* State11_InBattle_OnEnter - 0x004bb730 in the original binary.
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


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall State11_InBattle_OnEnter(int param_1)

{
  undefined1 uVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  byte bVar4;
  char cVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  undefined4 uVar10;
  byte bVar11;
  byte *pbVar12;
  int iVar13;
  undefined4 *puVar14;
  bool bVar15;
  undefined2 uVar16;
  undefined4 uVar17;
  char cStack_99;
  undefined *puStack_98;
  int iStack_94;
  undefined *apuStack_90 [2];
  int iStack_88;
  int iStack_84;
  char acStack_80 [128];
  
  *(undefined4 *)(param_1 + 0x23c4) = 0xffffffff;
  DAT_007a768c = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = _rand();
  *(char *)(param_1 + 0x23c8) = (char)iVar6;
  uVar7 = _rand();
  apuStack_90[0] = (undefined *)(uVar7 & 0x800000ff);
  if ((int)apuStack_90[0] < 0) {
    apuStack_90[0] = (undefined *)(((uint)(apuStack_90[0] + -1) | 0xffffff00) + 1);
  }
  *(byte *)(param_1 + 0x23c9) = (byte)apuStack_90[0];
  bVar4 = '\x01' << (*(byte *)(param_1 + 0x23c8) & 7);
  bVar4 = ~bVar4 & (byte)apuStack_90[0] | bVar4;
  *(byte *)(param_1 + 0x23c9) = bVar4;
  *(byte *)(param_1 + 0x23ca) = *(byte *)(param_1 + 0x23c8) + bVar4 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  _sprintf(acStack_80,s_stage_d_mp3_005569c0,(uint)*(byte *)(g_clientContext + 0x475c4));
  cVar5 = PlayMusicTrack(1);
  if (cVar5 == '\0') {
    iVar6 = _rand();
    _sprintf(acStack_80,s_stage_d_mp3_005569c0,iVar6 % 6 + 1);
    PlayMusicTrack(1);
  }
  iVar6 = LoadGameDataFiles(g_clientContext);
  if (iVar6 != 0) {
    ShowErrorDialog(1);
    return;
  }
  CreateButtonWidget(&DAT_00e9be90,0,0,1000,s_b_play_option_00554174,0xb,3,0x28,0x1e,1,0);
  CreateButtonWidget(&DAT_00e9be90,0,2,0x3ea,s_b_play_weapon2_00554154,0x2f,0x232,0x23,0x22,1,0);
  CreateButtonWidget(&DAT_00e9be90,0,3,0x3eb,s_b_play_skip_00554138,0x2ee,3,0x28,0x1e,0,0);
  CreateButtonWidget(&DAT_00e9be90,0,4,0x3ec,s_b_play_all_0055412c,0xa8,0x219,0x1d,0x10,1,0);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar6 == 2) {
    CreateButtonWidget(&DAT_00e9be90,0,0x11,0x3f9,s_b_play_tag_00554120,0x29e,0x232,0x28,0x22,0,0);
  }
  iVar6 = g_clientContext;
  pbVar12 = &DAT_0067e3cc + g_clientContext;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = _rand();
  *pbVar12 = (byte)iVar8;
  iVar8 = _rand();
  bVar4 = *pbVar12;
  (&DAT_0067e3cd)[iVar6] = (byte)iVar8;
  apuStack_90[0] = (undefined *)(bVar4 & 7);
  bVar11 = ~('\x01' << (sbyte)apuStack_90[0]) & (byte)iVar8 | '\0' << (sbyte)apuStack_90[0];
  (&DAT_0067e3cd)[iVar6] = bVar11;
  (&DAT_0067e3ce)[iVar6] = bVar4 + bVar11 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = _rand();
  *(char *)(param_1 + 0x22ff) = (char)iVar6;
  iVar6 = _rand();
  *(byte *)(param_1 + 0x2300) = (byte)iVar6;
  bVar4 = *(byte *)(param_1 + 0x22ff) & 7;
  bVar4 = ~('\x01' << bVar4) & (byte)iVar6 | '\0' << bVar4;
  *(byte *)(param_1 + 0x2300) = bVar4;
  *(byte *)(param_1 + 0x2301) = *(byte *)(param_1 + 0x22ff) + bVar4 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar6 == 3) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = 0;
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    apuStack_90[0] = &DAT_0067e3d0 + g_clientContext;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(iVar6 / 2 + 1);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    apuStack_90[0] = &DAT_0067e5f4 + g_clientContext;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = iVar6 / 2 + 1;
  }
  EncodeOutgoingPacketField(iVar6);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = g_clientContext;
  *(undefined4 *)(g_clientContext + 0x20b94) = 0;
  *(undefined4 *)(iVar6 + 0x20ba0) = 0;
  *(undefined4 *)(iVar6 + 0x1fe1c) = 0;
  *(undefined4 *)(iVar6 + 0x1fe20) = 0;
  *(undefined4 *)(iVar6 + 0x1fe34) = 0;
  *(undefined4 *)(iVar6 + 0x1fe38) = 0;
  iStack_94 = 0;
  iStack_88 = 0;
  iStack_84 = 0;
  apuStack_90[0] = (undefined *)0x0;
  iVar8 = 0x4592c;
  iVar13 = 0x4597c;
  do {
    if (*(char *)(iVar6 + 0x45914 + iStack_94) != '\0') {
      puStack_98 = apuStack_90[0] + iVar6 + 0x477ec;
      if (*(char *)(iVar6 + 0x4590c + iStack_94) == -1) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        puStack_98 = (undefined *)PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        CreateMobile(iStack_94,puStack_98,0xfffffff6,10000,
                     *(undefined1 *)(g_clientContext + 0x4590c + iStack_94),
                     *(undefined2 *)(iVar8 + -0x10 + g_clientContext),
                     *(undefined2 *)(iVar8 + g_clientContext),iStack_88 + 0x457f1 + g_clientContext,
                     iStack_84 + 0x457a9 + g_clientContext,*(undefined4 *)(iVar13 + g_clientContext),
                     *(undefined4 *)(iVar13 + 0x20 + g_clientContext),1);
        puStack_98 = (undefined *)(g_clientContext + 0x45354);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar9 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = g_clientContext;
        if (iVar9 == 2) {
          puStack_98 = apuStack_90[0] + g_clientContext + 0x47a10;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          puStack_98 = (undefined *)PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar10 = *(undefined4 *)(iVar13 + 0x20 + g_clientContext);
          uVar17 = *(undefined4 *)(iVar13 + g_clientContext);
          iVar6 = iStack_84 + 0x457a9 + g_clientContext;
          iVar9 = iStack_88 + 0x457f1 + g_clientContext;
          uVar2 = *(undefined2 *)(iVar8 + g_clientContext);
          uVar3 = *(undefined2 *)(iVar8 + -0x10 + g_clientContext);
          uVar1 = *(undefined1 *)(g_clientContext + 0x4590c + iStack_94);
          uVar16 = 10000;
          uVar7 = 0xfffffff6;
          goto LAB_004bbe6b;
        }
      }
      else {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        puStack_98 = (undefined *)PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        CreateMobile(iStack_94,puStack_98,*(undefined2 *)(iVar8 + 0x4100 + g_clientContext),
                     *(undefined2 *)(iVar8 + 0x4110 + g_clientContext),
                     *(undefined1 *)(g_clientContext + 0x4590c + iStack_94),
                     *(undefined2 *)(iVar8 + -0x10 + g_clientContext),
                     *(undefined2 *)(iVar8 + g_clientContext),iStack_88 + 0x457f1 + g_clientContext,
                     iStack_84 + 0x457a9 + g_clientContext,*(undefined4 *)(iVar13 + g_clientContext),
                     *(undefined4 *)(iVar13 + 0x20 + g_clientContext),1);
        puStack_98 = (undefined *)(g_clientContext + 0x45354);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar9 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = g_clientContext;
        if (iVar9 == 2) {
          puStack_98 = apuStack_90[0] + g_clientContext + 0x47a10;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          puStack_98 = (undefined *)PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar10 = *(undefined4 *)(iVar13 + 0x20 + g_clientContext);
          uVar17 = *(undefined4 *)(iVar13 + g_clientContext);
          iVar6 = iStack_84 + 0x457a9 + g_clientContext;
          iVar9 = iStack_88 + 0x457f1 + g_clientContext;
          uVar2 = *(undefined2 *)(iVar8 + g_clientContext);
          uVar3 = *(undefined2 *)(iVar8 + -0x10 + g_clientContext);
          uVar1 = *(undefined1 *)(g_clientContext + 0x4590c + iStack_94);
          uVar16 = *(undefined2 *)(iVar8 + 0x4110 + g_clientContext);
          uVar7 = (uint)*(ushort *)(iVar8 + 0x4100 + g_clientContext);
LAB_004bbe6b:
          CreateMobile(iStack_94 + 8,puStack_98,uVar7,uVar16,uVar1,uVar3,uVar2,iVar9,iVar6,uVar17,
                       uVar10,0);
          iVar6 = g_clientContext;
        }
      }
    }
    iStack_94 = iStack_94 + 1;
    iStack_84 = iStack_84 + 9;
    iVar13 = iVar13 + 4;
    apuStack_90[0] = apuStack_90[0] + 0x448;
    iStack_88 = iStack_88 + 0xd;
    iVar8 = iVar8 + 2;
    if (0x4599b < iVar13) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar6 == 3) {
        iVar6 = 0;
        do {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          apuStack_90[0] = (undefined *)PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          puStack_98 = &DAT_006a8e90 + g_clientContext + iVar6;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar8 = PeekPacketChecksumState();
          bVar15 = iVar8 < (int)apuStack_90[0];
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (bVar15) {
            apuStack_90[0] = (undefined *)0x0;
          }
          else {
            puStack_98 = &DAT_006a8e90 + g_clientContext + iVar6;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar8 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (iVar8 < 0x28) {
              apuStack_90[0] = (undefined *)0x1;
            }
            else {
              puStack_98 = &DAT_006a8e90 + g_clientContext + iVar6;
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              iVar8 = PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              apuStack_90[0] = (undefined *)(3 - (uint)(iVar8 < 0x50));
            }
          }
          puStack_98 = &DAT_006a81b8 + g_clientContext + iVar6;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          puStack_98 = (undefined *)PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          FUN_00438410(&DAT_006a7f70 + g_clientContext,
                       (int)puStack_98 % *(int *)(&DAT_006a7720 + g_clientContext),apuStack_90[0],0);
          iVar6 = iVar6 + 0x224;
        } while (iVar6 < 0xcd8);
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar13 = GetPlayerRecordBySlot(g_clientContext);
      iVar6 = g_clientContext;
      *(int *)(g_clientContext + 0x621e0) = iVar13;
      iVar8 = DAT_007934e8;
      if (iVar13 == 0) {
        *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
        *(undefined2 *)(iVar8 + 0x4d4) = 0x2000;
        *(undefined2 *)(iVar8 + 0x4d6) = 0xffff;
        *(int *)(iVar8 + 0x44d0) = *(int *)(iVar8 + 0x44d0) + 2;
        SendOutgoingPacket();
        iVar6 = g_clientContext;
      }
      uVar7 = DAT_005b3480 * 0xda003 + 0x5703b11;
      DAT_005b3480 = DAT_005b3480 + (uVar7 * 0x61 + 0x61) % 0xf4241;
      FUN_00439d90(&DAT_006a7f70 + iVar6,*(int *)(&DAT_006a7720 + iVar6) / 2 + -500 + uVar7 % 1000);
      CreateButtonWidget(&DAT_00e9be90,0,0x12,0x3fa,s_b_play_weapon3_00554144,0x58,0x232,0x25,0x26,1
                         ,0);
      iVar6 = g_clientContext;
      *(undefined4 *)(param_1 + 4) = 0;
      *(undefined4 *)(param_1 + 8) = 0;
      *(undefined1 *)(iVar6 + 0xebee5) = 0;
      *(undefined4 *)(iVar6 + 0xebef0) = 0xfffffffd;
      *(undefined4 *)(iVar6 + 0xebeec) = 0xfffffffd;
      *(undefined4 *)(iVar6 + 0xebee8) = 0xf5;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(0xffffffff);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(0xffffffff);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = DAT_007934e4;
      *(undefined1 *)(DAT_007934e4 + 8) = 1;
      SendMessageA(*(HWND *)(iVar6 + 4),0xc5,0x3c,0);
      iVar6 = g_clientContext;
      *(undefined1 *)(param_1 + 0x10) = 0;
      *(undefined4 *)(iVar6 + 0x621e4) = 0;
      *(undefined4 *)(iVar6 + 0x58b60) = 0;
      puVar14 = (undefined4 *)(iVar6 + 0x58b64);
      for (iVar8 = 0x16; iVar8 != 0; iVar8 = iVar8 + -1) {
        *puVar14 = 0;
        puVar14 = puVar14 + 1;
      }
      *(undefined2 *)puVar14 = 0;
      puVar14 = (undefined4 *)(iVar6 + 0x58bbe);
      for (iVar8 = 0x23; iVar8 != 0; iVar8 = iVar8 + -1) {
        *puVar14 = 0;
        puVar14 = puVar14 + 1;
      }
      *(undefined4 *)(iVar6 + 0x58c4a) = 0;
      *(undefined4 *)(iVar6 + 0x58c4e) = 0;
      *(undefined2 *)(iVar6 + 0x58c52) = 0;
      puVar14 = (undefined4 *)(iVar6 + 0x58c54);
      for (iVar8 = 0x140; iVar8 != 0; iVar8 = iVar8 + -1) {
        *puVar14 = 0;
        puVar14 = puVar14 + 1;
      }
      *(undefined4 *)(iVar6 + 0x59154) = 0xffffffff;
      *(undefined4 *)(iVar6 + 0x59158) = 0xffffffff;
      *(undefined4 *)(iVar6 + 0x5915c) = 0xffffffff;
      *(undefined4 *)(iVar6 + 0x59160) = 0xffffffff;
      *(undefined4 *)(iVar6 + 0x59164) = 0xffffffff;
      *(undefined4 *)(iVar6 + 0x59168) = 0xffffffff;
      *(undefined4 *)(iVar6 + 0x5916c) = 0xffffffff;
      *(undefined4 *)(iVar6 + 0x59170) = 0xffffffff;
      *(undefined4 *)(iVar6 + 0x59174) = 0xffffffff;
      *(undefined4 *)(iVar6 + 0x59178) = 0xffffffff;
      *(undefined4 *)(iVar6 + 0x5917c) = 0;
      *(undefined4 *)(iVar6 + 0x59180) = 0;
      *(undefined4 *)(iVar6 + 0x59184) = 0;
      *(undefined4 *)(iVar6 + 0x59188) = 0;
      *(undefined4 *)(iVar6 + 0x5918c) = 0;
      *(undefined4 *)(param_1 + 0xc) = 0;
      *(undefined1 *)(param_1 + 0x91) = 0;
      (&DAT_006a7758)[iVar6] = 1;
      *(undefined4 *)(iVar6 + 0xf037c) = 1;
      *(undefined4 *)(iVar6 + 0xf0380) = 0xffffffff;
      *(undefined4 *)(iVar6 + 0xf0378) = 0;
      *(undefined4 *)(iVar6 + 0xf0374) = 0xffffffff;
      *(undefined4 *)(&DAT_005f2f38 + iVar6) = 0;
      *(undefined1 *)(param_1 + 0x92) = 0;
      *(undefined1 *)(param_1 + 0x93) = 0;
      *(undefined1 *)(param_1 + 0x94) = 1;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(0);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      puStack_98 = (undefined *)(g_clientContext + 0xebcbc);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar10 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar10);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      *(undefined4 *)(g_clientContext + 0xebee0) = 0;
      *(undefined4 *)(param_1 + 0x11cc) = 0;
      *(undefined4 *)(param_1 + 0x98) = 0;
      *(undefined4 *)(param_1 + 0x89c) = 0;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar8 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = g_clientContext;
      *(int *)(&DAT_006a73c0 + g_clientContext) = -iVar8;
      *(undefined4 *)(param_1 + 0x10a8) = 0xffffffff;
      *(undefined4 *)(param_1 + 0x10ac) = 0xffffffff;
      *(undefined4 *)(param_1 + 0x10b0) = 0;
      *(undefined4 *)(param_1 + 0x10b4) = 0xffffffff;
      bVar15 = *(char *)(iVar6 + 0x45121) != '\0';
      *(bool *)(param_1 + 0x10bc) = bVar15;
      *(uint *)(&DAT_006a647c + iVar6) = (-(uint)bVar15 & 0xfffffff0) + 0xf;
      *(undefined1 *)(param_1 + 0x10bd) = 0;
      *(undefined1 *)(param_1 + 0x10be) = 0;
      *(undefined4 *)(iVar6 + 0x5b81c) = 0;
      *(undefined4 *)(iVar6 + 0x5b820) = 0;
      *(undefined4 *)(iVar6 + 0x5b824) = 0;
      *(undefined4 *)(iVar6 + 0x5b828) = 0;
      *(undefined4 *)(iVar6 + 0x5b82c) = 0;
      *(undefined4 *)(iVar6 + 0x5b830) = 0;
      *(undefined4 *)(iVar6 + 0x5b834) = 0;
      *(undefined4 *)(iVar6 + 0x5b838) = 0;
      *(undefined4 *)(iVar6 + 0x5b83c) = 0;
      *(undefined4 *)(iVar6 + 0x5b840) = 0;
      *(undefined4 *)(iVar6 + 0x5b844) = 0;
      *(undefined4 *)(iVar6 + 0x5b848) = 0;
      *(undefined4 *)(iVar6 + 0x5b84c) = 0;
      *(undefined4 *)(iVar6 + 0x5b850) = 0;
      *(undefined4 *)(iVar6 + 0x5b854) = 0;
      *(undefined4 *)(iVar6 + 0x5b858) = 0;
      *(undefined4 *)(param_1 + 0x10c4) = 0xffffffff;
      *(undefined4 *)(param_1 + 0x10c8) = 0xffffffff;
      *(undefined4 *)(param_1 + 0x10cc) = 0xffffffff;
      *(undefined4 *)(param_1 + 0x10d0) = 0xffffffff;
      *(undefined4 *)(param_1 + 0x10d4) = 0;
      *(undefined4 *)(param_1 + 0x10d8) = 0;
      *(undefined4 *)(param_1 + 0x10dc) = 0;
      *(undefined4 *)(param_1 + 0x10e0) = 0;
      *(undefined4 *)(param_1 + 0x10e4) = 0;
      *(undefined4 *)(param_1 + 0x10e8) = 0;
      *(undefined4 *)(param_1 + 0x10ec) = 0;
      *(undefined4 *)(param_1 + 0x10f0) = 0;
      *(undefined4 *)(param_1 + 0x10f4) = 0;
      *(undefined4 *)(param_1 + 0x10f8) = 0;
      *(undefined4 *)(param_1 + 0x10fc) = 0;
      *(undefined4 *)(param_1 + 0x1100) = 0;
      *(undefined4 *)(param_1 + 0x1104) = 0;
      *(undefined4 *)(param_1 + 0x1108) = 0;
      *(undefined4 *)(param_1 + 0x110c) = 0;
      *(undefined4 *)(param_1 + 0x1110) = 0;
      *(undefined4 *)(param_1 + 0x1114) = 0;
      *(undefined4 *)(param_1 + 0x1118) = 0;
      *(undefined4 *)(param_1 + 0x111c) = 0;
      *(undefined4 *)(param_1 + 0x1120) = 0;
      *(undefined4 *)(param_1 + 0x1124) = 0;
      *(undefined4 *)(param_1 + 0x1128) = 0;
      *(undefined4 *)(param_1 + 0x112c) = 0;
      *(undefined4 *)(param_1 + 0x1130) = 0;
      *(undefined4 *)(param_1 + 0x1134) = 0;
      *(undefined4 *)(param_1 + 0x1138) = 0;
      *(undefined4 *)(param_1 + 0x113c) = 0;
      *(undefined4 *)(param_1 + 0x1140) = 0;
      *(undefined4 *)(param_1 + 0x1144) = 0;
      *(undefined4 *)(param_1 + 0x1148) = 0;
      *(undefined4 *)(param_1 + 0x114c) = 0;
      *(undefined4 *)(param_1 + 0x1150) = 0;
      *(undefined4 *)(param_1 + 0x1154) = 0;
      *(undefined4 *)(param_1 + 0x1158) = 0;
      *(undefined4 *)(param_1 + 0x115c) = 0;
      *(undefined4 *)(param_1 + 0x1160) = 0;
      *(undefined4 *)(param_1 + 0x1164) = 0;
      *(undefined4 *)(param_1 + 0x1168) = 0;
      *(undefined4 *)(param_1 + 0x116c) = 0;
      *(undefined4 *)(param_1 + 0x1170) = 0;
      *(undefined4 *)(param_1 + 0x1174) = 0;
      *(undefined4 *)(param_1 + 0x1178) = 0;
      *(undefined4 *)(param_1 + 0x117c) = 0;
      *(undefined4 *)(param_1 + 0x1180) = 0;
      *(undefined4 *)(param_1 + 0x1184) = 0;
      *(undefined4 *)(param_1 + 0x1188) = 0;
      *(undefined4 *)(param_1 + 0x118c) = 0;
      *(undefined4 *)(param_1 + 0x1190) = 0;
      *(undefined4 *)(param_1 + 0x1194) = 0x1010101;
      *(undefined4 *)(param_1 + 0x1198) = 0x1010101;
      *(undefined4 *)(param_1 + 0x119c) = 0xffffffff;
      *(undefined1 *)(param_1 + 0x11a0) = 0;
      *(undefined1 *)(param_1 + 0x11ac) = 0;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = _rand();
      *(char *)(param_1 + 0x11c2) = (char)iVar6;
      iVar6 = _rand();
      *(byte *)(param_1 + 0x11c3) = (byte)iVar6;
      puStack_98 = (undefined *)(*(byte *)(param_1 + 0x11c2) & 7);
      bVar4 = ~('\x01' << (sbyte)puStack_98) & (byte)iVar6 | '\0' << (sbyte)puStack_98;
      *(byte *)(param_1 + 0x11c3) = bVar4;
      *(byte *)(param_1 + 0x11c4) = *(byte *)(param_1 + 0x11c2) + bVar4 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      *(undefined1 *)(param_1 + 0x11c5) = 0;
      *(undefined4 *)(param_1 + 0x11c8) = 0xffffffff;
      NoOpMethod();
      iStack_94 = 0;
      do {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(0);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(0);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(0);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(0);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(0);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(1);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iStack_94 = iStack_94 + 0x224;
      } while (iStack_94 < 0x1120);
      puVar14 = (undefined4 *)(param_1 + 0x2384);
      for (iVar6 = 0x10; iVar8 = g_clientContext, iVar6 != 0; iVar6 = iVar6 + -1) {
        *puVar14 = 0xffffffff;
        puVar14 = puVar14 + 1;
      }
      pbVar12 = (byte *)(g_clientContext + 0x5b818);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = _rand();
      *pbVar12 = (byte)iVar6;
      iVar6 = _rand();
      bVar4 = *pbVar12;
      *(byte *)(iVar8 + 0x5b819) = (byte)iVar6;
      puStack_98 = (undefined *)(bVar4 & 7);
      bVar11 = ~('\x01' << (sbyte)puStack_98) & (byte)iVar6 | '\0' << (sbyte)puStack_98;
      *(byte *)(iVar8 + 0x5b819) = bVar11;
      *(byte *)(iVar8 + 0x5b81a) = bVar4 + bVar11 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = g_clientContext;
      *(undefined1 *)(param_1 + 0x11d0) = 0;
      *(undefined4 *)(param_1 + 0x11d4) = 0xffffffff;
      *(undefined1 *)(param_1 + 0x11d8) = 1;
      *(undefined4 *)(&DAT_006a64b0 + iVar6) = 0;
      *(undefined4 *)(&DAT_006a64b4 + iVar6) = 0xffffffff;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = _rand();
      *(char *)(param_1 + 0x22fc) = (char)iVar6;
      uVar7 = _rand();
      puStack_98 = (undefined *)(uVar7 & 0x800000ff);
      if ((int)puStack_98 < 0) {
        puStack_98 = (undefined *)(((uint)(puStack_98 + -1) | 0xffffff00) + 1);
      }
      *(byte *)(param_1 + 0x22fd) = (byte)puStack_98;
      bVar4 = '\x01' << (*(byte *)(param_1 + 0x22fc) & 7);
      bVar4 = ~bVar4 & (byte)puStack_98 | bVar4;
      *(byte *)(param_1 + 0x22fd) = bVar4;
      *(byte *)(param_1 + 0x22fe) = *(byte *)(param_1 + 0x22fc) + bVar4 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      FUN_004d09c0();
      *(undefined4 *)(&DAT_006a64b8 + g_clientContext) = 0;
      _DAT_00e98abc = timeGetTime();
      DAT_00e98ab8 = 1;
      puVar14 = &DAT_00e98ac0;
      for (iVar6 = 0x400; iVar6 != 0; iVar6 = iVar6 + -1) {
        *puVar14 = 0;
        puVar14 = puVar14 + 1;
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(0xffffffff);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      puStack_98 = (undefined *)0xc300;
      FUN_004e8a70();
      if (apuStack_90[0] != DAT_00e9af14) {
        FUN_004e87b0(&DAT_00e9af10,&puStack_98,apuStack_90[0]);
      }
      puStack_98 = (undefined *)0xc306;
      FUN_004e8a70();
      if (apuStack_90[0] != DAT_00e9af14) {
        FUN_004e87b0(&DAT_00e9af10,&puStack_98,apuStack_90[0]);
      }
      puStack_98 = (undefined *)0xc40b;
      FUN_004e8a70();
      if (apuStack_90[0] != DAT_00e9af14) {
        FUN_004e87b0(&DAT_00e9af10,&puStack_98,apuStack_90[0]);
      }
      puStack_98 = (undefined *)0x8005;
      FUN_004e86f0(apuStack_90);
      puStack_98 = (undefined *)0x8006;
      FUN_004e86f0(apuStack_90);
      puStack_98 = (undefined *)0xc306;
      FUN_004e86f0(apuStack_90);
      puStack_98 = (undefined *)0xc400;
      FUN_004e86f0(apuStack_90);
      puStack_98 = (undefined *)0xc401;
      FUN_004e86f0(apuStack_90);
      puStack_98 = (undefined *)0x8403;
      FUN_004e86f0(apuStack_90);
      puStack_98 = (undefined *)0x8405;
      FUN_004e86f0(apuStack_90);
      puStack_98 = (undefined *)0xc409;
      FUN_004e86f0(apuStack_90);
      FUN_00438360();
      iVar6 = g_clientContext;
      pbVar12 = &DAT_006a9b6c + g_clientContext;
      *(undefined1 *)(param_1 + 0x2382) = 0;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((byte)(*pbVar12 + (&DAT_006a9b6d)[iVar6] + -0x34) == (&DAT_006a9b6e)[iVar6]) {
        cStack_99 = '\x01' - (((byte)(&DAT_006a9b6d)[iVar6] >> (*pbVar12 & 7) & 1) != 1);
      }
      else {
        g_valueGuardTamperFlag = 1;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        cStack_99 = '\0';
      }
      iVar8 = _rand();
      (&DAT_006a9b6f)[iVar6] = (byte)iVar8;
      iVar8 = _rand();
      bVar4 = (&DAT_006a9b6f)[iVar6];
      (&DAT_006a9b70)[iVar6] = (byte)iVar8;
      puStack_98 = (undefined *)(bVar4 & 7);
      bVar11 = ~('\x01' << (sbyte)puStack_98) & (byte)iVar8 |
               (cStack_99 != '\0') << (sbyte)puStack_98;
      (&DAT_006a9b70)[iVar6] = bVar11;
      (&DAT_006a9b71)[iVar6] = bVar4 + bVar11 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = g_clientContext;
      pbVar12 = &DAT_006a9b72 + g_clientContext;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar8 = _rand();
      *pbVar12 = (byte)iVar8;
      iVar8 = _rand();
      bVar4 = *pbVar12;
      (&DAT_006a9b73)[iVar6] = (byte)iVar8;
      puStack_98 = (undefined *)(bVar4 & 7);
      bVar11 = ~('\x01' << (sbyte)puStack_98) & (byte)iVar8 | '\0' << (sbyte)puStack_98;
      (&DAT_006a9b73)[iVar6] = bVar11;
      (&DAT_006a9b74)[iVar6] = bVar4 + bVar11 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = g_clientContext;
      *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 0;
      *(undefined4 *)(&DAT_005f376c + iVar6) = 0;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar8 = _rand();
      (&DAT_006aa62b)[iVar6] = (byte)iVar8;
      iVar8 = _rand();
      bVar4 = (&DAT_006aa62b)[iVar6];
      (&DAT_006aa62c)[iVar6] = (byte)iVar8;
      puStack_98 = (undefined *)(bVar4 & 7);
      bVar11 = ~('\x01' << (sbyte)puStack_98) & (byte)iVar8 | '\0' << (sbyte)puStack_98;
      (&DAT_006aa62c)[iVar6] = bVar11;
      (&DAT_006aa62d)[iVar6] = bVar4 + bVar11 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      *(undefined4 *)(param_1 + 0x23cc) = 0xffffffff;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = _rand();
      *(char *)(param_1 + 0x23d1) = (char)iVar6;
      iVar6 = _rand();
      *(byte *)(param_1 + 0x23d2) = (byte)iVar6;
      bVar4 = *(byte *)(param_1 + 0x23d1) & 7;
      bVar4 = ~('\x01' << bVar4) & (byte)iVar6 | '\0' << bVar4;
      *(byte *)(param_1 + 0x23d2) = bVar4;
      *(byte *)(param_1 + 0x23d3) = *(byte *)(param_1 + 0x23d1) + bVar4 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = g_clientContext;
      pbVar12 = &DAT_006a9b6f + g_clientContext;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar8 = _rand();
      *pbVar12 = (byte)iVar8;
      uVar7 = _rand();
      puStack_98 = (undefined *)(uVar7 & 0x800000ff);
      if ((int)puStack_98 < 0) {
        puStack_98 = (undefined *)(((uint)(puStack_98 + -1) | 0xffffff00) + 1);
      }
      bVar4 = *pbVar12;
      (&DAT_006a9b70)[iVar6] = (byte)puStack_98;
      bVar11 = '\x01' << (bVar4 & 7);
      bVar11 = ~bVar11 & (byte)puStack_98 | bVar11;
      (&DAT_006a9b70)[iVar6] = bVar11;
      (&DAT_006a9b71)[iVar6] = bVar4 + bVar11 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = g_clientContext;
      pbVar12 = &DAT_006a9b72 + g_clientContext;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar8 = _rand();
      *pbVar12 = (byte)iVar8;
      iVar8 = _rand();
      bVar4 = *pbVar12;
      (&DAT_006a9b73)[iVar6] = (byte)iVar8;
      puStack_98 = (undefined *)(bVar4 & 7);
      bVar11 = ~('\x01' << (sbyte)puStack_98) & (byte)iVar8 | '\0' << (sbyte)puStack_98;
      (&DAT_006a9b73)[iVar6] = bVar11;
      (&DAT_006a9b74)[iVar6] = bVar4 + bVar11 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = _rand();
      *(char *)(param_1 + 0x23d4) = (char)iVar6;
      iVar6 = _rand();
      *(byte *)(param_1 + 0x23d5) = (byte)iVar6;
      bVar4 = '\x01' << (*(byte *)(param_1 + 0x23d4) & 7);
      bVar4 = ~bVar4 & (byte)iVar6 | bVar4;
      *(byte *)(param_1 + 0x23d5) = bVar4;
      *(byte *)(param_1 + 0x23d6) = *(byte *)(param_1 + 0x23d4) + bVar4 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      return;
    }
  } while( true );
}

