/* Vector_FillN_12 - 0x00503eb0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-30, CERTAIN (was FUN_00503eb0).  The fill member of the
 * 0x12-byte element vector: assign the element at EDX into every slot of
 * [EAX, ECX), stepping 0x12. Like Vector_FillN_1e/_34 it is std::fill
 * over a RANGE despite the family's FillN name, which this tree uses for
 * this slot; the suffix is the element size.
 *
 * The slot is fixed by its one caller, FUN_00502b70 (the 0x12 vector's
 * _Insert_n, max_size 0xe38e38e), which calls it at 0x502dfa as the
 * shared tail of the append-overlap and shift arms - the same
 * `fill(_Where, ..., _Tmp)` that ends Vector_InsertN_1e and
 * Vector_InsertN_34 - with EDX = [ebp-0x28], the by-value element copy
 * made at entry. Assignment here is a plain 16+2-byte member copy, where
 * the construction helpers (Vector_UninitCopy_12, Vector_UninitFillN_12)
 * copy the counted name record by its length byte: an element type with
 * a user copy constructor and the default operator=, as in the _1e
 * family, and the same 16+2 move Vector_CopyBackward_12 makes.
 *
 * REGISTER ARGUMENT RECOVERED (2026-10-30): EAX, the range start, is read
 * at entry (`cmp eax,ecx`) - promoted to the trailing regEax. The one
 * call site passed no arguments and now passes the per-arm range.
 */
#include "ghidra_types.h"


void __fastcall Vector_FillN_12(undefined4 *param_1,undefined4 *param_2,undefined4 *regEax)

{
  undefined4 *in_EAX = regEax;
  
  for (; in_EAX != param_1; in_EAX = (undefined4 *)((int)in_EAX + 0x12)) {
    *in_EAX = *param_2;
    in_EAX[1] = param_2[1];
    in_EAX[2] = param_2[2];
    in_EAX[3] = param_2[3];
    *(undefined2 *)(in_EAX + 4) = *(undefined2 *)(param_2 + 4);
  }
  return;
}

