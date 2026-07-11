/* FUN_00500840 - 0x00500840 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_00500840(undefined4 param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  int *piVar2;
  undefined4 uVar3;
  int iVar4;
  int unaff_EBX;
  int *unaff_ESI;
  
  if (unaff_ESI[0xb] == 0) {
    piVar2 = _malloc(unaff_ESI[9] * 0x1768 + 4);
    if (piVar2 == (int *)0x0) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x8007000e);
    }
    *piVar2 = unaff_ESI[10];
    unaff_ESI[10] = (int)piVar2;
    iVar4 = unaff_ESI[9];
    piVar2 = piVar2 + iVar4 * 0x5da + -0x5d9;
    if (-1 < iVar4 + -1) {
      do {
        piVar2[0x5d8] = unaff_ESI[0xb];
        unaff_ESI[0xb] = (int)piVar2;
        piVar2 = piVar2 + -0x5da;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
  }
  puVar1 = (undefined4 *)unaff_ESI[0xb];
  unaff_ESI[0xb] = puVar1[0x5d8];
  puVar1[0x5d9] = param_2;
  *puVar1 = param_1;
  unaff_ESI[1] = unaff_ESI[1] + 1;
  puVar1[0x5d8] = *(undefined4 *)(*unaff_ESI + unaff_EBX * 4);
  *(undefined4 **)(*unaff_ESI + unaff_EBX * 4) = puVar1;
  if (((uint)unaff_ESI[6] < (uint)unaff_ESI[1]) && (unaff_ESI[8] == 0)) {
    uVar3 = FUN_00500e30();
    FUN_00501070(unaff_ESI,uVar3);
  }
  return puVar1;
}

