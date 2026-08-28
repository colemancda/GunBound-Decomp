/* StringMap_FreeNode_CString - 0x004156d0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED-REG FIX (2026-08-28): both inputs are registers and both are
 * read before written. EAX is the node being retired - `mov esi,eax` at
 * 0x4156d1 is the first instruction after the prologue push - and EDI is
 * the map that owns it, first touched at 0x4156d8 by
 * `mov eax,[edi+0x2c]`.
 *
 * The body is a free-list push: the node's +8 link is set to the map's
 * current free head at +0x2c, the node becomes the new head, the live
 * count at +4 is decremented, and when that count falls below the
 * threshold at +0x1c (with the lock byte at +0x20 clear) the map is
 * shrunk. When the count reaches zero the whole block chain at +0x28 is
 * freed.
 *
 * Its one ported call site, in StringMap_RemoveAll_CString's bucket
 * sweep, also needed a correction beyond the arguments: the original
 * captures the node in
 * EAX and only then advances the cursor (`mov eax,esi / mov esi,[esi+8]`
 * at 0x415590), whereas the port advanced first and called with nothing,
 * so writing the argument as the already-advanced value would have
 * retired the wrong node. See that file.
 *
 * NAMED (2026-08-28): ATL7's CAtlMap<K,V>::FreeNode out of VC7.1's
 * atlcoll.h. The class is settled from outside this function -
 * HashMap_Construct (0x4fe420) is the CAtlMap constructor for this very
 * object and its header pins all twelve members, and FUN_00500e30 is
 * CAtlMap::PickSize, scanning atlcoll.h's own s_anPrimes table at
 * 0x557850. Against that field map the body is the member verbatim:
 *
 *   pNode->~CNode()                           CStringPair_DestroyThunk
 *   pNode->m_pNext = m_pFree                  +8 takes [map+0x2c]
 *   m_pFree = pNode                           [map+0x2c] = node
 *   m_nElements--                             [map+4]
 *   if (m_nElements < m_nLoRehashThreshold
 *       && !IsLocked()) Rehash(PickSize(...)) +0x1c, +0x20, FUN_00409e20
 *   if (m_nElements == 0) FreePlexes()        the +0x28 chain, +0x2c = 0
 *
 * WHY THE SUFFIX IS A TYPE AND NOT A STRIDE. The node here is 0x10 bytes
 * - key at +0, value at +4, m_pNext at +8, m_nHash at +0xc - but so is
 * the node of the OTHER +8-linked instantiation in this image, the one
 * whose FreeNode is HashTable_OnNodeRemoved (0x409f60) and whose
 * RemoveAll is FUN_00415600. A stride suffix could not tell the two
 * apart. What does tell them apart is the node destructor each calls:
 * this one's, at 0x415890, is `lea ecx,[esi+4]; call 0x405320` followed
 * by `mov ecx,esi; jmp 0x405320` - TWO CStringA releases, so both the
 * key and the value are CStringA - while 0x409f60 runs a single one on
 * node+0 (`mov ecx,edi; call 0x405300`, which tail-jumps to the same
 * 0x405320), leaving a 4-byte POD value. Hence
 * CAtlMap<CStringA,CStringA>, and the _CString suffix names the VALUE
 * type, on the AtlArray_RemoveAt_CString precedent.
 *
 * Its maps are the two the arena carries at +0x6aa41c and +0x6aa44c,
 * which StringMap_RemoveAll_CString is called on from FUN_00418dc0.
 */
#include "ghidra_types.h"


void StringMap_FreeNode_CString(int regEax,int regEdi)

{
  int *piVar1;
  int in_EAX = regEax;
  undefined4 uVar2;
  int *_Memory;
  uint uVar3;
  int unaff_EDI = regEdi;
  
  /* DROPPED-REG FIX 2026-08-28: the node's {CStringA,CStringA} pair is
     at its +0; ESI already holds the node (`mov esi,eax` at 0x4156d1). */
  CStringPair_DestroyThunk(in_EAX);
  *(undefined4 *)(in_EAX + 8) = *(undefined4 *)(unaff_EDI + 0x2c);
  uVar3 = *(int *)(unaff_EDI + 4) - 1;
  *(int *)(unaff_EDI + 0x2c) = in_EAX;
  *(uint *)(unaff_EDI + 4) = uVar3;
  if ((uVar3 < *(uint *)(unaff_EDI + 0x1c)) && (*(int *)(unaff_EDI + 0x20) == 0)) {
    uVar2 = FUN_00500e30();
    FUN_00409e20(unaff_EDI,uVar2);
  }
  if (*(int *)(unaff_EDI + 4) == 0) {
    _Memory = *(int **)(unaff_EDI + 0x28);
    *(undefined4 *)(unaff_EDI + 0x2c) = 0;
    if (_Memory != (int *)0x0) {
      do {
        piVar1 = (int *)*_Memory;
        _free(_Memory);
        _Memory = piVar1;
      } while (piVar1 != (int *)0x0);
      *(undefined4 *)(unaff_EDI + 0x28) = 0;
    }
  }
  return;
}

