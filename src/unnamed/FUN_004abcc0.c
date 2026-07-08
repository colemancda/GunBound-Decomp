/* FUN_004abcc0 - 0x004abcc0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004abcc0(undefined4 *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_14 [8];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_00537d71;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  *param_1 = &PTR_FUN_005565cc;
  local_4 = 2;
  if (param_1[0x12a] != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4 = 1;
  if (param_1[0xa1] != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4 = 0;
  if (param_1[0x18] != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  *param_1 = &PTR_LAB_0055752c;
  *unaff_FS_OFFSET = local_c;
  return;
}

