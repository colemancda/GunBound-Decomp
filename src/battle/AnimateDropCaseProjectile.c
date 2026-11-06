/* AnimateDropCaseProjectile - 0x0046b610 in the original binary.
 *
 * RENAMED (from FUN_0046b610): slot 2 (+0x8) of vtable 0x555dec, whose
 * slot 0 is DropCaseProjectile_ScalarDtor (0x46aee0).  Slot 2 is the
 * Animate virtual: AnimateProjectileTick (0x48f1c0) sits there in the
 * sibling projectile vtables (e.g. 0x555dcc) and AnimateShot2_Bullet13 etc.
 * override it the same way.  This override keeps the base's opening (virtual
 * call through slot 6, which is this class's own 0x46af10, then
 * AdvanceSpriteAnimation) and drops the angle update.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void __fastcall AnimateDropCaseProjectile(int *param_1)

{
  (**(code **)(*param_1 + 0x18))();
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x46b62c
   * (`lea edi,[esi+0x1c2c]`, esi = param_1 per `mov esi,ecx` at function
   * entry, confirmed by objdump of orig/GunBound.gme). param_1 is `int *`
   * (scales by 4), so the byte offset is taken via `(int)param_1 +
   * 0x1c2c`. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)param_1 + 0x1c2c, 0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  AdvanceSpriteAnimation((int)param_1);
  return;
}

