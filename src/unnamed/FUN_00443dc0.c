/* FUN_00443dc0 - 0x00443dc0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00443dc0(undefined4 *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_14 [8];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_0053808f;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  local_4 = 3;
  if (param_1[0x1ae] != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 2;
  if (param_1[0x125] != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 1;
  if (param_1[0x9c] != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4 = (uint)local_4._1_3_ << 8;
  if (param_1[0x13] != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  *param_1 = &PTR_LAB_0055752c;
  *unaff_FS_OFFSET = local_c;
  return;
}

