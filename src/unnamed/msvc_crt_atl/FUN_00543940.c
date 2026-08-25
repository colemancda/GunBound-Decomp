/* FUN_00543940 - 0x00543940 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * The atexit destructor thunk for DAT_00f22518:
 * `mov eax,0xf22518; jmp 0x4e9ad0`.
 */
#include "ghidra_types.h"


void FUN_00543940(void)

{
  FUN_004e9ad0((undefined4 *)DAT_00f22518);
  return;
}

