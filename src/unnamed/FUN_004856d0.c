/* FUN_004856d0 - 0x004856d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_004856d0(undefined4 *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053c218;
  *unaff_FS_OFFSET = &local_c;
  FUN_00454dc0(param_1,0x186a2);
  local_4 = 0;
  *param_1 = &PTR_FUN_0055620c;
  *(undefined1 *)(param_1 + 0x1071) = 0;
  param_1[0xfee] = 0;
  EncodeOutgoingPacketField(0);
  *(undefined1 *)(param_1 + 0xfe8) = 0;
  param_1[0xfe7] = 0xffffffff;
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

