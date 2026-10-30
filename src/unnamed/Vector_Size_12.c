/* Vector_Size_12 - 0x004fdc30 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-30, CERTAIN (was FUN_004fdc30).  VC7.1 Dinkumware
 * std::vector<T>::size() for an 0x12-byte T: `_Myfirst == 0 ? 0 :
 * _Mylast - _Myfirst`, with _Myfirst at +4 and _Mylast at +8 (the
 * allocator word at +0) - the layout the Vector_*_1e/_34/_8 family
 * already uses.  The /0x12 is the 0x38e38e39 multiply plus `sar edx,2`.
 * The operand shapes come from its one caller, FUN_00502b70, which is
 * that vector's _Insert_n: it checks n against max_size() - size() with
 * max_size = 0xe38e38e (0xffffffff / 0x12), inlines capacity() from +0xc
 * and size() from +8 with the same divide, and calls this function at
 * 0x502c74 exactly where _Insert_n has `if (_Capacity < size() + _Count)
 * _Capacity = size() + _Count;` - the result plus n becomes the new
 * capacity, times 0x12 is the operator_new size.  Suffix = element size,
 * as in Vector_InsertN_1e.
 *
 * `this` RESTORED at that call (2026-10-30): `mov ecx,edi` at 0x502c72,
 * EDI = [ebp+8] = the caller's param_2, the vector.  The port called it
 * with no arguments.
 */
#include "ghidra_types.h"


int __fastcall Vector_Size_12(int param_1)

{
  if (*(int *)(param_1 + 4) == 0) {
    return 0;
  }
  return (*(int *)(param_1 + 8) - *(int *)(param_1 + 4)) / 0x12;
}

