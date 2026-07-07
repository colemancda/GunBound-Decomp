/* FUN_00443ed0 - 0x00443ed0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00443ed0(undefined4 *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_14 [8];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_0053ad09;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  *param_1 = &vtable_State07_AvatarStore;
  local_4 = 10;
  FUN_004254a0();
  local_4._0_1_ = 9;
  if (param_1[0xc971] != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 8;
  _eh_vector_destructor_iterator_(param_1 + 0xc522,0x224,8,FUN_0040a2a0);
  local_4._0_1_ = 7;
  FUN_00443dc0(param_1 + 0xc2ef);
  local_4._0_1_ = 6;
  if (param_1[0xc26a] != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 5;
  if (param_1[0xc1e1] != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 4;
  if (param_1[0xc158] != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 3;
  _eh_vector_destructor_iterator_(param_1 + 0x36d7,0x17e4,0x15,FUN_004254a0);
  local_4._0_1_ = 2;
  _eh_vector_destructor_iterator_(param_1 + 0x116,0x17e4,9,FUN_004254a0);
  local_4._0_1_ = 1;
  if (param_1[0x8f] != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4 = (uint)local_4._1_3_ << 8;
  if (param_1[6] != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  *param_1 = &PTR_LAB_00553fb0;
  *unaff_FS_OFFSET = local_c;
  return;
}

