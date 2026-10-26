/* TreeRotateLeft - 0x0040bc80 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * VC7 STL _Tree::_Lrotate(_Nodeptr _Wherenode): take param_1's right
 * child, promote it into param_1's place (re-parenting param_1's old
 * right-child's left subtree onto param_1, and fixing up whichever of
 * param_2's root link / the old parent's left-or-right child slot used to
 * point at param_1), then make param_1 the promoted node's new left
 * child. Same 0x14-byte node shape (_Left/_Parent/_Right, _Isnil at
 * +0x11) TreeInsertRebalance/TreeIteratorDecrement already attribute to
 * &g_valueGuardMap; param_2 is the tree container itself, dereferenced as
 * `*(int*)(param_2+4)` for its header-node pointer, the same `_Myhead`
 * access TreeErase's own param_1 makes.
 *
 * __thiscall here puts param_1 (the node being rotated, NOT a C++ `this`)
 * in ECX and param_2 (the container) on the stack - confirmed directly
 * off the entry disassembly (`mov eax,[ecx+8]` reads the node's Right
 * child before anything else) and off every call site below.
 *
 * SIGNATURE COMPLETED, CALL SITES FIXED (2026-10-26). functions.h
 * previously kept this at a K&R-empty `()` prototype, which let
 * TreeErase.c's `FUN_0040bc80(param_1)` compile silently: it was passing
 * TreeErase's own container argument into this function's NODE slot and
 * leaving the real container argument off entirely, the same
 * dropped/short-argument bug class LogicError_ctor's rename exposed.
 * Giving this a real 2-arg prototype forced reconstructing the missing
 * node argument at every call site (TreeErase.c's 3 sites, plus
 * TreeInsertRebalance.c's 2 - the latter has no live caller of its own
 * per its own header, but still has to compile under the real
 * prototype). Each was re-disassembled individually rather than assumed
 * uniform, because the rotation pivot is NOT the same local at every
 * site: TreeErase's original 0x40b7b3/0x40b7fd calls both load ECX from
 * `esi` (its `piVar3`), but 0x40b85d loads ECX from the then-current
 * `piVar5`; TreeInsertRebalance's 0x40bbf5 loads ECX from `piVar2`, but
 * 0x40bc41 loads it from `*(int*)(piVar6[1]+4)` (piVar6's grandparent) -
 * see each call site's own comment.
 */
#include "ghidra_types.h"


void __thiscall TreeRotateLeft(int param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  
  piVar1 = *(int **)(param_1 + 8);
  *(int *)(param_1 + 8) = *piVar1;
  if (*(char *)(*piVar1 + 0x11) == '\0') {
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

