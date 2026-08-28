/* FUN_00415890 - 0x00415890 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
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


void FUN_00415890(int regEsi)

{
  FUN_00405320(regEsi + 4);
  FUN_00405320(regEsi);
  return;
}

