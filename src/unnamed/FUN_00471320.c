/* FUN_00471320 - 0x00471320 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_00471320(undefined4 *param_1)

{
  byte bVar1;
  int iVar2;
  byte bVar3;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  puStack_8 = &LAB_00537eb1;
  *unaff_FS_OFFSET = &local_c;
  param_1[1] = 0x1f5;
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
  *param_1 = &PTR_FUN_00555edc;
  FUN_00406440();
  *(undefined1 *)(param_1 + 0x97) = 0;
  param_1[0x14] = 0;
  EncodeOutgoingPacketField(0);
  local_4._0_1_ = 1;
  *(undefined1 *)(param_1 + 0x120) = 0;
  param_1[0x9d] = 0;
  EncodeOutgoingPacketField(0);
  local_4 = CONCAT31(local_4._1_3_,2);
  *(undefined1 *)(param_1 + 0x1aa) = 0;
  param_1[0x127] = 0;
  EncodeOutgoingPacketField(0);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = _rand();
  *(byte *)(param_1 + 0xe) = (byte)iVar2;
  iVar2 = _rand();
  bVar1 = *(byte *)(param_1 + 0xe);
  *(byte *)((int)param_1 + 0x39) = (byte)iVar2;
  bVar3 = bVar1 & 7;
  bVar3 = ~('\x01' << bVar3) & (byte)iVar2 | '\0' << bVar3;
  *(byte *)((int)param_1 + 0x39) = bVar3;
  *(byte *)((int)param_1 + 0x3a) = bVar3 + bVar1 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

