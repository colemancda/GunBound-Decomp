/* AddToPacketChecksum - 0x0040aab0 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard flip prep): the cell arrives in
 * EAX and was dropped from both the peek and the encode; param_1 (the
 * surviving stack argument, [esp+8]) is the DELTA.  Original 0x40aab0:
 * `mov edi,eax; ... mov eax,edi; call Peek; <op> [esp+8]; push; call Encode`
 * with the cell still in EDI - i.e. self.Encode(self.Peek() + param_1).
 * Every call site was resolved before this promotion (all-or-nothing).
 */
#include "ghidra_types.h"
#include <windows.h>


void AddToPacketChecksum(void *self,int param_1)

{
  int iVar1;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState(self);
  EncodeOutgoingPacketField(self, iVar1 + param_1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return;
}

