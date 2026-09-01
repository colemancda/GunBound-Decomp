/* TreeEraseRange - 0x0040be20 in the original binary.
 *
 * VC7 STL _Tree::erase(iterator first, iterator last) of the CValueGuard
 * guard-cell map - the same instantiation TreeFind (0x40b8c0) and
 * TreeLowerBound (0x40b540) walk, prefixed like them.  The library shape
 * is verbatim: when first == begin (head->_Left, with the head at map+4)
 * and last == end (the head itself), take the erase-all fast path -
 * subtree-delete the root (head->_Parent) via FUN_0040c210, self-link
 * the head, zero _Mysize at map+8 - else loop erase(first++) through
 * FUN_0040b600 (the single-iterator erase overload) with FUN_0040c1b0
 * as the iterator increment, returning the out-iterator through
 * *param_1.
 *
 * The map identity is external, twice over: the caller at 0x40a204,
 * FUN_0040a1c0, is reached only from the atexit destructor thunk at
 * 0x5431b5 that pushes 0x79376c - the static object whose +4 field IS
 * &g_valueGuardMap (0x793770) - and the erase-one callee FUN_0040b600's
 * only other caller is EncodeOutgoingPacketField at 0x40a3d7, pushing
 * that same 0x793770.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


undefined4 * TreeEraseRange(undefined4 *param_1,int *param_2,int *param_3,int regEsi)

{
  int *piVar1;
  int *piVar2;
  undefined4 *puVar3;
  int *piVar4;
  
  piVar4 = param_3;
  puVar3 = param_1;
  piVar1 = *(int **)(regEsi + 4);
  piVar2 = param_2;
  if ((param_2 == (int *)*piVar1) && (param_3 == piVar1)) {
    FUN_0040c210(piVar1[1]);
    *(int *)(*(int *)(regEsi + 4) + 4) = *(int *)(regEsi + 4);
    *(undefined4 *)(regEsi + 8) = 0;
    *(undefined4 *)*(undefined4 *)(regEsi + 4) = *(undefined4 *)(regEsi + 4);
    *(int *)(*(int *)(regEsi + 4) + 8) = *(int *)(regEsi + 4);
    *puVar3 = **(undefined4 **)(regEsi + 4);
    return puVar3;
  }
  while (piVar2 != piVar4) {
    param_2 = piVar2;
    FUN_0040c1b0();
    FUN_0040b600(regEsi,&param_1,piVar2);
    piVar2 = param_2;
  }
  *puVar3 = piVar2;
  return puVar3;
}

