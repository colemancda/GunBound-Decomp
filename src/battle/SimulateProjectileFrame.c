/* SimulateProjectileFrame - 0x00455cc0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void __thiscall SimulateProjectileFrame(int param_1,int param_2)

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
  uint uVar15;
  int iVar16;
  byte *pbVar17;
  undefined4 *unaff_FS_OFFSET;
  int local_15b8;
  int local_15b4;
  uint local_15b0 [2];
  char local_15a5;
  int local_15a4;
  int local_15a0;
  int local_159c;
  int local_1598;
  int local_1594;
  int local_1590;
  int local_158c;
  int local_1588;
  int local_1584;
  undefined1 local_1580 [8];
  int local_1578;
  undefined1 local_1574 [20];
  int local_1560;
  undefined1 local_1350 [20];
  uint local_133c;
  undefined1 local_112c [20];
  int local_1118;
  undefined1 local_f08 [20];
  uint local_ef4;
  undefined1 local_ce4 [20];
  uint local_cd0;
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
  puStack_8 = &LAB_0053d8a0;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uStack_10 = 0x455cdf;
  local_15a0 = param_1 + 0x40;
  bVar7 = false;
  bVar6 = false;
  bVar5 = false;
  bVar4 = false;
  bVar3 = false;
  bVar2 = false;
  local_15a5 = '\0';
  local_159c = param_1;
  EncodeChecksumDeltaShr(local_15a0,local_1574,8);
  local_4 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_1590 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if (local_1560 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_15b0);
  }
  local_1588 = param_1 + 0x264;
  EncodeChecksumDeltaShr(local_1588,local_1574,8);
  local_4 = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_1598 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if (local_1560 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_15b0);
  }
  uVar11 = EncodeChecksumPairDiff(local_15a0,local_112c,param_1 + 0x488);
  local_4 = 2;
  EncodeChecksumDeltaShr(uVar11,local_1574,8);
  SUBFIELD(local_4,0,undefined1) = 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_1584 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),2);
  if (local_1560 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_15b0);
  }
  local_4 = 0xffffffff;
  if (local_1118 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_15b0);
  }
  uVar11 = EncodeChecksumPairDiff(local_1588,local_1574,local_159c + 0x6ac);
  local_4 = 4;
  EncodeChecksumDeltaShr(uVar11,local_112c,8);
  SUBFIELD(local_4,0,undefined1) = 5;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar12 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),4);
  local_15a0 = local_1118;
  if (local_1118 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_15b0);
  }
  local_4 = 0xffffffff;
  local_15a0 = local_1560;
  if (local_1560 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_15b0);
  }
  uVar15 = local_1584 - local_1590 >> 0x1f;
  iVar16 = (local_1584 - local_1590 ^ uVar15) - uVar15;
  uVar15 = iVar12 - local_1598 >> 0x1f;
  iVar13 = (iVar12 - local_1598 ^ uVar15) - uVar15;
  local_1588 = iVar16 + 1;
  local_15b0[0] = iVar13 + 1;
  local_158c = 0;
  if ((int)local_15b0[0] < local_1588) {
    local_1588 = ((local_1598 - iVar12) * 0x10000) / local_1588;
    local_1594 = iVar12 << 0x10;
    local_1590 = (uint)(local_1584 <= local_1590) * 2 + -1;
    local_15b0[0] = iVar16 + param_2;
    if (0 < (int)local_15b0[0]) {
      local_15a0 = local_1588 * param_2;
      local_1598 = local_159c + 0x15c0;
      local_1578 = local_1590 * param_2;
      local_15a4 = local_1584;
LAB_00456014:
      local_1594 = local_1594 + local_15a0;
      local_15b4 = local_1594 >> 0x10;
      local_15b8 = local_15a4;
      if ((local_15a5 == '\0') &&
         (iVar13 = FUN_004510f0(local_15a4), iVar12 = local_1598, iVar13 != 0)) {
        EncodeChecksumDeltaAdd(local_1598,local_1350,param_2);
        local_4 = 6;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar13 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar13 < 0x14) {
LAB_004560f2:
          EncodeChecksumDeltaAdd(iVar12,local_89c,param_2);
          local_4 = 8;
          bVar3 = true;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar13 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (iVar13 < 0x14) {
            uVar11 = 0x14;
          }
          else {
            EncodeChecksumDeltaAdd(iVar12,local_454,param_2);
            local_4 = 9;
            bVar3 = true;
            bVar2 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            uVar11 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
        }
        else {
          EncodeChecksumDeltaAdd(iVar12,local_ac0,param_2);
          local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),7);
          bVar4 = true;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar13 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (iVar13 < 0x65) goto LAB_004560f2;
          uVar11 = 100;
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(uVar11);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_4 = 8;
        if ((bVar2) && (bVar2 = false, local_440 != 0)) {
          ScrambleChecksumGuardBytes();
          TreeLowerBound(local_1580);
        }
        local_4 = 7;
        if ((bVar3) && (bVar3 = false, local_888 != 0)) {
          ScrambleChecksumGuardBytes();
          TreeLowerBound(local_1580);
        }
        local_4 = 6;
        if ((bVar4) && (bVar4 = false, local_aac != 0)) {
          ScrambleChecksumGuardBytes();
          TreeLowerBound(local_1580);
        }
        local_4 = 0xffffffff;
        if (local_133c != 0) {
          ScrambleChecksumGuardBytes();
          TreeLowerBound(local_1580);
        }
        local_15a5 = '\x01';
      }
      iVar12 = local_159c;
      pbVar17 = (byte *)(local_159c + 0xf4c);
      cVar8 = DecodeGuardedBool();
      if (cVar8 != '\0') {
        iVar13 = FUN_00451030(local_15a4);
        *(int *)(iVar12 + 0xf48) = iVar13;
        if (iVar13 != 0) {
          *(undefined4 *)(iVar12 + 0xf50) = 0;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar13 = _rand();
          *pbVar17 = (byte)iVar13;
          iVar13 = _rand();
          bVar10 = *pbVar17;
          *(byte *)(iVar12 + 0xf4d) = (byte)iVar13;
          bVar9 = '\x01' << (bVar10 & 7);
          bVar9 = ~bVar9 & (byte)iVar13 | bVar9;
          *(byte *)(iVar12 + 0xf4d) = bVar9;
          *(byte *)(iVar12 + 0xf4e) = bVar10 + bVar9 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar13 = g_clientContext;
          pbVar17 = (byte *)(g_clientContext + 0x62140);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar16 = _rand();
          *pbVar17 = (byte)iVar16;
          iVar16 = _rand();
          bVar10 = *pbVar17;
          *(byte *)(iVar13 + 0x62141) = (byte)iVar16;
          bVar9 = '\x01' << (bVar10 & 7);
          bVar9 = ~bVar9 & (byte)iVar16 | bVar9;
          *(byte *)(iVar13 + 0x62141) = bVar9;
          *(byte *)(iVar13 + 0x62142) = bVar10 + bVar9 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        }
      }
      cVar8 = PeekPacketChecksumBool();
      if ((cVar8 == '\0') && (iVar13 = FUN_004511b0(local_15a4), iVar13 != 0)) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar13 = _rand();
        *(byte *)(iVar12 + 0x3918) = (byte)iVar13;
        iVar13 = _rand();
        bVar10 = *(byte *)(iVar12 + 0x3918);
        *(byte *)(iVar12 + 0x3919) = (byte)iVar13;
        bVar9 = '\x01' << (bVar10 & 7);
        bVar9 = ~bVar9 & (byte)iVar13 | bVar9;
        *(byte *)(iVar12 + 0x3919) = bVar9;
        *(byte *)(iVar12 + 0x391a) = bVar10 + bVar9 + -0x34;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar11 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      FUN_00436dc0(local_15a4,local_15b4,uVar11);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar13 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar13 == 0) {
        EncodeChecksumDeltaShr(iVar12 + 0x6ac,local_ce4,8);
        local_4 = 10;
        EncodeChecksumDeltaShr(iVar12 + 0x488,local_f08,8);
        SUBFIELD(local_4,0,undefined1) = 0xb;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar13 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar16 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        FUN_00436bd0(local_15a4 - iVar16,local_15b4 - iVar13,*(undefined4 *)(iVar12 + 0x1e50));
        local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),10);
        if (local_ef4 != 0) {
          ScrambleChecksumGuardBytes();
          TreeLowerBound(local_1580);
          iVar12 = local_159c;
        }
        local_4 = 0xffffffff;
        if (local_cd0 != 0) {
          ScrambleChecksumGuardBytes();
          TreeLowerBound(local_1580);
          iVar12 = local_159c;
        }
      }
      iVar13 = local_15a4;
      cVar8 = PeekPacketChecksumBool();
      if (cVar8 != '\0') {
        FUN_00436ec0(iVar13,local_15b4);
      }
      iVar16 = local_15a4;
      if ((((-1 < iVar13) && (iVar13 < *(int *)(&DAT_006a7720 + g_clientContext))) && (-1 < local_15b4)
          ) && ((local_15b4 < *(int *)(&DAT_006a7724 + g_clientContext) &&
                (*(char *)(*(int *)(&DAT_006a7720 + g_clientContext) * local_15b4 +
                           *(int *)(&DAT_006a773c + g_clientContext) + iVar13) != '\0')))) {
        FUN_00458920(&local_15b8,&local_15b4,local_1584,local_158c,local_1590,local_1588,local_1594,
                     1,0);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(local_15b8 << 8);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(local_15b4 << 8);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(local_15b8);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(local_15b4);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar13 = _rand();
        *(char *)(iVar12 + 0xf45) = (char)iVar13;
        local_15b0[0] = _rand();
        local_15b0[0] = local_15b0[0] & 0x800000ff;
        if ((int)local_15b0[0] < 0) {
          local_15b0[0] = (local_15b0[0] - 1 | 0xffffff00) + 1;
        }
        *(byte *)(iVar12 + 0xf46) = (byte)local_15b0[0];
        bVar10 = '\x01' << (*(byte *)(iVar12 + 0xf45) & 7);
        bVar10 = ~bVar10 & (byte)local_15b0[0] | bVar10;
        *(byte *)(iVar12 + 0xf46) = bVar10;
        *(byte *)(iVar12 + 0xf47) = *(byte *)(iVar12 + 0xf45) + bVar10 + -0x34;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (DAT_0079352a != '\0') {
          uVar11 = 0xf002;
          goto LAB_0045723e;
        }
        goto LAB_00457294;
      }
      cVar8 = FUN_00450e10(local_15b4);
      if (cVar8 == '\0') {
        local_158c = local_158c + param_2;
        local_15a4 = iVar16 + local_1578;
        if ((int)local_15b0[0] <= local_158c) goto LAB_00457294;
        goto LAB_00456014;
      }
      FUN_00458920(&local_15b8,&local_15b4,local_1584,local_158c,local_1590,local_1588,local_1594,0,
                   1);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar12 = local_159c;
      EncodeOutgoingPacketField(local_15b8 << 8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(local_15b4 << 8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(local_15b8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(local_15b4);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar13 = _rand();
      *(char *)(iVar12 + 0xf45) = (char)iVar13;
      local_15b0[0] = _rand();
      local_15b0[0] = local_15b0[0] & 0x800000ff;
      if ((int)local_15b0[0] < 0) {
        local_15b0[0] = (local_15b0[0] - 1 | 0xffffff00) + 1;
      }
      *(byte *)(iVar12 + 0xf46) = (byte)local_15b0[0];
      bVar10 = '\x01' << (*(byte *)(iVar12 + 0xf45) & 7);
      bVar10 = ~bVar10 & (byte)local_15b0[0] | bVar10;
      *(byte *)(iVar12 + 0xf46) = bVar10;
      *(byte *)(iVar12 + 0xf47) = *(byte *)(iVar12 + 0xf45) + bVar10 + -0x34;
LAB_00457229:
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (DAT_0079352a != '\0') {
        uVar11 = 0xf003;
LAB_0045723e:
        QueueBroadcastEvent(uVar11);
        (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = *(undefined1 *)(iVar12 + 8);
        piVar1 = (int *)(&DAT_00e9aacd + g_dwBroadcastEventCursor);
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
        *piVar1 = local_15b8;
        piVar1 = (int *)(&DAT_00e9aad0 + g_dwBroadcastEventCursor);
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
        *piVar1 = local_15b4;
LAB_00457283:
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
        BroadcastQueuedEvent();
      }
    }
  }
  else {
    local_1588 = ((local_1590 - local_1584) * 0x10000) / (int)local_15b0[0];
    local_1594 = local_1584 << 0x10;
    local_1584 = iVar13 + param_2;
    local_1590 = (uint)(iVar12 <= local_1598) * 2 + -1;
    if (0 < local_1584) {
      local_15a0 = local_1588 * param_2;
      local_1598 = local_159c + 0x15c0;
      local_1578 = local_1590 * param_2;
      local_15a4 = iVar12;
      do {
        local_1594 = local_1594 + local_15a0;
        local_15b4 = local_15a4;
        local_15b8 = local_1594 >> 0x10;
        if ((local_15a5 == '\0') &&
           (iVar16 = FUN_004510f0(local_15b8), iVar13 = local_1598, iVar16 != 0)) {
          local_15b0[0] = EncodeChecksumDeltaAdd(local_1598,local_ac0,param_2);
          local_4 = 0xc;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15b0[0] = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if ((int)local_15b0[0] < 0x14) {
LAB_00456a3c:
            local_15b0[0] = EncodeChecksumDeltaAdd(iVar13,local_f08,param_2);
            local_4 = 0xe;
            bVar6 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_15b0[0] = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if ((int)local_15b0[0] < 0x14) {
              uVar11 = 0x14;
            }
            else {
              EncodeChecksumDeltaAdd(iVar13,local_ce4,param_2);
              local_4 = 0xf;
              bVar6 = true;
              bVar5 = true;
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              uVar11 = PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            }
          }
          else {
            local_15b0[0] = EncodeChecksumDeltaAdd(iVar13,local_1350,param_2);
            local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0xd);
            bVar7 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_15b0[0] = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if ((int)local_15b0[0] < 0x65) goto LAB_00456a3c;
            uVar11 = 100;
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(uVar11);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar15 = local_cd0;
          local_4 = 0xe;
          if ((bVar5) && (bVar5 = false, local_cd0 != 0)) {
            ScrambleChecksumGuardBytes();
            local_15b0[0] = uVar15;
            TreeLowerBound(local_1580);
          }
          uVar15 = local_ef4;
          local_4 = 0xd;
          if ((bVar6) && (bVar6 = false, local_ef4 != 0)) {
            ScrambleChecksumGuardBytes();
            local_15b0[0] = uVar15;
            TreeLowerBound(local_1580);
          }
          uVar15 = local_133c;
          local_4 = 0xc;
          if ((bVar7) && (bVar7 = false, local_133c != 0)) {
            ScrambleChecksumGuardBytes();
            local_15b0[0] = uVar15;
            TreeLowerBound(local_1580);
          }
          uVar15 = local_aac;
          local_4 = 0xffffffff;
          if (local_aac != 0) {
            ScrambleChecksumGuardBytes();
            local_15b0[0] = uVar15;
            TreeLowerBound(local_1580);
          }
          local_15a5 = '\x01';
        }
        iVar13 = local_159c;
        pbVar17 = (byte *)(local_159c + 0xf4c);
        cVar8 = DecodeGuardedBool();
        if (cVar8 != '\0') {
          iVar16 = FUN_00451030(local_15b8);
          *(int *)(iVar13 + 0xf48) = iVar16;
          if (iVar16 != 0) {
            *(undefined4 *)(iVar13 + 0xf50) = 0;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar16 = _rand();
            *pbVar17 = (byte)iVar16;
            iVar16 = _rand();
            bVar10 = *pbVar17;
            *(byte *)(iVar13 + 0xf4d) = (byte)iVar16;
            bVar9 = '\x01' << (bVar10 & 7);
            bVar10 = *pbVar17;
            bVar9 = ~bVar9 & (byte)iVar16 | bVar9;
            *(byte *)(iVar13 + 0xf4d) = bVar9;
            *(byte *)(iVar13 + 0xf4e) = bVar9 + bVar10 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar16 = g_clientContext;
            pbVar17 = (byte *)(g_clientContext + 0x62140);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar14 = _rand();
            *pbVar17 = (byte)iVar14;
            iVar14 = _rand();
            bVar10 = *pbVar17;
            *(byte *)(iVar16 + 0x62141) = (byte)iVar14;
            bVar9 = '\x01' << (bVar10 & 7);
            bVar10 = *pbVar17;
            bVar9 = ~bVar9 & (byte)iVar14 | bVar9;
            *(byte *)(iVar16 + 0x62141) = bVar9;
            *(byte *)(iVar16 + 0x62142) = bVar9 + bVar10 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
        }
        pbVar17 = (byte *)(iVar13 + 0x3918);
        cVar8 = PeekPacketChecksumBool();
        if ((cVar8 == '\0') && (iVar16 = FUN_004511b0(local_15b8), iVar16 != 0)) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar16 = _rand();
          *pbVar17 = (byte)iVar16;
          iVar16 = _rand();
          *(byte *)(iVar13 + 0x3919) = (byte)iVar16;
          bVar10 = '\x01' << (*pbVar17 & 7);
          bVar10 = ~bVar10 & (byte)iVar16 | bVar10;
          *(byte *)(iVar13 + 0x3919) = bVar10;
          *(byte *)(iVar13 + 0x391a) = bVar10 + *pbVar17 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar11 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        FUN_00436dc0(local_15b8,local_15a4,uVar11);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar16 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar16 == 0) {
          EncodeChecksumDeltaShr(iVar13 + 0x6ac,local_230,8);
          local_4 = 0x10;
          local_15b0[0] = EncodeChecksumDeltaShr(iVar13 + 0x488,local_678,8);
          SUBFIELD(local_4,0,undefined1) = 0x11;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar16 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15b0[0] = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          FUN_00436bd0(local_15b8 - local_15b0[0],local_15a4 - iVar16,
                       *(undefined4 *)(iVar13 + 0x1e50));
          uVar15 = local_664;
          local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x10);
          if (local_664 != 0) {
            ScrambleChecksumGuardBytes();
            local_15b0[0] = uVar15;
            TreeLowerBound(local_1580);
            iVar13 = local_159c;
          }
          uVar15 = local_21c;
          local_4 = 0xffffffff;
          if (local_21c != 0) {
            ScrambleChecksumGuardBytes();
            local_15b0[0] = uVar15;
            TreeLowerBound(local_1580);
            iVar13 = local_159c;
          }
        }
        iVar16 = local_15b8;
        cVar8 = PeekPacketChecksumBool();
        if (cVar8 != '\0') {
          FUN_00436ec0(iVar16,local_15a4);
        }
        iVar14 = local_15a4;
        if ((((-1 < iVar16) && (iVar16 < *(int *)(&DAT_006a7720 + g_clientContext))) &&
            (-1 < local_15a4)) &&
           ((local_15a4 < *(int *)(&DAT_006a7724 + g_clientContext) &&
            (*(char *)(local_15a4 * *(int *)(&DAT_006a7720 + g_clientContext) +
                       *(int *)(&DAT_006a773c + g_clientContext) + iVar16) != '\0')))) {
          FUN_00458a00(&local_15b8,&local_15b4,iVar12,local_158c,local_1590,local_1588,local_1594,1,
                       0);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b8 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b4 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b4);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar12 = _rand();
          *(char *)(iVar13 + 0xf45) = (char)iVar12;
          iVar12 = _rand();
          *(byte *)(iVar13 + 0xf46) = (byte)iVar12;
          bVar10 = '\x01' << (*(byte *)(iVar13 + 0xf45) & 7);
          bVar10 = ~bVar10 & (byte)iVar12 | bVar10;
          *(byte *)(iVar13 + 0xf46) = bVar10;
          *(byte *)(iVar13 + 0xf47) = bVar10 + *(char *)(iVar13 + 0xf45) + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (DAT_0079352a != '\0') {
            QueueBroadcastEvent(0xf002);
            (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = *(undefined1 *)(iVar13 + 8);
            piVar1 = (int *)(&DAT_00e9aacd + g_dwBroadcastEventCursor);
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
            *piVar1 = local_15b8;
            piVar1 = (int *)(&DAT_00e9aad0 + g_dwBroadcastEventCursor);
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
            *piVar1 = local_15b4;
            goto LAB_00457283;
          }
          break;
        }
        cVar8 = FUN_00450e10(local_15a4);
        if (cVar8 != '\0') {
          FUN_00458a00(&local_15b8,&local_15b4,iVar12,local_158c,local_1590,local_1588,local_1594,0,
                       1);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar12 = local_159c;
          EncodeOutgoingPacketField(local_15b8 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b4 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b4);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar13 = _rand();
          *(char *)(iVar12 + 0xf45) = (char)iVar13;
          iVar13 = _rand();
          *(byte *)(iVar12 + 0xf46) = (byte)iVar13;
          bVar10 = '\x01' << (*(byte *)(iVar12 + 0xf45) & 7);
          bVar10 = ~bVar10 & (byte)iVar13 | bVar10;
          *(byte *)(iVar12 + 0xf46) = bVar10;
          *(byte *)(iVar12 + 0xf47) = bVar10 + *(char *)(iVar12 + 0xf45) + -0x34;
          goto LAB_00457229;
        }
        local_158c = local_158c + param_2;
        local_15a4 = iVar14 + local_1578;
      } while (local_158c < local_1584);
    }
  }
LAB_00457294:
  *unaff_FS_OFFSET = local_c;
  return;
}

