/* FUN_004abb70 - 0x004abb70 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_004abb70(undefined4 *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  puStack_8 = &LAB_005392af;
  *unaff_FS_OFFSET = &local_c;
  param_1[1] = 0x186aa;
  param_1[2] = 0;
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
  *param_1 = &PTR_FUN_005565cc;
  *(undefined1 *)(param_1 + 0x9b) = 0;
  param_1[0x18] = 0;
  EncodeOutgoingPacketField(0);
  local_4._0_1_ = 1;
  *(undefined1 *)(param_1 + 0x124) = 0;
  param_1[0xa1] = 0;
  EncodeOutgoingPacketField(0);
  local_4._0_1_ = 2;
  *(undefined1 *)(param_1 + 0x1ad) = 0;
  param_1[0x12a] = 0;
  EncodeOutgoingPacketField(0);
  local_4 = CONCAT31(local_4._1_3_,3);
  param_1[0x11] = 0x10e;
  param_1[0x12] = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

