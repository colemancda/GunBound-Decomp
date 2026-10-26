/* TreeSubtreeMin - 0x0040bd00 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * VC7 STL _Tree::_Min: walk a subtree's _Left pointer (offset 0) until
 * _Isnil (offset 0x11) is set, returning the leftmost (minimum) node.
 * This is the same 0x14-byte node shape (_Left/_Parent/_Right, key at
 * +0xc, colour at +0x10, _Isnil at +0x11) TreeInsertRebalance's own
 * header documents for &g_valueGuardMap. Its only caller is the
 * erase(iterator) overload (0x40b600, now TreeErase) over that same map
 * - called there to find the in-order successor's minimum when the node
 * being erased has two children, textbook `_Tree::erase`'s splice step.
 */
#include "ghidra_types.h"


void TreeSubtreeMin(int *regEax)

{
  char cVar1;
  int *piVar2;

  piVar2 = (int *)*regEax;
  cVar1 = *(char *)((int)piVar2 + 0x11);
  while (cVar1 == '\0') {
    piVar2 = (int *)*piVar2;
    cVar1 = *(char *)((int)piVar2 + 0x11);
  }
  return;
}

