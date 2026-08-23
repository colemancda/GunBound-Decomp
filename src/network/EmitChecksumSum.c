/* EmitChecksumSum - 0x0040afb0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard flip prep): this reads TWO cells.
 * The second is the stack argument callers already passed; the first arrives
 * in EAX and was dropped, along with the encode's own cell.  Original
 * 0x40afb0: `mov edi,eax; ... mov eax,edi; call Peek; mov esi,eax;
 * mov eax,[esp+0xc]; call Peek; add eax,esi; push eax; call Encode` with the
 * cell still in EDI - i.e. self.Encode(self.Peek() + other.Peek()).
 * All 112 call sites were resolved before this promotion (see the commit
 * series); promotion is all-or-nothing, since a stray zero-arg call would
 * read a garbage stack slot as a cell once Peek is flipped.
 */
#include "ghidra_types.h"


void EmitChecksumSum(void *self,void *other)

{
  int iVar1;
  int iVar2;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = PeekPacketChecksumState(self);
  iVar2 = PeekPacketChecksumState(other);
  EncodeOutgoingPacketField(self, iVar2 + iVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  return;
}

