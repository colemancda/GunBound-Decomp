/* ExplodeSuperShot_Bullet16 - 0x004685b0 in the original binary.
 *
 * RENAMED (2026-08-16, from FUN_004685b0): CProjectile virtual slot 8 -
 * the post-detonation effect that the slot-6 Detonate override dispatches
 * right after marking the projectile dead (`param_1[5] = 1; (**(code
 * **)(*param_1 + 0x20))()`), only super-shot classes have it. "Explode" is
 * a descriptive label for that role, not a recovered name for mobile type
 * 15's super shot (texture bullet16p; vtable 0x555d74, ctor InitSuperShot_Bullet16
 * reached only through SpawnSuperShot's case 15). Type/role CONFIRMED via
 * vtable geometry (tools/projectile_class_map.py); the mobile NAME is not
 * confirmable (no mobile-type->name map in the repo).
 *
 * Body is a raw/near-verbatim Ghidra port, not hand-verified. See
 * src/README.md's "Raw/verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at both argless PeekPacketChecksumState() calls: the +0x1178/+0xf54 position pair off the live-in ECX object.
 */
#include "ghidra_types.h"


void __fastcall ExplodeSuperShot_Bullet16(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState((void *)(param_1 + 0x1178));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_1 + 0xf54));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004398e0(&DAT_006a7f70 + g_clientContext,*(int *)(param_1 + 8) + 3,uVar2,uVar1,param_1,1);
  return;
}

