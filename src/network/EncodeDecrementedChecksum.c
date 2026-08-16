/* EncodeDecrementedChecksum - 0x0040b060 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard flip prep): the cell arrives in
 * EAX and Ghidra dropped it, leaving both the peek and the encode arg-less.
 * The original (0x40b060) is `mov edi,eax; ... mov eax,edi; call 0x40a2e0;
 * dec eax; push eax; call 0x40a380` with no stack arguments at all, so the
 * whole function is `self.Encode(self.Peek() - 1)` and `self` is now a real
 * parameter.  All 16 call sites were updated in the same commit.
 */
#include "ghidra_types.h"


void EncodeDecrementedChecksum(void *self)

{
  int iVar1;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState(self);
  EncodeOutgoingPacketField(self, iVar1 + -1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return;
}

