/* Vector_UninitFillN_34 - 0x00504160 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED-REG FIX (2026-08-28): fills regEax copies of one 0x34-byte
 * record into the array starting at param_1.
 *
 * ECX -> param_1  the destination cursor (`mov esi,ecx` at 0x504163),
 *                 advanced by 0x34 per element.
 * EDX -> param_2  PHANTOM: written at 0x504174 (`mov edx,ebx`) before
 *                 any read.
 * [esp+4]
 *     -> param_3  a stack word every caller pushes and clears with
 *                 `add esp,4`, and that this function never reads - the
 *                 unused allocator argument of the STL _Ufill shape.
 * EAX -> regEax   the element COUNT (`test eax,eax` at 0x504160 is the
 *                 first instruction, and `mov edi,eax` at 0x504168 makes
 *                 it the loop counter).
 * EBX -> regEbx   the record being copied. `lea ebx,[ebx]` at 0x50416a
 *                 is a three-byte alignment NOP, not a write, so EBX is
 *                 read-before-written like the other two.
 *
 * The existing call in Vector_PushBack_34 was mis-slotted, not merely short:
 * it passed that function's param_1 into ECX, but the original puts the
 * VECTOR'S END POINTER there (`mov ecx,esi` with esi = *(param_1+8) at
 * 0x502854) and pushes param_1 as the ignored stack word instead.
 *
 * NAMED (2026-08-28): VC7.1 <memory>'s
 * `_Uninit_fill_n(_First, _Count, _Val, _Al)` for the 0x34-byte element -
 * `for (; 0 < _Count; --_Count, ++_First) _Al.construct(_First, _Val);` -
 * which is this loop exactly, with Vector_CopyElement_34 as the
 * construct. The stack word nobody reads is that `_Al&`, an empty
 * allocator object that still takes an argument slot; every caller
 * pushes it and drops it again with `add esp,4`.
 *
 * The count-vs-range split is settled from outside, not from the body:
 * Vector_PushBack_34 calls this with a literal 1 for the whole-array
 * case, and Vector_InsertN_34 calls it with its own element count, while
 * the range twin Vector_UninitCopy_34 takes a [first,last) pair instead.
 *
 * Named Vector_UninitFillN_34 and not reusing Vector_FillN_34: that one
 * is a different function (0x503ef0) and a different half of the insert,
 * a flat 0xd-dword ASSIGNMENT over live elements, where this one
 * CONSTRUCTS into raw storage through the element's copy constructor.
 */
#include "ghidra_types.h"


void __fastcall Vector_UninitFillN_34(int param_1,undefined4 param_2,undefined4 param_3,int regEax,
                             undefined4 *regEbx)

{
  int in_EAX = regEax;
  
  for (; in_EAX != 0; in_EAX = in_EAX + -1) {
    if (param_1 != 0) {
      Vector_CopyElement_34(0,regEbx,(undefined4 *)param_1);
    }
    param_1 = param_1 + 0x34;
  }
  return;
}

