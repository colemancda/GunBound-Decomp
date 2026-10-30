/* FUN_00500f70 - 0x00500f70 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX RECOVERED (2026-10-30): the body is a bare `jmp 0x500f80`, so
 * EAX (the node StringMap_FreeNode_ac passes) goes straight through
 * to FUN_00500f80.  Ghidra had inlined the target and dropped EAX.
 */
#include "ghidra_types.h"


void thunk_FUN_00500f80(int regEax)

{
  FUN_00500f80(regEax);
  return;
}

