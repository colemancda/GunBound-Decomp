/* FUN_0047bfd0 - 0x0047bfd0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at both argless PeekPacketChecksumState() calls: the +0x40/+0x264 position pair off the live-in ESI object (the
 * decompile already models it as unaff_ESI for the +0x3f9c store),
 * feeding CalculateAngleFromDelta.
 */
#include "ghidra_types.h"


void FUN_0047bfd0(void)

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

