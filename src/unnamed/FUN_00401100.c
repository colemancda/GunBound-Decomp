/* FUN_00401100 - 0x00401100 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __fastcall FUN_00401100(LPCRITICAL_SECTION param_1)

{
  undefined4 local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_00557fd8;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00528184) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  local_8 = 0;
  InitializeCriticalSection(param_1);
  return 0;
}

