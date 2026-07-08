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
      uVar3 = FUN_004ee9b0();
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
      uVar3 = FUN_004ee9b0();
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
      uVar10 = FUN_0040a4d0();
      puStack_7e84 = (undefined *)0x489673;
      cVar2 = FUN_004065a0();
      if (cVar2 == '\x01') {
LAB_0048968e:
        local_7e70 = 0;
      }
      else {
        puStack_7e84 = (undefined *)0x489682;
        cVar2 = FUN_004065a0();
        local_7e70 = 8;
        if (cVar2 == '\x01') goto LAB_0048968e;
      }
      puStack_7e84 = &DAT_00e9ba40;
      puStack_7e88 = (undefined1 *)0x4896a0;
      puStack_7e84 = (undefined *)FUN_0040a4d0();
      puStack_7e88 = local_77ec;
      iStack_7e8c = param_1 + 0x7864;
      uVar4 = FUN_0040a5f0();
      puStack_7e84 = (undefined *)(param_1 + 0x5620);
      puStack_7e88 = local_112c;
      iStack_7e8c = param_1 + 0xb30;
      local_4 = 0;
      uVar5 = FUN_0040aca0();
      puStack_7e84 = (undefined *)(param_1 + 0x53fc);
      puStack_7e88 = local_448c;
      iStack_7e8c = param_1 + 0x90c;
      local_4._0_1_ = 1;
      uVar6 = FUN_0040aba0();
      puStack_7e84 = (undefined *)0x4;
      local_4._0_1_ = 2;
      iStack_7e8c = 0x489722;
      puStack_7e88 = (undefined1 *)uVar10;
      iStack_7e8c = FUN_004065a0();
      uVar10 = FUN_0040a4d0(uVar4);
      uVar4 = FUN_0040a4d0(param_1 + 0x4d90);
      uVar5 = FUN_0040a4d0(uVar5);
      uVar6 = FUN_0040a4d0(uVar6);
      FUN_0042bbb0(*(undefined1 *)(param_1 + 8),local_7e70,4,0,*(int *)(param_1 + 0xae2c) != 0,uVar6
                   ,uVar5,uVar4,uVar10,uVar3);
      local_4._0_1_ = 1;
      puStack_7e84 = (undefined *)0x489782;
      FUN_0040a2a0();
      local_4 = (uint)local_4._1_3_ << 8;
      puStack_7e84 = (undefined *)0x489796;
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      puStack_7e84 = (undefined *)0x4897a9;
      FUN_0040a2a0();
      puStack_7e84 = (undefined *)0x4897b8;
      cVar2 = FUN_004065a0();
      if (cVar2 == '\0') {
        puStack_7e84 = (undefined *)0x0;
        puStack_7e88 = (undefined1 *)0x4897cd;
        FUN_004ee9b0();
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
      uVar10 = FUN_0040a4d0();
      puStack_7e84 = (undefined *)0x489811;
      cVar2 = FUN_004065a0();
      if (cVar2 == '\x01') {
LAB_0048982c:
        local_7e6c = 1;
      }
      else {
        puStack_7e84 = (undefined *)0x489820;
        cVar2 = FUN_004065a0();
        local_7e6c = 9;
        if (cVar2 == '\x01') goto LAB_0048982c;
      }
      puStack_7e84 = &DAT_00e9ba40;
      puStack_7e88 = (undefined1 *)0x48983e;
      puStack_7e84 = (undefined *)FUN_0040a4d0();
      puStack_7e88 = local_1e04;
      iStack_7e8c = param_1 + 0x7864;
      uVar4 = FUN_0040a6e0();
      puStack_7e84 = (undefined *)(param_1 + 0x5620);
      puStack_7e88 = local_73a4;
      iStack_7e8c = param_1 + 0xb30;
      local_4 = 3;
      uVar5 = FUN_0040aca0();
      puStack_7e84 = (undefined *)(param_1 + 0x53fc);
      puStack_7e88 = local_3bfc;
      iStack_7e8c = param_1 + 0x90c;
      local_4._0_1_ = 4;
      uVar6 = FUN_0040aba0();
      puStack_7e84 = (undefined *)0x4;
      local_4._0_1_ = 5;
      iStack_7e8c = 0x4898c0;
      puStack_7e88 = (undefined1 *)uVar10;
      iStack_7e8c = FUN_004065a0();
      uVar10 = FUN_0040a4d0(uVar4);
      uVar4 = FUN_0040a4d0(param_1 + 0x4d90);
      uVar5 = FUN_0040a4d0(uVar5);
      uVar6 = FUN_0040a4d0(uVar6);
      FUN_0042bbb0(*(undefined1 *)(param_1 + 8),local_7e6c,4,0,*(int *)(param_1 + 0xae2c) != 0,uVar6
                   ,uVar5,uVar4,uVar10,uVar3);
      local_4._0_1_ = 4;
      puStack_7e84 = (undefined *)0x489920;
      FUN_0040a2a0();
      local_4 = CONCAT31(local_4._1_3_,3);
      puStack_7e84 = (undefined *)0x489934;
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      puStack_7e84 = (undefined *)0x489947;
      FUN_0040a2a0();
      puStack_7e84 = (undefined *)0x489956;
      cVar2 = FUN_004065a0();
      if (cVar2 == '\0') {
        puStack_7e84 = (undefined *)0x0;
        puStack_7e88 = (undefined1 *)0x48996b;
        FUN_004ee9b0();
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
      uVar10 = FUN_0040a4d0();
      puStack_7e84 = (undefined *)0x4899af;
      cVar2 = FUN_004065a0();
      if (cVar2 == '\x01') {
LAB_004899ca:
        local_7e6c = 2;
      }
      else {
        puStack_7e84 = (undefined *)0x4899be;
        cVar2 = FUN_004065a0();
        local_7e6c = 10;
        if (cVar2 == '\x01') goto LAB_004899ca;
      }
      puStack_7e84 = (undefined *)0x1;
      puStack_7e88 = local_6b14;
      iStack_7e8c = param_1 + 0x4d90;
      uVar4 = FUN_0040a5f0();
      puStack_7e84 = (undefined *)(param_1 + 0x5620);
      puStack_7e88 = local_37b4;
      iStack_7e8c = param_1 + 0xb30;
      local_4 = 6;
      uVar5 = FUN_0040aca0();
      puStack_7e84 = (undefined *)(param_1 + 0x53fc);
      puStack_7e88 = local_6f5c;
      iStack_7e8c = param_1 + 0x90c;
      local_4._0_1_ = 7;
      uVar6 = FUN_0040aba0();
      puStack_7e84 = (undefined *)0x4;
      local_4._0_1_ = 8;
      iStack_7e8c = 0x489a55;
      puStack_7e88 = (undefined1 *)uVar10;
      iStack_7e8c = FUN_004065a0();
      uVar10 = FUN_0040a4d0(param_1 + 0x7864);
      uVar4 = FUN_0040a4d0(uVar4);
      uVar5 = FUN_0040a4d0(uVar5);
      uVar6 = FUN_0040a4d0(uVar6);
      FUN_0042bbb0(*(undefined1 *)(param_1 + 8),local_7e6c,4,0,*(int *)(param_1 + 0xae2c) != 0,uVar6
                   ,uVar5,uVar4,uVar10,uVar3);
      local_4._0_1_ = 7;
      puStack_7e84 = (undefined *)0x489ab5;
      FUN_0040a2a0();
      local_4 = CONCAT31(local_4._1_3_,6);
      puStack_7e84 = (undefined *)0x489ac9;
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      puStack_7e84 = (undefined *)0x489adc;
      FUN_0040a2a0();
      puStack_7e84 = (undefined *)0x489aeb;
      cVar2 = FUN_004065a0();
      if (cVar2 == '\0') {
        puStack_7e84 = (undefined *)0x0;
        puStack_7e88 = (undefined1 *)0x489b00;
        FUN_004ee9b0();
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
      uVar10 = FUN_0040a4d0();
      puStack_7e84 = (undefined *)0x489b44;
      cVar2 = FUN_004065a0();
      if (cVar2 == '\x01') {
LAB_00489b5f:
        local_7e6c = 3;
      }
      else {
        puStack_7e84 = (undefined *)0x489b53;
        cVar2 = FUN_004065a0();
        local_7e6c = 0xb;
        if (cVar2 == '\x01') goto LAB_00489b5f;
      }
      puStack_7e84 = (undefined *)0x1;
      puStack_7e88 = local_336c;
      iStack_7e8c = param_1 + 0x4d90;
      uVar4 = FUN_0040a6e0();
      puStack_7e84 = (undefined *)(param_1 + 0x5620);
      puStack_7e88 = local_66cc;
      iStack_7e8c = param_1 + 0xb30;
      local_4 = 9;
      uVar5 = FUN_0040aca0();
      puStack_7e84 = (undefined *)(param_1 + 0x53fc);
      puStack_7e88 = local_89c;
      iStack_7e8c = param_1 + 0x90c;
      local_4._0_1_ = 10;
      uVar6 = FUN_0040aba0();
      puStack_7e84 = (undefined *)0x4;
      local_4._0_1_ = 0xb;
      iStack_7e8c = 0x489bea;
      puStack_7e88 = (undefined1 *)uVar10;
      iStack_7e8c = FUN_004065a0();
      uVar10 = FUN_0040a4d0(param_1 + 0x7864);
      uVar4 = FUN_0040a4d0(uVar4);
      uVar5 = FUN_0040a4d0(uVar5);
      uVar6 = FUN_0040a4d0(uVar6);
      FUN_0042bbb0(*(undefined1 *)(param_1 + 8),local_7e6c,4,0,*(int *)(param_1 + 0xae2c) != 0,uVar6
                   ,uVar5,uVar4,uVar10,uVar3);
      local_4._0_1_ = 10;
      puStack_7e84 = (undefined *)0x489c4a;
      FUN_0040a2a0();
      local_4 = CONCAT31(local_4._1_3_,9);
      puStack_7e84 = (undefined *)0x489c5e;
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      puStack_7e84 = (undefined *)0x489c71;
      FUN_0040a2a0();
      puStack_7e84 = (undefined *)0x489c80;
      cVar2 = FUN_004065a0();
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
      uVar10 = FUN_0040a4d0();
      puStack_7e84 = (undefined *)0x48a1b3;
      cVar2 = FUN_004065a0();
      if (cVar2 == '\x01') {
LAB_0048a1ce:
        local_7e6c = 0;
      }
      else {
        puStack_7e84 = (undefined *)0x48a1c2;
        cVar2 = FUN_004065a0();
        local_7e6c = 8;
        if (cVar2 == '\x01') goto LAB_0048a1ce;
      }
      puStack_7e84 = (undefined *)0xf;
      puStack_7e88 = local_48d4;
      iVar1 = param_1 + 0x7864;
      iStack_7e8c = iVar1;
      uVar4 = FUN_0040a5f0();
      puStack_7e84 = (undefined *)(param_1 + 0x5a68);
      puStack_7e88 = local_2694;
      iStack_7e8c = param_1 + 0xb30;
      local_4 = 0xc;
      uVar5 = FUN_0040aca0();
      puStack_7e84 = (undefined *)(param_1 + 0x5844);
      puStack_7e88 = local_4d1c;
      iStack_7e8c = param_1 + 0x90c;
      local_4._0_1_ = 0xd;
      uVar6 = FUN_0040aba0();
      puStack_7e84 = (undefined *)0x6;
      local_4 = CONCAT31(local_4._1_3_,0xe);
      iStack_7e8c = 0x48a25b;
      puStack_7e88 = (undefined1 *)uVar10;
      iStack_7e8c = FUN_004065a0();
      uVar10 = uVar3;
      uVar4 = FUN_0040a4d0(uVar4);
      uVar7 = FUN_0040a4d0(param_1 + 0x4d90);
      uVar5 = FUN_0040a4d0(uVar5);
      uVar6 = FUN_0040a4d0(uVar6);
      FUN_0042bbb0(*(undefined1 *)(param_1 + 8),local_7e6c,4,1,
                   CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                            *(int *)(param_1 + 0xae2c) != 0),uVar6,uVar5,uVar7,uVar4,uVar10);
      uStack_38._0_1_ = 0xd;
      FUN_0040a2a0();
      uStack_38 = CONCAT31(uStack_38._1_3_,0xc);
      FUN_0040a2a0();
      uStack_38 = 0xffffffff;
      FUN_0040a2a0();
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar10 = FUN_0040a4d0(puVar11);
      cVar2 = FUN_004065a0();
      if (cVar2 == '\x01') {
LAB_0048a32a:
        uVar4 = 1;
      }
      else {
        cVar2 = FUN_004065a0();
        uVar4 = 9;
        if (cVar2 == '\x01') goto LAB_0048a32a;
      }
      uVar5 = FUN_0040a5f0(iVar1,auStack_4078,10);
      uStack_38 = 0xf;
      uVar6 = FUN_0040a5f0(param_1 + 0x4d90,auStack_2280,4);
      uStack_38._0_1_ = 0x10;
      uVar7 = FUN_0040aca0(param_1 + 0xb30,&iStack_7e8c,param_1 + 0x5a68);
      uStack_38._0_1_ = 0x11;
      uVar8 = FUN_0040aba0(param_1 + 0x90c,auStack_488,param_1 + 0x5844);
      uStack_38 = CONCAT31(uStack_38._1_3_,0x12);
      uVar9 = FUN_004065a0(uVar10,6);
      uVar10 = uVar3;
      uVar5 = FUN_0040a4d0(uVar5);
      uVar6 = FUN_0040a4d0(uVar6);
      uVar7 = FUN_0040a4d0(uVar7);
      uVar8 = FUN_0040a4d0(uVar8);
      FUN_0042bbb0(*(undefined1 *)(param_1 + 8),uVar4,4,1,
                   CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                            *(int *)(param_1 + 0xae2c) != 0),uVar8,uVar7,uVar6,uVar5,uVar10,uVar9);
      uStack_6c._0_1_ = 0x11;
      FUN_0040a2a0();
      uStack_6c._0_1_ = 0x10;
      FUN_0040a2a0();
      uStack_6c = CONCAT31(uStack_6c._1_3_,0xf);
      FUN_0040a2a0();
      uStack_6c = 0xffffffff;
      FUN_0040a2a0();
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar10 = FUN_0040a4d0(puVar11);
      cVar2 = FUN_004065a0();
      if (cVar2 == '\x01') {
LAB_0048a4ae:
        uVar4 = 2;
      }
      else {
        cVar2 = FUN_004065a0();
        uVar4 = 10;
        if (cVar2 == '\x01') goto LAB_0048a4ae;
      }
      uVar5 = FUN_0040a5f0(iVar1,auStack_71e8,10);
      uStack_6c = 0x13;
      uVar6 = FUN_0040a6e0(param_1 + 0x4d90,auStack_7630,4);
      uStack_6c._0_1_ = 0x14;
      uVar7 = FUN_0040aca0(param_1 + 0xb30,auStack_7a78,param_1 + 0x5a68);
      uStack_6c._0_1_ = 0x15;
      uVar8 = FUN_0040aba0(param_1 + 0x90c,auStack_7c9c,param_1 + 0x5844);
      uStack_6c = CONCAT31(uStack_6c._1_3_,0x16);
      uVar10 = FUN_004065a0(uVar10,6);
      uVar5 = FUN_0040a4d0(uVar5);
      uVar6 = FUN_0040a4d0(uVar6);
      uVar7 = FUN_0040a4d0(uVar7);
      uVar8 = FUN_0040a4d0(uVar8);
      FUN_0042bbb0(*(undefined1 *)(param_1 + 8),uVar4,4,1,*(int *)(param_1 + 0xae2c) != 0,uVar8,
                   uVar7,uVar6,uVar5,uVar3,uVar10);
      local_4._0_1_ = 0x15;
      puStack_7e84 = (undefined *)0x48a5b3;
      FUN_0040a2a0();
      local_4._0_1_ = 0x14;
      puStack_7e84 = (undefined *)0x48a5c7;
      FUN_0040a2a0();
      local_4 = CONCAT31(local_4._1_3_,0x13);
      puStack_7e84 = (undefined *)0x48a5db;
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      puStack_7e84 = (undefined *)0x48a5ee;
      FUN_0040a2a0();
      puStack_7e84 = (undefined *)0x48a5fd;
      cVar2 = FUN_004065a0();
      if (cVar2 == '\0') {
        puStack_7e84 = (undefined *)0x0;
        puStack_7e88 = (undefined1 *)0x48a612;
        FUN_004ee9b0();
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
    uVar10 = FUN_0040a4d0();
    puStack_7e84 = (undefined *)0x489ce8;
    cVar2 = FUN_004065a0();
    if (cVar2 == '\x01') {
LAB_00489d03:
      local_7e6c = 3;
    }
    else {
      puStack_7e84 = (undefined *)0x489cf7;
      cVar2 = FUN_004065a0();
      local_7e6c = 0xb;
      if (cVar2 == '\x01') goto LAB_00489d03;
    }
    iVar1 = param_1 + 0x5a68;
    puStack_7e88 = local_19bc;
    iStack_7e8c = param_1 + 0xb30;
    puStack_7e84 = (undefined *)iVar1;
    uVar4 = FUN_0040aca0();
    puStack_7e84 = (undefined *)(param_1 + 0x5844);
    puStack_7e88 = local_6284;
    iStack_7e8c = param_1 + 0x90c;
    local_4 = 0x17;
    uVar5 = FUN_0040aba0();
    puStack_7e84 = (undefined *)0x6;
    local_4 = CONCAT31(local_4._1_3_,0x18);
    iStack_7e8c = 0x489d6e;
    puStack_7e88 = (undefined1 *)uVar10;
    iStack_7e8c = FUN_004065a0();
    uVar10 = uVar3;
    uVar6 = FUN_0040a4d0(param_1 + 0x7864);
    uVar7 = FUN_0040a4d0(param_1 + 0x4d90);
    uVar4 = FUN_0040a4d0(uVar4);
    uVar5 = FUN_0040a4d0(uVar5);
    FUN_0042bbb0(*(undefined1 *)(param_1 + 8),local_7e6c,4,1,
                 CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                          *(int *)(param_1 + 0xae2c) != 0),uVar5,uVar4,uVar7,uVar6,uVar10);
    uStack_38 = CONCAT31(uStack_38._1_3_,0x17);
    FUN_0040a2a0();
    uStack_38 = 0xffffffff;
    FUN_0040a2a0();
    if (*(char *)(param_1 + 0x651c) == '\x01') {
      puVar11 = &DAT_00796aa0;
    }
    else {
      puVar11 = &DAT_00794e48;
    }
    uVar10 = FUN_0040a4d0(puVar11);
    cVar2 = FUN_004065a0();
    if (cVar2 == '\x01') {
LAB_00489e2b:
      uVar4 = 4;
    }
    else {
      cVar2 = FUN_004065a0();
      uVar4 = 0xc;
      if (cVar2 == '\x01') goto LAB_00489e2b;
    }
    uVar5 = FUN_0040a5f0(param_1 + 0x7864,auStack_d18,5);
    uStack_38 = 0x19;
    uVar6 = FUN_0040a5f0(param_1 + 0x4d90,auStack_5a28,2);
    uStack_38._0_1_ = 0x1a;
    uVar7 = FUN_0040aca0(param_1 + 0xb30,auStack_2f58,iVar1);
    uStack_38._0_1_ = 0x1b;
    uVar8 = FUN_0040aba0(param_1 + 0x90c,auStack_5e70,param_1 + 0x5844);
    uStack_38 = CONCAT31(uStack_38._1_3_,0x1c);
    uVar9 = FUN_004065a0(uVar10,6);
    uVar10 = uVar3;
    uVar5 = FUN_0040a4d0(uVar5);
    uVar6 = FUN_0040a4d0(uVar6);
    uVar7 = FUN_0040a4d0(uVar7);
    uVar8 = FUN_0040a4d0(uVar8);
    FUN_0042bbb0(*(undefined1 *)(param_1 + 8),uVar4,4,1,
                 CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                          *(int *)(param_1 + 0xae2c) != 0),uVar8,uVar7,uVar6,uVar5,uVar10,uVar9);
    uStack_6c._0_1_ = 0x1b;
    FUN_0040a2a0();
    uStack_6c._0_1_ = 0x1a;
    FUN_0040a2a0();
    uStack_6c = CONCAT31(uStack_6c._1_3_,0x19);
    FUN_0040a2a0();
    uStack_6c = 0xffffffff;
    FUN_0040a2a0();
    if (*(char *)(param_1 + 0x651c) == '\x01') {
      puVar11 = &DAT_00796aa0;
    }
    else {
      puVar11 = &DAT_00794e48;
    }
    uVar10 = FUN_0040a4d0(puVar11);
    cVar2 = FUN_004065a0();
    if (cVar2 == '\x01') {
LAB_00489fb5:
      uVar4 = 5;
    }
    else {
      cVar2 = FUN_004065a0();
      uVar4 = 0xd;
      if (cVar2 == '\x01') goto LAB_00489fb5;
    }
    uVar5 = FUN_0040a5f0(param_1 + 0x7864,auStack_15dc,5);
    uStack_6c = 0x1d;
    uVar6 = FUN_0040a6e0(param_1 + 0x4d90,auStack_51cc,2);
    uStack_6c._0_1_ = 0x1e;
    uVar7 = FUN_0040aca0(param_1 + 0xb30,auStack_2b44,iVar1);
    uStack_6c._0_1_ = 0x1f;
    uVar8 = FUN_0040aba0(param_1 + 0x90c,auStack_5614,param_1 + 0x5844);
    uStack_6c = CONCAT31(uStack_6c._1_3_,0x20);
    uVar10 = FUN_004065a0(uVar10,6);
    uVar5 = FUN_0040a4d0(uVar5);
    uVar6 = FUN_0040a4d0(uVar6);
    uVar7 = FUN_0040a4d0(uVar7);
    uVar8 = FUN_0040a4d0(uVar8);
    FUN_0042bbb0(*(undefined1 *)(param_1 + 8),uVar4,4,1,*(int *)(param_1 + 0xae2c) != 0,uVar8,uVar7,
                 uVar6,uVar5,uVar3,uVar10);
    local_4._0_1_ = 0x1f;
    puStack_7e84 = (undefined *)0x48a0ba;
    FUN_0040a2a0();
    local_4._0_1_ = 0x1e;
    puStack_7e84 = (undefined *)0x48a0ce;
    FUN_0040a2a0();
    local_4 = CONCAT31(local_4._1_3_,0x1d);
    puStack_7e84 = (undefined *)0x48a0e2;
    FUN_0040a2a0();
    local_4 = 0xffffffff;
    puStack_7e84 = (undefined *)0x48a0f5;
    FUN_0040a2a0();
    puStack_7e84 = (undefined *)0x48a104;
    cVar2 = FUN_004065a0();
