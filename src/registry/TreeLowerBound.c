/* TreeLowerBound - 0x0040b540 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * TreeLowerBound(undefined4 *param_1)

{
  /* BRING-UP NEUTER (2026-07-14): this is the CValueGuard guard-cell
   * std::map lower_bound. Both the map object (in_EAX) and the search key
   * (unaff_EBX) arrive via dropped registers - so the raw port reads them
   * as uninitialised C locals and faults (`in_EAX + 4` = read of 0x4, live-
   * reproduced once the broker connection opened and ProcessIncomingPackets
   * began running on a real receive ring). This is part of the same
   * ~1397-caller CValueGuard/ValueGuard.cpp migration as the checksum Peek/
   * Encode family; its callers here (ProcessIncomingPackets, SendOutgoingPacket,
   * FlushEncodedSocketBuffer) invoke it purely for guard-cell bookkeeping and
   * discard the result, so return the output node marked "not found" (a NULL
   * node) without ever dereferencing the dropped map. Remove once the guard
   * map is a real object threaded through its call sites. */
  *param_1 = 0;
  *(undefined1 *)(param_1 + 1) = 0;
  return param_1;
}

