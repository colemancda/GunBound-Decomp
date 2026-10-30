/* IntMap_RemoveKey_1768 - 0x00500710 in the original binary.
 *
 * NAMED (2026-10-29): ATL7 CAtlMap::RemoveKey(key) for the 0x1768-node
 * int-keyed maps - the same member as IntMap_RemoveKey_14 (0x5009b0),
 * instruction for instruction, with only the node offsets moved:
 * GetNode is IntMap_Find_1768 (0x50072b, map in ECX = EBX, pPrev slot
 * zeroed at 0x500723); on a miss return false; otherwise unlink the node
 * through m_nHash at node+0x1764 and m_pNext at node+0x1760, hand it to
 * IntMap_FreeNode_1768 (0x50075f / 0x50077b) and return true.
 *
 * The instantiation is fixed by the named callees (find and free are
 * both the 0x1768 members).  Both binary callers remove an entry they
 * have just consumed.  CommP2PReceiveDatagram at 0x4ff8a6 runs it on the map at
 * peer-record+0x50 (`lea ebx,[esi+0x50]`, still live) with the same key
 * in EDI that IntMap_LookupPair_1768 found there at 0x4ff871, after
 * handing the found pair to the owner's vtable slot 0;
 * RetransmitPendingP2PDatagrams at 0x4ffd6e (`lea ebx,[ebp+0x64]`)
 * likewise follows a slot-0 call.  Look up,
 * consume, remove: the RemoveKey shape.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * REGISTERS PROMOTED (2026-08-25): a thin wrapper over the map find that
 * keeps all three of the find's out-slots in one 12-byte scratch local and
 * throws the result away.  The map arrives in EBX (`mov ecx,ebx` at 0x500721);
 * the key falls through from its caller.
 */
#include "ghidra_types.h"


undefined4 IntMap_RemoveKey_1768(int *regEbx,uint regEdi)

{
  int iVar1;
  int local_c [3];
  
  local_c[0] = 0;
  iVar1 = IntMap_Find_1768(regEbx,(undefined4 *)local_c,(uint *)(local_c + 1),(uint *)(local_c + 2),
               regEdi);
  if (iVar1 == 0) {
    return 0;
  }
  if (local_c[0] == 0) {
    *(undefined4 *)(*regEbx + (*(uint *)(iVar1 + 0x1764) % (uint)regEbx[2]) * 4) =
         *(undefined4 *)(iVar1 + 0x1760);
    IntMap_FreeNode_1768(iVar1,(int)regEbx);
    return 1;
  }
  *(undefined4 *)(local_c[0] + 0x1760) = *(undefined4 *)(iVar1 + 0x1760);
  IntMap_FreeNode_1768(iVar1,(int)regEbx);
  return 1;
}

