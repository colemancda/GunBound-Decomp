/* SimulateShot2_Bullet11 - 0x004731b0 in the original binary.
 *
 * RENAMED (2026-08-16, from FUN_004731b0): CProjectile virtual slot 5
 * (SimulateProjectileFrame, base impl 0x455cc0) override for mobile type
 * 10's shot 2 (weapon index 1, texture bullet11s); vtable 0x555f38, ctor
 * InitShot2_Bullet11 reached only through SpawnPrimaryShot's case 10. Type/role
 * CONFIRMED via vtable geometry (tools/projectile_class_map.py); the
 * mobile NAME is not confirmable (no mobile-type->name map in the repo).
 *
 * Body is a raw/near-verbatim Ghidra port, not hand-verified. See
 * src/README.md's "Raw/verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 20 argless PeekPacketChecksumState() calls and all 18 1-arg
 * EncodeOutgoingPacketField() calls (38 sites).  Same shape as
 * SimulateSuperShot_Bullet13: the delta/pair helpers return their arg2
 * scratch cell, so each Peek that follows one reads that C local
 * (local_1574 / local_1350 / local_112c / local_ce4 / local_89c /
 * local_454 / local_230 / local_ac0 / local_f08 / local_678).  The pair
 * of peeks and the lone Encode at each block head use frame[0x38],
 * loaded at 0x4734f3 from frame[0x48]+0x15c0 = the C's local_15a0
 * (= param_1 + 0x15c0; frame[0x48] = `this`, spilled at 0x4731e6).
 * Unlike Bullet13 this variant reads the destination cells directly at
 * 0x4739cb/0x4739e8 and mirrors (`lea eax,[ebx+0x6ac]` / `+0x488` =
 * param_1+0x1ab / +0x122) - no scratch there.  The four-Encode groups
 * write the position cells param_1+0x10/0x99/0x3d5/0x45e.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void __thiscall SimulateShot2_Bullet11(int param_1,int param_2)

{
  int *piVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  char cVar8;
  byte bVar9;
  byte bVar10;
  undefined4 uVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  byte bVar15;
  uint uVar16;
  int iVar17;
  byte *pbVar18;
  undefined4 *unaff_FS_OFFSET;
  int local_15bc;
  int local_15b8;
  uint local_15b4 [2];
  char local_15a9;
  int local_15a8;
  int local_15a4;
  int local_15a0;
  int local_159c;
  int local_1598;
  int local_1594;
  int local_1590;
  int local_158c;
  int local_1588;
  int local_1584 [2];
  int local_157c [2];
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
  puStack_8 = &LAB_0053f984;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uStack_10 = 0x4731cf;
  local_15a4 = param_1 + 0x40;
  bVar7 = false;
  bVar6 = false;
  bVar5 = false;
  bVar4 = false;
  bVar3 = false;
  bVar2 = false;
  local_15a9 = '\0';
  local_1590 = param_1;
  EncodeChecksumDeltaShr(local_15a4,local_1574,8);
  local_4 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_1594 = PeekPacketChecksumState((void *)(local_1574));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_4 = 0xffffffff;
  if ((*(int *)(local_1574 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_1574 + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_15b4,&g_valueGuardMap);
  }
  local_158c = param_1 + 0x264;
  EncodeChecksumDeltaShr(local_158c,local_1574,8);
  local_4 = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_15a0 = PeekPacketChecksumState((void *)(local_1574));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_4 = 0xffffffff;
  if ((*(int *)(local_1574 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_1574 + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_15b4,&g_valueGuardMap);
  }
  uVar11 = EncodeChecksumPairDiff(local_15a4,local_1350,param_1 + 0x488);
  local_4 = 2;
  EncodeChecksumDeltaShr(uVar11,local_1574,8);
  SUBFIELD(local_4,0,undefined1) = 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_1588 = PeekPacketChecksumState((void *)(local_1574));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),2);
  if ((*(int *)(local_1574 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_1574 + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_15b4,&g_valueGuardMap);
  }
  local_4 = 0xffffffff;
  if ((*(int *)(local_1350 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_1350 + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_15b4,&g_valueGuardMap);
  }
  uVar11 = EncodeChecksumPairDiff(local_158c,local_1574,local_1590 + 0x6ac);
  local_4 = 4;
  EncodeChecksumDeltaShr(uVar11,local_1350,8);
  SUBFIELD(local_4,0,undefined1) = 5;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar12 = PeekPacketChecksumState((void *)(local_1350));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),4);
  local_15a4 = (*(int *)(local_1350 + 0x14));
  if ((*(int *)(local_1350 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_1350 + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_15b4,&g_valueGuardMap);
  }
  local_4 = 0xffffffff;
  local_15a4 = (*(int *)(local_1574 + 0x14));
  if ((*(int *)(local_1574 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_1574 + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_15b4,&g_valueGuardMap);
  }
  uVar16 = local_1588 - local_1594 >> 0x1f;
  iVar17 = (local_1588 - local_1594 ^ uVar16) - uVar16;
  uVar16 = iVar12 - local_15a0 >> 0x1f;
  iVar13 = (iVar12 - local_15a0 ^ uVar16) - uVar16;
  local_158c = iVar17 + 1;
  local_15b4[0] = iVar13 + 1;
  local_1598 = 0;
  if ((int)local_15b4[0] < local_158c) {
    local_158c = ((local_15a0 - iVar12) * 0x10000) / local_158c;
    local_159c = iVar12 << 0x10;
    local_1594 = (uint)(local_1588 <= local_1594) * 2 + -1;
    local_15b4[0] = iVar17 + param_2;
    if (0 < (int)local_15b4[0]) {
      local_15a4 = local_158c * param_2;
      local_15a0 = local_1590 + 0x15c0;
      local_157c[0] = local_1594 * param_2;
      local_15a8 = local_1588;
LAB_00473504:
      local_159c = local_159c + local_15a4;
      local_15b8 = local_159c >> 0x10;
      local_15bc = local_15a8;
      if ((local_15a9 == '\0') &&
         (iVar13 = FUN_004510f0(local_15a8,(int)(&DAT_006a7f88 + g_clientContext)), iVar12 = local_15a0, iVar13 != 0)) {
        EncodeChecksumDeltaAdd(local_15a0,local_112c,param_2);
        local_4 = 6;
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        iVar13 = PeekPacketChecksumState((void *)(local_112c));
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        if (iVar13 < 0x14) {
LAB_004735e2:
          EncodeChecksumDeltaAdd(iVar12,local_ce4,param_2);
          local_4 = 8;
          bVar3 = true;
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          iVar13 = PeekPacketChecksumState((void *)(local_ce4));
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          if (iVar13 < 0x14) {
            uVar11 = 0x14;
          }
          else {
            EncodeChecksumDeltaAdd(iVar12,local_89c,param_2);
            local_4 = 9;
            bVar3 = true;
            bVar2 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
            uVar11 = PeekPacketChecksumState((void *)(local_89c));
            LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          }
        }
        else {
          EncodeChecksumDeltaAdd(iVar12,local_454,param_2);
          local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),7);
          bVar4 = true;
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          iVar13 = PeekPacketChecksumState((void *)(local_454));
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          if (iVar13 < 0x65) goto LAB_004735e2;
          uVar11 = 100;
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        EncodeOutgoingPacketField((void *)(local_15a0), uVar11);
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        local_4 = 8;
        if ((bVar2) && (bVar2 = false, (*(int *)(local_89c + 0x14)) != 0)) {
          ScrambleChecksumGuardBytes();
          TreeLowerBound(local_1584,&g_valueGuardMap);
        }
        local_4 = 7;
        if ((bVar3) && (bVar3 = false, (*(int *)(local_ce4 + 0x14)) != 0)) {
          ScrambleChecksumGuardBytes();
          TreeLowerBound(local_1584,&g_valueGuardMap);
        }
        local_4 = 6;
        if ((bVar4) && (bVar4 = false, (*(int *)(local_454 + 0x14)) != 0)) {
          ScrambleChecksumGuardBytes();
          TreeLowerBound(local_1584,&g_valueGuardMap);
        }
        local_4 = 0xffffffff;
        if ((*(int *)(local_112c + 0x14)) != 0) {
          ScrambleChecksumGuardBytes(*(int *)(local_112c + 0x14),&g_valueGuardKeyTable);
          TreeLowerBound(local_1584,&g_valueGuardMap);
        }
        local_15a9 = '\x01';
      }
      iVar13 = local_1590;
      pbVar18 = (byte *)(local_1590 + 0xf4c);
      cVar8 = DecodeGuardedBool(pbVar18);
      if (cVar8 != '\0') {
        iVar12 = FUN_00451030(local_15a8,(int)(&DAT_006a7f88 + g_clientContext));
        *(int *)(iVar13 + 0xf48) = iVar12;
        if (iVar12 != 0) {
          *(undefined4 *)(iVar13 + 0xf50) = 0;
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          iVar12 = _rand();
          *pbVar18 = (byte)iVar12;
          iVar12 = _rand();
          bVar10 = *pbVar18;
          *(byte *)(iVar13 + 0xf4d) = (byte)iVar12;
          bVar9 = '\x01' << (bVar10 & 7);
          bVar9 = ~bVar9 & (byte)iVar12 | bVar9;
          *(byte *)(iVar13 + 0xf4d) = bVar9;
          *(byte *)(iVar13 + 0xf4e) = bVar10 + bVar9 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          iVar12 = g_clientContext;
          pbVar18 = (byte *)(g_clientContext + 0x62140);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          iVar17 = _rand();
          *pbVar18 = (byte)iVar17;
          iVar17 = _rand();
          bVar10 = *pbVar18;
          *(byte *)(iVar12 + 0x62141) = (byte)iVar17;
          bVar9 = '\x01' << (bVar10 & 7);
          bVar9 = ~bVar9 & (byte)iVar17 | bVar9;
          *(byte *)(iVar12 + 0x62141) = bVar9;
          *(byte *)(iVar12 + 0x62142) = bVar10 + bVar9 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        }
      }
      cVar8 = PeekPacketChecksumBool((byte *)(iVar13 + 0x3918));
      if ((cVar8 == '\0') && (iVar12 = FUN_004511b0(local_15a8,(int)(&DAT_006a7f88 + g_clientContext)), iVar12 != 0)) {
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        iVar12 = _rand();
        *(byte *)(iVar13 + 0x3918) = (byte)iVar12;
        iVar12 = _rand();
        bVar10 = *(byte *)(iVar13 + 0x3918);
        *(byte *)(iVar13 + 0x3919) = (byte)iVar12;
        bVar9 = '\x01' << (bVar10 & 7);
        bVar9 = ~bVar9 & (byte)iVar12 | bVar9;
        *(byte *)(iVar13 + 0x3919) = bVar9;
        *(byte *)(iVar13 + 0x391a) = bVar10 + bVar9 + -0x34;
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar11 = PeekPacketChecksumState((void *)(local_15a0));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      FUN_00436dc0(local_15a8,local_15b8,uVar11);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar12 = PeekPacketChecksumState((void *)(local_15a0));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      if (iVar12 == 0) {
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        iVar12 = PeekPacketChecksumState((void *)(param_1 + 0x1ab));
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        local_1584[0] = PeekPacketChecksumState((void *)(param_1 + 0x122));
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        FUN_00436bd0(local_15a8 - (local_1584[0] >> 8),local_15b8 - (iVar12 >> 8),
                     *(undefined4 *)(iVar13 + 0x1e50));
      }
      cVar8 = PeekPacketChecksumBool();
      iVar12 = local_15a8;
      if (cVar8 != '\0') {
        FUN_00436ec0(local_15a8,local_15b8);
      }
      iVar17 = local_15a8;
      if ((((iVar12 < 0) || (*(int *)(&g_nCameraBoundX + g_clientContext) <= iVar12)) || (local_15b8 < 0))
         || ((*(int *)(&g_nCameraBoundY + g_clientContext) <= local_15b8 ||
             (*(char *)(*(int *)(&g_nCameraBoundX + g_clientContext) * local_15b8 +
                        *(int *)(&DAT_006a773c + g_clientContext) + iVar12) == '\0')))) {
        cVar8 = HitTestMobilesAndJewels(local_15b8,(int)(&DAT_006a7f88 + g_clientContext),local_15a8);
        if (cVar8 != '\0') {
          FUN_00458920(&local_15bc,&local_15b8,local_1588,local_1598,local_1594,local_158c,
                       local_159c,0,1,param_2);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          iVar13 = local_1590;
          EncodeOutgoingPacketField((void *)(param_1 + 0x10), local_15bc << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EncodeOutgoingPacketField((void *)(param_1 + 0x99), local_15b8 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EncodeOutgoingPacketField((void *)(param_1 + 0x3d5), local_15bc);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EncodeOutgoingPacketField((void *)(param_1 + 0x45e), local_15b8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          iVar12 = _rand();
          *(char *)(iVar13 + 0xf45) = (char)iVar12;
          local_15b4[0] = _rand();
          local_15b4[0] = local_15b4[0] & 0x800000ff;
          if ((int)local_15b4[0] < 0) {
            local_15b4[0] = (local_15b4[0] - 1 | 0xffffff00) + 1;
          }
          *(byte *)(iVar13 + 0xf46) = (byte)local_15b4[0];
          bVar10 = '\x01' << (*(byte *)(iVar13 + 0xf45) & 7);
          bVar10 = ~bVar10 & (byte)local_15b4[0] | bVar10;
          *(byte *)(iVar13 + 0xf46) = bVar10;
          *(byte *)(iVar13 + 0xf47) = *(byte *)(iVar13 + 0xf45) + bVar10 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          if (DAT_0079352a != '\0') {
            uVar11 = 0xf003;
            goto LAB_00474491;
          }
          goto LAB_00474632;
        }
        local_1598 = local_1598 + param_2;
        local_15a8 = iVar17 + local_157c[0];
        if ((int)local_15b4[0] <= local_1598) goto LAB_00474632;
        goto LAB_00473504;
      }
      FUN_00458920(&local_15bc,&local_15b8,local_1588,local_1598,local_1594,local_158c,local_159c,1,
                   0,param_2);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)(param_1 + 0x10), local_15bc << 8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)(param_1 + 0x99), local_15b8 << 8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)(param_1 + 0x3d5), local_15bc);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)(param_1 + 0x45e), local_15b8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar12 = _rand();
      *(char *)(iVar13 + 0xf45) = (char)iVar12;
      local_15b4[0] = _rand();
      local_15b4[0] = local_15b4[0] & 0x800000ff;
      if ((int)local_15b4[0] < 0) {
        local_15b4[0] = (local_15b4[0] - 1 | 0xffffff00) + 1;
      }
      bVar10 = *(byte *)(iVar13 + 0xf45);
      *(byte *)(iVar13 + 0xf46) = (byte)local_15b4[0];
      bVar9 = '\x01' << (bVar10 & 7);
      bVar15 = ~bVar9 & (byte)local_15b4[0];
LAB_00474465:
      *(byte *)(iVar13 + 0xf46) = bVar15 | bVar9;
      *(byte *)(iVar13 + 0xf47) = bVar10 + (bVar15 | bVar9) + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      if (DAT_0079352a != '\0') {
        uVar11 = 0xf002;
LAB_00474491:
        QueueBroadcastEvent(uVar11,(int)&g_replayContext);
        (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = *(undefined1 *)(iVar13 + 8);
LAB_004745f5:
        piVar1 = (int *)(&DAT_00e9aacd + g_dwBroadcastEventCursor);
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
        *piVar1 = local_15bc;
        piVar1 = (int *)(&DAT_00e9aad0 + g_dwBroadcastEventCursor);
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
        *piVar1 = local_15b8;
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
        BroadcastQueuedEvent((int)&g_replayContext);
      }
    }
  }
  else {
    local_158c = ((local_1594 - local_1588) * 0x10000) / (int)local_15b4[0];
    local_159c = local_1588 << 0x10;
    local_1588 = iVar13 + param_2;
    local_1594 = (uint)(iVar12 <= local_15a0) * 2 + -1;
    if (0 < local_1588) {
      local_15a4 = local_158c * param_2;
      local_15a0 = local_1590 + 0x15c0;
      local_1584[0] = local_1594 * param_2;
      local_15a8 = iVar12;
      do {
        local_159c = local_159c + local_15a4;
        local_15b8 = local_15a8;
        local_15bc = local_159c >> 0x10;
        if ((local_15a9 == '\0') &&
           (iVar17 = FUN_004510f0(local_15bc,(int)(&DAT_006a7f88 + g_clientContext)), iVar13 = local_15a0, iVar17 != 0)) {
          local_15b4[0] = EncodeChecksumDeltaAdd(local_15a0,local_230,param_2);
          local_4 = 10;
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          local_15b4[0] = PeekPacketChecksumState((void *)(local_230));
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          if ((int)local_15b4[0] < 0x14) {
LAB_00473e6c:
            local_15b4[0] = EncodeChecksumDeltaAdd(iVar13,local_ac0,param_2);
            local_4 = 0xc;
            bVar6 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
            local_15b4[0] = PeekPacketChecksumState((void *)(local_ac0));
            LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
            if ((int)local_15b4[0] < 0x14) {
              uVar11 = 0x14;
            }
            else {
              EncodeChecksumDeltaAdd(iVar13,local_f08,param_2);
              local_4 = 0xd;
              bVar6 = true;
              bVar5 = true;
              EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
              uVar11 = PeekPacketChecksumState((void *)(local_f08));
              LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
            }
          }
          else {
            local_15b4[0] = EncodeChecksumDeltaAdd(iVar13,local_678,param_2);
            local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0xb);
            bVar7 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
            local_15b4[0] = PeekPacketChecksumState((void *)(local_678));
            LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
            if ((int)local_15b4[0] < 0x65) goto LAB_00473e6c;
            uVar11 = 100;
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EncodeOutgoingPacketField((void *)(local_15a0), uVar11);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          uVar16 = (*(int *)(local_f08 + 0x14));
          local_4 = 0xc;
          if ((bVar5) && (bVar5 = false, (*(int *)(local_f08 + 0x14)) != 0)) {
            ScrambleChecksumGuardBytes();
            local_15b4[0] = uVar16;
            TreeLowerBound(local_157c,&g_valueGuardMap);
          }
          uVar16 = (*(int *)(local_ac0 + 0x14));
          local_4 = 0xb;
          if ((bVar6) && (bVar6 = false, (*(int *)(local_ac0 + 0x14)) != 0)) {
            ScrambleChecksumGuardBytes();
            local_15b4[0] = uVar16;
            TreeLowerBound(local_157c,&g_valueGuardMap);
          }
          uVar16 = (*(int *)(local_678 + 0x14));
          local_4 = 10;
          if ((bVar7) && (bVar7 = false, (*(int *)(local_678 + 0x14)) != 0)) {
            ScrambleChecksumGuardBytes();
            local_15b4[0] = uVar16;
            TreeLowerBound(local_157c,&g_valueGuardMap);
          }
          uVar16 = (*(int *)(local_230 + 0x14));
          local_4 = 0xffffffff;
          if ((*(int *)(local_230 + 0x14)) != 0) {
            ScrambleChecksumGuardBytes(*(int *)(local_230 + 0x14),&g_valueGuardKeyTable);
            local_15b4[0] = uVar16;
            TreeLowerBound(local_157c,&g_valueGuardMap);
          }
          local_15a9 = '\x01';
        }
        iVar13 = local_1590;
        pbVar18 = (byte *)(local_1590 + 0xf4c);
        cVar8 = DecodeGuardedBool(pbVar18);
        if (cVar8 != '\0') {
          iVar17 = FUN_00451030(local_15bc,(int)(&DAT_006a7f88 + g_clientContext));
          *(int *)(iVar13 + 0xf48) = iVar17;
          if (iVar17 != 0) {
            *(undefined4 *)(iVar13 + 0xf50) = 0;
            EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
            iVar17 = _rand();
            *pbVar18 = (byte)iVar17;
            local_15b4[0] = _rand();
            local_15b4[0] = local_15b4[0] & 0x800000ff;
            if ((int)local_15b4[0] < 0) {
              local_15b4[0] = (local_15b4[0] - 1 | 0xffffff00) + 1;
            }
            bVar10 = *pbVar18;
            *(byte *)(iVar13 + 0xf4d) = (byte)local_15b4[0];
            bVar9 = '\x01' << (bVar10 & 7);
            bVar9 = ~bVar9 & (byte)local_15b4[0] | bVar9;
            *(byte *)(iVar13 + 0xf4d) = bVar9;
            *(byte *)(iVar13 + 0xf4e) = bVar10 + bVar9 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
            iVar17 = g_clientContext;
            pbVar18 = (byte *)(g_clientContext + 0x62140);
            EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
            iVar14 = _rand();
            *pbVar18 = (byte)iVar14;
            local_15b4[0] = _rand();
            local_15b4[0] = local_15b4[0] & 0x800000ff;
            if ((int)local_15b4[0] < 0) {
              local_15b4[0] = (local_15b4[0] - 1 | 0xffffff00) + 1;
            }
            bVar10 = *pbVar18;
            *(byte *)(iVar17 + 0x62141) = (byte)local_15b4[0];
            bVar9 = '\x01' << (bVar10 & 7);
            bVar9 = ~bVar9 & (byte)local_15b4[0] | bVar9;
            *(byte *)(iVar17 + 0x62141) = bVar9;
            *(byte *)(iVar17 + 0x62142) = bVar10 + bVar9 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          }
        }
        cVar8 = PeekPacketChecksumBool((byte *)(iVar13 + 0x3918));
        if ((cVar8 == '\0') && (iVar17 = FUN_004511b0(local_15bc,(int)(&DAT_006a7f88 + g_clientContext)), iVar17 != 0)) {
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          iVar17 = _rand();
          *(byte *)(iVar13 + 0x3918) = (byte)iVar17;
          local_15b4[0] = _rand();
          local_15b4[0] = local_15b4[0] & 0x800000ff;
          if ((int)local_15b4[0] < 0) {
            local_15b4[0] = (local_15b4[0] - 1 | 0xffffff00) + 1;
          }
          bVar10 = *(byte *)(iVar13 + 0x3918);
          *(byte *)(iVar13 + 0x3919) = (byte)local_15b4[0];
          bVar9 = '\x01' << (bVar10 & 7);
          bVar9 = ~bVar9 & (byte)local_15b4[0] | bVar9;
          *(byte *)(iVar13 + 0x3919) = bVar9;
          *(byte *)(iVar13 + 0x391a) = bVar10 + bVar9 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        local_15b4[0] = PeekPacketChecksumState((void *)(local_15a0));
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        FUN_00436dc0(local_15bc,local_15a8,local_15b4[0]);
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        iVar17 = PeekPacketChecksumState((void *)(local_15a0));
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        if (iVar17 == 0) {
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          local_15b4[0] = PeekPacketChecksumState((void *)(param_1 + 0x1ab));
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          local_157c[0] = PeekPacketChecksumState((void *)(param_1 + 0x122));
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          FUN_00436bd0(local_15bc - (local_157c[0] >> 8),local_15a8 - ((int)local_15b4[0] >> 8),
                       *(undefined4 *)(iVar13 + 0x1e50));
        }
        cVar8 = PeekPacketChecksumBool();
        iVar17 = local_15bc;
        if (cVar8 != '\0') {
          FUN_00436ec0(local_15bc,local_15a8);
        }
        iVar14 = local_15a8;
        if ((((-1 < iVar17) && (iVar17 < *(int *)(&g_nCameraBoundX + g_clientContext))) &&
            (-1 < local_15a8)) &&
           ((local_15a8 < *(int *)(&g_nCameraBoundY + g_clientContext) &&
            (*(char *)(*(int *)(&g_nCameraBoundX + g_clientContext) * local_15a8 +
                       *(int *)(&DAT_006a773c + g_clientContext) + iVar17) != '\0')))) {
          FUN_00458a00(&local_15bc,&local_15b8,iVar12,local_1598,local_1594,local_158c,local_159c,1,
                       0,param_2);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EncodeOutgoingPacketField((void *)(param_1 + 0x10), local_15bc << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EncodeOutgoingPacketField((void *)(param_1 + 0x99), local_15b8 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EncodeOutgoingPacketField((void *)(param_1 + 0x3d5), local_15bc);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EncodeOutgoingPacketField((void *)(param_1 + 0x45e), local_15b8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          iVar12 = _rand();
          *(char *)(iVar13 + 0xf45) = (char)iVar12;
          local_15b4[0] = _rand();
          local_15b4[0] = local_15b4[0] & 0x800000ff;
          if ((int)local_15b4[0] < 0) {
            local_15b4[0] = (local_15b4[0] - 1 | 0xffffff00) + 1;
          }
          bVar10 = *(byte *)(iVar13 + 0xf45);
          *(byte *)(iVar13 + 0xf46) = (byte)local_15b4[0];
          bVar9 = '\x01' << (bVar10 & 7);
          bVar15 = ~bVar9 & (byte)local_15b4[0];
          goto LAB_00474465;
        }
        cVar8 = HitTestMobilesAndJewels(local_15a8,(int)(&DAT_006a7f88 + g_clientContext),local_15bc);
        if (cVar8 != '\0') {
          FUN_00458a00(&local_15bc,&local_15b8,iVar12,local_1598,local_1594,local_158c,local_159c,0,
                       1,param_2);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          iVar12 = local_1590;
          EncodeOutgoingPacketField((void *)(param_1 + 0x10), local_15bc << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EncodeOutgoingPacketField((void *)(param_1 + 0x99), local_15b8 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EncodeOutgoingPacketField((void *)(param_1 + 0x3d5), local_15bc);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EncodeOutgoingPacketField((void *)(param_1 + 0x45e), local_15b8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          iVar13 = _rand();
          *(char *)(iVar12 + 0xf45) = (char)iVar13;
          iVar13 = _rand();
          *(byte *)(iVar12 + 0xf46) = (byte)iVar13;
          bVar10 = '\x01' << (*(byte *)(iVar12 + 0xf45) & 7);
          bVar10 = ~bVar10 & (byte)iVar13 | bVar10;
          *(byte *)(iVar12 + 0xf46) = bVar10;
          *(byte *)(iVar12 + 0xf47) = bVar10 + *(char *)(iVar12 + 0xf45) + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          if (DAT_0079352a != '\0') {
            QueueBroadcastEvent(0xf003,(int)&g_replayContext);
            (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = *(undefined1 *)(iVar12 + 8);
            goto LAB_004745f5;
          }
          break;
        }
        local_1598 = local_1598 + param_2;
        local_15a8 = iVar14 + local_1584[0];
      } while (local_1598 < local_1588);
    }
  }
LAB_00474632:
  *unaff_FS_OFFSET = local_c;
  return;
}

