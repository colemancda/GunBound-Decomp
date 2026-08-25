/* SortHeapIntRange - 0x004dfff0 in the original binary.
 *
 * std::sort_heap over 4-byte elements (_Sort_heap): repeatedly swap the root
 * to the end and re-sift the shrinking heap through AdjustHeapIntRange.
 *
 * EAX and EDI RECOVERED (2026-08-25) from the single site in SortIntRange, whose frame
 * is fixed by its own prologue: `mov ebx,[esp+0x14]` = E+8 = param_2 and
 * `mov edi,[esp+0x1c]` = E+4 = param_1, both loaded once at the entry and
 * never rewritten.  So `mov eax,ebx` at 0x4dfe59 is param_2,
 * and EDI still holds param_1 (the `push edi` two instructions earlier is an
 * argument to the previous call, not a write).
 * This is the introsort tail: the caller falls into it once the range is
 * large but the depth budget has run out.
 */
#include "ghidra_types.h"


void SortHeapIntRange(int regEax,undefined4 *regEdi)

{
  int iVar1;
  
  for (iVar1 = regEax - (int)regEdi; 1 < iVar1 >> 2; iVar1 = iVar1 + -4) {
    *(undefined4 *)((int)regEdi + iVar1 + -4) = *regEdi;
    AdjustHeapIntRange((int)regEdi,(iVar1 + -4) >> 2,0,*(int *)((int)regEdi + iVar1 + -4));
  }
  return;
}

