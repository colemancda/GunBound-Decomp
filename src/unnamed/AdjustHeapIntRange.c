/* AdjustHeapIntRange - 0x004e01b0 in the original binary.
 *
 * The heap sift used by MakeHeapIntRange and SortHeapIntRange
 * (_Adjust_heap): slide the hole down to a leaf taking the larger child,
 * then push the held value back up -- the _Push_heap tail.
 */
#include "ghidra_types.h"


void __fastcall AdjustHeapIntRange(int param_1,int param_2,int param_3,int regEbx)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = param_3;
  while( true ) {
    iVar2 = iVar1 * 2 + 2;
    if (param_2 <= iVar2) break;
    if (*(int *)(param_1 + iVar2 * 4) < *(int *)(param_1 + -4 + iVar2 * 4)) {
      iVar2 = iVar1 * 2 + 1;
    }
    *(undefined4 *)(param_1 + iVar1 * 4) = *(undefined4 *)(param_1 + iVar2 * 4);
    iVar1 = iVar2;
  }
  if (iVar2 == param_2) {
    *(undefined4 *)(param_1 + iVar1 * 4) = *(undefined4 *)(param_1 + -4 + param_2 * 4);
    iVar1 = param_2 + -1;
  }
  while (param_3 < iVar1) {
    iVar3 = (iVar1 + -1) / 2;
    iVar2 = *(int *)(param_1 + iVar3 * 4);
    if (regEbx <= iVar2) break;
    *(int *)(param_1 + iVar1 * 4) = iVar2;
    iVar1 = iVar3;
  }
  *(int *)(param_1 + iVar1 * 4) = regEbx;
  return;
}

