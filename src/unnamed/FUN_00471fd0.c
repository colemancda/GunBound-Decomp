/* FUN_00471fd0 - 0x00471fd0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void __thiscall FUN_00471fd0(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int iVar2;
  char cVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 *unaff_FS_OFFSET;
  undefined8 uVar11;
  undefined *puVar12;
  int iStack_4db8;
  undefined1 *puStack_4db4;
  undefined *puStack_4db0;
  uint uStack_4dac;
  undefined4 uStack_4da8;
  undefined4 uStack_4da4;
  undefined4 uStack_4da0;
  undefined4 uStack_4d9c;
  undefined4 uStack_4d98;
  uint uStack_4d94;
  int iStack_4d90;
  int iStack_4d8c;
  undefined4 uStack_4d88;
  int iStack_4d84;
  undefined1 *puStack_4d80;
  undefined *puStack_4d7c;
  uint uStack_4d78;
  uint uStack_4d74;
  undefined4 uStack_4d70;
  undefined4 uStack_4d6c;
  undefined4 uStack_4d68;
  undefined4 uStack_4d64;
  uint uStack_4d60;
  undefined4 uStack_4d5c;
  int iStack_4d58;
  undefined4 uStack_4d54;
  int iStack_4d50;
  undefined1 *puStack_4d4c;
  undefined *puStack_4d48;
  undefined4 local_4d34;
  undefined4 local_4d30;
  undefined1 local_4af8 [548];
  undefined1 local_48d4 [548];
  undefined1 local_46b0 [548];
  undefined1 local_448c [548];
  undefined1 local_4268 [548];
  undefined1 local_4044 [496];
  undefined1 auStack_3e54 [548];
  undefined1 auStack_3c30 [548];
  undefined1 auStack_3a0c [496];
  undefined1 auStack_381c [548];
  undefined1 auStack_35f8 [548];
  undefined1 auStack_33d4 [548];
  undefined1 auStack_31b0 [496];
  undefined1 auStack_2fc0 [600];
  undefined1 auStack_2d68 [496];
  undefined1 auStack_2b78 [600];
  undefined1 auStack_2920 [652];
  undefined1 local_2694 [392];
  undefined1 auStack_250c [704];
  undefined1 local_224c [392];
  undefined1 auStack_20c4 [652];
  undefined1 auStack_1e38 [444];
  undefined1 auStack_1c7c [600];
  undefined1 auStack_1a24 [496];
  undefined1 auStack_1834 [548];
  undefined1 auStack_1610 [704];
  undefined1 local_1350 [548];
  undefined1 local_112c [548];
  undefined1 local_f08 [548];
  undefined1 local_ce4 [548];
  undefined1 local_ac0 [444];
  undefined1 auStack_904 [652];
  undefined1 local_678 [548];
  undefined1 local_454 [548];
  undefined1 local_230 [400];
  undefined4 uStack_a0;
  undefined4 uStack_6c;
  undefined4 uStack_38;
  undefined4 uStack_10;
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053fb1c;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uStack_10 = 0x471fef;
  puStack_4d48 = (undefined *)0x471ffc;
  uVar4 = FUN_0045f840();
  switch(param_2) {
  case 1:
    if (*(int *)(param_1 + 0xb0a4) == -1) {
      puStack_4d48 = (undefined *)0x1;
      puStack_4d4c = (undefined1 *)0x472030;
      uVar4 = FUN_004ee9b0();
      *(undefined4 *)(param_1 + 0xb0a4) = uVar4;
    }
    break;
  default:
    iVar2 = *(int *)(param_1 + 0xb0a4);
    if (DAT_00793549 != '\0') {
      if (iVar2 != -1) {
        puStack_4d48 = (undefined *)0x473107;
        (**(code **)(**(int **)(DAT_00793554 + iVar2 * 4) + 0xc))();
      }
      if (iVar2 == 0) {
        DAT_00793568 = 0;
      }
    }
    *(undefined4 *)(param_1 + 0xb0a4) = 0xffffffff;
    break;
  case 4:
    if (*(int *)(param_1 + 0xb0a4) == -1) {
      puStack_4d48 = (undefined *)0x1;
      puStack_4d4c = (undefined1 *)0x472058;
      uVar4 = FUN_004ee9b0();
      *(undefined4 *)(param_1 + 0xb0a4) = uVar4;
    }
    break;
  case 5:
    if (param_3 != 2) break;
    puStack_4d48 = (undefined *)0xffffffff;
    puStack_4d4c = (undefined1 *)0x472085;
    QueueOutgoingPacketField();
    if (*(char *)(param_1 + 0x651c) == '\x01') {
      puStack_4d48 = &DAT_00796aa0;
    }
    else {
      puStack_4d48 = &DAT_00794e48;
    }
    puStack_4d4c = (undefined1 *)0x47209f;
    uVar7 = FUN_0040a4d0();
    puStack_4d48 = (undefined *)0x4720ae;
    cVar3 = FUN_004065a0();
    if (cVar3 == '\x01') {
LAB_004720c9:
      local_4d34 = 0;
    }
    else {
      puStack_4d48 = (undefined *)0x4720bd;
      cVar3 = FUN_004065a0();
      local_4d34 = 8;
      if (cVar3 == '\x01') goto LAB_004720c9;
    }
    puStack_4d48 = (undefined *)0x2;
    puStack_4d4c = local_454;
    iStack_4d50 = param_1 + 0x4d90;
    uStack_4d54 = 0x4720e7;
    uVar8 = FUN_0040a5f0();
    puStack_4d48 = (undefined *)(param_1 + 0x5620);
    puStack_4d4c = local_48d4;
    iStack_4d50 = param_1 + 0xb30;
    local_4 = 0;
    uStack_4d54 = 0x47210f;
    uVar9 = FUN_0040aca0();
    puStack_4d48 = (undefined *)(param_1 + 0x53fc);
    puStack_4d4c = local_ce4;
    iStack_4d50 = param_1 + 0x90c;
    SUBFIELD(local_4,0,undefined1) = 1;
    uStack_4d54 = 0x472134;
    uVar10 = FUN_0040aba0();
    puStack_4d48 = (undefined *)0x1;
    SUBFIELD(local_4,0,undefined1) = 2;
    iStack_4d50 = 0x472152;
    puStack_4d4c = (undefined1 *)uVar7;
    iStack_4d50 = FUN_004065a0();
    iStack_4d58 = param_1 + 0x7864;
    uStack_4d5c = 0x472160;
    uStack_4d54 = uVar4;
    iStack_4d58 = FUN_0040a4d0();
    uStack_4d60 = 0x472167;
    uStack_4d5c = uVar8;
    uStack_4d5c = FUN_0040a4d0();
    uStack_4d64 = 0x47216e;
    uStack_4d60 = uVar9;
    uStack_4d60 = FUN_0040a4d0();
    uStack_4d68 = 0x472179;
    uStack_4d64 = uVar10;
    uVar11 = FUN_0040a4d0();
    uStack_4d64 = (undefined4)uVar11;
    uStack_4d68 = CONCAT31((int3)((ulonglong)uVar11 >> 0x28),*(int *)(param_1 + 0xae2c) != 0);
    uStack_4d78 = (uint)*(byte *)(param_1 + 8);
    uStack_4d6c = 0;
    uStack_4d70 = 0xc;
    uStack_4d74 = local_4d34;
    puStack_4d7c = (undefined *)0x47219a;
    FUN_0042bbb0();
    SUBFIELD(local_4,0,undefined1) = 1;
    puStack_4d48 = (undefined *)0x4721ae;
    FUN_0040a2a0();
    local_4 = (uint)SUBFIELD(local_4,1,undefined3) << 8;
    puStack_4d48 = (undefined *)0x4721c2;
    FUN_0040a2a0();
    local_4 = 0xffffffff;
    puStack_4d48 = (undefined *)0x4721d9;
    FUN_0040a2a0();
    puStack_4d48 = (undefined *)0x4721e8;
    cVar3 = FUN_004065a0();
    goto joined_r0x00472d90;
  case 6:
    if (param_3 != 2) break;
    puStack_4d48 = (undefined *)0xffffffff;
    puStack_4d4c = (undefined1 *)0x47221a;
    QueueOutgoingPacketField();
    puStack_4d48 = (undefined *)0x5a;
    iVar2 = param_1 + 0x4d90;
    iStack_4d50 = 0x472228;
    puStack_4d4c = (undefined1 *)iVar2;
    cVar3 = FUN_0040b2d0();
    if (cVar3 == '\0') {
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puStack_4d48 = &DAT_00796aa0;
      }
      else {
        puStack_4d48 = &DAT_00794e48;
      }
      puStack_4d4c = (undefined1 *)0x4727e7;
      uVar7 = FUN_0040a4d0();
      puStack_4d48 = (undefined *)0x4727f6;
      cVar3 = FUN_004065a0();
      if (cVar3 == '\x01') {
LAB_00472811:
        local_4d30 = 0;
      }
      else {
        puStack_4d48 = (undefined *)0x472805;
        cVar3 = FUN_004065a0();
        local_4d30 = 8;
        if (cVar3 == '\x01') goto LAB_00472811;
      }
      puStack_4d48 = (undefined *)0x5;
      puStack_4d4c = local_4268;
      iVar1 = param_1 + 0x7864;
      uStack_4d54 = 0x47282f;
      iStack_4d50 = iVar1;
      uVar8 = FUN_0040a5f0();
      puStack_4d48 = (undefined *)0x1;
      puStack_4d4c = local_46b0;
      local_4 = 0x11;
      uStack_4d54 = 0x47284e;
      iStack_4d50 = iVar2;
      uVar9 = FUN_0040a5f0();
      puStack_4d48 = (undefined *)(param_1 + 0x5a68);
      puStack_4d4c = local_4af8;
      iStack_4d50 = param_1 + 0xb30;
      SUBFIELD(local_4,0,undefined1) = 0x12;
      uStack_4d54 = 0x472875;
      uVar10 = FUN_0040aca0();
      puStack_4d48 = (undefined *)(param_1 + 0x5844);
      puStack_4d4c = local_2694;
      iStack_4d50 = param_1 + 0x90c;
      SUBFIELD(local_4,0,undefined1) = 0x13;
      uStack_4d54 = 0x47289c;
      uVar5 = FUN_0040aba0();
      puStack_4d48 = (undefined *)0x4;
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x14);
      iStack_4d50 = 0x4728ba;
      puStack_4d4c = (undefined1 *)uVar7;
      iStack_4d50 = FUN_004065a0();
      uStack_4d5c = 0x4728c6;
      iStack_4d58 = uVar8;
      uStack_4d54 = uVar4;
      iStack_4d58 = FUN_0040a4d0();
      uStack_4d60 = 0x4728d1;
      uStack_4d5c = uVar9;
      uStack_4d5c = FUN_0040a4d0();
      uStack_4d64 = 0x4728dc;
      uStack_4d60 = uVar10;
      uStack_4d60 = FUN_0040a4d0();
      uStack_4d68 = 0x4728e7;
      uStack_4d64 = uVar5;
      uStack_4d64 = FUN_0040a4d0();
      uStack_4d68 = CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                             *(int *)(param_1 + 0xae2c) != 0);
      uStack_4d78 = (uint)*(byte *)(param_1 + 8);
      uStack_4d6c = 1;
      uStack_4d70 = 0xc;
      uStack_4d74 = local_4d30;
      puStack_4d7c = (undefined *)0x472908;
      FUN_0042bbb0();
      SUBFIELD(uStack_38,0,undefined1) = 0x13;
      puStack_4d7c = (undefined *)0x47291c;
      FUN_0040a2a0();
      SUBFIELD(uStack_38,0,undefined1) = 0x12;
      puStack_4d7c = (undefined *)0x472930;
      FUN_0040a2a0();
      uStack_38 = CONCAT31(SUBFIELD(uStack_38,1,undefined3),0x11);
      puStack_4d7c = (undefined *)0x472944;
      FUN_0040a2a0();
      uStack_38 = 0xffffffff;
      puStack_4d7c = (undefined *)0x47295b;
      FUN_0040a2a0();
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puStack_4d7c = &DAT_00796aa0;
      }
      else {
        puStack_4d7c = &DAT_00794e48;
      }
      puStack_4d80 = (undefined1 *)0x472975;
      uStack_4d68 = FUN_0040a4d0();
      puStack_4d7c = (undefined *)0x472984;
      cVar3 = FUN_004065a0();
      if (cVar3 == '\x01') {
LAB_0047299f:
        uStack_4d64 = 1;
      }
      else {
        puStack_4d7c = (undefined *)0x472993;
        cVar3 = FUN_004065a0();
        uStack_4d64 = 9;
        if (cVar3 == '\x01') goto LAB_0047299f;
      }
      puStack_4d7c = (undefined *)(param_1 + 0x5a68);
      puStack_4d80 = auStack_3a0c;
      iStack_4d84 = param_1 + 0xb30;
      uStack_4d88 = 0x4729c2;
      uStack_4d60 = FUN_0040aca0();
      puStack_4d7c = (undefined *)(param_1 + 0x5844);
      puStack_4d80 = auStack_3e54;
      iStack_4d84 = param_1 + 0x90c;
      uStack_38 = 0x15;
      uStack_4d88 = 0x4729ec;
      uStack_4d5c = FUN_0040aba0();
      puStack_4d7c = (undefined *)0x4;
      puStack_4d80 = (undefined1 *)uStack_4d68;
      uStack_38 = CONCAT31(SUBFIELD(uStack_38,1,undefined3),0x16);
      iStack_4d84 = 0x472a0a;
      iStack_4d84 = FUN_004065a0();
      iStack_4d90 = 0x472a12;
      iStack_4d8c = iVar1;
      uStack_4d88 = uVar4;
      iStack_4d8c = FUN_0040a4d0();
      uStack_4d94 = 0x472a19;
      iStack_4d90 = iVar2;
      iStack_4d90 = FUN_0040a4d0();
      uStack_4d94 = uStack_4d60;
      uStack_4d98 = 0x472a24;
      uStack_4d94 = FUN_0040a4d0();
      uStack_4d98 = uStack_4d5c;
      uStack_4d9c = 0x472a2f;
      uStack_4d98 = FUN_0040a4d0();
      uStack_4d9c = CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                             *(int *)(param_1 + 0xae2c) != 0);
      uStack_4dac = (uint)*(byte *)(param_1 + 8);
      uStack_4da0 = 1;
      uStack_4da4 = 0xc;
      uStack_4da8 = uStack_4d64;
      puStack_4db0 = (undefined *)0x472a50;
      FUN_0042bbb0();
      uStack_6c = CONCAT31(SUBFIELD(uStack_6c,1,undefined3),0x15);
      puStack_4db0 = (undefined *)0x472a64;
      FUN_0040a2a0();
      uStack_6c = 0xffffffff;
      puStack_4db0 = (undefined *)0x472a7b;
      FUN_0040a2a0();
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puStack_4db0 = &DAT_00796aa0;
      }
      else {
        puStack_4db0 = &DAT_00794e48;
      }
      puStack_4db4 = (undefined1 *)0x472a95;
      uStack_4d9c = FUN_0040a4d0();
      puStack_4db0 = (undefined *)0x472aa4;
      cVar3 = FUN_004065a0();
      if (cVar3 == '\x01') {
LAB_00472abf:
        uStack_4d98 = 2;
      }
      else {
        puStack_4db0 = (undefined *)0x472ab3;
        cVar3 = FUN_004065a0();
        uStack_4d98 = 10;
        if (cVar3 == '\x01') goto LAB_00472abf;
      }
      puStack_4db0 = (undefined *)0x5;
      puStack_4db4 = auStack_2920;
      iStack_4db8 = iVar1;
      uStack_4d94 = FUN_0040a6e0();
      puStack_4db0 = (undefined *)0x1;
      puStack_4db4 = auStack_2d68;
      uStack_6c = 0x17;
      iStack_4db8 = iVar2;
      iStack_4d90 = FUN_0040a6e0();
      puStack_4db0 = (undefined *)(param_1 + 0x5a68);
      puStack_4db4 = auStack_31b0;
      iStack_4db8 = param_1 + 0xb30;
      SUBFIELD(uStack_6c,0,undefined1) = 0x18;
      uStack_4d88 = FUN_0040aca0();
      puStack_4db0 = (undefined *)(param_1 + 0x5844);
      puStack_4db4 = auStack_35f8;
      iStack_4db8 = param_1 + 0x90c;
      SUBFIELD(uStack_6c,0,undefined1) = 0x19;
      iStack_4d8c = FUN_0040aba0();
      puStack_4db0 = (undefined *)0x4;
      puStack_4db4 = (undefined1 *)uStack_4d9c;
      uStack_6c = CONCAT31(SUBFIELD(uStack_6c,1,undefined3),0x1a);
      iStack_4db8 = 0x472b62;
      iStack_4db8 = FUN_004065a0();
      uVar7 = uVar4;
      uVar8 = FUN_0040a4d0(uStack_4d94);
      uVar9 = FUN_0040a4d0(iStack_4d90);
      uVar10 = FUN_0040a4d0(uStack_4d88);
      uVar5 = FUN_0040a4d0(iStack_4d8c);
      FUN_0042bbb0(*(undefined1 *)(param_1 + 8),uStack_4d98,0xc,1,
                   CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                            *(int *)(param_1 + 0xae2c) != 0),uVar5,uVar10,uVar9,uVar8,uVar7);
      SUBFIELD(uStack_a0,0,undefined1) = 0x19;
      FUN_0040a2a0();
      SUBFIELD(uStack_a0,0,undefined1) = 0x18;
      FUN_0040a2a0();
      uStack_a0 = CONCAT31(SUBFIELD(uStack_a0,1,undefined3),0x17);
      FUN_0040a2a0();
      uStack_a0 = 0xffffffff;
      FUN_0040a2a0();
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puVar12 = &DAT_00796aa0;
      }
      else {
        puVar12 = &DAT_00794e48;
      }
      uVar7 = FUN_0040a4d0(puVar12);
      cVar3 = FUN_004065a0();
      if (cVar3 == '\x01') {
LAB_00472c47:
        uVar8 = 3;
      }
      else {
        cVar3 = FUN_004065a0();
        uVar8 = 0xb;
        if (cVar3 == '\x01') goto LAB_00472c47;
      }
      uVar9 = FUN_0040a6e0(iVar1,auStack_1834,10);
      uStack_a0 = 0x1b;
      uVar10 = FUN_0040a6e0(iVar2,auStack_1c7c,2);
      SUBFIELD(uStack_a0,0,undefined1) = 0x1c;
      uVar5 = FUN_0040aca0(param_1 + 0xb30,auStack_20c4,param_1 + 0x5a68);
      SUBFIELD(uStack_a0,0,undefined1) = 0x1d;
      uVar6 = FUN_0040aba0(param_1 + 0x90c,auStack_250c,param_1 + 0x5844);
      uStack_a0 = CONCAT31(SUBFIELD(uStack_a0,1,undefined3),0x1e);
      uVar7 = FUN_004065a0(uVar7,4);
      uVar9 = FUN_0040a4d0(uVar9);
      uVar10 = FUN_0040a4d0(uVar10);
      uVar5 = FUN_0040a4d0(uVar5);
      uVar6 = FUN_0040a4d0(uVar6);
      FUN_0042bbb0(*(undefined1 *)(param_1 + 8),uVar8,0xc,1,
                   CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                            *(int *)(param_1 + 0xae2c) != 0),uVar6,uVar5,uVar10,uVar9,uVar4,uVar7);
      SUBFIELD(local_4,0,undefined1) = 0x1d;
      puStack_4d48 = (undefined *)0x472d40;
      FUN_0040a2a0();
      SUBFIELD(local_4,0,undefined1) = 0x1c;
      puStack_4d48 = (undefined *)0x472d54;
      FUN_0040a2a0();
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x1b);
      puStack_4d48 = (undefined *)0x472d68;
      FUN_0040a2a0();
    }
    else {
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puStack_4d48 = &DAT_00796aa0;
      }
      else {
        puStack_4d48 = &DAT_00794e48;
      }
      puStack_4d4c = (undefined1 *)0x47224b;
      uVar7 = FUN_0040a4d0();
      puStack_4d48 = (undefined *)0x47225a;
      cVar3 = FUN_004065a0();
      if (cVar3 == '\x01') {
LAB_00472275:
        local_4d30 = 0;
      }
      else {
        puStack_4d48 = (undefined *)0x472269;
        cVar3 = FUN_004065a0();
        local_4d30 = 8;
        if (cVar3 == '\x01') goto LAB_00472275;
      }
      puStack_4d48 = (undefined *)0x5;
      puStack_4d4c = local_112c;
      iVar1 = param_1 + 0x7864;
      uStack_4d54 = 0x472293;
      iStack_4d50 = iVar1;
      uVar8 = FUN_0040a5f0();
      puStack_4d48 = (undefined *)0x1;
      puStack_4d4c = local_4044;
      local_4 = 3;
      uStack_4d54 = 0x4722b2;
      iStack_4d50 = iVar2;
      uVar9 = FUN_0040a6e0();
      puStack_4d48 = (undefined *)(param_1 + 0x5a68);
      puStack_4d4c = local_224c;
      iStack_4d50 = param_1 + 0xb30;
      SUBFIELD(local_4,0,undefined1) = 4;
      uStack_4d54 = 0x4722d9;
      uVar10 = FUN_0040aca0();
      puStack_4d48 = (undefined *)(param_1 + 0x5844);
      puStack_4d4c = local_448c;
      iStack_4d50 = param_1 + 0x90c;
      SUBFIELD(local_4,0,undefined1) = 5;
      uStack_4d54 = 0x472300;
      uVar5 = FUN_0040aba0();
      puStack_4d48 = (undefined *)0x4;
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),6);
      iStack_4d50 = 0x47231e;
      puStack_4d4c = (undefined1 *)uVar7;
      iStack_4d50 = FUN_004065a0();
      uStack_4d5c = 0x47232a;
      iStack_4d58 = uVar8;
      uStack_4d54 = uVar4;
      iStack_4d58 = FUN_0040a4d0();
      uStack_4d60 = 0x472335;
      uStack_4d5c = uVar9;
      uStack_4d5c = FUN_0040a4d0();
      uStack_4d64 = 0x472340;
      uStack_4d60 = uVar10;
      uStack_4d60 = FUN_0040a4d0();
      uStack_4d68 = 0x47234b;
      uStack_4d64 = uVar5;
      uStack_4d64 = FUN_0040a4d0();
      uStack_4d68 = CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                             *(int *)(param_1 + 0xae2c) != 0);
      uStack_4d78 = (uint)*(byte *)(param_1 + 8);
      uStack_4d6c = 1;
      uStack_4d70 = 0xc;
      uStack_4d74 = local_4d30;
      puStack_4d7c = (undefined *)0x47236c;
      FUN_0042bbb0();
      SUBFIELD(uStack_38,0,undefined1) = 5;
      puStack_4d7c = (undefined *)0x472380;
      FUN_0040a2a0();
      SUBFIELD(uStack_38,0,undefined1) = 4;
      puStack_4d7c = (undefined *)0x472394;
      FUN_0040a2a0();
      uStack_38 = CONCAT31(SUBFIELD(uStack_38,1,undefined3),3);
      puStack_4d7c = (undefined *)0x4723a8;
      FUN_0040a2a0();
      uStack_38 = 0xffffffff;
      puStack_4d7c = (undefined *)0x4723bf;
      FUN_0040a2a0();
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puStack_4d7c = &DAT_00796aa0;
      }
      else {
        puStack_4d7c = &DAT_00794e48;
      }
      puStack_4d80 = (undefined1 *)0x4723d9;
      uStack_4d68 = FUN_0040a4d0();
      puStack_4d7c = (undefined *)0x4723e8;
      cVar3 = FUN_004065a0();
      if (cVar3 == '\x01') {
LAB_00472403:
        uStack_4d64 = 1;
      }
      else {
        puStack_4d7c = (undefined *)0x4723f7;
        cVar3 = FUN_004065a0();
        uStack_4d64 = 9;
        if (cVar3 == '\x01') goto LAB_00472403;
      }
      puStack_4d7c = (undefined *)(param_1 + 0x5a68);
      puStack_4d80 = auStack_1e38;
      iStack_4d84 = param_1 + 0xb30;
      uStack_4d88 = 0x472426;
      uStack_4d60 = FUN_0040aca0();
      puStack_4d7c = (undefined *)(param_1 + 0x5844);
      puStack_4d80 = auStack_3c30;
      iStack_4d84 = param_1 + 0x90c;
      uStack_38 = 7;
      uStack_4d88 = 0x472450;
      uStack_4d5c = FUN_0040aba0();
      puStack_4d7c = (undefined *)0x4;
      puStack_4d80 = (undefined1 *)uStack_4d68;
      uStack_38 = CONCAT31(SUBFIELD(uStack_38,1,undefined3),8);
      iStack_4d84 = 0x47246e;
      iStack_4d84 = FUN_004065a0();
      iStack_4d90 = 0x472476;
      iStack_4d8c = iVar1;
      uStack_4d88 = uVar4;
      iStack_4d8c = FUN_0040a4d0();
      uStack_4d94 = 0x47247d;
      iStack_4d90 = iVar2;
      iStack_4d90 = FUN_0040a4d0();
      uStack_4d94 = uStack_4d60;
      uStack_4d98 = 0x472488;
      uStack_4d94 = FUN_0040a4d0();
      uStack_4d98 = uStack_4d5c;
      uStack_4d9c = 0x472493;
      uStack_4d98 = FUN_0040a4d0();
      uStack_4d9c = CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                             *(int *)(param_1 + 0xae2c) != 0);
      uStack_4dac = (uint)*(byte *)(param_1 + 8);
      uStack_4da0 = 1;
      uStack_4da4 = 0xc;
      uStack_4da8 = uStack_4d64;
      puStack_4db0 = (undefined *)0x4724b4;
      FUN_0042bbb0();
      uStack_6c = CONCAT31(SUBFIELD(uStack_6c,1,undefined3),7);
      puStack_4db0 = (undefined *)0x4724c8;
      FUN_0040a2a0();
      uStack_6c = 0xffffffff;
      puStack_4db0 = (undefined *)0x4724df;
      FUN_0040a2a0();
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puStack_4db0 = &DAT_00796aa0;
      }
      else {
        puStack_4db0 = &DAT_00794e48;
      }
      puStack_4db4 = (undefined1 *)0x4724f9;
      uStack_4d9c = FUN_0040a4d0();
      puStack_4db0 = (undefined *)0x472508;
      cVar3 = FUN_004065a0();
      if (cVar3 == '\x01') {
LAB_00472523:
        uStack_4d98 = 2;
      }
      else {
        puStack_4db0 = (undefined *)0x472517;
        cVar3 = FUN_004065a0();
        uStack_4d98 = 10;
        if (cVar3 == '\x01') goto LAB_00472523;
      }
      puStack_4db0 = (undefined *)0x5;
      puStack_4db4 = auStack_1a24;
      iStack_4db8 = iVar1;
      uStack_4d94 = FUN_0040a6e0();
      puStack_4db0 = (undefined *)0x1;
      puStack_4db4 = auStack_33d4;
      uStack_6c = 9;
      iStack_4db8 = iVar2;
      iStack_4d90 = FUN_0040a5f0();
      puStack_4db0 = (undefined *)(param_1 + 0x5a68);
      puStack_4db4 = auStack_904;
      iStack_4db8 = param_1 + 0xb30;
      SUBFIELD(uStack_6c,0,undefined1) = 10;
      uStack_4d88 = FUN_0040aca0();
      puStack_4db0 = (undefined *)(param_1 + 0x5844);
      puStack_4db4 = auStack_381c;
      iStack_4db8 = param_1 + 0x90c;
      SUBFIELD(uStack_6c,0,undefined1) = 0xb;
      iStack_4d8c = FUN_0040aba0();
      puStack_4db0 = (undefined *)0x4;
      puStack_4db4 = (undefined1 *)uStack_4d9c;
      uStack_6c = CONCAT31(SUBFIELD(uStack_6c,1,undefined3),0xc);
      iStack_4db8 = 0x4725c6;
      iStack_4db8 = FUN_004065a0();
      uVar7 = uVar4;
      uVar8 = FUN_0040a4d0(uStack_4d94);
      uVar9 = FUN_0040a4d0(iStack_4d90);
      uVar10 = FUN_0040a4d0(uStack_4d88);
      uVar5 = FUN_0040a4d0(iStack_4d8c);
      FUN_0042bbb0(*(undefined1 *)(param_1 + 8),uStack_4d98,0xc,1,
                   CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                            *(int *)(param_1 + 0xae2c) != 0),uVar5,uVar10,uVar9,uVar8,uVar7);
      SUBFIELD(uStack_a0,0,undefined1) = 0xb;
      FUN_0040a2a0();
      SUBFIELD(uStack_a0,0,undefined1) = 10;
      FUN_0040a2a0();
      uStack_a0 = CONCAT31(SUBFIELD(uStack_a0,1,undefined3),9);
      FUN_0040a2a0();
      uStack_a0 = 0xffffffff;
      FUN_0040a2a0();
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puVar12 = &DAT_00796aa0;
      }
      else {
        puVar12 = &DAT_00794e48;
      }
      uVar7 = FUN_0040a4d0(puVar12);
      cVar3 = FUN_004065a0();
      if (cVar3 == '\x01') {
LAB_004726ab:
        uVar8 = 3;
      }
      else {
        cVar3 = FUN_004065a0();
        uVar8 = 0xb;
        if (cVar3 == '\x01') goto LAB_004726ab;
      }
      uVar9 = FUN_0040a6e0(iVar1,auStack_1610,10);
      uStack_a0 = 0xd;
      uVar10 = FUN_0040a5f0(iVar2,auStack_2b78,2);
      SUBFIELD(uStack_a0,0,undefined1) = 0xe;
      uVar5 = FUN_0040aca0(param_1 + 0xb30,&iStack_4db8,param_1 + 0x5a68);
      SUBFIELD(uStack_a0,0,undefined1) = 0xf;
      uVar6 = FUN_0040aba0(param_1 + 0x90c,auStack_2fc0,param_1 + 0x5844);
      uStack_a0 = CONCAT31(SUBFIELD(uStack_a0,1,undefined3),0x10);
      uVar7 = FUN_004065a0(uVar7,4);
      uVar9 = FUN_0040a4d0(uVar9);
      uVar10 = FUN_0040a4d0(uVar10);
      uVar5 = FUN_0040a4d0(uVar5);
      uVar6 = FUN_0040a4d0(uVar6);
      FUN_0042bbb0(*(undefined1 *)(param_1 + 8),uVar8,0xc,1,
                   CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                            *(int *)(param_1 + 0xae2c) != 0),uVar6,uVar5,uVar10,uVar9,uVar4,uVar7);
      SUBFIELD(local_4,0,undefined1) = 0xf;
      puStack_4d48 = (undefined *)0x4727a1;
      FUN_0040a2a0();
      SUBFIELD(local_4,0,undefined1) = 0xe;
      puStack_4d48 = (undefined *)0x4727b2;
      FUN_0040a2a0();
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0xd);
      puStack_4d48 = (undefined *)0x4727c6;
      FUN_0040a2a0();
    }
    local_4 = 0xffffffff;
    puStack_4d48 = (undefined *)0x472d7f;
    FUN_0040a2a0();
    puStack_4d48 = (undefined *)0x472d8e;
    cVar3 = FUN_004065a0();
joined_r0x00472d90:
    if (cVar3 == '\0') {
      puStack_4d48 = (undefined *)0x0;
      puStack_4d4c = (undefined1 *)0x472d9f;
      FUN_004ee9b0();
    }
    puStack_4d48 = (undefined *)0x472dad;
    cVar3 = FUN_004065a0();
    if (cVar3 == '\0') {
      puStack_4d48 = (undefined *)0x472dc0;
      cVar3 = FUN_004065a0();
      if (cVar3 == '\0') {
LAB_00472eec:
        puStack_4d48 = (undefined *)0x472ef1;
        cVar3 = FUN_0043a530();
        if (cVar3 == '\0') {
          puStack_4d48 = &DAT_007949c8;
          puStack_4d4c = (undefined1 *)0x472eff;
          puStack_4d48 = (undefined *)FUN_0040a4d0();
          puStack_4d4c = (undefined1 *)0x472f0f;
          QueueOutgoingPacketField();
        }
        puStack_4d48 = (undefined *)0x1;
        puStack_4d4c = (undefined1 *)0x472f20;
        FUN_00406500();
      }
    }
    break;
  case 8:
    if (param_3 != 2) break;
    puStack_4d48 = (undefined *)0xffffffff;
    puStack_4d4c = (undefined1 *)0x472dec;
    QueueOutgoingPacketField();
    puStack_4d48 = (undefined *)0x472df7;
    cVar3 = FUN_004065a0();
    if (cVar3 == '\x01') {
LAB_00472e11:
      uVar4 = 0;
    }
    else {
      puStack_4d48 = (undefined *)0x472e06;
      cVar3 = FUN_004065a0();
      if (cVar3 == '\x01') goto LAB_00472e11;
      uVar4 = 8;
    }
    puStack_4d48 = (undefined *)(param_1 + 0x5620);
    puStack_4d4c = local_f08;
    iStack_4d50 = param_1 + 0xb30;
    uStack_4d54 = 0x472e2e;
    uVar7 = FUN_0040aca0();
    puStack_4d48 = (undefined *)(param_1 + 0x53fc);
    puStack_4d4c = local_1350;
    iStack_4d50 = param_1 + 0x90c;
    local_4 = 0x1f;
    uStack_4d54 = 0x472e56;
    uVar8 = FUN_0040aba0();
    SUBFIELD(local_4,0,undefined1) = 0x20;
    puStack_4d48 = (undefined *)(uint)*(ushort *)(param_1 + 0xbfbc);
    puStack_4d4c = (undefined1 *)(param_1 + 0x7864);
    iStack_4d50 = 0x472e76;
    puStack_4d4c = (undefined1 *)FUN_0040a4d0();
    iStack_4d50 = param_1 + 0x4d90;
    uStack_4d54 = 0x472e83;
    iStack_4d50 = FUN_0040a4d0();
    iStack_4d58 = 0x472e8a;
    uStack_4d54 = uVar7;
    uStack_4d54 = FUN_0040a4d0();
    uStack_4d5c = 0x472e91;
    iStack_4d58 = uVar8;
    iStack_4d58 = FUN_0040a4d0();
    uStack_4d60 = (uint)*(byte *)(param_1 + 8);
    uStack_4d64 = 0x472e9e;
    uStack_4d5c = uVar4;
    FUN_004317b0();
    local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x1f);
    puStack_4d48 = (undefined *)0x472eb2;
    FUN_0040a2a0();
    local_4 = 0xffffffff;
    puStack_4d48 = (undefined *)0x472ec9;
    FUN_0040a2a0();
    puStack_4d48 = (undefined *)0x472ed8;
    cVar3 = FUN_004065a0();
    if (cVar3 == '\0') {
      puStack_4d48 = (undefined *)0x0;
      puStack_4d4c = (undefined1 *)0x472ee9;
      FUN_004ee9b0();
    }
    goto LAB_00472eec;
  case 10:
    if (param_3 == 2) {
      puStack_4d48 = (undefined *)0xffffffff;
      puStack_4d4c = (undefined1 *)0x472f44;
      QueueOutgoingPacketField();
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puStack_4d48 = &DAT_00796aa0;
      }
      else {
        puStack_4d48 = &DAT_00794e48;
      }
      puStack_4d4c = (undefined1 *)0x472f5e;
      uVar7 = FUN_0040a4d0();
      puStack_4d48 = (undefined *)0x2;
      puStack_4d4c = local_230;
      iStack_4d50 = param_1 + 0x4d90;
      uStack_4d54 = 0x472f78;
      uVar8 = FUN_0040a5f0();
      puStack_4d48 = (undefined *)(param_1 + 0x5eb0);
      puStack_4d4c = local_678;
      iStack_4d50 = param_1 + 0xb30;
      local_4 = 0x21;
      uStack_4d54 = 0x472fa0;
      uVar9 = FUN_0040aca0();
      puStack_4d48 = (undefined *)(param_1 + 0x5c8c);
      puStack_4d4c = local_ac0;
      iStack_4d50 = param_1 + 0x90c;
      SUBFIELD(local_4,0,undefined1) = 0x22;
      uStack_4d54 = 0x472fc5;
      uVar10 = FUN_0040aba0();
      puStack_4d48 = (undefined *)0x1;
      SUBFIELD(local_4,0,undefined1) = 0x23;
      iStack_4d50 = 0x472fe3;
      puStack_4d4c = (undefined1 *)uVar7;
      iStack_4d50 = FUN_004065a0();
      iStack_4d58 = param_1 + 0x7864;
      uStack_4d5c = 0x472ff1;
      uStack_4d54 = uVar4;
      iStack_4d58 = FUN_0040a4d0();
      uStack_4d60 = 0x472ff8;
      uStack_4d5c = uVar8;
      uStack_4d5c = FUN_0040a4d0();
      uStack_4d64 = 0x472fff;
      uStack_4d60 = uVar9;
      uStack_4d60 = FUN_0040a4d0();
      uStack_4d68 = 0x47300a;
      uStack_4d64 = uVar10;
      uStack_4d64 = FUN_0040a4d0();
      uStack_4d68 = CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                             *(int *)(param_1 + 0xae2c) != 0);
      uStack_4d74 = (uint)*(byte *)(param_1 + 8);
      uStack_4d6c = 0xc;
      uStack_4d70 = 0;
      uStack_4d78 = 0x473026;
      FUN_0042de70();
      SUBFIELD(local_4,0,undefined1) = 0x22;
      puStack_4d48 = (undefined *)0x47303a;
      FUN_0040a2a0();
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x21);
      puStack_4d48 = (undefined *)0x47304e;
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      puStack_4d48 = (undefined *)0x473065;
      FUN_0040a2a0();
      puStack_4d48 = (undefined *)0x473074;
      cVar3 = FUN_004065a0();
      if (cVar3 == '\0') {
        puStack_4d48 = (undefined *)0x0;
        puStack_4d4c = (undefined1 *)0x473085;
        FUN_004ee9b0();
      }
      puStack_4d48 = (undefined *)0x47308d;
      cVar3 = FUN_0043a530();
      if (cVar3 == '\0') {
        puStack_4d48 = &DAT_007949c8;
        puStack_4d4c = (undefined1 *)0x47309b;
        puStack_4d48 = (undefined *)FUN_0040a4d0();
        puStack_4d4c = (undefined1 *)0x4730ab;
        QueueOutgoingPacketField();
        iVar2 = g_clientContext;
        *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
        *(undefined4 *)(&DAT_005f376c + iVar2) = 0;
        puStack_4d48 = (undefined *)0x1;
        puStack_4d4c = (undefined1 *)0x4730d0;
        FUN_00406500();
      }
      else {
        puStack_4d48 = (undefined *)0x1;
        puStack_4d4c = (undefined1 *)0x4730e3;
        FUN_00406500();
      }
    }
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

