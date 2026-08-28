/* FUN_004154b0 - 0x004154b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REG FIX (2026-08-28): 0x4154b0 is a bare `jmp 0x415560`, so
 * EAX passes through untouched and is FUN_00415560's map argument. Its
 * one caller FUN_005432f0 is itself `mov eax,0x794e14 / jmp 0x4154b0`,
 * the atexit destructor for DAT_00794e14.
 */
#include "ghidra_types.h"


void thunk_FUN_00415560(int *regEax)

{
  FUN_00415560(regEax);
  return;
}

