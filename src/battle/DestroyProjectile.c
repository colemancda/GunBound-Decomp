/* DestroyProjectile - 0x00455570 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void DestroyProjectile(undefined4 *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_14 [8];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_0053804d;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  *param_1 = &PTR_FUN_00555c34;
  local_4 = 0x1c;
  if (param_1[0xf60] != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 0x1b;
  if (param_1[0xed7] != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 0x1a;
  if (param_1[0xe4d] != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 0x19;
  if (param_1[0xd80] != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 0x18;
  if (param_1[0xcf7] != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 0x17;
  if (param_1[0xc6b] != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 0x16;
  if (param_1[0xbe2] != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 0x15;
  if (param_1[0xb59] != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 0x14;
  if (param_1[0xad0] != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 0x13;
  if (param_1[0xa47] != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 0x12;
  if (param_1[0x9be] != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 0x11;
  if (param_1[0x935] != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 0x10;
  if (param_1[0x8ac] != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 0xf;
  if (param_1[0x823] != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 0xe;
  if (param_1[0x79a] != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 0xd;
  if (param_1[0x710] != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 0xc;
  if (param_1[0x687] != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 0xb;
  if (param_1[0x5fe] != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 10;
  if (param_1[0x575] != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 9;
  if (param_1[0x4ec] != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 8;
  if (param_1[0x463] != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 7;
  if (param_1[0x3da] != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 6;
  if (param_1[0x34b] != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 5;
  if (param_1[0x2c2] != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 4;
  if (param_1[0x239] != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 3;
  if (param_1[0x1b0] != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 2;
  if (param_1[0x127] != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 1;
  if (param_1[0x9e] != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  local_4 = 0;
  if (param_1[0x15] != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_14);
  }
  *param_1 = &PTR_LAB_0055752c;
  *unaff_FS_OFFSET = local_c;
  return;
}

