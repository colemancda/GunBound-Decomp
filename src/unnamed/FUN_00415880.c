/* FUN_00415880 - 0x00415880 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REG FIX (2026-08-28): 0x415880 is a bare `jmp 0x415890`, so
 * ESI passes through untouched; Ghidra had decompiled the target's body
 * inline here, which this port now expresses as the forward it is. */
#include "ghidra_types.h"


void thunk_FUN_00415890(int regEsi)

{
  FUN_00415890(regEsi);
  return;
}

