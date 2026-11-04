/* RBTree_RotateRight - 0x00404cd0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-11-04), CERTAIN. Right rotation, the mirror of
 * RBTree_RotateLeft (0x404c40), on the same 0x114-byte-node tree (left
 * +0x108, right +0x10c, parent +0x110, root tree+0, nil tree+0x14; field
 * roles per RBTree_Insert's header). It hoists the node's LEFT child,
 * gives the node that child's right, re-parents it and splices the child
 * into the node's old slot. In RBTree_Insert's fix-up it is the
 * grandparent rotation of the left-parent arm and the parent rotation of
 * the mirror arm - the pairing CLRS RB-INSERT-FIXUP prescribes - and
 * FUN_00404e60 (the erase fix-up) is its only other caller. No suffix:
 * only one instantiation of this tree exists.
 */
#include "ghidra_types.h"


void __fastcall RBTree_RotateRight(int *param_1)

{
  int iVar1;
  int iVar2;
  int in_EAX;
  
  if (in_EAX == 0) {
    return;
  }
  iVar1 = *(int *)(in_EAX + 0x108);
  *(undefined4 *)(in_EAX + 0x108) = *(undefined4 *)(iVar1 + 0x10c);
  if (*(int *)(iVar1 + 0x10c) != param_1[5]) {
    *(int *)(*(int *)(iVar1 + 0x10c) + 0x110) = in_EAX;
  }
  *(undefined4 *)(iVar1 + 0x110) = *(undefined4 *)(in_EAX + 0x110);
  iVar2 = *(int *)(in_EAX + 0x110);
  if (iVar2 == param_1[5]) {
    *param_1 = iVar1;
    *(int *)(iVar1 + 0x10c) = in_EAX;
    *(int *)(in_EAX + 0x110) = iVar1;
    return;
  }
  if (in_EAX == *(int *)(iVar2 + 0x10c)) {
    *(int *)(iVar2 + 0x10c) = iVar1;
    *(int *)(iVar1 + 0x10c) = in_EAX;
    *(int *)(in_EAX + 0x110) = iVar1;
    return;
  }
  *(int *)(iVar2 + 0x108) = iVar1;
  *(int *)(iVar1 + 0x10c) = in_EAX;
  *(int *)(in_EAX + 0x110) = iVar1;
  return;
}

