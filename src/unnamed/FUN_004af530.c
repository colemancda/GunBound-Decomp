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
  InitProjectile(param_1,0x186a2);
  local_4 = 0;
  *param_1 = &PTR_FUN_00556660;
  /* FIXED (2026-07-15): dropped `self` args - angr-confirmed at 0x4af574/
   * 0x4af590/0x4af5aa/0x4af5c4/0x4af5fc/0x4af625 (edi loaded from
   * esi+0x40b8/ebp/esi+0x4500/esi+0x4724/ebp/esi+0x40b8 respectively). The
   * zero-write pairs just above each of the first 4 calls match
   * tableHandle(+0x14)/activeFlag(+0x220) for cell bases param_1+0x40b8,
   * +0x42dc, +0x4500, +0x4724 - an array of 4 CValueGuard cells (stride
   * 0x224 = sizeof(CValueGuard)); the esi+0x40b8/+0x4500/+0x4724 sites
   * directly confirm esi==param_1 and pin cells 0/2/3. Call 5 reuses ebp
   * (cell 1) from call 2; call 6 is directly given as esi+0x40b8 (cell 0).
   * `param_1` is `undefined4 *` (scales by 4), so byte offsets are taken
   * via `(int)param_1 + N`. See tools/encodeoutgoingpacketfield_sites.json. */
  *(undefined1 *)(param_1 + 0x10b6) = 0;
  param_1[0x1033] = 0;
  EncodeOutgoingPacketField((int)param_1 + 0x40b8, 0);
  local_4 = 1;
  *(undefined1 *)(param_1 + 0x113f) = 0;
  param_1[0x10bc] = 0;
  EncodeOutgoingPacketField((int)param_1 + 0x42dc, 0);
  local_4 = 2;
  *(undefined1 *)(param_1 + 0x11c8) = 0;
  param_1[0x1145] = 0;
  EncodeOutgoingPacketField((int)param_1 + 0x4500, 0);
  local_4 = 3;
  *(undefined1 *)(param_1 + 0x1251) = 0;
  param_1[0x11ce] = 0;
  EncodeOutgoingPacketField((int)param_1 + 0x4724, 0);
  local_4 = 4;
  param_1[0xfe7] = 0;
  param_1[0x1028] = 0;
  param_1[0x102a] = 1000;
  param_1[0x102b] = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((int)param_1 + 0x42dc, 0xfff0bdc0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState();
  EncodeOutgoingPacketField((int)param_1 + 0x40b8, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  param_1[0x102c] = 0;
  param_1[0x1252] = 5;
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

