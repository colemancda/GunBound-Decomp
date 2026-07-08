/* FUN_004ffbe0 - 0x004ffbe0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004ffbe0(int *param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  char cVar4;
  uint uVar5;
  int iVar6;
  int *piVar7;
  undefined4 *puVar8;
  undefined4 *local_2c;
  int local_28;
  int local_24;
  _FILETIME local_18;
  undefined2 uStack_10;
  undefined2 uStack_e;
  undefined2 uStack_c;
  undefined2 uStack_a;
  undefined2 uStack_8;
  undefined4 uStack_6;
  undefined2 uStack_2;
  
  local_24 = 0;
  GetSystemTimeAsFileTime(&local_18);
  if (param_1[0xa5] != 0) {
    uVar5 = 0;
    if (param_1[0xa6] != 0) {
      piVar7 = (int *)param_1[0xa4];
      do {
        if (*piVar7 != 0) {
          iVar6 = ((int *)param_1[0xa4])[uVar5];
          goto LAB_004ffc26;
        }
        uVar5 = uVar5 + 1;
        piVar7 = piVar7 + 1;
      } while (uVar5 < (uint)param_1[0xa6]);
    }
  }
  iVar6 = 0;
LAB_004ffc26:
  if (iVar6 != 0) {
    do {
      if (iVar6 == 0) {
        local_28 = 0;
      }
      else {
        local_28 = *(int *)(iVar6 + 0xa4);
        if (local_28 == 0) {
          uVar5 = *(uint *)(iVar6 + 0xa8) % (uint)param_1[0xa6];
          local_28 = 0;
          do {
            uVar5 = uVar5 + 1;
            if ((uint)param_1[0xa6] <= uVar5) break;
            iVar2 = *(int *)(param_1[0xa4] + uVar5 * 4);
            if (iVar2 != 0) {
              local_28 = iVar2;
            }
          } while (local_28 == 0);
        }
      }
      if (*(int *)(iVar6 + 0x68) != 0) {
        uVar5 = 0;
        if (*(uint *)(iVar6 + 0x6c) != 0) {
          piVar7 = *(int **)(iVar6 + 100);
          do {
            if (*piVar7 != 0) {
              puVar3 = (undefined4 *)(*(int **)(iVar6 + 100))[uVar5];
              goto joined_r0x004ffcb0;
            }
            uVar5 = uVar5 + 1;
            piVar7 = piVar7 + 1;
          } while (uVar5 < *(uint *)(iVar6 + 0x6c));
        }
      }
      puVar3 = (undefined4 *)0x0;
joined_r0x004ffcb0:
      if (puVar3 != (undefined4 *)0x0) {
        if (puVar3 == (undefined4 *)0x0) {
          local_2c = (undefined4 *)0x0;
        }
        else {
          local_2c = (undefined4 *)puVar3[0x5d8];
          if (local_2c == (undefined4 *)0x0) {
            uVar5 = (uint)puVar3[0x5d9] % *(uint *)(iVar6 + 0x6c);
            local_2c = (undefined4 *)0x0;
            do {
              uVar5 = uVar5 + 1;
              if (*(uint *)(iVar6 + 0x6c) <= uVar5) break;
              puVar8 = *(undefined4 **)(*(int *)(iVar6 + 100) + uVar5 * 4);
              if (puVar8 != (undefined4 *)0x0) {
                local_2c = puVar8;
              }
            } while (local_2c == (undefined4 *)0x0);
          }
        }
        uVar1 = *puVar3;
        puVar8 = puVar3 + 1;
        if ((int)puVar3[0x5d6] < 6) {
          uVar5 = __aulldiv(local_18.dwLowDateTime - puVar3[0x5d4],
                            (local_18.dwHighDateTime - puVar3[0x5d5]) -
                            (uint)(local_18.dwLowDateTime < (uint)puVar3[0x5d4]),10000,0);
          if (uVar5 < 0x385) goto LAB_004ffe2f;
          iVar2 = *(int *)(iVar6 + 0x14);
          uStack_e = 0;
          uStack_c = 0;
          uStack_a = 0;
          uStack_8 = 0;
          uStack_6 = 0;
          uStack_2 = 0;
          uStack_10 = 2;
          if (iVar2 == 0) {
            iVar2 = *(int *)(iVar6 + 0x1c);
            if (iVar2 != 0) {
              uStack_e = *(undefined2 *)(iVar6 + 0x20);
              uStack_c = (undefined2)iVar2;
              uStack_a = (undefined2)((uint)iVar2 >> 0x10);
              FUN_004feb00(param_1,puVar8,&uStack_10,uVar1);
            }
            iVar2 = *(int *)(iVar6 + 0x24);
            if (iVar2 != 0) {
              uStack_e = *(undefined2 *)(iVar6 + 0x28);
              uStack_c = (undefined2)iVar2;
              uStack_a = (undefined2)((uint)iVar2 >> 0x10);
              goto LAB_004ffe20;
            }
          }
          else {
            uStack_c = (undefined2)iVar2;
            uStack_a = (undefined2)((uint)iVar2 >> 0x10);
            uStack_e = *(undefined2 *)(iVar6 + 0x18);
LAB_004ffe20:
            FUN_004feb00(param_1,puVar8,&uStack_10,uVar1);
          }
          puVar3[0x5d6] = puVar3[0x5d6] + 1;
LAB_004ffe2f:
          local_24 = local_24 + 1;
          puVar3 = local_2c;
        }
        else {
          if ((*(char *)(puVar3 + 0x5d7) == '\0') &&
             ((*(char *)(iVar6 + 0x30) != '\0' ||
              (cVar4 = (**(int (**)())(*param_1 + 4))(iVar6), cVar4 != '\0')))) {
            puVar3[0x5d6] = 0;
            *(undefined1 *)(puVar3 + 0x5d7) = 1;
            *(undefined1 *)(iVar6 + 0x30) = 1;
            goto LAB_004ffe2f;
          }
          (**(code **)*param_1)
                    (0,iVar6,*(undefined2 *)(puVar3 + 4),puVar3 + 5,
                     *(undefined2 *)((int)puVar3 + 0x12),puVar8);
          FUN_00500710();
          puVar3 = local_2c;
        }
        goto joined_r0x004ffcb0;
      }
      iVar6 = local_28;
    } while (local_28 != 0);
    if (local_24 != 0) {
      return;
    }
  }
  if (param_1[0xb0] != 0) {
    KillTimer((HWND)param_1[0xa3],param_1[0xb0]);
    param_1[0xb0] = 0;
  }
  return;
}

