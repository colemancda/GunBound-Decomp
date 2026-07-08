/* FUN_00488ac0 - 0x00488ac0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void __thiscall FUN_00488ac0(int param_1,undefined4 param_2,int param_3)

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
  undefined4 local_1584;
  undefined1 local_1574 [496];
  undefined1 auStack_1384 [600];
  undefined1 local_112c [548];
  undefined1 local_f08 [548];
  undefined1 local_ce4 [548];
  undefined1 local_ac0 [548];
  undefined1 local_89c [548];
  undefined1 local_678 [496];
  undefined1 auStack_488 [600];
  undefined1 local_230 [504];
  undefined4 uStack_38;
  undefined4 uStack_10;
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053e36e;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uStack_10 = 0x488adf;
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
    if (param_3 != 1) break;
    QueueOutgoingPacketField(0xffffffff);
    if (*(char *)(param_1 + 0x651c) == '\x01') {
      puVar11 = &DAT_00796aa0;
    }
    else {
      puVar11 = &DAT_00794e48;
    }
    uVar4 = FUN_0040a4d0(puVar11);
    cVar2 = FUN_004065a0();
    if ((cVar2 == '\x01') || (cVar2 = FUN_004065a0(), cVar2 == '\x01')) {
      uVar5 = 0;
    }
    else {
      uVar5 = 8;
    }
    uVar6 = FUN_0040aca0(param_1 + 0xb30,local_112c,param_1 + 0x5620);
    local_4 = 0;
    uVar7 = FUN_0040aba0(param_1 + 0x90c,local_89c,param_1 + 0x53fc);
    local_4 = 1;
    uVar4 = FUN_004065a0(uVar4,1);
    uVar8 = FUN_0040a4d0(param_1 + 0x7864);
    uVar9 = FUN_0040a4d0(param_1 + 0x4d90);
    uVar6 = FUN_0040a4d0(uVar6);
    uVar7 = FUN_0040a4d0(uVar7);
    FUN_0042bbb0(*(undefined1 *)(param_1 + 8),uVar5,1,0,*(int *)(param_1 + 0xae2c) != 0,uVar7,uVar6,
                 uVar9,uVar8,uVar3,uVar4);
    local_4 = 0;
    FUN_0040a2a0();
    local_4 = 0xffffffff;
    FUN_0040a2a0();
    cVar2 = FUN_004065a0();
    goto joined_r0x00488f1e;
  case 6:
    if (param_3 != 1) break;
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
LAB_00488d15:
      local_1584 = 0;
    }
    else {
      cVar2 = FUN_004065a0();
      local_1584 = 8;
      if (cVar2 == '\x01') goto LAB_00488d15;
    }
    uVar5 = FUN_0040aca0(param_1 + 0xb30,local_ce4,param_1 + 0x5a68);
    local_4 = 2;
    uVar6 = FUN_0040aba0(param_1 + 0x90c,local_1574,param_1 + 0x5844);
    local_4 = 3;
    uVar4 = FUN_004065a0(uVar4,2);
    uVar7 = FUN_0040a4d0(param_1 + 0x7864);
    uVar8 = FUN_0040a4d0(param_1 + 0x4d90);
    uVar5 = FUN_0040a4d0(uVar5);
    uVar6 = FUN_0040a4d0(uVar6);
    FUN_0042bbb0(*(undefined1 *)(param_1 + 8),local_1584,1,1,
                 CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                          *(int *)(param_1 + 0xae2c) != 0),uVar6,uVar5,uVar8,uVar7,uVar3,uVar4);
    uStack_38 = 2;
    FUN_0040a2a0();
    uStack_38 = 0xffffffff;
    FUN_0040a2a0();
    if (*(char *)(param_1 + 0x651c) == '\x01') {
      puVar11 = &DAT_00796aa0;
    }
    else {
      puVar11 = &DAT_00794e48;
    }
    uVar3 = FUN_0040a4d0(puVar11);
    cVar2 = FUN_004065a0();
    if (cVar2 == '\x01') {
LAB_00488e3f:
      uVar4 = 1;
    }
    else {
      cVar2 = FUN_004065a0();
      uVar4 = 9;
      if (cVar2 == '\x01') goto LAB_00488e3f;
    }
    uVar6 = FUN_0040aca0(param_1 + 0xb30,auStack_1384,param_1 + 0x5a68);
    uStack_38 = 4;
    uVar7 = FUN_0040aba0(param_1 + 0x90c,auStack_488,param_1 + 0x5844);
    uStack_38 = 5;
    uVar3 = FUN_004065a0(uVar3,2);
    uVar8 = FUN_0040a4d0(param_1 + 0x7864);
    uVar9 = FUN_0040a4d0(param_1 + 0x4d90);
    uVar6 = FUN_0040a4d0(uVar6);
    uVar7 = FUN_0040a4d0(uVar7);
    FUN_0042bbb0(*(undefined1 *)(param_1 + 8),uVar4,1,1,
                 CONCAT31((int3)((uint)*(int *)(param_1 + 0xae2c) >> 8),
                          *(int *)(param_1 + 0xae2c) != 0),uVar7,uVar6,uVar9,uVar8,uVar5,uVar3);
    local_4 = 4;
    FUN_0040a2a0();
    local_4 = 0xffffffff;
    FUN_0040a2a0();
    cVar2 = FUN_004065a0();
joined_r0x00488f1e:
    if (cVar2 == '\0') {
      FUN_004ee9b0(0);
    }
    cVar2 = FUN_004065a0();
    if ((cVar2 == '\0') && (cVar2 = FUN_004065a0(), cVar2 == '\0')) {
LAB_0048907a:
      cVar2 = FUN_0043a530();
      if (cVar2 == '\0') {
        uVar3 = FUN_0040a4d0(&DAT_007949c8);
        QueueOutgoingPacketField(uVar3);
      }
      FUN_00406500(1);
    }
    break;
  case 8:
    if (param_3 != 1) break;
    QueueOutgoingPacketField(0xffffffff);
    cVar2 = FUN_004065a0();
    if ((cVar2 == '\x01') || (cVar2 = FUN_004065a0(), cVar2 == '\x01')) {
      uVar3 = 0;
    }
    else {
      uVar3 = 8;
    }
    uVar4 = FUN_0040aca0(param_1 + 0xb30,local_ac0,param_1 + 0x5620);
    local_4 = 6;
    uVar5 = FUN_0040aba0(param_1 + 0x90c,local_f08,param_1 + 0x53fc);
    local_4 = 7;
    uVar10 = (uint)*(ushort *)(param_1 + 0xbfbc);
    uVar6 = FUN_0040a4d0(param_1 + 0x7864);
    uVar7 = FUN_0040a4d0(param_1 + 0x4d90);
    uVar4 = FUN_0040a4d0(uVar4);
    uVar5 = FUN_0040a4d0(uVar5);
    FUN_004317b0(*(undefined1 *)(param_1 + 8),uVar3,uVar5,uVar4,uVar7,uVar6,uVar10);
    local_4 = 6;
    FUN_0040a2a0();
    local_4 = 0xffffffff;
    FUN_0040a2a0();
    cVar2 = FUN_004065a0();
    if (cVar2 == '\0') {
      FUN_004ee9b0(0);
    }
    goto LAB_0048907a;
  case 10:
    if (param_3 == 1) {
      QueueOutgoingPacketField(0xffffffff);
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar4 = FUN_0040a4d0(puVar11);
      uVar5 = FUN_0040aca0(param_1 + 0xb30,local_230,param_1 + 0x5eb0);
      local_4 = 8;
      uVar6 = FUN_0040aba0(param_1 + 0x90c,local_678,param_1 + 0x5c8c);
      uVar12 = 1;
      local_4 = 9;
      uVar7 = FUN_004065a0(uVar4,1);
      uVar8 = FUN_0040a4d0(param_1 + 0x7864);
      uVar9 = FUN_0040a4d0(param_1 + 0x4d90);
      uVar5 = FUN_0040a4d0(uVar5);
      uVar6 = FUN_0040a4d0(uVar6);
      FUN_0042de70(*(undefined1 *)(param_1 + 8),0,1,*(int *)(param_1 + 0xae2c) != 0,uVar6,uVar5,
                   uVar9,uVar8,uVar3,uVar7,uVar4,uVar12);
      local_4 = 8;
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
  *unaff_FS_OFFSET = local_c;
  return;
}

