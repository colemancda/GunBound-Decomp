/* FUN_00404b00 - 0x00404b00 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_00404b00(uchar *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int *unaff_EBX;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  puVar2 = (undefined4 *)*unaff_EBX;
  puVar3 = (undefined4 *)0x0;
  if (puVar2 != (undefined4 *)unaff_EBX[5]) {
    do {
      puVar4 = puVar3;
      if (puVar3 != (undefined4 *)0x0) goto LAB_00404b4b;
      iVar1 = __mbsicmp(param_1,(uchar *)*puVar2);
      puVar4 = puVar2;
      if (iVar1 != 0) {
        if (iVar1 < 0) {
          puVar2 = (undefined4 *)puVar2[0x42];
          puVar4 = puVar3;
        }
        else {
          puVar2 = (undefined4 *)puVar2[0x43];
          puVar4 = puVar3;
        }
      }
      puVar3 = puVar4;
    } while (puVar2 != (undefined4 *)unaff_EBX[5]);
    if (puVar4 != (undefined4 *)0x0) {
LAB_00404b4b:
      puVar2 = (undefined4 *)FUN_00405040(unaff_EBX);
      while ((puVar3 = puVar2, puVar3 != (undefined4 *)0x0 &&
             (iVar1 = __mbsicmp(param_1,(uchar *)*puVar3), iVar1 == 0))) {
        puVar2 = (undefined4 *)FUN_00405040(unaff_EBX);
        puVar4 = puVar3;
      }
      return puVar4;
    }
  }
  return (undefined4 *)0x0;
}

