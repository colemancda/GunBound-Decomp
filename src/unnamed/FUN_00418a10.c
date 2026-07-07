/* FUN_00418a10 - 0x00418a10 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __fastcall FUN_00418a10(int param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005382e8;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  *(undefined1 *)(param_1 + 0x220) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  EncodeOutgoingPacketField(0);
  local_4 = 0;
  *(undefined1 *)(param_1 + 0x444) = 0;
  *(undefined4 *)(param_1 + 0x238) = 0;
  EncodeOutgoingPacketField(0);
  local_4._0_1_ = 1;
  *(undefined1 *)(param_1 + 0x668) = 0;
  *(undefined4 *)(param_1 + 0x45c) = 0;
  EncodeOutgoingPacketField(0);
  local_4._0_1_ = 2;
  *(undefined1 *)(param_1 + 0x88c) = 0;
  *(undefined4 *)(param_1 + 0x680) = 0;
  EncodeOutgoingPacketField(0);
  local_4._0_1_ = 3;
  FUN_00406440();
  FUN_00406440();
  FUN_00406440();
  FUN_00406440();
  FUN_00406440();
  FUN_00406440();
  *(undefined1 *)(param_1 + 0xac4) = 0;
  *(undefined4 *)(param_1 + 0x8b8) = 0;
  EncodeOutgoingPacketField(0);
  local_4._0_1_ = 4;
  *(undefined1 *)(param_1 + 0xce8) = 0;
  *(undefined4 *)(param_1 + 0xadc) = 0;
  EncodeOutgoingPacketField(0);
  local_4._0_1_ = 5;
  *(undefined1 *)(param_1 + 0xf0c) = 0;
  *(undefined4 *)(param_1 + 0xd00) = 0;
  EncodeOutgoingPacketField(0);
  local_4._0_1_ = 6;
  *(undefined1 *)(param_1 + 0x1130) = 0;
  *(undefined4 *)(param_1 + 0xf24) = 0;
  EncodeOutgoingPacketField(0);
  local_4._0_1_ = 7;
  *(undefined1 *)(param_1 + 0x1354) = 0;
  *(undefined4 *)(param_1 + 0x1148) = 0;
  EncodeOutgoingPacketField(0);
  local_4 = CONCAT31(local_4._1_3_,8);
  *(undefined1 *)(param_1 + 0x1578) = 0;
  *(undefined4 *)(param_1 + 0x136c) = 0;
  EncodeOutgoingPacketField(0);
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

