/* TickCrashParticleAdditive_556488 - 0x0049e470 in the original binary.
 *
 * RENAMED (from FUN_0049e470): slot 2 (+0x8) of vtable 0x556488, the
 * per-frame virtual TickActiveObjectLayers dispatches (slot 0
 * DeletePoisonedBaseObject, slot 4 NoOpMethod: the five-slot effect shape
 * of TickFlameEffect).  The vtable is stamped by
 * InitCrashParticleAdditive_556488 (0x49e44f), whose sole caller is
 * SpawnCrashParticleAdditive_556488; the suffix follows that class.  The
 * body is the minimal particle tick: the frame index +0x44 steps modulo the
 * guarded divisor and the object is marked dead (+0x14) once the age at
 * +0x40 passes 7.
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


void __fastcall TickCrashParticleAdditive_556488(int param_1)

{
  int iVar1;
  int iVar2;
  
  *(int *)(param_1 + 0x44) = *(int *)(param_1 + 0x44) + 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = PeekPacketChecksumState((void *)&DAT_00e9bed8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = *(int *)(param_1 + 0x40) + 1;
  *(int *)(param_1 + 0x40) = iVar2;
  *(int *)(param_1 + 0x44) = *(int *)(param_1 + 0x44) % iVar1;
  if (7 < iVar2) {
    *(undefined1 *)(param_1 + 0x14) = 1;
  }
  return;
}

