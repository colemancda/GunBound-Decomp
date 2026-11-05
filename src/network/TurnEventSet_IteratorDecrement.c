/* TurnEventSet_IteratorDecrement - 0x004e8eb0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004e8eb0 mean this function.)
 *
 * NAMED (2026-11-05), HIGH. Evidence from outside the body: The mirror of
 * TurnEventSet_IteratorIncrement (0x4e8f10) with the child links swapped:
 * when the iterator is the head sentinel (_Isnil at +0xf) it moves to
 * _Right (the maximum), otherwise it takes the rightmost node of the left
 * subtree or climbs while it is a left child. The caller
 * TurnEventSet_Insert uses it exactly where the std::set insert does
 * `--where` to compare the new key against its predecessor before choosing
 * between insert and duplicate. The caller currently passes no argument
 * (the EDX iterator pointer is dropped), see the report.
 */
#include "ghidra_types.h"


void __fastcall TurnEventSet_IteratorDecrement(undefined4 param_1,int *param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  piVar4 = (int *)*param_2;
  if (*(char *)((int)piVar4 + 0xf) != '\0') {
    *param_2 = piVar4[2];
    return;
  }
  iVar2 = *piVar4;
  if (*(char *)(iVar2 + 0xf) == '\0') {
    cVar1 = *(char *)(*(int *)(iVar2 + 8) + 0xf);
    iVar3 = *(int *)(iVar2 + 8);
    while (cVar1 == '\0') {
      cVar1 = *(char *)(*(int *)(iVar3 + 8) + 0xf);
      iVar2 = iVar3;
      iVar3 = *(int *)(iVar3 + 8);
    }
    *param_2 = iVar2;
    return;
  }
  piVar4 = (int *)piVar4[1];
  if (*(char *)((int)piVar4 + 0xf) == '\0') {
    do {
      if (*param_2 != *piVar4) break;
      *param_2 = (int)piVar4;
      piVar4 = (int *)piVar4[1];
    } while (*(char *)((int)piVar4 + 0xf) == '\0');
    if (*(char *)((int)piVar4 + 0xf) == '\0') {
      *param_2 = (int)piVar4;
    }
  }
  return;
}

