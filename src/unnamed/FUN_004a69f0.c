/* FUN_004a69f0 - 0x004a69f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004a69f0(undefined4 *param_1)

{
  undefined1 local_14 [8];
  undefined4 local_c;
  undefined1 *puStack_8;
  uint local_4;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00537d93) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  *param_1 = &PTR_FUN_00556510;
  local_4 = 1;
  if (param_1[0x9c] != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = local_4 & 0xffffff00;
  if (param_1[0x13] != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  *param_1 = &PTR_LAB_0055752c;
  return;
}

