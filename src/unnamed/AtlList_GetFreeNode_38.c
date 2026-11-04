/* AtlList_GetFreeNode_38 - 0x00501510 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-11-04), CERTAIN. ATL7 CAtlList::GetFreeNode for the
 * 0x38-byte-node list at comm engine+4, the same member as
 * AtlList_GetFreeNode_177c (0x504730) with only the stride changed. When
 * m_pFree (+0x10) is NULL: CAtlPlex::Create inlined - malloc(m_nBlockSize
 * (+0x14) * 0x38 + 4), the plex's 4-byte next link pushed onto m_pBlocks
 * (+0xc), AtlThrow(E_OUTOFMEMORY) (0x8007000e) on failure - then the
 * block's nodes are threaded onto m_pFree from the last (plex+4 +
 * (n-1)*0x38) down to the first. The list arrives in ESI, which is the EAX
 * that AtlList_NewNode_38 (0x500fa0, the sole caller) received: its entry
 * is push esi / mov esi,eax and the call follows at once. The 0x38 stride
 * matches the element NewNode fills (8 link bytes, a six-dword source
 * record at node+8, dwords 8-0xc zeroed, dword 0xd = 10) for the list
 * ConfigureAsyncSocket appends to at engine+4.
 *
 * ESI RECOVERED (2026-08-25): FUN_00500fa0's entry is `push esi; mov esi,eax`
 * and the call follows immediately, so ESI is that caller's own incoming EAX.
 * NOTE: FUN_00500fa0's EAX is itself an open backlog item; when it becomes a
 * parameter the argument at that call site is renamed with it.
 */
#include "ghidra_types.h"


void AtlList_GetFreeNode_38(int regEsi)

{
  undefined4 *puVar1;
  int iVar2;
  
  if (*(int *)(regEsi + 0x10) == 0) {
    puVar1 = _malloc(*(int *)(regEsi + 0x14) * 0x38 + 4);
    if (puVar1 == (undefined4 *)0x0) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x8007000e);
    }
    *puVar1 = *(undefined4 *)(regEsi + 0xc);
    *(undefined4 **)(regEsi + 0xc) = puVar1;
    iVar2 = *(int *)(regEsi + 0x14);
    puVar1 = puVar1 + iVar2 * 0xe + -0xd;
    if (-1 < iVar2 + -1) {
      do {
        *puVar1 = *(undefined4 *)(regEsi + 0x10);
        *(undefined4 **)(regEsi + 0x10) = puVar1;
        puVar1 = puVar1 + -0xe;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
  }
  return;
}

