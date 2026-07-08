/* FUN_0044fb40 - 0x0044fb40 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_0044fb40(undefined4 *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  puStack_8 = &LAB_0053ac2d;
  *unaff_FS_OFFSET = &local_c;
  param_1[1] = 0;
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
  *param_1 = &PTR_FUN_00555b38;
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
  *(undefined1 *)(param_1 + 0x232) = 0;
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

