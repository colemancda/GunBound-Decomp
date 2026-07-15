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
  InitProjectile(param_1,0x186a2);
  param_1[0xfe7] = 0;
  param_1[0x1028] = 0;
  local_4 = 0;
  *param_1 = &PTR_FUN_005564f0;
  /* FIXED (2026-07-15): dropped `self` args - angr-confirmed at 0x4a4740/
   * 0x4a475c/0x4a4776/0x4a4790/0x4a47ba/0x4a47df (edi loaded from
   * esi+0x40b0/ebp/esi+0x44f8/esi+0x471c/ebp/esi+0x40b0 respectively). The
   * zero-write pairs just above each of the first 4 calls match
   * tableHandle(+0x14)/activeFlag(+0x220) for cell bases param_1+0x40b0,
   * +0x42d4, +0x44f8, +0x471c - an array of 4 CValueGuard cells (stride
   * 0x224 = sizeof(CValueGuard)); the esi+0x40b0/+0x44f8/+0x471c sites
   * directly confirm esi==param_1 and pin cells 0/2/3. Call 5 reuses ebp
   * (cell 1) from call 2; call 6 is directly given as esi+0x40b0 (cell 0).
   * `param_1` is `undefined4 *` (scales by 4), so byte offsets are taken
   * via `(int)param_1 + N`. See tools/encodeoutgoingpacketfield_sites.json. */
  *(undefined1 *)(param_1 + 0x10b4) = 0;
  param_1[0x1031] = 0;
  EncodeOutgoingPacketField((int)param_1 + 0x40b0, 0);
  SUBFIELD(local_4,0,undefined1) = 1;
  *(undefined1 *)(param_1 + 0x113d) = 0;
  param_1[0x10ba] = 0;
  EncodeOutgoingPacketField((int)param_1 + 0x42d4, 0);
  SUBFIELD(local_4,0,undefined1) = 2;
  *(undefined1 *)(param_1 + 0x11c6) = 0;
  param_1[0x1143] = 0;
  EncodeOutgoingPacketField((int)param_1 + 0x44f8, 0);
  SUBFIELD(local_4,0,undefined1) = 3;
  *(undefined1 *)(param_1 + 0x124f) = 0;
  param_1[0x11cc] = 0;
  EncodeOutgoingPacketField((int)param_1 + 0x471c, 0);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),4);
  param_1[0xfe7] = 0;
  param_1[0x102a] = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((int)param_1 + 0x42d4, 0xfff0bdc0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState();
  EncodeOutgoingPacketField((int)param_1 + 0x40b0, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

