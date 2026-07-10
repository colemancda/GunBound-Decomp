/* FUN_004a7050 - 0x004a7050 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void __thiscall FUN_004a7050(int param_1,int param_2)

{
  int *piVar1;
  uint *puVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  bool bVar8;
  bool bVar9;
  char cVar10;
  undefined4 uVar11;
  byte bVar12;
  int iVar13;
  int iVar14;
  uint uVar15;
  byte bVar16;
  byte bVar17;
  int iVar18;
  byte *pbVar19;
  undefined4 *unaff_FS_OFFSET;
  uint local_15c4;
  byte *local_15bc [2];
  int local_15b4;
  int local_15b0;
  byte *local_15ac [2];
  uint local_15a4;
  int local_15a0;
  byte *local_159c;
  int local_1598;
  int local_1594;
  int local_1590;
  uint local_158c [2];
  int local_1584;
  int local_1580;
  int local_157c [2];
  undefined1 local_1574 [20];
  int local_1560;
  undefined1 local_1350 [20];
  int local_133c;
  undefined1 local_112c [20];
  byte *local_1118;
  undefined1 local_f08 [20];
  byte *local_ef4;
  undefined1 local_ce4 [20];
  byte *local_cd0;
  undefined1 local_ac0 [20];
  byte *local_aac;
  undefined1 local_89c [20];
  byte *local_888;
  undefined1 local_678 [20];
  byte *local_664;
  undefined1 local_454 [20];
  byte *local_440;
  undefined1 local_230 [20];
  byte *local_21c;
  undefined4 uStack_10;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053e8c0;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uStack_10 = 0x4a706f;
  local_15ac[0] = (byte *)(param_1 + 0x40);
  bVar9 = false;
  bVar8 = false;
  bVar7 = false;
  bVar6 = false;
  bVar5 = false;
  bVar4 = false;
  bVar3 = false;
  local_15b0 = param_1;
  FUN_0040b180(local_15ac[0],local_1574,8);
  local_4 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_1594 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if (local_1560 != 0) {
    FUN_0040a240();
    FUN_0040b540(local_158c);
  }
  local_1584 = param_1 + 0x264;
  FUN_0040b180(local_1584,local_1574,8);
  local_4 = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_1598 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if (local_1560 != 0) {
    FUN_0040a240();
    FUN_0040b540(local_158c);
  }
  uVar11 = FUN_0040aca0(local_15ac[0],local_1350,param_1 + 0x488);
  local_4 = 2;
  FUN_0040b180(uVar11,local_1574,8);
  SUBFIELD(local_4,0,undefined1) = 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_157c[0] = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),2);
  if (local_1560 != 0) {
    FUN_0040a240();
    FUN_0040b540(local_158c);
  }
  local_4 = 0xffffffff;
  if (local_133c != 0) {
    FUN_0040a240();
    FUN_0040b540(local_158c);
  }
  uVar11 = FUN_0040aca0(local_1584,local_1574,local_15b0 + 0x6ac);
  local_4 = 4;
  FUN_0040b180(uVar11,local_1350,8);
  SUBFIELD(local_4,0,undefined1) = 5;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_15c4 = PeekPacketChecksumState();
  local_158c[0] = local_15c4;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),4);
  if (local_133c != 0) {
    FUN_0040a240();
    FUN_0040b540(local_15bc);
  }
  local_4 = 0xffffffff;
  if (local_1560 != 0) {
    FUN_0040a240();
    FUN_0040b540(local_15bc);
  }
  uVar15 = local_157c[0] - local_1594 >> 0x1f;
  iVar13 = (local_157c[0] - local_1594 ^ uVar15) - uVar15;
  uVar15 = (int)(local_15c4 - local_1598) >> 0x1f;
  iVar18 = (local_15c4 - local_1598 ^ uVar15) - uVar15;
  iVar14 = iVar13 + 1;
  local_15bc[0] = (byte *)(iVar18 + 1);
  local_1590 = 0;
  if ((int)local_15bc[0] < iVar14) {
    iVar14 = (int)((local_1598 - local_15c4) * 0x10000) / iVar14;
    local_1598 = local_15c4 << 0x10;
    local_1594 = (uint)(local_157c[0] <= local_1594) * 2 + -1;
    local_15bc[0] = (byte *)(iVar13 + param_2);
    if (0 < (int)local_15bc[0]) {
      local_1584 = iVar14 * param_2;
      local_15a0 = local_15b0 + 0x15c0;
      local_1580 = local_1594 * param_2;
      local_15c4 = local_157c[0];
      do {
        iVar13 = local_15a0;
        local_1598 = local_1598 + local_1584;
        local_15a4 = local_1598 >> 0x10;
        local_15b4 = local_15c4;
        if ((!bVar3) && (iVar18 = FUN_004510f0(local_15c4), iVar18 != 0)) {
          local_15ac[0] = (byte *)FUN_0040a5f0(iVar13,local_112c,param_2);
          local_4 = 6;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15ac[0] = (byte *)PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if ((int)local_15ac[0] < 0x14) {
LAB_004a7499:
            local_15ac[0] = (byte *)FUN_0040a5f0(iVar13,local_89c,param_2);
            local_4 = 8;
            bVar5 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_15ac[0] = (byte *)PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if ((int)local_15ac[0] < 0x14) {
              uVar11 = 0x14;
            }
            else {
              FUN_0040a5f0(iVar13,local_454,param_2);
              local_4 = 9;
              bVar5 = true;
              bVar4 = true;
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              uVar11 = PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            }
          }
          else {
            local_15ac[0] = (byte *)FUN_0040a5f0(iVar13,local_ac0,param_2);
            local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),7);
            bVar6 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_15ac[0] = (byte *)PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if ((int)local_15ac[0] < 0x65) goto LAB_004a7499;
            uVar11 = 100;
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(uVar11);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          pbVar19 = local_440;
          local_4 = 8;
          if ((bVar4) && (bVar4 = false, local_440 != (byte *)0x0)) {
            FUN_0040a240();
            local_15ac[0] = pbVar19;
            FUN_0040b540(local_158c);
          }
          pbVar19 = local_888;
          local_4 = 7;
          if ((bVar5) && (bVar5 = false, local_888 != (byte *)0x0)) {
            FUN_0040a240();
            local_15ac[0] = pbVar19;
            FUN_0040b540(local_158c);
          }
          pbVar19 = local_aac;
          local_4 = 6;
          if ((bVar6) && (bVar6 = false, local_aac != (byte *)0x0)) {
            FUN_0040a240();
            local_15ac[0] = pbVar19;
            FUN_0040b540(local_158c);
          }
          pbVar19 = local_1118;
          local_4 = 0xffffffff;
          if (local_1118 != (byte *)0x0) {
            FUN_0040a240();
            local_15ac[0] = pbVar19;
            FUN_0040b540(local_158c);
          }
          bVar3 = true;
        }
        iVar13 = local_15b0;
        pbVar19 = (byte *)(local_15b0 + 0xf4c);
        cVar10 = FUN_00406860();
        if (cVar10 != '\0') {
          iVar18 = FUN_00451030(local_15c4);
          *(int *)(iVar13 + 0xf48) = iVar18;
          if (iVar18 != 0) {
            *(undefined4 *)(iVar13 + 0xf50) = 0;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar18 = _rand();
            *pbVar19 = (byte)iVar18;
            iVar18 = _rand();
            bVar17 = *pbVar19;
            *(byte *)(iVar13 + 0xf4d) = (byte)iVar18;
            bVar16 = '\x01' << (bVar17 & 7);
            bVar16 = ~bVar16 & (byte)iVar18 | bVar16;
            *(byte *)(iVar13 + 0xf4d) = bVar16;
            *(byte *)(iVar13 + 0xf4e) = bVar17 + bVar16 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar13 = g_clientContext;
            pbVar19 = (byte *)(g_clientContext + 0x62140);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar18 = _rand();
            *pbVar19 = (byte)iVar18;
            uVar15 = _rand();
            local_15ac[0] = (byte *)(uVar15 & 0x800000ff);
            if ((int)local_15ac[0] < 0) {
              local_15ac[0] = (byte *)(((uint)(local_15ac[0] + -1) | 0xffffff00) + 1);
            }
            bVar17 = *pbVar19;
            *(byte *)(iVar13 + 0x62141) = (byte)local_15ac[0];
            bVar16 = '\x01' << (bVar17 & 7);
            bVar16 = ~bVar16 & (byte)local_15ac[0] | bVar16;
            *(byte *)(iVar13 + 0x62141) = bVar16;
            *(byte *)(iVar13 + 0x62142) = bVar17 + bVar16 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar13 = local_15b0;
          }
        }
        pbVar19 = (byte *)(iVar13 + 0x3918);
        local_15ac[0] = pbVar19;
        cVar10 = PeekPacketChecksumBool();
        if ((cVar10 == '\0') && (iVar18 = FUN_004511b0(local_15c4), iVar18 != 0)) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar18 = _rand();
          *pbVar19 = (byte)iVar18;
          iVar18 = _rand();
          *(byte *)(iVar13 + 0x3919) = (byte)iVar18;
          bVar17 = '\x01' << (*pbVar19 & 7);
          bVar17 = ~bVar17 & (byte)iVar18 | bVar17;
          *(byte *)(iVar13 + 0x3919) = bVar17;
          *(byte *)(iVar13 + 0x391a) = *pbVar19 + bVar17 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar13 = local_15b0;
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar11 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        FUN_00436dc0(local_15c4,local_15a4,uVar11);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar18 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar18 == 0) {
          FUN_0040b180(iVar13 + 0x6ac,local_ce4,8);
          local_4 = 10;
          local_159c = (byte *)FUN_0040b180(iVar13 + 0x488,local_f08,8);
          SUBFIELD(local_4,0,undefined1) = 0xb;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar18 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_159c = (byte *)PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          FUN_00436bd0(local_15c4 - (int)local_159c,local_15a4 - iVar18,
                       *(undefined4 *)(iVar13 + 0x1e50));
          pbVar19 = local_ef4;
          local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),10);
          if (local_ef4 != (byte *)0x0) {
            FUN_0040a240();
            local_159c = pbVar19;
            FUN_0040b540(local_158c);
          }
          pbVar19 = local_cd0;
          local_4 = 0xffffffff;
          if (local_cd0 != (byte *)0x0) {
            FUN_0040a240();
            local_159c = pbVar19;
            FUN_0040b540(local_158c);
          }
        }
        uVar15 = local_15a4;
        cVar10 = PeekPacketChecksumBool();
        if (cVar10 != '\0') {
          FUN_00436ec0(local_15c4,uVar15);
        }
        if ((((-1 < (int)local_15c4) && ((int)local_15c4 < *(int *)(&DAT_006a7720 + g_clientContext)))
            && (-1 < (int)uVar15)) &&
           (((int)uVar15 < *(int *)(&DAT_006a7724 + g_clientContext) &&
            (*(char *)(*(int *)(&DAT_006a7720 + g_clientContext) * uVar15 +
                       *(int *)(&DAT_006a773c + g_clientContext) + local_15c4) != '\0')))) {
          FUN_00458920(&local_15b4,&local_15a4,local_157c[0],local_1590,local_1594,iVar14,local_1598
                       ,1,0);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar14 = local_15b0;
          EncodeOutgoingPacketField(local_15b4 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15a4 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b4);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15a4);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar13 = _rand();
          *(char *)(iVar14 + 0xf45) = (char)iVar13;
          uVar15 = _rand();
          local_15bc[0] = (byte *)(uVar15 & 0x800000ff);
          if ((int)local_15bc[0] < 0) {
            local_15bc[0] = (byte *)(((uint)(local_15bc[0] + -1) | 0xffffff00) + 1);
          }
          bVar17 = *(byte *)(iVar14 + 0xf45);
          *(byte *)(iVar14 + 0xf46) = (byte)local_15bc[0];
          bVar16 = '\x01' << (bVar17 & 7);
          bVar12 = ~bVar16 & (byte)local_15bc[0];
LAB_004a82c9:
          *(byte *)(iVar14 + 0xf47) = bVar17 + (bVar12 | bVar16) + -0x34;
          *(byte *)(iVar14 + 0xf46) = bVar12 | bVar16;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (DAT_0079352a != '\0') {
            Replay_AppendEvent(0xf002);
            (&g_replayEventBuffer)[g_replayEventCursor] = *(undefined1 *)(iVar14 + 8);
            piVar1 = (int *)(&DAT_00e9aacd + g_replayEventCursor);
            g_replayEventCursor = g_replayEventCursor + 1;
            *piVar1 = local_15b4;
            puVar2 = (uint *)(&DAT_00e9aad0 + g_replayEventCursor);
            g_replayEventCursor = g_replayEventCursor + 4;
            *puVar2 = local_15a4;
            g_replayEventCursor = g_replayEventCursor + 4;
            Replay_FlushEvent();
          }
          break;
        }
        local_1590 = local_1590 + param_2;
        local_15c4 = local_15c4 + local_1580;
      } while (local_1590 < (int)local_15bc[0]);
    }
  }
  else {
    iVar14 = ((local_1594 - local_157c[0]) * 0x10000) / (int)local_15bc[0];
    local_1594 = (uint)((int)local_15c4 <= local_1598) * 2 + -1;
    local_159c = (byte *)(iVar18 + param_2);
    if (0 < (int)local_159c) {
      local_1584 = iVar14 * param_2;
      local_15a0 = local_15b0 + 0x15c0;
      local_1580 = local_1594 * param_2;
      local_1598 = local_157c[0] << 0x10;
      do {
        iVar13 = local_15a0;
        local_1598 = local_1598 + local_1584;
        local_15b4 = local_1598 >> 0x10;
        local_15a4 = local_15c4;
        if ((!bVar3) && (iVar18 = FUN_004510f0(local_15b4), iVar18 != 0)) {
          local_15bc[0] = (byte *)FUN_0040a5f0(iVar13,local_ac0,param_2);
          local_4 = 0xc;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15bc[0] = (byte *)PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if ((int)local_15bc[0] < 0x14) {
LAB_004a7c59:
            local_15bc[0] = (byte *)FUN_0040a5f0(iVar13,local_f08,param_2);
            local_4 = 0xe;
            bVar8 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_15bc[0] = (byte *)PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if ((int)local_15bc[0] < 0x14) {
              uVar11 = 0x14;
            }
            else {
              FUN_0040a5f0(iVar13,local_ce4,param_2);
              local_4 = 0xf;
              bVar8 = true;
              bVar7 = true;
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              uVar11 = PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            }
          }
          else {
            local_15bc[0] = (byte *)FUN_0040a5f0(iVar13,local_112c,param_2);
            local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0xd);
            bVar9 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_15bc[0] = (byte *)PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if ((int)local_15bc[0] < 0x65) goto LAB_004a7c59;
            uVar11 = 100;
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(uVar11);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          pbVar19 = local_cd0;
          local_4 = 0xe;
          if ((bVar7) && (bVar7 = false, local_cd0 != (byte *)0x0)) {
            FUN_0040a240();
            local_15bc[0] = pbVar19;
            FUN_0040b540(local_15ac);
          }
          pbVar19 = local_ef4;
          local_4 = 0xd;
          if ((bVar8) && (bVar8 = false, local_ef4 != (byte *)0x0)) {
            FUN_0040a240();
            local_15bc[0] = pbVar19;
            FUN_0040b540(local_15ac);
          }
          pbVar19 = local_1118;
          local_4 = 0xc;
          if ((bVar9) && (bVar9 = false, local_1118 != (byte *)0x0)) {
            FUN_0040a240();
            local_15bc[0] = pbVar19;
            FUN_0040b540(local_15ac);
          }
          pbVar19 = local_aac;
          local_4 = 0xffffffff;
          if (local_aac != (byte *)0x0) {
            FUN_0040a240();
            local_15bc[0] = pbVar19;
            FUN_0040b540(local_15ac);
          }
          bVar3 = true;
        }
        iVar13 = local_15b0;
        pbVar19 = (byte *)(local_15b0 + 0xf4c);
        cVar10 = FUN_00406860();
        if (cVar10 != '\0') {
          iVar18 = FUN_00451030(local_15b4);
          *(int *)(iVar13 + 0xf48) = iVar18;
          if (iVar18 != 0) {
            *(undefined4 *)(iVar13 + 0xf50) = 0;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar18 = _rand();
            *pbVar19 = (byte)iVar18;
            iVar18 = _rand();
            bVar17 = *pbVar19;
            *(byte *)(iVar13 + 0xf4d) = (byte)iVar18;
            bVar16 = '\x01' << (bVar17 & 7);
            bVar16 = ~bVar16 & (byte)iVar18 | bVar16;
            *(byte *)(iVar13 + 0xf4d) = bVar16;
            *(byte *)(iVar13 + 0xf4e) = bVar17 + bVar16 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar13 = g_clientContext;
            pbVar19 = (byte *)(g_clientContext + 0x62140);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar18 = _rand();
            *pbVar19 = (byte)iVar18;
            uVar15 = _rand();
            local_15bc[0] = (byte *)(uVar15 & 0x800000ff);
            if ((int)local_15bc[0] < 0) {
              local_15bc[0] = (byte *)(((uint)(local_15bc[0] + -1) | 0xffffff00) + 1);
            }
            bVar17 = *pbVar19;
            *(byte *)(iVar13 + 0x62141) = (byte)local_15bc[0];
            bVar16 = '\x01' << (bVar17 & 7);
            bVar16 = ~bVar16 & (byte)local_15bc[0] | bVar16;
            *(byte *)(iVar13 + 0x62141) = bVar16;
            *(byte *)(iVar13 + 0x62142) = bVar17 + bVar16 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar13 = local_15b0;
          }
        }
        pbVar19 = (byte *)(iVar13 + 0x3918);
        local_15ac[0] = pbVar19;
        cVar10 = PeekPacketChecksumBool();
        if ((cVar10 == '\0') && (iVar18 = FUN_004511b0(local_15b4), iVar18 != 0)) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar18 = _rand();
          *pbVar19 = (byte)iVar18;
          iVar18 = _rand();
          *(byte *)(iVar13 + 0x3919) = (byte)iVar18;
          bVar17 = '\x01' << (*pbVar19 & 7);
          bVar17 = ~bVar17 & (byte)iVar18 | bVar17;
          *(byte *)(iVar13 + 0x3919) = bVar17;
          *(byte *)(iVar13 + 0x391a) = *pbVar19 + bVar17 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar13 = local_15b0;
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar11 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        FUN_00436dc0(local_15b4,local_15c4,uVar11);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar18 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar18 == 0) {
          FUN_0040b180(iVar13 + 0x6ac,local_230,8);
          local_4 = 0x10;
          local_15bc[0] = (byte *)FUN_0040b180(iVar13 + 0x488,local_678,8);
          SUBFIELD(local_4,0,undefined1) = 0x11;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar18 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15bc[0] = (byte *)PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          FUN_00436bd0(local_15b4 - (int)local_15bc[0],local_15c4 - iVar18,
                       *(undefined4 *)(iVar13 + 0x1e50));
          pbVar19 = local_664;
          local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x10);
          if (local_664 != (byte *)0x0) {
            FUN_0040a240();
            local_15bc[0] = pbVar19;
            FUN_0040b540(local_157c);
          }
          pbVar19 = local_21c;
          local_4 = 0xffffffff;
          if (local_21c != (byte *)0x0) {
            FUN_0040a240();
            local_15bc[0] = pbVar19;
            FUN_0040b540(local_157c);
          }
        }
        iVar13 = local_15b4;
        cVar10 = PeekPacketChecksumBool();
        if (cVar10 != '\0') {
          FUN_00436ec0(iVar13,local_15c4);
        }
        if ((((-1 < iVar13) && (iVar13 < *(int *)(&DAT_006a7720 + g_clientContext))) &&
            (-1 < (int)local_15c4)) &&
           (((int)local_15c4 < *(int *)(&DAT_006a7724 + g_clientContext) &&
            (*(char *)(*(int *)(&DAT_006a7720 + g_clientContext) * local_15c4 +
                       *(int *)(&DAT_006a773c + g_clientContext) + iVar13) != '\0')))) {
          FUN_00458a00(&local_15b4,&local_15a4,local_158c[0],local_1590,local_1594,iVar14,local_1598
                       ,1,0);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar14 = local_15b0;
          EncodeOutgoingPacketField(local_15b4 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15a4 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b4);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15a4);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar13 = _rand();
          *(char *)(iVar14 + 0xf45) = (char)iVar13;
          local_158c[0] = _rand();
          local_158c[0] = local_158c[0] & 0x800000ff;
          if ((int)local_158c[0] < 0) {
            local_158c[0] = (local_158c[0] - 1 | 0xffffff00) + 1;
          }
          bVar17 = *(byte *)(iVar14 + 0xf45);
          *(byte *)(iVar14 + 0xf46) = (byte)local_158c[0];
          bVar16 = '\x01' << (bVar17 & 7);
          bVar12 = ~bVar16 & (byte)local_158c[0];
          goto LAB_004a82c9;
        }
        local_1590 = local_1590 + param_2;
        local_15c4 = local_15c4 + local_1580;
      } while (local_1590 < (int)local_159c);
    }
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

