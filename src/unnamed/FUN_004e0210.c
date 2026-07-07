/* FUN_004e0210 - 0x004e0210 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e0210(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int iVar6;
  int in_EAX;
  int iVar7;
  int iVar8;
  undefined4 *unaff_EBX;
  undefined4 *puVar9;
  int iVar10;
  
  puVar4 = param_1;
  iVar8 = (int)unaff_EBX - (int)param_1 >> 2;
  iVar10 = in_EAX - (int)param_1 >> 2;
  iVar6 = iVar10;
  iVar7 = iVar8;
  while (iVar3 = iVar6, iVar3 != 0) {
    iVar6 = iVar7 % iVar3;
    iVar7 = iVar3;
  }
  if ((iVar7 < iVar8) && (0 < iVar7)) {
    puVar9 = param_1 + iVar7;
    param_1 = (undefined4 *)iVar7;
    do {
      uVar1 = *puVar9;
      puVar5 = puVar9 + iVar10;
      puVar2 = puVar9;
      if (puVar9 + iVar10 == unaff_EBX) {
        puVar5 = puVar4;
      }
      while (puVar5 != puVar9) {
        *puVar2 = *puVar5;
        iVar7 = (int)unaff_EBX - (int)puVar5 >> 2;
        puVar2 = puVar5;
        if (iVar10 < iVar7) {
          puVar5 = puVar5 + iVar10;
        }
        else {
          puVar5 = puVar4 + (iVar10 - iVar7);
        }
      }
      *puVar2 = uVar1;
      puVar9 = puVar9 + -1;
      param_1 = (undefined4 *)((int)param_1 + -1);
    } while (param_1 != (undefined4 *)0x0);
  }
  return;
}

