/* FUN_00503710 - 0x00503710 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int * FUN_00503710(int *param_1)

{
  int iVar1;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00537a58) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  FUN_0043de10();
  *param_1 = iVar1 + 0x10;
  local_4 = 0;
  FUN_0043de10();
  param_1[1] = iVar1 + 0x10;
  return param_1;
}

