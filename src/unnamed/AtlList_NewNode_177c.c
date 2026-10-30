/* AtlList_NewNode_177c - 0x00504420 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-30), CERTAIN: ATL7 CAtlList<E>::NewNode(element,
 * pPrev, pNext) for the comm connection's pending-send list, whose node
 * stride is 0x177c (hence the suffix, per the tree's container
 * convention). The list is EBX, and its layout is CAtlList's exactly:
 * m_pHead +0, m_pTail +4, m_nElements +8 (incremented here), m_pBlocks
 * +0xc and m_pFree +0x10 (both maintained by the GetFreeNode callee,
 * AtlList_GetFreeNode_177c), m_nBlockSize +0x14. That has no vptr, so
 * it is not MFC's CObject-derived CList. Member for member:
 * GetFreeNode, take m_pFree and its successor, placement-new the element at node+8
 * (guarded by new's null test, 0x504430/0x504434), m_pFree =
 * successor, node->m_pNext (+0) = pNext, node->m_pPrev (+4) = pPrev,
 * ++m_nElements, return the node.
 *
 * External confirmation from the one caller, CommConnectionSendOrQueue
 * (0x5038d7): it passes EBX = conn+0x20 (`add ebx,0x20` at 0x5038ca,
 * EBX being the connection loaded at 0x503851), pPrev = [ebx+4] (the
 * list tail, conn+0x24) and pNext = 0, then links the returned node
 * after the old tail or installs it as the head and makes it the new
 * tail - CAtlList::AddTail inlined around this call. The element is
 * the 6000-byte frame buffer with its length at +0x1770, and its
 * copy-constructor copies only that many bytes (rep movs at
 * 0x504436-0x50445a).
 *
 * FIXED (2026-10-30), all proven at the single call site:
 *  1. EBX, the list, was read as an uninitialised unaff_EBX. Promoted
 *     to the trailing regEbx (the Vector_Insert_34 shape), and
 *     CommConnectionSendOrQueue passes conn+0x20.
 *  2. The return value was a hard 0 under a note claiming no caller
 *     used it. The original returns the node in EAX (`mov eax,[ebx+0x10]`
 *     at 0x50442d, untouched to the `ret 0xc` at 0x504476), and the
 *     caller links it as the new tail and returns `node != 0` - so
 *     every queued send was being linked as NULL and reported as failed.
 *  3. Caller side: CommConnectionSendOrQueue's element was split by
 *     Ghidra into a 6000-byte buffer and a separate length local; the
 *     copy-ctor here reads the length at element+0x1770, so the two are
 *     coalesced there into one 0x1774-byte object.
 */
#include "ghidra_types.h"


undefined4 AtlList_NewNode_177c(undefined4 *param_1,undefined4 param_2,undefined4 param_3,
                                int regEbx)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  int unaff_EBX = regEbx;
  undefined4 *puVar5;
  
  FUN_00504730(unaff_EBX);
  puVar1 = *(undefined4 **)(unaff_EBX + 0x10);
  uVar2 = *puVar1;
  if (puVar1 != (undefined4 *)0x0) {
    puVar1[0x5de] = param_1[0x5dc];
    uVar4 = param_1[0x5dc];
    puVar5 = puVar1 + 2;
    for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *puVar5 = *param_1;
      param_1 = param_1 + 1;
      puVar5 = puVar5 + 1;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined1 *)puVar5 = *(undefined1 *)param_1;
      param_1 = (undefined4 *)((int)param_1 + 1);
      puVar5 = (undefined4 *)((int)puVar5 + 1);
    }
  }
  *(undefined4 *)(unaff_EBX + 0x10) = uVar2;
  *puVar1 = param_3;
  puVar1[1] = param_2;
  *(int *)(unaff_EBX + 8) = *(int *)(unaff_EBX + 8) + 1;
  /* CORRECTED (2026-10-30): this used to `return 0`, on the belief that
   * no caller used the result. EAX at the `ret 0xc` (0x504476) is still
   * the node loaded at 0x50442d, and CommConnectionSendOrQueue links it
   * as the list's new tail - see the header. */
  return (undefined4)puVar1;
}

