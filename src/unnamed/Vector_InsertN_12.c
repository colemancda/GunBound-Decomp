/* Vector_InsertN_12 - 0x00502b70 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-30, CERTAIN (was FUN_00502b70).  VC7.1's private
 * vector<T>::_Insert_n(_Where, _Count, _Val) for the 0x12-byte element,
 * the stride-0x12 sibling of Vector_InsertN_34 (0x502e20),
 * Vector_InsertN_8 (0x503130) and Vector_InsertN_1e (0x5033e0), arm for
 * arm:
 *   0x502b8f  copy the by-value element into the local _Tmp at
 *             [ebp-0x28] (the counted name copy, length byte at +0x11)
 *   0x502c01  max_size() - size() < _Count -> Vector_ThrowTooLong, with
 *             max_size 0xe38e38e = 0xffffffff / 0x12
 *   0x502c39  1.5x regrow, Vector_Size_12 at 0x502c74 for the
 *             size() + _Count floor, operator_new(cap * 0x12)
 *   realloc   Vector_UninitCopy_12 head, Vector_UninitFillN_12 gap,
 *             Vector_UninitCopy_12 tail, _free the old block
 *   0x502d69  append-overlap: Vector_UninitCopy_12 the tail up,
 *             Vector_UninitFillN_12 the remainder, then fill
 *   0x502dc3  shift: Vector_UninitCopy_12 the last n up,
 *             Vector_CopyBackward_12, then fill
 *   0x502dfa  Vector_FillN_12(_Where, end, _Tmp)
 * Calling convention as compiled (whole-program, not the _34 one): ECX =
 * the element, stack = vector, _Where, _Count, `ret 0xc`. Its one caller
 * Vector_Insert_12, the one-element insert, sets `mov ecx,[esp+0x18]` and
 * pushes 1, the position and the vector - insert()'s `_Insert_n(_Where,
 * 1, _Val)` - and is itself reached from the push_back FUN_00502750.
 *
 * The two 2026-09-20 notes below predate the name and are kept
 * verbatim: their FUN_00504550 is Vector_UninitCopy_12, and their
 * FUN_005029b0 is Vector_Insert_12, the one-element insert. The TODO
 * the second note describes was resolved 2026-10-30 - see
 * Vector_Insert_12.c, which now declares the element and passes it.
 *
 * DROPPED-ARGUMENT FIX (2026-09-20): the 4 FUN_00504550() calls here were
 * missing its dest argument (see FUN_00504550.c's header) and, in two
 * cases, were passing the wrong begin/end operand entirely because the
 * `iVar3` local is recycled across this function for several unrelated
 * SSA values - the first call's true begin operand is a fresh
 * `*(param_2 + 4)` reread, not the (by-then-stale) `iVar3` C variable.
 * Reconstructed per-site from a capstone disassembly of 0x502b70..0x502e10
 * against the original binary; see FUN_00504550.c for the ABI evidence.
 *
 * DROPPED-ARGUMENT FIX (2026-09-20, own callers): __thiscall with 4 real
 * params (ECX=`this` + ret 0xc = 3 stack dwords, disasm 0x502b70-
 * 0x502e0f); the declared shape was already correct. The sole call site
 * (FUN_005029b0.c) dropped `this` entirely, writing only the 3 stack args
 * (which already land correctly in param_2/param_3/param_4). Orig
 * 0x5029f7-0x502a04: `mov ecx,[esp+0x18]; push 1; push ebx; push edi;
 * call 0x502b70` - the real ECX/`this` value is FUN_005029b0's OWN 3rd
 * stack argument, which is not a declared parameter of FUN_005029b0 at
 * all (that function's own signature has a separate, out-of-scope bug -
 * it declares only 2 params plus the already-flagged `unaff_EDI`, and is
 * not one of this batch's 6 functions). Left as a TODO at the call site;
 * resolving it requires fixing FUN_005029b0's own parameter list.
 */
#include "ghidra_types.h"


void __thiscall Vector_InsertN_12(undefined4 *param_1,int param_2,int param_3,uint param_4)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xffffffc8;
  void *_Memory;
  uint uVar1;
  int iVar2;
  int iVar3;
  int iFillEnd;
  void *pvVar4;
  undefined4 uVar5;
  uint uVar6;
  uint extraout_ECX;
  undefined4 *puVar7;
  undefined4 *puVar8;
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
      Vector_ThrowTooLong();
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
        /* `this` restored: `mov ecx,edi` at 0x502c72, EDI = [ebp+8] =
         * param_2 (0x502bac) - see Vector_Size_12.c. */
        iVar3 = Vector_Size_12(param_2);
        local_18 = iVar3 + param_4;
      }
      local_18 = local_18 * 0x12;
      pvVar4 = operator_new(local_18);
      local_8 = 0;
      puVar8 = (undefined4 *)
               Vector_UninitCopy_12(0,*(undefined4 **)(param_2 + 4),(undefined4 *)param_3,
                             (undefined4 *)pvVar4);
      /* Count n in ECX (`mov ecx,esi` at 0x502caf, ESI = [ebp+0x10]),
       * destination = the head copy's return in EAX, element = the local
       * copy in EBX (`lea ebx,[ebp-0x28]` at 0x502cac); the pushed
       * [ebp+0xc] is the never-read allocator word. */
      Vector_UninitFillN_12(param_4,0,param_3,puVar8,local_2c);
      Vector_UninitCopy_12(0,(undefined4 *)param_3,*(undefined4 **)(param_2 + 8),
                    (undefined4 *)((int)puVar8 + param_4 * 0x12));
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
      Vector_UninitCopy_12(0,(undefined4 *)param_3,(undefined4 *)iVar3,
                    (undefined4 *)(param_3 + param_4 * 0x12));
      local_8 = 2;
      /* Count = n - (_Mylast - _Where)/0x12 in ECX (0x502d86-0x502da8),
       * destination = the not-yet-advanced _Mylast in EAX (0x502da1),
       * element = the local copy in EBX (0x502da5). */
      Vector_UninitFillN_12(param_4 - (uint)((iVar3 - param_3) / 0x12),0,param_3,
                            (undefined4 *)iVar3,local_2c);
      *(uint *)(param_2 + 8) = *(int *)(param_2 + 8) + param_4 * 0x12;
      /* fill end = new _Mylast - n*0x12 = the old _Mylast (0x502db2-0x502db9) */
      iFillEnd = iVar3;
    }
    else {
      iVar2 = iVar3 + param_4 * -0x12;
      uVar5 = Vector_UninitCopy_12(0,(undefined4 *)iVar2,(undefined4 *)iVar3,(undefined4 *)iVar3);
      *(undefined4 *)(param_2 + 8) = uVar5;
      Vector_CopyBackward_12((undefined4 *)iVar2,(undefined4 *)param_3,(undefined4 *)iVar3);
      /* fill end = _Where + n*0x12 (`lea ecx,[esi+ebx]` at 0x502def) */
      iFillEnd = param_3 + param_4 * 0x12;
    }
    /* fill(_Where, fill end, element copy): EAX = _Where (EBX / [ebp+0xc]),
     * ECX = the per-arm end above, EDX = `lea edx,[ebp-0x28]` (0x502df4) =
     * local_2c.  The port passed nothing. */
    Vector_FillN_12((undefined4 *)iFillEnd,local_2c,(undefined4 *)param_3);
  }
  *unaff_FS_OFFSET = local_10;
  return;
}

