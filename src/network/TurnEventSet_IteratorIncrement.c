/* TurnEventSet_IteratorIncrement - 0x004e8f10 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004e8f10 mean this function.)
 *
 * NAMED (2026-11-05), CERTAIN. Evidence from outside the body: _Tree
 * iterator operator++ over the turn-event set node layout (left +0, parent
 * +4, right +8, isnil byte +0xf): right subtree then leftmost, else climb
 * while we are the right child. TurnEventSet_Erase calls it first to take
 * the successor it returns, and TurnEventSet_EraseRange calls it per node.
 * Not TreeIteratorIncrement (0x40c1b0), which serves a different node
 * layout.
 */
#include "ghidra_types.h"


void __fastcall TurnEventSet_IteratorIncrement(undefined4 param_1,int *param_2)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  
  iVar2 = *param_2;
  if (*(char *)(iVar2 + 0xf) == '\0') {
    piVar3 = *(int **)(iVar2 + 8);
    if (*(char *)((int)piVar3 + 0xf) == '\0') {
      cVar1 = *(char *)(*piVar3 + 0xf);
      piVar4 = (int *)*piVar3;
      while (cVar1 == '\0') {
        cVar1 = *(char *)(*piVar4 + 0xf);
        piVar3 = piVar4;
        piVar4 = (int *)*piVar4;
      }
      *param_2 = (int)piVar3;
      return;
    }
    iVar2 = *(int *)(iVar2 + 4);
    cVar1 = *(char *)(iVar2 + 0xf);
    while ((cVar1 == '\0' && (*param_2 == *(int *)(iVar2 + 8)))) {
      *param_2 = iVar2;
      iVar2 = *(int *)(iVar2 + 4);
      cVar1 = *(char *)(iVar2 + 0xf);
    }
    *param_2 = iVar2;
  }
  return;
}

