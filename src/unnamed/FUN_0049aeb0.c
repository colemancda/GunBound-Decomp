/* FUN_0049aeb0 - 0x0049aeb0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void __thiscall FUN_0049aeb0(int param_1,int param_2)

{
  uint *puVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  bool bVar8;
  char cVar9;
  undefined4 uVar10;
  uint uVar11;
  byte bVar12;
  int iVar13;
  int iVar14;
  byte bVar15;
  uint uVar16;
  byte bVar17;
  int iVar18;
  int iVar19;
  byte *pbVar20;
  undefined4 *unaff_FS_OFFSET;
  uint local_15b0;
  uint local_15ac;
  uint local_15a8 [2];
  uint local_15a0;
  int local_159c;
  int local_1598;
  int local_1594;
  int local_1590;
  int local_158c;
  uint local_1588 [2];
  uint local_1580 [2];
  int local_1578;
  undefined1 local_1574 [20];
  int local_1560;
  undefined1 local_1350 [20];
  int local_133c;
  undefined1 local_112c [20];
  int local_1118;
  undefined1 local_f08 [20];
  uint local_ef4;
  undefined1 local_ce4 [20];
  int local_cd0;
  undefined1 local_ac0 [20];
  uint local_aac;
  undefined1 local_89c [20];
  int local_888;
  undefined1 local_678 [20];
  uint local_664;
  undefined1 local_454 [20];
  int local_440;
  undefined1 local_230 [20];
  uint local_21c;
  undefined4 uStack_10;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00540324;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uStack_10 = 0x49aecf;
  local_158c = param_1 + 0x40;
  bVar8 = false;
  bVar7 = false;
  bVar6 = false;
  bVar5 = false;
  bVar4 = false;
  bVar3 = false;
  bVar2 = false;
  EncodeChecksumDeltaShr(local_158c,local_1574,8);
  local_4 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_1590 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if (local_1560 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_1588);
  }
  local_1594 = param_1 + 0x264;
  EncodeChecksumDeltaShr(local_1594,local_1574,8);
  local_4 = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_159c = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if (local_1560 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_1588);
  }
  uVar10 = EncodeChecksumPairDiff(local_158c,local_1350,param_1 + 0x488);
  local_4 = 2;
  EncodeChecksumDeltaShr(uVar10,local_1574,8);
  SUBFIELD(local_4,0,undefined1) = 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_1580[0] = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),2);
  if (local_1560 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_1588);
  }
  local_4 = 0xffffffff;
  if (local_133c != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_1588);
  }
  uVar10 = EncodeChecksumPairDiff(local_1594,local_1574,param_1 + 0x6ac);
  local_4 = 4;
  EncodeChecksumDeltaShr(uVar10,local_1350,8);
  SUBFIELD(local_4,0,undefined1) = 5;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar11 = PeekPacketChecksumState();
  local_1588[0] = uVar11;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),4);
  if (local_133c != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_15a8);
  }
  local_4 = 0xffffffff;
  if (local_1560 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_15a8);
  }
  uVar16 = (int)(local_1580[0] - local_1590) >> 0x1f;
  iVar13 = (local_1580[0] - local_1590 ^ uVar16) - uVar16;
  uVar16 = (int)(uVar11 - local_159c) >> 0x1f;
  iVar18 = (uVar11 - local_159c ^ uVar16) - uVar16;
  iVar14 = iVar13 + 1;
  iVar19 = iVar18 + 1;
  local_1594 = 0;
  if (iVar19 < iVar14) {
    iVar14 = (int)((local_159c - uVar11) * 0x10000) / iVar14;
    local_159c = uVar11 << 0x10;
    local_1590 = (uint)((int)local_1580[0] <= local_1590) * 2 + -1;
    local_15a8[0] = iVar13 + param_2;
    if (0 < (int)local_15a8[0]) {
      local_158c = iVar14 * param_2;
      local_1598 = param_1 + 0x15c0;
      local_1578 = local_1590 * param_2;
      local_15ac = local_1580[0];
      do {
        iVar18 = local_1598;
        local_159c = local_159c + local_158c;
        local_15a0 = local_159c >> 0x10;
        local_15b0 = local_15ac;
        if ((!bVar2) && (iVar19 = FUN_004510f0(local_15ac), iVar19 != 0)) {
          EncodeChecksumDeltaAdd(iVar18,local_89c,param_2);
          local_4 = 6;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar19 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (iVar19 < 0x14) {
LAB_0049b2e9:
            EncodeChecksumDeltaAdd(iVar18,local_ce4,param_2);
            local_4 = 8;
            bVar4 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar19 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (iVar19 < 0x14) {
              uVar10 = 0x14;
            }
            else {
              EncodeChecksumDeltaAdd(iVar18,local_454,param_2);
              local_4 = 9;
              bVar4 = true;
              bVar3 = true;
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              uVar10 = PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            }
          }
          else {
            EncodeChecksumDeltaAdd(iVar18,local_112c,param_2);
            local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),7);
            bVar5 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar19 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (iVar19 < 0x65) goto LAB_0049b2e9;
            uVar10 = 100;
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(uVar10);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_4 = 8;
          if ((bVar3) && (bVar3 = false, local_440 != 0)) {
            ScrambleChecksumGuardBytes();
            TreeLowerBound(local_1588);
          }
          local_4 = 7;
          if ((bVar4) && (bVar4 = false, local_cd0 != 0)) {
            ScrambleChecksumGuardBytes();
            TreeLowerBound(local_1588);
          }
          local_4 = 6;
          if ((bVar5) && (bVar5 = false, local_1118 != 0)) {
            ScrambleChecksumGuardBytes();
            TreeLowerBound(local_1588);
          }
          local_4 = 0xffffffff;
          if (local_888 != 0) {
            ScrambleChecksumGuardBytes();
            TreeLowerBound(local_1588);
          }
          bVar2 = true;
        }
        cVar9 = DecodeGuardedBool();
        if (cVar9 != '\0') {
          iVar18 = FUN_00451030(local_15ac);
          *(int *)(param_1 + 0xf48) = iVar18;
          if (iVar18 != 0) {
            *(undefined4 *)(param_1 + 0xf50) = 0;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar18 = _rand();
            *(byte *)(param_1 + 0xf4c) = (byte)iVar18;
            iVar18 = _rand();
            bVar15 = *(byte *)(param_1 + 0xf4c);
            *(byte *)(param_1 + 0xf4d) = (byte)iVar18;
            bVar17 = '\x01' << (bVar15 & 7);
            bVar17 = ~bVar17 & (byte)iVar18 | bVar17;
            *(byte *)(param_1 + 0xf4d) = bVar17;
            *(byte *)(param_1 + 0xf4e) = bVar15 + bVar17 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar18 = g_clientContext;
            pbVar20 = (byte *)(g_clientContext + 0x62140);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar19 = _rand();
            *pbVar20 = (byte)iVar19;
            iVar19 = _rand();
            bVar15 = *pbVar20;
            *(byte *)(iVar18 + 0x62141) = (byte)iVar19;
            bVar17 = '\x01' << (bVar15 & 7);
            bVar17 = ~bVar17 & (byte)iVar19 | bVar17;
            *(byte *)(iVar18 + 0x62141) = bVar17;
            *(byte *)(iVar18 + 0x62142) = bVar15 + bVar17 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
        }
        cVar9 = PeekPacketChecksumBool();
        if ((cVar9 == '\0') && (iVar18 = FUN_004511b0(local_15ac), iVar18 != 0)) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar18 = _rand();
          *(byte *)(param_1 + 0x3918) = (byte)iVar18;
          iVar18 = _rand();
          bVar15 = *(byte *)(param_1 + 0x3918);
          *(byte *)(param_1 + 0x3919) = (byte)iVar18;
          bVar17 = '\x01' << (bVar15 & 7);
          bVar17 = ~bVar17 & (byte)iVar18 | bVar17;
          *(byte *)(param_1 + 0x3919) = bVar17;
          *(byte *)(param_1 + 0x391a) = bVar15 + bVar17 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar10 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        FUN_00436dc0(local_15ac,local_15a0,uVar10);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar18 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar11 = local_15ac;
        if (iVar18 == 0) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar18 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar19 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar11 = local_15ac;
          FUN_00436bd0(local_15ac - (iVar19 >> 8),local_15a0 - (iVar18 >> 8),
                       *(undefined4 *)(param_1 + 0x1e50));
        }
        cVar9 = PeekPacketChecksumBool();
        uVar16 = local_15a0;
        if (cVar9 != '\0') {
          FUN_00436ec0(uVar11,local_15a0);
        }
        if ((((-1 < (int)uVar11) && ((int)uVar11 < *(int *)(&DAT_006a7720 + g_clientContext))) &&
            (-1 < (int)uVar16)) &&
           (((int)uVar16 < *(int *)(&DAT_006a7724 + g_clientContext) &&
            (*(char *)(*(int *)(&DAT_006a7720 + g_clientContext) * uVar16 +
                       *(int *)(&DAT_006a773c + g_clientContext) + uVar11) != '\0')))) {
          FUN_00458920(&local_15b0,&local_15a0,local_1580[0],local_1594,local_1590,iVar14,local_159c
                       ,1,0);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b0 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15a0 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b0);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15a0);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar18 = _rand();
          *(char *)(param_1 + 0xf45) = (char)iVar18;
          local_15a8[0] = _rand();
          local_15a8[0] = local_15a8[0] & 0x800000ff;
          if ((int)local_15a8[0] < 0) {
            local_15a8[0] = (local_15a8[0] - 1 | 0xffffff00) + 1;
          }
          bVar15 = *(byte *)(param_1 + 0xf45);
          *(byte *)(param_1 + 0xf46) = (byte)local_15a8[0];
          bVar17 = '\x01' << (bVar15 & 7);
          bVar12 = ~bVar17 & (byte)local_15a8[0];
LAB_0049bfbb:
          *(byte *)(param_1 + 0xf47) = bVar15 + (bVar12 | bVar17) + -0x34;
          *(byte *)(param_1 + 0xf46) = bVar12 | bVar17;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (DAT_0079352a != '\0') {
            Replay_AppendEvent(0xf002);
            (&g_replayEventBuffer)[g_replayEventCursor] = *(undefined1 *)(param_1 + 8);
            puVar1 = (uint *)(&DAT_00e9aacd + g_replayEventCursor);
            g_replayEventCursor = g_replayEventCursor + 1;
            *puVar1 = local_15b0;
            puVar1 = (uint *)(&DAT_00e9aad0 + g_replayEventCursor);
            g_replayEventCursor = g_replayEventCursor + 4;
            *puVar1 = local_15a0;
            g_replayEventCursor = g_replayEventCursor + 4;
            Replay_FlushEvent();
          }
          break;
        }
        local_1594 = local_1594 + param_2;
        local_15ac = uVar11 + local_1578;
      } while (local_1594 < (int)local_15a8[0]);
    }
  }
  else {
    iVar19 = (int)((local_1590 - local_1580[0]) * 0x10000) / iVar19;
    local_1590 = (uint)((int)uVar11 <= local_159c) * 2 + -1;
    iVar18 = iVar18 + param_2;
    if (0 < iVar18) {
      local_158c = iVar19 * param_2;
      local_1598 = param_1 + 0x15c0;
      local_1578 = local_1590 * param_2;
      local_159c = local_1580[0] << 0x10;
      local_15ac = uVar11;
      do {
        local_159c = local_159c + local_158c;
        local_15b0 = local_159c >> 0x10;
        local_15a0 = local_15ac;
        if ((!bVar2) && (iVar13 = FUN_004510f0(local_15b0), iVar14 = local_1598, iVar13 != 0)) {
          local_15a8[0] = EncodeChecksumDeltaAdd(local_1598,local_230,param_2);
          local_4 = 10;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15a8[0] = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if ((int)local_15a8[0] < 0x14) {
LAB_0049b9fa:
            local_15a8[0] = EncodeChecksumDeltaAdd(iVar14,local_ac0,param_2);
            local_4 = 0xc;
            bVar7 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_15a8[0] = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if ((int)local_15a8[0] < 0x14) {
              uVar10 = 0x14;
            }
            else {
              EncodeChecksumDeltaAdd(iVar14,local_f08,param_2);
              local_4 = 0xd;
              bVar7 = true;
              bVar6 = true;
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              uVar10 = PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            }
          }
          else {
            local_15a8[0] = EncodeChecksumDeltaAdd(iVar14,local_678,param_2);
            local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0xb);
            bVar8 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_15a8[0] = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if ((int)local_15a8[0] < 0x65) goto LAB_0049b9fa;
            uVar10 = 100;
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(uVar10);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar11 = local_ef4;
          local_4 = 0xc;
          if ((bVar6) && (bVar6 = false, local_ef4 != 0)) {
            ScrambleChecksumGuardBytes();
            local_15a8[0] = uVar11;
            TreeLowerBound(local_1580);
          }
          uVar11 = local_aac;
          local_4 = 0xb;
          if ((bVar7) && (bVar7 = false, local_aac != 0)) {
            ScrambleChecksumGuardBytes();
            local_15a8[0] = uVar11;
            TreeLowerBound(local_1580);
          }
          uVar11 = local_664;
          local_4 = 10;
          if ((bVar8) && (bVar8 = false, local_664 != 0)) {
            ScrambleChecksumGuardBytes();
            local_15a8[0] = uVar11;
            TreeLowerBound(local_1580);
          }
          uVar11 = local_21c;
          local_4 = 0xffffffff;
          if (local_21c != 0) {
            ScrambleChecksumGuardBytes();
            local_15a8[0] = uVar11;
            TreeLowerBound(local_1580);
          }
          bVar2 = true;
        }
        cVar9 = DecodeGuardedBool();
        if (cVar9 != '\0') {
          iVar14 = FUN_00451030(local_15b0);
          *(int *)(param_1 + 0xf48) = iVar14;
          if (iVar14 != 0) {
            *(undefined4 *)(param_1 + 0xf50) = 0;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar14 = _rand();
            *(byte *)(param_1 + 0xf4c) = (byte)iVar14;
            iVar14 = _rand();
            bVar15 = *(byte *)(param_1 + 0xf4c);
            *(byte *)(param_1 + 0xf4d) = (byte)iVar14;
            bVar17 = '\x01' << (bVar15 & 7);
            bVar17 = ~bVar17 & (byte)iVar14 | bVar17;
            *(byte *)(param_1 + 0xf4d) = bVar17;
            *(byte *)(param_1 + 0xf4e) = bVar15 + bVar17 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar14 = g_clientContext;
            pbVar20 = (byte *)(g_clientContext + 0x62140);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar13 = _rand();
            *pbVar20 = (byte)iVar13;
            local_15a8[0] = _rand();
            local_15a8[0] = local_15a8[0] & 0x800000ff;
            if ((int)local_15a8[0] < 0) {
              local_15a8[0] = (local_15a8[0] - 1 | 0xffffff00) + 1;
            }
            bVar15 = *pbVar20;
            *(byte *)(iVar14 + 0x62141) = (byte)local_15a8[0];
            bVar17 = '\x01' << (bVar15 & 7);
            bVar17 = ~bVar17 & (byte)local_15a8[0] | bVar17;
            *(byte *)(iVar14 + 0x62141) = bVar17;
            *(byte *)(iVar14 + 0x62142) = bVar15 + bVar17 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
        }
        cVar9 = PeekPacketChecksumBool();
        if ((cVar9 == '\0') && (iVar14 = FUN_004511b0(local_15b0), iVar14 != 0)) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar14 = _rand();
          *(byte *)(param_1 + 0x3918) = (byte)iVar14;
          iVar14 = _rand();
          bVar15 = *(byte *)(param_1 + 0x3918);
          *(byte *)(param_1 + 0x3919) = (byte)iVar14;
          bVar17 = '\x01' << (bVar15 & 7);
          bVar17 = ~bVar17 & (byte)iVar14 | bVar17;
          *(byte *)(param_1 + 0x3919) = bVar17;
          *(byte *)(param_1 + 0x391a) = bVar15 + bVar17 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar10 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        FUN_00436dc0(local_15b0,local_15ac,uVar10);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar14 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar11 = local_15b0;
        if (iVar14 == 0) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar14 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15a8[0] = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar11 = local_15b0;
          FUN_00436bd0(local_15b0 - ((int)local_15a8[0] >> 8),local_15ac - (iVar14 >> 8),
                       *(undefined4 *)(param_1 + 0x1e50));
        }
        cVar9 = PeekPacketChecksumBool();
        uVar16 = local_15ac;
        if (cVar9 != '\0') {
          FUN_00436ec0(uVar11,local_15ac);
        }
        if ((((-1 < (int)uVar11) && ((int)uVar11 < *(int *)(&DAT_006a7720 + g_clientContext))) &&
            (-1 < (int)uVar16)) &&
           (((int)uVar16 < *(int *)(&DAT_006a7724 + g_clientContext) &&
            (*(char *)(*(int *)(&DAT_006a7720 + g_clientContext) * uVar16 +
                       *(int *)(&DAT_006a773c + g_clientContext) + uVar11) != '\0')))) {
          FUN_00458a00(&local_15b0,&local_15a0,local_1588[0],local_1594,local_1590,iVar19,local_159c
                       ,1,0);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b0 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15a0 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b0);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15a0);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar18 = _rand();
          *(char *)(param_1 + 0xf45) = (char)iVar18;
          local_1588[0] = _rand();
          local_1588[0] = local_1588[0] & 0x800000ff;
          if ((int)local_1588[0] < 0) {
            local_1588[0] = (local_1588[0] - 1 | 0xffffff00) + 1;
          }
          bVar15 = *(byte *)(param_1 + 0xf45);
          *(byte *)(param_1 + 0xf46) = (byte)local_1588[0];
          bVar17 = '\x01' << (bVar15 & 7);
          bVar12 = ~bVar17 & (byte)local_1588[0];
          goto LAB_0049bfbb;
        }
        local_1594 = local_1594 + param_2;
        local_15ac = uVar16 + local_1578;
      } while (local_1594 < iVar18);
    }
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

