/* FUN_00503130 - 0x00503130 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00503130(int param_1,int param_2,uint param_3)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  void *pvVar4;
  undefined4 uVar5;
  int extraout_ECX;
  int iVar6;
  undefined4 *unaff_FS_OFFSET;
  int local_24;
  int local_20;
  int local_1c;
  uint local_18;
  undefined1 *local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00537b98;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  local_14 = &stack0xffffffd0;
  FUN_00503710(&local_24);
  iVar6 = 0;
  local_8 = 0;
  iVar3 = *(int *)(param_1 + 4);
  if (iVar3 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = *(int *)(param_1 + 0xc) - iVar3 >> 3;
  }
  if (param_3 != 0) {
    if (iVar3 != 0) {
      iVar6 = *(int *)(param_1 + 8) - iVar3 >> 3;
    }
    if (0x1fffffffU - iVar6 < param_3) {
      uVar2 = FUN_005030a0();
      iVar3 = extraout_ECX;
    }
    if (iVar3 == 0) {
      iVar6 = 0;
    }
    else {
      iVar6 = *(int *)(param_1 + 8) - iVar3 >> 3;
    }
    if (uVar2 < iVar6 + param_3) {
      if (0x1fffffff - (uVar2 >> 1) < uVar2) {
        local_18 = 0;
      }
      else {
        local_18 = uVar2 + (uVar2 >> 1);
      }
      if (iVar3 == 0) {
        iVar6 = 0;
      }
      else {
        iVar6 = *(int *)(param_1 + 8) - iVar3 >> 3;
      }
      if (local_18 < iVar6 + param_3) {
        if (iVar3 == 0) {
          iVar3 = 0;
        }
        else {
          iVar3 = *(int *)(param_1 + 8) - iVar3 >> 3;
        }
        local_18 = iVar3 + param_3;
      }
      local_18 = local_18 << 3;
      pvVar4 = operator_new(local_18);
      local_8 = CONCAT31(local_8._1_3_,1);
      iVar3 = FUN_005045d0(param_2,pvVar4,param_2);
      FUN_00504190(iVar3,param_2);
      FUN_005045d0(*(undefined4 *)(param_1 + 8),iVar3 + param_3 * 8,param_2);
      iVar3 = *(int *)(param_1 + 4);
      if (iVar3 == 0) {
        iVar6 = 0;
      }
      else {
        iVar6 = *(int *)(param_1 + 8) - iVar3 >> 3;
      }
      if (iVar3 != 0) {
        FUN_00503110();
        _free(*(void **)(param_1 + 4));
      }
      *(uint *)(param_1 + 0xc) = local_18 + (int)pvVar4;
      *(void **)(param_1 + 8) = (void *)((int)pvVar4 + (param_3 + iVar6) * 8);
      *(void **)(param_1 + 4) = pvVar4;
    }
    else {
      local_1c = *(int *)(param_1 + 8);
      local_18 = param_3 * 8;
      if ((uint)(local_1c - param_2 >> 3) < param_3) {
        FUN_005045d0(local_1c,local_18 + param_2,param_2);
        local_8 = CONCAT31(local_8._1_3_,3);
        FUN_00504190(*(undefined4 *)(param_1 + 8),param_2);
        local_8 = 0;
        iVar3 = *(int *)(param_1 + 8) + local_18;
        *(int *)(param_1 + 8) = iVar3;
        FUN_00503f30(param_2,iVar3 - local_18,&local_24);
      }
      else {
        iVar3 = local_1c + param_3 * -8;
        uVar5 = FUN_005045d0(local_1c,local_1c,param_2);
        *(undefined4 *)(param_1 + 8) = uVar5;
        FUN_00504330(param_2,iVar3,local_1c,param_2);
        FUN_00503f30(param_2,local_18 + param_2,&local_24);
      }
    }
  }
  local_8 = 0xffffffff;
  piVar1 = (int *)(local_20 + -4);
  LOCK();
  iVar3 = *piVar1;
  *piVar1 = *piVar1 + -1;
  UNLOCK();
  if (iVar3 + -1 < 1) {
    (**(code **)(**(int **)(local_20 + -0x10) + 4))((undefined4 *)(local_20 + -0x10));
  }
  piVar1 = (int *)(local_24 + -4);
  LOCK();
  iVar3 = *piVar1;
  *piVar1 = *piVar1 + -1;
  UNLOCK();
  if (iVar3 == 1 || iVar3 + -1 < 0) {
    (**(code **)(**(int **)(local_24 + -0x10) + 4))((undefined4 *)(local_24 + -0x10));
  }
  *unaff_FS_OFFSET = local_10;
  return;
}

