/* StringMap_Rehash_10 - 0x00409e20 in the original binary.
 *
 * NAMED (2026-10-29): ATL7 CAtlMap::Rehash(nBins) for the 0x10-node
 * string maps, matched against atlcoll.h statement for statement:
 *
 *   if (nBins == 0) nBins = PickSize(m_nElements)   HashMap_PickSize,
 *                                                   0x409e55, EAX = [map+4]
 *   if (nBins == m_nBins) return                    cmp edi,[esi+8]
 *   if (m_ppBins == NULL) {
 *     InitHashTable(nBins, false); return }         HashMap_InitHashTable
 *                                                   (0x500c00), push 0
 *   ppBins = new CNode*[nBins], zeroed              operator new + rep stosd
 *   relink every node into ppBins[m_nHash % nBins]  div on [node+0xc]
 *   delete[] m_ppBins; m_ppBins = ppBins            _free (0x525421)
 *   m_nBins = nBins
 *   m_nHiRehashThreshold = m_fHiThreshold * nBins   +0x18 from +0x14
 *   m_nLoRehashThreshold = m_fLoThreshold * nBins   +0x1c from +0x10
 *   if (m_nLoRehashThreshold < 17) ... = 0          cmp eax,0x11
 *
 * The class is fixed from outside: every one of the four binary callers
 * calls it with (map, PickSize(...)) in the threshold arm that NewNode
 * and FreeNode share (count past +0x18 or under +0x1c, lock at +0x20
 * clear) - StringMap_Insert_Int (0x409dd4), StringMap_Insert_CString
 * (0x426a22), StringMap_FreeNode_CString (0x415701) and
 * HashTable_OnNodeRemoved (0x409f93).
 *
 * WHY _10.  The relink reads m_pNext at node+8 and m_nHash at node+0xc,
 * which is the 0x10-byte node (4-byte key, 4-byte value) and no other.
 * Every other node size has its own copy with the hash read further in:
 * IntMap_Rehash_14 (+0x10, 0x14 node), FUN_00500440 (+0x18, 0x1c),
 * FUN_00500300 (+0x24, 0x28), FUN_00405150 (+0x28, 0x2c), FUN_00500ce0
 * (+0xa8, 0xac) and FUN_00501070 (+0x1764, 0x1768).  It serves both the
 * CString-valued and the int-valued 0x10
 * maps (its callers include both inserts), so the suffix is the stride,
 * as on StringMap_Find_10, not a value type.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void StringMap_Rehash_10(int *param_1,uint param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  uint uVar6;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00537880) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  if (param_2 == 0) {
    param_2 = HashMap_PickSize();
  }
  if (param_2 != param_1[2]) {
    if (*param_1 == 0) {
      HashMap_InitHashTable(param_1,param_2,0);
      return;
    }
    local_8 = 0;
    puVar2 = operator_new(param_2 * 4);
    local_8 = 0xffffffff;
    uVar6 = param_2;
    puVar5 = puVar2;
    if (puVar2 == (undefined4 *)0x0) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x8007000e);
    }
    for (; uVar6 != 0; uVar6 = uVar6 - 1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    uVar6 = 0;
    if (param_1[2] != 0) {
      do {
        iVar3 = *(int *)(*param_1 + uVar6 * 4);
        while (iVar3 != 0) {
          uVar4 = *(uint *)(iVar3 + 0xc) % param_2;
          iVar1 = *(int *)(iVar3 + 8);
          *(undefined4 *)(iVar3 + 8) = puVar2[uVar4];
          puVar2[uVar4] = iVar3;
          iVar3 = iVar1;
        }
        uVar6 = uVar6 + 1;
      } while (uVar6 < (uint)param_1[2]);
    }
    _free((void *)*param_1);
    *param_1 = (int)puVar2;
    param_1[2] = param_2;
    iVar3 = FloatToInt64();
    param_1[6] = iVar3;
    uVar6 = FloatToInt64();
    param_1[7] = uVar6;
    if (uVar6 < 0x11) {
      param_1[7] = 0;
    }
  }
  return;
}

