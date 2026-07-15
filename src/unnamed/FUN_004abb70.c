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
  /* FIXED (2026-07-15): dropped `self` args - angr-confirmed at 0x4abbd3/
   * 0x4abbed/0x4abc07/0x4abc2d/0x4abc4c/0x4abc70 (edi loaded from ebp/
   * esi+0x270/esi+0x494/esi+0x270/ebp/esi+0x494 respectively). The
   * zero-write pairs above the first 3 calls match tableHandle(+0x14)/
   * activeFlag(+0x220) for cell bases param_1+0x4c, +0x270, +0x494 - an
   * array of 3 CValueGuard cells (stride 0x224 = sizeof(CValueGuard)); the
   * esi+0x270/esi+0x494 sites confirm esi==param_1 and pin cells 1/2
   * directly. Calls 4/5/6 reuse cell1/cell0/cell2 from calls 2/1/3.
   * `param_1` is `undefined4 *` (scales by 4), so byte offsets are taken
   * via `(int)param_1 + N`. See tools/encodeoutgoingpacketfield_sites.json. */
  *(undefined1 *)(param_1 + 0x9b) = 0;
  param_1[0x18] = 0;
  EncodeOutgoingPacketField((int)param_1 + 0x4c, 0);
  SUBFIELD(local_4,0,undefined1) = 1;
  *(undefined1 *)(param_1 + 0x124) = 0;
  param_1[0xa1] = 0;
  EncodeOutgoingPacketField((int)param_1 + 0x270, 0);
  SUBFIELD(local_4,0,undefined1) = 2;
  *(undefined1 *)(param_1 + 0x1ad) = 0;
  param_1[0x12a] = 0;
  EncodeOutgoingPacketField((int)param_1 + 0x494, 0);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),3);
  param_1[0x11] = 0x10e;
  param_1[0x12] = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((int)param_1 + 0x270, 0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((int)param_1 + 0x4c, 1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((int)param_1 + 0x494, 0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

