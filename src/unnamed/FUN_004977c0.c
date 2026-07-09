/* FUN_004977c0 - 0x004977c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_004977c0(undefined4 *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053c0f8;
  *unaff_FS_OFFSET = &local_c;
  FUN_00454dc0(param_1,0x186a3);
  local_4 = 0;
  *param_1 = &PTR_FUN_005563f0;
  *(undefined1 *)(param_1 + 0x107d) = 0;
  param_1[0xffa] = 0;
  EncodeOutgoingPacketField(0);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),1);
  *(undefined1 *)(param_1 + 0x1106) = 0;
  param_1[0x1083] = 0;
  EncodeOutgoingPacketField(0);
  *(undefined1 *)(param_1 + 0xfed) = 0;
  param_1[0xfee] = 0;
  param_1[0xfec] = 0;
  param_1[0xff0] = 0;
  *(undefined1 *)(param_1 + 0xff1) = 0;
  param_1[0xff4] = 0;
  param_1[0xff3] = 0xffffffff;
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

