/* TreeLowerBound - 0x0040b540 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * THE MAP OBJECT IS &DAT_00793770 (2026-08-21).  Scanning all 1180 direct
 * call sites: EAX is the immediate 0x793770 at 1179 of them (the one
 * exception is `mov eax,ebp`), and EBX is `lea ebx,[esp + N]` at ALL 1180 -
 * the scratch node the C already passes as param_1.  So the only argument
 * that was missing is the map, and it is the same object everywhere.
 *
 * It is now a real parameter, and the call sites pass it, even though THE
 * BODY IGNORES IT while the neuter stands.  That is deliberate: the value is
 * uniform so the sweep is free of per-site risk, and whoever restores the
 * real lower_bound gets the argument already threaded through all 1210 sites
 * instead of having to redo this scan.  Nothing about the current behaviour
 * changes - unlike ScrambleChecksumGuardBytes, whose body was live and was
 * writing through an uninitialised pointer, this stub was already correct as
 * a stub. */
#include "ghidra_types.h"


undefined4 * TreeLowerBound(undefined4 *param_1,void *guardMap)

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

