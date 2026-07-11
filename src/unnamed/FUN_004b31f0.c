/* FUN_004b31f0 - 0x004b31f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void __thiscall FUN_004b31f0(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  uint uVar12;
  undefined4 *unaff_FS_OFFSET;
  undefined *puVar13;
  undefined4 uVar14;
  undefined4 local_19cc;
  undefined1 local_19bc [444];
  undefined1 auStack_1800 [652];
  undefined1 local_1574 [444];
  undefined1 auStack_13b8 [652];
  undefined1 local_112c [548];
  undefined1 local_f08 [496];
  undefined1 auStack_d18 [600];
  undefined1 local_ac0 [496];
  undefined1 auStack_8d0 [600];
  undefined1 local_678 [548];
  undefined1 local_454 [548];
  undefined1 local_230 [452];
  undefined4 uStack_6c;
  undefined4 uStack_38;
  undefined4 uStack_10;
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053e0d4;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uStack_10 = 0x4b320f;
  uVar5 = FUN_0045f840();
  switch(param_2) {
  case 1:
    if (*(int *)(param_1 + 0xb0a4) == -1) {
      uVar5 = AcquireSoundChannel(1);
      *(undefined4 *)(param_1 + 0xb0a4) = uVar5;
    }
    break;
  default:
    iVar3 = *(int *)(param_1 + 0xb0a4);
    if (DAT_00793549 != '\0') {
      if (iVar3 != -1) {
        (**(code **)(**(int **)(DAT_00793554 + iVar3 * 4) + 0xc))();
      }
      if (iVar3 == 0) {
        DAT_00793568 = 0;
      }
    }
    *(undefined4 *)(param_1 + 0xb0a4) = 0xffffffff;
    break;
  case 4:
    if (*(int *)(param_1 + 0xb0a4) == -1) {
      uVar5 = AcquireSoundChannel(1);
      *(undefined4 *)(param_1 + 0xb0a4) = uVar5;
    }
    break;
  case 5:
    if (param_3 != 0xc) break;
    QueueOutgoingPacketField(0xffffffff);
    if (*(char *)(param_1 + 0x651c) == '\x01') {
      puVar13 = &DAT_00796aa0;
    }
    else {
      puVar13 = &DAT_00794e48;
    }
    uVar6 = PeekChecksumStateUnderLock(puVar13);
    cVar4 = PeekPacketChecksumBool();
    if ((cVar4 == '\x01') || (cVar4 = PeekPacketChecksumBool(), cVar4 == '\x01')) {
      uVar7 = 0;
    }
    else {
      uVar7 = 8;
    }
    uVar8 = EncodeChecksumPairDiff(param_1 + 0xb30,local_1574,param_1 + 0x5620);
    local_4 = 0;
    uVar9 = EncodeChecksumPairSum(param_1 + 0x90c,local_112c,param_1 + 0x53fc);
    local_4 = 1;
    uVar6 = PeekPacketChecksumBool(uVar6,1);
    uVar10 = PeekChecksumStateUnderLock(param_1 + 0x7864);
    uVar11 = PeekChecksumStateUnderLock(param_1 + 0x4d90);
    uVar8 = PeekChecksumStateUnderLock(uVar8);
    uVar9 = PeekChecksumStateUnderLock(uVar9);
    FUN_0042bbb0(*(undefined1 *)(param_1 + 8),uVar7,3,0,*(int *)(param_1 + 0xae2c) != 0,uVar9,uVar8,
                 uVar11,uVar10,uVar5,uVar6);
    local_4 = 0;
    ScrubChecksumGuard();
    local_4 = 0xffffffff;
    ScrubChecksumGuard();
    cVar4 = PeekPacketChecksumBool();
    goto joined_r0x004b376c;
  case 6:
    if (param_3 != 6) break;
    QueueOutgoingPacketField(0xffffffff);
    if (*(char *)(param_1 + 0x651c) == '\x01') {
      puVar13 = &DAT_00796aa0;
    }
    else {
      puVar13 = &DAT_00794e48;
    }
    uVar6 = PeekChecksumStateUnderLock(puVar13);
    cVar4 = PeekPacketChecksumBool();
    if (cVar4 == '\x01') {
LAB_004b3445:
      local_19cc = 0;
    }
    else {
      cVar4 = PeekPacketChecksumBool();
      local_19cc = 8;
      if (cVar4 == '\x01') goto LAB_004b3445;
    }
    iVar3 = param_1 + 0x5a68;
    iVar1 = param_1 + 0xb30;
    uVar7 = EncodeChecksumPairDiff(iVar1,local_19bc,iVar3);
    iVar2 = param_1 + 0x5844;
    local_4 = 2;
    uVar8 = EncodeChecksumPairSum(param_1 + 0x90c,local_454,iVar2);
    local_4 = 3;
    uVar6 = PeekPacketChecksumBool(uVar6,3);
    uVar9 = PeekChecksumStateUnderLock(param_1 + 0x7864);
    uVar10 = PeekChecksumStateUnderLock(param_1 + 0x4d90);
    uVar7 = PeekChecksumStateUnderLock(uVar7);
    uVar8 = PeekChecksumStateUnderLock(uVar8);
    FUN_0042bbb0(*(undefined1 *)(param_1 + 8),local_19cc,3,1,
                 CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                          *(int *)(param_1 + 0xae2c) != 0),uVar8,uVar7,uVar10,uVar9,uVar5,uVar6);
    uStack_38 = 2;
    ScrubChecksumGuard();
    uStack_38 = 0xffffffff;
    ScrubChecksumGuard();
    if (*(char *)(param_1 + 0x651c) == '\x01') {
      puVar13 = &DAT_00796aa0;
    }
    else {
      puVar13 = &DAT_00794e48;
    }
    uVar5 = PeekChecksumStateUnderLock(puVar13);
    cVar4 = PeekPacketChecksumBool();
    if (cVar4 == '\x01') {
LAB_004b356f:
      uVar6 = 1;
    }
    else {
      cVar4 = PeekPacketChecksumBool();
      uVar6 = 9;
      if (cVar4 == '\x01') goto LAB_004b356f;
    }
    uVar8 = EncodeChecksumPairDiff(iVar1,auStack_d18,iVar3);
    uStack_38 = 4;
    uVar9 = EncodeChecksumPairSum(param_1 + 0x90c,auStack_8d0,iVar2);
    uStack_38 = 5;
    uVar5 = PeekPacketChecksumBool(uVar5,3);
    uVar10 = PeekChecksumStateUnderLock(param_1 + 0x7864);
    uVar11 = PeekChecksumStateUnderLock(param_1 + 0x4d90);
    uVar8 = PeekChecksumStateUnderLock(uVar8);
    uVar9 = PeekChecksumStateUnderLock(uVar9);
    FUN_0042bbb0(*(undefined1 *)(param_1 + 8),uVar6,3,1,
                 CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                          *(int *)(param_1 + 0xae2c) != 0),uVar9,uVar8,uVar11,uVar10,uVar7,uVar5);
    uStack_6c = 4;
    ScrubChecksumGuard();
    uStack_6c = 0xffffffff;
    ScrubChecksumGuard();
    if (*(char *)(param_1 + 0x651c) == '\x01') {
      puVar13 = &DAT_00796aa0;
    }
    else {
      puVar13 = &DAT_00794e48;
    }
    uVar5 = PeekChecksumStateUnderLock(puVar13);
    cVar4 = PeekPacketChecksumBool();
    if (cVar4 == '\x01') {
LAB_004b368d:
      uVar6 = 2;
    }
    else {
      cVar4 = PeekPacketChecksumBool();
      uVar6 = 10;
      if (cVar4 == '\x01') goto LAB_004b368d;
    }
    uVar7 = EncodeChecksumPairDiff(iVar1,auStack_13b8,iVar3);
    uStack_6c = 6;
    uVar9 = EncodeChecksumPairSum(param_1 + 0x90c,auStack_1800,iVar2);
    uStack_6c = 7;
    uVar5 = PeekPacketChecksumBool(uVar5,3);
    uVar10 = PeekChecksumStateUnderLock(param_1 + 0x7864);
    uVar11 = PeekChecksumStateUnderLock(param_1 + 0x4d90);
    uVar7 = PeekChecksumStateUnderLock(uVar7);
    uVar9 = PeekChecksumStateUnderLock(uVar9);
    FUN_0042bbb0(*(undefined1 *)(param_1 + 8),uVar6,3,1,
                 CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                          *(int *)(param_1 + 0xae2c) != 0),uVar9,uVar7,uVar11,uVar10,uVar8,uVar5);
    local_4 = 6;
    ScrubChecksumGuard();
    local_4 = 0xffffffff;
    ScrubChecksumGuard();
    cVar4 = PeekPacketChecksumBool();
joined_r0x004b376c:
    if (cVar4 == '\0') {
      AcquireSoundChannel(0);
    }
    cVar4 = PeekPacketChecksumBool();
    if ((cVar4 == '\0') && (cVar4 = PeekPacketChecksumBool(), cVar4 == '\0')) {
LAB_004b38c8:
      cVar4 = FUN_0043a530();
      if (cVar4 == '\0') {
        uVar5 = PeekChecksumStateUnderLock(&DAT_007949c8);
        QueueOutgoingPacketField(uVar5);
      }
      SetGuardedBool(1);
    }
    break;
  case 8:
    if (param_3 != 0xc) break;
    QueueOutgoingPacketField(0xffffffff);
    cVar4 = PeekPacketChecksumBool();
    if ((cVar4 == '\x01') || (cVar4 = PeekPacketChecksumBool(), cVar4 == '\x01')) {
      uVar5 = 0;
    }
    else {
      uVar5 = 8;
    }
    uVar6 = EncodeChecksumPairDiff(param_1 + 0xb30,local_ac0,param_1 + 0x5620);
    local_4 = 8;
    uVar7 = EncodeChecksumPairSum(param_1 + 0x90c,local_f08,param_1 + 0x53fc);
    local_4 = 9;
    uVar12 = (uint)*(ushort *)(param_1 + 0xbfbc);
    uVar8 = PeekChecksumStateUnderLock(param_1 + 0x7864);
    uVar9 = PeekChecksumStateUnderLock(param_1 + 0x4d90);
    uVar6 = PeekChecksumStateUnderLock(uVar6);
    uVar7 = PeekChecksumStateUnderLock(uVar7);
    FUN_004317b0(*(undefined1 *)(param_1 + 8),uVar5,uVar7,uVar6,uVar9,uVar8,uVar12);
    local_4 = 8;
    ScrubChecksumGuard();
    local_4 = 0xffffffff;
    ScrubChecksumGuard();
    cVar4 = PeekPacketChecksumBool();
    if (cVar4 == '\0') {
      AcquireSoundChannel(0);
    }
    goto LAB_004b38c8;
  case 10:
    if (param_3 == 6) {
      QueueOutgoingPacketField(0xffffffff);
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puVar13 = &DAT_00796aa0;
      }
      else {
        puVar13 = &DAT_00794e48;
      }
      uVar6 = PeekChecksumStateUnderLock(puVar13);
      uVar7 = EncodeChecksumPairDiff(param_1 + 0xb30,local_230,param_1 + 0x5eb0);
      local_4 = 10;
      uVar8 = EncodeChecksumPairSum(param_1 + 0x90c,local_678,param_1 + 0x5c8c);
      uVar14 = 1;
      local_4 = 0xb;
      uVar9 = PeekPacketChecksumBool(uVar6,1);
      uVar10 = PeekChecksumStateUnderLock(param_1 + 0x7864);
      uVar11 = PeekChecksumStateUnderLock(param_1 + 0x4d90);
      uVar7 = PeekChecksumStateUnderLock(uVar7);
      uVar8 = PeekChecksumStateUnderLock(uVar8);
      FUN_0042de70(*(undefined1 *)(param_1 + 8),0,3,*(int *)(param_1 + 0xae2c) != 0,uVar8,uVar7,
                   uVar11,uVar10,uVar5,uVar9,uVar6,uVar14);
      local_4 = 10;
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      ScrubChecksumGuard();
      cVar4 = PeekPacketChecksumBool();
      if (cVar4 == '\0') {
        AcquireSoundChannel(0);
      }
      cVar4 = FUN_0043a530();
      if (cVar4 == '\0') {
        uVar5 = PeekChecksumStateUnderLock(&DAT_007949c8);
        QueueOutgoingPacketField(uVar5);
        iVar3 = g_clientContext;
        *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
        *(undefined4 *)(&DAT_005f376c + iVar3) = 0;
        SetGuardedBool(1);
      }
      else {
        SetGuardedBool(1);
      }
    }
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

