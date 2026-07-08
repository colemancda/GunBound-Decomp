/* FUN_00443840 - 0x00443840 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x00443957) */
/* WARNING: Removing unreachable block (ram,0x00443967) */
/* WARNING: Removing unreachable block (ram,0x00443971) */
/* WARNING: Removing unreachable block (ram,0x00443974) */
/* WARNING: Removing unreachable block (ram,0x00443963) */
/* WARNING: Removing unreachable block (ram,0x00443982) */
/* WARNING: Removing unreachable block (ram,0x0044398f) */
/* WARNING: Removing unreachable block (ram,0x0044399a) */
/* WARNING: Removing unreachable block (ram,0x00443996) */
/* WARNING: Removing unreachable block (ram,0x0044398a) */
/* WARNING: Removing unreachable block (ram,0x0044399d) */

void FUN_00443840(int param_1,undefined4 *param_2,int *param_3)

{
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  int *piVar5;
  int *piVar6;
  undefined1 local_50 [4];
  undefined1 local_4c;
  undefined4 local_3c;
  undefined4 local_38;
  undefined **local_34 [10];
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00537a38) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  if (*(char *)((int)param_3 + 0x15) != '\0') {
    local_38 = 0xf;
    local_3c = 0;
    local_4c = 0;
    FUN_0040bee0(s_invalid_map_set_T_iterator_00552000,0x1b);
    local_4 = 0;
    FUN_00409fd0(local_50);
    local_34[0] = &PTR_FUN_00544b74;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8(local_34,&DAT_00558458);
  }
  FUN_00443780();
  piVar6 = (int *)*param_3;
  if (*(char *)((int)piVar6 + 0x15) == '\0') {
    if (*(char *)(param_3[2] + 0x15) == '\0') {
      piVar6 = (int *)param_3[2];
    }
  }
  else {
    piVar6 = (int *)param_3[2];
  }
  piVar5 = (int *)param_3[1];
  if (*(char *)((int)piVar6 + 0x15) == '\0') {
    piVar6[1] = (int)piVar5;
  }
  if (*(int **)(*(int *)(param_1 + 4) + 4) == param_3) {
    *(int **)(*(int *)(param_1 + 4) + 4) = piVar6;
  }
  else if ((int *)*piVar5 == param_3) {
    *piVar5 = (int)piVar6;
  }
  else {
    piVar5[2] = (int)piVar6;
  }
  puVar1 = *(undefined4 **)(param_1 + 4);
  if ((int *)*puVar1 == param_3) {
    piVar3 = piVar5;
    if (*(char *)((int)piVar6 + 0x15) == '\0') {
      FUN_00443c00();
    }
    *puVar1 = piVar3;
  }
  iVar2 = *(int *)(param_1 + 4);
  if (*(int **)(iVar2 + 8) == param_3) {
    if (*(char *)((int)piVar6 + 0x15) == '\0') {
      FUN_00443be0();
      *(undefined4 *)(iVar2 + 8) = uVar4;
    }
    else {
      *(int **)(iVar2 + 8) = piVar5;
    }
  }
  if ((char)param_3[5] == '\x01') {
    if (piVar6 != *(int **)(*(int *)(param_1 + 4) + 4)) {
      do {
        piVar3 = piVar5;
        if ((char)piVar6[5] != '\x01') break;
        piVar5 = (int *)*piVar3;
        if (piVar6 == piVar5) {
          piVar5 = (int *)piVar3[2];
          if ((char)piVar5[5] == '\0') {
            *(undefined1 *)(piVar5 + 5) = 1;
            *(undefined1 *)(piVar3 + 5) = 0;
            FUN_00443b00(param_1);
            piVar5 = (int *)piVar3[2];
          }
          if (*(char *)((int)piVar5 + 0x15) == '\0') {
            if ((*(char *)(*piVar5 + 0x14) != '\x01') || (*(char *)(piVar5[2] + 0x14) != '\x01')) {
              if (*(char *)(piVar5[2] + 0x14) == '\x01') {
                *(undefined1 *)(*piVar5 + 0x14) = 1;
                *(undefined1 *)(piVar5 + 5) = 0;
                FUN_004437e0(param_1);
                piVar5 = (int *)piVar3[2];
              }
              *(char *)(piVar5 + 5) = (char)piVar3[5];
              *(undefined1 *)(piVar3 + 5) = 1;
              *(undefined1 *)(piVar5[2] + 0x14) = 1;
              FUN_00443b00(param_1);
              break;
            }
LAB_00443a72:
            *(undefined1 *)(piVar5 + 5) = 0;
          }
        }
        else {
          if ((char)piVar5[5] == '\0') {
            *(undefined1 *)(piVar5 + 5) = 1;
            *(undefined1 *)(piVar3 + 5) = 0;
            FUN_004437e0(param_1);
            piVar5 = (int *)*piVar3;
          }
          if (*(char *)((int)piVar5 + 0x15) == '\0') {
            if ((*(char *)(piVar5[2] + 0x14) == '\x01') && (*(char *)(*piVar5 + 0x14) == '\x01'))
            goto LAB_00443a72;
            if (*(char *)(*piVar5 + 0x14) == '\x01') {
              *(undefined1 *)(piVar5[2] + 0x14) = 1;
              *(undefined1 *)(piVar5 + 5) = 0;
              FUN_00443b00(param_1);
              piVar5 = (int *)*piVar3;
            }
            *(char *)(piVar5 + 5) = (char)piVar3[5];
            *(undefined1 *)(piVar3 + 5) = 1;
            *(undefined1 *)(*piVar5 + 0x14) = 1;
            FUN_004437e0(param_1);
            break;
          }
        }
        piVar5 = (int *)piVar3[1];
        piVar6 = piVar3;
      } while (piVar3 != *(int **)(*(int *)(param_1 + 4) + 4));
    }
    *(undefined1 *)(piVar6 + 5) = 1;
  }
  _free(param_3);
  if (*(int *)(param_1 + 8) != 0) {
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -1;
  }
  *param_2 = param_3;
  return;
}

