/* TickCrashParticleBurst - 0x00464320 in the original binary.
 *
 * RENAMED (from FUN_00464320): slot 2 (+0x8) of vtable 0x555ce0, the
 * per-frame virtual that TickActiveObjectLayers dispatches (slot 0 is
 * DeletePoisonedBaseObject, slot 4 NoOpMethod - the same 5-slot effect shape
 * as CFlameEffect's TickFlameEffect).  The only code that stamps 0x555ce0
 * is SpawnCrashParticleBurst's inline object build (0x4371f1), so this is
 * that class's Tick.  Per frame: +0x40 counts up and the object is marked
 * dead (+0x14) once it exceeds 0x1f; +0x38 / +0x3c advance by the +0x50 /
 * +0x54 velocities, the latter gaining 2 per frame after frame 8;
 * +0x44 steps through the frame divisor like TickFlameEffect.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at the file's one argless PeekPacketChecksumState() call
 * ((void *)&DAT_00e9bed8), from tools/guard_cell_resolve.py.
 */
#include "ghidra_types.h"


void __fastcall TickCrashParticleBurst(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x40) + 1;
  *(int *)(param_1 + 0x40) = iVar1;
  if (0x1f < iVar1) {
    *(undefined1 *)(param_1 + 0x14) = 1;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = PeekPacketChecksumState((void *)&DAT_00e9bed8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  *(int *)(param_1 + 0x38) = *(int *)(param_1 + 0x38) + *(int *)(param_1 + 0x50);
  *(int *)(param_1 + 0x44) = (*(int *)(param_1 + 0x44) + 6) % iVar1;
  *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + *(int *)(param_1 + 0x54);
  if (8 < *(int *)(param_1 + 0x40)) {
    *(int *)(param_1 + 0x54) = *(int *)(param_1 + 0x54) + 2;
  }
  return;
}

