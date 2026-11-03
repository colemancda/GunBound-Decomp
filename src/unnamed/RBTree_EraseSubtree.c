/* RBTree_EraseSubtree - 0x004054c0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): sole caller is FUN_00401a70. The body
 * recurses on the +0x108/+0x10c children (the 0x114-byte node of
 * RBTree_Insert), runs the CString destructor (CString_DestructThunk,
 * 0x405300) on the node key, pushes the node on the free list at tree+8
 * and decrements the count at tree+4, which is std::_Tree::_Erase (post-
 * order subtree free into the node pool).
 */
#include "ghidra_types.h"


void __thiscall RBTree_EraseSubtree(int param_1,int param_2)

{
  if (param_2 != *(int *)(param_1 + 0x14)) {
    /* Ghidra dropped the recursive calls' `this` (param_1) arg - this is
     * a binary-tree walk: same container `this`, left/right child nodes
     * at param_2+0x108/+0x10c passed as the node argument. */
    RBTree_EraseSubtree(param_1,*(undefined4 *)(param_2 + 0x108));
    RBTree_EraseSubtree(param_1,*(undefined4 *)(param_2 + 0x10c));
    CString_DestructThunk();
    *(undefined4 *)(param_2 + 0x108) = *(undefined4 *)(param_1 + 8);
    *(int *)(param_1 + 8) = param_2;
    *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + -1;
  }
  return;
}

