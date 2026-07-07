/* FUN_004f41d0 - 0x004f41d0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004f41d0(undefined4 *param_1,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int unaff_EBX;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int unaff_retaddr;
  undefined4 local_7c [4];
  int iStack_6c;
  int iStack_58;
  
  if (*(int *)(unaff_EBX + 0x110) != 0) {
    puVar1 = local_7c;
    for (iVar2 = 0x1f; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar1 = 0;
      puVar1 = puVar1 + 1;
    }
    local_7c[0] = 0x7c;
    do {
      iVar2 = (**(code **)(**(int **)(unaff_EBX + 0x110) + 100))
                        (*(int **)(unaff_EBX + 0x110),0,local_7c,0,0);
    } while (iVar2 != 0);
    uVar5 = 0;
    puVar1 = (undefined4 *)
             (((param_2 / *(int *)(unaff_EBX + 8)) * iStack_6c +
              (param_2 % *(int *)(unaff_EBX + 8)) * 2) * *(int *)(unaff_EBX + 4) + iStack_58);
    if (*(int *)(unaff_EBX + 4) != 0) {
      uVar4 = *(int *)(unaff_EBX + 4) * 2;
      do {
        puVar6 = param_1;
        puVar7 = puVar1;
        for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
          *puVar7 = *puVar6;
          puVar6 = puVar6 + 1;
          puVar7 = puVar7 + 1;
        }
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *(undefined1 *)puVar7 = *(undefined1 *)puVar6;
          puVar6 = (undefined4 *)((int)puVar6 + 1);
          puVar7 = (undefined4 *)((int)puVar7 + 1);
        }
        puVar1 = (undefined4 *)((int)puVar1 + iStack_6c);
        uVar4 = *(uint *)(unaff_EBX + 4) * 2;
        uVar5 = uVar5 + 1;
        param_1 = (undefined4 *)((int)param_1 + uVar4);
      } while (uVar5 < *(uint *)(unaff_EBX + 4));
    }
    (**(code **)(**(int **)(unaff_EBX + 0x110) + 0x80))(*(int **)(unaff_EBX + 0x110),0);
    *(undefined1 *)(unaff_retaddr + 0xc + unaff_EBX) = 1;
  }
  return;
}

