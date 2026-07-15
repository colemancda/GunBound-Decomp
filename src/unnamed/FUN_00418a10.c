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
  /* FIXED (2026-07-15): dropped `self` args - angr-confirmed at
   * 0x418a3d/0x418a56/.../0x418b68 (`mov edi,esi` then a run of
   * `lea edi,[esi+N]`, esi = this file's own param_1, set via `mov
   * esi,ecx` in the prologue) - 10 distinct CValueGuard cells at
   * param_1+0/0x224/0x448/0x66c/0x8a4/0xac8/0xcec/0xf10/0x1134/0x1358,
   * each confirmed by the activeFlag(+0x220)/tableHandle(+0x14)
   * zero-write pair immediately above its own call. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1, 0);
  local_4 = 0;
  *(undefined1 *)(param_1 + 0x444) = 0;
  *(undefined4 *)(param_1 + 0x238) = 0;
  EncodeOutgoingPacketField(param_1 + 0x224, 0);
  SUBFIELD(local_4,0,undefined1) = 1;
  *(undefined1 *)(param_1 + 0x668) = 0;
  *(undefined4 *)(param_1 + 0x45c) = 0;
  EncodeOutgoingPacketField(param_1 + 0x448, 0);
  SUBFIELD(local_4,0,undefined1) = 2;
  *(undefined1 *)(param_1 + 0x88c) = 0;
  *(undefined4 *)(param_1 + 0x680) = 0;
  EncodeOutgoingPacketField(param_1 + 0x66c, 0);
  SUBFIELD(local_4,0,undefined1) = 3;
  InitGuardedBool();
  InitGuardedBool();
  InitGuardedBool();
  InitGuardedBool();
  InitGuardedBool();
  InitGuardedBool();
  *(undefined1 *)(param_1 + 0xac4) = 0;
  *(undefined4 *)(param_1 + 0x8b8) = 0;
  EncodeOutgoingPacketField(param_1 + 0x8a4, 0);
  SUBFIELD(local_4,0,undefined1) = 4;
  *(undefined1 *)(param_1 + 0xce8) = 0;
  *(undefined4 *)(param_1 + 0xadc) = 0;
  EncodeOutgoingPacketField(param_1 + 0xac8, 0);
  SUBFIELD(local_4,0,undefined1) = 5;
  *(undefined1 *)(param_1 + 0xf0c) = 0;
  *(undefined4 *)(param_1 + 0xd00) = 0;
  EncodeOutgoingPacketField(param_1 + 0xcec, 0);
  SUBFIELD(local_4,0,undefined1) = 6;
  *(undefined1 *)(param_1 + 0x1130) = 0;
  *(undefined4 *)(param_1 + 0xf24) = 0;
  EncodeOutgoingPacketField(param_1 + 0xf10, 0);
  SUBFIELD(local_4,0,undefined1) = 7;
  *(undefined1 *)(param_1 + 0x1354) = 0;
  *(undefined4 *)(param_1 + 0x1148) = 0;
  EncodeOutgoingPacketField(param_1 + 0x1134, 0);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),8);
  *(undefined1 *)(param_1 + 0x1578) = 0;
  *(undefined4 *)(param_1 + 0x136c) = 0;
  EncodeOutgoingPacketField(param_1 + 0x1358, 0);
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

