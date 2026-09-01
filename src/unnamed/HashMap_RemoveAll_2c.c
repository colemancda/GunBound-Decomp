/* HashMap_RemoveAll_2c - 0x00404b90 in the original binary.
 *
 * ATL7 CAtlMap::RemoveAll - HashMap_Construct's header already lists
 * this address among "the RemoveAll bodies" beside the named
 * StringMap_RemoveAll_ac / StringMap_RemoveAll_CString, and the member
 * is verbatim: bracket with the m_nLockCount at map+0x20 (regEax[8],
 * ATL's DisableAutoRehash/EnableAutoRehash), walk m_ppBins over m_nBins
 * (regEax[2]) freeing every chained node through HashMap_FreeNode_2c
 * (0x405290, named with it), free the bin array, re-InitHashTable at
 * PickSize(0) (FUN_00500e30) when unlocked, and free the plex chain at
 * map+0x28 (regEax[10]).
 *
 * The _2c suffix is the node stride: this instantiation's next pointer
 * is at node+0x24, and in every sized sibling the ATL CNode tail
 * (m_pNext, m_nHash) sits at stride-8/stride-4 - StringMap_Insert_28's
 * nodes link at +0x20/+0x24, StringMap_FreeNode_ac's at +0xa4/+0xa8 -
 * so next at +0x24 means 0x2c-byte nodes.  The HashMap_ prefix (not
 * StringMap_/IntMap_) because the key type is unprovable from what
 * survives: neither this member nor the FreeNode touches key or value
 * (both POD), and no Find/Insert of this instantiation exists in the
 * image.  Its one map is at +0x1bfc of the messenger object destructed
 * by FUN_00401a70 (the only binary caller); nothing else references
 * that map, so a key-claiming prefix would be invented.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void HashMap_RemoveAll_2c(int *regEax)

{
  int iVar1;
  int *piVar2;
  int iVar5;
  undefined4 uVar3;
  int *_Memory;
  uint uVar4;
  undefined4 uVar5;
  
  regEax[8] = regEax[8] + 1;
  if ((*regEax != 0) && (uVar4 = 0, regEax[2] != 0)) {
    do {
      iVar1 = *(int *)(*regEax + uVar4 * 4);
      while (iVar1 != 0) {
        iVar5 = iVar1;
        iVar1 = *(int *)(iVar1 + 0x24);
        HashMap_FreeNode_2c(iVar5,(int)regEax);
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
  regEax[0xb] = 0;
  _Memory = (int *)regEax[10];
  if ((int *)regEax[10] != (int *)0x0) {
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

