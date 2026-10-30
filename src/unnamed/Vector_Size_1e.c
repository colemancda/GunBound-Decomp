/* Vector_Size_1e - 0x00502ad0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-30, CERTAIN (was FUN_00502ad0).  VC7.1 Dinkumware
 * std::vector<T>::size() for a 0x1e-byte T, the exact twin of
 * Vector_Size_12 (0x4fdc30) one stride up: `_Myfirst == 0 ? 0 :
 * (_Mylast - _Myfirst) / 0x1e` with _Myfirst at +4, _Mylast at +8. The
 * /0x1e is the 0x88888889 multiply, `add edx,ecx`, `sar edx,4` - the
 * same divide Vector_InsertN_1e and Vector_PushBack_1e inline.
 *
 * The operand shapes come from its one caller, Vector_InsertN_1e
 * (0x5033e0), the 0x1e vector's _Insert_n: it calls this at 0x5034df
 * exactly where _Insert_n has `if (_Capacity < size() + _Count)
 * _Capacity = size() + _Count;`, with ECX = ESI = that function's
 * [ebp+8], the vector - the same spot Vector_InsertN_12 calls
 * Vector_Size_12. Suffix = element size, as in the rest of the family.
 *
 * `this` RESTORED at that call (2026-10-30): the port called it with no
 * arguments.
 */
#include "ghidra_types.h"


int __fastcall Vector_Size_1e(int param_1)

{
  if (*(int *)(param_1 + 4) == 0) {
    return 0;
  }
  return (*(int *)(param_1 + 8) - *(int *)(param_1 + 4)) / 0x1e;
}

