/* FUN_00504480 - 0x00504480 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_00504480(int param_1,undefined4 param_2)

{
  byte bVar1;
  undefined4 *puVar2;
  undefined4 *in_EAX;
  int *piVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  int *unaff_EBX;
  undefined4 *puVar7;
  
  if (unaff_EBX[0xb] == 0) {
    piVar3 = _malloc(unaff_EBX[9] * 0x28 + 4);
    if (piVar3 == (int *)0x0) {
                    /* WARNING: Subroutine does not return */
      FUN_004010c0(0x8007000e);
    }
    *piVar3 = unaff_EBX[10];
    unaff_EBX[10] = (int)piVar3;
    iVar5 = unaff_EBX[9];
    piVar3 = piVar3 + iVar5 * 10 + -9;
    if (-1 < iVar5 + -1) {
      do {
        piVar3[8] = unaff_EBX[0xb];
        unaff_EBX[0xb] = (int)piVar3;
        piVar3 = piVar3 + -10;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
  }
  puVar2 = (undefined4 *)unaff_EBX[0xb];
  unaff_EBX[0xb] = puVar2[8];
  bVar1 = *(byte *)((int)in_EAX + 0x11);
  *(byte *)((int)puVar2 + 0x11) = bVar1;
  puVar7 = puVar2;
  for (uVar6 = (uint)(bVar1 >> 2); uVar6 != 0; uVar6 = uVar6 - 1) {
    *puVar7 = *in_EAX;
    in_EAX = in_EAX + 1;
    puVar7 = puVar7 + 1;
  }
  for (uVar6 = bVar1 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined1 *)puVar7 = *(undefined1 *)in_EAX;
    in_EAX = (undefined4 *)((int)in_EAX + 1);
    puVar7 = (undefined4 *)((int)puVar7 + 1);
  }
  *(undefined1 *)((uint)bVar1 + (int)puVar2) = 0;
  puVar2[9] = param_2;
  unaff_EBX[1] = unaff_EBX[1] + 1;
  puVar2[8] = *(undefined4 *)(*unaff_EBX + param_1 * 4);
  *(undefined4 **)(*unaff_EBX + param_1 * 4) = puVar2;
  if (((uint)unaff_EBX[6] < (uint)unaff_EBX[1]) && (unaff_EBX[8] == 0)) {
    uVar4 = FUN_00500e30();
    FUN_00500300(unaff_EBX,uVar4);
  }
  return puVar2;
}

