/* LocalizedStrings_EraseSubtree - 0x004158a0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004158a0 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. Evidence from outside the body: the caller
 * is LocalizedStrings_Clear, which invokes it on both children of the root
 * (node+0xc and node+0x10) of g_localizedStringTable. Each node it frees
 * is a LocalizedStrings_BuyNode node, whose CString value sits at node+4;
 * the dtor call goes through the 0x4158e0 thunk to 0x4158f0 (add ecx,4 /
 * jmp CString_Destruct), i.e. destroy the CString at node+4. It then
 * pushes the node on the free list at map+8 and decrements the count at
 * map+4, the same post-order erase as RBTree_EraseSubtree but on this
 * map's 0x18-byte nodes. The thunk at 0x4158e0 is left unnamed.
 */
#include "ghidra_types.h"


void __thiscall LocalizedStrings_EraseSubtree(int param_1,int param_2)

{
  if (param_2 != *(int *)(param_1 + 0x14)) {
    /* Ghidra dropped the recursive calls' `this` (param_1) arg - binary-
     * tree walk: same container `this`, left/right child nodes at
     * param_2+0xc/+0x10 passed as the node argument. */
    LocalizedStrings_EraseSubtree(param_1,*(undefined4 *)(param_2 + 0xc));
    LocalizedStrings_EraseSubtree(param_1,*(undefined4 *)(param_2 + 0x10));
    thunk_FUN_004158f0();
    *(undefined4 *)(param_2 + 0xc) = *(undefined4 *)(param_1 + 8);
    *(int *)(param_1 + 8) = param_2;
    *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + -1;
  }
  return;
}

