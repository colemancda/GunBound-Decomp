/* PeekPacketChecksumBool - 0x004065a0 in the original binary.
 *
 * The boolean reader of the value-guard / "packet-checksum" family (the
 * bit-valued sibling of PeekPacketChecksumState). Takes the guarded cell
 * in a register (EAX; Ghidra drops it): under the shared guard lock it
 * validates the (a,b,check) triple - on mismatch it sets
 * g_valueGuardTamperFlag and returns 0 - then returns bit (a & 7) of b as
 * a bool. Used pervasively to read guarded flags (e.g. the replay-playback
 * mode flag). See ARCHITECTURE.md "Packet-checksum utility family".
 *
 * NOT A QUICK FIX (2026-07-13): `in_EAX` is part of the same large,
 * already-acknowledged CValueGuard migration flagged in
 * PeekPacketChecksumState.c's own header (300+ callers there) - this
 * function has 190+ callers of its own (every Mobile*_MainAction,
 * SimulateMobileFrame/ProjectileFrame, most ProcessPacket handlers,
 * etc.), each passing a different guard cell address per call site.
 * Recovering the real cell for even a handful would need per-caller
 * tracing at this scale; this belongs to the CValueGuard/ValueGuard.cpp
 * migration effort, not a one-file bug-hunt pass.
 */
#include "ghidra_types.h"


char PeekPacketChecksumBool(void)

{
  byte bVar1;
  byte bVar2;
  byte *in_EAX;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  bVar1 = *in_EAX;
  bVar2 = in_EAX[1];
  if ((byte)((bVar1 + bVar2) - 0x34) != in_EAX[2]) {
    g_valueGuardTamperFlag = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    return '\0';
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return '\x01' - ((bVar2 >> (bVar1 & 7) & 1) != 1);
}

