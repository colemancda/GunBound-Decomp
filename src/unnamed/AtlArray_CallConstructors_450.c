/* AtlArray_CallConstructors_450 - 0x0044c870 in the original binary.
 *
 * NAMED (2026-10-29): ATL7 CAtlArray<E>::CallConstructors(pElements,
 * nElements) for the 0x450-byte avatar-item element, including its
 * exception path:
 *
 *   _ATLTRY {
 *     for (i = 0; i < nElements; i++)
 *       ::new (pElements + i) E;          0x44c8a3-0x44c8bd: i*0x450 +
 *   }                                     base, null test, call 0x428550
 *   _ATLCATCHALL() {
 *     while (i > 0) { i--;                catch block 0x44c8bf-0x44c8e0
 *       pElements[i].~E(); }              walks back calling 0x426810
 *     _ATLRETHROW;                        push 0; push 0; call 0x528798
 *   }
 *
 * Both binary callers are members of the same instantiation and call
 * it where atlcoll.h does:
 *
 * - AtlArray_SetCount_450 (0x44c857), the growing arm `else if
 *   (nNewSize > m_nSize) CallConstructors(m_pData + m_nSize, nNewSize -
 *   m_nSize)`: pushes m_nSize*0x450 + m_pData and nNewSize - m_nSize.
 * - FUN_0050cff0 (0x50d0c4), CAtlArray::InsertAt
 *   (AtlArray_CopyElement_450's header): after the memmove that opens the
 *   hole, `CallConstructors(m_pData + iElement, nElements)`.
 *
 * Its destructor twin is AtlArray_CallDestructors_450 (0x426700).
 *
 * Convention: plain __cdecl, (pElements, nElements) on the stack and a
 * bare `ret`; SetCount pops with `add esp,8` (0x44c85c), InsertAt folds
 * the 8 bytes into its `add esp,0x14` at 0x50d0cf.  The C port is
 * missing the catch block
 * (Ghidra did not decompile the funclet) and still registers SEH through
 * the uninitialised `unaff_FS_OFFSET`; neither is changed by this rename.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void AtlArray_CallConstructors_450(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined1 local_8;
  undefined3 uStack_7;
  
  puStack_c = &LAB_0053ac45;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  uStack_7 = 0;
  for (uVar2 = 0; uVar2 < param_2; uVar2 = uVar2 + 1) {
    iVar1 = uVar2 * 0x450 + param_1;
    local_8 = 1;
    if (iVar1 != 0) {
      AtlArray_ConstructElement_450(iVar1);
    }
  }
  *unaff_FS_OFFSET = local_10;
  return;
}

