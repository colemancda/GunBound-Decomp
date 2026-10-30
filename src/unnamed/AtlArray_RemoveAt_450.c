/* AtlArray_RemoveAt_450 - 0x0044c6a0 in the original binary.
 *
 * NAMED (2026-10-29): ATL7 CAtlArray<E>::RemoveAt(iElement, nElements)
 * for the 0x450-byte avatar-item record - the member
 * AtlArray_RemoveAll_450's header already identified at this address.
 * atlcoll.h's body in order: `if (iElement + nElements > m_nSize)
 * AtlThrow(E_INVALIDARG)` (the 0x80070057 push at 0x44c6b5); nMoveCount
 * = m_nSize - (iElement + nElements); CallDestructors inlined as a
 * 0x450-stride loop over AtlArray_DestroyElement_450 (0x44c6e5); memmove
 * the tail down (0x44c720); m_nSize -= nElements (0x44c733).  Array on
 * the stack (`ret 4`), iElement in EAX, nElements in EDI.
 *
 * What fixes the instantiation from outside: the per-element callee is
 * the 0x450 family's own named destructor and the stride is `imul
 * esi,esi,0x450`; and all four binary callers pass one of the arrays the
 * rest of the family serves, with nElements = 1 (EDI): State07's
 * avatar-store handler at 0x44496b and 0x444dad (g_clientContext +
 * 0x44e20) and 0x444ddf (+0x44e30), and FUN_0050a320's Avatar-Store
 * reorder at 0x50a42e (+0x44e20), which follows it with
 * AtlArray_InsertAt_450 on the same array.  The unsuffixed
 * AtlArray_RemoveAt (0x415470, POD 4-byte elements) and
 * AtlArray_RemoveAt_CString (0x4264d0) are the same template member at
 * other instantiations, hence the stride suffix.
 *
 * INDEX PROMOTED (2026-10-29).  iElement arrives in EAX (`mov esi,eax` at
 * 0x44c6a9, then `lea ebp,[esi+edi]` / `imul esi,esi,0x450`); it was the
 * undeclared `in_EAX`, so no C site passed it.  It is now the trailing
 * `regEax` parameter and all four sites pass it:
 *   0x44496b, 0x444dad, 0x444ddf (State07): the PeekChecksumStateUnderLock
 *     (0x40a4d0) result of the call just before each - 0x444954, 0x444d96,
 *     0x444dc8 - on this+0x3054c, EAX untouched up to the call;
 *   0x50a42e (FUN_0050a320): `mov eax,[ebp+0x94]` at 0x50a41c, EBP = this.
 * FUN_0050a320.cpp carries its own extern declaration, updated to match.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void AtlArray_RemoveAt_450(int *param_1,int regEdi,int regEax)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if ((uint)param_1[1] < (uint)(regEax + regEdi)) {
                    /* WARNING: Subroutine does not return */
    ThrowCxxException(0x80070057);
  }
  iVar1 = (param_1[1] - regEax) - regEdi;
  iVar2 = *param_1 + regEax * 0x450;
  for (iVar3 = regEdi; iVar3 != 0; iVar3 = iVar3 + -1) {
    AtlArray_DestroyElement_450(iVar2);
    iVar2 = iVar2 + 0x450;
  }
  if (iVar1 != 0) {
    _memmove((void *)(*param_1 + regEax * 0x450),(void *)((regEax + regEdi) * 0x450 + *param_1),
             iVar1 * 0x450);
  }
  param_1[1] = param_1[1] - regEdi;
  return;
}

