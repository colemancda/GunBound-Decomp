/* Vector_Copy_12 - 0x005040d0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-30, CERTAIN (was FUN_005040d0).  std::copy over 0x12-byte
 * elements, ascending: assign [ECX, EDX) onto EAX in 0x12 steps - the
 * forward counterpart of Vector_CopyBackward_12, with the same plain
 * 16+2-byte member assignment (and the one Vector_FillN_12 uses). Not a
 * copy of a whole vector; the name pairs with Vector_CopyBackward_*.
 *
 * The identity comes from its one caller, Vector_Erase_12 at 0x5027e2,
 * which is the 0x12 vector's erase(_Where): it passes ECX = _Where +
 * 0x12 (`lea ecx,[edi+0x12]`), EDX = _Mylast (`mov edx,[esi+8]`) and EAX
 * = _Where, then drops _Mylast by 0x12 - VC7.1's `copy(_Where + 1,
 * end(), _Where); --_Mylast;`. The stride and the member layout are
 * those of the rest of the 0x12 family.
 */
#include "ghidra_types.h"


void __fastcall Vector_Copy_12(undefined4 *param_1,undefined4 *param_2,undefined4 *regEax)

{
  
  for (; param_1 != param_2; param_1 = (undefined4 *)((int)param_1 + 0x12)) {
    *regEax = *param_1;
    regEax[1] = param_1[1];
    regEax[2] = param_1[2];
    regEax[3] = param_1[3];
    *(undefined2 *)(regEax + 4) = *(undefined2 *)(param_1 + 4);
    regEax = (undefined4 *)((int)regEax + 0x12);
  }
  return;
}

