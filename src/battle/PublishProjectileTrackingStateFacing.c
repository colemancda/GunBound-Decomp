/* PublishProjectileTrackingStateFacing - 0x00488880 in the original binary.
 *
 * The FACING variant of PublishProjectileTrackingState (0x458690), used as
 * vtable slot 3 by five per-weapon projectile classes (0x555d74, 0x555e0c,
 * 0x55620c, 0x556284, 0x5565ac - the Bullet16 / Bullet13 / Bullet3 families).
 * NEW CARVE (2026-08-19): Ghidra never carved it - reachable only through
 * those vtables - so this port is hand-derived from the capstone
 * disassembly of 0x488880..0x488a85.
 *
 * It is the same publish routine, with one addition, and that addition is
 * what identifies the third published field.  Where the base version stores
 * a literal 0 into the per-slot record's last dword, this one stores a
 * FACING FLAG computed from the value at this+0x1c2c:
 *
 *     angle = Peek(this + 0x1c2c);
 *     record[4] = (angle > 0x5a && angle < 0x10e) ? 1 : 0;
 *          i.e. (angle > 90 && angle < 270)
 *
 * A 90..270 degree window is the left half of a circle, so this+0x1c2c is the
 * projectile's ANGLE and the flag is "pointing left" - which is why the base
 * variant, used by classes whose sprite does not flip, can hardcode 0.  That
 * pins the field the base carve could only record as "(unnamed)".
 *
 * Everything else matches PublishProjectileTrackingState exactly: the null
 * check on the table pointer at ctx+0x20b94, the +0x3810 GuardedBool clearing
 * ctx+0x20bb4+id, the CheckGuardedBoolAnd flag written INVERTED to
 * ctx+0x20ba4+id, the 5-dword per-slot record at ctx+0x20c24 + id*20, and the
 * two row lookups through FUN_00455b60.
 *
 * Raw/near-verbatim hand port - not hand-verified against a running client.
 * See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"
#include <windows.h>


void __fastcall PublishProjectileTrackingStateFacing(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iAngle;
  int iFacing;
  char cVar5;
  int ctx;

  ctx = g_clientContext;
  iVar1 = *(int *)(ctx + 0x20b94);
  if (iVar1 == 0) {
    return;
  }
  cVar5 = PeekPacketChecksumBool((byte *)(param_1 + 0x3810));
  if (cVar5 != '\0') {
    *(undefined1 *)(ctx + *(int *)(param_1 + 8) + 0x20bb4) = 0;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState((void *)(param_1 + 0x488));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  cVar5 = CheckGuardedBoolAnd(iVar2 < 0);
  *(undefined1 *)(ctx + *(int *)(param_1 + 8) + 0x20ba4) = (cVar5 == '\0');

  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState((void *)(param_1 + 0xf54));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(int *)(ctx + *(int *)(param_1 + 8) * 0x14 + 0x20c24) = iVar2;

  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState((void *)(param_1 + 0x1178));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(int *)(ctx + *(int *)(param_1 + 8) * 0x14 + 0x20c28) = iVar2;

  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iAngle = PeekPacketChecksumState((void *)(param_1 + 0x1c2c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(int *)(ctx + *(int *)(param_1 + 8) * 0x14 + 0x20c2c) = iAngle;

  /* orig 0x4889b8-0x4889f7: the angle is re-peeked for the window test, and
   * again inside it - the original does not reuse the value above. */
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iAngle = PeekPacketChecksumState((void *)(param_1 + 0x1c2c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iFacing = 0;
  if (0x5a < iAngle) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState((void *)(param_1 + 0x1c2c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar2 < 0x10e) {
      iFacing = 1;
    }
  }
  *(int *)(ctx + *(int *)(param_1 + 8) * 0x14 + 0x20c34) = iFacing;

  iVar3 = *(int *)(ctx + 0x20b98);
  iVar4 = *(int *)(param_1 + 8);
  iVar2 = (((iVar4 >> 2) * iVar3 + (iVar4 & 3) * 2) << 6) + iVar1;
  if (iVar2 == 0) {
    return;
  }
  FUN_00455b60(0,*(uint *)(param_1 + 0x18),iVar2,iVar3,*(uint *)(param_1 + 0x30));

  iVar1 = *(int *)(ctx + 0x20b9c);
  if (iVar1 == 0) {
    return;
  }
  iVar3 = *(int *)(ctx + 0x20ba0);
  iVar4 = *(int *)(param_1 + 8);
  iVar2 = (((iVar4 >> 2) * iVar3 + (iVar4 & 3) * 2) << 6) + iVar1;
  iVar2 = FUN_00455b60(0,*(uint *)(param_1 + 0x38),iVar2,iVar3,*(uint *)(param_1 + 0x30));
  *(int *)(ctx + *(int *)(param_1 + 8) * 0x14 + 0x20c30) = iVar2 & 0xff;
  return;
}
