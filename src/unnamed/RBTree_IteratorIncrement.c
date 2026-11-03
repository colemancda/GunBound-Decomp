/* RBTree_IteratorIncrement - 0x00405040 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): sibling of RBTree_Insert and
 * RBTree_RemoveNode, which describe the 0x114-byte node with children at
 * +0x108/+0x10c, parent at +0x110 and the nil head at tree+0x14. The walk
 * is std::_Tree::_Inc on that node layout: leftmost of the right subtree,
 * else climb until coming from a left child. Its mirror is
 * RBTree_IteratorDecrement (0x4050a0). The node is in EAX and the tree in
 * the stack argument.
 */
#include "ghidra_types.h"


int RBTree_IteratorIncrement(int param_1,int regEax)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (regEax != 0) {
    iVar3 = *(int *)(regEax + 0x108);
    iVar1 = *(int *)(param_1 + 0x14);
    if (iVar3 == iVar1) {
      iVar3 = *(int *)(regEax + 0x110);
      if (*(int *)(regEax + 0x110) != iVar1) {
        do {
          iVar2 = iVar3;
          iVar3 = iVar2;
          if (regEax != *(int *)(iVar2 + 0x108)) break;
          iVar3 = *(int *)(iVar2 + 0x110);
          regEax = iVar2;
        } while (iVar3 != iVar1);
        if (iVar3 != iVar1) {
          return iVar3;
        }
      }
    }
    else if (iVar3 != 0) {
      for (iVar2 = *(int *)(iVar3 + 0x10c); iVar2 != iVar1; iVar2 = *(int *)(iVar2 + 0x10c)) {
        iVar3 = iVar2;
      }
      return iVar3;
    }
  }
  return 0;
}

