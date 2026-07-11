/* FUN_00418b90 - 0x00418b90 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00418b90(int param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_14 [8];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_00538258;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  local_4 = 8;
  if (*(int *)(param_1 + 0x136c) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 7;
  if (*(int *)(param_1 + 0x1148) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 6;
  if (*(int *)(param_1 + 0xf24) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 5;
  if (*(int *)(param_1 + 0xd00) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 4;
  if (*(int *)(param_1 + 0xadc) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 3;
  if (*(int *)(param_1 + 0x8b8) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 2;
  if (*(int *)(param_1 + 0x680) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 1;
  if (*(int *)(param_1 + 0x45c) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 0;
  if (*(int *)(param_1 + 0x238) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 0xffffffff;
  if (*(int *)(param_1 + 0x14) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

