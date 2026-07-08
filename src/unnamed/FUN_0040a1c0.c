/* FUN_0040a1c0 - 0x0040a1c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0040a1c0(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puVar1 = param_1;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00537b5b) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  local_4 = 0;
  _free((void *)*param_1);
  local_4 = 0xffffffff;
  FUN_0040be20(&param_1,*(undefined4 *)puVar1[2],(undefined4 *)puVar1[2]);
  _free((void *)puVar1[2]);
  puVar1[2] = 0;
  puVar1[3] = 0;
  return;
}

