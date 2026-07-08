/* FUN_004af530 - 0x004af530 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_004af530(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053bf92;
  *unaff_FS_OFFSET = &local_c;
  FUN_00454dc0(param_1,0x186a2);
  local_4 = 0;
  *param_1 = &PTR_FUN_00556660;
  *(undefined1 *)(param_1 + 0x10b6) = 0;
  param_1[0x1033] = 0;
  EncodeOutgoingPacketField(0);
  local_4 = 1;
  *(undefined1 *)(param_1 + 0x113f) = 0;
  param_1[0x10bc] = 0;
  EncodeOutgoingPacketField(0);
  local_4 = 2;
  *(undefined1 *)(param_1 + 0x11c8) = 0;
  param_1[0x1145] = 0;
  EncodeOutgoingPacketField(0);
  local_4 = 3;
  *(undefined1 *)(param_1 + 0x1251) = 0;
  param_1[0x11ce] = 0;
  EncodeOutgoingPacketField(0);
  local_4 = 4;
  param_1[0xfe7] = 0;
  param_1[0x1028] = 0;
  param_1[0x102a] = 1000;
  param_1[0x102b] = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0xfff0bdc0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  param_1[0x102c] = 0;
  param_1[0x1252] = 5;
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

