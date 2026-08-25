/* MakeHeapIntRange - 0x004dffb0 in the original binary.
 *
 * std::make_heap over 4-byte elements (_Make_heap): sift down from the last
 * internal node to the root through AdjustHeapIntRange.  SortIntRange calls
 * it with SortHeapIntRange when the introsort depth budget runs out.
 *
 * EAX RECOVERED (2026-08-25) from the single site in SortIntRange, whose frame
 * is fixed by its own prologue: `mov ebx,[esp+0x14]` = E+8 = param_2 and
 * `mov edi,[esp+0x1c]` = E+4 = param_1, both loaded once at the entry and
 * never rewritten.  So `mov eax,ebx` at 0x4dfe4f is param_2,
 * and the pushed argument is param_1.
 * This is the introsort tail: the caller falls into it once the range is
 * large but the depth budget has run out.
 */
#include "ghidra_types.h"


void MakeHeapIntRange(int param_1,int regEax)

{
  int iVar1;
  
  iVar1 = regEax - param_1 >> 2;
  if (1 < iVar1) {
    iVar1 = iVar1 - (regEax - param_1 >> 0x1f) >> 1;
    while (0 < iVar1) {
      iVar1 = iVar1 + -1;
      AdjustHeapIntRange(param_1,(regEax - param_1) >> 2,iVar1,*(int *)(param_1 + iVar1 * 4));
    }
  }
  return;
}

