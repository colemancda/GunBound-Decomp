/* FUN_0044c5f0 - 0x0044c5f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
*
 * DROPPED REGISTER RECOVERED (2026-08-27): unaff_EDI is the array, and it is
 * `g_clientContext + 0x44e20 / 0x44e30 / 0x44e40 / 0x44e50` -- four separate
 * arrays of the same 0x450-byte element.  Every site has the identical
 * two-instruction shape `mov edi,[0x5b3484]` (g_clientContext) then
 * `add edi,0x44eN0` directly before the call, and the constant differs per
 * site, so each one carries its own witness and no ordering assumption is
 * needed.  The two pairs of back-to-back calls take consecutive arrays.
 *
 * The body is CAtlArray<T>::RemoveAll for that element -- destructor loop
 * over m_nSize, free(m_pData), then m_pData/m_nSize/m_nMaxSize zeroed --
 * i.e. exactly the `nNewSize == 0` arm of AtlArray_SetCount_450 (0x44c7b0),
 * which walks the same 0x450 stride and calls the same FUN_00426810
 * per-element destructor.  The callers corroborate the container reading:
 * both files pass these same bases to FUN_0044c630 on the next line, and
 * FUN_0044bf00 _qsort's `*(void **)(g_clientContext + 0x44e40)` with
 * `*(size_t *)(g_clientContext + 0x44e44)` as the count and 0x450 as the
 * element width -- the m_pData/m_nSize pair at +0/+4 of one of them.
 */
#include "ghidra_types.h"


void FUN_0044c5f0(int *regEdi)

{
  int iVar1;
  int iVar2;
  int *unaff_EDI = regEdi;
  
  iVar2 = *unaff_EDI;
  if (iVar2 != 0) {
    for (iVar1 = unaff_EDI[1]; iVar1 != 0; iVar1 = iVar1 + -1) {
      FUN_00426810(iVar2);
      iVar2 = iVar2 + 0x450;
    }
    _free((void *)*unaff_EDI);
    *unaff_EDI = 0;
  }
  unaff_EDI[1] = 0;
  unaff_EDI[2] = 0;
  return;
}

