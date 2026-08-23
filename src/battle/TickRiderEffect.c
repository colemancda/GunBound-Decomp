/* TickRiderEffect - 0x004a2920 in the original binary.
 *
 * CRiderEffect's vtable slot 2 (Tick; vtable 0x5564bc - see
 * src/cxx/Effects.h).  NEW CARVE (2026-08-18): Ghidra never carved this
 * range - reachable only through the effect vtable - hand-derived from the
 * capstone disassembly of 0x4a2920..0x4a29f1.
 *
 * The falling "rider" motion: advance the sprite animation, then
 *  - while still above the target Y (+0x44, the spawner's param_3 - NOT an
 *    anim phase like the flames'), descend 5 px per tick;
 *  - once at/below target: if the guarded game-phase value ctx+0x45354
 *    peeks as 1 or 3, keep descending; otherwise DRIFT horizontally
 *    (m_facing picked at spawn from the screen half: +5 when set, else -5)
 *    without descending;
 *  - kill the object (m_dead=1) when it leaves the play area: y < -200,
 *    x < -20, or x > map width (the guarded ctx+0x6a7720) + 20.
 *
 * The original screams "parachute": fall to a height, then blow sideways.
 *
 * AdvanceSpriteAnimation returns its animation object; the original
 * compares the rider's +0x3c/+0x44 through that same pointer (this - the
 * call preserves it), spelled here directly off the object.
 */
#include "ghidra_types.h"
#include <windows.h>


void __thiscall TickRiderEffect(int param_1)

{
  int iVar1;
  char cVar2;

  AdvanceSpriteAnimation(param_1);
  if (*(int *)(param_1 + 0x3c) <= *(int *)(param_1 + 0x44)) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar1 = PeekPacketChecksumState((void *)(g_clientContext + 0x45354));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    cVar2 = (iVar1 == 1);
    if (cVar2 == '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar1 = PeekPacketChecksumState((void *)(g_clientContext + 0x45354));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      cVar2 = (iVar1 == 3);
    }
    if (cVar2 == '\0') {
      /* drifting phase: sideways only */
      *(int *)(param_1 + 0x38) =
          *(int *)(param_1 + 0x38) + ((*(char *)(param_1 + 0x40) != 0) ? 5 : -5);
      goto bounds;
    }
  }
  *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + -5;
bounds:
  if ((*(int *)(param_1 + 0x3c) < -200) || (*(int *)(param_1 + 0x38) < -0x14) ||
      (*(int *)(g_clientContext + 0x6a7720) + 0x14 < *(int *)(param_1 + 0x38))) {
    *(char *)(param_1 + 0x14) = 1;
  }
  return;
}
