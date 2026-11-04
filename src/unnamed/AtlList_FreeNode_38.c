/* AtlList_FreeNode_38 - 0x005006c0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-11-04), LIKELY. ATL7 CAtlList::FreeNode(pNode) for the comm
 * engine's list at engine+4 (0x38-byte nodes, see AtlList_NewNode_38).
 * Member for member: destroy the element (FUN_00500f90, which is add
 * ecx,0x18 / jmp 0x501010 - node+8 is where the element starts), push the
 * node onto the free list (node->m_pNext = m_pFree (+0x10), m_pFree =
 * node), decrement m_nElements (+8) and call RemoveAll
 * (AtlList_RemoveAll_38) when the count reaches zero.
 * CommConnectionList_Erase and FUN_004fddd0 carry the same sequence
 * inlined. Sole caller is AtlList_RemoveAll_38, whose loop pops the head
 * and hands it here. LIKELY on the suffix only: the body is stride-
 * independent and the 0x38 comes from the one list that uses it.
 */
#include "ghidra_types.h"


void __thiscall AtlList_FreeNode_38(int param_1,undefined4 *param_2)

{
  int iVar1;
  
  FUN_00500f90();
  *param_2 = *(undefined4 *)(param_1 + 0x10);
  iVar1 = *(int *)(param_1 + 8) + -1;
  *(undefined4 **)(param_1 + 0x10) = param_2;
  *(int *)(param_1 + 8) = iVar1;
  if (iVar1 == 0) {
    AtlList_RemoveAll_38();
  }
  return;
}

