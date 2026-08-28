/* FUN_005432f0 - 0x005432f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REG FIX (2026-08-28): the whole function is
 * `mov eax,0x794e14 / jmp 0x4154b0`, i.e. it exists only to hand
 * DAT_00794e14 to StringMap_RemoveAll_CString through
 * thunk_FUN_00415560. Registered
 * with _atexit by FUN_00540f00, so it stays a no-argument function
 * itself - only the value it forwards was missing.
 */
#include "ghidra_types.h"


void FUN_005432f0(void)

{
  thunk_FUN_00415560((int *)&DAT_00794e14);
  return;
}

