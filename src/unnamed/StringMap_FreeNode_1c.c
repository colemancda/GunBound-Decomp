/* StringMap_FreeNode_1c - 0x00500650 in the original binary.
 *
 * NAMED (2026-10-29): ATL7 CAtlMap::FreeNode for the 0x1c-node maps -
 * the member IntMap_FreeNode_1768 documents, at a smaller stride: push
 * the node onto m_pFree at map+0x2c through the node's m_pNext at
 * +0x14, drop m_nElements at map+4, Rehash (StringMap_Rehash_1c) at
 * PickSize when the count falls under map+0x1c with the lock at map+0x20
 * clear, and free the plex chain at map+0x28 when the map empties.  No
 * key or value destructor - POD node.
 *
 * WHICH INSTANTIATION, from the caller: both binary sites are in
 * FUN_004fe500 (0x4fe54f, 0x4fe564), which runs StringMap_Find_1c
 * (0x4fe520, map in EAX = ESI), unlinks the node it returned from its
 * bucket by reading +0x18 (m_nHash) and +0x14 (m_pNext), and hands that
 * node to this function in EAX with the same map still in ESI -
 * CAtlMap::RemoveKey's shape.  So the node is StringMap_Find_1c's, and
 * the prefix follows it.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * EAX and ESI RECOVERED (2026-08-25): EAX is the node its caller just found
 * or inserted (`mov eax,ecx` immediately before both calls) and ESI is the
 * map object, set once at the caller's entry and never rewritten -- the
 * linear trace reports `pop esi` only because one of the two sites sits in a
 * cold block past the epilogue.
 */
#include "ghidra_types.h"


void StringMap_FreeNode_1c(int regEax,int regEsi)

{
  int *piVar1;
  undefined4 uVar2;
  int *_Memory;
  uint uVar3;
  
  *(undefined4 *)(regEax + 0x14) = *(undefined4 *)(regEsi + 0x2c);
  uVar3 = *(int *)(regEsi + 4) - 1;
  *(int *)(regEsi + 0x2c) = regEax;
  *(uint *)(regEsi + 4) = uVar3;
  if ((uVar3 < *(uint *)(regEsi + 0x1c)) && (*(int *)(regEsi + 0x20) == 0)) {
    uVar2 = HashMap_PickSize();
    StringMap_Rehash_1c((int *)regEsi,uVar2);
  }
  if (*(int *)(regEsi + 4) == 0) {
    _Memory = *(int **)(regEsi + 0x28);
    *(undefined4 *)(regEsi + 0x2c) = 0;
    if (_Memory != (int *)0x0) {
      do {
        piVar1 = (int *)*_Memory;
        _free(_Memory);
        _Memory = piVar1;
      } while (piVar1 != (int *)0x0);
      *(undefined4 *)(regEsi + 0x28) = 0;
    }
  }
  return;
}

