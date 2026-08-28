/* StringMap_RemoveAll_ac - 0x00500140 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-08-28): ATL7's CAtlMap<K,V>::RemoveAll out of VC7.1's
 * atlcoll.h, for the 0xac-node instantiation. The class is settled from
 * outside - HashMap_Construct (0x4fe420) is the CAtlMap constructor over
 * this object and pins its members, FUN_00500e30 is CAtlMap::PickSize
 * with atlcoll.h's s_anPrimes table at 0x557850 - and the body is the
 * member verbatim: raise m_nLockCount at +0x20, sweep every bin of the
 * +0 array over the +8 bin count handing each node to
 * StringMap_FreeNode_ac, delete[] the bin array, zero m_nElements at +4,
 * InitHashTable(PickSize(0), false), free the +0x28 plex chain with
 * +0x2c nulled, then drop m_nLockCount again. See
 * StringMap_RemoveAll_CString for the line-by-line correspondence.
 *
 * The instantiation is the one StringMap_Find_ac and
 * StringMap_Insert_ac serve: the node this sweep steps through by +0xa4
 * is the node StringMap_FreeNode_ac retires, and FUN_00504050 ties that
 * node to StringMap_Find_ac directly. Its own caller is
 * DestroyCommEngine, which passes the map at +0xa4 of the comm engine.
 */
#include "ghidra_types.h"


void StringMap_RemoveAll_ac(int *regEax)

{
  int iVar1;
  int iNode;
  int *piVar2;
  undefined4 uVar3;
  int *_Memory;
  uint uVar4;
  undefined4 uVar5;
  
  regEax[8] = regEax[8] + 1;
  if ((*regEax != 0) && (uVar4 = 0, regEax[2] != 0)) {
    do {
      iVar1 = *(int *)(*regEax + uVar4 * 4);
      while (iVar1 != 0) {
        /* DROPPED-REG FIX 2026-08-28: the original captures the node in
           EAX before advancing (`mov eax,edi / mov edi,[edi+0xa4]`), so
           the retired node is the one BEFORE the step. */
        iNode = iVar1;
        iVar1 = *(int *)(iVar1 + 0xa4);
        StringMap_FreeNode_ac(iNode,(int)regEax);
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < (uint)regEax[2]);
  }
  _free((void *)*regEax);
  *regEax = 0;
  regEax[1] = 0;
  if (regEax[8] == 0) {
    uVar5 = 0;
    uVar3 = FUN_00500e30(0);
    HashMap_InitHashTable(regEax,uVar3,uVar5);
  }
  _Memory = (int *)regEax[10];
  regEax[0xb] = 0;
  if (_Memory != (int *)0x0) {
    do {
      piVar2 = (int *)*_Memory;
      _free(_Memory);
      _Memory = piVar2;
    } while (piVar2 != (int *)0x0);
    regEax[10] = 0;
  }
  regEax[8] = regEax[8] + -1;
  return;
}

