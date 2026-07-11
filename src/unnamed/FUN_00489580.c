/* FUN_00489580 - 0x00489580 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void __thiscall FUN_00489580(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  char cVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 *unaff_FS_OFFSET;
  undefined *puVar11;
  int iStack_7e8c;
  undefined1 *puStack_7e88;
  undefined *puStack_7e84;
  undefined4 local_7e70;
  undefined4 local_7e6c;
  undefined1 auStack_7c9c [548];
  undefined1 auStack_7a78 [652];
  undefined1 local_77ec [444];
  undefined1 auStack_7630 [652];
  undefined1 local_73a4 [444];
  undefined1 auStack_71e8 [652];
  undefined1 local_6f5c [548];
  undefined1 local_6d38 [548];
  undefined1 local_6b14 [548];
  undefined1 local_68f0 [548];
  undefined1 local_66cc [548];
  undefined1 local_64a8 [548];
  undefined1 local_6284 [548];
  undefined1 local_6060 [496];
  undefined1 auStack_5e70 [600];
  undefined1 local_5c18 [496];
  undefined1 auStack_5a28 [600];
  undefined1 local_57d0 [444];
  undefined1 auStack_5614 [652];
  undefined1 local_5388 [444];
  undefined1 auStack_51cc [652];
  undefined1 local_4f40 [548];
  undefined1 local_4d1c [548];
  undefined1 local_4af8 [548];
  undefined1 local_48d4 [548];
  undefined1 local_46b0 [548];
  undefined1 local_448c [548];
  undefined1 local_4268 [496];
  undefined1 auStack_4078 [600];
  undefined1 local_3e20 [548];
  undefined1 local_3bfc [548];
  undefined1 local_39d8 [548];
  undefined1 local_37b4 [548];
  undefined1 local_3590 [548];
  undefined1 local_336c [548];
  undefined1 local_3148 [496];
  undefined1 auStack_2f58 [600];
  undefined1 local_2d00 [444];
  undefined1 auStack_2b44 [652];
  undefined1 local_28b8 [548];
  undefined1 local_2694 [548];
  undefined1 local_2470 [496];
  undefined1 auStack_2280 [600];
  undefined1 local_2028 [548];
  undefined1 local_1e04 [548];
  undefined1 local_1be0 [548];
  undefined1 local_19bc [548];
  undefined1 local_1798 [444];
  undefined1 auStack_15dc [652];
  undefined1 local_1350 [548];
  undefined1 local_112c [548];
  undefined1 local_f08 [496];
  undefined1 auStack_d18 [600];
  undefined1 local_ac0 [548];
  undefined1 local_89c [548];
  undefined1 local_678 [496];
  undefined1 auStack_488 [600];
  undefined1 local_230 [452];
  undefined4 uStack_6c;
  undefined4 uStack_38;
  undefined4 uStack_10;
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053f429;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uStack_10 = 0x48959f;
  puStack_7e84 = (undefined *)0x4895ac;
  uVar3 = FUN_0045f840();
  switch(param_2) {
  case 1:
    if (*(int *)(param_1 + 0xb0a4) == -1) {
      puStack_7e84 = (undefined *)0x1;
      puStack_7e88 = (undefined1 *)0x4895e0;
      uVar3 = AcquireSoundChannel();
      *(undefined4 *)(param_1 + 0xb0a4) = uVar3;
    }
    break;
  default:
    iVar1 = *(int *)(param_1 + 0xb0a4);
    if (DAT_00793549 != '\0') {
      if (iVar1 != -1) {
        puStack_7e84 = (undefined *)0x48b336;
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
      puStack_7e84 = (undefined *)0x1;
      puStack_7e88 = (undefined1 *)0x489608;
      uVar3 = AcquireSoundChannel();
      *(undefined4 *)(param_1 + 0xb0a4) = uVar3;
    }
    break;
  case 5:
    switch(param_3) {
    case 3:
      puStack_7e84 = (undefined *)0xffffffff;
      puStack_7e88 = (undefined1 *)0x48964a;
      QueueOutgoingPacketField();
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puStack_7e84 = &DAT_00796aa0;
      }
      else {
        puStack_7e84 = &DAT_00794e48;
      }
      puStack_7e88 = (undefined1 *)0x489664;
      uVar10 = PeekChecksumStateUnderLock();
      puStack_7e84 = (undefined *)0x489673;
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\x01') {
LAB_0048968e:
        local_7e70 = 0;
      }
      else {
        puStack_7e84 = (undefined *)0x489682;
        cVar2 = PeekPacketChecksumBool();
        local_7e70 = 8;
        if (cVar2 == '\x01') goto LAB_0048968e;
      }
      puStack_7e84 = &DAT_00e9ba40;
      puStack_7e88 = (undefined1 *)0x4896a0;
      puStack_7e84 = (undefined *)PeekChecksumStateUnderLock();
      puStack_7e88 = local_77ec;
      iStack_7e8c = param_1 + 0x7864;
      uVar4 = EncodeChecksumDeltaAdd();
      puStack_7e84 = (undefined *)(param_1 + 0x5620);
      puStack_7e88 = local_112c;
      iStack_7e8c = param_1 + 0xb30;
      local_4 = 0;
      uVar5 = EncodeChecksumPairDiff();
      puStack_7e84 = (undefined *)(param_1 + 0x53fc);
      puStack_7e88 = local_448c;
      iStack_7e8c = param_1 + 0x90c;
      SUBFIELD(local_4,0,undefined1) = 1;
      uVar6 = EncodeChecksumPairSum();
      puStack_7e84 = (undefined *)0x4;
      SUBFIELD(local_4,0,undefined1) = 2;
      iStack_7e8c = 0x489722;
      puStack_7e88 = (undefined1 *)uVar10;
      iStack_7e8c = PeekPacketChecksumBool();
      uVar10 = PeekChecksumStateUnderLock(uVar4);
      uVar4 = PeekChecksumStateUnderLock(param_1 + 0x4d90);
      uVar5 = PeekChecksumStateUnderLock(uVar5);
      uVar6 = PeekChecksumStateUnderLock(uVar6);
      SpawnPrimaryShot(*(undefined1 *)(param_1 + 8),local_7e70,4,0,*(int *)(param_1 + 0xae2c) != 0,uVar6
                   ,uVar5,uVar4,uVar10,uVar3);
      SUBFIELD(local_4,0,undefined1) = 1;
      puStack_7e84 = (undefined *)0x489782;
      ScrubChecksumGuard();
      local_4 = (uint)SUBFIELD(local_4,1,undefined3) << 8;
      puStack_7e84 = (undefined *)0x489796;
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      puStack_7e84 = (undefined *)0x4897a9;
      ScrubChecksumGuard();
      puStack_7e84 = (undefined *)0x4897b8;
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\0') {
        puStack_7e84 = (undefined *)0x0;
        puStack_7e88 = (undefined1 *)0x4897cd;
        AcquireSoundChannel();
      }
    default:
      goto switchD_0048a765_caseD_4;
    case 7:
      puStack_7e84 = (undefined *)0xffffffff;
      puStack_7e88 = (undefined1 *)0x4897e8;
      QueueOutgoingPacketField();
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puStack_7e84 = &DAT_00796aa0;
      }
      else {
        puStack_7e84 = &DAT_00794e48;
      }
      puStack_7e88 = (undefined1 *)0x489802;
      uVar10 = PeekChecksumStateUnderLock();
      puStack_7e84 = (undefined *)0x489811;
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\x01') {
LAB_0048982c:
        local_7e6c = 1;
      }
      else {
        puStack_7e84 = (undefined *)0x489820;
        cVar2 = PeekPacketChecksumBool();
        local_7e6c = 9;
        if (cVar2 == '\x01') goto LAB_0048982c;
      }
      puStack_7e84 = &DAT_00e9ba40;
      puStack_7e88 = (undefined1 *)0x48983e;
      puStack_7e84 = (undefined *)PeekChecksumStateUnderLock();
      puStack_7e88 = local_1e04;
      iStack_7e8c = param_1 + 0x7864;
      uVar4 = EncodeChecksumDeltaSub();
      puStack_7e84 = (undefined *)(param_1 + 0x5620);
      puStack_7e88 = local_73a4;
      iStack_7e8c = param_1 + 0xb30;
      local_4 = 3;
      uVar5 = EncodeChecksumPairDiff();
      puStack_7e84 = (undefined *)(param_1 + 0x53fc);
      puStack_7e88 = local_3bfc;
      iStack_7e8c = param_1 + 0x90c;
      SUBFIELD(local_4,0,undefined1) = 4;
      uVar6 = EncodeChecksumPairSum();
      puStack_7e84 = (undefined *)0x4;
      SUBFIELD(local_4,0,undefined1) = 5;
      iStack_7e8c = 0x4898c0;
      puStack_7e88 = (undefined1 *)uVar10;
      iStack_7e8c = PeekPacketChecksumBool();
      uVar10 = PeekChecksumStateUnderLock(uVar4);
      uVar4 = PeekChecksumStateUnderLock(param_1 + 0x4d90);
      uVar5 = PeekChecksumStateUnderLock(uVar5);
      uVar6 = PeekChecksumStateUnderLock(uVar6);
      SpawnPrimaryShot(*(undefined1 *)(param_1 + 8),local_7e6c,4,0,*(int *)(param_1 + 0xae2c) != 0,uVar6
                   ,uVar5,uVar4,uVar10,uVar3);
      SUBFIELD(local_4,0,undefined1) = 4;
      puStack_7e84 = (undefined *)0x489920;
      ScrubChecksumGuard();
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),3);
      puStack_7e84 = (undefined *)0x489934;
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      puStack_7e84 = (undefined *)0x489947;
      ScrubChecksumGuard();
      puStack_7e84 = (undefined *)0x489956;
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\0') {
        puStack_7e84 = (undefined *)0x0;
        puStack_7e88 = (undefined1 *)0x48996b;
        AcquireSoundChannel();
      }
      goto switchD_0048a765_caseD_4;
    case 0xc:
      puStack_7e84 = (undefined *)0xffffffff;
      puStack_7e88 = (undefined1 *)0x489986;
      QueueOutgoingPacketField();
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puStack_7e84 = &DAT_00796aa0;
      }
      else {
        puStack_7e84 = &DAT_00794e48;
      }
      puStack_7e88 = (undefined1 *)0x4899a0;
      uVar10 = PeekChecksumStateUnderLock();
      puStack_7e84 = (undefined *)0x4899af;
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\x01') {
LAB_004899ca:
        local_7e6c = 2;
      }
      else {
        puStack_7e84 = (undefined *)0x4899be;
        cVar2 = PeekPacketChecksumBool();
        local_7e6c = 10;
        if (cVar2 == '\x01') goto LAB_004899ca;
      }
      puStack_7e84 = (undefined *)0x1;
      puStack_7e88 = local_6b14;
      iStack_7e8c = param_1 + 0x4d90;
      uVar4 = EncodeChecksumDeltaAdd();
      puStack_7e84 = (undefined *)(param_1 + 0x5620);
      puStack_7e88 = local_37b4;
      iStack_7e8c = param_1 + 0xb30;
      local_4 = 6;
      uVar5 = EncodeChecksumPairDiff();
      puStack_7e84 = (undefined *)(param_1 + 0x53fc);
      puStack_7e88 = local_6f5c;
      iStack_7e8c = param_1 + 0x90c;
      SUBFIELD(local_4,0,undefined1) = 7;
      uVar6 = EncodeChecksumPairSum();
      puStack_7e84 = (undefined *)0x4;
      SUBFIELD(local_4,0,undefined1) = 8;
      iStack_7e8c = 0x489a55;
      puStack_7e88 = (undefined1 *)uVar10;
      iStack_7e8c = PeekPacketChecksumBool();
      uVar10 = PeekChecksumStateUnderLock(param_1 + 0x7864);
      uVar4 = PeekChecksumStateUnderLock(uVar4);
      uVar5 = PeekChecksumStateUnderLock(uVar5);
      uVar6 = PeekChecksumStateUnderLock(uVar6);
      SpawnPrimaryShot(*(undefined1 *)(param_1 + 8),local_7e6c,4,0,*(int *)(param_1 + 0xae2c) != 0,uVar6
                   ,uVar5,uVar4,uVar10,uVar3);
      SUBFIELD(local_4,0,undefined1) = 7;
      puStack_7e84 = (undefined *)0x489ab5;
      ScrubChecksumGuard();
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),6);
      puStack_7e84 = (undefined *)0x489ac9;
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      puStack_7e84 = (undefined *)0x489adc;
      ScrubChecksumGuard();
      puStack_7e84 = (undefined *)0x489aeb;
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\0') {
        puStack_7e84 = (undefined *)0x0;
        puStack_7e88 = (undefined1 *)0x489b00;
        AcquireSoundChannel();
      }
      goto switchD_0048a765_caseD_4;
    case 0x11:
      puStack_7e84 = (undefined *)0xffffffff;
      puStack_7e88 = (undefined1 *)0x489b1b;
      QueueOutgoingPacketField();
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puStack_7e84 = &DAT_00796aa0;
      }
      else {
        puStack_7e84 = &DAT_00794e48;
      }
      puStack_7e88 = (undefined1 *)0x489b35;
      uVar10 = PeekChecksumStateUnderLock();
      puStack_7e84 = (undefined *)0x489b44;
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\x01') {
LAB_00489b5f:
        local_7e6c = 3;
      }
      else {
        puStack_7e84 = (undefined *)0x489b53;
        cVar2 = PeekPacketChecksumBool();
        local_7e6c = 0xb;
        if (cVar2 == '\x01') goto LAB_00489b5f;
      }
      puStack_7e84 = (undefined *)0x1;
      puStack_7e88 = local_336c;
      iStack_7e8c = param_1 + 0x4d90;
      uVar4 = EncodeChecksumDeltaSub();
      puStack_7e84 = (undefined *)(param_1 + 0x5620);
      puStack_7e88 = local_66cc;
      iStack_7e8c = param_1 + 0xb30;
      local_4 = 9;
      uVar5 = EncodeChecksumPairDiff();
      puStack_7e84 = (undefined *)(param_1 + 0x53fc);
      puStack_7e88 = local_89c;
      iStack_7e8c = param_1 + 0x90c;
      SUBFIELD(local_4,0,undefined1) = 10;
      uVar6 = EncodeChecksumPairSum();
      puStack_7e84 = (undefined *)0x4;
      SUBFIELD(local_4,0,undefined1) = 0xb;
      iStack_7e8c = 0x489bea;
      puStack_7e88 = (undefined1 *)uVar10;
      iStack_7e8c = PeekPacketChecksumBool();
      uVar10 = PeekChecksumStateUnderLock(param_1 + 0x7864);
      uVar4 = PeekChecksumStateUnderLock(uVar4);
      uVar5 = PeekChecksumStateUnderLock(uVar5);
      uVar6 = PeekChecksumStateUnderLock(uVar6);
      SpawnPrimaryShot(*(undefined1 *)(param_1 + 8),local_7e6c,4,0,*(int *)(param_1 + 0xae2c) != 0,uVar6
                   ,uVar5,uVar4,uVar10,uVar3);
      SUBFIELD(local_4,0,undefined1) = 10;
      puStack_7e84 = (undefined *)0x489c4a;
      ScrubChecksumGuard();
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),9);
      puStack_7e84 = (undefined *)0x489c5e;
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      puStack_7e84 = (undefined *)0x489c71;
      ScrubChecksumGuard();
      puStack_7e84 = (undefined *)0x489c80;
      cVar2 = PeekPacketChecksumBool();
    }
    goto joined_r0x0048a106;
  case 6:
    if (param_3 == 6) {
      puStack_7e84 = (undefined *)0xffffffff;
      puStack_7e88 = (undefined1 *)0x48a18a;
      QueueOutgoingPacketField();
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puStack_7e84 = &DAT_00796aa0;
      }
      else {
        puStack_7e84 = &DAT_00794e48;
      }
      puStack_7e88 = (undefined1 *)0x48a1a4;
      uVar10 = PeekChecksumStateUnderLock();
      puStack_7e84 = (undefined *)0x48a1b3;
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\x01') {
LAB_0048a1ce:
        local_7e6c = 0;
      }
      else {
        puStack_7e84 = (undefined *)0x48a1c2;
        cVar2 = PeekPacketChecksumBool();
        local_7e6c = 8;
        if (cVar2 == '\x01') goto LAB_0048a1ce;
      }
      puStack_7e84 = (undefined *)0xf;
      puStack_7e88 = local_48d4;
      iVar1 = param_1 + 0x7864;
      iStack_7e8c = iVar1;
      uVar4 = EncodeChecksumDeltaAdd();
      puStack_7e84 = (undefined *)(param_1 + 0x5a68);
      puStack_7e88 = local_2694;
      iStack_7e8c = param_1 + 0xb30;
      local_4 = 0xc;
      uVar5 = EncodeChecksumPairDiff();
      puStack_7e84 = (undefined *)(param_1 + 0x5844);
      puStack_7e88 = local_4d1c;
      iStack_7e8c = param_1 + 0x90c;
      SUBFIELD(local_4,0,undefined1) = 0xd;
      uVar6 = EncodeChecksumPairSum();
      puStack_7e84 = (undefined *)0x6;
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0xe);
      iStack_7e8c = 0x48a25b;
      puStack_7e88 = (undefined1 *)uVar10;
      iStack_7e8c = PeekPacketChecksumBool();
      uVar10 = uVar3;
      uVar4 = PeekChecksumStateUnderLock(uVar4);
      uVar7 = PeekChecksumStateUnderLock(param_1 + 0x4d90);
      uVar5 = PeekChecksumStateUnderLock(uVar5);
      uVar6 = PeekChecksumStateUnderLock(uVar6);
      SpawnPrimaryShot(*(undefined1 *)(param_1 + 8),local_7e6c,4,1,
                   CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                            *(int *)(param_1 + 0xae2c) != 0),uVar6,uVar5,uVar7,uVar4,uVar10);
      SUBFIELD(uStack_38,0,undefined1) = 0xd;
      ScrubChecksumGuard();
      uStack_38 = CONCAT31(SUBFIELD(uStack_38,1,undefined3),0xc);
      ScrubChecksumGuard();
      uStack_38 = 0xffffffff;
      ScrubChecksumGuard();
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar10 = PeekChecksumStateUnderLock(puVar11);
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\x01') {
LAB_0048a32a:
        uVar4 = 1;
      }
      else {
        cVar2 = PeekPacketChecksumBool();
        uVar4 = 9;
        if (cVar2 == '\x01') goto LAB_0048a32a;
      }
      uVar5 = EncodeChecksumDeltaAdd(iVar1,auStack_4078,10);
      uStack_38 = 0xf;
      uVar6 = EncodeChecksumDeltaAdd(param_1 + 0x4d90,auStack_2280,4);
      SUBFIELD(uStack_38,0,undefined1) = 0x10;
      uVar7 = EncodeChecksumPairDiff(param_1 + 0xb30,&iStack_7e8c,param_1 + 0x5a68);
      SUBFIELD(uStack_38,0,undefined1) = 0x11;
      uVar8 = EncodeChecksumPairSum(param_1 + 0x90c,auStack_488,param_1 + 0x5844);
      uStack_38 = CONCAT31(SUBFIELD(uStack_38,1,undefined3),0x12);
      uVar9 = PeekPacketChecksumBool(uVar10,6);
      uVar10 = uVar3;
      uVar5 = PeekChecksumStateUnderLock(uVar5);
      uVar6 = PeekChecksumStateUnderLock(uVar6);
      uVar7 = PeekChecksumStateUnderLock(uVar7);
      uVar8 = PeekChecksumStateUnderLock(uVar8);
      SpawnPrimaryShot(*(undefined1 *)(param_1 + 8),uVar4,4,1,
                   CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                            *(int *)(param_1 + 0xae2c) != 0),uVar8,uVar7,uVar6,uVar5,uVar10,uVar9);
      SUBFIELD(uStack_6c,0,undefined1) = 0x11;
      ScrubChecksumGuard();
      SUBFIELD(uStack_6c,0,undefined1) = 0x10;
      ScrubChecksumGuard();
      uStack_6c = CONCAT31(SUBFIELD(uStack_6c,1,undefined3),0xf);
      ScrubChecksumGuard();
      uStack_6c = 0xffffffff;
      ScrubChecksumGuard();
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar10 = PeekChecksumStateUnderLock(puVar11);
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\x01') {
LAB_0048a4ae:
        uVar4 = 2;
      }
      else {
        cVar2 = PeekPacketChecksumBool();
        uVar4 = 10;
        if (cVar2 == '\x01') goto LAB_0048a4ae;
      }
      uVar5 = EncodeChecksumDeltaAdd(iVar1,auStack_71e8,10);
      uStack_6c = 0x13;
      uVar6 = EncodeChecksumDeltaSub(param_1 + 0x4d90,auStack_7630,4);
      SUBFIELD(uStack_6c,0,undefined1) = 0x14;
      uVar7 = EncodeChecksumPairDiff(param_1 + 0xb30,auStack_7a78,param_1 + 0x5a68);
      SUBFIELD(uStack_6c,0,undefined1) = 0x15;
      uVar8 = EncodeChecksumPairSum(param_1 + 0x90c,auStack_7c9c,param_1 + 0x5844);
      uStack_6c = CONCAT31(SUBFIELD(uStack_6c,1,undefined3),0x16);
      uVar10 = PeekPacketChecksumBool(uVar10,6);
      uVar5 = PeekChecksumStateUnderLock(uVar5);
      uVar6 = PeekChecksumStateUnderLock(uVar6);
      uVar7 = PeekChecksumStateUnderLock(uVar7);
      uVar8 = PeekChecksumStateUnderLock(uVar8);
      SpawnPrimaryShot(*(undefined1 *)(param_1 + 8),uVar4,4,1,*(int *)(param_1 + 0xae2c) != 0,uVar8,
                   uVar7,uVar6,uVar5,uVar3,uVar10);
      SUBFIELD(local_4,0,undefined1) = 0x15;
      puStack_7e84 = (undefined *)0x48a5b3;
      ScrubChecksumGuard();
      SUBFIELD(local_4,0,undefined1) = 0x14;
      puStack_7e84 = (undefined *)0x48a5c7;
      ScrubChecksumGuard();
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x13);
      puStack_7e84 = (undefined *)0x48a5db;
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      puStack_7e84 = (undefined *)0x48a5ee;
      ScrubChecksumGuard();
      puStack_7e84 = (undefined *)0x48a5fd;
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\0') {
        puStack_7e84 = (undefined *)0x0;
        puStack_7e88 = (undefined1 *)0x48a612;
        AcquireSoundChannel();
      }
      break;
    }
    if (param_3 != 10) break;
    puStack_7e84 = (undefined *)0xffffffff;
    puStack_7e88 = (undefined1 *)0x489cbf;
    QueueOutgoingPacketField();
    if (*(char *)(param_1 + 0x651c) == '\x01') {
      puStack_7e84 = &DAT_00796aa0;
    }
    else {
      puStack_7e84 = &DAT_00794e48;
    }
    puStack_7e88 = (undefined1 *)0x489cd9;
    uVar10 = PeekChecksumStateUnderLock();
    puStack_7e84 = (undefined *)0x489ce8;
    cVar2 = PeekPacketChecksumBool();
    if (cVar2 == '\x01') {
LAB_00489d03:
      local_7e6c = 3;
    }
    else {
      puStack_7e84 = (undefined *)0x489cf7;
      cVar2 = PeekPacketChecksumBool();
      local_7e6c = 0xb;
      if (cVar2 == '\x01') goto LAB_00489d03;
    }
    iVar1 = param_1 + 0x5a68;
    puStack_7e88 = local_19bc;
    iStack_7e8c = param_1 + 0xb30;
    puStack_7e84 = (undefined *)iVar1;
    uVar4 = EncodeChecksumPairDiff();
    puStack_7e84 = (undefined *)(param_1 + 0x5844);
    puStack_7e88 = local_6284;
    iStack_7e8c = param_1 + 0x90c;
    local_4 = 0x17;
    uVar5 = EncodeChecksumPairSum();
    puStack_7e84 = (undefined *)0x6;
    local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x18);
    iStack_7e8c = 0x489d6e;
    puStack_7e88 = (undefined1 *)uVar10;
    iStack_7e8c = PeekPacketChecksumBool();
    uVar10 = uVar3;
    uVar6 = PeekChecksumStateUnderLock(param_1 + 0x7864);
    uVar7 = PeekChecksumStateUnderLock(param_1 + 0x4d90);
    uVar4 = PeekChecksumStateUnderLock(uVar4);
    uVar5 = PeekChecksumStateUnderLock(uVar5);
    SpawnPrimaryShot(*(undefined1 *)(param_1 + 8),local_7e6c,4,1,
                 CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                          *(int *)(param_1 + 0xae2c) != 0),uVar5,uVar4,uVar7,uVar6,uVar10);
    uStack_38 = CONCAT31(SUBFIELD(uStack_38,1,undefined3),0x17);
    ScrubChecksumGuard();
    uStack_38 = 0xffffffff;
    ScrubChecksumGuard();
    if (*(char *)(param_1 + 0x651c) == '\x01') {
      puVar11 = &DAT_00796aa0;
    }
    else {
      puVar11 = &DAT_00794e48;
    }
    uVar10 = PeekChecksumStateUnderLock(puVar11);
    cVar2 = PeekPacketChecksumBool();
    if (cVar2 == '\x01') {
LAB_00489e2b:
      uVar4 = 4;
    }
    else {
      cVar2 = PeekPacketChecksumBool();
      uVar4 = 0xc;
      if (cVar2 == '\x01') goto LAB_00489e2b;
    }
    uVar5 = EncodeChecksumDeltaAdd(param_1 + 0x7864,auStack_d18,5);
    uStack_38 = 0x19;
    uVar6 = EncodeChecksumDeltaAdd(param_1 + 0x4d90,auStack_5a28,2);
    SUBFIELD(uStack_38,0,undefined1) = 0x1a;
    uVar7 = EncodeChecksumPairDiff(param_1 + 0xb30,auStack_2f58,iVar1);
    SUBFIELD(uStack_38,0,undefined1) = 0x1b;
    uVar8 = EncodeChecksumPairSum(param_1 + 0x90c,auStack_5e70,param_1 + 0x5844);
    uStack_38 = CONCAT31(SUBFIELD(uStack_38,1,undefined3),0x1c);
    uVar9 = PeekPacketChecksumBool(uVar10,6);
    uVar10 = uVar3;
    uVar5 = PeekChecksumStateUnderLock(uVar5);
    uVar6 = PeekChecksumStateUnderLock(uVar6);
    uVar7 = PeekChecksumStateUnderLock(uVar7);
    uVar8 = PeekChecksumStateUnderLock(uVar8);
    SpawnPrimaryShot(*(undefined1 *)(param_1 + 8),uVar4,4,1,
                 CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                          *(int *)(param_1 + 0xae2c) != 0),uVar8,uVar7,uVar6,uVar5,uVar10,uVar9);
    SUBFIELD(uStack_6c,0,undefined1) = 0x1b;
    ScrubChecksumGuard();
    SUBFIELD(uStack_6c,0,undefined1) = 0x1a;
    ScrubChecksumGuard();
    uStack_6c = CONCAT31(SUBFIELD(uStack_6c,1,undefined3),0x19);
    ScrubChecksumGuard();
    uStack_6c = 0xffffffff;
    ScrubChecksumGuard();
    if (*(char *)(param_1 + 0x651c) == '\x01') {
      puVar11 = &DAT_00796aa0;
    }
    else {
      puVar11 = &DAT_00794e48;
    }
    uVar10 = PeekChecksumStateUnderLock(puVar11);
    cVar2 = PeekPacketChecksumBool();
    if (cVar2 == '\x01') {
LAB_00489fb5:
      uVar4 = 5;
    }
    else {
      cVar2 = PeekPacketChecksumBool();
      uVar4 = 0xd;
      if (cVar2 == '\x01') goto LAB_00489fb5;
    }
    uVar5 = EncodeChecksumDeltaAdd(param_1 + 0x7864,auStack_15dc,5);
    uStack_6c = 0x1d;
    uVar6 = EncodeChecksumDeltaSub(param_1 + 0x4d90,auStack_51cc,2);
    SUBFIELD(uStack_6c,0,undefined1) = 0x1e;
    uVar7 = EncodeChecksumPairDiff(param_1 + 0xb30,auStack_2b44,iVar1);
    SUBFIELD(uStack_6c,0,undefined1) = 0x1f;
    uVar8 = EncodeChecksumPairSum(param_1 + 0x90c,auStack_5614,param_1 + 0x5844);
    uStack_6c = CONCAT31(SUBFIELD(uStack_6c,1,undefined3),0x20);
    uVar10 = PeekPacketChecksumBool(uVar10,6);
    uVar5 = PeekChecksumStateUnderLock(uVar5);
    uVar6 = PeekChecksumStateUnderLock(uVar6);
    uVar7 = PeekChecksumStateUnderLock(uVar7);
    uVar8 = PeekChecksumStateUnderLock(uVar8);
    SpawnPrimaryShot(*(undefined1 *)(param_1 + 8),uVar4,4,1,*(int *)(param_1 + 0xae2c) != 0,uVar8,uVar7,
                 uVar6,uVar5,uVar3,uVar10);
    SUBFIELD(local_4,0,undefined1) = 0x1f;
    puStack_7e84 = (undefined *)0x48a0ba;
    ScrubChecksumGuard();
    SUBFIELD(local_4,0,undefined1) = 0x1e;
    puStack_7e84 = (undefined *)0x48a0ce;
    ScrubChecksumGuard();
    local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x1d);
    puStack_7e84 = (undefined *)0x48a0e2;
    ScrubChecksumGuard();
    local_4 = 0xffffffff;
    puStack_7e84 = (undefined *)0x48a0f5;
    ScrubChecksumGuard();
    puStack_7e84 = (undefined *)0x48a104;
    cVar2 = PeekPacketChecksumBool();
joined_r0x0048a106:
    if (cVar2 == '\0') {
      puStack_7e84 = (undefined *)0x0;
      puStack_7e88 = (undefined1 *)0x48a115;
      AcquireSoundChannel();
    }
    puStack_7e84 = (undefined *)0x48a123;
    cVar2 = PeekPacketChecksumBool();
    if (cVar2 == '\0') {
      puStack_7e84 = (undefined *)0x48a136;
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\0') {
LAB_0048a13e:
        puStack_7e84 = (undefined *)0x48a143;
        cVar2 = FUN_0043a530();
        if (cVar2 == '\0') {
          puStack_7e84 = &DAT_007949c8;
          puStack_7e88 = (undefined1 *)0x48a151;
          puStack_7e84 = (undefined *)PeekChecksumStateUnderLock();
          puStack_7e88 = (undefined1 *)0x48a161;
          QueueOutgoingPacketField();
        }
        puStack_7e84 = (undefined *)0x1;
        puStack_7e88 = (undefined1 *)0x48a172;
        SetGuardedBool();
      }
    }
    break;
  case 8:
    if (param_3 != 3) break;
    puStack_7e84 = (undefined *)0xffffffff;
    puStack_7e88 = (undefined1 *)0x48a63b;
    QueueOutgoingPacketField();
    puStack_7e84 = (undefined *)0x48a646;
    cVar2 = PeekPacketChecksumBool();
    if (cVar2 == '\x01') {
LAB_0048a661:
      local_7e70 = 0;
    }
    else {
      puStack_7e84 = (undefined *)0x48a655;
      cVar2 = PeekPacketChecksumBool();
      local_7e70 = 8;
      if (cVar2 == '\x01') goto LAB_0048a661;
    }
    puStack_7e84 = (undefined *)(param_1 + 0x5620);
    puStack_7e88 = local_68f0;
    iStack_7e8c = param_1 + 0xb30;
    uVar3 = EncodeChecksumPairDiff();
    puStack_7e84 = (undefined *)(param_1 + 0x53fc);
    puStack_7e88 = local_6d38;
    iStack_7e8c = param_1 + 0x90c;
    local_4 = 0x21;
    uVar10 = EncodeChecksumPairSum();
    SUBFIELD(local_4,0,undefined1) = 0x22;
    puStack_7e84 = (undefined *)(uint)*(ushort *)(param_1 + 0xbfbc);
    puStack_7e88 = (undefined1 *)(param_1 + 0x7864);
    iStack_7e8c = 0x48a6cc;
    puStack_7e88 = (undefined1 *)PeekChecksumStateUnderLock();
    iStack_7e8c = param_1 + 0x4d90;
    iStack_7e8c = PeekChecksumStateUnderLock();
    uVar3 = PeekChecksumStateUnderLock(uVar3);
    uVar10 = PeekChecksumStateUnderLock(uVar10);
    SpawnItemProjectile(*(undefined1 *)(param_1 + 8),local_7e70,uVar10,uVar3);
    local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x21);
    puStack_7e84 = (undefined *)0x48a70c;
    ScrubChecksumGuard();
    local_4 = 0xffffffff;
    puStack_7e84 = (undefined *)0x48a71f;
    ScrubChecksumGuard();
    puStack_7e84 = (undefined *)0x48a72e;
    cVar2 = PeekPacketChecksumBool();
    if (cVar2 == '\0') {
      puStack_7e84 = (undefined *)0x0;
      puStack_7e88 = (undefined1 *)0x48a743;
      AcquireSoundChannel();
    }
    goto LAB_0048a13e;
  case 10:
    switch(param_3) {
    case 3:
      puStack_7e84 = (undefined *)0xffffffff;
      puStack_7e88 = (undefined1 *)0x48a77f;
      QueueOutgoingPacketField();
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puStack_7e84 = &DAT_00796aa0;
      }
      else {
        puStack_7e84 = &DAT_00794e48;
      }
      puStack_7e88 = (undefined1 *)0x48a799;
      uVar10 = PeekChecksumStateUnderLock();
      puStack_7e84 = &DAT_00e9ba40;
      puStack_7e88 = (undefined1 *)0x48a7a7;
      puStack_7e84 = (undefined *)PeekChecksumStateUnderLock();
      puStack_7e88 = local_5c18;
      iStack_7e8c = param_1 + 0x7864;
      uVar4 = EncodeChecksumDeltaAdd();
      puStack_7e84 = (undefined *)(param_1 + 0x5eb0);
      puStack_7e88 = local_6060;
      iStack_7e8c = param_1 + 0xb30;
      local_4 = 0x23;
      uVar5 = EncodeChecksumPairDiff();
      puStack_7e84 = (undefined *)(param_1 + 0x5c8c);
      puStack_7e88 = local_64a8;
      iStack_7e8c = param_1 + 0x90c;
      SUBFIELD(local_4,0,undefined1) = 0x24;
      uVar6 = EncodeChecksumPairSum();
      puStack_7e84 = (undefined *)0x8;
      SUBFIELD(local_4,0,undefined1) = 0x25;
      iStack_7e8c = 0x48a829;
      puStack_7e88 = (undefined1 *)uVar10;
      iStack_7e8c = PeekPacketChecksumBool();
      uVar10 = PeekChecksumStateUnderLock(uVar4);
      uVar4 = PeekChecksumStateUnderLock(param_1 + 0x4d90);
      uVar5 = PeekChecksumStateUnderLock(uVar5);
      uVar6 = PeekChecksumStateUnderLock(uVar6);
      SpawnSuperShot(*(undefined1 *)(param_1 + 8),0,4,
                   CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                            *(int *)(param_1 + 0xae2c) != 0),uVar6,uVar5,uVar4,uVar10,uVar3);
      SUBFIELD(local_4,0,undefined1) = 0x24;
      puStack_7e84 = (undefined *)0x48a884;
      ScrubChecksumGuard();
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x23);
      puStack_7e84 = (undefined *)0x48a898;
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      puStack_7e84 = (undefined *)0x48a8ab;
      ScrubChecksumGuard();
      puStack_7e84 = (undefined *)0x48a8ba;
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\0') {
        puStack_7e84 = (undefined *)0x0;
        puStack_7e88 = (undefined1 *)0x48a8cf;
        AcquireSoundChannel();
      }
      break;
    case 5:
      puStack_7e84 = (undefined *)0xffffffff;
      puStack_7e88 = (undefined1 *)0x48a8ea;
      QueueOutgoingPacketField();
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puStack_7e84 = &DAT_00796aa0;
      }
      else {
        puStack_7e84 = &DAT_00794e48;
      }
      puStack_7e88 = (undefined1 *)0x48a904;
      uVar10 = PeekChecksumStateUnderLock();
      puStack_7e84 = &DAT_00e9ba40;
      puStack_7e88 = (undefined1 *)0x48a912;
      puStack_7e84 = (undefined *)PeekChecksumStateUnderLock();
      puStack_7e88 = local_4f40;
      iStack_7e8c = param_1 + 0x7864;
      uVar4 = EncodeChecksumDeltaSub();
      puStack_7e84 = (undefined *)(param_1 + 0x5eb0);
      puStack_7e88 = local_5388;
      iStack_7e8c = param_1 + 0xb30;
      local_4 = 0x26;
      uVar5 = EncodeChecksumPairDiff();
      puStack_7e84 = (undefined *)(param_1 + 0x5c8c);
      puStack_7e88 = local_57d0;
      iStack_7e8c = param_1 + 0x90c;
      SUBFIELD(local_4,0,undefined1) = 0x27;
      uVar6 = EncodeChecksumPairSum();
      puStack_7e84 = (undefined *)0x8;
      SUBFIELD(local_4,0,undefined1) = 0x28;
      iStack_7e8c = 0x48a994;
      puStack_7e88 = (undefined1 *)uVar10;
      iStack_7e8c = PeekPacketChecksumBool();
      uVar10 = PeekChecksumStateUnderLock(uVar4);
      uVar4 = PeekChecksumStateUnderLock(param_1 + 0x4d90);
      uVar5 = PeekChecksumStateUnderLock(uVar5);
      uVar6 = PeekChecksumStateUnderLock(uVar6);
      SpawnSuperShot(*(undefined1 *)(param_1 + 8),1,4,*(int *)(param_1 + 0xae2c) != 0,uVar6,uVar5,
                   uVar4,uVar10,uVar3);
      SUBFIELD(local_4,0,undefined1) = 0x27;
      puStack_7e84 = (undefined *)0x48a9ef;
      ScrubChecksumGuard();
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x26);
      puStack_7e84 = (undefined *)0x48aa03;
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      puStack_7e84 = (undefined *)0x48aa16;
      ScrubChecksumGuard();
      puStack_7e84 = (undefined *)0x48aa25;
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\0') {
        puStack_7e84 = (undefined *)0x0;
        puStack_7e88 = (undefined1 *)0x48aa3a;
        AcquireSoundChannel();
      }
      break;
    case 7:
      puStack_7e84 = (undefined *)0xffffffff;
      puStack_7e88 = (undefined1 *)0x48aa55;
      QueueOutgoingPacketField();
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puStack_7e84 = &DAT_00796aa0;
      }
      else {
        puStack_7e84 = &DAT_00794e48;
      }
      puStack_7e88 = (undefined1 *)0x48aa6f;
      uVar10 = PeekChecksumStateUnderLock();
      puStack_7e84 = (undefined *)0x1;
      puStack_7e88 = local_4268;
      iStack_7e8c = param_1 + 0x4d90;
      uVar4 = EncodeChecksumDeltaAdd();
      puStack_7e84 = (undefined *)(param_1 + 0x5eb0);
      puStack_7e88 = local_46b0;
      iStack_7e8c = param_1 + 0xb30;
      local_4 = 0x29;
      uVar5 = EncodeChecksumPairDiff();
      puStack_7e84 = (undefined *)(param_1 + 0x5c8c);
      puStack_7e88 = local_4af8;
      iStack_7e8c = param_1 + 0x90c;
      SUBFIELD(local_4,0,undefined1) = 0x2a;
      uVar6 = EncodeChecksumPairSum();
      puStack_7e84 = (undefined *)0x8;
      SUBFIELD(local_4,0,undefined1) = 0x2b;
      iStack_7e8c = 0x48aaf6;
      puStack_7e88 = (undefined1 *)uVar10;
      iStack_7e8c = PeekPacketChecksumBool();
      uVar10 = PeekChecksumStateUnderLock(param_1 + 0x7864);
      uVar4 = PeekChecksumStateUnderLock(uVar4);
      uVar5 = PeekChecksumStateUnderLock(uVar5);
      uVar6 = PeekChecksumStateUnderLock(uVar6);
      SpawnSuperShot(*(undefined1 *)(param_1 + 8),2,4,*(int *)(param_1 + 0xae2c) != 0,uVar6,uVar5,
                   uVar4,uVar10,uVar3);
      SUBFIELD(local_4,0,undefined1) = 0x2a;
      puStack_7e84 = (undefined *)0x48ab51;
      ScrubChecksumGuard();
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x29);
      puStack_7e84 = (undefined *)0x48ab65;
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      puStack_7e84 = (undefined *)0x48ab78;
      ScrubChecksumGuard();
      puStack_7e84 = (undefined *)0x48ab87;
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\0') {
        puStack_7e84 = (undefined *)0x0;
        puStack_7e88 = (undefined1 *)0x48ab9c;
        AcquireSoundChannel();
      }
      break;
    case 9:
      puStack_7e84 = (undefined *)0xffffffff;
      puStack_7e88 = (undefined1 *)0x48abb7;
      QueueOutgoingPacketField();
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puStack_7e84 = &DAT_00796aa0;
      }
      else {
        puStack_7e84 = &DAT_00794e48;
      }
      puStack_7e88 = (undefined1 *)0x48abd1;
      uVar10 = PeekChecksumStateUnderLock();
      puStack_7e84 = (undefined *)0x1;
      puStack_7e88 = local_3590;
      iStack_7e8c = param_1 + 0x4d90;
      uVar4 = EncodeChecksumDeltaSub();
      puStack_7e84 = (undefined *)(param_1 + 0x5eb0);
      puStack_7e88 = local_39d8;
      iStack_7e8c = param_1 + 0xb30;
      local_4 = 0x2c;
      uVar5 = EncodeChecksumPairDiff();
      puStack_7e84 = (undefined *)(param_1 + 0x5c8c);
      puStack_7e88 = local_3e20;
      iStack_7e8c = param_1 + 0x90c;
      SUBFIELD(local_4,0,undefined1) = 0x2d;
      uVar6 = EncodeChecksumPairSum();
      puStack_7e84 = (undefined *)0x8;
      SUBFIELD(local_4,0,undefined1) = 0x2e;
      iStack_7e8c = 0x48ac58;
      puStack_7e88 = (undefined1 *)uVar10;
      iStack_7e8c = PeekPacketChecksumBool();
      uVar10 = PeekChecksumStateUnderLock(param_1 + 0x7864);
      uVar4 = PeekChecksumStateUnderLock(uVar4);
      uVar5 = PeekChecksumStateUnderLock(uVar5);
      uVar6 = PeekChecksumStateUnderLock(uVar6);
      SpawnSuperShot(*(undefined1 *)(param_1 + 8),3,4,
                   CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                            *(int *)(param_1 + 0xae2c) != 0),uVar6,uVar5,uVar4,uVar10,uVar3);
      SUBFIELD(local_4,0,undefined1) = 0x2d;
      puStack_7e84 = (undefined *)0x48acb3;
      ScrubChecksumGuard();
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x2c);
      puStack_7e84 = (undefined *)0x48acc7;
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      puStack_7e84 = (undefined *)0x48acda;
      ScrubChecksumGuard();
      puStack_7e84 = (undefined *)0x48ace9;
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\0') {
        puStack_7e84 = (undefined *)0x0;
        puStack_7e88 = (undefined1 *)0x48acfe;
        AcquireSoundChannel();
      }
      break;
    case 0xc:
      puStack_7e84 = (undefined *)0xffffffff;
      puStack_7e88 = (undefined1 *)0x48ad19;
      QueueOutgoingPacketField();
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puStack_7e84 = &DAT_00796aa0;
      }
      else {
        puStack_7e84 = &DAT_00794e48;
      }
      puStack_7e88 = (undefined1 *)0x48ad33;
      uVar10 = PeekChecksumStateUnderLock();
      puStack_7e84 = &DAT_00e9ba40;
      puStack_7e88 = (undefined1 *)0x48ad41;
      puStack_7e84 = (undefined *)PeekChecksumStateUnderLock();
      puStack_7e88 = local_28b8;
      iStack_7e8c = param_1 + 0x7864;
      uVar4 = EncodeChecksumDeltaAdd();
      puStack_7e84 = (undefined *)(param_1 + 0x5eb0);
      puStack_7e88 = local_2d00;
      iStack_7e8c = param_1 + 0xb30;
      local_4 = 0x2f;
      uVar5 = EncodeChecksumPairDiff();
      puStack_7e84 = (undefined *)(param_1 + 0x5c8c);
      puStack_7e88 = local_3148;
      iStack_7e8c = param_1 + 0x90c;
      SUBFIELD(local_4,0,undefined1) = 0x30;
      uVar6 = EncodeChecksumPairSum();
      puStack_7e84 = (undefined *)0x8;
      SUBFIELD(local_4,0,undefined1) = 0x31;
      iStack_7e8c = 0x48adc7;
      puStack_7e88 = (undefined1 *)uVar10;
      iStack_7e8c = PeekPacketChecksumBool();
      PeekPacketChecksumBool(uVar3);
      uVar10 = PeekChecksumStateUnderLock(uVar4);
      uVar4 = PeekChecksumStateUnderLock(param_1 + 0x4d90);
      uVar5 = PeekChecksumStateUnderLock(uVar5);
      uVar6 = PeekChecksumStateUnderLock(uVar6);
      SpawnSuperShot(*(undefined1 *)(param_1 + 8),4,4,
                   CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                            *(int *)(param_1 + 0xae2c) != 0),uVar6,uVar5,uVar4,uVar10,uVar3);
      SUBFIELD(local_4,0,undefined1) = 0x30;
      puStack_7e84 = (undefined *)0x48ae2d;
      ScrubChecksumGuard();
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x2f);
      puStack_7e84 = (undefined *)0x48ae41;
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      puStack_7e84 = (undefined *)0x48ae54;
      ScrubChecksumGuard();
      puStack_7e84 = (undefined *)0x48ae63;
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\0') {
        puStack_7e84 = (undefined *)0x0;
        puStack_7e88 = (undefined1 *)0x48ae78;
        AcquireSoundChannel();
      }
      break;
    case 0xf:
      puStack_7e84 = (undefined *)0xffffffff;
      puStack_7e88 = (undefined1 *)0x48ae93;
      QueueOutgoingPacketField();
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puStack_7e84 = &DAT_00796aa0;
      }
      else {
        puStack_7e84 = &DAT_00794e48;
      }
      puStack_7e88 = (undefined1 *)0x48aead;
      uVar10 = PeekChecksumStateUnderLock();
      puStack_7e84 = &DAT_00e9ba40;
      puStack_7e88 = (undefined1 *)0x48aebb;
      puStack_7e84 = (undefined *)PeekChecksumStateUnderLock();
      puStack_7e88 = local_1be0;
      iStack_7e8c = param_1 + 0x7864;
      uVar4 = EncodeChecksumDeltaSub();
      puStack_7e84 = (undefined *)(param_1 + 0x5eb0);
      puStack_7e88 = local_2028;
      iStack_7e8c = param_1 + 0xb30;
      local_4 = 0x32;
      uVar5 = EncodeChecksumPairDiff();
      puStack_7e84 = (undefined *)(param_1 + 0x5c8c);
      puStack_7e88 = local_2470;
      iStack_7e8c = param_1 + 0x90c;
      SUBFIELD(local_4,0,undefined1) = 0x33;
      uVar6 = EncodeChecksumPairSum();
      puStack_7e84 = (undefined *)0x8;
      SUBFIELD(local_4,0,undefined1) = 0x34;
      iStack_7e8c = 0x48af41;
      puStack_7e88 = (undefined1 *)uVar10;
      iStack_7e8c = PeekPacketChecksumBool();
      PeekPacketChecksumBool(uVar3);
      uVar10 = PeekChecksumStateUnderLock(uVar4);
      uVar4 = PeekChecksumStateUnderLock(param_1 + 0x4d90);
      uVar5 = PeekChecksumStateUnderLock(uVar5);
      uVar6 = PeekChecksumStateUnderLock(uVar6);
      SpawnSuperShot(*(undefined1 *)(param_1 + 8),5,4,
                   CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                            *(int *)(param_1 + 0xae2c) != 0),uVar6,uVar5,uVar4,uVar10,uVar3);
      SUBFIELD(local_4,0,undefined1) = 0x33;
      puStack_7e84 = (undefined *)0x48afa7;
      ScrubChecksumGuard();
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x32);
      puStack_7e84 = (undefined *)0x48afbb;
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      puStack_7e84 = (undefined *)0x48afce;
      ScrubChecksumGuard();
      puStack_7e84 = (undefined *)0x48afdd;
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\0') {
        puStack_7e84 = (undefined *)0x0;
        puStack_7e88 = (undefined1 *)0x48aff2;
        AcquireSoundChannel();
      }
      break;
    case 0x11:
      puStack_7e84 = (undefined *)0xffffffff;
      puStack_7e88 = (undefined1 *)0x48b00d;
      QueueOutgoingPacketField();
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puStack_7e84 = &DAT_00796aa0;
      }
      else {
        puStack_7e84 = &DAT_00794e48;
      }
      puStack_7e88 = (undefined1 *)0x48b027;
      uVar10 = PeekChecksumStateUnderLock();
      puStack_7e84 = (undefined *)0x1;
      puStack_7e88 = local_f08;
      iStack_7e8c = param_1 + 0x4d90;
      uVar4 = EncodeChecksumDeltaAdd();
      puStack_7e84 = (undefined *)(param_1 + 0x5eb0);
      puStack_7e88 = local_1350;
      iStack_7e8c = param_1 + 0xb30;
      local_4 = 0x35;
      uVar5 = EncodeChecksumPairDiff();
      puStack_7e84 = (undefined *)(param_1 + 0x5c8c);
      puStack_7e88 = local_1798;
      iStack_7e8c = param_1 + 0x90c;
      SUBFIELD(local_4,0,undefined1) = 0x36;
      uVar6 = EncodeChecksumPairSum();
      puStack_7e84 = (undefined *)0x8;
      SUBFIELD(local_4,0,undefined1) = 0x37;
      iStack_7e8c = 0x48b0ae;
      puStack_7e88 = (undefined1 *)uVar10;
      iStack_7e8c = PeekPacketChecksumBool();
      uVar10 = PeekChecksumStateUnderLock(param_1 + 0x7864);
      uVar4 = PeekChecksumStateUnderLock(uVar4);
      uVar5 = PeekChecksumStateUnderLock(uVar5);
      uVar6 = PeekChecksumStateUnderLock(uVar6);
      SpawnSuperShot(*(undefined1 *)(param_1 + 8),6,4,*(int *)(param_1 + 0xae2c) != 0,uVar6,uVar5,
                   uVar4,uVar10,uVar3);
      SUBFIELD(local_4,0,undefined1) = 0x36;
      puStack_7e84 = (undefined *)0x48b109;
      ScrubChecksumGuard();
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x35);
      puStack_7e84 = (undefined *)0x48b11d;
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      puStack_7e84 = (undefined *)0x48b130;
      ScrubChecksumGuard();
      puStack_7e84 = (undefined *)0x48b13f;
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\0') {
        puStack_7e84 = (undefined *)0x0;
        puStack_7e88 = (undefined1 *)0x48b154;
        AcquireSoundChannel();
      }
      break;
    case 0x13:
      puStack_7e84 = (undefined *)0xffffffff;
      puStack_7e88 = (undefined1 *)0x48b16f;
      QueueOutgoingPacketField();
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puStack_7e84 = &DAT_00796aa0;
      }
      else {
        puStack_7e84 = &DAT_00794e48;
      }
      puStack_7e88 = (undefined1 *)0x48b189;
      uVar10 = PeekChecksumStateUnderLock();
      puStack_7e84 = (undefined *)0x1;
      puStack_7e88 = local_230;
      iStack_7e8c = param_1 + 0x4d90;
      uVar4 = EncodeChecksumDeltaSub();
      puStack_7e84 = (undefined *)(param_1 + 0x5eb0);
      puStack_7e88 = local_678;
      iStack_7e8c = param_1 + 0xb30;
      local_4 = 0x38;
      uVar5 = EncodeChecksumPairDiff();
      puStack_7e84 = (undefined *)(param_1 + 0x5c8c);
      puStack_7e88 = local_ac0;
      iStack_7e8c = param_1 + 0x90c;
      SUBFIELD(local_4,0,undefined1) = 0x39;
      uVar6 = EncodeChecksumPairSum();
      puStack_7e84 = (undefined *)0x8;
      SUBFIELD(local_4,0,undefined1) = 0x3a;
      iStack_7e8c = 0x48b210;
      puStack_7e88 = (undefined1 *)uVar10;
      iStack_7e8c = PeekPacketChecksumBool();
      uVar10 = PeekChecksumStateUnderLock(param_1 + 0x7864);
      uVar4 = PeekChecksumStateUnderLock(uVar4);
      uVar5 = PeekChecksumStateUnderLock(uVar5);
      uVar6 = PeekChecksumStateUnderLock(uVar6);
      SpawnSuperShot(*(undefined1 *)(param_1 + 8),7,4,*(int *)(param_1 + 0xae2c) != 0,uVar6,uVar5,
                   uVar4,uVar10,uVar3);
      SUBFIELD(local_4,0,undefined1) = 0x39;
      puStack_7e84 = (undefined *)0x48b26b;
      ScrubChecksumGuard();
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x38);
      puStack_7e84 = (undefined *)0x48b27f;
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      puStack_7e84 = (undefined *)0x48b292;
      ScrubChecksumGuard();
      puStack_7e84 = (undefined *)0x48b2a1;
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\0') {
        puStack_7e84 = (undefined *)0x0;
        puStack_7e88 = (undefined1 *)0x48b2b2;
        AcquireSoundChannel();
      }
      puStack_7e84 = (undefined *)0x48b2ba;
      cVar2 = FUN_0043a530();
      if (cVar2 == '\0') {
        puStack_7e84 = &DAT_007949c8;
        puStack_7e88 = (undefined1 *)0x48b2c8;
        puStack_7e84 = (undefined *)PeekChecksumStateUnderLock();
        puStack_7e88 = (undefined1 *)0x48b2d8;
        QueueOutgoingPacketField();
        iVar1 = g_clientContext;
        *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
        *(undefined4 *)(&DAT_005f376c + iVar1) = 0;
        puStack_7e84 = (undefined *)0x1;
        puStack_7e88 = (undefined1 *)0x48b2fd;
        SetGuardedBool();
      }
      else {
        puStack_7e84 = (undefined *)0x1;
        puStack_7e88 = (undefined1 *)0x48b310;
        SetGuardedBool();
      }
    }
  }
switchD_0048a765_caseD_4:
  *unaff_FS_OFFSET = local_c;
  return;
}

