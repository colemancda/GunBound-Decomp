/* TurnEventSet_RotateLeft - 0x004e8cb0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-11-04), CERTAIN. Left rotation for the set of ushort turn
 * events at g_replayContext+0x45230 (TurnEventSet_Find.c and
 * TurnEventSet_Erase.c map that container). Node fields are left +0,
 * parent +4, right +8, colour +0xe, nil flag +0xf, as read around every
 * call by its two callers, which are the container's red-black fix-ups:
 * TurnEventSet_InsertRebalance calls it when the new node is its parent's
 * right child (rotate the parent left, then recolour) and
 * TurnEventSet_Erase calls it in both arms of its erase fix-up. The body
 * hoists the right child (+8), moves that child's left into the node's
 * right slot, re-parents it and splices it in at the old parent (root slot
 * at head+4 when the old parent is the head). TurnEventSet_Erase's header
 * records that the two rotations are shared only with this set's insert
 * path. Mirror of TurnEventSet_RotateRight (0x4e8d50).
 */
#include "ghidra_types.h"


void __thiscall TurnEventSet_RotateLeft(int param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  
  piVar1 = *(int **)(param_1 + 8);
  *(int *)(param_1 + 8) = *piVar1;
  if (*(char *)(*piVar1 + 0xf) == '\0') {
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

