/* PeekPacketChecksumState - 0x0040a2e0 in the original binary.
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


uint PeekPacketChecksumState(void)

{
  /* BRING-UP WORKAROUND: skip the real guarded-value decode.
   *
   * This is CValueGuard::Peek() (src/cxx/ValueGuard.cpp, same address
   * 0x40a2e0) - the raw C port here is stale/superseded but is still what
   * actually gets linked, since none of its 300+ callers have been migrated
   * to the C++ CValueGuard type yet (that migration is a much larger, actively
   * in-progress effort - see ValueGuard.cpp/GuardedBool family - out of scope
   * here). The raw port also has its own bug independent of that migration:
   * it takes its "this"/cell pointer via a dropped EAX register (like
   * InitDirectDraw's HWND-in-EAX bug fixed earlier this session) and calls
   * FUN_0040b8c0 - an MSVC-STL-style shared tree-lookup helper - with its
   * search key and output pointer ALSO passed via dropped EBX/EAX registers,
   * which portable C can't express without inline assembly.
   *
   * Returning 0 unconditionally is safe for bring-up (reaching the logo/menu
   * states): every caller already tolerates 0 as "tamper detected/no value"
   * per the real implementation's own fallback paths. It does mean any
   * gameplay value actually protected by a guard cell will read as 0 in this
   * build - fine for reaching further states, not a gameplay-correctness
   * claim. Remove once callers migrate to real CValueGuard cells. */
  return 0;
}

