/* FUN_00422f70 - 0x00422f70 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00422f70(int param_1)

{
  int iVar1;
  DWORD DVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  int *piVar8;
  
  iVar1 = param_1;
  DVar2 = GetTickCount();
  piVar6 = (int *)(&DAT_005f3258 + param_1);
  param_1 = 0;
  if (0 < *piVar6) {
    piVar6 = (int *)(&DAT_005f2f58 + iVar1);
    do {
      if (((*piVar6 != -1) && (piVar6[0x40] != -1)) && (piVar6[0x80] < (int)(DVar2 / 1000))) {
        uVar3 = 0x3f - param_1;
        piVar8 = piVar6;
        piVar7 = piVar6;
        for (uVar4 = uVar3 & 0x3fffffff; piVar7 = piVar7 + 1, uVar4 != 0; uVar4 = uVar4 - 1) {
          *piVar8 = *piVar7;
          piVar8 = piVar8 + 1;
        }
        for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
          *(char *)piVar8 = (char)*piVar7;
          piVar7 = (int *)((int)piVar7 + 1);
          piVar8 = (int *)((int)piVar8 + 1);
        }
        piVar7 = piVar6 + 0x41;
        piVar8 = piVar6 + 0x40;
        for (uVar4 = uVar3 & 0x3fffffff; uVar4 != 0; uVar4 = uVar4 - 1) {
          *piVar8 = *piVar7;
          piVar7 = piVar7 + 1;
          piVar8 = piVar8 + 1;
        }
        for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
          *(char *)piVar8 = (char)*piVar7;
          piVar7 = (int *)((int)piVar7 + 1);
          piVar8 = (int *)((int)piVar8 + 1);
        }
        piVar7 = piVar6 + 0x81;
        piVar8 = piVar6 + 0x80;
        for (uVar3 = uVar3 & 0x3fffffff; uVar3 != 0; uVar3 = uVar3 - 1) {
          *piVar8 = *piVar7;
          piVar7 = piVar7 + 1;
          piVar8 = piVar8 + 1;
        }
        for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
          *(char *)piVar8 = (char)*piVar7;
          piVar7 = (int *)((int)piVar7 + 1);
          piVar8 = (int *)((int)piVar8 + 1);
        }
        *(int *)(&DAT_005f3258 + iVar1) = *(int *)(&DAT_005f3258 + iVar1) + -1;
      }
      param_1 = param_1 + 1;
      piVar6 = piVar6 + 1;
    } while (param_1 < *(int *)(&DAT_005f3258 + iVar1));
  }
  return;
}

