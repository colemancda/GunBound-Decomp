/* TreeReplaceNode - 0x00404d60 in the original binary.
 *
 * Replaces node param_1 by node regEax in a red-black tree: repoints the
 * parent's child slot (+0x108 / +0x10c, parent at +0x110), both children's
 * parent links, copies the colour (+0x104), and repoints the root slot
 * *param_2 if it held param_1.  Called from the delete fixup in
 * FUN_004048e0 with the deleted node and its in-order successor.  The same
 * node layout TreeLowerBound walks.
 *
 * RE-SLOTTED AND EAX RECOVERED (2026-08-24).  Tree-node "replace node ECX by
 * node EAX" (parent +0x110, children +0x108/+0x10c, colour +0x104, and the
 * root slot *EDX if it held ECX).  Sole call site 0x00404969 in FUN_004048e0,
 * the delete-fixup: ECX = the deleted node (its unaff_EBX, still open there),
 * EDX = its root-slot pointer (its regEax), EAX = the successor iVar2.  The
 * port passed nothing at all.
 */
#include "ghidra_types.h"


void __fastcall TreeReplaceNode(int param_1,int *param_2,int regEax)

{
  int iVar1;
  *(undefined4 *)(regEax + 0x110) = *(undefined4 *)(param_1 + 0x110);
  iVar1 = *(int *)(param_1 + 0x110);
  if (*(int *)(iVar1 + 0x108) == param_1) {
    *(int *)(iVar1 + 0x108) = regEax;
  }
  else {
    *(int *)(iVar1 + 0x10c) = regEax;
  }
  *(undefined4 *)(regEax + 0x10c) = *(undefined4 *)(param_1 + 0x10c);
  *(undefined4 *)(regEax + 0x108) = *(undefined4 *)(param_1 + 0x108);
  *(undefined4 *)(regEax + 0x104) = *(undefined4 *)(param_1 + 0x104);
  *(int *)(*(int *)(regEax + 0x10c) + 0x110) = regEax;
  *(int *)(*(int *)(regEax + 0x108) + 0x110) = regEax;
  if (*param_2 == param_1) {
    *param_2 = regEax;
  }
  return;
}

