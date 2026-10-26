/* TreeIteratorIncrement - 0x0040c1b0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * VC7 STL _Tree::_Inc(_Nodeptr): if the node's right child (offset +8)
 * is not _Isnil, descend to that subtree's leftmost node; otherwise
 * climb _Parent (offset +4) while the node is its parent's right child,
 * textbook in-order iterator increment. Same 0x14-byte node shape
 * (_Left/_Parent/_Right, _Isnil at +0x11) TreeInsertRebalance's header
 * attributes to &g_valueGuardMap. Both call sites are inside that same
 * map's erase path: TreeEraseRange's own header names this function as
 * "the iterator increment" it uses when looping erase(first++) across a
 * range, and TreeErase (0x40b600) calls it once before unlinking the
 * node being erased - both confirmed g_valueGuardMap call sites, not a
 * shared instantiation (the sibling TurnEventSet tree's own increment
 * helper is the still-unnamed FUN_004e8f10, a different function with a
 * different, 0x10-byte node layout - offsets +0xe/+0xf instead of
 * +0x10/+0x11 - so the two are not folded together).
 */
#include "ghidra_types.h"


void __fastcall TreeIteratorIncrement(undefined4 param_1,int *param_2)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;

  iVar2 = *param_2;
  if (*(char *)(iVar2 + 0x11) == '\0') {
    piVar3 = *(int **)(iVar2 + 8);
    if (*(char *)((int)piVar3 + 0x11) == '\0') {
      cVar1 = *(char *)(*piVar3 + 0x11);
      piVar4 = (int *)*piVar3;
      while (cVar1 == '\0') {
        cVar1 = *(char *)(*piVar4 + 0x11);
        piVar3 = piVar4;
        piVar4 = (int *)*piVar4;
      }
      *param_2 = (int)piVar3;
      return;
    }
    iVar2 = *(int *)(iVar2 + 4);
    cVar1 = *(char *)(iVar2 + 0x11);
    while ((cVar1 == '\0' && (*param_2 == *(int *)(iVar2 + 8)))) {
      *param_2 = iVar2;
      iVar2 = *(int *)(iVar2 + 4);
      cVar1 = *(char *)(iVar2 + 0x11);
    }
    *param_2 = iVar2;
  }
  return;
}

