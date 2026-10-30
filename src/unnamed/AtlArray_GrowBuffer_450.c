/* AtlArray_GrowBuffer_450 - 0x0042af40 in the original binary.
 *
 * NAMED (2026-10-29): ATL7 CAtlArray<E>::GrowBuffer(nNewSize) for the
 * 0x450-byte avatar-item element, the member AtlArray_SetCount_450's
 * header already maps it to.  Both callers are members of that one
 * instantiation and use it the way atlcoll.h does:
 *
 * - AtlArray_SetCount_450 (0x44c838): `else if (nNewSize > m_nMaxSize)
 *   { if (!GrowBuffer(nNewSize)) return false; }` - EAX = the new count.
 * - AtlArray_Add_450 (0x42ae56), CAtlArray::Add (AtlArray_RemoveAll_450's
 *   header names it): `if (iElement >= m_nMaxSize) { if
 *   (!GrowBuffer(iElement + 1)) AtlThrow(E_OUTOFMEMORY); }` - EAX =
 *   m_nSize + 1, and the failure arm is ThrowCxxException(0x8007000e).
 *
 * The body is GrowBuffer's own: return true when nNewSize fits
 * m_nMaxSize; with no buffer, malloc max(nNewSize, m_nGrowBy) elements;
 * otherwise grow by m_nGrowBy or, when that is 0, by ATL's
 * clamp(m_nSize / 8, 4, 1024) (0x42af80-0x42af99), malloc, memmove the
 * live elements (_memmove 0x525790), _free the old block, and return a
 * bool in AL.  The _450 suffix separates it from the unsuffixed
 * AtlArray_GrowBuffer (0x50ed30), the 4-byte widget-child instantiation
 * of the same member.
 *
 * Calling convention: nNewSize in EAX and the array in ESI, plain `ret`.
 * The port read the array through an uninitialised unaff_ESI and both C
 * call sites passed only the size (fixed below).
 *
 * ESI PROMOTED (2026-10-29): the array is now the trailing regEsi
 * parameter, aliased to the old unaff_ESI name in the body the way
 * AtlArray_GrowBuffer.c (0x50ed30) aliases its thisArray.  Both binary
 * callers set ESI to the array before the call:
 *   0x42ae56 in AtlArray_Add_450: `mov esi,ecx` (0x42ae46), ECX = that
 *     function's param_1; witness `mov edi,[esi+4]` / `lea eax,[edi+1]`
 *     (0x42ae4c/0x42ae53) is the port's `param_1[1] + 1` size argument.
 *   0x44c838 in AtlArray_SetCount_450: ESI is the array its whole body
 *     reads; witness `cmp edi,[esi+8]` (0x44c806) is the port's
 *     `param_2[2] < param_1` test, and `mov eax,edi` (0x44c836) the
 *     size param_1, so ESI = param_2.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


undefined4 AtlArray_GrowBuffer_450(uint regEax,int *regEsi)

{
  void *pvVar1;
  uint uVar2;
  int *unaff_ESI = regEsi;
  
  if (regEax <= (uint)unaff_ESI[2]) {
    return 1;
  }
  uVar2 = unaff_ESI[3];
  if (*unaff_ESI == 0) {
    if (regEax < uVar2) {
      regEax = uVar2;
    }
    pvVar1 = _malloc(regEax * 0x450);
    *unaff_ESI = (int)pvVar1;
    if (pvVar1 != (void *)0x0) {
      unaff_ESI[2] = regEax;
      return 1;
    }
  }
  else {
    if (uVar2 == 0) {
      uVar2 = (uint)unaff_ESI[1] >> 3;
      if (uVar2 < 4) {
        uVar2 = 4;
      }
      else if (0x400 < uVar2) {
        uVar2 = 0x400;
      }
    }
    uVar2 = uVar2 + unaff_ESI[2];
    if (uVar2 <= regEax) {
      uVar2 = regEax;
    }
    pvVar1 = _malloc(uVar2 * 0x450);
    if (pvVar1 != (void *)0x0) {
      _memmove(pvVar1,(void *)*unaff_ESI,unaff_ESI[1] * 0x450);
      _free((void *)*unaff_ESI);
      *unaff_ESI = (int)pvVar1;
      unaff_ESI[2] = uVar2;
      return 1;
    }
  }
  return 0;
}

