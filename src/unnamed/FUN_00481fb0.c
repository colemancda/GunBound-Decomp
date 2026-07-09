/* FUN_00481fb0 - 0x00481fb0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_00481fb0(undefined4 *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  puStack_8 = &LAB_00537d93;
  *unaff_FS_OFFSET = &local_c;
  param_1[1] = 0x1f7;
  param_1[2] = 0xffffffff;
  param_1[3] = 0;
  param_1[4] = 0;
  *(undefined1 *)(param_1 + 5) = 0;
  *(undefined1 *)((int)param_1 + 0x15) = 0;
  param_1[6] = 0xffffffff;
  param_1[7] = 0;
  *(undefined1 *)(param_1 + 8) = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  param_1[9] = 0xffffffff;
  local_4 = 0;
  *param_1 = &PTR_FUN_00556194;
  *(undefined1 *)(param_1 + 0x96) = 0;
  param_1[0x13] = 0;
  EncodeOutgoingPacketField(0);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),1);
  *(undefined1 *)(param_1 + 0x11f) = 0;
  param_1[0x9c] = 0;
  EncodeOutgoingPacketField(0);
  param_1[0x120] = 0;
  param_1[0x121] = 0xff;
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

