/* RBTree_RemoveNode - 0x004048e0 in the original binary.
 *
 * The erase half of the custom red-black tree whose insert half is the
 * already-named RBTree_Insert (0x4049a0): same node layout throughout -
 * colour at +0x104, left/right children at +0x108/+0x10c, parent at
 * +0x110, nil sentinel at tree+0x14 (regEax[5]) - which RBTree_Insert's
 * own header pinned from FUN_00404dd0's __mbsicmp descent.  Given
 * (regEax = the tree, regEbx = a node), it unlinks the node: find the
 * in-order successor via FUN_004050a0 when the node has two children,
 * splice, run the delete fixup FUN_00404e60 (the only other user of the
 * two rotation helpers, per RBTree_Insert's header) when the spliced
 * node was black, swap the successor into the node's place via
 * TreeReplaceNode (0x404d60, whose header already describes this exact
 * call), then push the removed node onto the tree's freelist (head at
 * tree+8, reusing the node's +0x108 as the link) and decrement the
 * count at tree+4.  Returns true, or false for a null node.
 *
 * The one binary call site, 0x40323c in FUN_00403170, removes the node
 * a FUN_00404b00 name lookup on the same owner+0x1be4 tree just
 * returned - erase-after-dispatch of the messenger's pending records.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


uint RBTree_RemoveNode(int *regEax,int regEbx)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (regEbx != 0) {
    iVar1 = regEax[5];
    iVar2 = regEbx;
    if ((*(int *)(regEbx + 0x108) != iVar1) && (*(int *)(regEbx + 0x10c) != iVar1)) {
      iVar2 = FUN_004050a0(regEax,regEbx);
    }
    iVar3 = *(int *)(iVar2 + 0x108);
    if (iVar3 == iVar1) {
      iVar3 = *(int *)(iVar2 + 0x10c);
    }
    *(undefined4 *)(iVar3 + 0x110) = *(undefined4 *)(iVar2 + 0x110);
    iVar1 = *(int *)(iVar2 + 0x110);
    if (iVar1 == regEax[5]) {
      *regEax = iVar3;
    }
    else if (iVar2 == *(int *)(iVar1 + 0x108)) {
      *(int *)(iVar1 + 0x108) = iVar3;
    }
    else {
      *(int *)(iVar1 + 0x10c) = iVar3;
    }
    if (*(int *)(iVar2 + 0x104) == 1) {
      FUN_00404e60();
    }
    if (iVar2 != regEbx) {
      TreeReplaceNode((int)regEbx,regEax,iVar2);
    }
    if (*regEax != 0) {
      *(int *)(*regEax + 0x110) = regEax[5];
    }
    thunk_FUN_00405320();
    iVar1 = regEax[2];
    *(int *)(regEbx + 0x108) = iVar1;
    regEax[1] = regEax[1] + -1;
    regEax[2] = regEbx;
    return CONCAT31((int3)((uint)iVar1 >> 8),1);
  }
  return (uint)regEax & 0xffffff00;
}

