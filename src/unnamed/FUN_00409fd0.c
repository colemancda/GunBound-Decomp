/* FUN_00409fd0 - 0x00409fd0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * __thiscall FUN_00409fd0(undefined4 *param_1,undefined4 param_2)

{
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00537868) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  FUN_00525d92();
  local_4 = 0;
  *param_1 = &PTR_FUN_00544b5c;
  param_1[8] = 0;
  param_1[9] = 0xf;
  *(undefined1 *)(param_1 + 4) = 0;
  FUN_0040b9f0(param_2,0,0xffffffff);
  return param_1;
}

