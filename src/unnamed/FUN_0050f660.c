/* FUN_0050f660 - 0x0050f660 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0050f660(int param_1)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  
  if ((*(char *)(param_1 + 0x44) != '\0') && (iVar4 = *(int *)(param_1 + 0x38), 0 < iVar4)) {
    iVar5 = *(int *)(param_1 + 0x50);
    cVar1 = FUN_0050f770();
    if (cVar1 == '\0') {
      uVar6 = *(uint *)(param_1 + 0x40);
      if ((iVar5 < *(int *)(param_1 + 0x2c) + (int)(*(int *)(param_1 + 0x34) * uVar6) / iVar4) &&
         (uVar2 = uVar6 - *(int *)(param_1 + 0x3c), uVar2 = uVar2 & ((int)uVar2 < 0) - 1,
         uVar2 != uVar6)) {
        *(uint *)(param_1 + 0x40) = uVar2;
        if (*(int **)(param_1 + 8) != (int *)0x0) {
          (**(code **)(**(int **)(param_1 + 8) + 0x1c))
                    (0x2000,*(undefined4 *)(param_1 + 0x24),uVar2);
        }
      }
      iVar4 = *(int *)(param_1 + 0x38);
      iVar5 = *(int *)(param_1 + 0x2c);
      if (0 < iVar4) {
        iVar5 = iVar5 + (*(int *)(param_1 + 0x34) * *(int *)(param_1 + 0x40)) / iVar4;
      }
      iVar3 = ScrollListWidget_ThumbHeight();
      if (iVar3 + iVar5 < *(int *)(param_1 + 0x50)) {
        iVar5 = *(int *)(param_1 + 0x3c) + *(int *)(param_1 + 0x40);
        iVar4 = iVar4 - *(int *)(param_1 + 0x3c);
        iVar3 = iVar4;
        if (iVar5 <= iVar4) {
          iVar3 = iVar5;
        }
        if (iVar3 < 0) {
          iVar4 = 0;
        }
        else if (iVar5 <= iVar4) {
          iVar4 = iVar5;
        }
        if (iVar4 != *(int *)(param_1 + 0x40)) {
          *(int *)(param_1 + 0x40) = iVar4;
          if (*(int **)(param_1 + 8) != (int *)0x0) {
            (**(code **)(**(int **)(param_1 + 8) + 0x1c))
                      (0x2000,*(undefined4 *)(param_1 + 0x24),iVar4);
          }
        }
      }
    }
  }
  uVar6 = 0;
  if (*(int *)(param_1 + 0x10) != 0) {
    if (*(int *)(param_1 + 0x10) == 0) {
                    /* WARNING: Subroutine does not return */
      FUN_004010c0(0x80070057);
    }
    do {
      (**(code **)(**(int **)(*(int *)(param_1 + 0xc) + uVar6 * 4) + 0x20))();
      uVar6 = uVar6 + 1;
    } while (uVar6 < *(uint *)(param_1 + 0x10));
  }
  return;
}

