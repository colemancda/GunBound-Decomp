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
 * call sites (every one in State07_AvatarStore_OnCommand) load ECX the same way, `add
 * ecx,0x44e20` on g_clientContext, which is the owned-item array
 * AtlArray_RemoveAll_450's header identifies among the four 0x450-element
 * CAtlArrays at +0x44e20/+0x44e30/+0x44e40/+0x44e50, and whose element
 * size AtlArray_SetCount_450 and the 0x450-stride renderers confirm.
 *
 * Convention: ECX = the array, EAX = the index, plain `ret`.  The _450
 * suffix follows AtlArray_SetCount_450 / AtlArray_RemoveAll_450.
 *
 * ARRAY AND INDEX PROMOTED (2026-10-29).  The definition read the index
 * from an uninitialised in_EAX local and all 30 C sites in State07_AvatarStore_OnCommand.c
 * were argless.  It is now (int *param_1, uint regEax) - the array first,
 * the EAX index trailing, as AtlArray_RemoveAt_450 does; __fastcall is
 * dropped because ECX here is an erased-__thiscall `this` and every caller
 * is raw C.  At every binary site ECX is `mov ecx,[0x5b3484]` / `add
 * ecx,0x44e20` (g_clientContext+0x44e20) and EAX is the result of the
 * PeekChecksumStateUnderLock (0x40a4d0) call immediately before it, on
 * this+0x3054c (the selected-item index guard; pushed as esi/ebx/edi,
 * each `lea r,[ebp+0x3054c]`), with no EAX write in between.  Each site
 * was checked individually; State07_AvatarStore_OnCommand.c's header lists the pairing.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


int AtlArray_GetAt_450(int *param_1,uint regEax)

{
  if ((uint)param_1[1] <= regEax) {
                    /* WARNING: Subroutine does not return */
    ThrowCxxException(0x80070057);
  }
  return regEax * 0x450 + *param_1;
}

