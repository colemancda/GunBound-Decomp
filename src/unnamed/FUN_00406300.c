/* FUN_00406300 - 0x00406300 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void __fastcall FUN_00406300(undefined4 param_1,uint param_2,char param_3)

{
  int iVar1;
  uint uVar2;
  int in_EAX;
  int *piVar3;
  uint unaff_ESI;
  
  iVar1 = *(int *)(*(int *)(in_EAX + 4) + 0x1c);
  uVar2 = *(uint *)(iVar1 + 4);
  while( true ) {
    if (param_2 < uVar2) {
      return;
    }
    if (uVar2 == param_2) break;
    iVar1 = *(int *)(iVar1 + 0x1c);
    uVar2 = *(uint *)(iVar1 + 4);
  }
  piVar3 = *(int **)(iVar1 + 0x10);
  uVar2 = piVar3[2];
  if (unaff_ESI < uVar2) {
    return;
  }
  while (uVar2 != unaff_ESI) {
    piVar3 = (int *)piVar3[4];
    uVar2 = piVar3[2];
    if (unaff_ESI < uVar2) {
      return;
    }
  }
  if (param_3 != '\0') {
    if ((piVar3[9] != 3) && (piVar3[9] != -1)) {
      return;
    }
    if ((char)piVar3[0x13] == '\x01') {
                    /* WARNING: Could not recover jumptable at 0x00406367. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*piVar3 + 4))();
      return;
    }
                    /* WARNING: Could not recover jumptable at 0x00406374. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*piVar3 + 4))();
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00406347. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*piVar3 + 4))();
  return;
}

