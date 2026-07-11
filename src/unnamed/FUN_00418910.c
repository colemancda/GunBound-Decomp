/* FUN_00418910 - 0x00418910 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00418910(int param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_14 [8];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_00538327;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  local_4 = 2;
  if (*(int *)(param_1 + 0x6ac) != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  local_4 = 1;
  if (*(int *)(param_1 + 0x47c) != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  local_4 = 0;
  if (*(int *)(param_1 + 600) != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  local_4 = 0xffffffff;
  if (*(int *)(param_1 + 0x34) != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

