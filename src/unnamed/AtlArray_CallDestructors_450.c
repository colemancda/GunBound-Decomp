/* AtlArray_CallDestructors_450 - 0x00426700 in the original binary.
 *
 * NAMED (2026-10-29): ATL7 CAtlArray<E>::CallDestructors(pElements,
 * nElements) for the 0x450-byte avatar-item element - run ~E on each of
 * nElements records at 0x450 stride (`add esi,0x450`, 0x426716) through
 * the element destructor at 0x426810.  The name comes from the one
 * caller: AtlArray_SetCount_450's `else if (nNewSize < m_nSize)` arm
 * (0x44c819-0x44c829) passes ECX = &m_pData[nNewSize] (`imul ecx,ecx,
 * 0x450; add ecx,edx`) and EAX = m_nSize - nNewSize, which is exactly
 * SetCount's `CallDestructors(m_pData + nNewSize, m_nSize - nNewSize)`,
 * then stores m_nSize = nNewSize.  Its constructor twin is 0x44c870,
 * which SetCount calls from the growing arm.
 *
 * Convention: ECX = first element, EAX = count, plain `ret`; the port's
 * __fastcall + trailing regEax already carries both.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void __fastcall AtlArray_CallDestructors_450(int param_1,int regEax)

{
  
  for (; regEax != 0; regEax = regEax + -1) {
    FUN_00426810(param_1);
    param_1 = param_1 + 0x450;
  }
  return;
}

