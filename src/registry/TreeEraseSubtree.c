/* TreeEraseSubtree - 0x0040c210 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * VC7 STL _Tree::_Erase(_Nodeptr): recursively free a whole subtree -
 * recurse into the right child (offset +8), then free the current node
 * and iterate down the left child (offset 0) until _Isnil (offset
 * +0x11). This is the private subtree-destroyer the public erase(iterator)
 * overload (TreeErase, 0x40b600) is paired with in the standard library,
 * distinct from it by exactly that public/private split. Its only two
 * callers are itself (the right-child recursion) and TreeEraseRange,
 * whose own header names it explicitly: "subtree-delete the root
 * (head->_Parent) via FUN_0040c210" on the erase(begin,end) fast path
 * over &g_valueGuardMap - confirmed same 0x14-byte node shape
 * (_Isnil at +0x11) TreeInsertRebalance's header attributes to that map.
 */
#include "ghidra_types.h"


void TreeEraseSubtree(int *param_1)

{
  char cVar1;
  int *piVar2;

  cVar1 = *(char *)((int)param_1 + 0x11);
  while (cVar1 == '\0') {
    TreeEraseSubtree(param_1[2]);
    piVar2 = (int *)*param_1;
    _free(param_1);
    param_1 = piVar2;
    cVar1 = *(char *)((int)piVar2 + 0x11);
  }
  return;
}

