/* RBTree_RemoveRebalance - 0x00404e60 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00404e60 mean this function.)
 *
 * NAMED (2026-11-05), CERTAIN. Evidence from outside the body: The red-
 * black delete fix-up. Sole caller RBTree_RemoveNode runs it (node in EAX,
 * tree in EDI) when the spliced node was black, before TreeReplaceNode.
 * The body descends with sibling/uncle colour tests and calls only
 * RBTree_RotateLeft / RBTree_RotateRight, whose headers name this function
 * as their erase-side user. Node layout (colour +0x104, left +0x108, right
 * +0x10c, parent +0x110) is the one RBTree_Insert and RBTree_RemoveNode
 * pin. Counterpart of TurnEventSet_InsertRebalance for the other tree.
 */
#include "ghidra_types.h"


void RBTree_RemoveRebalance(void)

{
  int in_EAX;
  int iVar1;
  int iVar2;
  int *unaff_EDI;
  
  if (in_EAX == *unaff_EDI) {
    *(undefined4 *)(in_EAX + 0x104) = 1;
    return;
  }
  do {
    if (*(int *)(in_EAX + 0x104) != 1) break;
    iVar2 = *(int *)(in_EAX + 0x110);
    iVar1 = *(int *)(iVar2 + 0x108);
    if (in_EAX == iVar1) {
      iVar1 = *(int *)(iVar2 + 0x10c);
      if (*(int *)(iVar1 + 0x104) == 0) {
        *(undefined4 *)(iVar1 + 0x104) = 1;
        *(undefined4 *)(*(int *)(iVar1 + 0x110) + 0x104) = 0;
        RBTree_RotateLeft();
        iVar2 = *(int *)(in_EAX + 0x110);
        iVar1 = *(int *)(iVar2 + 0x10c);
      }
      if ((*(int *)(*(int *)(iVar1 + 0x108) + 0x104) != 1) ||
         (*(int *)(*(int *)(iVar1 + 0x10c) + 0x104) != 1)) {
        if (*(int *)(*(int *)(iVar1 + 0x10c) + 0x104) == 1) {
          *(undefined4 *)(*(int *)(iVar1 + 0x108) + 0x104) = 1;
          *(undefined4 *)(iVar1 + 0x104) = 0;
          RBTree_RotateRight();
          iVar2 = *(int *)(in_EAX + 0x110);
          iVar1 = *(int *)(iVar2 + 0x10c);
        }
        *(undefined4 *)(iVar1 + 0x104) = *(undefined4 *)(iVar2 + 0x104);
        *(undefined4 *)(*(int *)(in_EAX + 0x110) + 0x104) = 1;
        *(undefined4 *)(*(int *)(iVar1 + 0x10c) + 0x104) = 1;
        RBTree_RotateLeft();
        goto LAB_0040501c;
      }
LAB_00404eeb:
      *(undefined4 *)(iVar1 + 0x104) = 0;
      in_EAX = *(int *)(in_EAX + 0x110);
    }
    else {
      if (*(int *)(iVar1 + 0x104) == 0) {
        *(undefined4 *)(iVar1 + 0x104) = 1;
        *(undefined4 *)(*(int *)(iVar1 + 0x110) + 0x104) = 0;
        RBTree_RotateRight();
        iVar2 = *(int *)(in_EAX + 0x110);
        iVar1 = *(int *)(iVar2 + 0x108);
      }
      if ((*(int *)(*(int *)(iVar1 + 0x10c) + 0x104) == 1) &&
         (*(int *)(*(int *)(iVar1 + 0x108) + 0x104) == 1)) goto LAB_00404eeb;
      if (*(int *)(*(int *)(iVar1 + 0x108) + 0x104) == 1) {
        *(undefined4 *)(*(int *)(iVar1 + 0x10c) + 0x104) = 1;
        *(undefined4 *)(iVar1 + 0x104) = 0;
        RBTree_RotateLeft();
        iVar2 = *(int *)(in_EAX + 0x110);
        iVar1 = *(int *)(iVar2 + 0x108);
      }
      *(undefined4 *)(iVar1 + 0x104) = *(undefined4 *)(iVar2 + 0x104);
      *(undefined4 *)(*(int *)(in_EAX + 0x110) + 0x104) = 1;
      *(undefined4 *)(*(int *)(iVar1 + 0x108) + 0x104) = 1;
      RBTree_RotateRight();
LAB_0040501c:
      in_EAX = *unaff_EDI;
    }
  } while (in_EAX != *unaff_EDI);
  *(undefined4 *)(in_EAX + 0x104) = 1;
  return;
}

