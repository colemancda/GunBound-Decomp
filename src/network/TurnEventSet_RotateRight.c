/* TurnEventSet_RotateRight - 0x004e8d50 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-11-04), CERTAIN. Right rotation, mirror of
 * TurnEventSet_RotateLeft (0x4e8cb0), for the turn-event set at
 * g_replayContext+0x45230 (left +0, parent +4, right +8, colour +0xe, nil
 * flag +0xf). It hoists the node's left child (+0), moves that child's
 * right into the node's left slot, re-parents it and splices it in at the
 * old parent. TurnEventSet_InsertRebalance calls it for the grandparent
 * rotation in its left-parent arm and the parent rotation in the mirror
 * arm; TurnEventSet_Erase calls it in both arms of its erase fix-up.
 * Always paired with the left rotation in those fix-ups, as the CLRS
 * insert and delete fix-ups pair them.
 */
#include "ghidra_types.h"


void __thiscall TurnEventSet_RotateRight(int *param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = *param_1;
  *param_1 = *(int *)(iVar1 + 8);
  if (*(char *)(*(int *)(iVar1 + 8) + 0xf) == '\0') {
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

