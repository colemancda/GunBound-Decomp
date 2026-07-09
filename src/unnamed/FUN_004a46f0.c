/* FUN_004a46f0 - 0x004a46f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_004a46f0(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053cfc0;
  *unaff_FS_OFFSET = &local_c;
  FUN_00454dc0(param_1,0x186a2);
  param_1[0xfe7] = 0;
  param_1[0x1028] = 0;
  local_4 = 0;
  *param_1 = &PTR_FUN_005564f0;
  *(undefined1 *)(param_1 + 0x10b4) = 0;
  param_1[0x1031] = 0;
  EncodeOutgoingPacketField(0);
  SUBFIELD(local_4,0,undefined1) = 1;
  *(undefined1 *)(param_1 + 0x113d) = 0;
  param_1[0x10ba] = 0;
  EncodeOutgoingPacketField(0);
  SUBFIELD(local_4,0,undefined1) = 2;
  *(undefined1 *)(param_1 + 0x11c6) = 0;
  param_1[0x1143] = 0;
  EncodeOutgoingPacketField(0);
  SUBFIELD(local_4,0,undefined1) = 3;
  *(undefined1 *)(param_1 + 0x124f) = 0;
  param_1[0x11cc] = 0;
  EncodeOutgoingPacketField(0);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),4);
  param_1[0xfe7] = 0;
  param_1[0x102a] = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0xfff0bdc0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