joined_r0x0048a106:
    if (cVar2 == '\0') {
      puStack_7e84 = (undefined *)0x0;
      puStack_7e88 = (undefined1 *)0x48a115;
      FUN_004ee9b0();
    }
    puStack_7e84 = (undefined *)0x48a123;
    cVar2 = FUN_004065a0();
    if (cVar2 == '\0') {
      puStack_7e84 = (undefined *)0x48a136;
      cVar2 = FUN_004065a0();
      if (cVar2 == '\0') {
LAB_0048a13e:
        puStack_7e84 = (undefined *)0x48a143;
        cVar2 = FUN_0043a530();
        if (cVar2 == '\0') {
          puStack_7e84 = &DAT_007949c8;
          puStack_7e88 = (undefined1 *)0x48a151;
          puStack_7e84 = (undefined *)FUN_0040a4d0();
          puStack_7e88 = (undefined1 *)0x48a161;
          QueueOutgoingPacketField();
        }
        puStack_7e84 = (undefined *)0x1;
        puStack_7e88 = (undefined1 *)0x48a172;
        FUN_00406500();
      }
    }
    break;
  case 8:
    if (param_3 != 3) break;
    puStack_7e84 = (undefined *)0xffffffff;
    puStack_7e88 = (undefined1 *)0x48a63b;
    QueueOutgoingPacketField();
    puStack_7e84 = (undefined *)0x48a646;
    cVar2 = FUN_004065a0();
    if (cVar2 == '\x01') {
LAB_0048a661:
      local_7e70 = 0;
    }
    else {
      puStack_7e84 = (undefined *)0x48a655;
      cVar2 = FUN_004065a0();
      local_7e70 = 8;
      if (cVar2 == '\x01') goto LAB_0048a661;
    }
    puStack_7e84 = (undefined *)(param_1 + 0x5620);
    puStack_7e88 = local_68f0;
    iStack_7e8c = param_1 + 0xb30;
    uVar3 = FUN_0040aca0();
    puStack_7e84 = (undefined *)(param_1 + 0x53fc);
    puStack_7e88 = local_6d38;
    iStack_7e8c = param_1 + 0x90c;
    local_4 = 0x21;
    uVar10 = FUN_0040aba0();
    local_4._0_1_ = 0x22;
    puStack_7e84 = (undefined *)(uint)*(ushort *)(param_1 + 0xbfbc);
    puStack_7e88 = (undefined1 *)(param_1 + 0x7864);
    iStack_7e8c = 0x48a6cc;
    puStack_7e88 = (undefined1 *)FUN_0040a4d0();
    iStack_7e8c = param_1 + 0x4d90;
    iStack_7e8c = FUN_0040a4d0();
    uVar3 = FUN_0040a4d0(uVar3);
    uVar10 = FUN_0040a4d0(uVar10);
    FUN_004317b0(*(undefined1 *)(param_1 + 8),local_7e70,uVar10,uVar3);
    local_4 = CONCAT31(local_4._1_3_,0x21);
    puStack_7e84 = (undefined *)0x48a70c;
    FUN_0040a2a0();
    local_4 = 0xffffffff;
    puStack_7e84 = (undefined *)0x48a71f;
    FUN_0040a2a0();
    puStack_7e84 = (undefined *)0x48a72e;
    cVar2 = FUN_004065a0();
    if (cVar2 == '\0') {
      puStack_7e84 = (undefined *)0x0;
      puStack_7e88 = (undefined1 *)0x48a743;
      FUN_004ee9b0();
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
      uVar10 = FUN_0040a4d0();
      puStack_7e84 = &DAT_00e9ba40;
      puStack_7e88 = (undefined1 *)0x48a7a7;
      puStack_7e84 = (undefined *)FUN_0040a4d0();
      puStack_7e88 = local_5c18;
      iStack_7e8c = param_1 + 0x7864;
      uVar4 = FUN_0040a5f0();
      puStack_7e84 = (undefined *)(param_1 + 0x5eb0);
      puStack_7e88 = local_6060;
      iStack_7e8c = param_1 + 0xb30;
      local_4 = 0x23;
      uVar5 = FUN_0040aca0();
      puStack_7e84 = (undefined *)(param_1 + 0x5c8c);
      puStack_7e88 = local_64a8;
      iStack_7e8c = param_1 + 0x90c;
      local_4._0_1_ = 0x24;
      uVar6 = FUN_0040aba0();
      puStack_7e84 = (undefined *)0x8;
      local_4._0_1_ = 0x25;
      iStack_7e8c = 0x48a829;
      puStack_7e88 = (undefined1 *)uVar10;
      iStack_7e8c = FUN_004065a0();
      uVar10 = FUN_0040a4d0(uVar4);
      uVar4 = FUN_0040a4d0(param_1 + 0x4d90);
      uVar5 = FUN_0040a4d0(uVar5);
      uVar6 = FUN_0040a4d0(uVar6);
      FUN_0042de70(*(undefined1 *)(param_1 + 8),0,4,
                   CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                            *(int *)(param_1 + 0xae2c) != 0),uVar6,uVar5,uVar4,uVar10,uVar3);
      local_4._0_1_ = 0x24;
      puStack_7e84 = (undefined *)0x48a884;
      FUN_0040a2a0();
      local_4 = CONCAT31(local_4._1_3_,0x23);
      puStack_7e84 = (undefined *)0x48a898;
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      puStack_7e84 = (undefined *)0x48a8ab;
      FUN_0040a2a0();
      puStack_7e84 = (undefined *)0x48a8ba;
      cVar2 = FUN_004065a0();
      if (cVar2 == '\0') {
        puStack_7e84 = (undefined *)0x0;
        puStack_7e88 = (undefined1 *)0x48a8cf;
        FUN_004ee9b0();
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
      uVar10 = FUN_0040a4d0();
      puStack_7e84 = &DAT_00e9ba40;
      puStack_7e88 = (undefined1 *)0x48a912;
      puStack_7e84 = (undefined *)FUN_0040a4d0();
      puStack_7e88 = local_4f40;
      iStack_7e8c = param_1 + 0x7864;
      uVar4 = FUN_0040a6e0();
      puStack_7e84 = (undefined *)(param_1 + 0x5eb0);
      puStack_7e88 = local_5388;
      iStack_7e8c = param_1 + 0xb30;
      local_4 = 0x26;
      uVar5 = FUN_0040aca0();
      puStack_7e84 = (undefined *)(param_1 + 0x5c8c);
      puStack_7e88 = local_57d0;
      iStack_7e8c = param_1 + 0x90c;
      local_4._0_1_ = 0x27;
      uVar6 = FUN_0040aba0();
      puStack_7e84 = (undefined *)0x8;
      local_4._0_1_ = 0x28;
      iStack_7e8c = 0x48a994;
      puStack_7e88 = (undefined1 *)uVar10;
      iStack_7e8c = FUN_004065a0();
      uVar10 = FUN_0040a4d0(uVar4);
      uVar4 = FUN_0040a4d0(param_1 + 0x4d90);
      uVar5 = FUN_0040a4d0(uVar5);
      uVar6 = FUN_0040a4d0(uVar6);
      FUN_0042de70(*(undefined1 *)(param_1 + 8),1,4,*(int *)(param_1 + 0xae2c) != 0,uVar6,uVar5,
                   uVar4,uVar10,uVar3);
      local_4._0_1_ = 0x27;
      puStack_7e84 = (undefined *)0x48a9ef;
      FUN_0040a2a0();
      local_4 = CONCAT31(local_4._1_3_,0x26);
      puStack_7e84 = (undefined *)0x48aa03;
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      puStack_7e84 = (undefined *)0x48aa16;
      FUN_0040a2a0();
      puStack_7e84 = (undefined *)0x48aa25;
      cVar2 = FUN_004065a0();
      if (cVar2 == '\0') {
        puStack_7e84 = (undefined *)0x0;
        puStack_7e88 = (undefined1 *)0x48aa3a;
        FUN_004ee9b0();
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
      uVar10 = FUN_0040a4d0();
      puStack_7e84 = (undefined *)0x1;
      puStack_7e88 = local_4268;
      iStack_7e8c = param_1 + 0x4d90;
      uVar4 = FUN_0040a5f0();
      puStack_7e84 = (undefined *)(param_1 + 0x5eb0);
      puStack_7e88 = local_46b0;
      iStack_7e8c = param_1 + 0xb30;
      local_4 = 0x29;
      uVar5 = FUN_0040aca0();
      puStack_7e84 = (undefined *)(param_1 + 0x5c8c);
      puStack_7e88 = local_4af8;
      iStack_7e8c = param_1 + 0x90c;
      local_4._0_1_ = 0x2a;
      uVar6 = FUN_0040aba0();
      puStack_7e84 = (undefined *)0x8;
      local_4._0_1_ = 0x2b;
      iStack_7e8c = 0x48aaf6;
      puStack_7e88 = (undefined1 *)uVar10;
      iStack_7e8c = FUN_004065a0();
      uVar10 = FUN_0040a4d0(param_1 + 0x7864);
      uVar4 = FUN_0040a4d0(uVar4);
      uVar5 = FUN_0040a4d0(uVar5);
      uVar6 = FUN_0040a4d0(uVar6);
      FUN_0042de70(*(undefined1 *)(param_1 + 8),2,4,*(int *)(param_1 + 0xae2c) != 0,uVar6,uVar5,
                   uVar4,uVar10,uVar3);
      local_4._0_1_ = 0x2a;
      puStack_7e84 = (undefined *)0x48ab51;
      FUN_0040a2a0();
      local_4 = CONCAT31(local_4._1_3_,0x29);
      puStack_7e84 = (undefined *)0x48ab65;
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      puStack_7e84 = (undefined *)0x48ab78;
      FUN_0040a2a0();
      puStack_7e84 = (undefined *)0x48ab87;
      cVar2 = FUN_004065a0();
      if (cVar2 == '\0') {
        puStack_7e84 = (undefined *)0x0;
        puStack_7e88 = (undefined1 *)0x48ab9c;
        FUN_004ee9b0();
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
      uVar10 = FUN_0040a4d0();
      puStack_7e84 = (undefined *)0x1;
      puStack_7e88 = local_3590;
      iStack_7e8c = param_1 + 0x4d90;
      uVar4 = FUN_0040a6e0();
      puStack_7e84 = (undefined *)(param_1 + 0x5eb0);
      puStack_7e88 = local_39d8;
      iStack_7e8c = param_1 + 0xb30;
      local_4 = 0x2c;
      uVar5 = FUN_0040aca0();
      puStack_7e84 = (undefined *)(param_1 + 0x5c8c);
      puStack_7e88 = local_3e20;
      iStack_7e8c = param_1 + 0x90c;
      local_4._0_1_ = 0x2d;
      uVar6 = FUN_0040aba0();
      puStack_7e84 = (undefined *)0x8;
      local_4._0_1_ = 0x2e;
      iStack_7e8c = 0x48ac58;
      puStack_7e88 = (undefined1 *)uVar10;
      iStack_7e8c = FUN_004065a0();
      uVar10 = FUN_0040a4d0(param_1 + 0x7864);
      uVar4 = FUN_0040a4d0(uVar4);
      uVar5 = FUN_0040a4d0(uVar5);
      uVar6 = FUN_0040a4d0(uVar6);
      FUN_0042de70(*(undefined1 *)(param_1 + 8),3,4,
                   CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                            *(int *)(param_1 + 0xae2c) != 0),uVar6,uVar5,uVar4,uVar10,uVar3);
      local_4._0_1_ = 0x2d;
      puStack_7e84 = (undefined *)0x48acb3;
      FUN_0040a2a0();
      local_4 = CONCAT31(local_4._1_3_,0x2c);
      puStack_7e84 = (undefined *)0x48acc7;
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      puStack_7e84 = (undefined *)0x48acda;
      FUN_0040a2a0();
      puStack_7e84 = (undefined *)0x48ace9;
      cVar2 = FUN_004065a0();
      if (cVar2 == '\0') {
        puStack_7e84 = (undefined *)0x0;
        puStack_7e88 = (undefined1 *)0x48acfe;
        FUN_004ee9b0();
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
      uVar10 = FUN_0040a4d0();
      puStack_7e84 = &DAT_00e9ba40;
      puStack_7e88 = (undefined1 *)0x48ad41;
      puStack_7e84 = (undefined *)FUN_0040a4d0();
      puStack_7e88 = local_28b8;
      iStack_7e8c = param_1 + 0x7864;
      uVar4 = FUN_0040a5f0();
      puStack_7e84 = (undefined *)(param_1 + 0x5eb0);
      puStack_7e88 = local_2d00;
      iStack_7e8c = param_1 + 0xb30;
      local_4 = 0x2f;
      uVar5 = FUN_0040aca0();
      puStack_7e84 = (undefined *)(param_1 + 0x5c8c);
      puStack_7e88 = local_3148;
      iStack_7e8c = param_1 + 0x90c;
      local_4._0_1_ = 0x30;
      uVar6 = FUN_0040aba0();
      puStack_7e84 = (undefined *)0x8;
      local_4._0_1_ = 0x31;
      iStack_7e8c = 0x48adc7;
      puStack_7e88 = (undefined1 *)uVar10;
      iStack_7e8c = FUN_004065a0();
      FUN_004065a0(uVar3);
      uVar10 = FUN_0040a4d0(uVar4);
      uVar4 = FUN_0040a4d0(param_1 + 0x4d90);
      uVar5 = FUN_0040a4d0(uVar5);
      uVar6 = FUN_0040a4d0(uVar6);
      FUN_0042de70(*(undefined1 *)(param_1 + 8),4,4,
                   CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                            *(int *)(param_1 + 0xae2c) != 0),uVar6,uVar5,uVar4,uVar10,uVar3);
      local_4._0_1_ = 0x30;
      puStack_7e84 = (undefined *)0x48ae2d;
      FUN_0040a2a0();
      local_4 = CONCAT31(local_4._1_3_,0x2f);
      puStack_7e84 = (undefined *)0x48ae41;
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      puStack_7e84 = (undefined *)0x48ae54;
      FUN_0040a2a0();
      puStack_7e84 = (undefined *)0x48ae63;
      cVar2 = FUN_004065a0();
      if (cVar2 == '\0') {
        puStack_7e84 = (undefined *)0x0;
        puStack_7e88 = (undefined1 *)0x48ae78;
        FUN_004ee9b0();
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
      uVar10 = FUN_0040a4d0();
      puStack_7e84 = &DAT_00e9ba40;
      puStack_7e88 = (undefined1 *)0x48aebb;
      puStack_7e84 = (undefined *)FUN_0040a4d0();
      puStack_7e88 = local_1be0;
      iStack_7e8c = param_1 + 0x7864;
      uVar4 = FUN_0040a6e0();
      puStack_7e84 = (undefined *)(param_1 + 0x5eb0);
      puStack_7e88 = local_2028;
      iStack_7e8c = param_1 + 0xb30;
      local_4 = 0x32;
      uVar5 = FUN_0040aca0();
      puStack_7e84 = (undefined *)(param_1 + 0x5c8c);
      puStack_7e88 = local_2470;
      iStack_7e8c = param_1 + 0x90c;
      local_4._0_1_ = 0x33;
      uVar6 = FUN_0040aba0();
      puStack_7e84 = (undefined *)0x8;
      local_4._0_1_ = 0x34;
      iStack_7e8c = 0x48af41;
      puStack_7e88 = (undefined1 *)uVar10;
      iStack_7e8c = FUN_004065a0();
      FUN_004065a0(uVar3);
      uVar10 = FUN_0040a4d0(uVar4);
      uVar4 = FUN_0040a4d0(param_1 + 0x4d90);
      uVar5 = FUN_0040a4d0(uVar5);
      uVar6 = FUN_0040a4d0(uVar6);
      FUN_0042de70(*(undefined1 *)(param_1 + 8),5,4,
                   CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                            *(int *)(param_1 + 0xae2c) != 0),uVar6,uVar5,uVar4,uVar10,uVar3);
      local_4._0_1_ = 0x33;
      puStack_7e84 = (undefined *)0x48afa7;
      FUN_0040a2a0();
      local_4 = CONCAT31(local_4._1_3_,0x32);
      puStack_7e84 = (undefined *)0x48afbb;
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      puStack_7e84 = (undefined *)0x48afce;
      FUN_0040a2a0();
      puStack_7e84 = (undefined *)0x48afdd;
      cVar2 = FUN_004065a0();
      if (cVar2 == '\0') {
        puStack_7e84 = (undefined *)0x0;
        puStack_7e88 = (undefined1 *)0x48aff2;
        FUN_004ee9b0();
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
      uVar10 = FUN_0040a4d0();
      puStack_7e84 = (undefined *)0x1;
      puStack_7e88 = local_f08;
      iStack_7e8c = param_1 + 0x4d90;
      uVar4 = FUN_0040a5f0();
      puStack_7e84 = (undefined *)(param_1 + 0x5eb0);
      puStack_7e88 = local_1350;
      iStack_7e8c = param_1 + 0xb30;
      local_4 = 0x35;
      uVar5 = FUN_0040aca0();
      puStack_7e84 = (undefined *)(param_1 + 0x5c8c);
      puStack_7e88 = local_1798;
      iStack_7e8c = param_1 + 0x90c;
      local_4._0_1_ = 0x36;
      uVar6 = FUN_0040aba0();
      puStack_7e84 = (undefined *)0x8;
      local_4._0_1_ = 0x37;
      iStack_7e8c = 0x48b0ae;
      puStack_7e88 = (undefined1 *)uVar10;
      iStack_7e8c = FUN_004065a0();
      uVar10 = FUN_0040a4d0(param_1 + 0x7864);
      uVar4 = FUN_0040a4d0(uVar4);
      uVar5 = FUN_0040a4d0(uVar5);
      uVar6 = FUN_0040a4d0(uVar6);
      FUN_0042de70(*(undefined1 *)(param_1 + 8),6,4,*(int *)(param_1 + 0xae2c) != 0,uVar6,uVar5,
                   uVar4,uVar10,uVar3);
      local_4._0_1_ = 0x36;
      puStack_7e84 = (undefined *)0x48b109;
      FUN_0040a2a0();
      local_4 = CONCAT31(local_4._1_3_,0x35);
      puStack_7e84 = (undefined *)0x48b11d;
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      puStack_7e84 = (undefined *)0x48b130;
      FUN_0040a2a0();
      puStack_7e84 = (undefined *)0x48b13f;
      cVar2 = FUN_004065a0();
      if (cVar2 == '\0') {
        puStack_7e84 = (undefined *)0x0;
        puStack_7e88 = (undefined1 *)0x48b154;
        FUN_004ee9b0();
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
      uVar10 = FUN_0040a4d0();
      puStack_7e84 = (undefined *)0x1;
      puStack_7e88 = local_230;
      iStack_7e8c = param_1 + 0x4d90;
      uVar4 = FUN_0040a6e0();
      puStack_7e84 = (undefined *)(param_1 + 0x5eb0);
      puStack_7e88 = local_678;
      iStack_7e8c = param_1 + 0xb30;
      local_4 = 0x38;
      uVar5 = FUN_0040aca0();
      puStack_7e84 = (undefined *)(param_1 + 0x5c8c);
      puStack_7e88 = local_ac0;
      iStack_7e8c = param_1 + 0x90c;
      local_4._0_1_ = 0x39;
      uVar6 = FUN_0040aba0();
      puStack_7e84 = (undefined *)0x8;
      local_4._0_1_ = 0x3a;
      iStack_7e8c = 0x48b210;
      puStack_7e88 = (undefined1 *)uVar10;
      iStack_7e8c = FUN_004065a0();
      uVar10 = FUN_0040a4d0(param_1 + 0x7864);
      uVar4 = FUN_0040a4d0(uVar4);
      uVar5 = FUN_0040a4d0(uVar5);
      uVar6 = FUN_0040a4d0(uVar6);
      FUN_0042de70(*(undefined1 *)(param_1 + 8),7,4,*(int *)(param_1 + 0xae2c) != 0,uVar6,uVar5,
                   uVar4,uVar10,uVar3);
      local_4._0_1_ = 0x39;
      puStack_7e84 = (undefined *)0x48b26b;
      FUN_0040a2a0();
      local_4 = CONCAT31(local_4._1_3_,0x38);
      puStack_7e84 = (undefined *)0x48b27f;
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      puStack_7e84 = (undefined *)0x48b292;
      FUN_0040a2a0();
      puStack_7e84 = (undefined *)0x48b2a1;
      cVar2 = FUN_004065a0();
      if (cVar2 == '\0') {
        puStack_7e84 = (undefined *)0x0;
        puStack_7e88 = (undefined1 *)0x48b2b2;
        FUN_004ee9b0();
      }
      puStack_7e84 = (undefined *)0x48b2ba;
      cVar2 = FUN_0043a530();
      if (cVar2 == '\0') {
        puStack_7e84 = &DAT_007949c8;
        puStack_7e88 = (undefined1 *)0x48b2c8;
        puStack_7e84 = (undefined *)FUN_0040a4d0();
        puStack_7e88 = (undefined1 *)0x48b2d8;
        QueueOutgoingPacketField();
        iVar1 = g_clientContext;
        *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
        *(undefined4 *)(&DAT_005f376c + iVar1) = 0;
        puStack_7e84 = (undefined *)0x1;
        puStack_7e88 = (undefined1 *)0x48b2fd;
        FUN_00406500();
      }
      else {
        puStack_7e84 = (undefined *)0x1;
        puStack_7e88 = (undefined1 *)0x48b310;
        FUN_00406500();
      }
    }
  }
switchD_0048a765_caseD_4:
  *unaff_FS_OFFSET = local_c;
  return;
}

