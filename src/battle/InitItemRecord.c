/* InitItemRecord - 0x00418850 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __fastcall InitItemRecord(int param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00538367;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  *(undefined1 *)(param_1 + 0x240) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  EncodeOutgoingPacketField(0);
  local_4 = 0;
  *(undefined1 *)(param_1 + 0x464) = 0;
  *(undefined4 *)(param_1 + 600) = 0;
  EncodeOutgoingPacketField(0);
  local_4 = 1;
  *(undefined1 *)(param_1 + 0x688) = 0;
  *(undefined4 *)(param_1 + 0x47c) = 0;
  EncodeOutgoingPacketField(0);
  local_4 = 2;
  InitGuardedBool();
  InitGuardedBool();
  InitGuardedBool();
  *(undefined1 *)(param_1 + 0x8b8) = 0;
  *(undefined4 *)(param_1 + 0x6ac) = 0;
  EncodeOutgoingPacketField(0);
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

