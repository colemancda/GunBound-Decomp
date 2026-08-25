/* InsertionSortIntRange - 0x004e0030 in the original binary.
 *
 * The small-range case of SortIntRange (_Insertion_sort): for each element,
 * walk back to its insertion point and rotate it into place through
 * RotateIntRange.
 */
#include "ghidra_types.h"


void InsertionSortIntRange(int *param_1)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  int *unaff_EDI;
  
  if ((unaff_EDI != param_1) && (piVar5 = unaff_EDI + 1, piVar5 != param_1)) {
    piVar4 = unaff_EDI + 2;
    do {
      iVar1 = *piVar5;
      piVar2 = unaff_EDI;
      if (iVar1 < *unaff_EDI) {
joined_r0x004e006b:
        if ((piVar2 != piVar5) && (piVar5 != piVar4)) {
          RotateIntRange((undefined4 *)piVar2,(int)piVar5,(undefined4 *)piVar4);
        }
      }
      else {
        piVar3 = piVar4 + -2;
        if (iVar1 < piVar4[-2]) {
          do {
            piVar2 = piVar3;
            piVar3 = piVar2 + -1;
          } while (iVar1 < *piVar3);
          goto joined_r0x004e006b;
        }
      }
      piVar5 = piVar5 + 1;
      piVar4 = piVar4 + 1;
    } while (piVar5 != param_1);
  }
  return;
}

