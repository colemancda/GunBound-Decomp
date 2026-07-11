/* FUN_00495d60 - 0x00495d60 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00495d60(undefined4 *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_14 [8];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_00539864;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  *param_1 = &PTR_FUN_005563d0;
  local_4 = 3;
  if (param_1[0x1189] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 2;
  if (param_1[0x1100] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 1;
  if (param_1[0x1077] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  local_4 = (uint)SUBFIELD(local_4,1,undefined3) << 8;
  if (param_1[0xfee] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  local_4 = 0xffffffff;
  FUN_00455570(param_1);
  *unaff_FS_OFFSET = local_c;
  return;
}

