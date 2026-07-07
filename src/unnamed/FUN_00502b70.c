/* FUN_00502b70 - 0x00502b70 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_00502b70(undefined4 *param_1,int param_2,int param_3,uint param_4)

{
  void *_Memory;
  uint uVar1;
  int iVar2;
  int iVar3;
  void *pvVar4;
  undefined4 uVar5;
  uint uVar6;
  uint extraout_ECX;
  undefined4 *puVar7;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_2c [4];
  byte local_1b;
  uint local_18;
  undefined1 *local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00537ad0;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  local_1b = *(byte *)((int)param_1 + 0x11);
  uVar1 = (uint)local_1b;
  puVar7 = local_2c;
  for (uVar6 = (uint)(local_1b >> 2); uVar6 != 0; uVar6 = uVar6 - 1) {
    *puVar7 = *param_1;
    param_1 = param_1 + 1;
    puVar7 = puVar7 + 1;
  }
  for (uVar6 = uVar1 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined1 *)puVar7 = *(undefined1 *)param_1;
    param_1 = (undefined4 *)((int)param_1 + 1);
    puVar7 = (undefined4 *)((int)puVar7 + 1);
  }
  iVar3 = *(int *)(param_2 + 4);
  local_14 = &stack0xffffffc8;
  *(undefined1 *)((int)local_2c + uVar1) = 0;
  if (iVar3 == 0) {
    local_18 = 0;
  }
  else {
    local_18 = (*(int *)(param_2 + 0xc) - iVar3) / 0x12;
  }
  if (param_4 != 0) {
    if (iVar3 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = (*(int *)(param_2 + 8) - iVar3) / 0x12;
    }
    if (0xe38e38eU - iVar2 < param_4) {
      FUN_005030a0();
      local_18 = extraout_ECX;
    }
    if (iVar3 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = (*(int *)(param_2 + 8) - iVar3) / 0x12;
    }
    if (local_18 < iVar2 + param_4) {
      if (0xe38e38e - (local_18 >> 1) < local_18) {
        local_18 = 0;
      }
      else {
        local_18 = local_18 + (local_18 >> 1);
      }
      if (iVar3 == 0) {
        iVar3 = 0;
      }
      else {
        iVar3 = (*(int *)(param_2 + 8) - iVar3) / 0x12;
      }
      if (local_18 < iVar3 + param_4) {
        iVar3 = FUN_004fdc30();
        local_18 = iVar3 + param_4;
      }
      local_18 = local_18 * 0x12;
      pvVar4 = operator_new(local_18);
      local_8 = 0;
      FUN_00504550(param_3,param_3);
      FUN_00504110(param_3);
      FUN_00504550(*(undefined4 *)(param_2 + 8),param_3);
      _Memory = *(void **)(param_2 + 4);
      if (_Memory == (void *)0x0) {
        iVar3 = 0;
      }
      else {
        iVar3 = (*(int *)(param_2 + 8) - (int)_Memory) / 0x12;
      }
      if (_Memory != (void *)0x0) {
        _free(_Memory);
      }
      *(uint *)(param_2 + 0xc) = local_18 + (int)pvVar4;
      *(void **)(param_2 + 8) = (void *)((int)pvVar4 + (param_4 + iVar3) * 0x12);
      *(void **)(param_2 + 4) = pvVar4;
      *unaff_FS_OFFSET = local_10;
      return;
    }
    iVar3 = *(int *)(param_2 + 8);
    if ((uint)((iVar3 - param_3) / 0x12) < param_4) {
      FUN_00504550(iVar3,param_3);
      local_8 = 2;
      FUN_00504110(param_3);
      *(uint *)(param_2 + 8) = *(int *)(param_2 + 8) + param_4 * 0x12;
    }
    else {
      iVar2 = iVar3 + param_4 * -0x12;
      uVar5 = FUN_00504550(iVar3,iVar2);
      *(undefined4 *)(param_2 + 8) = uVar5;
      FUN_005042f0(iVar2);
    }
    FUN_00503eb0();
  }
  *unaff_FS_OFFSET = local_10;
  return;
}

