/* FUN_004f1da0 - 0x004f1da0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004f1da0(int param_1)

{
  void *pvVar1;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00537838) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  local_4 = 0;
  FUN_004f1e20(param_1);
  local_4 = 0xffffffff;
  pvVar1 = *(void **)(param_1 + 0x150);
  if (pvVar1 != (void *)0x0) {
    _eh_vector_destructor_iterator_(pvVar1,0x160,*(int *)((int)pvVar1 + -4),FUN_004f1d40);
    _free((void *)((int)pvVar1 + -4));
  }
  *(undefined4 *)(param_1 + 0x150) = 0;
  return;
}

