/* FUN_004e9ad0 - 0x004e9ad0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX RECOVERED (2026-08-25): the static object DAT_00f22518, handed over by the
 * CRT atexit destructor thunk at 0x543940 (`mov eax,<obj>; jmp 0x4e9ad0`).
 * A `jmp rel32` from an unported thunk is invisible both to an E8-relative
 * call scan and to a search for the address as a stored dword, which is how
 * this first looked like an unreachable function.
 */
#include "ghidra_types.h"


void FUN_004e9ad0(undefined4 *regEax)

{
  FUN_004e9af0(regEax);
  FUN_004e9520();
  return;
}

