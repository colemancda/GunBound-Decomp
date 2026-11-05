/* AtlArray_RemoveAt_4004 - 0x004e5cc0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004e5cc0 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. Evidence from outside the body:
 * CAtlArray::RemoveAt(iElement = EAX, nElements = EBX) over 0x4004-byte
 * elements, array in EDI (data +0, count +4): `if (iElement + nElements >
 * m_nSize) AtlThrow(E_INVALIDARG)` (ThrowCxxException(0x80070057)),
 * memmove the tail down, m_nSize -= nElements, with no destructor loop
 * (POD elements, as in AtlArray_RemoveAt). The array is the connection
 * send queue at conn + 0x24a40 that CArray_Grow_4004 grows; sole caller
 * HandleSocketEvent pops one element (RemoveAt(0, 1)) after a send().
 * Prefix is AtlArray_ by the tree's behaviour rule (E_INVALIDARG throw),
 * not CArray_ as the sibling CArray_Grow_4004 is spelled; LIKELY because
 * the sibling spelling may reflect a reading of the same array that was
 * not rechecked.
 */
#include "ghidra_types.h"


void AtlArray_RemoveAt_4004(int regEbx,int regEax,int *regEdi)

{
  int iVar1;
  
  if ((uint)regEdi[1] < (uint)(regEax + regEbx)) {
                    /* WARNING: Subroutine does not return */
    ThrowCxxException(0x80070057);
  }
  iVar1 = (regEdi[1] - regEax) - regEbx;
  if (iVar1 != 0) {
    _memmove((void *)(regEax * 0x4004 + *regEdi),
             (void *)((regEax + regEbx) * 0x4004 + *regEdi),iVar1 * 0x4004);
  }
  regEdi[1] = regEdi[1] - regEbx;
  return;
}

