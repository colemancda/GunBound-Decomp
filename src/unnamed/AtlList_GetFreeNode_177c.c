/* AtlList_GetFreeNode_177c - 0x00504730 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-30), CERTAIN: ATL7 CAtlList<E>::GetFreeNode() for the
 * 0x177c-stride pending-send list, the helper its one caller
 * AtlList_NewNode_177c invokes first, exactly as CAtlList::NewNode
 * begins with GetFreeNode(). The list arrives in ESI, which that caller
 * sets as `mov esi,ebx` at 0x504426 (EBX being its own list, conn+0x20
 * at its call site); the port already passes it as regEsi. Member for
 * member: when m_pFree (+0x10) is NULL, CAtlPlex::Create inlined -
 * malloc(m_nBlockSize (+0x14) * 0x177c + 4), the plex's 4-byte next
 * link pushed onto m_pBlocks (+0xc) - with AtlThrow(E_OUTOFMEMORY)
 * (ThrowCxxException(0x8007000e) at 0x504781) on failure; then the
 * block's nodes are threaded onto m_pFree from the last one (plex+4 +
 * (n-1)*0x177c, the `lea eax,[edx+eax-0x1778]` at 0x504764) down to
 * the first.
 */
#include "ghidra_types.h"


void AtlList_GetFreeNode_177c(int regEsi)

{
  undefined4 *puVar1;
  int iVar2;
  
  if (*(int *)(regEsi + 0x10) == 0) {
    puVar1 = _malloc(*(int *)(regEsi + 0x14) * 0x177c + 4);
    if (puVar1 == (undefined4 *)0x0) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x8007000e);
    }
    *puVar1 = *(undefined4 *)(regEsi + 0xc);
    *(undefined4 **)(regEsi + 0xc) = puVar1;
    iVar2 = *(int *)(regEsi + 0x14);
    puVar1 = puVar1 + iVar2 * 0x5df + -0x5de;
    if (-1 < iVar2 + -1) {
      do {
        *puVar1 = *(undefined4 *)(regEsi + 0x10);
        *(undefined4 **)(regEsi + 0x10) = puVar1;
        puVar1 = puVar1 + -0x5df;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
  }
  return;
}

