/* TreeRotateRight - 0x0040bd20 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * VC7 STL _Tree::_Rrotate(_Nodeptr _Wherenode): the mirror of
 * TreeRotateLeft - take param_1's left child, promote it into param_1's
 * place, then make param_1 the promoted node's new right child. Same
 * node shape and param_2 (tree container, `_Myhead` access) role as
 * TreeRotateLeft - see that file's header for the shared evidence.
 *
 * SIGNATURE COMPLETED, CALL SITES FIXED (2026-10-26). Same dropped/short-
 * argument bug and fix as TreeRotateLeft: functions.h's K&R-empty `()`
 * prototype let TreeErase.c's and TreeInsertRebalance.c's one-argument
 * calls compile silently, passing the container into this function's
 * NODE slot. Each of the 3 TreeErase.c sites and 2 TreeInsertRebalance.c
 * sites was re-disassembled individually (see TreeRotateLeft's header for
 * why that was necessary rather than assumed uniform); see each call
 * site's own comment for its specific pivot.
 */
#include "ghidra_types.h"


void __thiscall TreeRotateRight(int *param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = *param_1;
  *param_1 = *(int *)(iVar1 + 8);
  if (*(char *)(*(int *)(iVar1 + 8) + 0x11) == '\0') {
    *(int **)(*(int *)(iVar1 + 8) + 4) = param_1;
  }
  *(int *)(iVar1 + 4) = param_1[1];
  if (param_1 == *(int **)(*(int *)(param_2 + 4) + 4)) {
    *(int *)(*(int *)(param_2 + 4) + 4) = iVar1;
    *(int **)(iVar1 + 8) = param_1;
    param_1[1] = iVar1;
    return;
  }
  piVar2 = (int *)param_1[1];
  if (param_1 == (int *)piVar2[2]) {
    piVar2[2] = iVar1;
    *(int **)(iVar1 + 8) = param_1;
    param_1[1] = iVar1;
    return;
  }
  *piVar2 = iVar1;
  *(int **)(iVar1 + 8) = param_1;
  param_1[1] = iVar1;
  return;
}

