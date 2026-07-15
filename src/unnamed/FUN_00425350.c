/* FUN_00425350 - 0x00425350 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __fastcall FUN_00425350(int param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005381d6;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  *(undefined1 *)(param_1 + 0x220) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  /* FIXED (2026-07-15): dropped `self` args - angr-confirmed at
   * 0x42537d/0x425396/.../0x425480 (`mov edi,esi` then a run of
   * `lea edi,[esi+N]`, esi = this file's own param_1) - 11 distinct
   * CValueGuard cells at param_1+0/0x23c/0x460/0x684/0x8a8/0xacc/0xcf0/
   * 0xf14/0x1138/0x135c/0x1580, each confirmed by the activeFlag(+0x220)/
   * tableHandle(+0x14) zero-write pair immediately above its own call.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1, 0);
  local_4 = 0;
  *(undefined1 *)(param_1 + 0x45c) = 0;
  *(undefined4 *)(param_1 + 0x250) = 0;
  EncodeOutgoingPacketField(param_1 + 0x23c, 0);
  SUBFIELD(local_4,0,undefined1) = 1;
  *(undefined1 *)(param_1 + 0x680) = 0;
  *(undefined4 *)(param_1 + 0x474) = 0;
  EncodeOutgoingPacketField(param_1 + 0x460, 0);
  SUBFIELD(local_4,0,undefined1) = 2;
  *(undefined1 *)(param_1 + 0x8a4) = 0;
  *(undefined4 *)(param_1 + 0x698) = 0;
  EncodeOutgoingPacketField(param_1 + 0x684, 0);
  SUBFIELD(local_4,0,undefined1) = 3;
  *(undefined1 *)(param_1 + 0xac8) = 0;
  *(undefined4 *)(param_1 + 0x8bc) = 0;
  EncodeOutgoingPacketField(param_1 + 0x8a8, 0);
  SUBFIELD(local_4,0,undefined1) = 4;
  *(undefined1 *)(param_1 + 0xcec) = 0;
  *(undefined4 *)(param_1 + 0xae0) = 0;
  EncodeOutgoingPacketField(param_1 + 0xacc, 0);
  SUBFIELD(local_4,0,undefined1) = 5;
  *(undefined1 *)(param_1 + 0xf10) = 0;
  *(undefined4 *)(param_1 + 0xd04) = 0;
  EncodeOutgoingPacketField(param_1 + 0xcf0, 0);
  SUBFIELD(local_4,0,undefined1) = 6;
  *(undefined1 *)(param_1 + 0x1134) = 0;
  *(undefined4 *)(param_1 + 0xf28) = 0;
  EncodeOutgoingPacketField(param_1 + 0xf14, 0);
  SUBFIELD(local_4,0,undefined1) = 7;
  *(undefined1 *)(param_1 + 0x1358) = 0;
  *(undefined4 *)(param_1 + 0x114c) = 0;
  EncodeOutgoingPacketField(param_1 + 0x1138, 0);
  SUBFIELD(local_4,0,undefined1) = 8;
  *(undefined1 *)(param_1 + 0x157c) = 0;
  *(undefined4 *)(param_1 + 0x1370) = 0;
  EncodeOutgoingPacketField(param_1 + 0x135c, 0);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),9);
  *(undefined1 *)(param_1 + 0x17a0) = 0;
  *(undefined4 *)(param_1 + 0x1594) = 0;
  EncodeOutgoingPacketField(param_1 + 0x1580, 0);
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

