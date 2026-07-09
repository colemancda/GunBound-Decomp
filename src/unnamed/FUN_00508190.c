/* FUN_00508190 - 0x00508190 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00508190(int param_1,undefined4 param_2,undefined4 param_3)

{
  int *piVar1;
  int *piVar2;
  undefined4 *puVar3;
  uint uVar4;
  char cVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 uVar8;
  int iVar9;
  undefined4 *puVar10;
  int iVar11;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053795b;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  puVar6 = *(undefined4 **)(param_1 + 4);
  while (puVar6 != (undefined4 *)0x0) {
    piVar1 = puVar6 + 2;
    puVar6 = (undefined4 *)*puVar6;
    if ((*(int *)(*piVar1 + 0x20) == 0) && (*(int *)(*piVar1 + 0x24) == 0)) {
      FUN_00509960();
      *unaff_FS_OFFSET = local_c;
      return;
    }
  }
  puVar6 = operator_new(0x9c);
  local_4 = 0;
  if (puVar6 == (undefined4 *)0x0) {
    puVar10 = (undefined4 *)0x0;
  }
  else {
    FUN_00505760(puVar6);
    *puVar6 = &PTR_LAB_00557c34;
    *(undefined1 *)(puVar6 + 0xe) = 1;
    puVar10 = puVar6;
  }
  local_4 = 0xffffffff;
  puVar10[9] = 0;
  puVar10[0x13] = 0;
  puVar10[0x11] = 0x2713;
  puVar10[0x12] = 0;
  puVar10[10] = 0xf3;
  puVar10[0xb] = 0xca;
  puVar10[0xc] = 0x139;
  puVar10[0xd] = 0xc1;
  puVar10[0x25] = param_2;
  puVar10[0x26] = param_3;
  puVar7 = (undefined4 *)CreateTextEntryWidget(0,0x60,0x2c,0xbe,0xc,0x14);
  FUN_0050e670(puVar7);
  FUN_00506f60();
  FUN_0050efa0(param_1);
  (**(code **)*puVar7)(1);
  uVar8 = CreateTextEntryWidget(1,0x60,0x46,0xbe,0xc,4);
  FUN_0050e670(uVar8);
  iVar11 = 0;
  piVar1 = puVar10 + 3;
  param_1 = 0xad;
  do {
    iVar9 = CreateLabelWidget(iVar11,iVar11 + 0x518,param_1,8,0x1b,0x1b);
    *(bool *)(iVar9 + 0x3a) = iVar11 == 3;
    uVar4 = puVar10[4];
    if (((uint)puVar10[5] <= uVar4) && (cVar5 = FUN_0050ed30(), cVar5 == '\0')) goto LAB_0050874e;
    piVar2 = (int *)(*piVar1 + uVar4 * 4);
    if (piVar2 != (int *)0x0) {
      *piVar2 = iVar9;
    }
    puVar10[4] = puVar10[4] + 1;
    FUN_0050e730(puVar10[10],puVar10[0xb]);
    param_1 = param_1 + 0x20;
    iVar11 = iVar11 + 1;
    *(undefined4 **)(iVar9 + 8) = puVar10;
  } while (param_1 < 0x12d);
  puVar7 = operator_new(0x40);
  if (puVar7 == (undefined4 *)0x0) {
    puVar7 = (undefined4 *)0x0;
  }
  else {
    puVar7[3] = 0;
    puVar7[4] = 0;
    puVar7[5] = 0;
    puVar7[6] = 0;
    *(undefined1 *)(puVar7 + 1) = 0;
    puVar7[2] = 0;
    *(undefined1 *)(puVar7 + 7) = 1;
    *(undefined1 *)((int)puVar7 + 0x1d) = 0;
    *(undefined1 *)((int)puVar7 + 0x1e) = 0;
    puVar7[8] = 1;
    *(undefined1 *)(puVar7 + 0xe) = 0;
    *(undefined1 *)((int)puVar7 + 0x39) = 0;
    *(undefined1 *)((int)puVar7 + 0x3a) = 0;
    *puVar7 = &PTR_LAB_00557da0;
  }
  puVar7[9] = 4;
  puVar7[0xf] = 0x514;
  puVar7[10] = 0x16;
  puVar7[0xb] = 0x5f;
  puVar7[0xc] = 0x2d;
  puVar7[0xd] = 0x18;
  *(undefined1 *)((int)puVar7 + 0x3a) = 1;
  uVar4 = puVar10[4];
  if (((uint)puVar10[5] <= uVar4) && (cVar5 = FUN_0050ed30(), cVar5 == '\0')) {
                    /* WARNING: Subroutine does not return */
    FUN_004010c0(0x8007000e);
  }
  puVar3 = (undefined4 *)(*piVar1 + uVar4 * 4);
  if (puVar3 != (undefined4 *)0x0) {
    *puVar3 = puVar7;
  }
  puVar10[4] = puVar10[4] + 1;
  FUN_0050e730(puVar10[10],puVar10[0xb]);
  puVar7[2] = puVar10;
  puVar7 = operator_new(0x40);
  if (puVar7 == (undefined4 *)0x0) {
    puVar7 = (undefined4 *)0x0;
  }
  else {
    puVar7[3] = 0;
    puVar7[4] = 0;
    puVar7[5] = 0;
    puVar7[6] = 0;
    *(undefined1 *)(puVar7 + 1) = 0;
    puVar7[2] = 0;
    *(undefined1 *)(puVar7 + 7) = 1;
    *(undefined1 *)((int)puVar7 + 0x1d) = 0;
    *(undefined1 *)((int)puVar7 + 0x1e) = 0;
    puVar7[8] = 1;
    *(undefined1 *)(puVar7 + 0xe) = 0;
    *(undefined1 *)((int)puVar7 + 0x39) = 0;
    *(undefined1 *)((int)puVar7 + 0x3a) = 0;
    *puVar7 = &PTR_LAB_00557da0;
  }
  puVar7[9] = 5;
  puVar7[0xf] = 0x515;
  puVar7[10] = 0x45;
  puVar7[0xb] = 0x5f;
  puVar7[0xc] = 0x2d;
  puVar7[0xd] = 0x18;
  uVar4 = puVar10[4];
  if (((uint)puVar10[5] <= uVar4) && (cVar5 = FUN_0050ed30(), cVar5 == '\0')) {
                    /* WARNING: Subroutine does not return */
    FUN_004010c0(0x8007000e);
  }
  puVar3 = (undefined4 *)(*piVar1 + uVar4 * 4);
  if (puVar3 != (undefined4 *)0x0) {
    *puVar3 = puVar7;
  }
  puVar10[4] = puVar10[4] + 1;
  FUN_0050e730(puVar10[10],puVar10[0xb]);
  puVar7[2] = puVar10;
  puVar7 = operator_new(0x40);
  if (puVar7 == (undefined4 *)0x0) {
    puVar7 = (undefined4 *)0x0;
  }
  else {
    puVar7[3] = 0;
    puVar7[4] = 0;
    puVar7[5] = 0;
    puVar7[6] = 0;
    *(undefined1 *)(puVar7 + 1) = 0;
    puVar7[2] = 0;
    *(undefined1 *)(puVar7 + 7) = 1;
    *(undefined1 *)((int)puVar7 + 0x1d) = 0;
    *(undefined1 *)((int)puVar7 + 0x1e) = 0;
    puVar7[8] = 1;
    *(undefined1 *)(puVar7 + 0xe) = 0;
    *(undefined1 *)((int)puVar7 + 0x39) = 0;
    *(undefined1 *)((int)puVar7 + 0x3a) = 0;
    *puVar7 = &PTR_LAB_00557da0;
  }
  puVar7[9] = 6;
  puVar7[0xf] = 0x516;
  puVar7[10] = 0x16;
  puVar7[0xb] = 0x7a;
  puVar7[0xc] = 0x2d;
  puVar7[0xd] = 0x18;
  uVar4 = puVar10[4];
  if (((uint)puVar10[5] <= uVar4) && (cVar5 = FUN_0050ed30(), cVar5 == '\0')) {
                    /* WARNING: Subroutine does not return */
    FUN_004010c0(0x8007000e);
  }
  puVar3 = (undefined4 *)(*piVar1 + uVar4 * 4);
  if (puVar3 != (undefined4 *)0x0) {
    *puVar3 = puVar7;
  }
  puVar10[4] = puVar10[4] + 1;
  FUN_0050e730(puVar10[10],puVar10[0xb]);
  puVar7[2] = puVar10;
  puVar7 = operator_new(0x40);
  if (puVar7 == (undefined4 *)0x0) {
    puVar7 = (undefined4 *)0x0;
  }
  else {
    puVar7[3] = 0;
    puVar7[4] = 0;
    puVar7[5] = 0;
    puVar7[6] = 0;
    *(undefined1 *)(puVar7 + 1) = 0;
    puVar7[2] = 0;
    *(undefined1 *)(puVar7 + 7) = 1;
    *(undefined1 *)((int)puVar7 + 0x1d) = 0;
    *(undefined1 *)((int)puVar7 + 0x1e) = 0;
    puVar7[8] = 1;
    *(undefined1 *)(puVar7 + 0xe) = 0;
    *(undefined1 *)((int)puVar7 + 0x39) = 0;
    *(undefined1 *)((int)puVar7 + 0x3a) = 0;
    *puVar7 = &PTR_LAB_00557da0;
  }
  puVar7[9] = 7;
  puVar7[0xf] = 0x517;
  puVar7[10] = 0x45;
  puVar7[0xb] = 0x7a;
  puVar7[0xc] = 0x2d;
  puVar7[0xd] = 0x18;
  uVar4 = puVar10[4];
  if (((uint)puVar10[5] <= uVar4) && (cVar5 = FUN_0050ed30(), cVar5 == '\0')) {
                    /* WARNING: Subroutine does not return */
    FUN_004010c0(0x8007000e);
  }
  puVar3 = (undefined4 *)(*piVar1 + uVar4 * 4);
  if (puVar3 != (undefined4 *)0x0) {
    *puVar3 = puVar7;
  }
  puVar10[4] = puVar10[4] + 1;
  FUN_0050e730(puVar10[10],puVar10[0xb]);
  puVar7[2] = puVar10;
  puVar7 = operator_new(0x40);
  if (puVar7 == (undefined4 *)0x0) {
    puVar7 = (undefined4 *)0x0;
  }
  else {
    puVar7[3] = 0;
    puVar7[4] = 0;
    puVar7[5] = 0;
    puVar7[6] = 0;
    *(undefined1 *)(puVar7 + 1) = 0;
    puVar7[2] = 0;
    *(undefined1 *)(puVar7 + 7) = 1;
    *(undefined1 *)((int)puVar7 + 0x1d) = 0;
    *(undefined1 *)((int)puVar7 + 0x1e) = 0;
    puVar7[8] = 1;
    *(undefined1 *)(puVar7 + 0xe) = 0;
    *(undefined1 *)((int)puVar7 + 0x39) = 0;
    *(undefined1 *)((int)puVar7 + 0x3a) = 0;
    *puVar7 = &PTR_LAB_00557da0;
  }
  puVar7[9] = 8;
  puVar7[0xf] = 0x51d;
  puVar7[10] = 0xd5;
  puVar7[0xb] = 0x99;
  puVar7[0xc] = 0x52;
  puVar7[0xd] = 0x22;
  uVar4 = puVar10[4];
  if (((uint)puVar10[5] <= uVar4) && (cVar5 = FUN_0050ed30(), cVar5 == '\0')) {
                    /* WARNING: Subroutine does not return */
    FUN_004010c0(0x8007000e);
  }
  puVar3 = (undefined4 *)(*piVar1 + uVar4 * 4);
  if (puVar3 != (undefined4 *)0x0) {
    *puVar3 = puVar7;
  }
  puVar10[4] = puVar10[4] + 1;
  FUN_0050e730(puVar10[10],puVar10[0xb]);
  puVar7[2] = puVar10;
  puVar7 = operator_new(0x40);
  if (puVar7 == (undefined4 *)0x0) {
    puVar7 = (undefined4 *)0x0;
  }
  else {
    puVar7[3] = 0;
    puVar7[4] = 0;
    puVar7[5] = 0;
    puVar7[6] = 0;
    *(undefined1 *)(puVar7 + 1) = 0;
    puVar7[2] = 0;
    *(undefined1 *)(puVar7 + 7) = 1;
    *(undefined1 *)((int)puVar7 + 0x1d) = 0;
    *(undefined1 *)((int)puVar7 + 0x1e) = 0;
    puVar7[8] = 1;
    *(undefined1 *)(puVar7 + 0xe) = 0;
    *(undefined1 *)((int)puVar7 + 0x39) = 0;
    *(undefined1 *)((int)puVar7 + 0x3a) = 0;
    *puVar7 = &PTR_LAB_00557da0;
  }
  puVar7[9] = 9;
  puVar7[0xf] = 0x51c;
  puVar7[10] = 0x80;
  puVar7[0xb] = 0x99;
  puVar7[0xc] = 0x52;
  puVar7[0xd] = 0x22;
  uVar4 = puVar10[4];
  if ((uVar4 < (uint)puVar10[5]) || (cVar5 = FUN_0050ed30(), cVar5 != '\0')) {
    puVar3 = (undefined4 *)(*piVar1 + uVar4 * 4);
    if (puVar3 != (undefined4 *)0x0) {
      *puVar3 = puVar7;
    }
    puVar10[4] = puVar10[4] + 1;
    FUN_0050e730(puVar10[10],puVar10[0xb]);
    puVar7[2] = puVar10;
    puVar10[0x24] = 1;
    FUN_0050eea0(puVar10);
    *unaff_FS_OFFSET = puVar6;
    return;
  }
LAB_0050874e:
                    /* WARNING: Subroutine does not return */
  FUN_004010c0(0x8007000e);
}

