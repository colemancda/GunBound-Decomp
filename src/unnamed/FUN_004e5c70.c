/* FUN_004e5c70 - 0x004e5c70 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint FUN_004e5c70(undefined4 *param_1)

{
  uint uVar1;
  char cVar2;
  int iVar3;
  int *unaff_EBX;
  undefined4 *puVar4;
  
  uVar1 = unaff_EBX[1];
  if ((uint)unaff_EBX[2] <= uVar1) {
    cVar2 = FUN_004e5d10();
    if (cVar2 == '\0') {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x8007000e);
    }
  }
  puVar4 = (undefined4 *)(uVar1 * 0x4004 + *unaff_EBX);
  if (puVar4 != (undefined4 *)0x0) {
    for (iVar3 = 0x1001; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *param_1;
      param_1 = param_1 + 1;
      puVar4 = puVar4 + 1;
    }
  }
  unaff_EBX[1] = unaff_EBX[1] + 1;
  return uVar1;
}

