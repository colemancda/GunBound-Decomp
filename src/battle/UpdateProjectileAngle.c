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
 * FUN_004513b0 / AnimateShot_Type13. What the two source cells are (the name
 * says nothing about them) is deliberately not claimed.
 *
 * ESI PROMOTED TO A PARAMETER (2026-11-06). The object pointer arrives in
 * ESI (lea edi,[esi+0x1c2c] at 0x458675; the +0x488/+0x6ac loads use it
 * too). All 23 binary call sites were traced from their function entry:
 * ESI is the enclosing method's own `this` (ECX at entry) at every one -
 * `push esi / mov esi,ecx` at entry and no other ESI write before the call
 * at 0x45140d/0x4514bb (FUN_004513b0), 0x45326a/0x4532fe
 * (DetonateSuperShot_Bullet6), 0x46c9a2, 0x47ebe6, 0x48d11b, 0x48f1cb,
 * 0x4960aa/0x4963f7 (Bullet7), 0x49cc93, 0x4a169b, 0x4a2f02, 0x4a4b7a/
 * 0x4a4ec7 (Bullet2), 0x4ae108, 0x4af9ca/0x4afd72 (Shot2_Bullet12); and
 * `mov esi,ebp` (0x48749b) / `mov esi,ebx` (0x4a031b) right before the call
 * in the Bullet13 pair, where EBP/EBX were set from ECX at entry
 * (0x486ebf / 0x49fd5f) and written nowhere else. Sites 0x4887ee, 0x4b1076
 * and 0x4b2ac6 sit in methods that start at 0x488780, 0x4b106d and 0x4b2abd
 * (same `push esi / mov esi,ecx` entry) which have no port; 0x47ebe6 and
 * 0x49cc93 have no call in the port either.
 *
 * DROPPED ARGUMENTS OF CalculateAngleFromDelta RECOVERED: 0x458628-0x45864c
 * computes EAX = cell(+0x488) / 100 and ECX = cell(+0x6ac) / 100 (signed
 * magic divide by 100 via 0x51eb851f) before `call 0x4f1f10`, whose entry
 * pins EAX = dx and ECX = dy. The port had discarded both Peek results and
 * called it with no arguments.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at both argless PeekPacketChecksumState() calls: the +0x6ac/+0x488 pair (0x4585f7/0x458618) off the live-in ESI the file already declares as unaff_ESI (int *, so /4), feeding CalculateAngleFromDelta.  The worklist's 10 sites overrun into the neighbouring function; this one owns two.
 */
#include "ghidra_types.h"


void UpdateProjectileAngle(int *self)

{
  int iVar1;
  int cellX;
  int cellY;

  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  cellY = PeekPacketChecksumState((void *)(self + 0x1ab));   /* +0x6ac */
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  cellX = PeekPacketChecksumState((void *)(self + 0x122));   /* +0x488 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = CalculateAngleFromDelta(cellX / 100, cellY / 100);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  /* lea edi,[esi+0x1c2c] at 0x458675; self is `int *`, so take the byte
   * offset via (int)self + 0x1c2c. */
  EncodeOutgoingPacketField((int)self + 0x1c2c, ((iVar1 + 1) / 3) * 3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  return;
}
