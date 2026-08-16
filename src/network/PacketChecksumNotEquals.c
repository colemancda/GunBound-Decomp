/* PacketChecksumNotEquals - 0x0040b2a0 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard flip prep): the internal
 * PeekPacketChecksumState() call reads param_1 - the original loads its cell
 * with `mov eax,[esp+8]`, which with the single prologue push is the first
 * stack argument, and the value it is compared against is [esp+0xc] = param_2
 * (already named here).
 */
#include "ghidra_types.h"
#include <windows.h>


bool PacketChecksumNotEquals(undefined4 param_1,int param_2)

{
  int iVar1;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState((void *)(param_1));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return iVar1 != param_2;
}

