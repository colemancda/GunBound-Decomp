/* CStringPair_Destroy - 0x00415890 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-08-28): the destructor of one {CStringA, CStringA} pair -
 * two CString handle releases through FUN_00405320, second member first.
 * The name is type-level rather than container-level on purpose: the
 * same instantiation serves BOTH the 8-byte vector family (the sweeps
 * in Vector_DestroyRange_8 and Vector_Tidy_8) and, through the thunk at
 * 0x415880 (CStringPair_DestroyThunk), StringMap_FreeNode_CString's
 * node teardown - naming it for either container would misdescribe the
 * other.
 *
 * (The note below predates the renames of 2026-08-28: FUN_00503110 is
 * now Vector_DestroyRange_8 and FUN_00502a90 is Vector_Tidy_8.)
 *
 * DROPPED-REG FIX (2026-08-28): ESI is an 8-byte {CStringA, CStringA}
 * pair being destroyed - `lea ecx,[esi+4]` at 0x415890 releases the
 * second string, then the tail-jump releases the first, both through
 * FUN_00405320 (the CString handle release: [ecx] is the data pointer,
 * header at -0x10, refcount at -4). Both direct callers hold the cursor
 * in ESI (the 8-byte sweeps in FUN_00503110 and FUN_00502a90), and the
 * thunk at 0x415880 forwards it untouched for
 * StringMap_FreeNode_CString, whose node's pair sits at +0 of its
 * regEax node - the two CStringA releases that pinned that map's value
 * type during naming.
 */
#include "ghidra_types.h"


void CStringPair_Destroy(int regEsi)

{
  FUN_00405320(regEsi + 4);
  FUN_00405320(regEsi);
  return;
}

