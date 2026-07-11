/* FUN_004857f0 - 0x004857f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void __thiscall FUN_004857f0(int param_1,int param_2)

{
  int *piVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  char cVar8;
  int iVar9;
  undefined4 uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  byte bVar15;
  uint uVar16;
  byte bVar17;
  byte *pbVar18;
  undefined4 *unaff_FS_OFFSET;
  int local_15c0;
  int local_15bc;
  int local_15b8;
  byte local_15b2;
  char local_15b1;
  int local_15b0 [2];
  int local_15a8;
  int local_15a4;
  int local_15a0;
  int local_159c;
  int local_1598;
  int local_1594 [2];
  int local_158c;
  int local_1588;
  int local_1584;
  int local_1580 [2];
  int local_1578;
  undefined1 local_1574 [20];
  int local_1560;
  undefined1 local_1350 [20];
  int local_133c;
  undefined1 local_112c [20];
  int local_1118;
  undefined1 local_f08 [20];
  int local_ef4;
  undefined1 local_ce4 [20];
  int local_cd0;
  undefined1 local_ac0 [20];
  int local_aac;
  undefined1 local_89c [20];
  int local_888;
  undefined1 local_678 [20];
  int local_664;
  undefined1 local_454 [20];
  int local_440;
  undefined1 local_230 [20];
  int local_21c;
  undefined4 uStack_10;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053f760;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uStack_10 = 0x48580f;
  local_15a0 = param_1 + 0x40;
  bVar7 = false;
  bVar6 = false;
  bVar5 = false;
  bVar4 = false;
  bVar3 = false;
  bVar2 = false;
  local_15b1 = '\0';
  local_15a8 = param_1;
  EncodeChecksumDeltaShr(local_15a0,local_1574,8);
  local_4 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar9 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  local_15bc = local_1560;
  if (local_1560 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_15b0);
  }
  local_158c = param_1 + 0x264;
  EncodeChecksumDeltaShr(local_158c,local_1574,8);
  local_4 = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_159c = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  local_15bc = local_1560;
  if (local_1560 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_15b0);
  }
  uVar10 = EncodeChecksumPairDiff(local_15a0,local_112c,param_1 + 0x488);
  local_4 = 2;
  EncodeChecksumDeltaShr(uVar10,local_1574,8);
  local_4 = 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_15a0 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar11 = local_1560;
  local_4 = 2;
  if (local_1560 != 0) {
    ScrambleChecksumGuardBytes();
    local_15bc = iVar11;
    TreeLowerBound(local_15b0);
  }
  iVar11 = local_1118;
  local_4 = 0xffffffff;
  if (local_1118 != 0) {
    ScrambleChecksumGuardBytes();
    local_15bc = iVar11;
    TreeLowerBound(local_15b0);
  }
  uVar10 = EncodeChecksumPairDiff(local_158c,local_1574,local_15a8 + 0x6ac);
  local_4 = 4;
  EncodeChecksumDeltaShr(uVar10,local_112c,8);
  local_4 = 5;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar11 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 4;
  local_15bc = local_1118;
  if (local_1118 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_15b0);
  }
  local_4 = 0xffffffff;
  local_15bc = local_1560;
  if (local_1560 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_15b0);
  }
  uVar16 = local_15a0 - iVar9 >> 0x1f;
  iVar14 = (local_15a0 - iVar9 ^ uVar16) - uVar16;
  uVar16 = iVar11 - local_159c >> 0x1f;
  iVar12 = (iVar11 - local_159c ^ uVar16) - uVar16;
  local_15bc = iVar14 + 1;
  iVar13 = iVar12 + 1;
  if (iVar13 < local_15bc) {
    local_15bc = ((local_159c - iVar11) * 0x10000) / local_15bc;
    local_1584 = iVar11 << 0x10;
    if (iVar9 < local_15a0) {
      local_15c0 = local_15a0 + -1;
      local_158c = -1;
    }
    else {
      local_15c0 = local_15a0 + 1;
      local_158c = 1;
    }
    local_15b0[0] = iVar14 + param_2;
    local_1588 = 0;
    if (0 < local_15b0[0]) {
      local_15a0 = local_15bc * param_2;
      local_1598 = local_15a8 + 0x15c0;
      local_1578 = local_158c * param_2;
      local_159c = local_15c0;
      do {
        iVar9 = local_1598;
        local_1584 = local_1584 + local_15a0;
        local_15b8 = local_1584 >> 0x10;
        local_15a4 = local_15c0;
        if ((local_15b1 == '\0') && (iVar11 = FUN_004510f0(local_15c0), iVar11 != 0)) {
          EncodeChecksumDeltaAdd(iVar9,local_f08,param_2);
          local_4 = 6;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar11 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (iVar11 < 0x14) {
LAB_00485c3d:
            EncodeChecksumDeltaAdd(iVar9,local_454,param_2);
            local_4 = 8;
            bVar3 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar11 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (iVar11 < 0x14) {
              uVar10 = 0x14;
            }
            else {
              EncodeChecksumDeltaAdd(iVar9,local_89c,param_2);
              local_4 = 9;
              bVar3 = true;
              bVar2 = true;
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              uVar10 = PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            }
          }
          else {
            EncodeChecksumDeltaAdd(iVar9,local_1350,param_2);
            local_4 = 7;
            bVar4 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar11 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (iVar11 < 0x65) goto LAB_00485c3d;
            uVar10 = 100;
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(uVar10);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_4 = 8;
          if ((bVar2) && (bVar2 = false, local_888 != 0)) {
            ScrambleChecksumGuardBytes();
            TreeLowerBound(local_1594);
          }
          local_4 = 7;
          if ((bVar3) && (bVar3 = false, local_440 != 0)) {
            ScrambleChecksumGuardBytes();
            TreeLowerBound(local_1594);
          }
          local_4 = 6;
          if ((bVar4) && (bVar4 = false, local_133c != 0)) {
            ScrambleChecksumGuardBytes();
            TreeLowerBound(local_1594);
          }
          local_4 = 0xffffffff;
          if (local_ef4 != 0) {
            ScrambleChecksumGuardBytes();
            TreeLowerBound(local_1594);
          }
          local_15b1 = '\x01';
        }
        iVar9 = local_15a8;
        pbVar18 = (byte *)(local_15a8 + 0xf4c);
        cVar8 = FUN_00406860();
        if (cVar8 != '\0') {
          iVar11 = FUN_00451030(local_15a4);
          *(int *)(iVar9 + 0xf48) = iVar11;
          if (iVar11 != 0) {
            *(undefined4 *)(iVar9 + 0xf50) = 0;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar11 = _rand();
            *pbVar18 = (byte)iVar11;
            iVar11 = _rand();
            bVar15 = *pbVar18;
            *(byte *)(iVar9 + 0xf4d) = (byte)iVar11;
            bVar17 = '\x01' << (bVar15 & 7);
            bVar17 = ~bVar17 & (byte)iVar11 | bVar17;
            *(byte *)(iVar9 + 0xf4d) = bVar17;
            *(byte *)(iVar9 + 0xf4e) = bVar15 + bVar17 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar9 = g_clientContext;
            pbVar18 = (byte *)(g_clientContext + 0x62140);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar11 = _rand();
            *pbVar18 = (byte)iVar11;
            iVar11 = _rand();
            bVar15 = *pbVar18;
            *(byte *)(iVar9 + 0x62141) = (byte)iVar11;
            local_15b2 = '\x01' << (bVar15 & 7);
            bVar17 = ~local_15b2 & (byte)iVar11 | local_15b2;
            *(byte *)(iVar9 + 0x62141) = bVar17;
            *(byte *)(iVar9 + 0x62142) = bVar15 + bVar17 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar9 = local_15a8;
          }
        }
        cVar8 = PeekPacketChecksumBool();
        iVar11 = local_15a4;
        if ((cVar8 == '\0') && (iVar12 = FUN_004511b0(local_15a4), iVar12 != 0)) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar11 = _rand();
          *(byte *)(iVar9 + 0x3918) = (byte)iVar11;
          iVar11 = _rand();
          bVar15 = *(byte *)(iVar9 + 0x3918);
          *(byte *)(iVar9 + 0x3919) = (byte)iVar11;
          bVar17 = '\x01' << (bVar15 & 7);
          bVar17 = ~bVar17 & (byte)iVar11 | bVar17;
          *(byte *)(iVar9 + 0x3919) = bVar17;
          *(byte *)(iVar9 + 0x391a) = bVar15 + bVar17 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar9 = local_15a8;
          iVar11 = local_15a4;
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_1580[0] = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        FUN_00436dc0(iVar11,local_15b8,local_1580[0]);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar12 = PeekPacketChecksumState();
        local_15b2 = iVar12 == 0;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (local_15b2 != 0) {
          local_1580[0] = EncodeChecksumDeltaShr(iVar9 + 0x6ac,local_ce4,8);
          local_4 = 10;
          local_1594[0] = EncodeChecksumDeltaShr(iVar9 + 0x488,local_ac0,8);
          local_4 = 0xb;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_1580[0] = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_1594[0] = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          FUN_00436bd0(iVar11 - local_1594[0],local_15b8 - local_1580[0],
                       *(undefined4 *)(iVar9 + 0x1e50));
          local_4 = 10;
          local_1594[0] = local_aac;
          if (local_aac != 0) {
            ScrambleChecksumGuardBytes();
            TreeLowerBound(local_1580);
            iVar11 = local_15a4;
          }
          local_4 = 0xffffffff;
          local_1594[0] = local_cd0;
          if (local_cd0 != 0) {
            ScrambleChecksumGuardBytes();
            TreeLowerBound(local_1580);
            iVar11 = local_15a4;
          }
        }
        cVar8 = PeekPacketChecksumBool();
        iVar9 = local_15b8;
        if (cVar8 != '\0') {
          FUN_00436ec0(iVar11,local_15b8);
        }
        if (iVar11 < 0) {
LAB_0048631a:
          iVar13 = *(int *)(&DAT_006a7720 + g_clientContext) + -1;
          iVar12 = iVar13;
          if (iVar11 <= iVar13) {
            iVar12 = iVar11;
          }
          if (iVar12 < 0) {
            local_15c0 = 0;
          }
          else if (iVar13 < iVar11) {
            local_15c0 = iVar13;
          }
          iVar11 = *(int *)(&DAT_006a7724 + g_clientContext) + -1;
          iVar12 = iVar11;
          if (iVar9 <= iVar11) {
            iVar12 = iVar9;
          }
          if (iVar12 < -0x113) {
            local_15b8 = -0x113;
          }
          else if (iVar11 < iVar9) {
            local_15b8 = iVar11;
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar9 = local_15a8;
          EncodeOutgoingPacketField(local_15c0 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b8 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15c0);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar11 = _rand();
          *(char *)(iVar9 + 0xf45) = (char)iVar11;
          iVar11 = _rand();
          *(byte *)(iVar9 + 0xf46) = (byte)iVar11;
          bVar15 = '\x01' << (*(byte *)(iVar9 + 0xf45) & 7);
          bVar15 = ~bVar15 & (byte)iVar11 | bVar15;
          *(byte *)(iVar9 + 0xf46) = bVar15;
          *(byte *)(iVar9 + 0xf47) = bVar15 + *(char *)(iVar9 + 0xf45) + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (DAT_0079352a != '\0') {
            uVar10 = 0xf004;
LAB_00486469:
            Replay_AppendEvent(uVar10);
            (&g_replayEventBuffer)[g_replayEventCursor] = *(undefined1 *)(iVar9 + 8);
            piVar1 = (int *)(&DAT_00e9aacd + g_replayEventCursor);
            g_replayEventCursor = g_replayEventCursor + 1;
            *piVar1 = local_15c0;
            piVar1 = (int *)(&DAT_00e9aad0 + g_replayEventCursor);
            g_replayEventCursor = g_replayEventCursor + 4;
            *piVar1 = local_15b8;
LAB_00486e6e:
            g_replayEventCursor = g_replayEventCursor + 4;
            Replay_FlushEvent();
          }
          break;
        }
        if ((((iVar11 < *(int *)(&DAT_006a7720 + g_clientContext)) && (-1 < iVar9)) &&
            (iVar9 < *(int *)(&DAT_006a7724 + g_clientContext))) &&
           (*(char *)(*(int *)(&DAT_006a7720 + g_clientContext) * iVar9 +
                      *(int *)(&DAT_006a773c + g_clientContext) + iVar11) != '\0')) {
          FUN_00458920(&local_15c0,&local_15b8,local_159c,local_1588,local_158c,local_15bc,
                       local_1584,1,0);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar9 = local_15a8;
          EncodeOutgoingPacketField(local_15c0 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b8 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15c0);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar11 = _rand();
          *(char *)(iVar9 + 0xf45) = (char)iVar11;
          iVar11 = _rand();
          *(byte *)(iVar9 + 0xf46) = (byte)iVar11;
          bVar15 = '\x01' << (*(byte *)(iVar9 + 0xf45) & 7);
          bVar15 = ~bVar15 & (byte)iVar11 | bVar15;
          *(byte *)(iVar9 + 0xf46) = bVar15;
          *(byte *)(iVar9 + 0xf47) = bVar15 + *(char *)(iVar9 + 0xf45) + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (DAT_0079352a != '\0') {
            uVar10 = 0xf002;
            goto LAB_00486469;
          }
          break;
        }
        if (((*(int *)(&DAT_006a7720 + g_clientContext) + -1 < iVar11) || (iVar9 < -0x113)) ||
           (*(int *)(&DAT_006a7724 + g_clientContext) + -1 < iVar9)) goto LAB_0048631a;
        local_1588 = local_1588 + param_2;
        local_15c0 = iVar11 + local_1578;
      } while (local_1588 < local_15b0[0]);
    }
  }
  else {
    local_15bc = ((iVar9 - local_15a0) * 0x10000) / iVar13;
    local_1584 = local_15a0 << 0x10;
    if (local_159c < iVar11) {
      local_15a4 = iVar11 + -1;
      local_158c = -1;
    }
    else {
      local_15a4 = iVar11 + 1;
      local_158c = 1;
    }
    local_1594[0] = iVar12 + param_2;
    local_1588 = 0;
    if (0 < local_1594[0]) {
      local_15a0 = local_15bc * param_2;
      local_1598 = local_15a8 + 0x15c0;
      local_1578 = local_158c * param_2;
      local_159c = local_15a4;
      do {
        iVar9 = local_1598;
        local_15b8 = local_15a4;
        local_1584 = local_1584 + local_15a0;
        local_15c0 = local_1584 >> 0x10;
        if ((local_15b1 == '\0') && (iVar11 = FUN_004510f0(local_15c0), iVar11 != 0)) {
          local_15b0[0] = EncodeChecksumDeltaAdd(iVar9,local_1350,param_2);
          local_4 = 0xc;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15b0[0] = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (local_15b0[0] < 0x14) {
LAB_0048661d:
            local_15b0[0] = EncodeChecksumDeltaAdd(iVar9,local_ac0,param_2);
            local_4 = 0xe;
            bVar6 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_15b0[0] = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (local_15b0[0] < 0x14) {
              uVar10 = 0x14;
            }
            else {
              EncodeChecksumDeltaAdd(iVar9,local_ce4,param_2);
              local_4 = 0xf;
              bVar6 = true;
              bVar5 = true;
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              uVar10 = PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            }
          }
          else {
            local_15b0[0] = EncodeChecksumDeltaAdd(iVar9,local_f08,param_2);
            local_4 = 0xd;
            bVar7 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_15b0[0] = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (local_15b0[0] < 0x65) goto LAB_0048661d;
            uVar10 = 100;
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(uVar10);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar9 = local_cd0;
          local_4 = 0xe;
          if ((bVar5) && (bVar5 = false, local_cd0 != 0)) {
            ScrambleChecksumGuardBytes();
            local_15b0[0] = iVar9;
            TreeLowerBound(local_1580);
          }
          iVar9 = local_aac;
          local_4 = 0xd;
          if ((bVar6) && (bVar6 = false, local_aac != 0)) {
            ScrambleChecksumGuardBytes();
            local_15b0[0] = iVar9;
            TreeLowerBound(local_1580);
          }
          iVar9 = local_ef4;
          local_4 = 0xc;
          if ((bVar7) && (bVar7 = false, local_ef4 != 0)) {
            ScrambleChecksumGuardBytes();
            local_15b0[0] = iVar9;
            TreeLowerBound(local_1580);
          }
          iVar9 = local_133c;
          local_4 = 0xffffffff;
          if (local_133c != 0) {
            ScrambleChecksumGuardBytes();
            local_15b0[0] = iVar9;
            TreeLowerBound(local_1580);
          }
          local_15b1 = '\x01';
        }
        iVar9 = local_15a8;
        pbVar18 = (byte *)(local_15a8 + 0xf4c);
        cVar8 = FUN_00406860();
        if (cVar8 != '\0') {
          iVar11 = FUN_00451030(local_15c0);
          *(int *)(iVar9 + 0xf48) = iVar11;
          if (iVar11 != 0) {
            *(undefined4 *)(iVar9 + 0xf50) = 0;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar11 = _rand();
            *pbVar18 = (byte)iVar11;
            iVar11 = _rand();
            bVar15 = *pbVar18;
            *(byte *)(iVar9 + 0xf4d) = (byte)iVar11;
            bVar17 = '\x01' << (bVar15 & 7);
            bVar17 = ~bVar17 & (byte)iVar11 | bVar17;
            *(byte *)(iVar9 + 0xf4d) = bVar17;
            *(byte *)(iVar9 + 0xf4e) = bVar17 + bVar15 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar9 = g_clientContext;
            pbVar18 = (byte *)(g_clientContext + 0x62140);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar11 = _rand();
            *pbVar18 = (byte)iVar11;
            iVar11 = _rand();
            bVar15 = *pbVar18;
            *(byte *)(iVar9 + 0x62141) = (byte)iVar11;
            bVar17 = '\x01' << (bVar15 & 7);
            bVar15 = *pbVar18;
            bVar17 = ~bVar17 & (byte)iVar11 | bVar17;
            *(byte *)(iVar9 + 0x62141) = bVar17;
            *(byte *)(iVar9 + 0x62142) = bVar17 + bVar15 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar9 = local_15a8;
          }
        }
        pbVar18 = (byte *)(iVar9 + 0x3918);
        cVar8 = PeekPacketChecksumBool();
        if ((cVar8 == '\0') && (iVar11 = FUN_004511b0(local_15c0), iVar11 != 0)) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar11 = _rand();
          *pbVar18 = (byte)iVar11;
          iVar11 = _rand();
          *(byte *)(iVar9 + 0x3919) = (byte)iVar11;
          bVar15 = '\x01' << (*pbVar18 & 7);
          bVar15 = ~bVar15 & (byte)iVar11 | bVar15;
          *(byte *)(iVar9 + 0x3919) = bVar15;
          *(byte *)(iVar9 + 0x391a) = bVar15 + *pbVar18 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar10 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        FUN_00436dc0(local_15c0,local_15a4,uVar10);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar11 = PeekPacketChecksumState();
        local_15b2 = iVar11 == 0;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (local_15b2 != 0) {
          EncodeChecksumDeltaShr(iVar9 + 0x6ac,local_230,8);
          local_4 = 0x10;
          local_15b0[0] = EncodeChecksumDeltaShr(iVar9 + 0x488,local_678,8);
          local_4 = 0x11;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar11 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15b0[0] = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          FUN_00436bd0(local_15c0 - local_15b0[0],local_15a4 - iVar11,
                       *(undefined4 *)(iVar9 + 0x1e50));
          iVar9 = local_664;
          local_4 = 0x10;
          if (local_664 != 0) {
            ScrambleChecksumGuardBytes();
            local_15b0[0] = iVar9;
            TreeLowerBound(local_1580);
          }
          iVar9 = local_21c;
          local_4 = 0xffffffff;
          if (local_21c != 0) {
            ScrambleChecksumGuardBytes();
            local_15b0[0] = iVar9;
            TreeLowerBound(local_1580);
          }
        }
        cVar8 = PeekPacketChecksumBool();
        iVar11 = local_15a4;
        iVar9 = local_15c0;
        if (cVar8 != '\0') {
          FUN_00436ec0(local_15c0,local_15a4);
        }
        if (iVar9 < 0) {
LAB_00486cde:
          iVar13 = *(int *)(&DAT_006a7720 + g_clientContext) + -1;
          iVar12 = iVar13;
          if (iVar9 <= iVar13) {
            iVar12 = iVar9;
          }
          if (iVar12 < 0) {
            local_15c0 = 0;
          }
          else if (iVar13 < iVar9) {
            local_15c0 = iVar13;
          }
          iVar9 = *(int *)(&DAT_006a7724 + g_clientContext) + -1;
          iVar12 = iVar9;
          if (iVar11 <= iVar9) {
            iVar12 = iVar11;
          }
          if (iVar12 < -0x113) {
            local_15b8 = -0x113;
          }
          else if (iVar9 < iVar11) {
            local_15b8 = iVar9;
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar9 = local_15a8;
          EncodeOutgoingPacketField(local_15c0 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b8 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15c0);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar11 = _rand();
          *(char *)(iVar9 + 0xf45) = (char)iVar11;
          iVar11 = _rand();
          *(byte *)(iVar9 + 0xf46) = (byte)iVar11;
          bVar15 = '\x01' << (*(byte *)(iVar9 + 0xf45) & 7);
          bVar15 = ~bVar15 & (byte)iVar11 | bVar15;
          *(byte *)(iVar9 + 0xf46) = bVar15;
          *(byte *)(iVar9 + 0xf47) = bVar15 + *(char *)(iVar9 + 0xf45) + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (DAT_0079352a != '\0') {
            Replay_AppendEvent(0xf004);
            (&g_replayEventBuffer)[g_replayEventCursor] = *(undefined1 *)(iVar9 + 8);
LAB_00486e42:
            piVar1 = (int *)(&DAT_00e9aacd + g_replayEventCursor);
            g_replayEventCursor = g_replayEventCursor + 1;
            *piVar1 = local_15c0;
            piVar1 = (int *)(&DAT_00e9aad0 + g_replayEventCursor);
            g_replayEventCursor = g_replayEventCursor + 4;
            *piVar1 = local_15b8;
            goto LAB_00486e6e;
          }
          break;
        }
        if ((((iVar9 < *(int *)(&DAT_006a7720 + g_clientContext)) && (-1 < iVar11)) &&
            (iVar11 < *(int *)(&DAT_006a7724 + g_clientContext))) &&
           (*(char *)(iVar11 * *(int *)(&DAT_006a7720 + g_clientContext) +
                      *(int *)(&DAT_006a773c + g_clientContext) + iVar9) != '\0')) {
          FUN_00458a00(&local_15c0,&local_15b8,local_159c,local_1588,local_158c,local_15bc,
                       local_1584,1,0);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar9 = local_15a8;
          EncodeOutgoingPacketField(local_15c0 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b8 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15c0);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar11 = _rand();
          *(char *)(iVar9 + 0xf45) = (char)iVar11;
          iVar11 = _rand();
          *(byte *)(iVar9 + 0xf46) = (byte)iVar11;
          bVar15 = '\x01' << (*(byte *)(iVar9 + 0xf45) & 7);
          bVar15 = ~bVar15 & (byte)iVar11 | bVar15;
          *(byte *)(iVar9 + 0xf46) = bVar15;
          *(byte *)(iVar9 + 0xf47) = bVar15 + *(char *)(iVar9 + 0xf45) + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (DAT_0079352a != '\0') {
            Replay_AppendEvent(0xf002);
            (&g_replayEventBuffer)[g_replayEventCursor] = *(undefined1 *)(iVar9 + 8);
            goto LAB_00486e42;
          }
          break;
        }
        if (((*(int *)(&DAT_006a7720 + g_clientContext) + -1 < iVar9) || (iVar11 < -0x113)) ||
           (*(int *)(&DAT_006a7724 + g_clientContext) + -1 < iVar11)) goto LAB_00486cde;
        local_1588 = local_1588 + param_2;
        local_15a4 = iVar11 + local_1578;
      } while (local_1588 < local_1594[0]);
    }
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

