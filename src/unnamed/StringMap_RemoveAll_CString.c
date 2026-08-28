/* StringMap_RemoveAll_CString - 0x00415560 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED-REG FIX (2026-08-28): EAX is the map, read at 0x415562 by
 * `mov edi,eax` before anything writes it. The body walks every bucket
 * of the table at +0, hands each node to StringMap_FreeNode_CString,
 * frees the bucket array, and re-initialises the table when the nesting
 * counter at +0x20
 * has returned to zero.
 *
 * The bucket sweep also needed a correction. The original is
 * `mov eax,esi / mov esi,[esi+8] / call 0x4156d0` at 0x415590: it
 * captures the node FIRST and advances the cursor SECOND. The port
 * advanced first and called with no arguments, so the node was lost;
 * writing the call in terms of the already-advanced iVar1 would have
 * retired the wrong node, and the last node of each bucket would have
 * been retired as a null. The captured value gets a local of its own.
 *
 * All three sites resolve. FUN_00418dc0 passes two arena offsets with
 * `lea eax,[edi+0x6aa44c]` and `lea eax,[edi+0x6aa41c]` at
 * 0x418e76/0x418e81 - an ADDRESS, which callsite_regs.py renders
 * identically to a load. The third arrives through
 * FUN_005432f0 -> thunk_FUN_00415560, a two-step tail jump that begins
 * `mov eax,0x794e14`: the atexit destructor for DAT_00794e14.
 *
 * NAMED (2026-08-28): ATL7's CAtlMap<K,V>::RemoveAll out of VC7.1's
 * atlcoll.h, for the same instantiation as StringMap_FreeNode_CString -
 * see that file for why the suffix is a value type rather than the node
 * stride. The class comes from outside this function: HashMap_Construct
 * (0x4fe420) is the CAtlMap constructor over this object and pins the
 * member offsets, and FUN_00500e30 is CAtlMap::PickSize, reading
 * atlcoll.h's own s_anPrimes table at 0x557850. Against that map the
 * body is the member verbatim, in order:
 *
 *   DisableAutoRehash()                   m_nLockCount++  at +0x20
 *   for each bin, for each node,          the +0 bin array over the
 *       FreeNode(pKill)                   +8 bin count
 *   delete[] m_ppBins; m_ppBins = NULL    +0
 *   m_nElements = 0                       +4
 *   InitHashTable(PickSize(0), false)     HashMap_InitHashTable, second
 *                                         argument 0 = bAllocNow false
 *   FreePlexes()                          +0x2c = NULL, free the +0x28
 *                                         chain
 *   EnableAutoRehash()                    m_nLockCount--
 *
 * The `if (m_nLockCount == 0)` around InitHashTable is dead in every
 * instantiation - DisableAutoRehash has just raised the count - and it
 * is present here exactly as the template writes it, which is a small
 * extra confirmation that this is library source and not hand-written.
 */
#include "ghidra_types.h"


void StringMap_RemoveAll_CString(int *regEax)

{
  int iVar1;
  int iNode;
  int *piVar2;
  int *in_EAX = regEax;
  undefined4 uVar3;
  int *_Memory;
  uint uVar4;
  undefined4 uVar5;
  
  in_EAX[8] = in_EAX[8] + 1;
  if ((*in_EAX != 0) && (uVar4 = 0, in_EAX[2] != 0)) {
    do {
      iVar1 = *(int *)(*in_EAX + uVar4 * 4);
      while (iVar1 != 0) {
        /* DROPPED-REG FIX 2026-08-28: the original captures the node in
           EAX before advancing (`mov eax,esi / mov esi,[esi+8]` at
           0x415590), so the retired node is the one BEFORE the step. */
        iNode = iVar1;
        iVar1 = *(int *)(iVar1 + 8);
        StringMap_FreeNode_CString(iNode,(int)in_EAX);
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < (uint)in_EAX[2]);
  }
  _free((void *)*in_EAX);
  *in_EAX = 0;
  in_EAX[1] = 0;
  if (in_EAX[8] == 0) {
    uVar5 = 0;
    uVar3 = FUN_00500e30(0);
    HashMap_InitHashTable(in_EAX,uVar3,uVar5);
  }
  in_EAX[0xb] = 0;
  _Memory = (int *)in_EAX[10];
  if ((int *)in_EAX[10] != (int *)0x0) {
    do {
      piVar2 = (int *)*_Memory;
      _free(_Memory);
      _Memory = piVar2;
    } while (piVar2 != (int *)0x0);
    in_EAX[10] = 0;
  }
  in_EAX[8] = in_EAX[8] + -1;
  return;
}

