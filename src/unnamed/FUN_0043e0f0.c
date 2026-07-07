/* FUN_0043e0f0 - 0x0043e0f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0043e0f0(int *param_1)

{
  int *piVar1;
  int *piVar2;
  undefined4 in_EAX;
  int iVar3;
  int unaff_EBX;
  
  iVar3 = FUN_0043e150(unaff_EBX,in_EAX);
  piVar2 = (int *)*param_1;
  piVar1 = (int *)0x0;
  while (piVar2 != (int *)param_1[5]) {
    piVar1 = piVar2;
    if ((unaff_EBX < *piVar2) || (unaff_EBX == *piVar2)) {
      piVar2 = (int *)piVar2[3];
    }
    else {
      piVar2 = (int *)piVar2[4];
    }
  }
  *(int **)(iVar3 + 0x14) = piVar1;
  if (piVar1 != (int *)0x0) {
    if ((*piVar1 <= unaff_EBX) && (unaff_EBX != *piVar1)) {
      piVar1[4] = iVar3;
      return;
    }
    piVar1[3] = iVar3;
    return;
  }
  *param_1 = iVar3;
  return;
}

