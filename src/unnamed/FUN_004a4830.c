/* FUN_004a4830 - 0x004a4830 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004a4830(undefined4 *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_14 [8];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_0053bfd2;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  *param_1 = &PTR_FUN_005564f0;
  local_4 = 3;
  if (param_1[0x11cc] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  local_4 = 2;
  if (param_1[0x1143] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  local_4 = 1;
  if (param_1[0x10ba] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  local_4 = 0;
  if (param_1[0x1031] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  local_4 = 0xffffffff;
  *param_1 = &PTR_FUN_005560d0;
  FUN_00455570(param_1);
  *unaff_FS_OFFSET = local_c;
  return;
}

