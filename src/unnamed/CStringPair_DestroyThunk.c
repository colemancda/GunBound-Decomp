/* CStringPair_DestroyThunk - 0x00415880 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-08-28): the bare-jmp forward to CStringPair_Destroy
 * (0x415890, was FUN_00415890); its one caller is
 * StringMap_FreeNode_CString. Thunk-suffix naming per
 * WorkerThreadProcThunk.
 *
 * DROPPED-REG FIX (2026-08-28): 0x415880 is a bare `jmp 0x415890`, so
 * ESI passes through untouched; Ghidra had decompiled the target's body
 * inline here, which this port now expresses as the forward it is. */
#include "ghidra_types.h"


void CStringPair_DestroyThunk(int regEsi)

{
  CStringPair_Destroy(regEsi);
  return;
}

