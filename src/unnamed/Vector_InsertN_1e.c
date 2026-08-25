/* Vector_InsertN_1e - 0x005033e0 in the original binary.
 *
 * std::vector<T>::_Insert_n for 0x1e-byte elements: if the free tail is too
 * short, reallocate; otherwise shift the tail up with Vector_CopyBackward_1e
 * and fill the gap with Vector_FillN_1e.  The element being inserted lives
 * by value in this frame -- see the header note on local_38.
 *
 * THE BY-VALUE ELEMENT BUFFER (2026-08-25).  Three calls here pass the address
 * of [ebp-0x34] in a register, and nothing in this function ever writes that
 * slot -- only `lea`s it -- so it is a scratch object the callees fill: the
 * element being inserted, 0x1e bytes wide (the stride this function multiplies
 * by).  Ghidra dropped it because its only users were dropped registers.  The
 * next ebp slot in use is 0x14, so the object has room for exactly that width.
 */
#include "ghidra_types.h"


void __thiscall Vector_InsertN_1e(uint param_1,int param_2,int param_3)

{
  int iVar1;
  void *pvVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  uint extraout_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_38 [0x1e];   /* the inserted element; see the header note */
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00537970;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  CopyNameKey();
  iVar1 = *(int *)(param_2 + 4);
  if (iVar1 == 0) {
    uVar5 = 0;
  }
  else {
    uVar5 = (*(int *)(param_2 + 0xc) - iVar1) / 0x1e;
  }
  if (param_1 != 0) {
    if (iVar1 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = (*(int *)(param_2 + 8) - *(int *)(param_2 + 4)) / 0x1e;
    }
    if (0x8888888U - iVar1 < param_1) {
      FUN_005030a0();
      uVar5 = extraout_ECX;
    }
    if (*(int *)(param_2 + 4) == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = (*(int *)(param_2 + 8) - *(int *)(param_2 + 4)) / 0x1e;
    }
    if (uVar5 < iVar1 + param_1) {
      if (0x8888888 - (uVar5 >> 1) < uVar5) {
        uVar5 = 0;
      }
      else {
        uVar5 = uVar5 + (uVar5 >> 1);
      }
      if (*(int *)(param_2 + 4) == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = (*(int *)(param_2 + 8) - *(int *)(param_2 + 4)) / 0x1e;
      }
      if (uVar5 < iVar1 + param_1) {
        iVar1 = FUN_00502ad0();
        uVar5 = iVar1 + param_1;
      }
      pvVar2 = operator_new(uVar5 * 0x1e);
      local_8 = 0;
      FUN_005046b0(param_3,param_3);
      FUN_00504270(param_3);
      FUN_005046b0(*(undefined4 *)(param_2 + 8),param_3);
      iVar1 = 0;
      if (*(int *)(param_2 + 4) != 0) {
        iVar1 = (*(int *)(param_2 + 8) - *(int *)(param_2 + 4)) / 0x1e;
      }
      if (*(void **)(param_2 + 4) != (void *)0x0) {
        _free(*(void **)(param_2 + 4));
      }
      *(void **)(param_2 + 0xc) = (void *)(uVar5 * 0x1e + (int)pvVar2);
      *(void **)(param_2 + 8) = (void *)((param_1 + iVar1) * 0x1e + (int)pvVar2);
      *(void **)(param_2 + 4) = pvVar2;
      *unaff_FS_OFFSET = local_10;
      return;
    }
    iVar1 = *(int *)(param_2 + 8);
    if ((uint)((iVar1 - param_3) / 0x1e) < param_1) {
      iVar3 = param_1 * 0x1e;
      FUN_005046b0(iVar1,iVar3);
      local_8 = 2;
      FUN_00504270(iVar3);
      *(int *)(param_2 + 8) = *(int *)(param_2 + 8) + iVar3;
    }
    else {
      uVar4 = FUN_005046b0(iVar1,param_1 * 0x1e);
      *(undefined4 *)(param_2 + 8) = uVar4;
      Vector_CopyBackward_1e(0,(undefined4 *)(iVar1 - param_1 * 0x1e),(undefined4 *)iVar1,
                 (undefined4 *)param_3);
    }
    Vector_FillN_1e(0,(undefined4 *)(param_3 + iVar3),(undefined4 *)param_3,
                 (undefined4 *)local_38);
  }
  *unaff_FS_OFFSET = local_10;
  return;
}

