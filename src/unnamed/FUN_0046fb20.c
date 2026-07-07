/* FUN_0046fb20 - 0x0046fb20 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void __thiscall FUN_0046fb20(int param_1,int param_2)

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
  undefined4 uVar10;
  int iVar11;
  int iVar12;
  byte bVar13;
  uint uVar14;
  int iVar15;
  int iVar16;
  byte *pbVar17;
  undefined4 *unaff_FS_OFFSET;
  int local_15bc;
  int local_15b8;
  int local_15b4;
  int local_15b0;
  char local_15a9;
  uint local_15a8 [2];
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
  puStack_8 = &LAB_0053fc80;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uStack_10 = 0x46fb3f;
  local_1584 = param_1 + 0x40;
  bVar7 = false;
  bVar6 = false;
  bVar5 = false;
  bVar4 = false;
  bVar3 = false;
  bVar2 = false;
  local_15a9 = '\0';
  local_159c = param_1;
  FUN_0040b180(local_1584,local_1574,8);
  local_4 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_1590 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  local_15b8 = local_1560;
  if (local_1560 != 0) {
    FUN_0040a240();
    FUN_0040b540(local_15a8);
  }
  local_158c = param_1 + 0x264;
  FUN_0040b180(local_158c,local_1574,8);
  local_4 = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_15a0 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  local_15b8 = local_1560;
  if (local_1560 != 0) {
    FUN_0040a240();
    FUN_0040b540(local_15a8);
  }
  uVar10 = FUN_0040aca0(local_1584,local_ac0,param_1 + 0x488);
  local_4 = 2;
  FUN_0040b180(uVar10,local_1574,8);
  local_4._0_1_ = 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_1588 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar11 = local_1560;
  local_4 = CONCAT31(local_4._1_3_,2);
  if (local_1560 != 0) {
    FUN_0040a240();
    local_15b8 = iVar11;
    FUN_0040b540(local_15a8);
  }
  iVar11 = local_aac;
  local_4 = 0xffffffff;
  if (local_aac != 0) {
    FUN_0040a240();
    local_15b8 = iVar11;
    FUN_0040b540(local_15a8);
  }
  uVar10 = FUN_0040aca0(local_158c,local_1574,local_159c + 0x6ac);
  local_4 = 4;
  FUN_0040b180(uVar10,local_ac0,8);
  local_4._0_1_ = 5;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar11 = PeekPacketChecksumState();
  local_1584 = iVar11;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = CONCAT31(local_4._1_3_,4);
  local_15b8 = local_aac;
  if (local_aac != 0) {
    FUN_0040a240();
    FUN_0040b540(local_15a8);
  }
  local_4 = 0xffffffff;
  local_15b8 = local_1560;
  if (local_1560 != 0) {
    FUN_0040a240();
    FUN_0040b540(local_15a8);
  }
  uVar14 = local_1588 - local_1590 >> 0x1f;
  iVar12 = (local_1588 - local_1590 ^ uVar14) - uVar14;
  uVar14 = iVar11 - local_15a0 >> 0x1f;
  iVar15 = (iVar11 - local_15a0 ^ uVar14) - uVar14;
  local_158c = iVar12 + 1;
  iVar16 = iVar15 + 1;
  local_1598 = 0;
  if (iVar16 < local_158c) {
    local_158c = ((local_15a0 - iVar11) * 0x10000) / local_158c;
    local_1594 = iVar11 << 0x10;
    local_1590 = (uint)(local_1588 <= local_1590) * 2 + -1;
    local_15a8[0] = iVar12 + param_2;
    if (0 < (int)local_15a8[0]) {
      local_15b8 = local_158c * param_2;
      local_15a0 = local_159c + 0x15c0;
      local_1578 = local_1590 * param_2;
      local_15b0 = local_1588;
      do {
        local_1594 = local_1594 + local_15b8;
        local_15b4 = local_1594 >> 0x10;
        local_15bc = local_15b0;
        if ((local_15a9 == '\0') &&
           (iVar15 = FUN_004510f0(local_15b0), iVar11 = local_15a0, iVar15 != 0)) {
          FUN_0040a5f0(local_15a0,local_112c,param_2);
          local_4 = 6;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar15 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (iVar15 < 0x14) {
LAB_0046ff52:
            FUN_0040a5f0(iVar11,local_89c,param_2);
            local_4 = 8;
            bVar3 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar15 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (iVar15 < 0x14) {
              uVar10 = 0x14;
            }
            else {
              FUN_0040a5f0(iVar11,local_454,param_2);
              local_4 = 9;
              bVar3 = true;
              bVar2 = true;
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              uVar10 = PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            }
          }
          else {
            FUN_0040a5f0(iVar11,local_1350,param_2);
            local_4 = CONCAT31(local_4._1_3_,7);
            bVar4 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar15 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (iVar15 < 0x65) goto LAB_0046ff52;
            uVar10 = 100;
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(uVar10);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_4 = 8;
          if ((bVar2) && (bVar2 = false, local_440 != 0)) {
            FUN_0040a240();
            FUN_0040b540(local_1580);
          }
          local_4 = 7;
          if ((bVar3) && (bVar3 = false, local_888 != 0)) {
            FUN_0040a240();
            FUN_0040b540(local_1580);
          }
          local_4 = 6;
          if ((bVar4) && (bVar4 = false, local_133c != 0)) {
            FUN_0040a240();
            FUN_0040b540(local_1580);
          }
          local_4 = 0xffffffff;
          if (local_1118 != 0) {
            FUN_0040a240();
            FUN_0040b540(local_1580);
          }
          local_15a9 = '\x01';
        }
        iVar11 = local_159c;
        pbVar17 = (byte *)(local_159c + 0xf4c);
        cVar8 = FUN_00406860();
        if (cVar8 != '\0') {
          iVar15 = FUN_00451030(local_15b0);
          *(int *)(iVar11 + 0xf48) = iVar15;
          if (iVar15 != 0) {
            *(undefined4 *)(iVar11 + 0xf50) = 0;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar15 = _rand();
            *pbVar17 = (byte)iVar15;
            iVar15 = _rand();
            bVar13 = *pbVar17;
            *(byte *)(iVar11 + 0xf4d) = (byte)iVar15;
            bVar9 = '\x01' << (bVar13 & 7);
            bVar9 = ~bVar9 & (byte)iVar15 | bVar9;
            *(byte *)(iVar11 + 0xf4d) = bVar9;
            *(byte *)(iVar11 + 0xf4e) = bVar13 + bVar9 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar15 = DAT_005b3484;
            pbVar17 = (byte *)(DAT_005b3484 + 0x62140);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar12 = _rand();
            *pbVar17 = (byte)iVar12;
            iVar12 = _rand();
            bVar13 = *pbVar17;
            *(byte *)(iVar15 + 0x62141) = (byte)iVar12;
            bVar9 = '\x01' << (bVar13 & 7);
            bVar9 = ~bVar9 & (byte)iVar12 | bVar9;
            *(byte *)(iVar15 + 0x62141) = bVar9;
            *(byte *)(iVar15 + 0x62142) = bVar13 + bVar9 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
        }
        cVar8 = FUN_004065a0();
        if ((cVar8 == '\0') && (iVar15 = FUN_004511b0(local_15b0), iVar15 != 0)) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar15 = _rand();
          *(byte *)(iVar11 + 0x3918) = (byte)iVar15;
          iVar15 = _rand();
          bVar13 = *(byte *)(iVar11 + 0x3918);
          *(byte *)(iVar11 + 0x3919) = (byte)iVar15;
          bVar9 = '\x01' << (bVar13 & 7);
          bVar9 = ~bVar9 & (byte)iVar15 | bVar9;
          *(byte *)(iVar11 + 0x3919) = bVar9;
          *(byte *)(iVar11 + 0x391a) = bVar13 + bVar9 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar10 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        FUN_00436dc0(local_15b0,local_15b4,uVar10);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar15 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar15 == 0) {
          FUN_0040b180(iVar11 + 0x6ac,local_ce4,8);
          local_4 = 10;
          FUN_0040b180(iVar11 + 0x488,local_f08,8);
          local_4._0_1_ = 0xb;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar15 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar12 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          FUN_00436bd0(local_15b0 - iVar12,local_15b4 - iVar15,*(undefined4 *)(iVar11 + 0x1e50));
          local_4 = CONCAT31(local_4._1_3_,10);
          if (local_ef4 != 0) {
            FUN_0040a240();
            FUN_0040b540(local_1580);
            iVar11 = local_159c;
          }
          local_4 = 0xffffffff;
          if (local_cd0 != 0) {
            FUN_0040a240();
            FUN_0040b540(local_1580);
            iVar11 = local_159c;
          }
        }
        cVar8 = FUN_004065a0();
        if (cVar8 != '\0') {
          FUN_00436ec0(local_15b0,local_15b4);
        }
        if (*(int *)(iVar11 + 0x3f9c) < (int)(uint)(byte)(&DAT_005f2f54)[DAT_005b3484]) {
          FUN_00436fd0(local_15b0,local_15b4,param_2,local_1588,local_1584);
        }
        iVar12 = local_15b0;
        iVar15 = DAT_005b3484;
        *(int *)(iVar11 + 0x3f9c) = (*(int *)(iVar11 + 0x3f9c) + 1) % 6;
        if ((((-1 < local_15b0) && (local_15b0 < *(int *)(&DAT_006a7720 + iVar15))) &&
            (-1 < local_15b4)) &&
           ((local_15b4 < *(int *)(&DAT_006a7724 + iVar15) &&
            (*(char *)(*(int *)(&DAT_006a7720 + iVar15) * local_15b4 +
                       *(int *)(&DAT_006a773c + iVar15) + local_15b0) != '\0')))) {
          FUN_00458920(&local_15bc,&local_15b4,local_1588,local_1598,local_1590,local_158c,
                       local_1594,1,0);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15bc << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b4 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15bc);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b4);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar15 = _rand();
          *(char *)(iVar11 + 0xf45) = (char)iVar15;
          local_15a8[0] = _rand();
          local_15a8[0] = local_15a8[0] & 0x800000ff;
          if ((int)local_15a8[0] < 0) {
            local_15a8[0] = (local_15a8[0] - 1 | 0xffffff00) + 1;
          }
          *(byte *)(iVar11 + 0xf46) = (byte)local_15a8[0];
          bVar13 = '\x01' << (*(byte *)(iVar11 + 0xf45) & 7);
          bVar13 = ~bVar13 & (byte)local_15a8[0] | bVar13;
          *(byte *)(iVar11 + 0xf46) = bVar13;
          *(byte *)(iVar11 + 0xf47) = *(byte *)(iVar11 + 0xf45) + bVar13 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (DAT_0079352a != '\0') {
            uVar10 = 0xf002;
LAB_00471165:
            Replay_AppendEvent(uVar10);
            (&g_replayEventBuffer)[g_replayEventCursor] = *(undefined1 *)(iVar11 + 8);
LAB_0047117e:
            piVar1 = (int *)(&DAT_00e9aacd + g_replayEventCursor);
            g_replayEventCursor = g_replayEventCursor + 1;
            *piVar1 = local_15bc;
            piVar1 = (int *)(&DAT_00e9aad0 + g_replayEventCursor);
            g_replayEventCursor = g_replayEventCursor + 4;
            *piVar1 = local_15b4;
LAB_004711aa:
            g_replayEventCursor = g_replayEventCursor + 4;
            Replay_FlushEvent();
          }
          break;
        }
        cVar8 = FUN_00450e10(local_15b4);
        if (cVar8 != '\0') {
          FUN_00458920(&local_15bc,&local_15b4,local_1588,local_1598,local_1590,local_158c,
                       local_1594,0,1);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar11 = local_159c;
          EncodeOutgoingPacketField(local_15bc << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b4 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15bc);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b4);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar15 = _rand();
          *(char *)(iVar11 + 0xf45) = (char)iVar15;
          iVar15 = _rand();
          *(byte *)(iVar11 + 0xf46) = (byte)iVar15;
          bVar13 = '\x01' << (*(byte *)(iVar11 + 0xf45) & 7);
          bVar13 = ~bVar13 & (byte)iVar15 | bVar13;
          *(byte *)(iVar11 + 0xf46) = bVar13;
          *(byte *)(iVar11 + 0xf47) = bVar13 + *(char *)(iVar11 + 0xf45) + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (DAT_0079352a != '\0') {
            Replay_AppendEvent(0xf003);
            (&g_replayEventBuffer)[g_replayEventCursor] = *(undefined1 *)(iVar11 + 8);
            goto LAB_0047117e;
          }
          break;
        }
        local_1598 = local_1598 + param_2;
        local_15b0 = iVar12 + local_1578;
      } while (local_1598 < (int)local_15a8[0]);
    }
  }
  else {
    local_158c = ((local_1590 - local_1588) * 0x10000) / iVar16;
    local_1594 = local_1588 << 0x10;
    iVar15 = iVar15 + param_2;
    local_1590 = (uint)(iVar11 <= local_15a0) * 2 + -1;
    if (0 < iVar15) {
      local_15b8 = local_158c * param_2;
      local_15a0 = local_159c + 0x15c0;
      local_1578 = local_1590 * param_2;
      local_15b0 = iVar11;
      do {
        local_1594 = local_1594 + local_15b8;
        local_15b4 = local_15b0;
        local_15bc = local_1594 >> 0x10;
        if ((local_15a9 == '\0') &&
           (iVar12 = FUN_004510f0(local_15bc), iVar11 = local_15a0, iVar12 != 0)) {
          local_15a8[0] = FUN_0040a5f0(local_15a0,local_1350,param_2);
          local_4 = 0xc;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15a8[0] = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if ((int)local_15a8[0] < 0x14) {
LAB_0047090c:
            local_15a8[0] = FUN_0040a5f0(iVar11,local_f08,param_2);
            local_4 = 0xe;
            bVar6 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_15a8[0] = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if ((int)local_15a8[0] < 0x14) {
              uVar10 = 0x14;
            }
            else {
              FUN_0040a5f0(iVar11,local_ce4,param_2);
              local_4 = 0xf;
              bVar6 = true;
              bVar5 = true;
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              uVar10 = PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            }
          }
          else {
            local_15a8[0] = FUN_0040a5f0(iVar11,local_112c,param_2);
            local_4 = CONCAT31(local_4._1_3_,0xd);
            bVar7 = true;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_15a8[0] = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if ((int)local_15a8[0] < 0x65) goto LAB_0047090c;
            uVar10 = 100;
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(uVar10);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar14 = local_cd0;
          local_4 = 0xe;
          if ((bVar5) && (bVar5 = false, local_cd0 != 0)) {
            FUN_0040a240();
            local_15a8[0] = uVar14;
            FUN_0040b540(local_1580);
          }
          uVar14 = local_ef4;
          local_4 = 0xd;
          if ((bVar6) && (bVar6 = false, local_ef4 != 0)) {
            FUN_0040a240();
            local_15a8[0] = uVar14;
            FUN_0040b540(local_1580);
          }
          uVar14 = local_1118;
          local_4 = 0xc;
          if ((bVar7) && (bVar7 = false, local_1118 != 0)) {
            FUN_0040a240();
            local_15a8[0] = uVar14;
            FUN_0040b540(local_1580);
          }
          uVar14 = local_133c;
          local_4 = 0xffffffff;
          if (local_133c != 0) {
            FUN_0040a240();
            local_15a8[0] = uVar14;
            FUN_0040b540(local_1580);
          }
          local_15a9 = '\x01';
        }
        iVar11 = local_159c;
        pbVar17 = (byte *)(local_159c + 0xf4c);
        cVar8 = FUN_00406860();
        if (cVar8 != '\0') {
          iVar12 = FUN_00451030(local_15bc);
          *(int *)(iVar11 + 0xf48) = iVar12;
          if (iVar12 != 0) {
            *(undefined4 *)(iVar11 + 0xf50) = 0;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar12 = _rand();
            *pbVar17 = (byte)iVar12;
            iVar12 = _rand();
            bVar13 = *pbVar17;
            *(byte *)(iVar11 + 0xf4d) = (byte)iVar12;
            bVar9 = '\x01' << (bVar13 & 7);
            bVar13 = *pbVar17;
            bVar9 = ~bVar9 & (byte)iVar12 | bVar9;
            *(byte *)(iVar11 + 0xf4d) = bVar9;
            *(byte *)(iVar11 + 0xf4e) = bVar9 + bVar13 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar12 = DAT_005b3484;
            pbVar17 = (byte *)(DAT_005b3484 + 0x62140);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar16 = _rand();
            *pbVar17 = (byte)iVar16;
            iVar16 = _rand();
            bVar13 = *pbVar17;
            *(byte *)(iVar12 + 0x62141) = (byte)iVar16;
            bVar9 = '\x01' << (bVar13 & 7);
            bVar13 = *pbVar17;
            bVar9 = ~bVar9 & (byte)iVar16 | bVar9;
            *(byte *)(iVar12 + 0x62141) = bVar9;
            *(byte *)(iVar12 + 0x62142) = bVar9 + bVar13 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
        }
        pbVar17 = (byte *)(iVar11 + 0x3918);
        cVar8 = FUN_004065a0();
        if ((cVar8 == '\0') && (iVar12 = FUN_004511b0(local_15bc), iVar12 != 0)) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar12 = _rand();
          *pbVar17 = (byte)iVar12;
          iVar12 = _rand();
          *(byte *)(iVar11 + 0x3919) = (byte)iVar12;
          bVar13 = '\x01' << (*pbVar17 & 7);
          bVar13 = ~bVar13 & (byte)iVar12 | bVar13;
          *(byte *)(iVar11 + 0x3919) = bVar13;
          *(byte *)(iVar11 + 0x391a) = bVar13 + *pbVar17 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar10 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        FUN_00436dc0(local_15bc,local_15b0,uVar10);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar12 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar12 == 0) {
          FUN_0040b180(iVar11 + 0x6ac,local_230,8);
          local_4 = 0x10;
          local_15a8[0] = FUN_0040b180(iVar11 + 0x488,local_678,8);
          local_4._0_1_ = 0x11;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar12 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15a8[0] = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          FUN_00436bd0(local_15bc - local_15a8[0],local_15b0 - iVar12,
                       *(undefined4 *)(iVar11 + 0x1e50));
          uVar14 = local_664;
          local_4 = CONCAT31(local_4._1_3_,0x10);
          if (local_664 != 0) {
            FUN_0040a240();
            local_15a8[0] = uVar14;
            FUN_0040b540(local_1580);
            iVar11 = local_159c;
          }
          uVar14 = local_21c;
          local_4 = 0xffffffff;
          if (local_21c != 0) {
            FUN_0040a240();
            local_15a8[0] = uVar14;
            FUN_0040b540(local_1580);
            iVar11 = local_159c;
          }
        }
        cVar8 = FUN_004065a0();
        if (cVar8 != '\0') {
          FUN_00436ec0(local_15bc,local_15b0);
        }
        if (*(int *)(iVar11 + 0x3f9c) < (int)(uint)(byte)(&DAT_005f2f54)[DAT_005b3484]) {
          FUN_00436fd0(local_15bc,local_15b0,param_2,local_1588,local_1584);
        }
        iVar16 = local_15b0;
        iVar12 = DAT_005b3484;
        *(int *)(iVar11 + 0x3f9c) = (*(int *)(iVar11 + 0x3f9c) + 1) % 6;
        if ((((-1 < local_15bc) && (local_15bc < *(int *)(&DAT_006a7720 + iVar12))) &&
            (-1 < local_15b0)) &&
           ((local_15b0 < *(int *)(&DAT_006a7724 + iVar12) &&
            (*(char *)(local_15b0 * *(int *)(&DAT_006a7720 + iVar12) +
                       *(int *)(&DAT_006a773c + iVar12) + local_15bc) != '\0')))) {
          FUN_00458a00(&local_15bc,&local_15b4,local_1584,local_1598,local_1590,local_158c,
                       local_1594,1,0);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15bc << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b4 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15bc);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b4);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar15 = _rand();
          *(char *)(iVar11 + 0xf45) = (char)iVar15;
          iVar15 = _rand();
          *(byte *)(iVar11 + 0xf46) = (byte)iVar15;
          bVar13 = '\x01' << (*(byte *)(iVar11 + 0xf45) & 7);
          bVar13 = ~bVar13 & (byte)iVar15 | bVar13;
          *(byte *)(iVar11 + 0xf46) = bVar13;
          *(byte *)(iVar11 + 0xf47) = bVar13 + *(char *)(iVar11 + 0xf45) + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (DAT_0079352a != '\0') {
            Replay_AppendEvent(0xf002);
            (&g_replayEventBuffer)[g_replayEventCursor] = *(undefined1 *)(iVar11 + 8);
            piVar1 = (int *)(&DAT_00e9aacd + g_replayEventCursor);
            g_replayEventCursor = g_replayEventCursor + 1;
            *piVar1 = local_15bc;
            piVar1 = (int *)(&DAT_00e9aad0 + g_replayEventCursor);
            g_replayEventCursor = g_replayEventCursor + 4;
            *piVar1 = local_15b4;
            goto LAB_004711aa;
          }
          break;
        }
        cVar8 = FUN_00450e10(local_15b0);
        if (cVar8 != '\0') {
          FUN_00458a00(&local_15bc,&local_15b4,local_1584,local_1598,local_1590,local_158c,
                       local_1594,0,1);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar11 = local_159c;
          EncodeOutgoingPacketField(local_15bc << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b4 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15bc);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15b4);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar15 = _rand();
          *(char *)(iVar11 + 0xf45) = (char)iVar15;
          iVar15 = _rand();
          *(byte *)(iVar11 + 0xf46) = (byte)iVar15;
          bVar13 = '\x01' << (*(byte *)(iVar11 + 0xf45) & 7);
          bVar13 = ~bVar13 & (byte)iVar15 | bVar13;
          *(byte *)(iVar11 + 0xf46) = bVar13;
          *(byte *)(iVar11 + 0xf47) = bVar13 + *(char *)(iVar11 + 0xf45) + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (DAT_0079352a != '\0') {
            uVar10 = 0xf003;
            goto LAB_00471165;
          }
          break;
        }
        local_1598 = local_1598 + param_2;
        local_15b0 = iVar16 + local_1578;
      } while (local_1598 < iVar15);
    }
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

