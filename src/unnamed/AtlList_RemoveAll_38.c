/* AtlList_RemoveAll_38 - 0x004ff6d0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-11-04), LIKELY. ATL7 CAtlList::RemoveAll for the list at
 * comm engine+4 (the same 0x38-byte-node list AtlList_NewNode_38 appends
 * to from ConfigureAsyncSocket). Member for member: while m_nElements (+8)
 * is non-zero pop m_pHead (+0) and FreeNode it (AtlList_FreeNode_38), then
 * m_pHead, m_pTail (+4) and m_pFree (+0x10) = NULL, free the plex chain at
 * m_pBlocks (+0xc) block by block and clear it. Callers:
 * DestroyCommP2POwner (ESI = owner+4, the list), CommConnectionList_Erase
 * (the inlined FreeNode tail: when the count reaches zero), CommEngineDrainAndCloseConnections
 * (same tail) and AtlList_FreeNode_38 - FreeNode's last act in ATL is to
 * call RemoveAll when the count reaches zero, and that is what the three
 * inlined tails and the out-of-line one do. LIKELY on the suffix only: the
 * body is stride-independent, and the 0x38 comes from the one list all
 * callers hold.
 */
#include "ghidra_types.h"


void AtlList_RemoveAll_38(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *unaff_ESI;
  
  iVar1 = unaff_ESI[2];
  while (iVar1 != 0) {
    puVar2 = (undefined4 *)*unaff_ESI;
    *unaff_ESI = *puVar2;
    AtlList_FreeNode_38(puVar2);
    iVar1 = unaff_ESI[2];
  }
  *unaff_ESI = 0;
  unaff_ESI[1] = 0;
  unaff_ESI[4] = 0;
  puVar2 = (undefined4 *)unaff_ESI[3];
  while (puVar2 != (undefined4 *)0x0) {
    puVar3 = (undefined4 *)*puVar2;
    _free(puVar2);
    puVar2 = puVar3;
  }
  unaff_ESI[3] = 0;
  return;
}

