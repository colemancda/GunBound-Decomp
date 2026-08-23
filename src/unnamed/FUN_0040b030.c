/* FUN_0040b030 - 0x0040b030 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard flip prep): the cell arrives in
 * EAX and was dropped from both calls; the original (0x40b030) has no stack
 * arguments at all - it is the increment twin of EncodeDecrementedChecksum:
 * self.Encode(self.Peek() + 1).  All 10 callers fixed alongside.
 */
#include "ghidra_types.h"


void FUN_0040b030(void *self)

{
  int iVar1;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = PeekPacketChecksumState(self);
  EncodeOutgoingPacketField(self, iVar1 + 1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  return;
}

