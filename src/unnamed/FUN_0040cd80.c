/* FUN_0040cd80 - 0x0040cd80 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0040cd80(undefined4 *param_1)

{
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00537728) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  *param_1 = &PTR_FUN_005520a0;
  local_4 = 0;
  FUN_004f3060(param_1);
  local_4 = 0xffffffff;
  *param_1 = &PTR_FUN_00557534;
  FUN_004f3060(param_1);
  if ((undefined4 *)param_1[1] != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)param_1[1])(1);
  }
  return;
}

