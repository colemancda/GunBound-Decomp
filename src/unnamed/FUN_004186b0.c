/* FUN_004186b0 - 0x004186b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004186b0(int param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_14 [8];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_0053844c;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  local_4 = 8;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x6c08),0x224,8,FUN_0040a2a0);
  SUBFIELD(local_4,0,undefined1) = 7;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x5ae8),0x224,8,FUN_0040a2a0);
  SUBFIELD(local_4,0,undefined1) = 6;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x49c8),0x224,8,FUN_0040a2a0);
  SUBFIELD(local_4,0,undefined1) = 5;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x38a8),0x224,8,FUN_0040a2a0);
  SUBFIELD(local_4,0,undefined1) = 4;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x2788),0x224,8,FUN_0040a2a0);
  SUBFIELD(local_4,0,undefined1) = 3;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x1668),0x224,8,FUN_0040a2a0);
  SUBFIELD(local_4,0,undefined1) = 2;
  if (*(int *)(param_1 + 0x1458) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 1;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x548),0x224,7,FUN_0040a2a0);
  local_4 = (uint)SUBFIELD(local_4,1,undefined3) << 8;
  if (*(int *)(param_1 + 0x338) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4 = 0xffffffff;
  if (*(int *)(param_1 + 0x114) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

