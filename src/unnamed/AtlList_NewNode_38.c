/* AtlList_NewNode_38 - 0x00500fa0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00500fa0 mean this function.)
 *
 * NAMED (2026-11-04), CERTAIN. ATL7 CAtlList::NewNode(element, pPrev,
 * pNext) for the 0x38-byte-node list at comm engine+4, the same member as
 * AtlList_NewNode_177c (0x504420). Member for member: GetFreeNode
 * (AtlList_GetFreeNode_38), take m_pFree (+0x10) and its successor,
 * construct the element at node+8 when the node is non-null (a six-dword
 * copy from the source record in EDI, a zeroed tail, a trailing 10),
 * m_pFree = successor, node->m_pNext (+0) = pNext, node->m_pPrev (+4) =
 * pPrev, ++m_nElements (+8), return the node (mov eax,[esi+0x10] at
 * 0x500fa8 stays in EAX to the ret 8). External confirmation from the
 * caller ConfigureAsyncSocket (orig 0x4ff455-0x4ff47b): it passes the list
 * at engine+4 (EAX), pPrev = the tail at engine+8, pNext = 0 and the
 * freshly built source record in EDI, then links the returned node as the
 * new tail (or the head when the tail is NULL) - CAtlList::AddTail inlined
 * around this call.
 */
#include "ghidra_types.h"


undefined4 AtlList_NewNode_38(undefined4 param_1,undefined4 param_2,int regEax,undefined4 *regEdi)

{
  undefined4 *puVar1;
  
  AtlList_GetFreeNode_38(regEax);
  puVar1 = *(undefined4 **)(regEax + 0x10);
  if (puVar1 != (undefined4 *)0x0) {
    puVar1[8] = 0;
    puVar1[9] = 0;
    puVar1[10] = 0;
    puVar1[0xb] = 0;
    puVar1[0xc] = 0;
    puVar1[0xd] = 10;
    puVar1[2] = *regEdi;
    puVar1[3] = regEdi[1];
    puVar1[4] = regEdi[2];
    puVar1[5] = regEdi[3];
    puVar1[6] = regEdi[4];
    puVar1[7] = regEdi[5];
  }
  *(undefined4 *)(regEax + 0x10) = *puVar1;
  puVar1[1] = param_1;
  *puVar1 = param_2;
  *(int *)(regEax + 8) = *(int *)(regEax + 8) + 1;
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

