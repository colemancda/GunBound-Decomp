/* AtlArray_GetAt_450 - 0x00426570 in the original binary.
 *
 * NAMED (2026-10-29): ATL7 CAtlArray<E>::GetAt(iElement) for the
 * 0x450-byte avatar-item element - the same member as the unsuffixed
 * AtlArray_GetAt (0x415450, 4-byte stride), at this element's stride:
 *
 *   if (iElement >= m_nSize)              cmp eax,[ecx+4]; jb
 *     AtlThrow(E_INVALIDARG);             push 0x80070057; call 0x4010c0
 *   return m_pData[iElement];             [ecx] + eax*0x450
 *
 * Container and stride are fixed from outside the body.  All 30 binary
 * call sites (every one in FUN_00445450) load ECX the same way, `add
 * ecx,0x44e20` on g_clientContext, which is the owned-item array
 * AtlArray_RemoveAll_450's header identifies among the four 0x450-element
 * CAtlArrays at +0x44e20/+0x44e30/+0x44e40/+0x44e50, and whose element
 * size AtlArray_SetCount_450 and the 0x450-stride renderers confirm.
 *
 * Convention: ECX = the array, EAX = the index, plain `ret`.  All 30 C
 * call sites in FUN_00445450.c are still argless (they drop both
 * registers), and the definition still reads the index from an
 * uninitialised in_EAX local; recovering them is a separate fix.  The _450
 * suffix follows AtlArray_SetCount_450 / AtlArray_RemoveAll_450.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


int __fastcall AtlArray_GetAt_450(int *param_1)

{
  uint in_EAX;
  
  if ((uint)param_1[1] <= in_EAX) {
                    /* WARNING: Subroutine does not return */
    ThrowCxxException(0x80070057);
  }
  return in_EAX * 0x450 + *param_1;
}

