/* PacketChecksumGreaterEqual - 0x0040b300 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard flip prep): the internal
 * PeekPacketChecksumState() call reads param_1 - the original loads its cell
 * with `mov eax,[esp+8]`, which with the single prologue push is the first
 * stack argument, and the value it is compared against is [esp+0xc] = param_2
 * (already named here).
 */
#include "ghidra_types.h"


bool PacketChecksumGreaterEqual(undefined4 param_1,int param_2)

{
  int iVar1;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState((void *)(param_1));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return param_2 <= iVar1;
}

