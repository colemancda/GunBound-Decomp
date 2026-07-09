/* FUN_00509fd0 - 0x00509fd0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00509fd0(undefined4 *param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  iVar2 = param_1[2];
  while (iVar2 != 0) {
    puVar3 = (undefined4 *)*param_1;
    *param_1 = *puVar3;
    *puVar3 = param_1[4];
    param_1[4] = puVar3;
    piVar1 = param_1 + 2;
    *piVar1 = *piVar1 + -1;
    if (*piVar1 == 0) {
      /* Ghidra emitted this __fastcall self-call with no args (it lost
       * track of ECX); MSVC hard-errors on the byte-count mismatch
       * (C2708), so pass the current parameter through. */
      FUN_00509fd0(param_1);
    }
    iVar2 = param_1[2];
  }
  *param_1 = 0;
  param_1[1] = 0;
  param_1[4] = 0;
  puVar3 = (undefined4 *)param_1[3];
  while (puVar3 != (undefined4 *)0x0) {
    puVar4 = (undefined4 *)*puVar3;
    _free(puVar3);
    puVar3 = puVar4;
  }
  param_1[3] = 0;
  return;
}

