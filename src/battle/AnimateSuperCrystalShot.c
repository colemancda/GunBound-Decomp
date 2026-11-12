/* AnimateSuperCrystalShot - 0x00490780 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Slot 2 of the SuperCrystalShot vtable 0x556340, the vtable
 * SpawnSuperCrystalShot stamps (slot 0 is SuperCrystalShot_ScalarDtor,
 * 0x48f260). Slot 2 is the per-frame animate slot in the projectile
 * vtables (AnimateProjectileTick 0x48f1c0, AnimateSuperShot_Bullet3,
 * AnimateKnightIon and so on), and this class gets its own override rather
 * than AnimateProjectileTick. It runs the shared 0x48f300 step, bumps a
 * frame counter at +0x3f9c, and sets the dead flag at +0x14 when that step
 * reports false or the counter exceeds a guarded value (DAT_00e55ab8).
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at the file's one argless PeekPacketChecksumState() call
 * ((void *)&DAT_00e55ab8), from tools/guard_cell_resolve.py.
 */
#include "ghidra_types.h"


void __fastcall AnimateSuperCrystalShot(int param_1)

{
  char cVar1;
  int iVar2;
  
  cVar1 = FUN_0048f300(param_1);
  if (cVar1 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar2 = PeekPacketChecksumState((void *)&DAT_00e55ab8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (*(int *)(param_1 + 0x3f9c) <= iVar2) goto LAB_004907bd;
  }
  *(undefined1 *)(param_1 + 0x14) = 1;
LAB_004907bd:
  *(int *)(param_1 + 0x3f9c) = *(int *)(param_1 + 0x3f9c) + 1;
  return;
}

