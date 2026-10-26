/* TreeIteratorDecrement - 0x0040c150 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * VC7 STL _Tree::_Dec(_Nodeptr): the predecessor step. If the node is nil
 * (the header), return its _Right (+8) - the header's _Right is the
 * rightmost real node, so this is "one before begin() wraps to end()"
 * made concrete the usual STL way. Otherwise, if the node's _Left (+0) is
 * not nil, descend to that left subtree's maximum (walk _Right until
 * _Isnil). Otherwise climb _Parent (+4) while the node is its parent's
 * _Left child, textbook in-order iterator decrement. Same 0x14-byte node
 * shape (_Left/_Parent/_Right, _Isnil at +0x11) TreeInsertRebalance's
 * header attributes to &g_valueGuardMap.
 *
 * Direct disassembly of the original TreeInsert (0x40b540-0x40b5f4) shows
 * the sole call, at 0x40b5b3: `lea edx,[esp+0x14] / call 0x40c150`. That
 * call sits exactly where VC7's `_Tree::insert` computes the in-order
 * predecessor of the descent's last "went left" node (to compare keys
 * against it before deciding equal/insert-right) - `_Addleft` true but
 * the candidate node isn't already the tree's leftmost. TreeInsert.c's
 * current body is a deliberate bring-up neuter (see its own header) that
 * never reaches this call, so there is no live call site in the C tree
 * right now; the identity comes from the ORIGINAL binary's disassembly at
 * that call site, the same precedent already used for
 * TreeInsertRebalance.
 *
 * Structurally distinct from its mirror, TreeIteratorIncrement (0x40c1b0,
 * which checks _Right/_Left in the opposite roles and climbs while
 * "equal to parent's _Right"), and from TreeSubtreeMin (0x40bd00, which
 * only ever walks _Left and never touches _Parent or _Right) - no
 * collision with either.
 */
#include "ghidra_types.h"


void __fastcall TreeIteratorDecrement(undefined4 param_1,int *param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int *piVar4;

  piVar4 = (int *)*param_2;
  if (*(char *)((int)piVar4 + 0x11) != '\0') {
    *param_2 = piVar4[2];
    return;
  }
  iVar2 = *piVar4;
  if (*(char *)(iVar2 + 0x11) == '\0') {
    cVar1 = *(char *)(*(int *)(iVar2 + 8) + 0x11);
    iVar3 = *(int *)(iVar2 + 8);
    while (cVar1 == '\0') {
      cVar1 = *(char *)(*(int *)(iVar3 + 8) + 0x11);
      iVar2 = iVar3;
      iVar3 = *(int *)(iVar3 + 8);
    }
    *param_2 = iVar2;
    return;
  }
  piVar4 = (int *)piVar4[1];
  if (*(char *)((int)piVar4 + 0x11) == '\0') {
    do {
      if (*param_2 != *piVar4) break;
      *param_2 = (int)piVar4;
      piVar4 = (int *)piVar4[1];
    } while (*(char *)((int)piVar4 + 0x11) == '\0');
    if (*(char *)((int)piVar4 + 0x11) == '\0') {
      *param_2 = (int)piVar4;
    }
  }
  return;
}
