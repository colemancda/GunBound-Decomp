/* FUN_00466890 - 0x00466890 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void __thiscall FUN_00466890(int param_1,undefined4 param_2,int param_3)

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
  undefined *puVar11;
  undefined4 uVar12;
  undefined1 local_112c [548];
  undefined1 local_f08 [548];
  undefined1 local_ce4 [548];
  undefined1 local_ac0 [548];
  undefined1 local_89c [548];
  undefined1 local_678 [548];
  undefined1 local_454 [548];
  undefined1 local_230 [544];
  undefined4 uStack_10;
  int local_4;
  
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_005400f8) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. local_4's
   * `._0_1_`/`._1_3_` partial-field accesses are rewritten as plain
   * int operations, same reasoning as FUN_004174c0.c's fix. */
  uStack_10 = 0x4668af;
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
    uVar5 = FUN_0040a4d0(puVar11);
    cVar2 = FUN_004065a0();
    if ((cVar2 == '\x01') || (cVar2 = FUN_004065a0(), cVar2 == '\x01')) {
      uVar6 = 0;
    }
    else {
      uVar6 = 8;
    }
    uVar7 = FUN_0040aca0(param_1 + 0xb30,local_ce4,param_1 + 0x5620);
    local_4 = 0;
    uVar8 = FUN_0040aba0(param_1 + 0x90c,local_454,param_1 + 0x53fc);
    local_4 = 1;
    uVar5 = FUN_004065a0(uVar5,1);
    uVar9 = FUN_0040a4d0(param_1 + 0x7864);
    uVar10 = FUN_0040a4d0(param_1 + 0x4d90);
    uVar7 = FUN_0040a4d0(uVar7);
    uVar8 = FUN_0040a4d0(uVar8);
    FUN_0042bbb0(*(undefined1 *)(param_1 + 8),uVar6,8,0,*(int *)(param_1 + 0xae2c) != 0,uVar8,uVar7,
                 uVar10,uVar9,uVar3,uVar5);
    local_4 = 0;
    FUN_0040a2a0();
    local_4 = 0xffffffff;
    FUN_0040a2a0();
    cVar2 = FUN_004065a0();
    if (cVar2 == '\0') {
      FUN_004ee9b0(0);
    }
    cVar2 = FUN_004065a0();
    if ((cVar2 != '\0') || (cVar2 = FUN_004065a0(), cVar2 != '\0')) break;
    goto LAB_00466d5c;
  case 6:
    if (param_3 != 1) break;
    QueueOutgoingPacketField(0xffffffff);
    if (*(char *)(param_1 + 0x651c) == '\x01') {
      puVar11 = &DAT_00796aa0;
    }
    else {
      puVar11 = &DAT_00794e48;
    }
    uVar5 = FUN_0040a4d0(puVar11);
    cVar2 = FUN_004065a0();
    if ((cVar2 == '\x01') || (cVar2 = FUN_004065a0(), cVar2 == '\x01')) {
      uVar6 = 0;
    }
    else {
      uVar6 = 8;
    }
    uVar7 = FUN_0040aca0(param_1 + 0xb30,local_89c,param_1 + 0x5a68);
    local_4 = 2;
    uVar8 = FUN_0040aba0(param_1 + 0x90c,local_112c,param_1 + 0x5844);
    local_4 = 3;
    uVar5 = FUN_004065a0(uVar5,1);
    uVar9 = FUN_0040a4d0(param_1 + 0x7864);
    uVar10 = FUN_0040a4d0(param_1 + 0x4d90);
    uVar7 = FUN_0040a4d0(uVar7);
    uVar8 = FUN_0040a4d0(uVar8);
    FUN_0042bbb0(*(undefined1 *)(param_1 + 8),uVar6,8,1,*(int *)(param_1 + 0xae2c) != 0,uVar8,uVar7,
                 uVar10,uVar9,uVar3,uVar5);
    local_4 = 2;
    FUN_0040a2a0();
    local_4 = 0xffffffff;
    FUN_0040a2a0();
    cVar2 = FUN_004065a0();
    if (cVar2 == '\0') {
      FUN_004ee9b0(0);
    }
    cVar2 = FUN_004065a0();
    if ((cVar2 != '\0') || (cVar2 = FUN_004065a0(), cVar2 != '\0')) break;
    cVar2 = FUN_0043a530();
    if (cVar2 == '\0') {
      uVar3 = 0x1e;
      goto LAB_00466d70;
    }
    goto LAB_00466d7f;
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
    uVar5 = FUN_0040aca0(param_1 + 0xb30,local_ac0,param_1 + 0x5620);
    local_4 = 4;
    uVar6 = FUN_0040aba0(param_1 + 0x90c,local_f08,param_1 + 0x53fc);
    local_4 = 5;
    uVar4 = (uint)*(ushort *)(param_1 + 0xbfbc);
    uVar7 = FUN_0040a4d0(param_1 + 0x7864);
    uVar8 = FUN_0040a4d0(param_1 + 0x4d90);
    uVar5 = FUN_0040a4d0(uVar5);
    uVar6 = FUN_0040a4d0(uVar6);
    FUN_004317b0(*(undefined1 *)(param_1 + 8),uVar3,uVar6,uVar5,uVar8,uVar7,uVar4);
    local_4 = 4;
    FUN_0040a2a0();
    local_4 = 0xffffffff;
    FUN_0040a2a0();
    cVar2 = FUN_004065a0();
    if (cVar2 == '\0') {
      FUN_004ee9b0(0);
    }
LAB_00466d5c:
    cVar2 = FUN_0043a530();
    if (cVar2 == '\0') {
      uVar3 = FUN_0040a4d0(&DAT_007949c8);
LAB_00466d70:
      QueueOutgoingPacketField(uVar3);
    }
LAB_00466d7f:
    FUN_00406500(1);
    break;
  case 10:
    if (param_3 == 1) {
      QueueOutgoingPacketField(0xffffffff);
      if (*(char *)(param_1 + 0x651c) == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar5 = FUN_0040a4d0(puVar11);
      uVar6 = FUN_0040aca0(param_1 + 0xb30,local_230,param_1 + 0x5eb0);
      local_4 = 6;
      uVar7 = FUN_0040aba0(param_1 + 0x90c,local_678,param_1 + 0x5c8c);
      uVar12 = 1;
      local_4 = 7;
      uVar8 = FUN_004065a0(uVar5,1);
      uVar9 = FUN_0040a4d0(param_1 + 0x7864);
      uVar10 = FUN_0040a4d0(param_1 + 0x4d90);
      uVar6 = FUN_0040a4d0(uVar6);
      uVar7 = FUN_0040a4d0(uVar7);
      FUN_0042de70(*(undefined1 *)(param_1 + 8),8,8,*(int *)(param_1 + 0xae2c) != 0,uVar7,uVar6,
                   uVar10,uVar9,uVar3,uVar8,uVar5,uVar12);
      local_4 = 6;
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
  return;
}

