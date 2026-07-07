/* FUN_004e0090 - 0x004e0090 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_004e0090(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *unaff_ESI;
  int *piVar4;
  
  iVar1 = (int)param_2 - (int)param_1 >> 2;
  if (iVar1 < 0x29) {
    iVar1 = *unaff_ESI;
    if (iVar1 < *param_1) {
      *unaff_ESI = *param_1;
      *param_1 = iVar1;
    }
    iVar1 = *param_2;
    if (iVar1 < *unaff_ESI) {
      *param_2 = *unaff_ESI;
      *unaff_ESI = iVar1;
    }
    iVar1 = *unaff_ESI;
    if (iVar1 < *param_1) {
      *unaff_ESI = *param_1;
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
    iVar1 = *unaff_ESI;
    piVar3 = unaff_ESI + -iVar2;
    if (iVar1 < *piVar3) {
      *unaff_ESI = *piVar3;
      *piVar3 = iVar1;
    }
    iVar1 = unaff_ESI[iVar2];
    if (iVar1 < *unaff_ESI) {
      unaff_ESI[iVar2] = *unaff_ESI;
      *unaff_ESI = iVar1;
    }
    iVar1 = *unaff_ESI;
    if (iVar1 < *piVar3) {
      *unaff_ESI = *piVar3;
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
    iVar1 = *unaff_ESI;
    if (iVar1 < param_1[iVar2]) {
      *unaff_ESI = param_1[iVar2];
      param_1[iVar2] = iVar1;
    }
    iVar1 = *piVar3;
    if (iVar1 < *unaff_ESI) {
      *piVar3 = *unaff_ESI;
      *unaff_ESI = iVar1;
    }
    iVar1 = *unaff_ESI;
    if (iVar1 < param_1[iVar2]) {
      *unaff_ESI = param_1[iVar2];
      param_1[iVar2] = iVar1;
      return;
    }
  }
  return;
}

