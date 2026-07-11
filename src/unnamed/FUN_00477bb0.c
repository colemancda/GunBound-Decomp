/* FUN_00477bb0 - 0x00477bb0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_00477bb0(undefined4 *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  byte bVar3;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_00539e53;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  param_1[2] = param_2;
  param_1[1] = 0x186a6;
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
  *param_1 = &PTR_FUN_00555fdc;
  *(undefined1 *)(param_1 + 0x96) = 0;
  param_1[0x13] = 0;
  EncodeOutgoingPacketField(0);
  local_4 = 1;
  *(undefined1 *)(param_1 + 0x11f) = 0;
  param_1[0x9c] = 0;
  EncodeOutgoingPacketField(0);
  local_4 = 2;
  *(undefined1 *)(param_1 + 0x1a8) = 0;
  param_1[0x125] = 0;
  EncodeOutgoingPacketField(0);
  local_4 = 3;
  *(undefined1 *)(param_1 + 0x231) = 0;
  param_1[0x1ae] = 0;
  EncodeOutgoingPacketField(0);
  local_4 = 4;
  *(undefined1 *)(param_1 + 0x2ba) = 0;
  param_1[0x237] = 0;
  EncodeOutgoingPacketField(0);
  local_4 = 5;
  *(undefined1 *)(param_1 + 0x344) = 0;
  param_1[0x2c1] = 0;
  EncodeOutgoingPacketField(0);
  local_4 = 6;
  *(undefined1 *)(param_1 + 0x3cd) = 0;
  param_1[0x34a] = 0;
  EncodeOutgoingPacketField(0);
  local_4 = 7;
  InitGuardedBool();
  InitGuardedBool();
  *(undefined1 *)(param_1 + 0x458) = 0;
  param_1[0x3d5] = 0;
  EncodeOutgoingPacketField(0);
  local_4 = 8;
  *(undefined1 *)(param_1 + 0x4e1) = 0;
  param_1[0x45e] = 0;
  EncodeOutgoingPacketField(0);
  local_4 = 9;
  *(undefined1 *)(param_1 + 0x56a) = 0;
  param_1[0x4e7] = 0;
  EncodeOutgoingPacketField(0);
  local_4 = 10;
  *(undefined1 *)(param_1 + 0x5f3) = 0;
  param_1[0x570] = 0;
  EncodeOutgoingPacketField(0);
  local_4 = 0xb;
  *(undefined1 *)(param_1 + 0x67c) = 0;
  param_1[0x5f9] = 0;
  EncodeOutgoingPacketField(0);
  local_4 = 0xc;
  *(undefined1 *)(param_1 + 0x705) = 0;
  param_1[0x682] = 0;
  EncodeOutgoingPacketField(0);
  local_4 = 0xd;
  InitGuardedBool();
  *(undefined1 *)(param_1 + 0x78f) = 0;
  param_1[0x70c] = 0;
  EncodeOutgoingPacketField(0);
  param_1[0x790] = 0;
  param_1[0x791] = 0;
  param_1[0x792] = 0;
  param_1[0x793] = 0;
  local_4 = 0xf;
  *(undefined1 *)(param_1 + 0x81c) = 0;
  param_1[0x799] = 0;
  EncodeOutgoingPacketField(0);
  local_4 = 0x10;
  *(undefined1 *)(param_1 + 0x8a5) = 0;
  param_1[0x822] = 0;
  EncodeOutgoingPacketField(0);
  local_4 = 0x11;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  param_1[699] = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = _rand();
  *(char *)(param_1 + 0x3ce) = (char)iVar2;
  iVar2 = _rand();
  *(byte *)((int)param_1 + 0xf39) = (byte)iVar2;
  bVar3 = ~('\x01' << (*(byte *)(param_1 + 0x3ce) & 7)) & (byte)iVar2 |
          '\0' << (*(byte *)(param_1 + 0x3ce) & 7);
  *(byte *)((int)param_1 + 0xf39) = bVar3;
  *(byte *)((int)param_1 + 0xf3a) = bVar3 + *(char *)(param_1 + 0x3ce) + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = _rand();
  *(char *)((int)param_1 + 0xf3b) = (char)iVar2;
  iVar2 = _rand();
  *(byte *)(param_1 + 0x3cf) = (byte)iVar2;
  bVar3 = *(byte *)((int)param_1 + 0xf3b) & 7;
  bVar3 = ~('\x01' << bVar3) & (byte)iVar2 | '\0' << bVar3;
  *(byte *)(param_1 + 0x3cf) = bVar3;
  *(byte *)((int)param_1 + 0xf3d) = *(byte *)((int)param_1 + 0xf3b) + bVar3 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = _rand();
  *(char *)(param_1 + 0x706) = (char)iVar2;
  iVar2 = _rand();
  *(byte *)((int)param_1 + 0x1c19) = (byte)iVar2;
  bVar3 = *(byte *)(param_1 + 0x706) & 7;
  bVar3 = ~('\x01' << bVar3) & (byte)iVar2 | '\0' << bVar3;
  *(byte *)((int)param_1 + 0x1c19) = bVar3;
  *(byte *)((int)param_1 + 0x1c1a) = *(byte *)(param_1 + 0x706) + bVar3 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

