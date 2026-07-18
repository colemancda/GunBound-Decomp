/* FUN_004ee320 - 0x004ee320 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004ee320(int param_1)

{
  uint *puVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  undefined4 unaff_EDI;
  int iVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  undefined4 uStack_28;
  
  piVar3 = *(int **)(param_1 + 4);
  if (piVar3 != (int *)0x0) {
    uStack_28 = 0;
    puVar1 = (uint *)(param_1 + 0x588);
    iVar2 = param_1 + 0x88;
    iVar8 = 0x14;
    *puVar1 = 0x40;
    iVar9 = iVar2;
    iVar4 = (**(code **)(*piVar3 + 0x28))(piVar3,0x14,iVar2,puVar1);
    if (iVar4 == -0x7ff8ffe2) {
      piVar3 = *(int **)(param_1 + 4);
      if (piVar3 != (int *)0x0) {
        (**(code **)(*piVar3 + 0x1c))(piVar3);
      }
      *(undefined1 *)(param_1 + 0x54) = 1;
      iVar4 = (**(code **)(**(int **)(param_1 + 4) + 0x28))
                        (*(int **)(param_1 + 4),0x14,iVar2,puVar1,0);
    }
    if (-1 < iVar4) {
      if (*(char *)(param_1 + 0x5a4) != '\0') {
        iVar2 = *(int *)(param_1 + 0x28) + *(int *)(param_1 + 0x59c);
        iVar4 = *(int *)(param_1 + 0x58c);
        iVar7 = iVar4;
        if (iVar4 <= iVar2) {
          iVar7 = iVar2;
        }
        iVar5 = *(int *)(param_1 + 0x590);
        if ((iVar7 <= iVar5) && (iVar5 = iVar4, iVar4 <= iVar2)) {
          iVar5 = iVar2;
        }
        *(int *)(param_1 + 0x59c) = iVar5;
        iVar2 = *(int *)(param_1 + 0x2c) + *(int *)(param_1 + 0x5a0);
        iVar4 = *(int *)(param_1 + 0x594);
        iVar7 = iVar4;
        if (iVar4 <= iVar2) {
          iVar7 = iVar2;
        }
        iVar5 = *(int *)(param_1 + 0x598);
        if ((iVar7 <= iVar5) && (iVar5 = iVar2, iVar2 < iVar4)) {
          iVar5 = iVar4;
        }
        *(int *)(param_1 + 0x5a0) = iVar5;
      }
      uVar10 = 0;
      if (*puVar1 != 0) {
        pcVar6 = (char *)(param_1 + 0x8c);
        do {
          iVar2 = *(int *)(pcVar6 + -4);
          iVar4 = iVar2 + -0xc;
          if ((-1 < iVar4) && (iVar4 < 8)) {
            if (*pcVar6 < '\0') {
              if (*(int *)(param_1 + 0x68 + iVar4 * 4) == 0) {
                EnqueueInputEvent(iVar2 + 8,*(undefined4 *)(param_1 + 0x59c),
                             *(undefined4 *)(param_1 + 0x5a0));
                *(undefined4 *)(param_1 + 0x68 + iVar4 * 4) = *(undefined4 *)(param_1 + 0x50);
                *(undefined1 *)(iVar2 + 0x54 + param_1) = 1;
              }
              else {
                EnqueueInputEvent(iVar2 + 0x1c,*(undefined4 *)(param_1 + 0x59c),
                             *(undefined4 *)(param_1 + 0x5a0));
                *(undefined1 *)(iVar2 + 0x54 + param_1) = 1;
              }
            }
            else {
              EnqueueInputEvent(iVar2 + 0x12,*(undefined4 *)(param_1 + 0x59c),
                           *(undefined4 *)(param_1 + 0x5a0));
            }
          }
          uVar10 = uVar10 + 1;
          pcVar6 = pcVar6 + 0x14;
        } while (uVar10 < *puVar1);
      }
      piVar3 = (int *)(param_1 + 0x28);
      *piVar3 = 0;
      *(undefined4 *)(param_1 + 0x2c) = 0;
      *(undefined4 *)(param_1 + 0x30) = 0;
      *(undefined4 *)(param_1 + 0x34) = 0;
      *(undefined4 *)(param_1 + 0x38) = 0;
      *(undefined4 *)(param_1 + 0x3c) = 0;
      *(undefined4 *)(param_1 + 0x40) = 0;
      *(undefined4 *)(param_1 + 0x44) = 0;
      (**(code **)(**(int **)(param_1 + 4) + 0x24))(*(int **)(param_1 + 4),0x10,&uStack_28);
      *(int *)(param_1 + 0x2c) = *(int *)(param_1 + 0x2c) + iVar9;
      *(uint *)(param_1 + 0x30) = *(int *)(param_1 + 0x30) + uVar10;
      *piVar3 = *piVar3 + iVar8;
      *(undefined4 *)(param_1 + 0x58) = uStack_28;
      *(undefined4 *)(param_1 + 0x5c) = unaff_EDI;
    }
  }
  return;
}

