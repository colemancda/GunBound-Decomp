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
  /* FIXED (2026-07-15): dropped `self` args - angr-confirmed at 0x44fb9f/
   * 0x44fbb9/0x44fbd3/0x44fbed/0x44fc05/0x44fc29/0x44fc47/0x44fc65 (edi
   * loaded from ebp/esi+0x25c/esi+0x480/esi+0x6a4/ebp/esi+0x25c/esi+0x480/
   * esi+0x6a4 respectively). The zero-write pairs above the first 4 calls
   * match tableHandle(+0x14)/activeFlag(+0x220) for cell bases
   * param_1+0x38, +0x25c, +0x480, +0x6a4 - an array of 4 CValueGuard cells
   * (stride 0x224 = sizeof(CValueGuard)); the esi+0x25c/+0x480/+0x6a4
   * sites confirm esi==param_1 and pin cells 1/2/3 directly. Calls 5-8
   * repeat cells 0/1/2/3 (ebp reused from call 1). `param_1` is
   * `undefined4 *` (scales by 4), so byte offsets are taken via `(int)
   * param_1 + N`. See tools/encodeoutgoingpacketfield_sites.json. */
  *(undefined1 *)(param_1 + 0x96) = 0;
  param_1[0x13] = 0;
  EncodeOutgoingPacketField((int)param_1 + 0x38, 0);
  local_4 = 1;
  *(undefined1 *)(param_1 + 0x11f) = 0;
  param_1[0x9c] = 0;
  EncodeOutgoingPacketField((int)param_1 + 0x25c, 0);
  local_4 = 2;
  *(undefined1 *)(param_1 + 0x1a8) = 0;
  param_1[0x125] = 0;
  EncodeOutgoingPacketField((int)param_1 + 0x480, 0);
  local_4 = 3;
  *(undefined1 *)(param_1 + 0x231) = 0;
  param_1[0x1ae] = 0;
  EncodeOutgoingPacketField((int)param_1 + 0x6a4, 0);
  local_4 = 4;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((int)param_1 + 0x38, 0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((int)param_1 + 0x25c, 0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((int)param_1 + 0x480, 0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((int)param_1 + 0x6a4, 0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(undefined1 *)(param_1 + 0x232) = 0;
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

