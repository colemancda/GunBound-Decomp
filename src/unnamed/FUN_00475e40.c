/* FUN_00475e40 - 0x00475e40 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void __thiscall FUN_00475e40(int param_1,undefined4 param_2,int param_3)

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
  undefined4 local_1134;
  undefined4 local_1130;
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
  puStack_8 = &LAB_005400f8;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uStack_10 = 0x475e5f;
  uVar3 = FUN_0045f840();
  switch(param_2) {
  case 1:
    if (*(int *)(param_1 + 0xb0a4) == -1) {
      uVar3 = FUN_004ee9b0(1);
      *(undefined4 *)(param_1 + 0xb0a4) = uVar3;
    }
    break;
  case 4:
    if (*(int *)(param_1 + 0xb0a4) == -1) {
      uVar3 = FUN_004ee9b0(1);
      *(undefined4 *)(param_1 + 0xb0a4) = uVar3;
    }
    break;
  case 5:
    if (param_3 != 0xd) break;
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
LAB_00475f39:
      local_1134 = 0;
    }
    else {
      cVar2 = PeekPacketChecksumBool();
      local_1134 = 8;
      if (cVar2 == '\x01') goto LAB_00475f39;
    }
    uVar6 = EncodeChecksumPairDiff(param_1 + 0xb30,local_ce4,param_1 + 0x5620);
    local_4 = 0;
    uVar7 = EncodeChecksumPairSum(param_1 + 0x90c,local_454,param_1 + 0x53fc);
    SUBFIELD(local_4,0,undefined1) = 1;
    uVar5 = PeekPacketChecksumBool(uVar5,1);
    uVar8 = PeekChecksumStateUnderLock(param_1 + 0x7864);
    uVar9 = PeekChecksumStateUnderLock(param_1 + 0x4d90);
    uVar6 = PeekChecksumStateUnderLock(uVar6);
    uVar7 = PeekChecksumStateUnderLock(uVar7);
    FUN_0042bbb0(*(undefined1 *)(param_1 + 8),local_1134,10,0,*(int *)(param_1 + 0xae2c) != 0,uVar7,
                 uVar6,uVar9,uVar8,uVar3,uVar5);
    local_4 = (uint)SUBFIELD(local_4,1,undefined3) << 8;
    ScrubChecksumGuard();
    local_4 = 0xffffffff;
    ScrubChecksumGuard();
    cVar2 = PeekPacketChecksumBool();
    goto joined_r0x00476181;
  case 6:
    if (param_3 != 4) break;
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
LAB_0047609a:
      local_1130 = 0;
    }
    else {
      cVar2 = PeekPacketChecksumBool();
      local_1130 = 8;
      if (cVar2 == '\x01') goto LAB_0047609a;
    }
    uVar6 = EncodeChecksumPairDiff(param_1 + 0xb30,local_89c,param_1 + 0x5a68);
    local_4 = 2;
    uVar7 = EncodeChecksumPairSum(param_1 + 0x90c,local_112c,param_1 + 0x5844);
    SUBFIELD(local_4,0,undefined1) = 3;
    uVar5 = PeekPacketChecksumBool(uVar5,1);
    uVar8 = PeekChecksumStateUnderLock(param_1 + 0x7864);
    uVar9 = PeekChecksumStateUnderLock(param_1 + 0x4d90);
    uVar6 = PeekChecksumStateUnderLock(uVar6);
    uVar7 = PeekChecksumStateUnderLock(uVar7);
    FUN_0042bbb0(*(undefined1 *)(param_1 + 8),local_1130,10,1,*(int *)(param_1 + 0xae2c) != 0,uVar7,
                 uVar6,uVar9,uVar8,uVar3,uVar5);
    local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),2);
    ScrubChecksumGuard();
    local_4 = 0xffffffff;
    ScrubChecksumGuard();
    cVar2 = PeekPacketChecksumBool();
joined_r0x00476181:
    if (cVar2 == '\0') {
      FUN_004ee9b0(0);
    }
    cVar2 = PeekPacketChecksumBool();
    if ((cVar2 == '\0') && (cVar2 = PeekPacketChecksumBool(), cVar2 == '\0')) {
LAB_004762dd:
      cVar2 = FUN_0043a530();
      if (cVar2 == '\0') {
        uVar3 = PeekChecksumStateUnderLock(&DAT_007949c8);
        QueueOutgoingPacketField(uVar3);
      }
      SetGuardedBool(1);
    }
    break;
  case 8:
    if (param_3 != 0xd) break;
    QueueOutgoingPacketField(0xffffffff);
    cVar2 = PeekPacketChecksumBool();
    if ((cVar2 == '\x01') || (cVar2 = PeekPacketChecksumBool(), cVar2 == '\x01')) {
      uVar3 = 0;
    }
    else {
      uVar3 = 8;
    }
    uVar5 = EncodeChecksumPairDiff(param_1 + 0xb30,local_ac0,param_1 + 0x5620);
    local_4 = 4;
    uVar6 = EncodeChecksumPairSum(param_1 + 0x90c,local_f08,param_1 + 0x53fc);
    SUBFIELD(local_4,0,undefined1) = 5;
    uVar4 = (uint)*(ushort *)(param_1 + 0xbfbc);
    uVar7 = PeekChecksumStateUnderLock(param_1 + 0x7864);
    uVar8 = PeekChecksumStateUnderLock(param_1 + 0x4d90);
    uVar5 = PeekChecksumStateUnderLock(uVar5);
    uVar6 = PeekChecksumStateUnderLock(uVar6);
    FUN_004317b0(*(undefined1 *)(param_1 + 8),uVar3,uVar6,uVar5,uVar8,uVar7,uVar4);
    local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),4);
    ScrubChecksumGuard();
    local_4 = 0xffffffff;
    ScrubChecksumGuard();
    cVar2 = PeekPacketChecksumBool();
    if (cVar2 == '\0') {
      FUN_004ee9b0(0);
    }
    goto LAB_004762dd;
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
      local_4 = 6;
      uVar7 = EncodeChecksumPairSum(param_1 + 0x90c,local_678,param_1 + 0x5c8c);
      uVar12 = 1;
      SUBFIELD(local_4,0,undefined1) = 7;
      uVar8 = PeekPacketChecksumBool(uVar5,1);
      uVar9 = PeekChecksumStateUnderLock(param_1 + 0x7864);
      uVar10 = PeekChecksumStateUnderLock(param_1 + 0x4d90);
      uVar6 = PeekChecksumStateUnderLock(uVar6);
      uVar7 = PeekChecksumStateUnderLock(uVar7);
      FUN_0042de70(*(undefined1 *)(param_1 + 8),8,10,
                   CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                            *(int *)(param_1 + 0xae2c) != 0),uVar7,uVar6,uVar10,uVar9,uVar3,uVar8,
                   uVar5,uVar12);
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),6);
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
      }
      SetGuardedBool(1);
    }
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
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

