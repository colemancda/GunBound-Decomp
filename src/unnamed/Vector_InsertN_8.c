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
 * the by-value element's handles. Push-back wrapper: Vector_PushBack_8
 * (insert 1 at end), itself sandwiched between the _34 and _1e
 * push-backs.
 *
 * Helper renames of 2026-08-28, for reading older notes: FUN_00503710 =
 * Vector_CopyElement_8, FUN_005045d0 = Vector_UninitCopy_8,
 * FUN_00504190 = Vector_UninitFillN_8, FUN_00504330 =
 * Vector_CopyBackward_8, FUN_00503f30 = Vector_FillN_8, FUN_00503110 =
 * Vector_DestroyRange_8.
 *
 * ELEMENT RECOVERED (2026-10-30): the by-value element arrives in ECX -
 * `mov edi,ecx` at 0x50315b, ECX not written before it - and is the
 * source Vector_CopyElement_8 clones from (it reads [edi] and [edi+4] at
 * 0x503725/0x503741).  The three stack words (vector, _Where, _Count)
 * were already parameters; ECX becomes the trailing regEcx and is passed
 * to Vector_CopyElement_8 as its EDI source.  The one caller,
 * Vector_PushBack_8's fallback, leaves its own incoming ECX (the
 * element) untouched down to the call at 0x5028db.
 *
 * FIXED (2026-10-30), from the disassembly of every helper call:
 *
 * - SEH-prologue artifact stripped (push -1 / push 0x537b98 / mov fs:[0],
 *   esp at 0x503133-0x503141, the [ebp-0x10] esp save and the try-state
 *   byte at [ebp-4]); the catch blocks at 0x503299 and 0x50332d are not in
 *   this decompile, and the port wrote through an uninitialised
 *   unaff_FS_OFFSET on every call.
 * - Vector_UninitFillN_8 takes ECX = the value, EDX = the count and one
 *   stack word, the destination (0x5041b4/0x5041b6/0x5041ad); the second
 *   pushed word is VC7.1's unused allocator. Both calls passed the
 *   destination as the value and the _Where iterator as the count. Now:
 *   0x50322e  ECX = &local_24 (lea ecx,[ebp-0x20]), EDX = ebx = _Count,
 *             dest = eax = the head copy's end;
 *   0x5032ff  ECX = &local_24, EDX = _Count - (old end - _Where) / 8
 *             (sub ebx,ecx at 0x5032f6), dest = eax = the old end.
 * - Vector_UninitCopy_8 takes ECX = first ([edi] source walk), stack =
 *   last, dest, allocator (0x5045f6, [ebp+8], [ebp+0xc]). Its port is
 *   __thiscall erased to cdecl, so first is the leading stack word; all
 *   four calls had dropped ECX and shifted the stack words one slot
 *   left. Now:
 *   0x503219  (old begin [esi+4], _Where, new buffer)
 *   0x50324b  (_Where, old end [esi+8], head end + _Count*8)
 *   0x5032e0  (_Where, old end, _Where + _Count*8)
 *   0x503356  (old end - _Count*8, old end, old end)
 * - the by-value element copy is one 8-byte {CString, CString} pair:
 *   Vector_CopyElement_8 writes [0] and [4] of &local_24 ([ebp-0x20]),
 *   the fill calls read the same pair through it, and the epilogue
 *   releases [ebp-0x1c] and [ebp-0x20]. Ghidra split it into local_24
 *   and local_20, which MSVC need not keep adjacent, so it is coalesced
 *   into local_24[2].
 */
#include "ghidra_types.h"


void Vector_InsertN_8(int param_1,int param_2,uint param_3,int regEcx)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  void *pvVar4;
  undefined4 uVar5;
  int extraout_ECX;
  int iVar6;
  int local_24[2];
  int local_1c;
  uint local_18;
  
  /* 0x50315b: mov edi,ecx - the element is the clone's source */
  Vector_CopyElement_8(local_24,regEcx);
  iVar6 = 0;
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
      uVar2 = Vector_ThrowTooLong();
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
      /* 0x503219: ECX = old begin, (_Where, new buffer) */
      iVar3 = (int)Vector_UninitCopy_8(*(int *)(param_1 + 4),param_2,(int *)pvVar4);
      /* 0x50322e: ECX = &element, EDX = _Count, dest = the head's end */
      Vector_UninitFillN_8((undefined4)local_24,param_3,(int *)iVar3);
      /* 0x50324b: ECX = _Where, (old end, head end + _Count*8) */
      Vector_UninitCopy_8(param_2,*(int *)(param_1 + 8),(int *)(iVar3 + param_3 * 8));
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
        /* 0x5032e0: ECX = _Where, (old end, _Where + _Count*8) */
        Vector_UninitCopy_8(param_2,local_1c,(int *)(local_18 + param_2));
        /* 0x5032ff: ECX = &element, EDX = the count past the old end,
           dest = the old end */
        Vector_UninitFillN_8((undefined4)local_24,
                             param_3 - (*(int *)(param_1 + 8) - param_2 >> 3),
                             *(int **)(param_1 + 8));
        iVar3 = *(int *)(param_1 + 8) + local_18;
        *(int *)(param_1 + 8) = iVar3;
        Vector_FillN_8((int *)param_2,(int *)(iVar3 - local_18),local_24);
      }
      else {
        iVar3 = local_1c + param_3 * -8;
        /* 0x503356: ECX = old end - _Count*8, (old end, old end) */
        uVar5 = (undefined4)Vector_UninitCopy_8(iVar3,local_1c,(int *)local_1c);
        *(undefined4 *)(param_1 + 8) = uVar5;
        Vector_CopyBackward_8(param_2,iVar3,local_1c,param_2);
        Vector_FillN_8((int *)param_2,(int *)(local_18 + param_2),local_24);
      }
    }
  }
  piVar1 = (int *)(local_24[1] + -4);
  LOCK();
  iVar3 = *piVar1;
  *piVar1 = *piVar1 + -1;
  UNLOCK();
  if (iVar3 + -1 < 1) {
    (**(code **)(**(int **)(local_24[1] + -0x10) + 4))((undefined4 *)(local_24[1] + -0x10));
  }
  piVar1 = (int *)(local_24[0] + -4);
  LOCK();
  iVar3 = *piVar1;
  *piVar1 = *piVar1 + -1;
  UNLOCK();
  if (iVar3 == 1 || iVar3 + -1 < 0) {
    (**(code **)(**(int **)(local_24[0] + -0x10) + 4))((undefined4 *)(local_24[0] + -0x10));
  }
  return;
}
