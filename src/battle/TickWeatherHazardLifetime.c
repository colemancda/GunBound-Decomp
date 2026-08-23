/* TickWeatherHazardLifetime - 0x00471a90 in the original binary.
 *
 * NAMED (2026-07-16): the per-tick lifetime countdown SHARED by the
 * Firewall and Lightning hazards - vtable slot 4 (+0x10) of both
 * PTR_FUN_00555edc (Firewall) and PTR_FUN_00555e74 (Lightning).
 * Decrements the lifetime guard cell at this+0x488 (the +4-shifted
 * layout those two use vs the Tornado's +0x484; spawn param_4 = 10000)
 * by one each tick; when it goes negative it sets the node's dead/
 * finished flag at this+0x14, dropping the hazard from the active-object
 * list. Tornado has its own +0x484 copy (TickTornadoHazardLifetime).
 * See InitTornadoHazard.c for the field map.
 *
 * PeekPacketChecksumState()/EncodeOutgoingPacketField(cell, v-1) are the
 * guard-cell (CValueGuard) read/write idiom for the +0x488 cell. Raw port. *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at both argless PeekPacketChecksumState() calls: both read the hazard's +0x488 lifetime cell, which the Encode
 * between them decrements.  The worklist MISMATCH is stale - 2 C : 2
 * orig today.
 */
#include "ghidra_types.h"


void __fastcall TickWeatherHazardLifetime(int param_1)

{
  int iVar1;

  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = PeekPacketChecksumState((void *)(param_1 + 0x488));
  EncodeOutgoingPacketField((void *)(param_1 + 0x488), iVar1 + -1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = PeekPacketChecksumState((void *)(param_1 + 0x488));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar1 < 0) {
    *(undefined1 *)(param_1 + 0x14) = 1;
  }
  return;
}
