/* FUN_00418540 - 0x00418540 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __fastcall FUN_00418540(int param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053852c;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  *(undefined1 *)(param_1 + 800) = 0;
  *(undefined4 *)(param_1 + 0x114) = 0;
  EncodeOutgoingPacketField(0);
  local_4 = 0;
  *(undefined1 *)(param_1 + 0x544) = 0;
  *(undefined4 *)(param_1 + 0x338) = 0;
  EncodeOutgoingPacketField(0);
  SUBFIELD(local_4,0,undefined1) = 1;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x548),0x224,7,FUN_0040a280,ScrubChecksumGuard);
  SUBFIELD(local_4,0,undefined1) = 2;
  *(undefined1 *)(param_1 + 0x1664) = 0;
  *(undefined4 *)(param_1 + 0x1458) = 0;
  EncodeOutgoingPacketField(0);
  SUBFIELD(local_4,0,undefined1) = 3;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x1668),0x224,8,FUN_0040a280,ScrubChecksumGuard);
  SUBFIELD(local_4,0,undefined1) = 4;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x2788),0x224,8,FUN_0040a280,ScrubChecksumGuard);
  SUBFIELD(local_4,0,undefined1) = 5;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x38a8),0x224,8,FUN_0040a280,ScrubChecksumGuard);
  SUBFIELD(local_4,0,undefined1) = 6;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x49c8),0x224,8,FUN_0040a280,ScrubChecksumGuard);
  SUBFIELD(local_4,0,undefined1) = 7;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x5ae8),0x224,8,FUN_0040a280,ScrubChecksumGuard);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),8);
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x6c08),0x224,8,FUN_0040a280,ScrubChecksumGuard);
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

