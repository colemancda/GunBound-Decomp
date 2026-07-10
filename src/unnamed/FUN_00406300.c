/* FUN_00406300 - 0x00406300 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __fastcall FUN_00406300(undefined4 param_1,uint param_2,int param_3)

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
      /* Ghidra emitted a bare `return;` in a value-returning function;
       * MSVC falls through with whatever's in EAX, gcc 14 rejects it
       * (-Wreturn-mismatch). This path's result is unused by callers -
       * return 0 to satisfy both toolchains without inventing a value. */
      return 0;
    }
    if (uVar2 == param_2) break;
    iVar1 = *(int *)(iVar1 + 0x1c);
    uVar2 = *(uint *)(iVar1 + 4);
  }
  piVar3 = *(int **)(iVar1 + 0x10);
  uVar2 = piVar3[2];
  if (unaff_ESI < uVar2) {
    /* Ghidra emitted a bare `return;` in a value-returning function;
     * MSVC falls through with whatever's in EAX, gcc 14 rejects it
     * (-Wreturn-mismatch). This path's result is unused by callers -
     * return 0 to satisfy both toolchains without inventing a value. */
    return 0;
  }
  while (uVar2 != unaff_ESI) {
    piVar3 = (int *)piVar3[4];
    uVar2 = piVar3[2];
    if (unaff_ESI < uVar2) {
      /* Ghidra emitted a bare `return;` in a value-returning function;
       * MSVC falls through with whatever's in EAX, gcc 14 rejects it
       * (-Wreturn-mismatch). This path's result is unused by callers -
       * return 0 to satisfy both toolchains without inventing a value. */
      return 0;
    }
  }
  if (param_3 != '\0') {
    if ((piVar3[9] != 3) && (piVar3[9] != -1)) {
      /* Ghidra emitted a bare `return;` in a value-returning function;
       * MSVC falls through with whatever's in EAX, gcc 14 rejects it
       * (-Wreturn-mismatch). This path's result is unused by callers -
       * return 0 to satisfy both toolchains without inventing a value. */
      return 0;
    }
    if ((char)piVar3[0x13] == '\x01') {
                    /* WARNING: Could not recover jumptable at 0x00406367. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*piVar3 + 4))();
      /* Ghidra emitted a bare `return;` in a value-returning function;
       * MSVC falls through with whatever's in EAX, gcc 14 rejects it
       * (-Wreturn-mismatch). This path's result is unused by callers -
       * return 0 to satisfy both toolchains without inventing a value. */
      return 0;
    }
                    /* WARNING: Could not recover jumptable at 0x00406374. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*piVar3 + 4))();
    /* Ghidra emitted a bare `return;` in a value-returning function;
     * MSVC falls through with whatever's in EAX, gcc 14 rejects it
     * (-Wreturn-mismatch). This path's result is unused by callers -
     * return 0 to satisfy both toolchains without inventing a value. */
    return 0;
  }
                    /* WARNING: Could not recover jumptable at 0x00406347. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*piVar3 + 4))();
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

