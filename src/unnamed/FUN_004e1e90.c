/* FUN_004e1e90 - 0x004e1e90 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e1e90(int param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_14 [8];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_00537c4e;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  local_4 = 2;
  if (*(int *)(param_1 + 0xf1c) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4 = 1;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x890),0x224,3,FUN_0040a2a0);
  local_4 = 0;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x224),0x224,3,FUN_0040a2a0);
  local_4 = 0xffffffff;
  if (*(int *)(param_1 + 0x14) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

