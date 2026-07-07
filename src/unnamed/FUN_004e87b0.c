/* FUN_004e87b0 - 0x004e87b0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x004e88c7) */
/* WARNING: Removing unreachable block (ram,0x004e88d7) */
/* WARNING: Removing unreachable block (ram,0x004e88e1) */
/* WARNING: Removing unreachable block (ram,0x004e88e4) */
/* WARNING: Removing unreachable block (ram,0x004e88d3) */
/* WARNING: Removing unreachable block (ram,0x004e88f2) */
/* WARNING: Removing unreachable block (ram,0x004e88ff) */
/* WARNING: Removing unreachable block (ram,0x004e890a) */
/* WARNING: Removing unreachable block (ram,0x004e8906) */
/* WARNING: Removing unreachable block (ram,0x004e88fa) */
/* WARNING: Removing unreachable block (ram,0x004e890d) */

void FUN_004e87b0(int param_1,undefined4 *param_2,int *param_3)

{
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  int *piVar5;
  int *piVar6;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_50 [4];
  undefined1 local_4c;
  undefined4 local_3c;
  undefined4 local_38;
  undefined **local_34 [10];
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00537a38;
  *unaff_FS_OFFSET = &local_c;
  if (*(char *)((int)param_3 + 0xf) != '\0') {
    local_38 = 0xf;
    local_3c = 0;
    local_4c = 0;
    FUN_0040bee0(s_invalid_map_set<T>_iterator_00552000,0x1b);
    local_4 = 0;
    FUN_00409fd0(local_50);
    local_34[0] = &PTR_FUN_00544b74;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8(local_34,&DAT_00558458);
  }
  FUN_004e8f10();
  piVar6 = (int *)*param_3;
  if (*(char *)((int)piVar6 + 0xf) == '\0') {
    if (*(char *)(param_3[2] + 0xf) == '\0') {
      piVar6 = (int *)param_3[2];
    }
  }
  else {
    piVar6 = (int *)param_3[2];
  }
  piVar5 = (int *)param_3[1];
  if (*(char *)((int)piVar6 + 0xf) == '\0') {
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
    if (*(char *)((int)piVar6 + 0xf) == '\0') {
      piVar3 = (int *)FUN_004e8d30();
    }
    *puVar1 = piVar3;
  }
  iVar2 = *(int *)(param_1 + 4);
  if (*(int **)(iVar2 + 8) == param_3) {
    if (*(char *)((int)piVar6 + 0xf) == '\0') {
      uVar4 = FUN_004e8d10();
      *(undefined4 *)(iVar2 + 8) = uVar4;
    }
    else {
      *(int **)(iVar2 + 8) = piVar5;
    }
  }
  if (*(char *)((int)param_3 + 0xe) == '\x01') {
    if (piVar6 != *(int **)(*(int *)(param_1 + 4) + 4)) {
      do {
        piVar3 = piVar5;
        if (*(char *)((int)piVar6 + 0xe) != '\x01') break;
        piVar5 = (int *)*piVar3;
        if (piVar6 == piVar5) {
          piVar5 = (int *)piVar3[2];
          if (*(char *)((int)piVar5 + 0xe) == '\0') {
            *(undefined1 *)((int)piVar5 + 0xe) = 1;
            *(undefined1 *)((int)piVar3 + 0xe) = 0;
            FUN_004e8cb0(param_1);
            piVar5 = (int *)piVar3[2];
          }
          if (*(char *)((int)piVar5 + 0xf) == '\0') {
            if ((*(char *)(*piVar5 + 0xe) != '\x01') || (*(char *)(piVar5[2] + 0xe) != '\x01')) {
              if (*(char *)(piVar5[2] + 0xe) == '\x01') {
                *(undefined1 *)(*piVar5 + 0xe) = 1;
                *(undefined1 *)((int)piVar5 + 0xe) = 0;
                FUN_004e8d50(param_1);
                piVar5 = (int *)piVar3[2];
              }
              *(undefined1 *)((int)piVar5 + 0xe) = *(undefined1 *)((int)piVar3 + 0xe);
              *(undefined1 *)((int)piVar3 + 0xe) = 1;
              *(undefined1 *)(piVar5[2] + 0xe) = 1;
              FUN_004e8cb0(param_1);
              break;
            }
LAB_004e89e2:
            *(undefined1 *)((int)piVar5 + 0xe) = 0;
          }
        }
        else {
          if (*(char *)((int)piVar5 + 0xe) == '\0') {
            *(undefined1 *)((int)piVar5 + 0xe) = 1;
            *(undefined1 *)((int)piVar3 + 0xe) = 0;
            FUN_004e8d50(param_1);
            piVar5 = (int *)*piVar3;
          }
          if (*(char *)((int)piVar5 + 0xf) == '\0') {
            if ((*(char *)(piVar5[2] + 0xe) == '\x01') && (*(char *)(*piVar5 + 0xe) == '\x01'))
            goto LAB_004e89e2;
            if (*(char *)(*piVar5 + 0xe) == '\x01') {
              *(undefined1 *)(piVar5[2] + 0xe) = 1;
              *(undefined1 *)((int)piVar5 + 0xe) = 0;
              FUN_004e8cb0(param_1);
              piVar5 = (int *)*piVar3;
            }
            *(undefined1 *)((int)piVar5 + 0xe) = *(undefined1 *)((int)piVar3 + 0xe);
            *(undefined1 *)((int)piVar3 + 0xe) = 1;
            *(undefined1 *)(*piVar5 + 0xe) = 1;
            FUN_004e8d50(param_1);
            break;
          }
        }
        piVar5 = (int *)piVar3[1];
        piVar6 = piVar3;
      } while (piVar3 != *(int **)(*(int *)(param_1 + 4) + 4));
    }
    *(undefined1 *)((int)piVar6 + 0xe) = 1;
  }
  _free(param_3);
  if (*(int *)(param_1 + 8) != 0) {
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -1;
  }
  *param_2 = param_3;
  *unaff_FS_OFFSET = local_c;
  return;
}

