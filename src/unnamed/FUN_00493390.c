/* FUN_00493390 - 0x00493390 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void __thiscall FUN_00493390(int *param_1,int param_2)

{
  int *piVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  char cVar8;
  undefined4 uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  byte bVar15;
  uint uVar16;
  byte bVar17;
  byte *pbVar18;
  undefined4 *unaff_FS_OFFSET;
  int local_15ac;
  int local_159c;
  uint local_1598 [2];
  char local_158d;
  int *local_158c;
  int local_1588;
  int *local_1584;
  undefined1 local_1580 [8];
  int local_1578;
  undefined1 local_1574 [20];
  uint local_1560;
  undefined1 local_1350 [20];
  int local_133c;
  undefined1 local_112c [20];
  uint local_1118;
  undefined1 local_f08 [20];
  uint local_ef4;
  undefined1 local_ce4 [20];
  uint local_cd0;
  undefined1 local_ac0 [20];
  int local_aac;
  undefined1 local_89c [20];
  int local_888;
  undefined1 local_678 [20];
  int local_664;
  undefined1 local_454 [20];
  int local_440;
  undefined1 local_230 [20];
  uint local_21c;
  undefined4 uStack_10;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053d10a;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uStack_10 = 0x4933af;
  local_1584 = param_1 + 0x10;
  bVar7 = false;
  bVar6 = false;
  bVar5 = false;
  bVar4 = false;
  bVar3 = false;
  bVar2 = false;
  local_158d = '\0';
  EncodeChecksumDeltaShr(local_1584,local_1350,8);
  local_4 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_1588 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if (local_133c != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_1598);
  }
  EncodeChecksumDeltaShr(param_1 + 0x99,local_f08,8);
  local_4 = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_158c = (int *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if (local_ef4 != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_1598);
  }
  uVar9 = EncodeChecksumPairDiff(local_1584,local_454,param_1 + 0x122);
  local_4 = 2;
  EncodeChecksumDeltaShr(uVar9,local_89c,8);
  SUBFIELD(local_4,0,undefined1) = 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_1584 = (int *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),2);
  if (local_888 != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_1598);
  }
  local_4 = 0xffffffff;
  if (local_440 != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_1598);
  }
  uVar9 = EncodeChecksumPairDiff(param_1 + 0x99,local_678,param_1 + 0x1ab);
  local_4 = 4;
  EncodeChecksumDeltaShr(uVar9,local_ac0,8);
  SUBFIELD(local_4,0,undefined1) = 5;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_159c = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),4);
  if (local_aac != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_1598);
  }
  local_4 = 0xffffffff;
  if (local_664 != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_1598);
  }
  uVar16 = (int)local_1584 - local_1588 >> 0x1f;
  iVar13 = ((int)local_1584 - local_1588 ^ uVar16) - uVar16;
  uVar16 = local_159c - (int)local_158c >> 0x1f;
  iVar10 = (local_159c - (int)local_158c ^ uVar16) - uVar16;
  iVar14 = iVar13 + 1;
  iVar11 = iVar10 + 1;
  if (iVar11 < iVar14) {
    iVar10 = (int)local_158c - local_159c;
    if (local_1588 < (int)local_1584) {
      local_15ac = (int)local_1584 + -1;
      local_1578 = -1;
    }
    else {
      local_15ac = (int)local_1584 + 1;
      local_1578 = 1;
    }
    local_1598[0] = iVar13 + param_2;
    local_1588 = 0;
    if (0 < (int)local_1598[0]) {
      local_158c = param_1 + 0x570;
      local_1578 = local_1578 * param_2;
      local_1584 = (int *)(local_159c << 0x10);
      do {
        piVar1 = local_158c;
        local_1584 = (int *)((int)local_1584 + ((iVar10 * 0x10000) / iVar14) * param_2);
        local_159c = (int)local_1584 >> 0x10;
        if ((local_158d == '\0') && (iVar11 = FUN_004510f0(local_15ac), iVar11 != 0)) {
          EncodeChecksumDeltaAdd(piVar1,local_1574,param_2);
          local_4 = 6;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar11 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (iVar11 < 0x14) {
LAB_004937c8:
            EncodeChecksumDeltaAdd(piVar1,local_112c,param_2);
            local_4 = 8;
            bVar3 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar11 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (iVar11 < 0x14) {
              uVar9 = 0x14;
            }
            else {
              EncodeChecksumDeltaAdd(piVar1,local_1350,param_2);
              local_4 = 9;
              bVar3 = true;
              bVar2 = true;
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              uVar9 = PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            }
          }
          else {
            EncodeChecksumDeltaAdd(piVar1,local_ce4,param_2);
            local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),7);
            bVar4 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar11 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (iVar11 < 0x65) goto LAB_004937c8;
            uVar9 = 100;
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(uVar9);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_4 = 8;
          if ((bVar2) && (bVar2 = false, local_133c != 0)) {
            ScrambleChecksumGuardBytes();
            FUN_0040b540(local_1580);
          }
          local_4 = 7;
          if ((bVar3) && (bVar3 = false, local_1118 != 0)) {
            ScrambleChecksumGuardBytes();
            FUN_0040b540(local_1580);
          }
          local_4 = 6;
          if ((bVar4) && (bVar4 = false, local_cd0 != 0)) {
            ScrambleChecksumGuardBytes();
            FUN_0040b540(local_1580);
          }
          local_4 = 0xffffffff;
          if (local_1560 != 0) {
            ScrambleChecksumGuardBytes();
            FUN_0040b540(local_1580);
          }
          local_158d = '\x01';
        }
        cVar8 = FUN_00406860();
        if ((cVar8 != '\0') && ((char)param_1[0xfe7] == '\0')) {
          iVar11 = FUN_00451030(local_15ac);
          param_1[0x3d2] = iVar11;
          if (iVar11 != 0) {
            param_1[0x3d4] = 0;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar11 = _rand();
            *(byte *)(param_1 + 0x3d3) = (byte)iVar11;
            iVar11 = _rand();
            bVar15 = *(byte *)(param_1 + 0x3d3);
            *(byte *)((int)param_1 + 0xf4d) = (byte)iVar11;
            bVar17 = '\x01' << (bVar15 & 7);
            bVar17 = ~bVar17 & (byte)iVar11 | bVar17;
            *(byte *)((int)param_1 + 0xf4d) = bVar17;
            *(byte *)((int)param_1 + 0xf4e) = bVar15 + bVar17 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar11 = g_clientContext;
            pbVar18 = (byte *)(g_clientContext + 0x62140);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar13 = _rand();
            *pbVar18 = (byte)iVar13;
            iVar13 = _rand();
            bVar15 = *pbVar18;
            *(byte *)(iVar11 + 0x62141) = (byte)iVar13;
            bVar17 = '\x01' << (bVar15 & 7);
            bVar17 = ~bVar17 & (byte)iVar13 | bVar17;
            *(byte *)(iVar11 + 0x62141) = bVar17;
            *(byte *)(iVar11 + 0x62142) = bVar15 + bVar17 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
        }
        cVar8 = PeekPacketChecksumBool();
        if ((cVar8 == '\0') && (iVar11 = FUN_004511b0(local_15ac), iVar11 != 0)) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar11 = _rand();
          *(byte *)(param_1 + 0xe46) = (byte)iVar11;
          iVar11 = _rand();
          bVar15 = *(byte *)(param_1 + 0xe46);
          *(byte *)((int)param_1 + 0x3919) = (byte)iVar11;
          bVar17 = '\x01' << (bVar15 & 7);
          bVar17 = ~bVar17 & (byte)iVar11 | bVar17;
          *(byte *)((int)param_1 + 0x3919) = bVar17;
          *(byte *)((int)param_1 + 0x391a) = bVar15 + bVar17 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar9 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        FUN_00436dc0(local_15ac,local_159c,uVar9);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar11 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar11 == 0) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar11 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar13 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          FUN_00436bd0(local_15ac - (iVar13 >> 8),local_159c - (iVar11 >> 8),param_1[0x794]);
        }
        cVar8 = PeekPacketChecksumBool();
        if (cVar8 != '\0') {
          FUN_00436ec0(local_15ac,local_159c);
        }
        if (((char)param_1[0xfe7] == '\x01') &&
           (((((local_15ac < 0 || (*(int *)(&DAT_006a7720 + g_clientContext) <= local_15ac)) ||
              (local_159c < 0)) ||
             ((*(int *)(&DAT_006a7724 + g_clientContext) <= local_159c ||
              (*(char *)(*(int *)(&DAT_006a7720 + g_clientContext) * local_159c +
                         *(int *)(&DAT_006a773c + g_clientContext) + local_15ac) == '\0')))) ||
            (cVar8 = FUN_00450e10(local_159c), cVar8 != '\0')))) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15ac << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_159c << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15ac);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_159c);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar10 = _rand();
          *(char *)((int)param_1 + 0xf45) = (char)iVar10;
          local_1598[0] = _rand();
          local_1598[0] = local_1598[0] & 0x800000ff;
          if ((int)local_1598[0] < 0) {
            local_1598[0] = (local_1598[0] - 1 | 0xffffff00) + 1;
          }
          *(byte *)((int)param_1 + 0xf46) = (byte)local_1598[0];
          bVar15 = '\x01' << (*(byte *)((int)param_1 + 0xf45) & 7);
          bVar15 = ~bVar15 & (byte)local_1598[0] | bVar15;
          *(byte *)((int)param_1 + 0xf46) = bVar15;
          *(byte *)((int)param_1 + 0xf47) = *(byte *)((int)param_1 + 0xf45) + bVar15 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          break;
        }
        if ((((char)param_1[0xfe7] == '\0') && (-1 < local_15ac)) &&
           ((local_15ac < *(int *)(&DAT_006a7720 + g_clientContext) &&
            (((-1 < local_159c && (local_159c < *(int *)(&DAT_006a7724 + g_clientContext))) &&
             (*(char *)(*(int *)(&DAT_006a7720 + g_clientContext) * local_159c +
                        *(int *)(&DAT_006a773c + g_clientContext) + local_15ac) != '\0')))))) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15ac << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_159c << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15ac);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_159c);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          *(undefined1 *)(param_1 + 0xfe7) = 1;
          local_1598[0] = EncodeChecksumDeltaDiv(param_1 + 0x1ab,local_1574,2);
          local_4 = 10;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar9 = PeekPacketChecksumState();
          EncodeOutgoingPacketField(uVar9);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_4 = 0xffffffff;
          if (local_1560 != 0) {
            ScrambleChecksumGuardBytes();
            local_1598[0] = local_1560;
            FUN_0040b540(local_1580);
          }
          (**(code **)(*param_1 + 4))(s_special_005563c8);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar10 = _rand();
          *(char *)(param_1 + 0xe04) = (char)iVar10;
          iVar10 = _rand();
          *(byte *)((int)param_1 + 0x3811) = (byte)iVar10;
          bVar15 = *(byte *)(param_1 + 0xe04) & 7;
          bVar15 = ~('\x01' << bVar15) & (byte)iVar10 | '\0' << bVar15;
          *(byte *)((int)param_1 + 0x3811) = bVar15;
          *(byte *)((int)param_1 + 0x3812) = *(byte *)(param_1 + 0xe04) + bVar15 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (DAT_0079352a != '\0') {
            Replay_AppendEvent(0xf002);
            (&g_replayEventBuffer)[g_replayEventCursor] = (char)param_1[2];
LAB_004948b7:
            piVar1 = (int *)(&DAT_00e9aacd + g_replayEventCursor);
            g_replayEventCursor = g_replayEventCursor + 1;
            *piVar1 = local_15ac;
            piVar1 = (int *)(&DAT_00e9aad0 + g_replayEventCursor);
            g_replayEventCursor = g_replayEventCursor + 4;
            *piVar1 = local_159c;
            g_replayEventCursor = g_replayEventCursor + 4;
            Replay_FlushEvent();
          }
          break;
        }
        local_15ac = local_15ac + local_1578;
        local_1588 = local_1588 + param_2;
      } while (local_1588 < (int)local_1598[0]);
    }
  }
  else {
    iVar13 = local_1588 - (int)local_1584;
    local_1584 = (int *)((int)local_1584 << 0x10);
    if ((int)local_158c < local_159c) {
      local_159c = local_159c + -1;
      local_1578 = -1;
    }
    else {
      local_159c = local_159c + 1;
      local_1578 = 1;
    }
    iVar10 = iVar10 + param_2;
    local_1588 = 0;
    if (0 < iVar10) {
      local_158c = param_1 + 0x570;
      local_1578 = local_1578 * param_2;
      do {
        local_1584 = (int *)((int)local_1584 + ((iVar13 * 0x10000) / iVar11) * param_2);
        local_15ac = (int)local_1584 >> 0x10;
        if ((local_158d == '\0') &&
           (iVar14 = FUN_004510f0(local_15ac), piVar1 = local_158c, iVar14 != 0)) {
          local_1598[0] = EncodeChecksumDeltaAdd(local_158c,local_f08,param_2);
          local_4 = 0xb;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_1598[0] = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if ((int)local_1598[0] < 0x14) {
LAB_0049410b:
            local_1598[0] = EncodeChecksumDeltaAdd(piVar1,local_ce4,param_2);
            local_4 = 0xd;
            bVar6 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_1598[0] = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if ((int)local_1598[0] < 0x14) {
              uVar9 = 0x14;
            }
            else {
              EncodeChecksumDeltaAdd(piVar1,local_1574,param_2);
              local_4 = 0xe;
              bVar6 = true;
              bVar5 = true;
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              uVar9 = PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            }
          }
          else {
            local_1598[0] = EncodeChecksumDeltaAdd(piVar1,local_112c,param_2);
            local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0xc);
            bVar7 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_1598[0] = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if ((int)local_1598[0] < 0x65) goto LAB_0049410b;
            uVar9 = 100;
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(uVar9);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar16 = local_1560;
          local_4 = 0xd;
          if ((bVar5) && (bVar5 = false, local_1560 != 0)) {
            ScrambleChecksumGuardBytes();
            local_1598[0] = uVar16;
            FUN_0040b540(local_1580);
          }
          uVar16 = local_cd0;
          local_4 = 0xc;
          if ((bVar6) && (bVar6 = false, local_cd0 != 0)) {
            ScrambleChecksumGuardBytes();
            local_1598[0] = uVar16;
            FUN_0040b540(local_1580);
          }
          uVar16 = local_1118;
          local_4 = 0xb;
          if ((bVar7) && (bVar7 = false, local_1118 != 0)) {
            ScrambleChecksumGuardBytes();
            local_1598[0] = uVar16;
            FUN_0040b540(local_1580);
          }
          uVar16 = local_ef4;
          local_4 = 0xffffffff;
          if (local_ef4 != 0) {
            ScrambleChecksumGuardBytes();
            local_1598[0] = uVar16;
            FUN_0040b540(local_1580);
          }
          local_158d = '\x01';
        }
        cVar8 = FUN_00406860();
        if ((cVar8 != '\0') && ((char)param_1[0xfe7] == '\0')) {
          iVar14 = FUN_00451030(local_15ac);
          param_1[0x3d2] = iVar14;
          if (iVar14 != 0) {
            param_1[0x3d4] = 0;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar14 = _rand();
            *(byte *)(param_1 + 0x3d3) = (byte)iVar14;
            iVar14 = _rand();
            bVar15 = *(byte *)(param_1 + 0x3d3);
            *(byte *)((int)param_1 + 0xf4d) = (byte)iVar14;
            bVar17 = '\x01' << (bVar15 & 7);
            bVar17 = ~bVar17 & (byte)iVar14 | bVar17;
            *(byte *)((int)param_1 + 0xf4d) = bVar17;
            *(byte *)((int)param_1 + 0xf4e) = bVar15 + bVar17 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar14 = g_clientContext;
            pbVar18 = (byte *)(g_clientContext + 0x62140);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar12 = _rand();
            *pbVar18 = (byte)iVar12;
            local_1598[0] = _rand();
            local_1598[0] = local_1598[0] & 0x800000ff;
            if ((int)local_1598[0] < 0) {
              local_1598[0] = (local_1598[0] - 1 | 0xffffff00) + 1;
            }
            bVar15 = *pbVar18;
            *(byte *)(iVar14 + 0x62141) = (byte)local_1598[0];
            bVar17 = '\x01' << (bVar15 & 7);
            bVar17 = ~bVar17 & (byte)local_1598[0] | bVar17;
            *(byte *)(iVar14 + 0x62141) = bVar17;
            *(byte *)(iVar14 + 0x62142) = bVar15 + bVar17 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
        }
        cVar8 = PeekPacketChecksumBool();
        if ((cVar8 == '\0') && (iVar14 = FUN_004511b0(local_15ac), iVar14 != 0)) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar14 = _rand();
          *(byte *)(param_1 + 0xe46) = (byte)iVar14;
          iVar14 = _rand();
          bVar15 = *(byte *)(param_1 + 0xe46);
          *(byte *)((int)param_1 + 0x3919) = (byte)iVar14;
          bVar17 = '\x01' << (bVar15 & 7);
          bVar17 = ~bVar17 & (byte)iVar14 | bVar17;
          *(byte *)((int)param_1 + 0x3919) = bVar17;
          *(byte *)((int)param_1 + 0x391a) = bVar17 + bVar15 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_1598[0] = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        FUN_00436dc0(local_15ac,local_159c,local_1598[0]);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar14 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar14 == 0) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar14 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_1598[0] = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          FUN_00436bd0(local_15ac - ((int)local_1598[0] >> 8),local_159c - (iVar14 >> 8),
                       param_1[0x794]);
        }
        cVar8 = PeekPacketChecksumBool();
        if (cVar8 != '\0') {
          FUN_00436ec0(local_15ac,local_159c);
        }
        if (((((local_15ac < 0) || (*(int *)(&DAT_006a7720 + g_clientContext) <= local_15ac)) ||
             (local_159c < 0)) ||
            ((*(int *)(&DAT_006a7724 + g_clientContext) <= local_159c ||
             (*(char *)(local_159c * *(int *)(&DAT_006a7720 + g_clientContext) +
                        *(int *)(&DAT_006a773c + g_clientContext) + local_15ac) == '\0')))) &&
           ((char)param_1[0xfe7] == '\x01')) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15ac << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_159c << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15ac);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_159c);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar10 = _rand();
          *(char *)((int)param_1 + 0xf45) = (char)iVar10;
          iVar10 = _rand();
          *(byte *)((int)param_1 + 0xf46) = (byte)iVar10;
          bVar15 = '\x01' << (*(byte *)((int)param_1 + 0xf45) & 7);
          bVar15 = ~bVar15 & (byte)iVar10 | bVar15;
          *(byte *)((int)param_1 + 0xf46) = bVar15;
          *(byte *)((int)param_1 + 0xf47) = bVar15 + *(char *)((int)param_1 + 0xf45) + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          break;
        }
        if (((-1 < local_15ac) && (local_15ac < *(int *)(&DAT_006a7720 + g_clientContext))) &&
           ((-1 < local_159c &&
            (((local_159c < *(int *)(&DAT_006a7724 + g_clientContext) &&
              (*(char *)(local_159c * *(int *)(&DAT_006a7720 + g_clientContext) +
                         *(int *)(&DAT_006a773c + g_clientContext) + local_15ac) != '\0')) &&
             ((char)param_1[0xfe7] == '\0')))))) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15ac << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_159c << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15ac);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_159c);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          *(undefined1 *)(param_1 + 0xfe7) = 1;
          local_1598[0] = EncodeChecksumDeltaDiv(param_1 + 0x1ab,local_230,2);
          local_4 = 0xf;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar9 = PeekPacketChecksumState();
          EncodeOutgoingPacketField(uVar9);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_4 = 0xffffffff;
          if (local_21c != 0) {
            ScrambleChecksumGuardBytes();
            local_1598[0] = local_21c;
            FUN_0040b540(local_1580);
          }
          (**(code **)(*param_1 + 4))(s_special_005563c8);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar10 = _rand();
          *(char *)(param_1 + 0xe04) = (char)iVar10;
          iVar10 = _rand();
          *(byte *)((int)param_1 + 0x3811) = (byte)iVar10;
          bVar15 = ~('\x01' << (*(byte *)(param_1 + 0xe04) & 7)) & (byte)iVar10 |
                   '\0' << (*(byte *)(param_1 + 0xe04) & 7);
          *(byte *)((int)param_1 + 0x3811) = bVar15;
          *(byte *)((int)param_1 + 0x3812) = bVar15 + (char)param_1[0xe04] + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (DAT_0079352a != '\0') {
            Replay_AppendEvent(0xf002);
            (&g_replayEventBuffer)[g_replayEventCursor] = (char)param_1[2];
            goto LAB_004948b7;
          }
          break;
        }
        local_1588 = local_1588 + param_2;
        local_159c = local_159c + local_1578;
      } while (local_1588 < iVar10);
    }
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

