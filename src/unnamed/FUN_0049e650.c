/* FUN_0049e650 - 0x0049e650 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void __thiscall FUN_0049e650(int param_1,int param_2)

{
  int *piVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  byte bVar6;
  byte bVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  byte *pbVar11;
  undefined4 *unaff_FS_OFFSET;
  bool bVar12;
  int local_15c4;
  int local_15c0;
  uint local_15bc;
  int local_15b8;
  int local_15b4;
  char local_15ad;
  int local_15ac;
  int local_15a8 [2];
  char local_159d;
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
  puStack_8 = &LAB_0053ee50;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uStack_10 = 0x49e66f;
  local_1584 = param_1 + 0x40;
  local_15bc = 0;
  local_15ad = '\0';
  local_159c = param_1;
  FUN_0040b180(local_1584,local_1574,8);
  local_4 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_1598 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  local_15b4 = local_1560;
  if (local_1560 != 0) {
    FUN_0040a240();
    FUN_0040b540(local_15a8);
  }
  local_1594 = param_1 + 0x264;
  FUN_0040b180(local_1594,local_1574,8);
  local_4 = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_158c = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  local_15b4 = local_1560;
  if (local_1560 != 0) {
    FUN_0040a240();
    FUN_0040b540(local_15a8);
  }
  uVar3 = FUN_0040aca0(local_1584,local_ac0,param_1 + 0x488);
  local_4 = 2;
  FUN_0040b180(uVar3,local_1574,8);
  local_4 = 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_1590 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = local_1560;
  local_4 = 2;
  if (local_1560 != 0) {
    FUN_0040a240();
    local_15b4 = iVar4;
    FUN_0040b540(local_15a8);
  }
  iVar4 = local_aac;
  local_4 = 0xffffffff;
  if (local_aac != 0) {
    FUN_0040a240();
    local_15b4 = iVar4;
    FUN_0040b540(local_15a8);
  }
  uVar3 = FUN_0040aca0(local_1594,local_1574,local_159c + 0x6ac);
  local_4 = 4;
  FUN_0040b180(uVar3,local_ac0,8);
  local_4 = 5;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 4;
  local_15b4 = local_aac;
  if (local_aac != 0) {
    FUN_0040a240();
    FUN_0040b540(local_15a8);
  }
  local_4 = 0xffffffff;
  local_15b4 = local_1560;
  if (local_1560 != 0) {
    FUN_0040a240();
    FUN_0040b540(local_15a8);
  }
  uVar8 = local_1590 - local_1598 >> 0x1f;
  iVar5 = (local_1590 - local_1598 ^ uVar8) - uVar8;
  uVar8 = iVar4 - local_158c >> 0x1f;
  iVar9 = (iVar4 - local_158c ^ uVar8) - uVar8;
  local_1584 = iVar5 + 1;
  iVar10 = iVar9 + 1;
  if (iVar10 < local_1584) {
    local_1584 = ((local_158c - iVar4) * 0x10000) / local_1584;
    local_1588 = iVar4 << 0x10;
    if (local_1598 < local_1590) {
      local_15ac = local_1590 + -1;
      local_1590 = -1;
    }
    else {
      local_15ac = local_1590 + 1;
      local_1590 = 1;
    }
    local_15a8[0] = iVar5 + param_2;
    local_1594 = 0;
    if (0 < local_15a8[0]) {
      local_15b4 = local_1584 * param_2;
      local_158c = local_159c + 0x15c0;
      local_1578 = local_1590 * param_2;
      local_1598 = local_15ac;
      do {
        local_1588 = local_1588 + local_15b4;
        local_15c0 = local_1588 >> 0x10;
        local_15c4 = local_15ac;
        if ((local_15ad == '\0') &&
           (iVar5 = FUN_004510f0(local_15ac), iVar4 = local_158c, iVar5 != 0)) {
          local_15b8 = FUN_0040a5f0(local_158c,local_112c,param_2);
          local_4 = 6;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15b8 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (local_15b8 < 0x14) {
LAB_0049ea8b:
            local_15b8 = FUN_0040a5f0(iVar4,local_89c,param_2);
            local_4 = 8;
            local_15bc = local_15bc | 2;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_15b8 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (local_15b8 < 0x14) {
              uVar3 = 0x14;
            }
            else {
              FUN_0040a5f0(iVar4,local_454,param_2);
              local_4 = 9;
              local_15bc = local_15bc | 4;
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              uVar3 = PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            }
          }
          else {
            local_15b8 = FUN_0040a5f0(iVar4,local_1350,param_2);
            local_4 = 7;
            local_15bc = local_15bc | 1;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_15b8 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (local_15b8 < 0x65) goto LAB_0049ea8b;
            uVar3 = 100;
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(uVar3);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar4 = local_440;
          local_4 = 8;
          if (((local_15bc & 4) != 0) && (local_15bc = local_15bc & 0xfffffffb, local_440 != 0)) {
            FUN_0040a240();
            local_15b8 = iVar4;
            FUN_0040b540(local_1580);
          }
          iVar4 = local_888;
          local_4 = 7;
          if (((local_15bc & 2) != 0) && (local_15bc = local_15bc & 0xfffffffd, local_888 != 0)) {
            FUN_0040a240();
            local_15b8 = iVar4;
            FUN_0040b540(local_1580);
          }
          iVar4 = local_133c;
          local_4 = 6;
          if (((local_15bc & 1) != 0) && (local_15bc = local_15bc & 0xfffffffe, local_133c != 0)) {
            FUN_0040a240();
            local_15b8 = iVar4;
            FUN_0040b540(local_1580);
          }
          iVar4 = local_1118;
          local_4 = 0xffffffff;
          if (local_1118 != 0) {
            FUN_0040a240();
            local_15b8 = iVar4;
            FUN_0040b540(local_1580);
          }
          local_15ad = '\x01';
        }
        iVar4 = local_159c;
        pbVar11 = (byte *)(local_159c + 0xf4c);
        cVar2 = FUN_00406860();
        if (cVar2 != '\0') {
          iVar5 = FUN_00451030(local_15ac);
          *(int *)(iVar4 + 0xf48) = iVar5;
          if (iVar5 != 0) {
            *(undefined4 *)(iVar4 + 0xf50) = 0;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = _rand();
            *pbVar11 = (byte)iVar5;
            iVar5 = _rand();
            bVar7 = *pbVar11;
            *(byte *)(iVar4 + 0xf4d) = (byte)iVar5;
            bVar6 = '\x01' << (bVar7 & 7);
            bVar7 = *pbVar11;
            bVar6 = ~bVar6 & (byte)iVar5 | bVar6;
            *(byte *)(iVar4 + 0xf4d) = bVar6;
            *(byte *)(iVar4 + 0xf4e) = bVar6 + bVar7 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = g_clientContext;
            pbVar11 = (byte *)(g_clientContext + 0x62140);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar9 = _rand();
            *pbVar11 = (byte)iVar9;
            iVar9 = _rand();
            bVar7 = *pbVar11;
            *(byte *)(iVar5 + 0x62141) = (byte)iVar9;
            bVar6 = '\x01' << (bVar7 & 7);
            bVar7 = *pbVar11;
            bVar6 = ~bVar6 & (byte)iVar9 | bVar6;
            *(byte *)(iVar5 + 0x62141) = bVar6;
            *(byte *)(iVar5 + 0x62142) = bVar6 + bVar7 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
        }
        pbVar11 = (byte *)(iVar4 + 0x3918);
        cVar2 = PeekPacketChecksumBool();
        if ((cVar2 == '\0') && (iVar5 = FUN_004511b0(local_15ac), iVar5 != 0)) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = _rand();
          *pbVar11 = (byte)iVar5;
          iVar5 = _rand();
          *(byte *)(iVar4 + 0x3919) = (byte)iVar5;
          bVar7 = '\x01' << (*pbVar11 & 7);
          bVar7 = ~bVar7 & (byte)iVar5 | bVar7;
          *(byte *)(iVar4 + 0x3919) = bVar7;
          *(byte *)(iVar4 + 0x391a) = bVar7 + *pbVar11 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar3 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        FUN_00436dc0(local_15ac,local_15c0,uVar3);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar5 = PeekPacketChecksumState();
        local_159d = iVar5 == 0;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (local_159d != '\0') {
          FUN_0040b180(iVar4 + 0x6ac,local_ce4,8);
          local_4 = 10;
          local_15b8 = FUN_0040b180(iVar4 + 0x488,local_f08,8);
          local_4 = 0xb;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15b8 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          FUN_00436bd0(local_15ac - local_15b8,local_15c0 - iVar5,*(undefined4 *)(iVar4 + 0x1e50));
          iVar5 = local_ef4;
          local_4 = 10;
          if (local_ef4 != 0) {
            FUN_0040a240();
            local_15b8 = iVar5;
            FUN_0040b540(local_1580);
            iVar4 = local_159c;
          }
          iVar5 = local_cd0;
          local_4 = 0xffffffff;
          if (local_cd0 != 0) {
            FUN_0040a240();
            local_15b8 = iVar5;
            FUN_0040b540(local_1580);
            iVar4 = local_159c;
          }
        }
        iVar5 = local_15ac;
        cVar2 = PeekPacketChecksumBool();
        if (cVar2 != '\0') {
          FUN_00436ec0(iVar5,local_15c0);
        }
        iVar9 = local_15ac;
        iVar10 = local_15c0;
        if ((((-1 < iVar5) && (iVar5 < *(int *)(&DAT_006a7720 + g_clientContext))) && (-1 < local_15c0)
            ) && ((local_15c0 < *(int *)(&DAT_006a7724 + g_clientContext) &&
                  (*(char *)(*(int *)(&DAT_006a7720 + g_clientContext) * local_15c0 +
                             *(int *)(&DAT_006a773c + g_clientContext) + iVar5) != '\0')))) {
          FUN_00458920(&local_15c4,&local_15c0,local_1598,local_1594,local_1590,local_1584,
                       local_1588,1,0);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15c4 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15c0 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15c4);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15c0);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = _rand();
          *(char *)(iVar4 + 0xf45) = (char)iVar5;
          iVar5 = _rand();
          *(byte *)(iVar4 + 0xf46) = (byte)iVar5;
          bVar7 = '\x01' << (*(byte *)(iVar4 + 0xf45) & 7);
          bVar7 = ~bVar7 & (byte)iVar5 | bVar7;
          *(byte *)(iVar4 + 0xf46) = bVar7;
          *(byte *)(iVar4 + 0xf47) = bVar7 + *(char *)(iVar4 + 0xf45) + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (DAT_0079352a != '\0') {
            uVar3 = 0xf002;
            goto LAB_0049fcc1;
          }
          break;
        }
        cVar2 = FUN_00450e10(local_15c0);
        if (cVar2 != '\0') {
          FUN_00458920(&local_15c4,&local_15c0,local_1598,local_1594,local_1590,local_1584,
                       local_1588,0,1);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar4 = local_159c;
          EncodeOutgoingPacketField(local_15c4 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15c0 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15c4);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15c0);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          bVar12 = DAT_0079352a != '\0';
          *(undefined1 *)(iVar4 + 0x3fa0) = 1;
          if (bVar12) {
            Replay_AppendEvent(0xf003);
            (&g_replayEventBuffer)[g_replayEventCursor] = *(undefined1 *)(iVar4 + 8);
            goto LAB_0049fcda;
          }
          break;
        }
        if (((iVar9 < 0) || (*(int *)(&DAT_006a7720 + g_clientContext) + -1 < iVar9)) ||
           ((iVar10 < -0x113 || (*(int *)(&DAT_006a7724 + g_clientContext) + -1 < iVar10))))
        goto LAB_0049fb78;
        local_1594 = local_1594 + param_2;
        local_15ac = iVar9 + local_1578;
      } while (local_1594 < local_15a8[0]);
    }
  }
  else {
    local_1584 = ((local_1598 - local_1590) * 0x10000) / iVar10;
    local_1588 = local_1590 << 0x10;
    if (local_158c < iVar4) {
      local_15ac = iVar4 + -1;
      local_1590 = -1;
    }
    else {
      local_15ac = iVar4 + 1;
      local_1590 = 1;
    }
    local_15b8 = iVar9 + param_2;
    local_1594 = 0;
    if (0 < local_15b8) {
      local_15b4 = local_1584 * param_2;
      local_158c = local_159c + 0x15c0;
      local_1578 = local_1590 * param_2;
      local_1598 = local_15ac;
      do {
        local_1588 = local_1588 + local_15b4;
        local_15c0 = local_15ac;
        local_15c4 = local_1588 >> 0x10;
        if ((local_15ad == '\0') &&
           (iVar5 = FUN_004510f0(local_15c4), iVar4 = local_158c, iVar5 != 0)) {
          local_15a8[0] = FUN_0040a5f0(local_158c,local_1350,param_2);
          local_4 = 0xc;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15a8[0] = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (local_15a8[0] < 0x14) {
LAB_0049f398:
            local_15a8[0] = FUN_0040a5f0(iVar4,local_f08,param_2);
            local_4 = 0xe;
            local_15bc = local_15bc | 0x10;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_15a8[0] = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (local_15a8[0] < 0x14) {
              uVar3 = 0x14;
            }
            else {
              FUN_0040a5f0(iVar4,local_ce4,param_2);
              local_4 = 0xf;
              local_15bc = local_15bc | 0x20;
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              uVar3 = PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            }
          }
          else {
            local_15a8[0] = FUN_0040a5f0(iVar4,local_112c,param_2);
            local_4 = 0xd;
            local_15bc = local_15bc | 8;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_15a8[0] = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (local_15a8[0] < 0x65) goto LAB_0049f398;
            uVar3 = 100;
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(uVar3);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar4 = local_cd0;
          local_4 = 0xe;
          if (((local_15bc & 0x20) != 0) && (local_15bc = local_15bc & 0xffffffdf, local_cd0 != 0))
          {
            FUN_0040a240();
            local_15a8[0] = iVar4;
            FUN_0040b540(local_1580);
          }
          iVar4 = local_ef4;
          local_4 = 0xd;
          if (((local_15bc & 0x10) != 0) && (local_15bc = local_15bc & 0xffffffef, local_ef4 != 0))
          {
            FUN_0040a240();
            local_15a8[0] = iVar4;
            FUN_0040b540(local_1580);
          }
          iVar4 = local_1118;
          local_4 = 0xc;
          if (((local_15bc & 8) != 0) && (local_15bc = local_15bc & 0xfffffff7, local_1118 != 0)) {
            FUN_0040a240();
            local_15a8[0] = iVar4;
            FUN_0040b540(local_1580);
          }
          iVar4 = local_133c;
          local_4 = 0xffffffff;
          if (local_133c != 0) {
            FUN_0040a240();
            local_15a8[0] = iVar4;
            FUN_0040b540(local_1580);
          }
          local_15ad = '\x01';
        }
        iVar4 = local_159c;
        pbVar11 = (byte *)(local_159c + 0xf4c);
        cVar2 = FUN_00406860();
        if (cVar2 != '\0') {
          iVar5 = FUN_00451030(local_15c4);
          *(int *)(iVar4 + 0xf48) = iVar5;
          if (iVar5 != 0) {
            *(undefined4 *)(iVar4 + 0xf50) = 0;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = _rand();
            *pbVar11 = (byte)iVar5;
            iVar5 = _rand();
            bVar7 = *pbVar11;
            *(byte *)(iVar4 + 0xf4d) = (byte)iVar5;
            bVar6 = '\x01' << (bVar7 & 7);
            bVar7 = *pbVar11;
            bVar6 = ~bVar6 & (byte)iVar5 | bVar6;
            *(byte *)(iVar4 + 0xf4d) = bVar6;
            *(byte *)(iVar4 + 0xf4e) = bVar6 + bVar7 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = g_clientContext;
            pbVar11 = (byte *)(g_clientContext + 0x62140);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar9 = _rand();
            *pbVar11 = (byte)iVar9;
            iVar9 = _rand();
            bVar7 = *pbVar11;
            *(byte *)(iVar5 + 0x62141) = (byte)iVar9;
            bVar6 = '\x01' << (bVar7 & 7);
            bVar7 = *pbVar11;
            bVar6 = ~bVar6 & (byte)iVar9 | bVar6;
            *(byte *)(iVar5 + 0x62141) = bVar6;
            *(byte *)(iVar5 + 0x62142) = bVar6 + bVar7 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
        }
        pbVar11 = (byte *)(iVar4 + 0x3918);
        cVar2 = PeekPacketChecksumBool();
        if ((cVar2 == '\0') && (iVar5 = FUN_004511b0(local_15c4), iVar5 != 0)) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = _rand();
          *pbVar11 = (byte)iVar5;
          iVar5 = _rand();
          *(byte *)(iVar4 + 0x3919) = (byte)iVar5;
          bVar7 = '\x01' << (*pbVar11 & 7);
          bVar7 = ~bVar7 & (byte)iVar5 | bVar7;
          *(byte *)(iVar4 + 0x3919) = bVar7;
          *(byte *)(iVar4 + 0x391a) = bVar7 + *pbVar11 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar3 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        FUN_00436dc0(local_15c4,local_15ac,uVar3);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar5 = PeekPacketChecksumState();
        local_159d = iVar5 == 0;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (local_159d != '\0') {
          FUN_0040b180(iVar4 + 0x6ac,local_230,8);
          local_4 = 0x10;
          local_15a8[0] = FUN_0040b180(iVar4 + 0x488,local_678,8);
          local_4 = 0x11;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15a8[0] = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          FUN_00436bd0(local_15c4 - local_15a8[0],local_15ac - iVar5,*(undefined4 *)(iVar4 + 0x1e50)
                      );
          iVar5 = local_664;
          local_4 = 0x10;
          if (local_664 != 0) {
            FUN_0040a240();
            local_15a8[0] = iVar5;
            FUN_0040b540(local_1580);
            iVar4 = local_159c;
          }
          iVar5 = local_21c;
          local_4 = 0xffffffff;
          if (local_21c != 0) {
            FUN_0040a240();
            local_15a8[0] = iVar5;
            FUN_0040b540(local_1580);
            iVar4 = local_159c;
          }
        }
        iVar5 = local_15c4;
        cVar2 = PeekPacketChecksumBool();
        if (cVar2 != '\0') {
          FUN_00436ec0(iVar5,local_15ac);
        }
        iVar10 = local_15ac;
        iVar9 = local_15c4;
        if ((((-1 < iVar5) && (iVar5 < *(int *)(&DAT_006a7720 + g_clientContext))) && (-1 < local_15ac)
            ) && ((local_15ac < *(int *)(&DAT_006a7724 + g_clientContext) &&
                  (*(char *)(local_15ac * *(int *)(&DAT_006a7720 + g_clientContext) +
                             *(int *)(&DAT_006a773c + g_clientContext) + iVar5) != '\0')))) {
          FUN_00458a00(&local_15c4,&local_15c0,local_1598,local_1594,local_1590,local_1584,
                       local_1588,1,0);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15c4 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15c0 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15c4);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15c0);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = _rand();
          *(char *)(iVar4 + 0xf45) = (char)iVar5;
          iVar5 = _rand();
          *(byte *)(iVar4 + 0xf46) = (byte)iVar5;
          bVar7 = '\x01' << (*(byte *)(iVar4 + 0xf45) & 7);
          bVar7 = ~bVar7 & (byte)iVar5 | bVar7;
          *(byte *)(iVar4 + 0xf46) = bVar7;
          *(byte *)(iVar4 + 0xf47) = bVar7 + *(char *)(iVar4 + 0xf45) + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (DAT_0079352a != '\0') {
            Replay_AppendEvent(0xf002);
            (&g_replayEventBuffer)[g_replayEventCursor] = *(undefined1 *)(iVar4 + 8);
            piVar1 = (int *)(&DAT_00e9aacd + g_replayEventCursor);
            g_replayEventCursor = g_replayEventCursor + 1;
            *piVar1 = local_15c4;
            piVar1 = (int *)(&DAT_00e9aad0 + g_replayEventCursor);
            g_replayEventCursor = g_replayEventCursor + 4;
            *piVar1 = local_15c0;
            goto LAB_0049fd06;
          }
          break;
        }
        cVar2 = FUN_00450e10(local_15ac);
        if (cVar2 != '\0') {
          FUN_00458a00(&local_15c4,&local_15c0,local_1598,local_1594,local_1590,local_1584,
                       local_1588,0,1);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar4 = local_159c;
          EncodeOutgoingPacketField(local_15c4 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15c0 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15c4);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15c0);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          bVar12 = DAT_0079352a != '\0';
          *(undefined1 *)(iVar4 + 0x3fa0) = 1;
          if (bVar12) {
            uVar3 = 0xf003;
            goto LAB_0049fcc1;
          }
          break;
        }
        if (((iVar9 < 0) || (*(int *)(&DAT_006a7720 + g_clientContext) + -1 < iVar9)) ||
           ((iVar10 < -0x113 || (*(int *)(&DAT_006a7724 + g_clientContext) + -1 < iVar10))))
        goto LAB_0049fb78;
        local_1594 = local_1594 + param_2;
        local_15ac = iVar10 + local_1578;
      } while (local_1594 < local_15b8);
    }
  }
LAB_0049fd17:
  *unaff_FS_OFFSET = local_c;
  return;
LAB_0049fb78:
  iVar5 = *(int *)(&DAT_006a7720 + g_clientContext) + -1;
  iVar4 = iVar5;
  if (iVar9 <= iVar5) {
    iVar4 = iVar9;
  }
  if (iVar4 < 0) {
    local_15c4 = 0;
  }
  else if (iVar5 < iVar9) {
    local_15c4 = iVar5;
  }
  iVar5 = *(int *)(&DAT_006a7724 + g_clientContext) + -1;
  iVar4 = iVar5;
  if (iVar10 <= iVar5) {
    iVar4 = iVar10;
  }
  if (iVar4 < -0x113) {
    local_15c0 = -0x113;
  }
  else if (iVar5 < iVar10) {
    local_15c0 = iVar5;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = local_159c;
  EncodeOutgoingPacketField(local_15c4 << 8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(local_15c0 << 8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(local_15c4);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(local_15c0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = _rand();
  *(char *)(iVar4 + 0xf45) = (char)iVar5;
  iVar5 = _rand();
  *(byte *)(iVar4 + 0xf46) = (byte)iVar5;
  bVar7 = '\x01' << (*(byte *)(iVar4 + 0xf45) & 7);
  bVar7 = ~bVar7 & (byte)iVar5 | bVar7;
  *(byte *)(iVar4 + 0xf46) = bVar7;
  *(byte *)(iVar4 + 0xf47) = bVar7 + *(char *)(iVar4 + 0xf45) + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (DAT_0079352a != '\0') {
    uVar3 = 0xf004;
LAB_0049fcc1:
    Replay_AppendEvent(uVar3);
    (&g_replayEventBuffer)[g_replayEventCursor] = *(undefined1 *)(iVar4 + 8);
LAB_0049fcda:
    piVar1 = (int *)(&DAT_00e9aacd + g_replayEventCursor);
    g_replayEventCursor = g_replayEventCursor + 1;
    *piVar1 = local_15c4;
    piVar1 = (int *)(&DAT_00e9aad0 + g_replayEventCursor);
    g_replayEventCursor = g_replayEventCursor + 4;
    *piVar1 = local_15c0;
LAB_0049fd06:
    g_replayEventCursor = g_replayEventCursor + 4;
    Replay_FlushEvent();
  }
  goto LAB_0049fd17;
}

