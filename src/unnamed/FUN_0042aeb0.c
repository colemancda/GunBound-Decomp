/* FUN_0042aeb0 - 0x0042aeb0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined2 * FUN_0042aeb0(undefined2 *param_1,undefined2 *param_2)

{
  undefined4 uVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  local_c = *unaff_FS_OFFSET;
  puStack_8 = &LAB_005380ab;
  *unaff_FS_OFFSET = &local_c;
  *param_1 = *param_2;
  *(undefined1 *)(param_1 + 1) = *(undefined1 *)(param_2 + 1);
  *(undefined4 *)(param_1 + 2) = *(undefined4 *)(param_2 + 2);
  *(undefined1 *)(param_1 + 0x114) = 0;
  *(undefined4 *)(param_1 + 0xe) = 0;
  uVar1 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar1);
  local_4 = 0;
  *(undefined1 *)(param_1 + 0x226) = 0;
  *(undefined4 *)(param_1 + 0x120) = 0;
  uVar1 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar1);
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

