/* IntMap_RemoveKey_14 - 0x005009b0 in the original binary.
 *
 * NAMED (2026-10-29): ATL7 CAtlMap::RemoveKey(key) for the 0x14-node
 * int-keyed maps, atlcoll.h's VC7.1 body with RemoveNode inlined:
 * pPrev = NULL; pNode = GetNode(key, iBin, nHash, pPrev) - the call to
 * IntMap_Find_14 at 0x5009cb, map in ECX = EBX, with the pPrev slot
 * zeroed first (0x5009c3); if no node, return false (`xor al,al`);
 * otherwise unlink it - m_ppBins[pNode->m_nHash % m_nBins] = m_pNext
 * when pPrev is NULL (m_nHash read at node+0x10, m_pNext at +0xc,
 * m_nBins at map+8), else pPrev->m_pNext = pNode->m_pNext - hand it to
 * IntMap_FreeNode_14 (0x5009f9 / 0x500a0f, node in EAX, map in ESI) and
 * return true (`mov al,1`).
 *
 * The instantiation is fixed by the named callees: the find and the
 * free are both the 0x14-node members, so the suffix follows them.  The
 * one binary caller, CommP2PReceiveDatagram at 0x4ffb93, removes the key EDI from
 * the map at peer-record+0x20 inside its enumerate-and-expire loop
 * (FUN_00500b70 / FUN_00500ba0 walk the same map; an entry whose stored
 * FILETIME is more than 60000 ms old, `cmp eax,0xea60`, is removed) -
 * the shape a RemoveKey caller has.  IntMap_RemoveKey_1768 (0x500710)
 * is the same member for the 0x1768-node instantiation.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * REGISTERS PROMOTED (2026-08-25): a thin wrapper over the map find that
 * keeps all three of the find's out-slots in one 12-byte scratch local and
 * throws the result away.  The map arrives in EBX (`mov ecx,ebx` at 0x5009c1);
 * the key falls through from its caller.
 */
#include "ghidra_types.h"


undefined4 IntMap_RemoveKey_14(int *regEbx,uint regEdi)

{
  int iVar1;
  int local_c [3];
  
  local_c[0] = 0;
  iVar1 = IntMap_Find_14(regEbx,(undefined4 *)local_c,(uint *)(local_c + 1),(uint *)(local_c + 2),
               regEdi);
  if (iVar1 == 0) {
    return 0;
  }
  if (local_c[0] == 0) {
    *(undefined4 *)(*regEbx + (*(uint *)(iVar1 + 0x10) % (uint)regEbx[2]) * 4) =
         *(undefined4 *)(iVar1 + 0xc);
    IntMap_FreeNode_14(iVar1,(int)regEbx);
    return 1;
  }
  *(undefined4 *)(local_c[0] + 0xc) = *(undefined4 *)(iVar1 + 0xc);
  IntMap_FreeNode_14(iVar1,(int)regEbx);
  return 1;
}

