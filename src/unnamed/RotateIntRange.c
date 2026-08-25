/* RotateIntRange - 0x004e0210 in the original binary.
 *
 * std::rotate over 4-byte elements (_Rotate), by the juggling algorithm:
 * the Euclidean loop at the top computes gcd(range, offset), and the outer
 * loop then walks that many independent cycles, moving one element per step.
 * InsertionSortIntRange calls it to slide an element into place.
 *
 * EAX and EBX RECOVERED (2026-08-25) from the single site 0x4e0074, and the
 * pairing is exact: the two guards the source writes as
 * `(piVar2 != piVar5) && (piVar5 != piVar4)` are `cmp edx,esi; je` followed by
 * `cmp esi,ebx; je` immediately above the call, so EDX is piVar2 (the pushed
 * argument), EAX is piVar5 and EBX is piVar4.
 */
#include "ghidra_types.h"


void RotateIntRange(undefined4 *param_1,int regEax,undefined4 *regEbx)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  int iVar10;
  
  puVar4 = param_1;
  iVar8 = (int)regEbx - (int)param_1 >> 2;
  iVar10 = regEax - (int)param_1 >> 2;
  iVar6 = iVar10;
  iVar7 = iVar8;
  while (iVar3 = iVar6, iVar3 != 0) {
    iVar6 = iVar7 % iVar3;
    iVar7 = iVar3;
  }
  if ((iVar7 < iVar8) && (0 < iVar7)) {
    puVar9 = param_1 + iVar7;
    param_1 = (undefined4 *)iVar7;
    do {
      uVar1 = *puVar9;
      puVar5 = puVar9 + iVar10;
      puVar2 = puVar9;
      if (puVar9 + iVar10 == regEbx) {
        puVar5 = puVar4;
      }
      while (puVar5 != puVar9) {
        *puVar2 = *puVar5;
        iVar7 = (int)regEbx - (int)puVar5 >> 2;
        puVar2 = puVar5;
        if (iVar10 < iVar7) {
          puVar5 = puVar5 + iVar10;
        }
        else {
          puVar5 = puVar4 + (iVar10 - iVar7);
        }
      }
      *puVar2 = uVar1;
      puVar9 = puVar9 + -1;
      param_1 = (undefined4 *)((int)param_1 + -1);
    } while (param_1 != (undefined4 *)0x0);
  }
  return;
}

