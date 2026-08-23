/* TickTornadoHazardLifetime - 0x004acc90 in the original binary.
 *
 * NAMED (2026-07-16): the Tornado hazard's per-tick lifetime countdown -
 * vtable slot 4 (+0x10) of PTR_FUN_005565e4. Decrements the lifetime
 * guard cell at this+0x484 (spawn param_4, initialised to 10000) by one
 * each tick; when the value goes negative it sets the node's dead/
 * finished flag at this+0x14, which makes the active-object list drop the
 * tornado. Appears only in the Tornado vtable (Firewall/Lightning share
 * their own +0x488 copy, TickWeatherHazardLifetime). See InitTornado
 * Hazard.c for the field map.
 *
 * The EnterCriticalSection/PeekPacketChecksumState/EncodeOutgoingPacket
 * Field calls are the guard-cell (CValueGuard) read/write idiom used
 * throughout this family - PeekPacketChecksumState() reads the +0x484
 * cell, EncodeOutgoingPacketField(cell, v-1) writes it back. Raw port. *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at both argless PeekPacketChecksumState() calls: both read the tornado's +0x484 lifetime cell around its decrement
 * Encode - the tornado object's layout is 4 bytes off the other
 * hazards' (+0x484 vs +0x488).  Worklist MISMATCH is stale.
 */
#include "ghidra_types.h"


void __fastcall TickTornadoHazardLifetime(int param_1)

{
  int iVar1;

  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = PeekPacketChecksumState((void *)(param_1 + 0x484));
  EncodeOutgoingPacketField((void *)(param_1 + 0x484), iVar1 + -1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = PeekPacketChecksumState((void *)(param_1 + 0x484));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar1 < 0) {
    *(undefined1 *)(param_1 + 0x14) = 1;
  }
  return;
}
