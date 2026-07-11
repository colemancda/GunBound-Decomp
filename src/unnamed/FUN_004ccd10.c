/* FUN_004ccd10 - 0x004ccd10 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x004cdb8e) */
/* WARNING: Removing unreachable block (ram,0x004cdb98) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004ccd10(int *param_1)

{
  undefined2 *puVar1;
  int *piVar2;
  undefined *puVar3;
  char cVar4;
  undefined2 uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  undefined4 uVar9;
  char *pcVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  uint uVar14;
  byte bVar15;
  byte bVar16;
  char *pcVar17;
  int unaff_EBX;
  code *pcVar18;
  byte *pbVar19;
  undefined4 *unaff_FS_OFFSET;
  bool bVar20;
  undefined4 uVar21;
  undefined4 uVar22;
  undefined *local_71c;
  char local_715;
  uint local_714;
  int *local_710;
  int local_70c;
  int local_708;
  int local_704;
  undefined1 local_700 [8];
  char local_6f8 [128];
  undefined1 local_678 [20];
  undefined *local_664;
  undefined1 local_458;
  undefined1 local_454 [20];
  undefined *local_440;
  undefined1 local_230 [20];
  undefined *local_21c;
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  local_c = *unaff_FS_OFFSET;
  puStack_8 = &LAB_0053e001;
  *unaff_FS_OFFSET = &local_c;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0xffffffff);
  pcVar18 = (code *)LeaveCriticalSection;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0xffffffff);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = g_clientContext;
  *(undefined1 *)((int)param_1 + 0x11c5) = 0;
  (&DAT_006a64a4)[iVar7] = 0;
  *(undefined4 *)(&DAT_006a64a8 + iVar7) = 0xffffffff;
  *(undefined4 *)(&DAT_006a64ac + iVar7) = 1;
  pbVar19 = &DAT_005f3770 + iVar7;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = _rand();
  *pbVar19 = (byte)iVar6;
  iVar6 = _rand();
  (&DAT_005f3771)[iVar7] = (byte)iVar6;
  bVar15 = '\x01' << (*pbVar19 & 7);
  bVar15 = ~bVar15 & (byte)iVar6 | bVar15;
  (&DAT_005f3771)[iVar7] = bVar15;
  (&DAT_005f3772)[iVar7] = bVar15 + *pbVar19 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = g_clientContext;
  pbVar19 = (byte *)(g_clientContext + 0x62140);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = _rand();
  *pbVar19 = (byte)iVar6;
  iVar6 = _rand();
  bVar15 = *pbVar19;
  *(byte *)(iVar7 + 0x62141) = (byte)iVar6;
  local_714 = bVar15 & 7;
  bVar15 = *pbVar19;
  bVar16 = ~('\x01' << (sbyte)local_714) & (byte)iVar6 | '\0' << (sbyte)local_714;
  *(byte *)(iVar7 + 0x62141) = bVar16;
  *(byte *)(iVar7 + 0x62142) = bVar16 + bVar15 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = g_clientContext;
  pbVar19 = (byte *)(g_clientContext + 0x62143);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = _rand();
  *pbVar19 = (byte)iVar6;
  iVar6 = _rand();
  bVar15 = *pbVar19;
  *(byte *)(iVar7 + 0x62144) = (byte)iVar6;
  local_714 = bVar15 & 7;
  bVar15 = *pbVar19;
  bVar16 = ~('\x01' << (sbyte)local_714) & (byte)iVar6 | '\0' << (sbyte)local_714;
  *(byte *)(iVar7 + 0x62144) = bVar16;
  *(byte *)(iVar7 + 0x62145) = bVar16 + bVar15 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = g_clientContext;
  pbVar19 = (byte *)(g_clientContext + 0x62146);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = _rand();
  *pbVar19 = (byte)iVar6;
  iVar6 = _rand();
  bVar15 = *pbVar19;
  *(byte *)(iVar7 + 0x62147) = (byte)iVar6;
  local_714 = bVar15 & 7;
  bVar15 = *pbVar19;
  bVar16 = ~('\x01' << (sbyte)local_714) & (byte)iVar6 | '\0' << (sbyte)local_714;
  *(byte *)(iVar7 + 0x62147) = bVar16;
  *(byte *)(iVar7 + 0x62148) = bVar16 + bVar15 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = g_clientContext;
  pbVar19 = &DAT_006a9b6f + g_clientContext;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = _rand();
  *pbVar19 = (byte)iVar6;
  iVar6 = _rand();
  bVar15 = *pbVar19;
  (&DAT_006a9b70)[iVar7] = (byte)iVar6;
  local_714 = bVar15 & 7;
  bVar15 = *pbVar19;
  bVar16 = ~('\x01' << (sbyte)local_714) & (byte)iVar6 | '\0' << (sbyte)local_714;
  (&DAT_006a9b70)[iVar7] = bVar16;
  (&DAT_006a9b71)[iVar7] = bVar16 + bVar15 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = g_clientContext;
  pbVar19 = &DAT_006a9b72 + g_clientContext;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = _rand();
  *pbVar19 = (byte)iVar6;
  iVar6 = _rand();
  bVar15 = *pbVar19;
  (&DAT_006a9b73)[iVar7] = (byte)iVar6;
  local_714 = bVar15 & 7;
  bVar15 = *pbVar19;
  bVar16 = ~('\x01' << (sbyte)local_714) & (byte)iVar6 | '\0' << (sbyte)local_714;
  (&DAT_006a9b73)[iVar7] = bVar16;
  (&DAT_006a9b74)[iVar7] = bVar16 + bVar15 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = g_clientContext;
  pbVar19 = &DAT_006aa625 + g_clientContext;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = _rand();
  *pbVar19 = (byte)iVar6;
  iVar6 = _rand();
  bVar15 = *pbVar19;
  (&DAT_006aa626)[iVar7] = (byte)iVar6;
  local_714 = bVar15 & 7;
  bVar15 = *pbVar19;
  bVar16 = ~('\x01' << (sbyte)local_714) & (byte)iVar6 | '\0' << (sbyte)local_714;
  (&DAT_006aa626)[iVar7] = bVar16;
  (&DAT_006aa627)[iVar7] = bVar16 + bVar15 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = LoadGameDataFiles(g_clientContext);
  if (iVar7 != 0) {
    ShowErrorDialog(1);
    goto LAB_004ce3a6;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = PeekPacketChecksumState();
  local_715 = iVar7 != 3;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (local_715 == '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_71c = &DAT_0067e5f4 + g_clientContext;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    local_715 = iVar7 <= iVar6;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (local_715 == '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar9 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      cVar4 = PacketChecksumGreaterEqual(&DAT_0067e3d0 + g_clientContext,uVar9);
      if (cVar4 == '\0') goto LAB_004cd6de;
    }
    cVar4 = FUN_0040b390(g_clientContext + 0x3b6c4,g_clientContext + 0x3b49c);
    iVar7 = DAT_007934e8;
    if ((cVar4 != '\0') && (*(char *)((int)param_1 + 0x2382) == '\0')) {
      *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x4200;
      *(undefined4 *)(iVar7 + 0x44d0) = 6;
      cVar4 = FUN_0040b410(&DAT_0067e5f4 + g_clientContext,&DAT_0067e3d0 + g_clientContext);
      iVar7 = DAT_007934e8;
      if (cVar4 == '\0') {
        *(undefined1 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = 0;
      }
      else {
        *(undefined1 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = 1;
      }
      *(int *)(iVar7 + 0x44d0) = *(int *)(iVar7 + 0x44d0) + 1;
      FUN_004d25e0();
      SendOutgoingPacket();
      *(undefined1 *)((int)param_1 + 0x2382) = 1;
      pcVar18 = (code *)LeaveCriticalSection;
    }
  }
  else {
    local_710 = param_1 + 0x477;
    local_708 = 0;
    local_70c = 0;
    local_704 = 0;
    do {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar7 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (1 < iVar7) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(0);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar8 = GetPlayerRecordBySlot(g_clientContext);
        local_714 = uVar8;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar7 = PeekPacketChecksumState();
        EncodeOutgoingPacketField(iVar7 + 4);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_458 = 0;
        local_664 = (undefined *)0x0;
        EncodeOutgoingPacketField(0);
        local_4 = 0;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(500);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar7 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_71c = (undefined *)(local_704 + 0x5113c + g_clientContext);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_71c = (undefined *)PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar9 = EncodeChecksumDeltaMul(local_678,local_230,local_71c + iVar7);
        local_4 = 1;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_71c = (undefined *)PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeChecksumDeltaDiv(uVar9,local_454,local_71c);
        local_4 = 2;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar9 = PeekPacketChecksumState();
        EncodeOutgoingPacketField(uVar9);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        puVar3 = local_440;
        local_4 = 1;
        if (local_440 != (undefined *)0x0) {
          ScrambleChecksumGuardBytes();
          local_71c = puVar3;
          FUN_0040b540(local_700);
          uVar8 = local_714;
        }
        puVar3 = local_21c;
        local_4 = 0;
        if (local_21c != (undefined *)0x0) {
          ScrambleChecksumGuardBytes();
          local_71c = puVar3;
          FUN_0040b540(local_700);
          uVar8 = local_714;
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar7 = PeekPacketChecksumState();
        iVar6 = PeekPacketChecksumState();
        EncodeOutgoingPacketField(iVar6 + iVar7);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar9 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_71c = (undefined *)PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        FUN_004368f0(local_71c,uVar9,4);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar9 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = uVar8 + 0xae15;
        iVar7 = iVar6;
        pcVar10 = (char *)GetLocalizedString(&g_localizedStringTable,0x274);
        _sprintf(local_6f8,pcVar10,iVar7,uVar9);
        (**(code **)(*param_1 + 0x28))(local_6f8,4,3);
        FUN_00438360();
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar7 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (local_708 == iVar7) {
          iVar7 = *(int *)(g_clientContext + 0x44e60) + 1;
          pcVar10 = (char *)GetLocalizedString(&g_localizedStringTable,5000);
          _sprintf(local_6f8,pcVar10,iVar6,iVar7);
          iVar6 = DAT_007934e8;
          *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
          *(undefined2 *)(iVar6 + 0x4d4) = 0x5010;
          *(undefined1 *)(iVar6 + 0x4d6) = 0xff;
          iVar7 = *(int *)(iVar6 + 0x44d0);
          *(int *)(iVar6 + 0x44d0) = iVar7 + 1;
          pcVar10 = local_6f8;
          do {
            cVar4 = *pcVar10;
            pcVar10 = pcVar10 + 1;
          } while (cVar4 != '\0');
          *(char *)(iVar7 + 0x4d1 + iVar6) = (char)pcVar10 - ((char)local_6f8 + '\x01');
          iVar7 = *(int *)(iVar6 + 0x44d0);
          *(int *)(iVar6 + 0x44d0) = iVar7 + 1;
          pcVar10 = local_6f8;
          do {
            cVar4 = *pcVar10;
            pcVar10 = pcVar10 + 1;
          } while (cVar4 != '\0');
          uVar8 = (int)pcVar10 - (int)(local_6f8 + 1);
          uVar13 = ((int)uVar8 < 0) - 1 & uVar8;
          pcVar10 = local_6f8;
          pcVar17 = (char *)(iVar7 + 0x4d1 + iVar6);
          for (uVar14 = uVar13 >> 2; uVar14 != 0; uVar14 = uVar14 - 1) {
            *(undefined4 *)pcVar17 = *(undefined4 *)pcVar10;
            pcVar10 = pcVar10 + 4;
            pcVar17 = pcVar17 + 4;
          }
          for (uVar13 = uVar13 & 3; uVar13 != 0; uVar13 = uVar13 - 1) {
            *pcVar17 = *pcVar10;
            pcVar10 = pcVar10 + 1;
            pcVar17 = pcVar17 + 1;
          }
          *(int *)(iVar6 + 0x44d0) = *(int *)(iVar6 + 0x44d0) + uVar8;
          FUN_004d25e0();
          SendOutgoingPacket();
        }
        puVar3 = local_664;
        local_4 = 0xffffffff;
        if (local_664 != (undefined *)0x0) {
          ScrambleChecksumGuardBytes();
          local_71c = puVar3;
          FUN_0040b540(local_700);
        }
      }
      local_704 = local_704 + 0x1120;
      local_708 = local_708 + 1;
      local_70c = local_70c + 0x224;
      local_710 = local_710 + 0x89;
      pcVar18 = (code *)LeaveCriticalSection;
    } while (local_704 < 0x8900);
  }
LAB_004cd6de:
  FUN_004d09c0();
  iVar7 = g_clientContext;
  *(undefined1 *)(param_1 + 0x468) = 0;
  if (*(int *)(iVar7 + 0x621e4) != 0) {
    uVar8 = *(uint *)(*(int *)(iVar7 + 0x621e4) + 8) & 7;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_71c = (undefined *)PeekPacketChecksumState();
    (*pcVar18)(&DAT_005a9068);
    param_1[uVar8 + 0x44d] = param_1[uVar8 + 0x44d] + param_1[0x429] / unaff_EBX;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar18)(&DAT_005a9068);
    if (param_1[uVar8 + 0x455] < param_1[0x429] / (int)local_71c) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_71c = (undefined *)PeekPacketChecksumState();
      (*pcVar18)(&DAT_005a9068);
      param_1[uVar8 + 0x455] = param_1[0x429] / (int)local_71c;
    }
    param_1[uVar8 + 0x45d] = param_1[uVar8 + 0x45d] + 1;
  }
  cVar4 = FUN_00439e40((char)param_1[0x428]);
  if (cVar4 == '\x01') {
    iVar7 = param_1[0x428];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    (*pcVar18)(&DAT_005a9068);
    if (iVar6 == iVar7) {
      if (*(int *)(g_clientContext + 0x621e0) != 0) {
        Replay_AppendEvent(0x8402);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar5 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar5;
        g_replayEventCursor = g_replayEventCursor + 2;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar5 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar5;
        g_replayEventCursor = g_replayEventCursor + 2;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar7 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        (&g_replayEventBuffer)[g_replayEventCursor] = '\x01' - (iVar7 != 1);
        g_replayEventCursor = g_replayEventCursor + 1;
        Replay_FlushEvent();
        iVar7 = *(int *)(g_clientContext + 0x621e0);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = _rand();
        *(byte *)(iVar7 + 0x8ba8) = (byte)iVar6;
        iVar6 = _rand();
        bVar15 = *(byte *)(iVar7 + 0x8ba8);
        *(byte *)(iVar7 + 0x8ba9) = (byte)iVar6;
        local_71c = (undefined *)(bVar15 & 7);
        bVar16 = ~('\x01' << (sbyte)local_71c) & (byte)iVar6 | '\0' << (sbyte)local_71c;
        *(byte *)(iVar7 + 0x8ba9) = bVar16;
        *(byte *)(iVar7 + 0x8baa) = bVar15 + bVar16 + -0x34;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar7 = *(int *)(g_clientContext + 0x621e0);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = _rand();
        *(byte *)(iVar7 + 0x8bb1) = (byte)iVar6;
        iVar6 = _rand();
        bVar15 = *(byte *)(iVar7 + 0x8bb1);
        *(byte *)(iVar7 + 0x8bb2) = (byte)iVar6;
        local_71c = (undefined *)(bVar15 & 7);
        bVar16 = ~('\x01' << (sbyte)local_71c) & (byte)iVar6 | '\0' << (sbyte)local_71c;
        *(byte *)(iVar7 + 0x8bb2) = bVar16;
        *(byte *)(iVar7 + 0x8bb3) = bVar15 + bVar16 + -0x34;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar7 = *(int *)(g_clientContext + 0x621e0);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = _rand();
        *(byte *)(iVar7 + 0x8bab) = (byte)iVar6;
        iVar6 = _rand();
        bVar15 = *(byte *)(iVar7 + 0x8bab);
        *(byte *)(iVar7 + 0x8bac) = (byte)iVar6;
        bVar16 = '\x01' << (bVar15 & 7);
        bVar16 = ~bVar16 & (byte)iVar6 | bVar16;
        *(byte *)(iVar7 + 0x8bac) = bVar16;
        *(byte *)(iVar7 + 0x8bad) = bVar15 + bVar16 + -0x34;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      Replay_AppendEvent(0xc301);
      (&g_replayEventBuffer)[g_replayEventCursor] = 1;
      puVar1 = (undefined2 *)(&DAT_00e9aacd + g_replayEventCursor);
      g_replayEventCursor = g_replayEventCursor + 1;
      *puVar1 = 0xffff;
      g_replayEventCursor = g_replayEventCursor + 2;
      FUN_0041f200(0);
      Replay_FlushEvent();
    }
    goto LAB_004ce3a6;
  }
  if (*(int *)(g_clientContext + 0x621e0) != 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar7 = PeekPacketChecksumState();
    local_715 = 4 < iVar7;
    (*pcVar18)(&DAT_005a9068);
    if (((local_715 == '\0') &&
        ((cVar4 = PeekPacketChecksumBool(), cVar4 != '\x01' || (*(char *)(g_clientContext + 0x45127) != '\x03')))
        ) || (*(short *)(*(int *)(g_clientContext + 0x621e0) + 0xbfbc) != 0)) {
      CreateButtonWidget(&DAT_00e9be90,0,0x12,0x3fa,s_b_play_weapon3_00554144,0x58,0x232,0x25,0x26,0
                         ,0);
      if (*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) {
        piVar2 = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10);
        uVar8 = piVar2[2];
        while (uVar8 < 0x13) {
          if (uVar8 == 0x12) {
            (**(code **)(*piVar2 + 4))(s_disable_00551e68);
            break;
          }
          piVar2 = (int *)piVar2[4];
          uVar8 = piVar2[2];
        }
      }
      cVar4 = PeekPacketChecksumBool();
      if (cVar4 == '\x01') {
        iVar7 = *(int *)(g_clientContext + 0x621e0);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = _rand();
        *(byte *)(iVar7 + 0x8bba) = (byte)iVar6;
        iVar6 = _rand();
        bVar15 = *(byte *)(iVar7 + 0x8bba);
        *(byte *)(iVar7 + 0x8bbb) = (byte)iVar6;
        local_71c = (undefined *)(bVar15 & 7);
        bVar16 = ~('\x01' << (sbyte)local_71c) & (byte)iVar6 | '\0' << (sbyte)local_71c;
        *(byte *)(iVar7 + 0x8bbb) = bVar16;
        *(byte *)(iVar7 + 0x8bbc) = bVar15 + bVar16 + -0x34;
        (*pcVar18)(&DAT_005a9068);
        cVar4 = PeekPacketChecksumBool();
        if (cVar4 == '\x01') {
          FUN_00406300(1);
          FUN_00405fb0();
          uVar22 = 6;
          pcVar10 = s_b_play_weapon1_00554164;
          uVar21 = 0x3e9;
          uVar9 = 1;
        }
        else {
          FUN_00406300(1);
          FUN_00405fb0();
          uVar22 = 0x2e;
          pcVar10 = s_b_play_weapon2_00554154;
          uVar21 = 0x3ea;
          uVar9 = 2;
        }
        CreateButtonWidget(&DAT_00e9be90,0,uVar9,uVar21,pcVar10,uVar22,0x232,0x25,0x26,1,0);
        pcVar18 = (code *)LeaveCriticalSection;
      }
    }
    else {
      cVar4 = PeekPacketChecksumBool();
      if (cVar4 == '\0') {
        CreateButtonWidget(&DAT_00e9be90,0,0x12,0x3fa,s_b_play_weapon3_00554144,0x58,0x232,0x25,0x26
                           ,1,0);
        FUN_00406300(1);
        pcVar18 = (code *)LeaveCriticalSection;
      }
    }
  }
  if (*(int *)(g_clientContext + 0x621e0) != 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar7 = PeekPacketChecksumState();
    (*pcVar18)(&DAT_005a9068);
    if (param_1[0x428] == iVar7) {
      local_71c = (undefined *)CONCAT31(SUBFIELD(local_71c,1,undefined3),*(int *)(g_clientContext + 0xebef0) == -0x18);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeGuardedBool(local_71c);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      pcVar18 = (code *)LeaveCriticalSection;
    }
  }
  iVar7 = g_clientContext;
  pcVar10 = (char *)(param_1[0x428] + 0x1194 + (int)param_1);
  if (*pcVar10 != '\0') {
    *pcVar10 = '\0';
    _DAT_00e9b4e8 = *(undefined2 *)(iVar7 + 0x4591c + param_1[0x428] * 2);
    pcVar10 = (char *)(param_1[0x428] * 0xd + 0x457f1 + iVar7);
    pcVar17 = &DAT_00e9b4fd;
    do {
      cVar4 = *pcVar10;
      pcVar10 = pcVar10 + 1;
      *pcVar17 = cVar4;
      pcVar17 = pcVar17 + 1;
    } while (cVar4 != '\0');
    pcVar10 = (char *)(param_1[0x428] * 9 + 0x457a9 + iVar7);
    pcVar17 = &DAT_00e9b4ea;
    do {
      cVar4 = *pcVar10;
      pcVar10 = pcVar10 + 1;
      *pcVar17 = cVar4;
      pcVar17 = pcVar17 + 1;
    } while (cVar4 != '\0');
    uVar9 = *(undefined4 *)(iVar7 + 0x4593c + param_1[0x428] * 4);
    pcVar10 = (char *)GetLocalizedString(&g_localizedStringTable,3000);
    _sprintf(&DAT_00e9b50a,pcVar10,uVar9);
    uVar8 = *(uint *)(g_clientContext + 0x4597c + param_1[0x428] * 4);
    if (999 < uVar8) {
      uVar8 = 999;
    }
    uVar9 = *(undefined4 *)(g_clientContext + 0x4599c + param_1[0x428] * 4);
    pcVar10 = (char *)GetLocalizedString(&g_localizedStringTable,0xbb9);
    _sprintf(&DAT_00e9b58a,pcVar10,uVar8,uVar9);
    iVar7 = *(int *)(g_clientContext + 0x472fc + param_1[0x428] * 4);
    uVar8 = *(int *)(g_clientContext + 0x4731c + param_1[0x428] * 4) + iVar7;
    if (uVar8 == 0) {
      uVar8 = 1;
    }
    uVar8 = (uint)(iVar7 * 100) / uVar8;
    pcVar10 = (char *)GetLocalizedString(&g_localizedStringTable,0xbba);
    _sprintf(&DAT_00e9b60a,pcVar10,uVar8);
    uVar8 = *(uint *)(g_clientContext + 0x4735c + param_1[0x428] * 4);
    if (uVar8 == 0) {
      uVar8 = 1;
    }
    uVar8 = *(uint *)(g_clientContext + 0x4733c + param_1[0x428] * 4) / uVar8;
    pcVar10 = (char *)GetLocalizedString(&g_localizedStringTable,0xbbb);
    _sprintf(&DAT_00e9b68a,pcVar10,uVar8);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar11 = PeekPacketChecksumState();
    (*pcVar18)(&DAT_005a9068);
    iVar12 = FUN_00420650(g_clientContext,param_1[0x428],iVar11);
    iVar7 = iVar11 + param_1[0x428] * 0x14;
    iVar6 = *(int *)(g_clientContext + 0x459bc + iVar7 * 4);
    uVar8 = *(int *)(g_clientContext + 0x45c3c + iVar7 * 4) + iVar6;
    if (uVar8 == 0) {
      uVar8 = 1;
    }
    uVar8 = (uint)(iVar6 * 100) / uVar8;
    uVar9 = GetLocalizedString(&g_localizedStringTable,iVar11 + 1000);
    pcVar10 = (char *)GetLocalizedString(&g_localizedStringTable,0xbbc);
    _sprintf(&DAT_00e9b70a,pcVar10,uVar9,uVar8);
    iVar7 = iVar12 + param_1[0x428] * 0x14;
    iVar6 = *(int *)(g_clientContext + 0x459bc + iVar7 * 4);
    uVar8 = *(int *)(g_clientContext + 0x45c3c + iVar7 * 4) + iVar6;
    if (uVar8 == 0) {
      uVar8 = 1;
    }
    uVar8 = (uint)(iVar6 * 100) / uVar8;
    uVar9 = GetLocalizedString(&g_localizedStringTable,iVar12 + 1000);
    pcVar10 = (char *)GetLocalizedString(&g_localizedStringTable,0xbbd);
    _sprintf(&DAT_00e9b78a,pcVar10,uVar9,uVar8);
    _DAT_00e9b810 = 800;
    _DAT_00e9b80c = 0xfffffff6;
    DAT_00e9b80a = 1;
    param_1[0x8f1] = 0x50;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00406300(param_1[0x428] == iVar7);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (param_1[0x428] == iVar7) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar7 = PeekPacketChecksumState();
    local_715 = iVar7 == 2;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (local_715 == '\0') goto LAB_004ce0c7;
    uVar9 = 1;
  }
  else {
LAB_004ce0c7:
    uVar9 = 0;
  }
  FUN_00406300(uVar9);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = g_clientContext;
  if (((param_1[0x428] == iVar6) && (*(int *)(g_clientContext + 0xf0374) != -1)) &&
     ((char)param_1[0x42f] != '\0')) {
    FUN_004cbda0(param_1,*(int *)(g_clientContext + 0xf0374));
    iVar7 = g_clientContext;
    *(undefined4 *)(g_clientContext + 0xf0374) = 0xffffffff;
  }
  *(undefined4 *)(iVar7 + 0x5b81c) = 0;
  *(undefined4 *)(iVar7 + 0x5b820) = 0;
  *(undefined4 *)(iVar7 + 0x5b824) = 0;
  *(undefined4 *)(iVar7 + 0x5b828) = 0;
  *(undefined4 *)(iVar7 + 0x5b82c) = 0;
  *(undefined4 *)(iVar7 + 0x5b830) = 0;
  *(undefined4 *)(iVar7 + 0x5b834) = 0;
  *(undefined4 *)(iVar7 + 0x5b838) = 0;
  *(undefined4 *)(iVar7 + 0x5b83c) = 0;
  *(undefined4 *)(iVar7 + 0x5b840) = 0;
  *(undefined4 *)(iVar7 + 0x5b844) = 0;
  *(undefined4 *)(iVar7 + 0x5b848) = 0;
  *(undefined4 *)(iVar7 + 0x5b84c) = 0;
  *(undefined4 *)(iVar7 + 0x5b850) = 0;
  *(undefined4 *)(iVar7 + 0x5b854) = 0;
  *(undefined4 *)(iVar7 + 0x5b858) = 0;
  iVar7 = *(int *)(*(int *)(&DAT_006a7f8c + iVar7) + 0x1c);
  uVar8 = *(uint *)(iVar7 + 4);
  while (uVar8 < 0x186ab) {
    if (uVar8 == 0x186aa) {
      iVar7 = *(int *)(iVar7 + 0x10);
      bVar20 = true;
      if (*(int *)(iVar7 + 8) == 0) goto LAB_004ce1a4;
      break;
    }
    iVar7 = *(int *)(iVar7 + 0x1c);
    uVar8 = *(uint *)(iVar7 + 4);
  }
  goto LAB_004ce1bd;
  while( true ) {
    iVar7 = *(int *)(iVar7 + 0x10);
    bVar20 = *(int *)(iVar7 + 8) == 0;
    if (!bVar20) break;
LAB_004ce1a4:
    if (bVar20) {
      FUN_004ac180();
      break;
    }
  }
LAB_004ce1bd:
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  AcquireSoundChannel(0);
  local_71c = (undefined *)0x8005;
  FUN_004e8a70();
  if (local_714 != DAT_00e9af14) {
    FUN_004e87b0(&DAT_00e9af10,&local_71c,local_714);
  }
  local_71c = (undefined *)0x8006;
  FUN_004e8a70();
  if (local_714 != DAT_00e9af14) {
    FUN_004e87b0(&DAT_00e9af10,&local_71c,local_714);
  }
  local_71c = (undefined *)0xc306;
  FUN_004e8a70();
  if (local_714 != DAT_00e9af14) {
    FUN_004e87b0(&DAT_00e9af10,&local_71c,local_714);
  }
  local_71c = (undefined *)0xc400;
  FUN_004e8a70();
  if (local_714 != DAT_00e9af14) {
    FUN_004e87b0(&DAT_00e9af10,&local_71c,local_714);
  }
  local_71c = (undefined *)0xc401;
  FUN_004e8a70();
  if (local_714 != DAT_00e9af14) {
    FUN_004e87b0(&DAT_00e9af10,&local_71c,local_714);
  }
  local_71c = (undefined *)0x8403;
  FUN_004e8a70();
  if (local_714 != DAT_00e9af14) {
    FUN_004e87b0(&DAT_00e9af10,&local_71c,local_714);
  }
  local_71c = (undefined *)0x8405;
  FUN_004e8a70();
  if (local_714 != DAT_00e9af14) {
    FUN_004e87b0(&DAT_00e9af10,&local_71c,local_714);
  }
  local_71c = (undefined *)0xc409;
  FUN_004e8a70();
  if (local_714 != DAT_00e9af14) {
    FUN_004e87b0(&DAT_00e9af10,&local_71c,local_714);
  }
LAB_004ce3a6:
  *unaff_FS_OFFSET = local_c;
  return;
}

