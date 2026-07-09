/* EncodeChecksumState - 0x0040a4a0 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>


undefined4 EncodeChecksumState(void)

{
  undefined4 uVar1;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* bare `return;` in a value-returning function - MSVC falls through
   * with whatever's in EAX (here, uVar1, still live from the call
   * above); gcc 14 errors on this (-Wreturn-mismatch). Matches this
   * function's own C++ promotion, CValueGuard::Encode() in
   * src/cxx/ValueGuard.cpp, which returns the peeked value. */
  return uVar1;
}

