/* UpdateProjectileAngle - 0x004585e0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (batch 40), LIKELY. Recomputes the projectile's angle cell: reads
 * the guarded cells at this+0x488 and this+0x6ac, divides each by 100,
 * feeds the pair to CalculateAngleFromDelta (the atan2 lookup), and stores
 * ((angle + 1) / 3) * 3 into the guarded cell at this+0x1c2c via
 * EncodeOutgoingPacketField.
 *
 * External evidence for "projectile" and "Angle": this+0x1c2c is the cell
 * PublishProjectileTrackingState and PublishProjectileTrackingStateFacing
 * both read and treat as the angle (the latter tests it against a 90..270
 * degree window for the facing flag), and the 23 binary call sites (15 source files) are
 * the Detonate/Animate routines of the Bullet projectile classes plus
 * FUN_004513b0 / FUN_0046c990. What the two source cells are (the name
 * says nothing about them) is deliberately not claimed.
 *
 * NOT DONE: the object pointer arrives in ESI (lea edi,[esi+0x1c2c] at
 * 0x458675; the +0x488/+0x6ac loads use esi too) and is still dropped by
 * the port. It was not promoted to a parameter because callsite_regs.py
 * shows the register set at only 2 of 23 binary sites (0x48749d esi=ebp,
 * 0x4a031d esi=ebx); the rest inherit the caller's own ESI and were not
 * individually proven.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at both argless PeekPacketChecksumState() calls: the +0x6ac/+0x488 pair (0x4585f7/0x458618) off the live-in ESI the file already declares as unaff_ESI (int *, so /4), feeding CalculateAngleFromDelta.  The worklist's 10 sites overrun into the neighbouring function; this one owns two.
 */
#include "ghidra_types.h"


void UpdateProjectileAngle(void)

{
  int iVar1;
  /* FIXED (2026-07-15): this file's decompile never surfaced unaff_ESI
   * as a variable because EVERY use of it in this function is as a
   * dropped-self-arg to a K&R-declared callee (PeekPacketChecksumState
   * at 0x40a2e0 also drops its self arg the same way, out of scope
   * here); objdump of orig/GunBound.gme confirms esi is never assigned
   * anywhere in this function, i.e. it's the incoming register value at
   * entry, same convention as unaff_ESI in sibling files (e.g.
   * FUN_0047fee0.c, FUN_0047c040.c). Declared here to name the
   * EncodeOutgoingPacketField cell below. */
  int *unaff_ESI;

  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  PeekPacketChecksumState((void *)(unaff_ESI + 0x1ab));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  PeekPacketChecksumState((void *)(unaff_ESI + 0x122));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = CalculateAngleFromDelta();
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x458675
   * (`lea edi,[esi+0x1c2c]`, esi = unaff_ESI per the note above).
   * unaff_ESI is `int *` (scales by 4), so the byte offset is taken via
   * `(int)unaff_ESI + 0x1c2c`. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)unaff_ESI + 0x1c2c, ((iVar1 + 1) / 3) * 3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  return;
}

