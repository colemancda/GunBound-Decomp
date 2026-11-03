/* RBTree_IteratorDecrement - 0x004050a0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): exact mirror of RBTree_IteratorIncrement
 * (0x405040) with +0x108 and +0x10c swapped, on the same 0x114-byte node
 * tree used by RBTree_Insert and RBTree_RemoveNode; this is
 * std::_Tree::_Dec. Its caller is RBTree_RemoveNode.
 */
#include "ghidra_types.h"


int RBTree_IteratorDecrement(int param_1,int regEax)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (regEax != 0) {
    iVar3 = *(int *)(regEax + 0x10c);
    iVar1 = *(int *)(param_1 + 0x14);
    if (iVar3 == iVar1) {
      iVar3 = *(int *)(regEax + 0x110);
      if (*(int *)(regEax + 0x110) != iVar1) {
        do {
          iVar2 = iVar3;
          iVar3 = iVar2;
          if (regEax != *(int *)(iVar2 + 0x10c)) break;
          iVar3 = *(int *)(iVar2 + 0x110);
          regEax = iVar2;
        } while (iVar3 != iVar1);
        if (iVar3 != iVar1) {
          return iVar3;
        }
      }
    }
    else if (iVar3 != 0) {
      for (iVar2 = *(int *)(iVar3 + 0x108); iVar2 != iVar1; iVar2 = *(int *)(iVar2 + 0x108)) {
        iVar3 = iVar2;
      }
      return iVar3;
    }
  }
  return 0;
}

