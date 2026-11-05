/* Tree_RotateRight_18 - 0x004437e0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004437e0 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. VC7 STL _Tree::_Rrotate for the 0x18-byte-
 * node instantiation of Tree_Init_18 and Tree_Buynode_18 (left +0, parent
 * +4, right +8, isnil +0x15; the head sentinel is at tree + 4 and its
 * parent field at head + 4 holds the root). With x the node in ECX and the
 * tree on the stack: y = x.left; x.left = y.right, re-parenting that child
 * unless it is nil; y.parent = x.parent; the root, x's parent's left or its
 * right is repointed to y depending on which slot x held; then y.right = x
 * and x.parent = y, so the left child is promoted. The only caller is the
 * erase rebalance at 0x443840, which uses it and its mirror
 * Tree_RotateLeft_18 (0x443b00) in the textbook sibling cases of the red-
 * black erase fix-up. The node pointer layout is corroborated by the
 * neighbours; the body contains no value access.
 */
#include "ghidra_types.h"


void __thiscall Tree_RotateRight_18(int *param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = *param_1;
  *param_1 = *(int *)(iVar1 + 8);
  if (*(char *)(*(int *)(iVar1 + 8) + 0x15) == '\0') {
    *(int **)(*(int *)(iVar1 + 8) + 4) = param_1;
  }
  *(int *)(iVar1 + 4) = param_1[1];
  if (param_1 == *(int **)(*(int *)(param_2 + 4) + 4)) {
    *(int *)(*(int *)(param_2 + 4) + 4) = iVar1;
    *(int **)(iVar1 + 8) = param_1;
    param_1[1] = iVar1;
    return;
  }
  piVar2 = (int *)param_1[1];
  if (param_1 == (int *)piVar2[2]) {
    piVar2[2] = iVar1;
    *(int **)(iVar1 + 8) = param_1;
    param_1[1] = iVar1;
    return;
  }
  *piVar2 = iVar1;
  *(int **)(iVar1 + 8) = param_1;
  param_1[1] = iVar1;
  return;
}

