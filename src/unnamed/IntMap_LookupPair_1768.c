/* IntMap_LookupPair_1768 - 0x005006f0 in the original binary.
 *
 * NAMED (2026-10-29): ATL7 CAtlMap::Lookup(key) - the overload that
 * returns the CPair* (NULL on a miss) rather than copying the value out -
 * for the 0x1768-node int-keyed maps.  The whole body is GetNode: call
 * IntMap_Find_1768 (0x500701; map in ECX, key in EDI) and return what it
 * returned - after the call only `pop esi; add esp,0xc; ret` run, so EAX
 * reaches the caller untouched.
 *
 * Named LookupPair, not Lookup, because IntMap_Lookup_14 (0x500900) is
 * the OTHER overload, bool Lookup(key, VALUE&), and in this tree a shared
 * stem with only the stride suffix differing means one member at two
 * instantiations.  "Pair" is ATL's own word for what comes back (CPair).
 *
 * The one binary caller, FUN_004ff770 at 0x4ff871, uses it as a pointer
 * lookup: map = peer-record+0x50 (`lea ebx,[esi+0x50]; mov ecx,ebx`),
 * key in EDI; `test eax,eax`, and on a hit it passes the pair's fields
 * (+0x10, +0x12, +0x14 and the value at +4 - m_key at +0, m_value from +4)
 * to the owner's vtable slot 0, then IntMap_RemoveKey_1768s the same key
 * from the same map (0x4ff8a6).
 *
 * RETURN VALUE FIXED (2026-10-29).  The port used to discard the find's
 * result and `return 0`, on the stated belief that callers ignore it.
 * The caller tests it, so the port made every lookup look like a miss and
 * FUN_004ff770's hit branch - the slot-0 dispatch and the RemoveKey -
 * could never run.  It now returns IntMap_Find_1768's result, as the
 * original does; the older note below that it "throws the result away"
 * predates this fix.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * REGISTERS PROMOTED (2026-08-25): a thin wrapper over the map find that
 * keeps all three of the find's out-slots in one 12-byte scratch local and
 * throws the result away.  Neither the map (ECX) nor the key (EDI) is set here:
 * both fall straight through from its own caller.
 */
#include "ghidra_types.h"


undefined4 IntMap_LookupPair_1768(int *regEcx,uint regEdi)

{
  undefined1 local_c [12];
  
  /* EAX from the find survives to the `ret` (0x500706-0x50070a touch only
   * ESI and ESP) - see the header's RETURN VALUE FIXED note. */
  return (undefined4)IntMap_Find_1768(regEcx,(undefined4 *)local_c,(uint *)(local_c + 4),
                                      (uint *)(local_c + 8),regEdi);
}

