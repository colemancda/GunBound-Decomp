/* FUN_004542a0 - 0x004542a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void __thiscall FUN_004542a0(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  char cVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 *unaff_FS_OFFSET;
  undefined *puVar11;
  undefined4 uVar12;
  undefined4 local_1e0c;
  undefined4 local_1e08;
  undefined1 local_1e04 [548];
  undefined1 local_1be0 [548];
  undefined1 local_19bc [548];
  undefined1 local_1798 [548];
  undefined1 local_1574 [548];
  undefined1 local_1350 [548];
  undefined1 local_112c [548];
  undefined1 local_f08 [548];
  undefined1 local_ce4 [548];
  undefined1 local_ac0 [548];
  undefined1 local_89c [548];
  undefined1 local_678 [548];
  undefined1 local_454 [548];
  undefined1 local_230 [544];
  undefined4 uStack_10;
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005403ca;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uStack_10 = 0x4542bf;
  uVar3 = FUN_0045f840();
  switch(param_2) {
  case 1:
    if (*(int *)(param_1 + 0xb0a4) == -1) {
      uVar3 = FUN_004ee9b0(1);
      *(undefined4 *)(param_1 + 0xb0a4) = uVar3;
    }
    break;
  default:
    iVar1 = *(int *)(param_1 + 0xb0a4);
    if (DAT_00793549 != '\0') {
      if (iVar1 != -1) {
        (**(code **)(**(int **)(DAT_00793554 + iVar1 * 4) + 0xc))();
      }
      if (iVar1 == 0) {
        DAT_00793568 = 0;
      }
    }
    *(undefined4 *)(param_1 + 0xb0a4) = 0xffffffff;
    break;
  case 4:
    if (*(int *)(param_1 + 0xb0a4) == -1) {
      uVar3 = FUN_004ee9b0(1);
      *(undefined4 *)(param_1 + 0xb0a4) = uVar3;
    }
    break;
  case 5:
    if (param_3 != 8) break;
    QueueOutgoingPacketField(0xffffffff);
    if (*(char *)(param_1 + 0x651c) == '\x01') {
      puVar11 = &DAT_00796aa0;
    }
    else {
      puVar11 = &DAT_00794e48;
    }
    uVar5 = PeekChecksumStateUnderLock(puVar11);
    cVar2 = PeekPacketChecksumBool();
    if (cVar2 == '\x01') {
LAB_0045439b:
      local_1e0c = 0;
    }
    else {
      cVar2 = PeekPacketChecksumBool();
      local_1e0c = 8;
      if (cVar2 == '\x01') goto LAB_0045439b;
    }
    uVar6 = EncodeChecksumPairDiff(param_1 + 0xb30,local_19bc,param_1 + 0x5620);
    local_4 = 0;
    uVar7 = EncodeChecksumPairSum(param_1 + 0x90c,local_112c,param_1 + 0x53fc);
    local_4 = 1;
    uVar5 = PeekPacketChecksumBool(uVar5,1);
    uVar8 = PeekChecksumStateUnderLock(param_1 + 0x7864);
    uVar9 = PeekChecksumStateUnderLock(param_1 + 0x4d90);
    uVar6 = PeekChecksumStateUnderLock(uVar6);
    uVar7 = PeekChecksumStateUnderLock(uVar7);
    FUN_0042bbb0(*(undefined1 *)(param_1 + 8),local_1e0c,5,0,*(int *)(param_1 + 0xae2c) != 0,uVar7,
                 uVar6,uVar9,uVar8,uVar3,uVar5);
    local_4 = 0;
    ScrubChecksumGuard();
    local_4 = 0xffffffff;
    ScrubChecksumGuard();
    cVar2 = PeekPacketChecksumBool();
    goto joined_r0x00454a06;
  case 6:
    switch(param_3) {
    case 8:
      QueueOutgoingPacketField(0xffffffff);
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar5 = PeekChecksumStateUnderLock(puVar11);
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\x01') {
LAB_00454508:
        local_1e08 = 0;
      }
      else {
        cVar2 = PeekPacketChecksumBool();
        local_1e08 = 8;
        if (cVar2 == '\x01') goto LAB_00454508;
      }
      uVar6 = EncodeChecksumPairDiff(param_1 + 0xb30,local_1574,param_1 + 0x5a68);
      local_4 = 2;
      uVar7 = EncodeChecksumPairSum(param_1 + 0x90c,local_ce4,param_1 + 0x5844);
      local_4 = 3;
      uVar5 = PeekPacketChecksumBool(uVar5,4);
      uVar8 = PeekChecksumStateUnderLock(param_1 + 0x7864);
      uVar9 = PeekChecksumStateUnderLock(param_1 + 0x4d90);
      uVar6 = PeekChecksumStateUnderLock(uVar6);
      uVar7 = PeekChecksumStateUnderLock(uVar7);
      FUN_0042bbb0(*(undefined1 *)(param_1 + 8),local_1e08,5,1,*(int *)(param_1 + 0xae2c) != 0,uVar7
                   ,uVar6,uVar9,uVar8,uVar3,uVar5);
      local_4 = 2;
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      ScrubChecksumGuard();
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\0') {
        FUN_004ee9b0(0);
      }
    default:
      goto switchD_004544ac_caseD_9;
    case 10:
      QueueOutgoingPacketField(0xffffffff);
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar5 = PeekChecksumStateUnderLock(puVar11);
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\x01') {
LAB_00454665:
        local_1e08 = 1;
      }
      else {
        cVar2 = PeekPacketChecksumBool();
        local_1e08 = 9;
        if (cVar2 == '\x01') goto LAB_00454665;
      }
      uVar6 = EncodeChecksumPairDiff(param_1 + 0xb30,local_1e04,param_1 + 0x5a68);
      local_4 = 4;
      uVar7 = EncodeChecksumPairSum(param_1 + 0x90c,local_454,param_1 + 0x5844);
      local_4 = 5;
      uVar5 = PeekPacketChecksumBool(uVar5,4);
      uVar8 = PeekChecksumStateUnderLock(param_1 + 0x7864);
      uVar9 = PeekChecksumStateUnderLock(param_1 + 0x4d90);
      uVar6 = PeekChecksumStateUnderLock(uVar6);
      uVar7 = PeekChecksumStateUnderLock(uVar7);
      FUN_0042bbb0(*(undefined1 *)(param_1 + 8),local_1e08,5,1,*(int *)(param_1 + 0xae2c) != 0,uVar7
                   ,uVar6,uVar9,uVar8,uVar3,uVar5);
      local_4 = 4;
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      ScrubChecksumGuard();
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\0') {
        FUN_004ee9b0(0);
      }
      goto switchD_004544ac_caseD_9;
    case 0xc:
      QueueOutgoingPacketField(0xffffffff);
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar5 = PeekChecksumStateUnderLock(puVar11);
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\x01') {
LAB_004547bc:
        local_1e08 = 2;
      }
      else {
        cVar2 = PeekPacketChecksumBool();
        local_1e08 = 10;
        if (cVar2 == '\x01') goto LAB_004547bc;
      }
      uVar6 = EncodeChecksumPairDiff(param_1 + 0xb30,local_1be0,param_1 + 0x5a68);
      local_4 = 6;
      uVar7 = EncodeChecksumPairSum(param_1 + 0x90c,local_89c,param_1 + 0x5844);
      local_4 = 7;
      uVar5 = PeekPacketChecksumBool(uVar5,4);
      uVar8 = PeekChecksumStateUnderLock(param_1 + 0x7864);
      uVar9 = PeekChecksumStateUnderLock(param_1 + 0x4d90);
      uVar6 = PeekChecksumStateUnderLock(uVar6);
      uVar7 = PeekChecksumStateUnderLock(uVar7);
      FUN_0042bbb0(*(undefined1 *)(param_1 + 8),local_1e08,5,1,*(int *)(param_1 + 0xae2c) != 0,uVar7
                   ,uVar6,uVar9,uVar8,uVar3,uVar5);
      local_4 = 6;
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      ScrubChecksumGuard();
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\0') {
        FUN_004ee9b0(0);
      }
      goto switchD_004544ac_caseD_9;
    case 0xe:
      QueueOutgoingPacketField(0xffffffff);
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar5 = PeekChecksumStateUnderLock(puVar11);
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\x01') {
LAB_00454919:
        local_1e08 = 3;
      }
      else {
        cVar2 = PeekPacketChecksumBool();
        local_1e08 = 0xb;
        if (cVar2 == '\x01') goto LAB_00454919;
      }
      uVar6 = EncodeChecksumPairDiff(param_1 + 0xb30,local_1350,param_1 + 0x5a68);
      local_4 = 8;
      uVar7 = EncodeChecksumPairSum(param_1 + 0x90c,local_1798,param_1 + 0x5844);
      local_4 = 9;
      uVar5 = PeekPacketChecksumBool(uVar5,4);
      uVar8 = PeekChecksumStateUnderLock(param_1 + 0x7864);
      uVar9 = PeekChecksumStateUnderLock(param_1 + 0x4d90);
      uVar6 = PeekChecksumStateUnderLock(uVar6);
      uVar7 = PeekChecksumStateUnderLock(uVar7);
      FUN_0042bbb0(*(undefined1 *)(param_1 + 8),local_1e08,5,1,*(int *)(param_1 + 0xae2c) != 0,uVar7
                   ,uVar6,uVar9,uVar8,uVar3,uVar5);
      local_4 = 8;
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      ScrubChecksumGuard();
      cVar2 = PeekPacketChecksumBool();
    }
joined_r0x00454a06:
    if (cVar2 == '\0') {
      FUN_004ee9b0(0);
    }
    cVar2 = PeekPacketChecksumBool();
    if ((cVar2 == '\0') && (cVar2 = PeekPacketChecksumBool(), cVar2 == '\0')) {
LAB_00454b61:
      cVar2 = FUN_0043a530();
      if (cVar2 == '\0') {
        uVar3 = PeekChecksumStateUnderLock(&DAT_007949c8);
        QueueOutgoingPacketField(uVar3);
      }
      FUN_00406500(1);
    }
    break;
  case 8:
    uVar3 = 8;
    if (param_3 != 8) break;
    QueueOutgoingPacketField(0xffffffff);
    cVar2 = PeekPacketChecksumBool();
    if ((cVar2 == '\x01') || (cVar2 = PeekPacketChecksumBool(), cVar2 == '\x01')) {
      uVar3 = 0;
    }
    uVar5 = EncodeChecksumPairDiff(param_1 + 0xb30,local_ac0,param_1 + 0x5620);
    local_4 = 10;
    uVar6 = EncodeChecksumPairSum(param_1 + 0x90c,local_f08,param_1 + 0x53fc);
    local_4 = 0xb;
    uVar4 = (uint)*(ushort *)(param_1 + 0xbfbc);
    uVar7 = PeekChecksumStateUnderLock(param_1 + 0x7864);
    uVar8 = PeekChecksumStateUnderLock(param_1 + 0x4d90);
    uVar5 = PeekChecksumStateUnderLock(uVar5);
    uVar6 = PeekChecksumStateUnderLock(uVar6);
    FUN_004317b0(*(undefined1 *)(param_1 + 8),uVar3,uVar6,uVar5,uVar8,uVar7,uVar4);
    local_4 = 10;
    ScrubChecksumGuard();
    local_4 = 0xffffffff;
    ScrubChecksumGuard();
    cVar2 = PeekPacketChecksumBool();
    if (cVar2 == '\0') {
      FUN_004ee9b0(0);
    }
    goto LAB_00454b61;
  case 10:
    if (param_3 == 8) {
      QueueOutgoingPacketField(0xffffffff);
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar5 = PeekChecksumStateUnderLock(puVar11);
      uVar6 = EncodeChecksumPairDiff(param_1 + 0xb30,local_230,param_1 + 0x5eb0);
      local_4 = 0xc;
      uVar7 = EncodeChecksumPairSum(param_1 + 0x90c,local_678,param_1 + 0x5c8c);
      uVar12 = 1;
      local_4 = 0xd;
      uVar8 = PeekPacketChecksumBool(uVar5,1);
      uVar9 = PeekChecksumStateUnderLock(param_1 + 0x7864);
      uVar10 = PeekChecksumStateUnderLock(param_1 + 0x4d90);
      uVar6 = PeekChecksumStateUnderLock(uVar6);
      uVar7 = PeekChecksumStateUnderLock(uVar7);
      FUN_0042de70(*(undefined1 *)(param_1 + 8),0,5,*(int *)(param_1 + 0xae2c) != 0,uVar7,uVar6,
                   uVar10,uVar9,uVar3,uVar8,uVar5,uVar12);
      local_4 = 0xc;
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      ScrubChecksumGuard();
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\0') {
        FUN_004ee9b0(0);
      }
      cVar2 = FUN_0043a530();
      if (cVar2 == '\0') {
        uVar3 = PeekChecksumStateUnderLock(&DAT_007949c8);
        QueueOutgoingPacketField(uVar3);
        iVar1 = g_clientContext;
        *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
        *(undefined4 *)(&DAT_005f376c + iVar1) = 0;
        FUN_00406500(1);
      }
      else {
        FUN_00406500(1);
      }
    }
  }
switchD_004544ac_caseD_9:
  *unaff_FS_OFFSET = local_c;
  return;
}

