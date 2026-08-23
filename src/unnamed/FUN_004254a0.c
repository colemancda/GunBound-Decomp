/* FUN_004254a0 - 0x004254a0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004254a0(int param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_14 [8];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_00538146;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  local_4 = 9;
  if (*(int *)(param_1 + 0x1594) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(param_1 + 0x1594),&g_valueGuardKeyTable);
    TreeLowerBound(local_14,&g_valueGuardMap);
  }
  local_4 = 8;
  if (*(int *)(param_1 + 0x1370) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(param_1 + 0x1370),&g_valueGuardKeyTable);
    TreeLowerBound(local_14,&g_valueGuardMap);
  }
  local_4 = 7;
  if (*(int *)(param_1 + 0x114c) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(param_1 + 0x114c),&g_valueGuardKeyTable);
    TreeLowerBound(local_14,&g_valueGuardMap);
  }
  local_4 = 6;
  if (*(int *)(param_1 + 0xf28) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(param_1 + 0xf28),&g_valueGuardKeyTable);
    TreeLowerBound(local_14,&g_valueGuardMap);
  }
  local_4 = 5;
  if (*(int *)(param_1 + 0xd04) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(param_1 + 0xd04),&g_valueGuardKeyTable);
    TreeLowerBound(local_14,&g_valueGuardMap);
  }
  local_4 = 4;
  if (*(int *)(param_1 + 0xae0) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(param_1 + 0xae0),&g_valueGuardKeyTable);
    TreeLowerBound(local_14,&g_valueGuardMap);
  }
  local_4 = 3;
  if (*(int *)(param_1 + 0x8bc) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(param_1 + 0x8bc),&g_valueGuardKeyTable);
    TreeLowerBound(local_14,&g_valueGuardMap);
  }
  local_4 = 2;
  if (*(int *)(param_1 + 0x698) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(param_1 + 0x698),&g_valueGuardKeyTable);
    TreeLowerBound(local_14,&g_valueGuardMap);
  }
  local_4 = 1;
  if (*(int *)(param_1 + 0x474) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(param_1 + 0x474),&g_valueGuardKeyTable);
    TreeLowerBound(local_14,&g_valueGuardMap);
  }
  local_4 = 0;
  if (*(int *)(param_1 + 0x250) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(param_1 + 0x250),&g_valueGuardKeyTable);
    TreeLowerBound(local_14,&g_valueGuardMap);
  }
  local_4 = 0xffffffff;
  if (*(int *)(param_1 + 0x14) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(param_1 + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_14,&g_valueGuardMap);
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

