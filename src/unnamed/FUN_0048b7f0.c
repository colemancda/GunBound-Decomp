/* FUN_0048b7f0 - 0x0048b7f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void __thiscall FUN_0048b7f0(int param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  byte bVar4;
  int iVar5;
  byte bVar6;
  byte bVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  byte *pbVar11;
  undefined4 *unaff_FS_OFFSET;
  int local_15c4;
  uint local_15c0;
  int local_15bc;
  int local_15b8;
  int local_15b4;
  char local_15ad;
  uint local_15ac;
  int local_15a8;
  int local_15a4;
  int local_15a0;
  int local_159c;
  uint local_1598 [2];
  int local_1590;
  int local_158c;
  int local_1588;
  int local_1584;
  int local_1580 [2];
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
  puStack_8 = &LAB_0053f194;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uStack_10 = 0x48b80f;
  local_1578 = param_1 + 0x40;
  local_15c0 = 0;
  local_15ad = '\0';
  local_15b4 = param_1;
  EncodeChecksumDeltaShr(local_1578,local_1574,8);
  local_4 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_159c = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if ((*(int *)(local_1574 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_1598);
  }
  local_1584 = param_1 + 0x264;
  EncodeChecksumDeltaShr(local_1584,local_1574,8);
  local_4 = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_15a4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if ((*(int *)(local_1574 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_1598);
  }
  uVar2 = EncodeChecksumPairDiff(local_1578,local_1350,param_1 + 0x488);
  local_4 = 2;
  EncodeChecksumDeltaShr(uVar2,local_1574,8);
  SUBFIELD(local_4,0,undefined1) = 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_1590 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),2);
  if ((*(int *)(local_1574 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_1598);
  }
  local_4 = 0xffffffff;
  if ((*(int *)(local_1350 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_1598);
  }
  uVar2 = EncodeChecksumPairDiff(local_1584,local_1574,local_15b4 + 0x6ac);
  local_4 = 4;
  EncodeChecksumDeltaShr(uVar2,local_1350,8);
  SUBFIELD(local_4,0,undefined1) = 5;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),4);
  if ((*(int *)(local_1350 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_1598);
  }
  local_4 = 0xffffffff;
  if ((*(int *)(local_1574 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_1598);
  }
  uVar8 = local_1590 - local_159c >> 0x1f;
  iVar5 = (local_1590 - local_159c ^ uVar8) - uVar8;
  uVar8 = iVar3 - local_15a4 >> 0x1f;
  iVar9 = (iVar3 - local_15a4 ^ uVar8) - uVar8;
  local_1578 = iVar5 + 1;
  iVar10 = iVar9 + 1;
  if (iVar10 < local_1578) {
    local_1578 = ((local_15a4 - iVar3) * 0x10000) / local_1578;
    local_1588 = iVar3 << 0x10;
    if (local_159c < local_1590) {
      local_15b8 = local_1590 + -1;
      local_1590 = -1;
    }
    else {
      local_15b8 = local_1590 + 1;
      local_1590 = 1;
    }
    local_15ac = iVar5 + param_2;
    local_15a4 = 0;
    if (0 < (int)local_15ac) {
      local_1584 = local_1578 * param_2;
      local_15a8 = local_15b4 + 0x15c0;
      local_1580[0] = local_1590 * param_2;
      local_159c = local_15b8;
      do {
        local_1588 = local_1588 + local_1584;
        local_15bc = local_1588 >> 0x10;
        local_15c4 = local_15b8;
        if ((local_15ad == '\0') &&
           (iVar5 = FUN_004510f0(local_15b8), iVar3 = local_15a8, iVar5 != 0)) {
          EncodeChecksumDeltaAdd(local_15a8,local_89c,param_2);
          local_4 = 6;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (iVar5 < 0x14) {
LAB_0048bc2e:
            EncodeChecksumDeltaAdd(iVar3,local_ce4,param_2);
            local_4 = 8;
            local_15c0 = local_15c0 | 2;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (iVar5 < 0x14) {
              uVar2 = 0x14;
            }
            else {
              EncodeChecksumDeltaAdd(iVar3,local_112c,param_2);
              local_4 = 9;
              local_15c0 = local_15c0 | 4;
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              uVar2 = PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            }
          }
          else {
            EncodeChecksumDeltaAdd(iVar3,local_454,param_2);
            local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),7);
            local_15c0 = local_15c0 | 1;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (iVar5 < 0x65) goto LAB_0048bc2e;
            uVar2 = 100;
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(uVar2);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_4 = 8;
          if (((local_15c0 & 4) != 0) && (local_15c0 = local_15c0 & 0xfffffffb, (*(int *)(local_112c + 0x14)) != 0)) {
            ScrambleChecksumGuardBytes();
            TreeLowerBound(local_1598);
          }
          local_4 = 7;
          if (((local_15c0 & 2) != 0) && (local_15c0 = local_15c0 & 0xfffffffd, (*(int *)(local_ce4 + 0x14)) != 0)) {
            ScrambleChecksumGuardBytes();
            TreeLowerBound(local_1598);
          }
          local_4 = 6;
          if (((local_15c0 & 1) != 0) && (local_15c0 = local_15c0 & 0xfffffffe, (*(int *)(local_454 + 0x14)) != 0)) {
            ScrambleChecksumGuardBytes();
            TreeLowerBound(local_1598);
          }
          local_4 = 0xffffffff;
          if ((*(int *)(local_89c + 0x14)) != 0) {
            ScrambleChecksumGuardBytes();
            TreeLowerBound(local_1598);
          }
          local_15ad = '\x01';
        }
        iVar3 = local_15b4;
        pbVar11 = (byte *)(local_15b4 + 0xf4c);
        cVar1 = DecodeGuardedBool();
        if ((cVar1 != '\0') && (*(char *)(iVar3 + 0x3f9c) == '\0')) {
          iVar5 = FUN_00451030(local_15b8);
          *(int *)(iVar3 + 0xf48) = iVar5;
          if (iVar5 != 0) {
            *(undefined4 *)(iVar3 + 0xf50) = 0;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = _rand();
            *pbVar11 = (byte)iVar5;
            iVar5 = _rand();
            bVar7 = *pbVar11;
            *(byte *)(iVar3 + 0xf4d) = (byte)iVar5;
            bVar6 = '\x01' << (bVar7 & 7);
            bVar6 = ~bVar6 & (byte)iVar5 | bVar6;
            *(byte *)(iVar3 + 0xf4d) = bVar6;
            *(byte *)(iVar3 + 0xf4e) = bVar6 + bVar7 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar3 = g_clientContext;
            pbVar11 = (byte *)(g_clientContext + 0x62140);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = _rand();
            *pbVar11 = (byte)iVar5;
            iVar5 = _rand();
            bVar7 = *pbVar11;
            *(byte *)(iVar3 + 0x62141) = (byte)iVar5;
            bVar6 = '\x01' << (bVar7 & 7);
            bVar7 = *pbVar11;
            bVar6 = ~bVar6 & (byte)iVar5 | bVar6;
            *(byte *)(iVar3 + 0x62141) = bVar6;
            *(byte *)(iVar3 + 0x62142) = bVar6 + bVar7 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar3 = local_15b4;
          }
        }
        cVar1 = PeekPacketChecksumBool();
        if ((cVar1 == '\0') && (iVar5 = FUN_004511b0(local_15b8), iVar5 != 0)) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = _rand();
          *(byte *)(iVar3 + 0x3918) = (byte)iVar5;
          iVar5 = _rand();
          bVar7 = *(byte *)(iVar3 + 0x3918);
          *(byte *)(iVar3 + 0x3919) = (byte)iVar5;
          bVar6 = '\x01' << (bVar7 & 7);
          bVar6 = ~bVar6 & (byte)iVar5 | bVar6;
          *(byte *)(iVar3 + 0x3919) = bVar6;
          *(byte *)(iVar3 + 0x391a) = bVar6 + bVar7 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar2 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        FUN_00436dc0(local_15b8,local_15bc,uVar2);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar3 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar3 == 0) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar3 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          FUN_00436bd0(local_15b8 - (iVar5 >> 8),local_15bc - (iVar3 >> 8),
                       *(undefined4 *)(local_15b4 + 0x1e50));
        }
        cVar1 = PeekPacketChecksumBool();
        if (cVar1 != '\0') {
          FUN_00436ec0(local_15b8,local_15bc);
        }
        cVar1 = FUN_00450e10(local_15bc);
        iVar3 = local_15b4;
        if (cVar1 != '\0') {
          FUN_00458920(&local_15c4,&local_15bc,local_159c,local_15a4,local_1590,local_1578,
                       local_1588,0,1);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar3 = local_15b4;
          EncodeOutgoingPacketField(local_15c4 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15bc << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = local_15c4;
LAB_0048c475:
          EncodeOutgoingPacketField(iVar5);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
LAB_0048c494:
          EncodeOutgoingPacketField(local_15bc);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = _rand();
          *(char *)(iVar3 + 0xf45) = (char)iVar5;
          iVar5 = _rand();
          *(byte *)(iVar3 + 0xf46) = (byte)iVar5;
          bVar7 = '\x01' << (*(byte *)(iVar3 + 0xf45) & 7);
          bVar7 = ~bVar7 & (byte)iVar5 | bVar7;
          *(byte *)(iVar3 + 0xf46) = bVar7;
          *(byte *)(iVar3 + 0xf47) = bVar7 + *(char *)(iVar3 + 0xf45) + -0x34;
LAB_0048d0e3:
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          break;
        }
        local_15c4 = 0;
        do {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_158c = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15a0 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = FUN_00425ac0(g_clientContext,local_15a0,local_158c,iVar5 / *(int *)(iVar3 + 0x3fa4));
          if (((iVar5 != 0) && (cVar1 = PeekPacketChecksumBool(), cVar1 != '\0')) &&
             (cVar1 = PeekPacketChecksumBool(), cVar1 != '\x01')) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar3 = local_15b4;
            EncodeOutgoingPacketField(local_15b8 << 8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField(local_15bc << 8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField(local_15b8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            goto LAB_0048c494;
          }
          local_15c4 = local_15c4 + 1;
        } while (local_15c4 < 8);
        local_15c4 = 0;
        do {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15a0 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_158c = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar2 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = FUN_00425c90(uVar2,local_158c,local_15a0 / *(int *)(iVar3 + 0x3fa4));
          if (iVar5 != 0) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar3 = local_15b4;
            EncodeOutgoingPacketField(local_15b8 << 8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField(local_15bc << 8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField(local_15b8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            goto LAB_0048c494;
          }
          local_15c4 = local_15c4 + 1;
        } while (local_15c4 < 8);
        local_15c4 = 0;
        do {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15a0 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_158c = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar2 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = FUN_00425e60(uVar2,local_158c,local_15a0 / *(int *)(iVar3 + 0x3fa4));
          if (iVar5 != 0) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar3 = local_15b4;
            EncodeOutgoingPacketField(local_15b8 << 8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField(local_15bc << 8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = local_15b8;
            goto LAB_0048c475;
          }
          local_15c4 = local_15c4 + 1;
        } while (local_15c4 < 0x40);
        local_15b8 = local_15b8 + local_1580[0];
        local_15a4 = local_15a4 + param_2;
      } while (local_15a4 < (int)local_15ac);
    }
  }
  else {
    local_1578 = ((local_159c - local_1590) * 0x10000) / iVar10;
    local_1588 = local_1590 << 0x10;
    if (local_15a4 < iVar3) {
      local_15b8 = iVar3 + -1;
      local_1590 = -1;
    }
    else {
      local_15b8 = iVar3 + 1;
      local_1590 = 1;
    }
    local_1598[0] = iVar9 + param_2;
    local_15a4 = 0;
    if (0 < (int)local_1598[0]) {
      local_1584 = local_1578 * param_2;
      local_15a8 = local_15b4 + 0x15c0;
      local_158c = local_1590 * param_2;
      local_159c = local_15b8;
      do {
        local_1588 = local_1588 + local_1584;
        iVar3 = local_1588 >> 0x10;
        local_15bc = local_15b8;
        local_15c4 = iVar3;
        if ((local_15ad == '\0') && (iVar5 = FUN_004510f0(iVar3), iVar5 != 0)) {
          EncodeChecksumDeltaAdd(local_15a8,local_230,param_2);
          local_4 = 10;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar3 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (iVar3 < 0x14) {
LAB_0048c664:
            EncodeChecksumDeltaAdd(local_15a8,local_ac0,param_2);
            local_4 = 0xc;
            local_15c0 = local_15c0 | 0x10;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar3 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (iVar3 < 0x14) {
              uVar2 = 0x14;
            }
            else {
              EncodeChecksumDeltaAdd(local_15a8,local_f08,param_2);
              local_4 = 0xd;
              local_15c0 = local_15c0 | 0x20;
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              uVar2 = PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            }
          }
          else {
            EncodeChecksumDeltaAdd(local_15a8,local_678,param_2);
            local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0xb);
            local_15c0 = local_15c0 | 8;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar3 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (iVar3 < 0x65) goto LAB_0048c664;
            uVar2 = 100;
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(uVar2);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar8 = (*(int *)(local_f08 + 0x14));
          local_4 = 0xc;
          if (((local_15c0 & 0x20) != 0) && (local_15c0 = local_15c0 & 0xffffffdf, (*(int *)(local_f08 + 0x14)) != 0))
          {
            ScrambleChecksumGuardBytes();
            local_15ac = uVar8;
            TreeLowerBound(local_1580);
          }
          uVar8 = (*(int *)(local_ac0 + 0x14));
          local_4 = 0xb;
          if (((local_15c0 & 0x10) != 0) && (local_15c0 = local_15c0 & 0xffffffef, (*(int *)(local_ac0 + 0x14)) != 0))
          {
            ScrambleChecksumGuardBytes();
            local_15ac = uVar8;
            TreeLowerBound(local_1580);
          }
          uVar8 = (*(int *)(local_678 + 0x14));
          local_4 = 10;
          if (((local_15c0 & 8) != 0) && (local_15c0 = local_15c0 & 0xfffffff7, (*(int *)(local_678 + 0x14)) != 0)) {
            ScrambleChecksumGuardBytes();
            local_15ac = uVar8;
            TreeLowerBound(local_1580);
          }
          uVar8 = (*(int *)(local_230 + 0x14));
          local_4 = 0xffffffff;
          if ((*(int *)(local_230 + 0x14)) != 0) {
            ScrambleChecksumGuardBytes();
            local_15ac = uVar8;
            TreeLowerBound(local_1580);
          }
          local_15ad = '\x01';
          iVar3 = local_15c4;
        }
        iVar5 = local_15b4;
        pbVar11 = (byte *)(local_15b4 + 0xf4c);
        cVar1 = DecodeGuardedBool();
        if ((cVar1 != '\0') && (*(char *)(local_15b4 + 0x3f9c) == '\0')) {
          iVar9 = FUN_00451030(iVar3);
          *(int *)(local_15b4 + 0xf48) = iVar9;
          if (iVar9 != 0) {
            *(undefined4 *)(local_15b4 + 0xf50) = 0;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar3 = _rand();
            *pbVar11 = (byte)iVar3;
            iVar3 = _rand();
            bVar7 = *pbVar11;
            *(byte *)(iVar5 + 0xf4d) = (byte)iVar3;
            bVar6 = '\x01' << (bVar7 & 7);
            bVar6 = ~bVar6 & (byte)iVar3 | bVar6;
            *(byte *)(iVar5 + 0xf4d) = bVar6;
            *(byte *)(iVar5 + 0xf4e) = bVar7 + bVar6 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar3 = g_clientContext;
            pbVar11 = (byte *)(g_clientContext + 0x62140);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = _rand();
            *pbVar11 = (byte)iVar5;
            local_15ac = _rand();
            local_15ac = local_15ac & 0x800000ff;
            if ((int)local_15ac < 0) {
              local_15ac = (local_15ac - 1 | 0xffffff00) + 1;
            }
            bVar7 = *pbVar11;
            *(byte *)(iVar3 + 0x62141) = (byte)local_15ac;
            bVar6 = '\x01' << (bVar7 & 7);
            bVar6 = ~bVar6 & (byte)local_15ac | bVar6;
            *(byte *)(iVar3 + 0x62141) = bVar6;
            *(byte *)(iVar3 + 0x62142) = bVar7 + bVar6 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar3 = local_15c4;
          }
        }
        iVar5 = local_15b4;
        pbVar11 = (byte *)(local_15b4 + 0x3918);
        cVar1 = PeekPacketChecksumBool();
        if ((cVar1 == '\0') && (iVar3 = FUN_004511b0(iVar3), iVar3 != 0)) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar3 = _rand();
          *pbVar11 = (byte)iVar3;
          iVar3 = _rand();
          bVar7 = *pbVar11;
          *(byte *)(iVar5 + 0x3919) = (byte)iVar3;
          bVar6 = '\x01' << (bVar7 & 7);
          bVar6 = ~bVar6 & (byte)iVar3 | bVar6;
          *(byte *)(iVar5 + 0x3919) = bVar6;
          *(byte *)(iVar5 + 0x391a) = bVar7 + bVar6 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar2 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        FUN_00436dc0(local_15c4,local_15b8,uVar2);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar3 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar3 == 0) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar3 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15ac = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          FUN_00436bd0(local_15c4 - ((int)local_15ac >> 8),local_15b8 - (iVar3 >> 8),
                       *(undefined4 *)(local_15b4 + 0x1e50));
        }
        cVar1 = PeekPacketChecksumBool();
        if (cVar1 != '\0') {
          FUN_00436ec0(local_15c4,local_15b8);
        }
        cVar1 = FUN_00450e10(local_15b8);
        iVar3 = local_15b4;
        if (cVar1 != '\0') {
          FUN_00458a00(&local_15c4,&local_15bc,local_159c,local_15a4,local_1590,local_1578,
                       local_1588,0,1);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar3 = local_15b4;
          EncodeOutgoingPacketField(local_15c4 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15bc << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15c4);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(local_15bc);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = _rand();
          *(char *)(iVar3 + 0xf45) = (char)iVar5;
          local_1598[0] = _rand();
          local_1598[0] = local_1598[0] & 0x800000ff;
          if ((int)local_1598[0] < 0) {
            local_1598[0] = (local_1598[0] - 1 | 0xffffff00) + 1;
          }
          bVar7 = *(byte *)(iVar3 + 0xf45);
          *(byte *)(iVar3 + 0xf46) = (byte)local_1598[0];
          bVar6 = '\x01' << (bVar7 & 7);
          bVar4 = ~bVar6 & (byte)local_1598[0];
LAB_0048d0d0:
          *(byte *)(iVar3 + 0xf46) = bVar4 | bVar6;
          *(byte *)(iVar3 + 0xf47) = bVar7 + (bVar4 | bVar6) + -0x34;
          goto LAB_0048d0e3;
        }
        local_15bc = 0;
        do {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15ac = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_1580[0] = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15a0 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = FUN_00425ac0(g_clientContext,local_15a0,local_1580[0],
                               (int)local_15ac / *(int *)(iVar3 + 0x3fa4));
          if (((iVar5 != 0) && (cVar1 = PeekPacketChecksumBool(), cVar1 != '\0')) &&
             (cVar1 = PeekPacketChecksumBool(), cVar1 != '\x01')) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar3 = local_15b4;
            EncodeOutgoingPacketField(local_15c4 << 8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField(local_15b8 << 8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField(local_15c4);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField(local_15b8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = _rand();
            *(char *)(iVar3 + 0xf45) = (char)iVar5;
            local_1598[0] = _rand();
            local_1598[0] = local_1598[0] & 0x800000ff;
            if ((int)local_1598[0] < 0) {
              local_1598[0] = (local_1598[0] - 1 | 0xffffff00) + 1;
            }
            bVar7 = *(byte *)(iVar3 + 0xf45);
            *(byte *)(iVar3 + 0xf46) = (byte)local_1598[0];
            bVar6 = '\x01' << (bVar7 & 7);
            bVar4 = ~bVar6 & (byte)local_1598[0];
            goto LAB_0048d0d0;
          }
          local_15bc = local_15bc + 1;
        } while (local_15bc < 8);
        local_15bc = 0;
        do {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15ac = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_1580[0] = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15a0 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = FUN_00425c90(local_15a0,local_1580[0],(int)local_15ac / *(int *)(iVar3 + 0x3fa4));
          if (iVar5 != 0) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar3 = local_15b4;
            EncodeOutgoingPacketField(local_15c4 << 8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField(local_15b8 << 8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField(local_15c4);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField(local_15b8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = _rand();
            *(char *)(iVar3 + 0xf45) = (char)iVar5;
            local_1598[0] = _rand();
            local_1598[0] = local_1598[0] & 0x800000ff;
            if ((int)local_1598[0] < 0) {
              local_1598[0] = (local_1598[0] - 1 | 0xffffff00) + 1;
            }
            bVar7 = *(byte *)(iVar3 + 0xf45);
            *(byte *)(iVar3 + 0xf46) = (byte)local_1598[0];
            bVar6 = '\x01' << (bVar7 & 7);
            bVar4 = ~bVar6 & (byte)local_1598[0];
            goto LAB_0048d0d0;
          }
          local_15bc = local_15bc + 1;
        } while (local_15bc < 8);
        local_15bc = 0;
        do {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15ac = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_1580[0] = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15a0 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = FUN_00425e60(local_15a0,local_1580[0],(int)local_15ac / *(int *)(iVar3 + 0x3fa4));
          if (iVar5 != 0) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar3 = local_15b4;
            EncodeOutgoingPacketField(local_15c4 << 8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField(local_15b8 << 8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField(local_15c4);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField(local_15b8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = _rand();
            *(char *)(iVar3 + 0xf45) = (char)iVar5;
            local_1598[0] = _rand();
            local_1598[0] = local_1598[0] & 0x800000ff;
            if ((int)local_1598[0] < 0) {
              local_1598[0] = (local_1598[0] - 1 | 0xffffff00) + 1;
            }
            bVar7 = *(byte *)(iVar3 + 0xf45);
            *(byte *)(iVar3 + 0xf46) = (byte)local_1598[0];
            bVar6 = '\x01' << (bVar7 & 7);
            bVar4 = ~bVar6 & (byte)local_1598[0];
            goto LAB_0048d0d0;
          }
          local_15bc = local_15bc + 1;
        } while (local_15bc < 0x40);
        local_15b8 = local_15b8 + local_158c;
        local_15a4 = local_15a4 + param_2;
      } while (local_15a4 < (int)local_1598[0]);
    }
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

