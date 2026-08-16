/* AnimateShot2_Bullet13 - 0x004a1690 in the original binary.
 *
 * RENAMED (2026-08-16, from FUN_004a1690): CProjectile virtual slot 2
 * (AnimateProjectileTick, base impl 0x48f1c0) override for mobile type
 * 12's shot 2 (weapon index 1, texture bullet13s); vtable 0x55649c, ctor
 * FUN_0049e540 reached only through SpawnPrimaryShot's case 12. Type/role
 * CONFIRMED via vtable geometry (tools/projectile_class_map.py); the
 * mobile NAME is not confirmable (no mobile-type->name map in the repo).
 *
 * Body is a raw/near-verbatim Ghidra port, not hand-verified. See
 * src/README.md's "Raw/verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at both argless PeekPacketChecksumState() calls: both off the live-in ECX object beside the already-fixed
 * +0x3920/+0x3d6c Encodes - AnimateProjectileTick's shape.
 */
#include "ghidra_types.h"


void __fastcall AnimateShot2_Bullet13(int *param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  
  (**(code **)(*param_1 + 0x18))();
  FUN_004585e0();
  if (param_1[0xfe7] != -1) {
    param_1[0xfe7] = param_1[0xfe7] + 1;
  }
  AdvanceSpriteAnimation((int)param_1);
  cVar1 = PeekPacketChecksumBool((byte *)param_1 + 0x391b);
  if (cVar1 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState((void *)((int)param_1 + 0x3920));
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4a16ea
     * (`lea edi,[esi + 0x3920]`, esi = this file's own param_1, preserved
     * across the earlier vtable/AdvanceSpriteAnimation/checksum calls as
     * the fastcall this-pointer): cell is param_1+0x3920. `param_1` is
     * `int *`, so byte offsets use `(int)param_1 + N`. See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((int)param_1 + 0x3920, iVar2 + 1);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  iVar2 = param_1[0xed1];
  param_1[0xed1] = iVar2 + 1;
  if (iVar2 + 1 == 5) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState((void *)((int)param_1 + 0xf54));
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4a1723
     * (`lea edi,[esi + 0x3d6c]`, esi = param_1): cell is param_1+0x3d6c -
     * the same offset used as a CValueGuard cell (with
     * CompareChecksumPair/CompareChecksumExceeds) in FUN_004acd10.c. See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((int)param_1 + 0x3d6c, uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  return;
}

