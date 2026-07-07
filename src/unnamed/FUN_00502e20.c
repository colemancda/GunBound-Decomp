/* FUN_00502e20 - 0x00502e20 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_00502e20(uint param_1,int param_2,int param_3)

{
  void *_Memory;
  int iVar1;
  int iVar2;
  void *pvVar3;
  undefined4 uVar4;
  uint uVar5;
  uint extraout_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00537980;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  FUN_00503680();
  iVar2 = *(int *)(param_2 + 4);
  if (iVar2 == 0) {
    uVar5 = 0;
  }
  else {
    uVar5 = (*(int *)(param_2 + 0xc) - iVar2) / 0x34;
  }
  if (param_1 != 0) {
    if (iVar2 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = (*(int *)(param_2 + 8) - iVar2) / 0x34;
    }
    if (0x4ec4ec4U - iVar1 < param_1) {
      FUN_005030a0();
      uVar5 = extraout_ECX;
    }
    if (iVar2 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = (*(int *)(param_2 + 8) - iVar2) / 0x34;
    }
    if (uVar5 < iVar1 + param_1) {
      if (0x4ec4ec4 - (uVar5 >> 1) < uVar5) {
        uVar5 = 0;
      }
      else {
        uVar5 = uVar5 + (uVar5 >> 1);
      }
      if (iVar2 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = (*(int *)(param_2 + 8) - iVar2) / 0x34;
      }
      if (uVar5 < iVar2 + param_1) {
        iVar2 = FUN_00404890();
        uVar5 = iVar2 + param_1;
      }
      pvVar3 = operator_new(uVar5 * 0x34);
      local_8 = 0;
      FUN_005045a0(param_3);
      FUN_00504160(param_3);
      FUN_005045a0(param_3);
      _Memory = *(void **)(param_2 + 4);
      if (_Memory == (void *)0x0) {
        iVar2 = 0;
      }
      else {
        iVar2 = (*(int *)(param_2 + 8) - (int)_Memory) / 0x34;
      }
      if (_Memory != (void *)0x0) {
        _free(_Memory);
      }
      *(void **)(param_2 + 0xc) = (void *)(uVar5 * 0x34 + (int)pvVar3);
      *(void **)(param_2 + 8) = (void *)((param_1 + iVar2) * 0x34 + (int)pvVar3);
      *(void **)(param_2 + 4) = pvVar3;
      *unaff_FS_OFFSET = local_10;
      return;
    }
    if ((uint)((*(int *)(param_2 + 8) - param_3) / 0x34) < param_1) {
      FUN_005045a0(param_3);
      local_8 = 2;
      FUN_00504160(param_3);
      *(uint *)(param_2 + 8) = *(int *)(param_2 + 8) + param_1 * 0x34;
    }
    else {
      uVar4 = FUN_005045a0(param_3);
      *(undefined4 *)(param_2 + 8) = uVar4;
      FUN_00503f10();
    }
    FUN_00503ef0();
  }
  *unaff_FS_OFFSET = local_10;
  return;
}

