/* FUN_0043e0f0 - 0x0043e0f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * REGISTERS RECOVERED (2026-08-25).  Inserts a (key, value) node into the
 * localized-string map param_1 (ECX): regEbx is the signed id key the tree
 * walk compares (`cmp ebx,[node]` / jl), regEax the string value; both are
 * FUN_0043de70's pass-through ECX/EAX.  FUN_0043e150 allocates the node from
 * the two.
 */
#include "ghidra_types.h"


void __fastcall FUN_0043e0f0(int *param_1,int regEbx,undefined4 regEax)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  iVar3 = FUN_0043e150(regEbx,regEax,(undefined4 *)param_1);
  piVar2 = (int *)*param_1;
  piVar1 = (int *)0x0;
  while (piVar2 != (int *)param_1[5]) {
    piVar1 = piVar2;
    if ((regEbx < *piVar2) || (regEbx == *piVar2)) {
      piVar2 = (int *)piVar2[3];
    }
    else {
      piVar2 = (int *)piVar2[4];
    }
  }
  *(int **)(iVar3 + 0x14) = piVar1;
  if (piVar1 != (int *)0x0) {
    if ((*piVar1 <= regEbx) && (regEbx != *piVar1)) {
      piVar1[4] = iVar3;
      return;
    }
    piVar1[3] = iVar3;
    return;
  }
  *param_1 = iVar3;
  return;
}

