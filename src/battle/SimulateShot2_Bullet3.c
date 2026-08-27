/* SimulateShot2_Bullet3 - 0x00493390 in the original binary.
 *
 * RENAMED (2026-08-16, from FUN_00493390): CProjectile virtual slot 5
 * (SimulateProjectileFrame, base impl 0x455cc0) override for mobile type
 * 2's shot 2 (weapon index 1, texture bullet3s); vtable 0x5563a8, ctor
 * InitShot2_Bullet3 reached only through SpawnPrimaryShot's case 2. Type/role
 * CONFIRMED via vtable geometry (tools/projectile_class_map.py); the
 * mobile NAME is not confirmable (no mobile-type->name map in the repo).
 *
 * Body is a raw/near-verbatim Ghidra port, not hand-verified. See
 * src/README.md's "Raw/verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 22 argless PeekPacketChecksumState() calls and all 20 1-arg
 * EncodeOutgoingPacketField() calls (42 sites).  Same shape as the other
 * three Simulate overrides (Bullet11/13/14): the delta/pair helpers
 * return their arg2 scratch cell, so each Peek that follows one reads
 * that C local (local_1350 / local_f08 / local_89c / local_ac0 /
 * local_1574 / local_112c / local_ce4 / local_230).  The block-head peek
 * pairs and the lone Encodes use frame[0x38] = the C's local_158c =
 * param_1 + 0x570 (int index; == +0x15c0 bytes); the four-Encode groups
 * write the position cells param_1+0x10/0x99/0x3d5/0x45e (this =
 * frame[0x20]).  This variant also has two extra sites per copy: the
 * peeks at 0x493eb8/0x4947bb read the EncodeChecksumDeltaDiv scratch
 * (local_1574 / local_230 - captured by the C in local_1598[0]) and the
 * Encodes right after them write back into param_1+0x1ab (0x493ebe /
 * 0x4947c1, `dword ptr [esp+0x20] + 0x6ac`).
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void __thiscall SimulateShot2_Bullet3(int *param_1,int param_2)

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
  undefined1 local_1574 [548];
  undefined1 local_1350 [548];
  undefined1 local_112c [548];
  undefined1 local_f08 [548];
  undefined1 local_ce4 [548];
  undefined1 local_ac0 [548];
  undefined1 local_89c [548];
  undefined1 local_678 [548];
  undefined1 local_454 [548];
  undefined1 local_230 [548];
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
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_1588 = PeekPacketChecksumState((void *)(local_1350));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_4 = 0xffffffff;
  if ((*(int *)(local_1350 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_1350 + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_1598,&g_valueGuardMap);
  }
  EncodeChecksumDeltaShr(param_1 + 0x99,local_f08,8);
  local_4 = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_158c = (int *)PeekPacketChecksumState((void *)(local_f08));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_4 = 0xffffffff;
  if ((*(int *)(local_f08 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_f08 + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_1598,&g_valueGuardMap);
  }
  uVar9 = EncodeChecksumPairDiff(local_1584,local_454,param_1 + 0x122);
  local_4 = 2;
  EncodeChecksumDeltaShr(uVar9,local_89c,8);
  SUBFIELD(local_4,0,undefined1) = 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_1584 = (int *)PeekPacketChecksumState((void *)(local_89c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),2);
  if ((*(int *)(local_89c + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_89c + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_1598,&g_valueGuardMap);
  }
  local_4 = 0xffffffff;
  if ((*(int *)(local_454 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_454 + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_1598,&g_valueGuardMap);
  }
  uVar9 = EncodeChecksumPairDiff(param_1 + 0x99,local_678,param_1 + 0x1ab);
  local_4 = 4;
  EncodeChecksumDeltaShr(uVar9,local_ac0,8);
  SUBFIELD(local_4,0,undefined1) = 5;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_159c = PeekPacketChecksumState((void *)(local_ac0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),4);
  if ((*(int *)(local_ac0 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_ac0 + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_1598,&g_valueGuardMap);
  }
  local_4 = 0xffffffff;
  if ((*(int *)(local_678 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_678 + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_1598,&g_valueGuardMap);
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
        if ((local_158d == '\0') && (iVar11 = FUN_004510f0(local_15ac,(int)(&DAT_006a7f88 + g_clientContext)), iVar11 != 0)) {
          EncodeChecksumDeltaAdd(piVar1,local_1574,param_2);
          local_4 = 6;
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          iVar11 = PeekPacketChecksumState((void *)(local_1574));
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          if (iVar11 < 0x14) {
LAB_004937c8:
            EncodeChecksumDeltaAdd(piVar1,local_112c,param_2);
            local_4 = 8;
            bVar3 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
            iVar11 = PeekPacketChecksumState((void *)(local_112c));
            LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
            if (iVar11 < 0x14) {
              uVar9 = 0x14;
            }
            else {
              EncodeChecksumDeltaAdd(piVar1,local_1350,param_2);
              local_4 = 9;
              bVar3 = true;
              bVar2 = true;
              EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
              uVar9 = PeekPacketChecksumState((void *)(local_1350));
              LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
            }
          }
          else {
            EncodeChecksumDeltaAdd(piVar1,local_ce4,param_2);
            local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),7);
            bVar4 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
            iVar11 = PeekPacketChecksumState((void *)(local_ce4));
            LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
            if (iVar11 < 0x65) goto LAB_004937c8;
            uVar9 = 100;
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EncodeOutgoingPacketField((void *)(local_158c), uVar9);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          local_4 = 8;
          if ((bVar2) && (bVar2 = false, (*(int *)(local_1350 + 0x14)) != 0)) {
            ScrambleChecksumGuardBytes();
            TreeLowerBound(local_1580,&g_valueGuardMap);
          }
          local_4 = 7;
          if ((bVar3) && (bVar3 = false, (*(int *)(local_112c + 0x14)) != 0)) {
            ScrambleChecksumGuardBytes();
            TreeLowerBound(local_1580,&g_valueGuardMap);
          }
          local_4 = 6;
          if ((bVar4) && (bVar4 = false, (*(int *)(local_ce4 + 0x14)) != 0)) {
            ScrambleChecksumGuardBytes();
            TreeLowerBound(local_1580,&g_valueGuardMap);
          }
          local_4 = 0xffffffff;
          if ((*(int *)(local_1574 + 0x14)) != 0) {
            ScrambleChecksumGuardBytes(*(int *)(local_1574 + 0x14),&g_valueGuardKeyTable);
            TreeLowerBound(local_1580,&g_valueGuardMap);
          }
          local_158d = '\x01';
        }
        cVar8 = DecodeGuardedBool((byte *)(param_1 + 0x3d3));
        if ((cVar8 != '\0') && ((char)param_1[0xfe7] == '\0')) {
          iVar11 = FUN_00451030(local_15ac,(int)(&DAT_006a7f88 + g_clientContext));
          param_1[0x3d2] = iVar11;
          if (iVar11 != 0) {
            param_1[0x3d4] = 0;
            EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
            iVar11 = _rand();
            *(byte *)(param_1 + 0x3d3) = (byte)iVar11;
            iVar11 = _rand();
            bVar15 = *(byte *)(param_1 + 0x3d3);
            *(byte *)((int)param_1 + 0xf4d) = (byte)iVar11;
            bVar17 = '\x01' << (bVar15 & 7);
            bVar17 = ~bVar17 & (byte)iVar11 | bVar17;
            *(byte *)((int)param_1 + 0xf4d) = bVar17;
            *(byte *)((int)param_1 + 0xf4e) = bVar15 + bVar17 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
            iVar11 = g_clientContext;
            pbVar18 = (byte *)(g_clientContext + 0x62140);
            EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
            iVar13 = _rand();
            *pbVar18 = (byte)iVar13;
            iVar13 = _rand();
            bVar15 = *pbVar18;
            *(byte *)(iVar11 + 0x62141) = (byte)iVar13;
            bVar17 = '\x01' << (bVar15 & 7);
            bVar17 = ~bVar17 & (byte)iVar13 | bVar17;
            *(byte *)(iVar11 + 0x62141) = bVar17;
            *(byte *)(iVar11 + 0x62142) = bVar15 + bVar17 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          }
        }
        cVar8 = PeekPacketChecksumBool();
        if ((cVar8 == '\0') && (iVar11 = FUN_004511b0(local_15ac,(int)(&DAT_006a7f88 + g_clientContext)), iVar11 != 0)) {
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          iVar11 = _rand();
          *(byte *)(param_1 + 0xe46) = (byte)iVar11;
          iVar11 = _rand();
          bVar15 = *(byte *)(param_1 + 0xe46);
          *(byte *)((int)param_1 + 0x3919) = (byte)iVar11;
          bVar17 = '\x01' << (bVar15 & 7);
          bVar17 = ~bVar17 & (byte)iVar11 | bVar17;
          *(byte *)((int)param_1 + 0x3919) = bVar17;
          *(byte *)((int)param_1 + 0x391a) = bVar15 + bVar17 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        uVar9 = PeekPacketChecksumState((void *)(local_158c));
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        FUN_00436dc0(local_15ac,local_159c,uVar9);
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        iVar11 = PeekPacketChecksumState((void *)(local_158c));
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        if (iVar11 == 0) {
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          iVar11 = PeekPacketChecksumState((void *)(param_1 + 0x1ab));
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          iVar13 = PeekPacketChecksumState((void *)(param_1 + 0x122));
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          FUN_00436bd0(local_15ac - (iVar13 >> 8),local_159c - (iVar11 >> 8),param_1[0x794]);
        }
        cVar8 = PeekPacketChecksumBool();
        if (cVar8 != '\0') {
          FUN_00436ec0(local_15ac,local_159c);
        }
        if (((char)param_1[0xfe7] == '\x01') &&
           (((((local_15ac < 0 || (*(int *)(&g_nCameraBoundX + g_clientContext) <= local_15ac)) ||
              (local_159c < 0)) ||
             ((*(int *)(&g_nCameraBoundY + g_clientContext) <= local_159c ||
              (*(char *)(*(int *)(&g_nCameraBoundX + g_clientContext) * local_159c +
                         *(int *)(&DAT_006a773c + g_clientContext) + local_15ac) == '\0')))) ||
            (cVar8 = FUN_00450e10(local_159c), cVar8 != '\0')))) {
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EncodeOutgoingPacketField((void *)(param_1 + 0x10), local_15ac << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EncodeOutgoingPacketField((void *)(param_1 + 0x99), local_159c << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EncodeOutgoingPacketField((void *)(param_1 + 0x3d5), local_15ac);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EncodeOutgoingPacketField((void *)(param_1 + 0x45e), local_159c);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
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
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          break;
        }
        if ((((char)param_1[0xfe7] == '\0') && (-1 < local_15ac)) &&
           ((local_15ac < *(int *)(&g_nCameraBoundX + g_clientContext) &&
            (((-1 < local_159c && (local_159c < *(int *)(&g_nCameraBoundY + g_clientContext))) &&
             (*(char *)(*(int *)(&g_nCameraBoundX + g_clientContext) * local_159c +
                        *(int *)(&DAT_006a773c + g_clientContext) + local_15ac) != '\0')))))) {
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EncodeOutgoingPacketField((void *)(param_1 + 0x10), local_15ac << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EncodeOutgoingPacketField((void *)(param_1 + 0x99), local_159c << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EncodeOutgoingPacketField((void *)(param_1 + 0x3d5), local_15ac);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EncodeOutgoingPacketField((void *)(param_1 + 0x45e), local_159c);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          *(undefined1 *)(param_1 + 0xfe7) = 1;
          local_1598[0] = EncodeChecksumDeltaDiv(param_1 + 0x1ab,local_1574,2);
          local_4 = 10;
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          uVar9 = PeekPacketChecksumState((void *)(local_1598[0]));
          EncodeOutgoingPacketField((void *)(param_1 + 0x1ab), uVar9);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          local_4 = 0xffffffff;
          if ((*(int *)(local_1574 + 0x14)) != 0) {
            ScrambleChecksumGuardBytes(*(int *)(local_1574 + 0x14),&g_valueGuardKeyTable);
            local_1598[0] = (*(int *)(local_1574 + 0x14));
            TreeLowerBound(local_1580,&g_valueGuardMap);
          }
          (**(code **)(*param_1 + 4))(s_special_005563c8);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          iVar10 = _rand();
          *(char *)(param_1 + 0xe04) = (char)iVar10;
          iVar10 = _rand();
          *(byte *)((int)param_1 + 0x3811) = (byte)iVar10;
          bVar15 = *(byte *)(param_1 + 0xe04) & 7;
          bVar15 = ~('\x01' << bVar15) & (byte)iVar10 | '\0' << bVar15;
          *(byte *)((int)param_1 + 0x3811) = bVar15;
          *(byte *)((int)param_1 + 0x3812) = *(byte *)(param_1 + 0xe04) + bVar15 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          if (DAT_0079352a != '\0') {
            QueueBroadcastEvent(0xf002,(int)&g_replayContext);
            (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = (char)param_1[2];
LAB_004948b7:
            piVar1 = (int *)(&DAT_00e9aacd + g_dwBroadcastEventCursor);
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
            *piVar1 = local_15ac;
            piVar1 = (int *)(&DAT_00e9aad0 + g_dwBroadcastEventCursor);
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
            *piVar1 = local_159c;
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
            BroadcastQueuedEvent((int)&g_replayContext);
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
           (iVar14 = FUN_004510f0(local_15ac,(int)(&DAT_006a7f88 + g_clientContext)), piVar1 = local_158c, iVar14 != 0)) {
          local_1598[0] = EncodeChecksumDeltaAdd(local_158c,local_f08,param_2);
          local_4 = 0xb;
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          local_1598[0] = PeekPacketChecksumState((void *)(local_f08));
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          if ((int)local_1598[0] < 0x14) {
LAB_0049410b:
            local_1598[0] = EncodeChecksumDeltaAdd(piVar1,local_ce4,param_2);
            local_4 = 0xd;
            bVar6 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
            local_1598[0] = PeekPacketChecksumState((void *)(local_ce4));
            LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
            if ((int)local_1598[0] < 0x14) {
              uVar9 = 0x14;
            }
            else {
              EncodeChecksumDeltaAdd(piVar1,local_1574,param_2);
              local_4 = 0xe;
              bVar6 = true;
              bVar5 = true;
              EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
              uVar9 = PeekPacketChecksumState((void *)(local_1574));
              LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
            }
          }
          else {
            local_1598[0] = EncodeChecksumDeltaAdd(piVar1,local_112c,param_2);
            local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0xc);
            bVar7 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
            local_1598[0] = PeekPacketChecksumState((void *)(local_112c));
            LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
            if ((int)local_1598[0] < 0x65) goto LAB_0049410b;
            uVar9 = 100;
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EncodeOutgoingPacketField((void *)(local_158c), uVar9);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          uVar16 = (*(int *)(local_1574 + 0x14));
          local_4 = 0xd;
          if ((bVar5) && (bVar5 = false, (*(int *)(local_1574 + 0x14)) != 0)) {
            ScrambleChecksumGuardBytes();
            local_1598[0] = uVar16;
            TreeLowerBound(local_1580,&g_valueGuardMap);
          }
          uVar16 = (*(int *)(local_ce4 + 0x14));
          local_4 = 0xc;
          if ((bVar6) && (bVar6 = false, (*(int *)(local_ce4 + 0x14)) != 0)) {
            ScrambleChecksumGuardBytes();
            local_1598[0] = uVar16;
            TreeLowerBound(local_1580,&g_valueGuardMap);
          }
          uVar16 = (*(int *)(local_112c + 0x14));
          local_4 = 0xb;
          if ((bVar7) && (bVar7 = false, (*(int *)(local_112c + 0x14)) != 0)) {
            ScrambleChecksumGuardBytes();
            local_1598[0] = uVar16;
            TreeLowerBound(local_1580,&g_valueGuardMap);
          }
          uVar16 = (*(int *)(local_f08 + 0x14));
          local_4 = 0xffffffff;
          if ((*(int *)(local_f08 + 0x14)) != 0) {
            ScrambleChecksumGuardBytes(*(int *)(local_f08 + 0x14),&g_valueGuardKeyTable);
            local_1598[0] = uVar16;
            TreeLowerBound(local_1580,&g_valueGuardMap);
          }
          local_158d = '\x01';
        }
        cVar8 = DecodeGuardedBool((byte *)(param_1 + 0x3d3));
        if ((cVar8 != '\0') && ((char)param_1[0xfe7] == '\0')) {
          iVar14 = FUN_00451030(local_15ac,(int)(&DAT_006a7f88 + g_clientContext));
          param_1[0x3d2] = iVar14;
          if (iVar14 != 0) {
            param_1[0x3d4] = 0;
            EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
            iVar14 = _rand();
            *(byte *)(param_1 + 0x3d3) = (byte)iVar14;
            iVar14 = _rand();
            bVar15 = *(byte *)(param_1 + 0x3d3);
            *(byte *)((int)param_1 + 0xf4d) = (byte)iVar14;
            bVar17 = '\x01' << (bVar15 & 7);
            bVar17 = ~bVar17 & (byte)iVar14 | bVar17;
            *(byte *)((int)param_1 + 0xf4d) = bVar17;
            *(byte *)((int)param_1 + 0xf4e) = bVar15 + bVar17 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
            iVar14 = g_clientContext;
            pbVar18 = (byte *)(g_clientContext + 0x62140);
            EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
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
            LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          }
        }
        cVar8 = PeekPacketChecksumBool();
        if ((cVar8 == '\0') && (iVar14 = FUN_004511b0(local_15ac,(int)(&DAT_006a7f88 + g_clientContext)), iVar14 != 0)) {
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          iVar14 = _rand();
          *(byte *)(param_1 + 0xe46) = (byte)iVar14;
          iVar14 = _rand();
          bVar15 = *(byte *)(param_1 + 0xe46);
          *(byte *)((int)param_1 + 0x3919) = (byte)iVar14;
          bVar17 = '\x01' << (bVar15 & 7);
          bVar17 = ~bVar17 & (byte)iVar14 | bVar17;
          *(byte *)((int)param_1 + 0x3919) = bVar17;
          *(byte *)((int)param_1 + 0x391a) = bVar17 + bVar15 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        local_1598[0] = PeekPacketChecksumState((void *)(local_158c));
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        FUN_00436dc0(local_15ac,local_159c,local_1598[0]);
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        iVar14 = PeekPacketChecksumState((void *)(local_158c));
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        if (iVar14 == 0) {
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          iVar14 = PeekPacketChecksumState((void *)(param_1 + 0x1ab));
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          local_1598[0] = PeekPacketChecksumState((void *)(param_1 + 0x122));
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          FUN_00436bd0(local_15ac - ((int)local_1598[0] >> 8),local_159c - (iVar14 >> 8),
                       param_1[0x794]);
        }
        cVar8 = PeekPacketChecksumBool();
        if (cVar8 != '\0') {
          FUN_00436ec0(local_15ac,local_159c);
        }
        if (((((local_15ac < 0) || (*(int *)(&g_nCameraBoundX + g_clientContext) <= local_15ac)) ||
             (local_159c < 0)) ||
            ((*(int *)(&g_nCameraBoundY + g_clientContext) <= local_159c ||
             (*(char *)(local_159c * *(int *)(&g_nCameraBoundX + g_clientContext) +
                        *(int *)(&DAT_006a773c + g_clientContext) + local_15ac) == '\0')))) &&
           ((char)param_1[0xfe7] == '\x01')) {
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EncodeOutgoingPacketField((void *)(param_1 + 0x10), local_15ac << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EncodeOutgoingPacketField((void *)(param_1 + 0x99), local_159c << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EncodeOutgoingPacketField((void *)(param_1 + 0x3d5), local_15ac);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EncodeOutgoingPacketField((void *)(param_1 + 0x45e), local_159c);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          iVar10 = _rand();
          *(char *)((int)param_1 + 0xf45) = (char)iVar10;
          iVar10 = _rand();
          *(byte *)((int)param_1 + 0xf46) = (byte)iVar10;
          bVar15 = '\x01' << (*(byte *)((int)param_1 + 0xf45) & 7);
          bVar15 = ~bVar15 & (byte)iVar10 | bVar15;
          *(byte *)((int)param_1 + 0xf46) = bVar15;
          *(byte *)((int)param_1 + 0xf47) = bVar15 + *(char *)((int)param_1 + 0xf45) + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          break;
        }
        if (((-1 < local_15ac) && (local_15ac < *(int *)(&g_nCameraBoundX + g_clientContext))) &&
           ((-1 < local_159c &&
            (((local_159c < *(int *)(&g_nCameraBoundY + g_clientContext) &&
              (*(char *)(local_159c * *(int *)(&g_nCameraBoundX + g_clientContext) +
                         *(int *)(&DAT_006a773c + g_clientContext) + local_15ac) != '\0')) &&
             ((char)param_1[0xfe7] == '\0')))))) {
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EncodeOutgoingPacketField((void *)(param_1 + 0x10), local_15ac << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EncodeOutgoingPacketField((void *)(param_1 + 0x99), local_159c << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EncodeOutgoingPacketField((void *)(param_1 + 0x3d5), local_15ac);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EncodeOutgoingPacketField((void *)(param_1 + 0x45e), local_159c);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          *(undefined1 *)(param_1 + 0xfe7) = 1;
          local_1598[0] = EncodeChecksumDeltaDiv(param_1 + 0x1ab,local_230,2);
          local_4 = 0xf;
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          uVar9 = PeekPacketChecksumState((void *)(local_1598[0]));
          EncodeOutgoingPacketField((void *)(param_1 + 0x1ab), uVar9);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          local_4 = 0xffffffff;
          if ((*(int *)(local_230 + 0x14)) != 0) {
            ScrambleChecksumGuardBytes(*(int *)(local_230 + 0x14),&g_valueGuardKeyTable);
            local_1598[0] = (*(int *)(local_230 + 0x14));
            TreeLowerBound(local_1580,&g_valueGuardMap);
          }
          (**(code **)(*param_1 + 4))(s_special_005563c8);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          iVar10 = _rand();
          *(char *)(param_1 + 0xe04) = (char)iVar10;
          iVar10 = _rand();
          *(byte *)((int)param_1 + 0x3811) = (byte)iVar10;
          bVar15 = ~('\x01' << (*(byte *)(param_1 + 0xe04) & 7)) & (byte)iVar10 |
                   '\0' << (*(byte *)(param_1 + 0xe04) & 7);
          *(byte *)((int)param_1 + 0x3811) = bVar15;
          *(byte *)((int)param_1 + 0x3812) = bVar15 + (char)param_1[0xe04] + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          if (DAT_0079352a != '\0') {
            QueueBroadcastEvent(0xf002,(int)&g_replayContext);
            (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = (char)param_1[2];
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

