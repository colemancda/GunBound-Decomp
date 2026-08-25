/* MedianIntRange - 0x004e0090 in the original binary.
 *
 * Pivot selection for PartitionIntRange (_Median).  Under 41 elements it is
 * the plain three-element median swap network; at 41 or more it takes the
 * median of nine, sampling at eighths of the range.  The 0x29 threshold is
 * the STL's own `if (40 < _Count)`.
 */
#include "ghidra_types.h"


void __thiscall MedianIntRange(int *param_1,int *param_2,int *regEsi)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  
  iVar1 = (int)param_2 - (int)param_1 >> 2;
  if (iVar1 < 0x29) {
    iVar1 = *regEsi;
    if (iVar1 < *param_1) {
      *regEsi = *param_1;
      *param_1 = iVar1;
    }
    iVar1 = *param_2;
    if (iVar1 < *regEsi) {
      *param_2 = *regEsi;
      *regEsi = iVar1;
    }
    iVar1 = *regEsi;
    if (iVar1 < *param_1) {
      *regEsi = *param_1;
      *param_1 = iVar1;
    }
  }
  else {
    iVar1 = iVar1 + 1;
    iVar2 = (int)(iVar1 + (iVar1 >> 0x1f & 7U)) >> 3;
    iVar1 = param_1[iVar2];
    if (iVar1 < *param_1) {
      param_1[iVar2] = *param_1;
      *param_1 = iVar1;
    }
    iVar1 = param_1[iVar2 * 2];
    if (iVar1 < param_1[iVar2]) {
      param_1[iVar2 * 2] = param_1[iVar2];
      param_1[iVar2] = iVar1;
    }
    iVar1 = param_1[iVar2];
    if (iVar1 < *param_1) {
      param_1[iVar2] = *param_1;
      *param_1 = iVar1;
    }
    iVar1 = *regEsi;
    piVar3 = regEsi + -iVar2;
    if (iVar1 < *piVar3) {
      *regEsi = *piVar3;
      *piVar3 = iVar1;
    }
    iVar1 = regEsi[iVar2];
    if (iVar1 < *regEsi) {
      regEsi[iVar2] = *regEsi;
      *regEsi = iVar1;
    }
    iVar1 = *regEsi;
    if (iVar1 < *piVar3) {
      *regEsi = *piVar3;
      *piVar3 = iVar1;
    }
    piVar3 = param_2 + -iVar2;
    iVar1 = *piVar3;
    piVar4 = param_2 + iVar2 * -2;
    if (iVar1 < *piVar4) {
      *piVar3 = *piVar4;
      *piVar4 = iVar1;
    }
    iVar1 = *param_2;
    if (iVar1 < *piVar3) {
      *param_2 = *piVar3;
      *piVar3 = iVar1;
    }
    iVar1 = *piVar3;
    if (iVar1 < *piVar4) {
      *piVar3 = *piVar4;
      *piVar4 = iVar1;
    }
    iVar1 = *regEsi;
    if (iVar1 < param_1[iVar2]) {
      *regEsi = param_1[iVar2];
      param_1[iVar2] = iVar1;
    }
    iVar1 = *piVar3;
    if (iVar1 < *regEsi) {
      *piVar3 = *regEsi;
      *regEsi = iVar1;
    }
    iVar1 = *regEsi;
    if (iVar1 < param_1[iVar2]) {
      *regEsi = param_1[iVar2];
      param_1[iVar2] = iVar1;
      return;
    }
  }
  return;
}

