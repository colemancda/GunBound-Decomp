/* AtlArray_SetCount_450 - 0x0044c7b0 in the original binary.
 *
 * ATL7 CAtlArray<T>::SetCount for the 0x450-byte element, matched statement
 * for statement against src/cxx/AtlArray.h:
 *
 *   if (nGrowBy != -1) m_nGrowBy = nGrowBy;          -> arr[3] = growBy
 *   if (nNewSize == 0) { destructors; free; 0; 0 }   -> the param_1 == 0 arm
 *   else if (nNewSize > m_nMaxSize) GrowBuffer(...)  -> arr[2] < newCount
 *   else if (nNewSize < m_nSize)   CallDestructors   -> FUN_00426700
 *   else if (nNewSize > m_nSize)   CallConstructors  -> FUN_0044c870
 *   m_nSize = nNewSize; return true;
 *
 * It is ATL and not MFC.  MFC's CArray::SetSize returns VOID and throws
 * CMemoryException when the reallocation fails; this one returns a bool and
 * propagates failure as 0 (`if (cVar1 == '\0') return 0;`), which is
 * CAtlArray::SetCount's contract.  Its GrowBuffer is FUN_0042af40 and its
 * per-element destructor FUN_00426810 -- both still unnamed; the sibling
 * AtlArray_GrowBuffer/AtlArray_RemoveAt in this tree belong to a different
 * element size, which is why this one carries the _450 suffix, as
 * CArray_Grow_1750/_4004/_206 do.
 *
 * DROPPED REGISTER PROMOTED (2026-08-27): in_EAX is nGrowBy, and it is the
 * literal -1 at all three call sites -- every caller uses the default
 * argument, so `or eax,0xffffffff` right before the call is the compiler
 * materialising CAtlArray's `int nGrowBy = -1`.  That is also what identifies
 * the parameter: the -1 sentinel is the first thing the body tests.
 *
 * (A fourth binary call at 0x50d14a is an SEH unwind funclet past
 * FUN_0050cff0's 0x126 bytes, with no ported C counterpart -- 3 C sites
 * against 4 binary sites is correct here.)
 */
#include "ghidra_types.h"


undefined1 __fastcall AtlArray_SetCount_450(uint param_1,int *param_2,int growBy)

{
  char cVar1;
  int in_EAX = growBy;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  if (in_EAX != -1) {
    param_2[3] = in_EAX;
  }
  if (param_1 == 0) {
    iVar4 = *param_2;
    if (iVar4 != 0) {
      for (iVar3 = param_2[1]; iVar3 != 0; iVar3 = iVar3 + -1) {
        FUN_00426810(iVar4);
        iVar4 = iVar4 + 0x450;
      }
      _free((void *)*param_2);
      *param_2 = 0;
    }
    param_2[1] = 0;
    param_2[2] = 0;
    return 1;
  }
  if ((uint)param_2[2] < param_1) {
    cVar1 = FUN_0042af40(param_1);
    if (cVar1 == '\0') {
      return 0;
    }
    uVar2 = param_2[1];
  }
  else {
    uVar2 = param_2[1];
    if (param_1 <= uVar2) {
      if (param_1 < uVar2) {
        FUN_00426700((int)(param_1 * 0x450 + *param_2),uVar2 - param_1);
        param_2[1] = param_1;
        return 1;
      }
      goto LAB_0044c85f;
    }
  }
  FUN_0044c870(uVar2 * 0x450 + *param_2,param_1 - uVar2);
LAB_0044c85f:
  param_2[1] = param_1;
  return 1;
}

