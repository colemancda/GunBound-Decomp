/* UpdateIonTargetAngle - 0x0047bfd0 in the original binary.
 *
 * RENAMED (from FUN_0047bfd0): helper of the two Ion Animate virtuals
 * (AnimateKnightIon, AnimateLaserIon - 3 call sites each, ESI = the ion
 * object).  It takes dx = [+0x3fa8] - Peek(+0x40) and dy = [+0x3fac] -
 * Peek(+0x264) and stores CalculateAngleFromDelta(dx, dy) (0x4f1f10, EAX =
 * dx, ECX = dy) at +0x3f9c.  Operand shapes from outside: +0x40 / +0x264
 * are the object X / Y guard cells, and SpawnKnightIon / SpawnLaserIon
 * store (param_2, param_3 + 200) at +0x3fa8 / +0x3fac, where CreateMobile
 * passes (x, y - 200): the ion spawns 200 above its mobile and the stored
 * pair is the mobile's own position, so this is the angle from the ion to
 * the point it is anchored on.  The Ion Animate bodies then adjust
 * [+0x3f9c] in small steps (+-1, 2 or 4).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at both argless PeekPacketChecksumState() calls: the +0x40/+0x264 position pair off the live-in ESI object (the
 * decompile already models it as unaff_ESI for the +0x3f9c store),
 * feeding CalculateAngleFromDelta.
 */
#include "ghidra_types.h"


void UpdateIonTargetAngle(void)

{
  undefined4 uVar1;
  int unaff_ESI;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  PeekPacketChecksumState((void *)(unaff_ESI + 0x40));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  PeekPacketChecksumState((void *)(unaff_ESI + 0x264));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = CalculateAngleFromDelta();
  *(undefined4 *)(unaff_ESI + 0x3f9c) = uVar1;
  return;
}

