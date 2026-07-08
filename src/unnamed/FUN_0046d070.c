/* FUN_0046d070 - 0x0046d070 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void __thiscall FUN_0046d070(int param_1,undefined4 param_2,int param_3)

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
  uint uVar10;
  undefined4 *unaff_FS_OFFSET;
  undefined *puVar11;
  undefined4 uVar12;
  undefined4 local_337c;
  undefined4 local_3378;
  undefined1 local_336c [548];
  undefined1 local_3148 [548];
  undefined1 local_2f24 [548];
  undefined1 local_2d00 [548];
  undefined1 local_2adc [548];
  undefined1 local_28b8 [548];
  undefined1 local_2694 [548];
  undefined1 local_2470 [548];
  undefined1 local_224c [548];
  undefined1 local_2028 [548];
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
  puStack_8 = &LAB_0053fd98;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uStack_10 = 0x46d08f;
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
    if (param_3 != 4) break;
    QueueOutgoingPacketField(0xffffffff);
    if (*(char *)(param_1 + 0x651c) == '\x01') {
      puVar11 = &DAT_00796aa0;
    }
    else {
      puVar11 = &DAT_00794e48;
    }
    uVar4 = FUN_0040a4d0(puVar11);
    cVar2 = FUN_004065a0();
    if (cVar2 == '\x01') {
LAB_0046d169:
      local_337c = 0;
    }
    else {
      cVar2 = FUN_004065a0();
      local_337c = 8;
      if (cVar2 == '\x01') goto LAB_0046d169;
    }
    uVar5 = FUN_0040a4d0(&DAT_00e9ba40);
    uVar5 = FUN_0040a5f0(param_1 + 0x7864,local_ce4,uVar5);
    local_4 = 0;
    uVar6 = FUN_0040aca0(param_1 + 0xb30,local_2f24,param_1 + 0x5620);
    local_4 = 1;
    uVar7 = FUN_0040aba0(param_1 + 0x90c,local_1e04,param_1 + 0x53fc);
    local_4 = 2;
    uVar4 = FUN_004065a0(uVar4,1);
    uVar5 = FUN_0040a4d0(uVar5);
    uVar8 = FUN_0040a4d0(param_1 + 0x4d90);
    uVar6 = FUN_0040a4d0(uVar6);
    uVar7 = FUN_0040a4d0(uVar7);
    FUN_0042bbb0(*(undefined1 *)(param_1 + 8),local_337c,0xd,0,*(int *)(param_1 + 0xae2c) != 0,uVar7
                 ,uVar6,uVar8,uVar5,uVar3,uVar4);
    local_4 = 1;
    FUN_0040a2a0();
    local_4 = 0;
    FUN_0040a2a0();
    local_4 = 0xffffffff;
    FUN_0040a2a0();
    cVar2 = FUN_004065a0();
    goto joined_r0x0046d9da;
  case 6:
    switch(param_3) {
    case 1:
      QueueOutgoingPacketField(0xffffffff);
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar4 = FUN_0040a4d0(puVar11);
      cVar2 = FUN_004065a0();
      if (cVar2 == '\x01') {
LAB_0046d318:
        local_3378 = 0;
      }
      else {
        cVar2 = FUN_004065a0();
        local_3378 = 8;
        if (cVar2 == '\x01') goto LAB_0046d318;
      }
      uVar5 = FUN_0040a4d0(&DAT_00e9ba40);
      uVar5 = FUN_0040a5f0(param_1 + 0x7864,local_454,uVar5);
      local_4 = 3;
      uVar6 = FUN_0040a5f0(param_1 + 0x4d90,local_2694,1);
      local_4 = 4;
      uVar7 = FUN_0040aca0(param_1 + 0xb30,local_1574,param_1 + 0x5a68);
      local_4 = 5;
      uVar8 = FUN_0040aba0(param_1 + 0x90c,local_2adc,param_1 + 0x5844);
      local_4 = 6;
      uVar4 = FUN_004065a0(uVar4,4);
      uVar5 = FUN_0040a4d0(uVar5);
      uVar6 = FUN_0040a4d0(uVar6);
      uVar7 = FUN_0040a4d0(uVar7);
      uVar8 = FUN_0040a4d0(uVar8);
      FUN_0042bbb0(*(undefined1 *)(param_1 + 8),local_3378,0xd,1,
                   CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                            *(int *)(param_1 + 0xae2c) != 0),uVar8,uVar7,uVar6,uVar5,uVar3,uVar4);
      local_4 = 5;
      FUN_0040a2a0();
      local_4 = 4;
      FUN_0040a2a0();
      local_4 = 3;
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      FUN_0040a2a0();
      cVar2 = FUN_004065a0();
      if (cVar2 == '\0') {
        FUN_004ee9b0(0);
      }
    default:
      goto switchD_0046d2bc_caseD_2;
    case 6:
      QueueOutgoingPacketField(0xffffffff);
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar4 = FUN_0040a4d0(puVar11);
      cVar2 = FUN_004065a0();
      if (cVar2 == '\x01') {
LAB_0046d4e6:
        local_3378 = 1;
      }
      else {
        cVar2 = FUN_004065a0();
        local_3378 = 9;
        if (cVar2 == '\x01') goto LAB_0046d4e6;
      }
      uVar5 = FUN_0040a4d0(&DAT_00e9ba40);
      uVar5 = FUN_0040a6e0(param_1 + 0x7864,local_89c,uVar5);
      local_4 = 7;
      uVar6 = FUN_0040a5f0(param_1 + 0x4d90,local_336c,1);
      local_4 = 8;
      uVar7 = FUN_0040aca0(param_1 + 0xb30,local_112c,param_1 + 0x5a68);
      local_4 = 9;
      uVar8 = FUN_0040aba0(param_1 + 0x90c,local_224c,param_1 + 0x5844);
      local_4 = 10;
      uVar4 = FUN_004065a0(uVar4,4);
      uVar5 = FUN_0040a4d0(uVar5);
      uVar6 = FUN_0040a4d0(uVar6);
      uVar7 = FUN_0040a4d0(uVar7);
      uVar8 = FUN_0040a4d0(uVar8);
      FUN_0042bbb0(*(undefined1 *)(param_1 + 8),local_3378,0xd,1,*(int *)(param_1 + 0xae2c) != 0,
                   uVar8,uVar7,uVar6,uVar5,uVar3,uVar4);
      local_4 = 9;
      FUN_0040a2a0();
      local_4 = 8;
      FUN_0040a2a0();
      local_4 = 7;
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      FUN_0040a2a0();
      cVar2 = FUN_004065a0();
      if (cVar2 == '\0') {
        FUN_004ee9b0(0);
      }
      goto switchD_0046d2bc_caseD_2;
    case 0xb:
      QueueOutgoingPacketField(0xffffffff);
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar4 = FUN_0040a4d0(puVar11);
      cVar2 = FUN_004065a0();
      if (cVar2 == '\x01') {
LAB_0046d6ae:
        local_3378 = 2;
      }
      else {
        cVar2 = FUN_004065a0();
        local_3378 = 10;
        if (cVar2 == '\x01') goto LAB_0046d6ae;
      }
      uVar5 = FUN_0040a4d0(&DAT_00e9ba40);
      uVar5 = FUN_0040a5f0(param_1 + 0x7864,local_28b8,uVar5);
      local_4 = 0xb;
      uVar6 = FUN_0040a6e0(param_1 + 0x4d90,local_2d00,1);
      local_4 = 0xc;
      uVar7 = FUN_0040aca0(param_1 + 0xb30,local_3148,param_1 + 0x5a68);
      local_4 = 0xd;
      uVar8 = FUN_0040aba0(param_1 + 0x90c,local_19bc,param_1 + 0x5844);
      local_4 = 0xe;
      uVar4 = FUN_004065a0(uVar4,4);
      uVar5 = FUN_0040a4d0(uVar5);
      uVar6 = FUN_0040a4d0(uVar6);
      uVar7 = FUN_0040a4d0(uVar7);
      uVar8 = FUN_0040a4d0(uVar8);
      FUN_0042bbb0(*(undefined1 *)(param_1 + 8),local_3378,0xd,1,*(int *)(param_1 + 0xae2c) != 0,
                   uVar8,uVar7,uVar6,uVar5,uVar3,uVar4);
      local_4 = 0xd;
      FUN_0040a2a0();
      local_4 = 0xc;
      FUN_0040a2a0();
      local_4 = 0xb;
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      FUN_0040a2a0();
      cVar2 = FUN_004065a0();
      if (cVar2 == '\0') {
        FUN_004ee9b0(0);
      }
      goto switchD_0046d2bc_caseD_2;
    case 0x10:
      QueueOutgoingPacketField(0xffffffff);
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar4 = FUN_0040a4d0(puVar11);
      cVar2 = FUN_004065a0();
      if (cVar2 == '\x01') {
LAB_0046d87c:
        local_3378 = 3;
      }
      else {
        cVar2 = FUN_004065a0();
        local_3378 = 0xb;
        if (cVar2 == '\x01') goto LAB_0046d87c;
      }
      uVar5 = FUN_0040a4d0(&DAT_00e9ba40);
      uVar5 = FUN_0040a6e0(param_1 + 0x7864,local_1798,uVar5);
      local_4 = 0xf;
      uVar6 = FUN_0040a6e0(param_1 + 0x4d90,local_1be0,1);
      local_4 = 0x10;
      uVar7 = FUN_0040aca0(param_1 + 0xb30,local_2028,param_1 + 0x5a68);
      local_4 = 0x11;
      uVar8 = FUN_0040aba0(param_1 + 0x90c,local_2470,param_1 + 0x5844);
      local_4 = 0x12;
      uVar4 = FUN_004065a0(uVar4,4);
      uVar5 = FUN_0040a4d0(uVar5);
      uVar6 = FUN_0040a4d0(uVar6);
      uVar7 = FUN_0040a4d0(uVar7);
      uVar8 = FUN_0040a4d0(uVar8);
      FUN_0042bbb0(*(undefined1 *)(param_1 + 8),local_3378,0xd,1,
                   CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                            *(int *)(param_1 + 0xae2c) != 0),uVar8,uVar7,uVar6,uVar5,uVar3,uVar4);
      local_4 = 0x11;
      FUN_0040a2a0();
      local_4 = 0x10;
      FUN_0040a2a0();
      local_4 = 0xf;
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      FUN_0040a2a0();
      cVar2 = FUN_004065a0();
    }
joined_r0x0046d9da:
    if (cVar2 == '\0') {
      FUN_004ee9b0(0);
    }
    cVar2 = FUN_004065a0();
    if ((cVar2 == '\0') && (cVar2 = FUN_004065a0(), cVar2 == '\0')) {
LAB_0046db83:
      cVar2 = FUN_0043a530();
      if (cVar2 == '\0') {
        uVar3 = FUN_0040a4d0(&DAT_007949c8);
        QueueOutgoingPacketField(uVar3);
      }
      FUN_00406500(1);
    }
    break;
  case 8:
    if (param_3 == 4) {
      QueueOutgoingPacketField(0xffffffff);
      cVar2 = FUN_004065a0();
      if ((cVar2 == '\x01') || (cVar2 = FUN_004065a0(), cVar2 == '\x01')) {
        uVar3 = 0;
      }
      else {
        uVar3 = 8;
      }
      uVar4 = FUN_0040aca0(param_1 + 0xb30,local_230,param_1 + 0x5620);
      local_4 = 0x16;
      uVar5 = FUN_0040aba0(param_1 + 0x90c,local_678,param_1 + 0x53fc);
      local_4 = 0x17;
      uVar10 = (uint)*(ushort *)(param_1 + 0xbfbc);
      uVar6 = FUN_0040a4d0(param_1 + 0x7864);
      uVar7 = FUN_0040a4d0(param_1 + 0x4d90);
      uVar4 = FUN_0040a4d0(uVar4);
      uVar5 = FUN_0040a4d0(uVar5);
      FUN_004317b0(*(undefined1 *)(param_1 + 8),uVar3,uVar5,uVar4,uVar7,uVar6,uVar10);
      local_4 = 0x16;
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      FUN_0040a2a0();
      cVar2 = FUN_004065a0();
      if (cVar2 == '\0') {
        FUN_004ee9b0(0);
      }
      cVar2 = FUN_0043a530();
      if (cVar2 == '\0') {
        uVar3 = FUN_0040a4d0(&DAT_007949c8);
        QueueOutgoingPacketField(uVar3);
        iVar1 = DAT_005b3484;
        *(undefined4 *)(&DAT_005f3768 + DAT_005b3484) = 5;
        *(undefined4 *)(&DAT_005f376c + iVar1) = 0;
        FUN_00406500(1);
      }
      else {
        FUN_00406500(1);
      }
    }
    break;
  case 10:
    if (param_3 != 4) break;
    QueueOutgoingPacketField(0xffffffff);
    if (*(char *)(param_1 + 0x651c) == '\x01') {
      puVar11 = &DAT_00796aa0;
    }
    else {
      puVar11 = &DAT_00794e48;
    }
    uVar4 = FUN_0040a4d0(puVar11);
    uVar5 = FUN_0040a4d0(&DAT_00e9ba40);
    uVar5 = FUN_0040a5f0(param_1 + 0x7864,local_ac0,uVar5);
    local_4 = 0x13;
    uVar6 = FUN_0040aca0(param_1 + 0xb30,local_f08,param_1 + 0x5620);
    local_4 = 0x14;
    uVar7 = FUN_0040aba0(param_1 + 0x90c,local_1350,param_1 + 0x53fc);
    uVar12 = 1;
    local_4 = 0x15;
    uVar8 = FUN_004065a0(uVar4,1);
    uVar5 = FUN_0040a4d0(uVar5);
    uVar9 = FUN_0040a4d0(param_1 + 0x4d90);
    uVar6 = FUN_0040a4d0(uVar6);
    uVar7 = FUN_0040a4d0(uVar7);
    FUN_0042de70(*(undefined1 *)(param_1 + 8),8,0xd,
                 CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                          *(int *)(param_1 + 0xae2c) != 0),uVar7,uVar6,uVar9,uVar5,uVar3,uVar8,uVar4
                 ,uVar12);
    local_4 = 0x14;
    FUN_0040a2a0();
    local_4 = 0x13;
    FUN_0040a2a0();
    local_4 = 0xffffffff;
    FUN_0040a2a0();
    cVar2 = FUN_004065a0();
    if (cVar2 == '\0') {
      FUN_004ee9b0(0);
    }
    goto LAB_0046db83;
  }
switchD_0046d2bc_caseD_2:
  *unaff_FS_OFFSET = local_c;
  return;
}

