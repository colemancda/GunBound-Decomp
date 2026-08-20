/* AnimatePrimaryShot_Bullet4 - 0x004a4610 in the original binary.
 *
 * RENAMED (2026-08-16, from FUN_004a4610): CProjectile virtual slot 2
 * (AnimateProjectileTick, base impl 0x48f1c0) override for mobile type 3's
 * shot 1 AND shot 2 (one class for both, textures bullet4n/bullet4s);
 * vtable 0x5564d0, ctor InitPrimaryShot_Bullet4 reached only through
 * SpawnPrimaryShot's case 3. Type/role CONFIRMED via vtable geometry
 * (tools/projectile_class_map.py); the mobile NAME is not confirmable (no
 * mobile-type->name map in the repo).
 *
 * Body is a raw/near-verbatim Ghidra port, not hand-verified. See
 * src/README.md's "Raw/verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at all 3 argless Peeks: &DAT_00e9bed8 (the modulus for the
 * animation-frame wrap), the param_1+0x3920 counter the Encode beside
 * it increments, and param_1+0xf54 feeding the +0x3d6c Encode - both
 * bases already established by the 2026-07-15 notes below.
 */
#include "ghidra_types.h"


void __fastcall AnimatePrimaryShot_Bullet4(int *param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  
  (**(code **)(*param_1 + 0x18))();
  AdvanceSpriteAnimation((int)param_1);
  iVar3 = param_1[0xfe9] + 2;
  param_1[0xfe9] = iVar3;
  if (0x1e < iVar3) {
    iVar3 = 0x1e;
  }
  param_1[0xfe9] = iVar3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState((void *)&DAT_00e9bed8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  param_1[0xfe7] = (param_1[0xfe8] + param_1[0xfe7]) % iVar3;
  cVar1 = PeekPacketChecksumBool((byte *)param_1 + 0x391b);
  if (cVar1 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState((void *)((int)param_1 + 0x3920));
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4a46a5
     * (`lea edi,[esi + 0x3920]`, esi = this file's own param_1, preserved
     * across the earlier vtable/AdvanceSpriteAnimation/checksum calls as
     * the fastcall this-pointer): cell is param_1+0x3920. `param_1` is
     * `int *`, so byte offsets use `(int)param_1 + N`. See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((int)param_1 + 0x3920, iVar3 + 1);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  iVar3 = param_1[0xed1];
  param_1[0xed1] = iVar3 + 1;
  if (iVar3 + 1 == 5) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState((void *)((int)param_1 + 0xf54));
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4a46de
     * (`lea edi,[esi + 0x3d6c]`, esi = param_1): cell is param_1+0x3d6c -
     * the same offset used as a CValueGuard cell (with
     * CompareChecksumPair/CompareChecksumExceeds) in FUN_004acd10.c. See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((int)param_1 + 0x3d6c, uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  return;
}

