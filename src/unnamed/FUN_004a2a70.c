/* FUN_004a2a70 - 0x004a2a70 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_004a2a70(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053c022;
  *unaff_FS_OFFSET = &local_c;
  InitProjectile(param_1,0x186a2);
  local_4 = 0;
  *param_1 = &PTR_FUN_005564d0;
  /* FIXED (2026-07-15): dropped `self` args - angr-confirmed at 0x4a2ab6/
   * 0x4a2ad8/0x4a2af8/0x4a2b18/0x4a2b3e/0x4a2b63 (edi loaded from ebx/ebp/
   * esi+0x43f0/esi+0x4614/ebp/ebx respectively). The zero-write pairs just
   * above each of the first 4 calls match tableHandle(+0x14)/activeFlag
   * (+0x220) for cell bases param_1+0x3fa8, +0x41cc, +0x43f0, +0x4614 - an
   * array of 4 CValueGuard cells (stride 0x224 = sizeof(CValueGuard)); the
   * esi+0x43f0/esi+0x4614 sites confirm esi==param_1 and pin cells 2/3
   * directly. Calls 5/6 reuse ebp/ebx (cells 1/0) from calls 2/1.
   * `param_1` is `undefined4 *` (scales by 4), so byte offsets are taken
   * via `(int)param_1 + N`. See tools/encodeoutgoingpacketfield_sites.json. */
  *(undefined1 *)(param_1 + 0x1072) = 0;
  param_1[0xfef] = 0;
  EncodeOutgoingPacketField((int)param_1 + 0x3fa8, 0);
  SUBFIELD(local_4,0,undefined1) = 1;
  *(undefined1 *)(param_1 + 0x10fb) = 0;
  param_1[0x1078] = 0;
  EncodeOutgoingPacketField((int)param_1 + 0x41cc, 0);
  SUBFIELD(local_4,0,undefined1) = 2;
  *(undefined1 *)(param_1 + 0x1184) = 0;
  param_1[0x1101] = 0;
  EncodeOutgoingPacketField((int)param_1 + 0x43f0, 0);
  SUBFIELD(local_4,0,undefined1) = 3;
  *(undefined1 *)(param_1 + 0x120d) = 0;
  param_1[0x118a] = 0;
  EncodeOutgoingPacketField((int)param_1 + 0x4614, 0);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),4);
  param_1[0xfe7] = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((int)param_1 + 0x41cc, 0xfff0bdc0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState();
  EncodeOutgoingPacketField((int)param_1 + 0x3fa8, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  param_1[0xfe9] = 2;
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

