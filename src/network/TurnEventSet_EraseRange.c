/* TurnEventSet_EraseRange - 0x004e8db0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004e8db0 mean this function.)
 *
 * NAMED (2026-11-05), CERTAIN. Evidence from outside the body:
 * _Tree::erase(first, last) for the turn-event set. Sole caller
 * ReplayContext_Destructor passes (begin = *header, end = header, set =
 * g_replayContext + 0x45230) i.e. clear(). Whole range ->
 * TurnEventSet_EraseSubtree and reset the header links and size; otherwise
 * it advances (TurnEventSet_IteratorIncrement) and calls
 * TurnEventSet_Erase per node. The set is the one TurnEventSet_Erase's
 * header identifies.
 */
#include "ghidra_types.h"


undefined4 * TurnEventSet_EraseRange(undefined4 *param_1,int *param_2,int *param_3,int regEsi)

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
    TurnEventSet_EraseSubtree(piVar1[1]);
    *(int *)(*(int *)(regEsi + 4) + 4) = *(int *)(regEsi + 4);
    *(undefined4 *)(regEsi + 8) = 0;
    *(undefined4 *)*(undefined4 *)(regEsi + 4) = *(undefined4 *)(regEsi + 4);
    *(int *)(*(int *)(regEsi + 4) + 8) = *(int *)(regEsi + 4);
    *puVar3 = **(undefined4 **)(regEsi + 4);
    return puVar3;
  }
  while (piVar2 != piVar4) {
    param_2 = piVar2;
    FUN_004e8f10();
    TurnEventSet_Erase(regEsi,&param_1,piVar2);
    piVar2 = param_2;
  }
  *puVar3 = piVar2;
  return puVar3;
}

