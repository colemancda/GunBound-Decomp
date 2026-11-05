/* Tree_RotateLeft_18 - 0x00443b00 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00443b00 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. VC7 STL _Tree::_Lrotate for the same
 * 0x18-byte-node instantiation as Tree_RotateRight_18 (0x4437e0), of which
 * it is the exact mirror (left +0, parent +4, right +8, isnil +0x15; root
 * at head + 4 where the head sentinel is at tree + 4). With x the node and
 * the tree on the stack: y = x.right; x.right = y.left, re-parenting that
 * child unless it is nil; y.parent = x.parent; the root, x's parent's left
 * or its right is repointed to y; then y.left = x and x.parent = y, so the
 * right child is promoted. Its only caller is the erase rebalance at
 * 0x443840, in the mirror arm of the sibling cases.
 */
#include "ghidra_types.h"


void __thiscall Tree_RotateLeft_18(int param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  
  piVar1 = *(int **)(param_1 + 8);
  *(int *)(param_1 + 8) = *piVar1;
  if (*(char *)(*piVar1 + 0x15) == '\0') {
    *(int *)(*piVar1 + 4) = param_1;
  }
  piVar1[1] = *(int *)(param_1 + 4);
  if (param_1 == *(int *)(*(int *)(param_2 + 4) + 4)) {
    *(int **)(*(int *)(param_2 + 4) + 4) = piVar1;
    *piVar1 = param_1;
    *(int **)(param_1 + 4) = piVar1;
    return;
  }
  piVar2 = *(int **)(param_1 + 4);
  if (param_1 == *piVar2) {
    *piVar2 = (int)piVar1;
    *piVar1 = param_1;
    *(int **)(param_1 + 4) = piVar1;
    return;
  }
  piVar2[2] = (int)piVar1;
  *piVar1 = param_1;
  *(int **)(param_1 + 4) = piVar1;
  return;
}

