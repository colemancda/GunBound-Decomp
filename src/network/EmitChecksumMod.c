/* EmitChecksumMod - 0x0040ab60 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard flip prep): the cell arrives in
 * EAX and was dropped; param_1 (the surviving stack argument, [esp+8]) is the
 * DIVISOR, not a cell.  Original 0x40ab60: `mov edi,eax; ... mov eax,edi;
 * call Peek; cdq; idiv [esp+8]; push edx; call Encode` with the cell still in
 * EDI - i.e. self.Encode(self.Peek() %% param_1).
 */
#include "ghidra_types.h"


void EmitChecksumMod(void *self,int param_1)

{
  int iVar1;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState(self);
  EncodeOutgoingPacketField(self, iVar1 % param_1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return;
}

