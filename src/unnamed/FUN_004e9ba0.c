/* FUN_004e9ba0 - 0x004e9ba0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
  *
 * FIX (2026-11-03): the tail `jmp 0x4f33b0` (0x4e9ba6) keeps ECX = this;
 * FUN_004f33b0 now receives it. Callers: FUN_004e9b80 (this) and the
 * excluded CRT atexit stub 0x543290 (ECX = 0xe9b1e0).
 */
#include "ghidra_types.h"


void __fastcall FUN_004e9ba0(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_00557300;
  FUN_004f33b0(param_1);
  return;
}

