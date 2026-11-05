/* RBTree_RotateLeft - 0x00404c40 in the original binary.
 * (FUN_00404dd0 in the notes below is RBTree_LinkNode's old symbol.)
 * (Historical notes below: FUN_00404e60 is now RBTree_RemoveRebalance.)
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00404c40 mean this function.)
 *
 * NAMED (2026-11-04), CERTAIN. Left rotation of the red-black tree whose
 * 0x114-byte nodes carry colour +0x104 and left/right/parent
 * +0x108/+0x10c/+0x110, root at tree+0 and nil sentinel at tree+0x14.
 * Those field roles are fixed from outside by RBTree_Insert's header:
 * FUN_00404dd0, the descent half, links the new node under the parent's
 * +0x108 or +0x10c and stores the parent at +0x110. The node arrives in
 * EAX and the tree in ECX (unchanged here, callers pass EAX=node,
 * ECX=EDI=tree). The body hoists the node's right child (+0x10c), gives
 * the node that child's left (+0x108), re-parents it, and splices the
 * child into the node's old slot (tree+0 when the old parent is the nil).
 * Callers: RBTree_Insert (orig 0x4049a0) uses it in the textbook fix-up
 * arms - rotate the parent left when the new node is a right child under a
 * left-child parent, rotate the grandparent left in the mirror arm - and
 * the erase fix-up FUN_00404e60 (three sites). Mirror of
 * RBTree_RotateRight (0x404cd0). No suffix: RBTree_Insert's header records
 * this as the only instantiation of the tree in the image.
 */
#include "ghidra_types.h"


void __fastcall RBTree_RotateLeft(int *param_1)

{
  int iVar1;
  int iVar2;
  int in_EAX;
  
  if (in_EAX == 0) {
    return;
  }
  iVar1 = *(int *)(in_EAX + 0x10c);
  *(undefined4 *)(in_EAX + 0x10c) = *(undefined4 *)(iVar1 + 0x108);
  if (*(int *)(iVar1 + 0x108) != param_1[5]) {
    *(int *)(*(int *)(iVar1 + 0x108) + 0x110) = in_EAX;
  }
  *(undefined4 *)(iVar1 + 0x110) = *(undefined4 *)(in_EAX + 0x110);
  iVar2 = *(int *)(in_EAX + 0x110);
  if (iVar2 == param_1[5]) {
    *param_1 = iVar1;
    *(int *)(iVar1 + 0x108) = in_EAX;
    *(int *)(in_EAX + 0x110) = iVar1;
    return;
  }
  if (in_EAX == *(int *)(iVar2 + 0x108)) {
    *(int *)(iVar2 + 0x108) = iVar1;
    *(int *)(iVar1 + 0x108) = in_EAX;
    *(int *)(in_EAX + 0x110) = iVar1;
    return;
  }
  *(int *)(iVar2 + 0x10c) = iVar1;
  *(int *)(iVar1 + 0x108) = in_EAX;
  *(int *)(in_EAX + 0x110) = iVar1;
  return;
}

