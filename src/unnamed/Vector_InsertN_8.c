/* Vector_InsertN_8 - 0x00503130 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-08-28): the insert-n member of the 8-byte {CStringA,
 * CStringA} pair vector, the stride-8 sibling of Vector_InsertN_34
 * (0x502e20) and Vector_InsertN_1e (0x5033e0), between which it sits in
 * the binary just as every other member of this family does. All three
 * share the VC7.1 insert(pos, n, val) shape arm for arm: copy-construct
 * the by-value element first (Vector_CopyElement_8, whose &local_24
 * result the fill calls consume), max_size guard (0x1fffffff =
 * 0xffffffff / 8 exactly, where the _34 twin guards 0x4ec4ec4 =
 * 0xffffffff / 0x34), 1.5x regrow through operator_new, then the same
 * three arms - realloc (Vector_UninitCopy_8 head + Vector_UninitFillN_8
 * + tail copy, destroy + _free the old buffer), append-overlap
 * (uninit-copy the tail up, fill through Vector_FillN_8), and shift
 * (Vector_UninitCopy_8 + Vector_CopyBackward_8 + fill). The stride is
 * pinned by the >>3 size computations and the param_3 * 8 stepping, and
 * the element type by the epilogue's two refcounted CString releases on
 * the by-value element's handles. Push-back wrapper: FUN_00502890
 * (insert 1 at end), itself sandwiched between the _34 and _1e
 * push-backs.
 *
 * Helper renames of 2026-08-28, for reading older notes: FUN_00503710 =
 * Vector_CopyElement_8, FUN_005045d0 = Vector_UninitCopy_8,
 * FUN_00504190 = Vector_UninitFillN_8, FUN_00504330 =
 * Vector_CopyBackward_8, FUN_00503f30 = Vector_FillN_8, FUN_00503110 =
 * Vector_DestroyRange_8.
 */
#include "ghidra_types.h"


void Vector_InsertN_8(int param_1,int param_2,uint param_3)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xffffffd0;
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
  Vector_CopyElement_8(&local_24);
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
      local_8 = CONCAT31(SUBFIELD(local_8,1,undefined3),1);
      iVar3 = Vector_UninitCopy_8(param_2,pvVar4,param_2);
      Vector_UninitFillN_8(iVar3,param_2);
      Vector_UninitCopy_8(*(undefined4 *)(param_1 + 8),iVar3 + param_3 * 8,param_2);
      iVar3 = *(int *)(param_1 + 4);
      if (iVar3 == 0) {
        iVar6 = 0;
      }
      else {
        iVar6 = *(int *)(param_1 + 8) - iVar3 >> 3;
      }
      if (iVar3 != 0) {
        /* DROPPED-REG FIX 2026-08-28: destroy the old elements before the
           free - EAX = iVar3 (the old begin, the very guard above), EDI =
           `mov edi,[esi+8]` at 0x50326c, the old end. */
        Vector_DestroyRange_8(iVar3,*(int *)(param_1 + 8));
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
        Vector_UninitCopy_8(local_1c,local_18 + param_2,param_2);
        local_8 = CONCAT31(SUBFIELD(local_8,1,undefined3),3);
        Vector_UninitFillN_8(*(undefined4 *)(param_1 + 8),param_2);
        local_8 = 0;
        iVar3 = *(int *)(param_1 + 8) + local_18;
        *(int *)(param_1 + 8) = iVar3;
        Vector_FillN_8(param_2,iVar3 - local_18,&local_24);
      }
      else {
        iVar3 = local_1c + param_3 * -8;
        uVar5 = Vector_UninitCopy_8(local_1c,local_1c,param_2);
        *(undefined4 *)(param_1 + 8) = uVar5;
        Vector_CopyBackward_8(param_2,iVar3,local_1c,param_2);
        Vector_FillN_8(param_2,local_18 + param_2,&local_24);
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

