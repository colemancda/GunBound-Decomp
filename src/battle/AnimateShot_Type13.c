/* AnimateShot_Type13 - 0x0046c990 in the original binary.
 *
 * RENAMED (from FUN_0046c990): slot 2 (+0x8) of vtable 0x555e0c, whose
 * slot 0 is Shot_Type13_ScalarDtor (0x46b650).  Slot 2 is the projectile
 * Animate virtual, where AnimateProjectileTick (0x48f1c0) sits in the base
 * vtables.  Its body is that function's with extra steps: the slot-6
 * virtual call (here made only when +0x24 is non-zero),
 * UpdateProjectileAngle, AdvanceSpriteAnimation and the +0x3920 / +0x3d6c
 * counter Encodes, plus a slot-1 call (ResolveNamedState) when the +0x34
 * flag is set.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at both argless PeekPacketChecksumState() calls: AnimateProjectileTick's shape.
 */
#include "ghidra_types.h"


void __fastcall AnimateShot_Type13(int *param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (param_1[9] != 0) {
    (**(code **)(*param_1 + 0x18))();
  }
  UpdateProjectileAngle();
  AdvanceSpriteAnimation((int)param_1);
  if ((char)param_1[0xd] == '\x01') {
    (**(code **)(*param_1 + 4))(&PTR_DAT_00555e2c);
  }
  cVar1 = PeekPacketChecksumBool((byte *)param_1 + 0x391b);
  if (cVar1 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar2 = PeekPacketChecksumState((void *)((int)param_1 + 0x3920));
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x46c9f1
     * (`lea edi,[esi + 0x3920]`, esi = this file's own param_1, preserved
     * across the earlier vtable/AdvanceSpriteAnimation/checksum calls as
     * the fastcall this-pointer): cell is param_1+0x3920. `param_1` is
     * `int *`, so byte offsets use `(int)param_1 + N`. See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((int)param_1 + 0x3920, iVar2 + 1);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  iVar2 = param_1[0xed1];
  param_1[0xed1] = iVar2 + 1;
  if (iVar2 + 1 == 5) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar3 = PeekPacketChecksumState((void *)((int)param_1 + 0xf54));
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x46ca2a
     * (`lea edi,[esi + 0x3d6c]`, esi = param_1): cell is param_1+0x3d6c -
     * the same offset used as a CValueGuard cell (with
     * CompareChecksumPair/CompareChecksumExceeds) in FUN_004acd10.c. See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((int)param_1 + 0x3d6c, uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  return;
}

