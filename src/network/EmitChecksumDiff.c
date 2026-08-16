/* EmitChecksumDiff - 0x0040aff0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard flip prep): this reads TWO cells.
 * The first arrives in EAX and was dropped entirely; the second is the single
 * stack argument the callers already pass ([esp+0xc]).  Original 0x40aff0:
 * `mov edi,eax; ... mov eax,edi; call Peek; mov esi,eax;
 * mov eax,[esp+0xc]; call Peek; sub esi,eax; push esi; call Encode` with the
 * cell still in EDI - i.e. self.Encode(self.Peek() - other.Peek()).
 */
#include "ghidra_types.h"


void EmitChecksumDiff(void *self,void *other)

{
  int iVar1;
  int iVar2;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState(self);
  iVar2 = PeekPacketChecksumState(other);
  EncodeOutgoingPacketField(self, iVar1 - iVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return;
}

