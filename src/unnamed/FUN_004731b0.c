/* FUN_004731b0 - 0x004731b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void __thiscall FUN_004731b0(int param_1,int param_2)

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
  FUN_0040b180(local_15a4,local_1574,8);
  local_4 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_1594 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if (local_1560 != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_15b4);
  }
  local_158c = param_1 + 0x264;
  FUN_0040b180(local_158c,local_1574,8);
  local_4 = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_15a0 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if (local_1560 != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_15b4);
  }
  uVar11 = EncodeChecksumPairDiff(local_15a4,local_1350,param_1 + 0x488);
  local_4 = 2;
  FUN_0040b180(uVar11,local_1574,8);
  SUBFIELD(local_4,0,undefined1) = 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_1588 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),2);
  if (local_1560 != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_15b4);
  }
  local_4 = 0xffffffff;
  if (local_133c != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_15b4);
  }
  uVar11 = EncodeChecksumPairDiff(local_158c,local_1574,local_1590 + 0x6ac);
  local_4 = 4;
  FUN_0040b180(uVar11,local_1350,8);
  SUBFIELD(local_4,0,undefined1) = 5;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar12 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),4);
  local_15a4 = local_133c;
  if (local_133c != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_15b4);
  }
  local_4 = 0xffffffff;
  local_15a4 = local_1560;
  if (local_1560 != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_15b4);
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
         (iVar13 = FUN_004510f0(local_15a8), iVar12 = local_15a0, iVar13 != 0)) {
        EncodeChecksumDeltaAdd(local_15a0,local_112c,param_2);
        local_4 = 6;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar13 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar13 < 0x14) {
LAB_004735e2:
          EncodeChecksumDeltaAdd(iVar12,local_ce4,param_2);
          local_4 = 8;
          bVar3 = true;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar13 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (iVar13 < 0x14) {
            uVar11 = 0x14;
          }
          else {
            EncodeChecksumDeltaAdd(iVar12,local_89c,param_2);
            local_4 = 9;
            bVar3 = true;
            bVar2 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            uVar11 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
        }
        else {
          EncodeChecksumDeltaAdd(iVar12,local_454,param_2);
          local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),7);
          bVar4 = true;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar13 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (iVar13 < 0x65) goto LAB_004735e2;
          uVar11 = 100;
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(uVar11);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_4 = 8;
        if ((bVar2) && (bVar2 = false, local_888 != 0)) {
          ScrambleChecksumGuardBytes();
          FUN_0040b540(local_1584);
        }
        local_4 = 7;
        if ((bVar3) && (bVar3 = false, local_cd0 != 0)) {
          ScrambleChecksumGuardBytes();
          FUN_0040b540(local_1584);
        }
        local_4 = 6;
        if ((bVar4) && (bVar4 = false, local_440 != 0)) {
          ScrambleChecksumGuardBytes();
          FUN_0040b540(local_1584);
        }
        local_4 = 0xffffffff;
        if (local_1118 != 0) {
          ScrambleChecksumGuardBytes();
          FUN_0040b540(local_1584);
        }
        local_15a9 = '\x01';
      }
      iVar13 = local_1590;
      pbVar18 = (byte *)(local_1590 + 0xf4c);
      cVar8 = FUN_00406860();
      if (cVar8 != '\0') {
        iVar12 = FUN_00451030(local_15a8);
        *(int *)(iVar13 + 0xf48) = iVar12;
        if (iVar12 != 0) {
          *(undefined4 *)(iVar13 + 0xf50) = 0;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar12 = _rand();
          *pbVar18 = (byte)iVar12;
          iVar12 = _rand();
          bVar10 = *pbVar18;
          *(byte *)(iVar13 + 0xf4d) = (byte)iVar12;
          bVar9 = '\x01' << (bVar10 & 7);
          bVar9 = ~bVar9 & (byte)iVar12 | bVar9;
          *(byte *)(iVar13 + 0xf4d) = bVar9;
          *(byte *)(iVar13 + 0xf4e) = bVar10 + bVar9 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar12 = g_clientContext;
          pbVar18 = (byte *)(g_clientContext + 0x62140);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar17 = _rand();
          *pbVar18 = (byte)iVar17;
          iVar17 = _rand();
          bVar10 = *pbVar18;
          *(byte *)(iVar12 + 0x62141) = (byte)iVar17;
          bVar9 = '\x01' << (bVar10 & 7);
          bVar9 = ~bVar9 & (byte)iVar17 | bVar9;
          *(byte *)(iVar12 + 0x62141) = bVar9;
          *(byte *)(iVar12 + 0x62142) = bVar10 + bVar9 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        }
      }
      cVar8 = PeekPacketChecksumBool();
      if ((cVar8 == '\0') && (iVar12 = FUN_004511b0(local_15a8), iVar12 != 0)) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar12 = _rand();
        *(byte *)(iVar13 + 0x3918) = (byte)iVar12;
        iVar12 = _rand();
        bVar10 = *(byte *)(iVar13 + 0x3918);
        *(byte *)(iVar13 + 0x3919) = (byte)iVar12;
        bVar9 = '\x01' << (bVar10 & 7);
        bVar9 = ~bVar9 & (byte)iVar12 | bVar9;
        *(byte *)(iVar13 + 0x3919) = bVar9;
        *(byte *)(iVar13 + 0x391a) = bVar10 + bVar9 + -0x34;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar11 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      FUN_00436dc0(local_15a8,local_15b8,uVar11);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar12 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar12 == 0) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar12 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_1584[0] = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        FUN_00436bd0(local_15a8 - (local_1584[0] >> 8),local_15b8 - (iVar12 >> 8),
                     *(undefined4 *)(iVar13 + 0x1e50));
      }
      cVar8 = PeekPacketChecksumBool();
      iVar12 = local_15a8;
      if (cVar8 != '\0') {
        FUN_00436ec0(local_15a8,local_15b8);
      }
      iVar17 = local_15a8;
      if ((((iVar12 < 0) || (*(int *)(&DAT_006a7720 + g_clientContext) <= iVar12)) || (local_15b8 < 0))
         || ((*(int *)(&DAT_006a7724 + g_clientContext) <= local_15b8 ||
             (*(char *)(*(int *)(&DAT_006a7720 + g_clientContext) * local_15b8 +
                        *(int *)(&DAT_006a773c + g_clientContext) + iVar12) == '\0')))) {
        cVar8 = FUN_00450e10(local_15b8);
        if (cVar8 != '\0') {
          FUN_00458920(&local_15bc,&local_15b8,local_1588,local_1598,local_1594,local_158c,
                       local_159c,0,1);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar13 = local_1590;
          EncodeOutgoingPacketField(local_15bc << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b8 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15bc);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
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
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
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
                   0);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(local_15bc << 8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(local_15b8 << 8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(local_15bc);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(local_15b8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
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
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (DAT_0079352a != '\0') {
        uVar11 = 0xf002;
LAB_00474491:
        Replay_AppendEvent(uVar11);
        (&g_replayEventBuffer)[g_replayEventCursor] = *(undefined1 *)(iVar13 + 8);
LAB_004745f5:
        piVar1 = (int *)(&DAT_00e9aacd + g_replayEventCursor);
        g_replayEventCursor = g_replayEventCursor + 1;
        *piVar1 = local_15bc;
        piVar1 = (int *)(&DAT_00e9aad0 + g_replayEventCursor);
        g_replayEventCursor = g_replayEventCursor + 4;
        *piVar1 = local_15b8;
        g_replayEventCursor = g_replayEventCursor + 4;
        Replay_FlushEvent();
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
           (iVar17 = FUN_004510f0(local_15bc), iVar13 = local_15a0, iVar17 != 0)) {
          local_15b4[0] = EncodeChecksumDeltaAdd(local_15a0,local_230,param_2);
          local_4 = 10;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15b4[0] = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if ((int)local_15b4[0] < 0x14) {
LAB_00473e6c:
            local_15b4[0] = EncodeChecksumDeltaAdd(iVar13,local_ac0,param_2);
            local_4 = 0xc;
            bVar6 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_15b4[0] = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if ((int)local_15b4[0] < 0x14) {
              uVar11 = 0x14;
            }
            else {
              EncodeChecksumDeltaAdd(iVar13,local_f08,param_2);
              local_4 = 0xd;
              bVar6 = true;
              bVar5 = true;
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              uVar11 = PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            }
          }
          else {
            local_15b4[0] = EncodeChecksumDeltaAdd(iVar13,local_678,param_2);
            local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0xb);
            bVar7 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_15b4[0] = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if ((int)local_15b4[0] < 0x65) goto LAB_00473e6c;
            uVar11 = 100;
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(uVar11);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar16 = local_ef4;
          local_4 = 0xc;
          if ((bVar5) && (bVar5 = false, local_ef4 != 0)) {
            ScrambleChecksumGuardBytes();
            local_15b4[0] = uVar16;
            FUN_0040b540(local_157c);
          }
          uVar16 = local_aac;
          local_4 = 0xb;
          if ((bVar6) && (bVar6 = false, local_aac != 0)) {
            ScrambleChecksumGuardBytes();
            local_15b4[0] = uVar16;
            FUN_0040b540(local_157c);
          }
          uVar16 = local_664;
          local_4 = 10;
          if ((bVar7) && (bVar7 = false, local_664 != 0)) {
            ScrambleChecksumGuardBytes();
            local_15b4[0] = uVar16;
            FUN_0040b540(local_157c);
          }
          uVar16 = local_21c;
          local_4 = 0xffffffff;
          if (local_21c != 0) {
            ScrambleChecksumGuardBytes();
            local_15b4[0] = uVar16;
            FUN_0040b540(local_157c);
          }
          local_15a9 = '\x01';
        }
        iVar13 = local_1590;
        pbVar18 = (byte *)(local_1590 + 0xf4c);
        cVar8 = FUN_00406860();
        if (cVar8 != '\0') {
          iVar17 = FUN_00451030(local_15bc);
          *(int *)(iVar13 + 0xf48) = iVar17;
          if (iVar17 != 0) {
            *(undefined4 *)(iVar13 + 0xf50) = 0;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
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
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar17 = g_clientContext;
            pbVar18 = (byte *)(g_clientContext + 0x62140);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
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
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
        }
        cVar8 = PeekPacketChecksumBool();
        if ((cVar8 == '\0') && (iVar17 = FUN_004511b0(local_15bc), iVar17 != 0)) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
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
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_15b4[0] = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        FUN_00436dc0(local_15bc,local_15a8,local_15b4[0]);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar17 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar17 == 0) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15b4[0] = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_157c[0] = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          FUN_00436bd0(local_15bc - (local_157c[0] >> 8),local_15a8 - ((int)local_15b4[0] >> 8),
                       *(undefined4 *)(iVar13 + 0x1e50));
        }
        cVar8 = PeekPacketChecksumBool();
        iVar17 = local_15bc;
        if (cVar8 != '\0') {
          FUN_00436ec0(local_15bc,local_15a8);
        }
        iVar14 = local_15a8;
        if ((((-1 < iVar17) && (iVar17 < *(int *)(&DAT_006a7720 + g_clientContext))) &&
            (-1 < local_15a8)) &&
           ((local_15a8 < *(int *)(&DAT_006a7724 + g_clientContext) &&
            (*(char *)(*(int *)(&DAT_006a7720 + g_clientContext) * local_15a8 +
                       *(int *)(&DAT_006a773c + g_clientContext) + iVar17) != '\0')))) {
          FUN_00458a00(&local_15bc,&local_15b8,iVar12,local_1598,local_1594,local_158c,local_159c,1,
                       0);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15bc << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b8 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15bc);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
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
        cVar8 = FUN_00450e10(local_15a8);
        if (cVar8 != '\0') {
          FUN_00458a00(&local_15bc,&local_15b8,iVar12,local_1598,local_1594,local_158c,local_159c,0,
                       1);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar12 = local_1590;
          EncodeOutgoingPacketField(local_15bc << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b8 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15bc);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b8);
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
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (DAT_0079352a != '\0') {
            Replay_AppendEvent(0xf003);
            (&g_replayEventBuffer)[g_replayEventCursor] = *(undefined1 *)(iVar12 + 8);
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

