/* IntMap_GetNextAssoc_14 - 0x00500ba0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00500ba0 mean this function.)
 *
 * NAMED (2026-11-04), CERTAIN. ATL7 CAtlMap::GetNextAssoc(pos, key, value)
 * for the 0x14-node int-keyed map (m_pNext at node+0xc, hash at +0x10, as
 * in IntMap_RemoveKey_14). Advance the position to node->m_pNext, or, when
 * that is NULL, to the next non-empty bin after hash % m_nBins; then
 * return the node's key (+0) and its two-dword value (+4, +8). The map
 * arrives in EBX and the position is passed by reference, as the CAtlMap
 * member takes it. Caller evidence: CommP2PReceiveDatagram's enumerate
 * loop starts from IntMap_GetStartPosition_14, calls this with the
 * position, a key local and a FILETIME local, compares that FILETIME
 * against GetSystemTimeAsFileTime (the value IntMap_SetAt_14 stored just
 * above) and, when more than 60000 ms old, passes the key local to
 * IntMap_RemoveKey_14 on the same map.
 */
#include "ghidra_types.h"


void IntMap_GetNextAssoc_14(int *param_1,undefined4 *param_2,undefined4 *param_3,int *regEbx)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  puVar1 = (undefined4 *)*param_1;
  if (puVar1 == (undefined4 *)0x0) {
    iVar4 = 0;
  }
  else {
    iVar4 = puVar1[3];
    if (iVar4 == 0) {
      uVar3 = (uint)puVar1[4] % (uint)regEbx[2];
      do {
        uVar3 = uVar3 + 1;
        if ((uint)regEbx[2] <= uVar3) break;
        iVar2 = *(int *)(*regEbx + uVar3 * 4);
        if (iVar2 != 0) {
          iVar4 = iVar2;
        }
      } while (iVar4 == 0);
    }
  }
  *param_1 = iVar4;
  *param_2 = *puVar1;
  *param_3 = puVar1[1];
  param_3[1] = puVar1[2];
  return;
}

