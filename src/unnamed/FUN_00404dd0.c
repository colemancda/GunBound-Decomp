/* FUN_00404dd0 - 0x00404dd0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __thiscall FUN_00404dd0(int *param_1,uchar *param_2)

{
  undefined4 in_EAX;
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  iVar1 = FUN_00405360(param_2,in_EAX);
  puVar4 = (undefined4 *)0x0;
  puVar3 = (undefined4 *)*param_1;
  if ((undefined4 *)*param_1 != (undefined4 *)param_1[5]) {
    do {
      puVar4 = puVar3;
      iVar2 = __mbsicmp(param_2,(uchar *)*puVar4);
      if (iVar2 < 1) {
        puVar3 = (undefined4 *)puVar4[0x42];
      }
      else {
        puVar3 = (undefined4 *)puVar4[0x43];
      }
    } while (puVar3 != (undefined4 *)param_1[5]);
  }
  *(undefined4 **)(iVar1 + 0x110) = puVar4;
  if (puVar4 != (undefined4 *)0x0) {
    iVar2 = __mbsicmp(param_2,(uchar *)*puVar4);
    if (0 < iVar2) {
      puVar4[0x43] = iVar1;
      /* Ghidra emitted a bare `return;` in a value-returning function;
       * MSVC falls through with whatever's in EAX, gcc 14 rejects it
       * (-Wreturn-mismatch). This path's result is unused by callers -
       * return 0 to satisfy both toolchains without inventing a value. */
      return 0;
    }
    puVar4[0x42] = iVar1;
    /* Ghidra emitted a bare `return;` in a value-returning function;
     * MSVC falls through with whatever's in EAX, gcc 14 rejects it
     * (-Wreturn-mismatch). This path's result is unused by callers -
     * return 0 to satisfy both toolchains without inventing a value. */
    return 0;
  }
  *param_1 = iVar1;
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

