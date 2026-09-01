/* FUN_00500fa0 - 0x00500fa0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00500fa0(undefined4 param_1,undefined4 param_2,int regEax,undefined4 *regEdi)

{
  undefined4 *puVar1;
  
  FUN_00501510(regEax);
  puVar1 = *(undefined4 **)(regEax + 0x10);
  if (puVar1 != (undefined4 *)0x0) {
    puVar1[8] = 0;
    puVar1[9] = 0;
    puVar1[10] = 0;
    puVar1[0xb] = 0;
    puVar1[0xc] = 0;
    puVar1[0xd] = 10;
    puVar1[2] = *regEdi;
    puVar1[3] = regEdi[1];
    puVar1[4] = regEdi[2];
    puVar1[5] = regEdi[3];
    puVar1[6] = regEdi[4];
    puVar1[7] = regEdi[5];
  }
  *(undefined4 *)(regEax + 0x10) = *puVar1;
  puVar1[1] = param_1;
  *puVar1 = param_2;
  *(int *)(regEax + 8) = *(int *)(regEax + 8) + 1;
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

