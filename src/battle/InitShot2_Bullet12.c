/* InitShot2_Bullet12 - 0x004af530 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_004af530).  Constructor for one per-weapon PROJECTILE
 * class: it delegates to InitProjectile(this, 0x186a2) - class id 100002,
 * stamped at object +0x4 - and installs vtable 0x556660.
 *
 * The bullet identity comes from that vtable's slots.  Slots SHARED with
 * other projectile vtables carry no information (that is how the multi-class
 * virtuals like DetonateSuperShot_Bullet2_8_11 are named in the first place),
 * so only slots UNIQUE to this vtable were used, and every one of them agrees
 * on a single role and bullet number.  See the commit for the census.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at the file's one argless PeekPacketChecksumState() call: param_1+0x42dc, the ctor's just-seeded cell - InitShot2_Bullet7's shape.
 */
#include "ghidra_types.h"


undefined4 * InitShot2_Bullet12(undefined4 *param_1)

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
  uVar1 = PeekPacketChecksumState((void *)((int)param_1 + 0x42dc));
  EncodeOutgoingPacketField((int)param_1 + 0x40b8, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  param_1[0x102c] = 0;
  param_1[0x1252] = 5;
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

