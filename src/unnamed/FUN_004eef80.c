/* FUN_004eef80 - 0x004eef80 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_004eef80(int param_1,int param_2)

{
  LPCRITICAL_SECTION lpCriticalSection;
  char cVar1;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  undefined4 unaff_EDI;
  undefined8 uVar11;
  undefined4 *puVar12;
  undefined1 *puVar13;
  undefined4 uVar14;
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined4 local_20;
  undefined1 local_1c [28];
  
  if ((*(int *)(param_1 + 0x50) != 0) && (*(char *)(param_1 + 0x4c) != '\0')) {
    lpCriticalSection = (LPCRITICAL_SECTION)(param_1 + 0x20);
    EnterCriticalSection(lpCriticalSection);
    if (DAT_00793560 < *(uint *)(param_1 + 0x38)) {
      LeaveCriticalSection(lpCriticalSection);
      return;
    }
    piVar3 = *(int **)(DAT_00793558 + *(uint *)(param_1 + 0x38) * 4);
    uVar14 = 0;
    puVar13 = local_24;
    puVar12 = &local_20;
    iVar2 = (**(code **)(*piVar3 + 0x2c))
                      (piVar3,(param_2 != 0) - 1 & DAT_00588f44,DAT_00588f44,local_28,local_1c,
                       puVar12,puVar13,0);
    if (iVar2 == 0) {
      if (*(int *)(param_1 + 0x50) == 0) {
LAB_004ef344:
        cVar1 = (char)((uint)puVar13 >> 0x18);
        piVar3 = *(int **)(DAT_00793558 + *(int *)(param_1 + 0x38) * 4);
        (**(code **)(*piVar3 + 0x4c))(piVar3,puVar12,unaff_EDI,uVar14);
        if (cVar1 == '\0') {
          LeaveCriticalSection(lpCriticalSection);
          return;
        }
      }
      else {
        cVar1 = FUN_004eec70();
        uVar6 = DAT_00588f44;
        while (DAT_00588f44 = uVar6, cVar1 != '\0') {
          if (*(int *)(param_1 + 0xa4) < *(int *)(param_1 + 0x54)) {
            if (*(int *)(param_1 + 0x3c) != 0) {
              uVar5 = ((int)*(uint *)(param_1 + 0xac) < 0) - 1 & *(uint *)(param_1 + 0xac);
              puVar9 = *(undefined4 **)(param_1 + 0xa8);
              puVar10 = puVar12;
              for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                *puVar10 = *puVar9;
                puVar9 = puVar9 + 1;
                puVar10 = puVar10 + 1;
              }
              for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                *(undefined1 *)puVar10 = *(undefined1 *)puVar9;
                puVar9 = (undefined4 *)((int)puVar9 + 1);
                puVar10 = (undefined4 *)((int)puVar10 + 1);
              }
              FUN_004f0960();
              *(undefined4 *)(param_1 + 0xa4) = 0;
              cVar1 = FUN_004eec70();
              if (cVar1 != '\0') {
                iVar2 = FUN_00514950(*(undefined4 *)(param_1 + 0x98),*(undefined4 *)(param_1 + 0xa4)
                                     ,param_1 + 0x58,param_1 + 0x8c);
                *(int *)(param_1 + 0x54) = iVar2;
                if (iVar2 == 0) {
                  piVar3 = *(int **)(DAT_00793558 + *(int *)(param_1 + 0x38) * 4);
                  goto LAB_004ef161;
                }
                iVar2 = FUN_00512f80(param_1 + 0x58,iVar2,0,0,0,DAT_00588f3c);
                if (iVar2 != 0) {
                  FUN_005133a0(&stack0xffffffc8);
                  goto LAB_004ef13b;
                }
              }
LAB_004ef25f:
              piVar3 = *(int **)(DAT_00793558 + *(int *)(param_1 + 0x38) * 4);
              (**(code **)(*piVar3 + 0x4c))(piVar3,puVar12,unaff_EDI,uVar14,puVar13);
              goto LAB_004ef285;
            }
            if (*(int *)(param_1 + 0x48) == 0) {
              uVar5 = ((int)*(uint *)(param_1 + 0xac) < 0) - 1 & *(uint *)(param_1 + 0xac);
              puVar9 = *(undefined4 **)(param_1 + 0xa8);
              puVar10 = puVar12;
              for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                *puVar10 = *puVar9;
                puVar9 = puVar9 + 1;
                puVar10 = puVar10 + 1;
              }
              for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                *(undefined1 *)puVar10 = *(undefined1 *)puVar9;
                puVar9 = (undefined4 *)((int)puVar9 + 1);
                puVar10 = (undefined4 *)((int)puVar10 + 1);
              }
              uVar5 = DAT_00588f44 - *(int *)(param_1 + 0xac);
              puVar9 = (undefined4 *)(*(int *)(param_1 + 0xac) + (int)puVar12);
              uVar6 = uVar5 >> 2;
              if (DAT_00588f38 == 8) {
                uVar4 = 0x80808080;
              }
              else {
                uVar4 = 0;
              }
              for (; uVar6 != 0; uVar6 = uVar6 - 1) {
                *puVar9 = uVar4;
                puVar9 = puVar9 + 1;
              }
              for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                *(char *)puVar9 = (char)uVar4;
                puVar9 = (undefined4 *)((int)puVar9 + 1);
              }
              *(undefined4 *)(param_1 + 0x48) = 1;
            }
            else if (*(int *)(param_1 + 0x48) == 1) {
              uVar5 = uVar6 >> 2;
              puVar9 = puVar12;
              if (DAT_00588f38 == 8) {
                uVar4 = 0x80808080;
              }
              else {
                uVar4 = 0;
              }
              for (; uVar5 != 0; uVar5 = uVar5 - 1) {
                *puVar9 = uVar4;
                puVar9 = puVar9 + 1;
              }
              for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
                *(char *)puVar9 = (char)uVar4;
                puVar9 = (undefined4 *)((int)puVar9 + 1);
              }
              *(undefined4 *)(param_1 + 0x48) = 2;
            }
            goto LAB_004ef344;
          }
          uVar11 = FUN_0050f890(*(undefined4 *)(param_1 + 0x9c),
                                *(int *)(param_1 + 0xa8) + *(int *)(param_1 + 0xac));
          iVar2 = (int)uVar11;
          if (iVar2 < 1) goto LAB_004ef25f;
          iVar8 = *(int *)(param_1 + 0xac) + (int)((ulonglong)uVar11 >> 0x20);
          *(int *)(param_1 + 0x9c) = *(int *)(param_1 + 0x9c) + iVar2;
          *(int *)(param_1 + 0xa4) = *(int *)(param_1 + 0xa4) - iVar2;
          *(int *)(param_1 + 0xac) = iVar8;
          if (*(int *)(param_1 + 0xb0) <= iVar8) {
            uVar5 = ((int)*(uint *)(param_1 + 0xb0) < 0) - 1 & *(uint *)(param_1 + 0xb0);
            puVar9 = *(undefined4 **)(param_1 + 0xa8);
            puVar10 = puVar12;
            for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
              *puVar10 = *puVar9;
              puVar9 = puVar9 + 1;
              puVar10 = puVar10 + 1;
            }
            for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
              *(undefined1 *)puVar10 = *(undefined1 *)puVar9;
              puVar9 = (undefined4 *)((int)puVar9 + 1);
              puVar10 = (undefined4 *)((int)puVar10 + 1);
            }
            uVar6 = *(uint *)(param_1 + 0xb0);
            puVar9 = *(undefined4 **)(param_1 + 0xa8);
            uVar5 = *(int *)(param_1 + 0xac) - uVar6;
            if (DAT_00588f44 < uVar5) {
              uVar5 = ((int)uVar6 < 0) - 1 & uVar6;
              puVar10 = (undefined4 *)(uVar6 + (int)puVar9);
              for (uVar7 = uVar5 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
                *puVar9 = *puVar10;
                puVar10 = puVar10 + 1;
                puVar9 = puVar9 + 1;
              }
            }
            else {
              uVar5 = ((int)uVar5 < 0) - 1 & uVar5;
              puVar10 = (undefined4 *)(uVar6 + (int)puVar9);
              for (uVar7 = uVar5 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
                *puVar9 = *puVar10;
                puVar10 = puVar10 + 1;
                puVar9 = puVar9 + 1;
              }
            }
            for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
              *(undefined1 *)puVar9 = *(undefined1 *)puVar10;
              puVar10 = (undefined4 *)((int)puVar10 + 1);
              puVar9 = (undefined4 *)((int)puVar9 + 1);
            }
            *(int *)(param_1 + 0xac) = *(int *)(param_1 + 0xac) - *(int *)(param_1 + 0xb0);
            goto LAB_004ef344;
          }
LAB_004ef13b:
          cVar1 = FUN_004eec70();
          uVar6 = DAT_00588f44;
        }
        piVar3 = *(int **)(DAT_00793558 + *(int *)(param_1 + 0x38) * 4);
LAB_004ef161:
        (**(code **)(*piVar3 + 0x4c))(piVar3,puVar12,unaff_EDI,uVar14,puVar13);
      }
      LeaveCriticalSection(lpCriticalSection);
      if (DAT_00793549 != '\0') {
        (**(code **)(*(int *)*DAT_00793554 + 0xc))();
        DAT_00793568 = 0;
      }
    }
    else {
LAB_004ef285:
      LeaveCriticalSection(lpCriticalSection);
      if (DAT_00793549 != '\0') {
        (**(code **)(*(int *)*DAT_00793554 + 0xc))();
        DAT_00793568 = 0;
        return;
      }
    }
  }
  return;
}

