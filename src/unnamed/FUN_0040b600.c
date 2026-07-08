/* FUN_0040b600 - 0x0040b600 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x0040b717) */
/* WARNING: Removing unreachable block (ram,0x0040b727) */
/* WARNING: Removing unreachable block (ram,0x0040b731) */
/* WARNING: Removing unreachable block (ram,0x0040b734) */
/* WARNING: Removing unreachable block (ram,0x0040b723) */
/* WARNING: Removing unreachable block (ram,0x0040b742) */
/* WARNING: Removing unreachable block (ram,0x0040b74f) */
/* WARNING: Removing unreachable block (ram,0x0040b75a) */
/* WARNING: Removing unreachable block (ram,0x0040b756) */
/* WARNING: Removing unreachable block (ram,0x0040b74a) */
/* WARNING: Removing unreachable block (ram,0x0040b75d) */

void FUN_0040b600(int param_1,undefined4 *param_2,int *param_3)

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
  undefined4 local_4;

  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00537a38) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  if (*(char *)((int)param_3 + 0x11) != '\0') {
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
  FUN_0040c1b0();
  piVar6 = (int *)*param_3;
  if (*(char *)((int)piVar6 + 0x11) == '\0') {
    if (*(char *)(param_3[2] + 0x11) == '\0') {
      piVar6 = (int *)param_3[2];
    }
  }
  else {
    piVar6 = (int *)param_3[2];
  }
  piVar5 = (int *)param_3[1];
  if (*(char *)((int)piVar6 + 0x11) == '\0') {
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
    if (*(char *)((int)piVar6 + 0x11) == '\0') {
      /* FUN_0040bd00 is void-returning (see its own definition) - this
       * call site's return-value use is a Ghidra per-call-site
       * decompilation inconsistency, same class as entry/WinMain.c's
       * FUN_004058c0 fix. piVar3 keeps its prior value (piVar5) as a
       * result. */
      FUN_0040bd00();
    }
    *puVar1 = piVar3;
  }
  iVar2 = *(int *)(param_1 + 4);
  if (*(int **)(iVar2 + 8) == param_3) {
    if (*(char *)((int)piVar6 + 0x11) == '\0') {
      /* FUN_0040bce0 is void-returning (see its own definition) - this
       * call site's return-value use is a Ghidra per-call-site
       * decompilation inconsistency, same class as entry/WinMain.c's
       * FUN_004058c0 fix. uVar4 is left uninitialized here as a
       * result. */
      FUN_0040bce0();
      *(undefined4 *)(iVar2 + 8) = uVar4;
    }
    else {
      *(int **)(iVar2 + 8) = piVar5;
    }
  }
  if ((char)param_3[4] == '\x01') {
    if (piVar6 != *(int **)(*(int *)(param_1 + 4) + 4)) {
      do {
        piVar3 = piVar5;
        if ((char)piVar6[4] != '\x01') break;
        piVar5 = (int *)*piVar3;
        if (piVar6 == piVar5) {
          piVar5 = (int *)piVar3[2];
          if ((char)piVar5[4] == '\0') {
            *(undefined1 *)(piVar5 + 4) = 1;
            *(undefined1 *)(piVar3 + 4) = 0;
            FUN_0040bc80(param_1);
            piVar5 = (int *)piVar3[2];
          }
          if (*(char *)((int)piVar5 + 0x11) == '\0') {
            if ((*(char *)(*piVar5 + 0x10) != '\x01') || (*(char *)(piVar5[2] + 0x10) != '\x01')) {
              if (*(char *)(piVar5[2] + 0x10) == '\x01') {
                *(undefined1 *)(*piVar5 + 0x10) = 1;
                *(undefined1 *)(piVar5 + 4) = 0;
                FUN_0040bd20(param_1);
                piVar5 = (int *)piVar3[2];
              }
              *(char *)(piVar5 + 4) = (char)piVar3[4];
              *(undefined1 *)(piVar3 + 4) = 1;
              *(undefined1 *)(piVar5[2] + 0x10) = 1;
              FUN_0040bc80(param_1);
              break;
            }
LAB_0040b832:
            *(undefined1 *)(piVar5 + 4) = 0;
          }
        }
        else {
          if ((char)piVar5[4] == '\0') {
            *(undefined1 *)(piVar5 + 4) = 1;
            *(undefined1 *)(piVar3 + 4) = 0;
            FUN_0040bd20(param_1);
            piVar5 = (int *)*piVar3;
          }
          if (*(char *)((int)piVar5 + 0x11) == '\0') {
            if ((*(char *)(piVar5[2] + 0x10) == '\x01') && (*(char *)(*piVar5 + 0x10) == '\x01'))
            goto LAB_0040b832;
            if (*(char *)(*piVar5 + 0x10) == '\x01') {
              *(undefined1 *)(piVar5[2] + 0x10) = 1;
              *(undefined1 *)(piVar5 + 4) = 0;
              FUN_0040bc80(param_1);
              piVar5 = (int *)*piVar3;
            }
            *(char *)(piVar5 + 4) = (char)piVar3[4];
            *(undefined1 *)(piVar3 + 4) = 1;
            *(undefined1 *)(*piVar5 + 0x10) = 1;
            FUN_0040bd20(param_1);
            break;
          }
        }
        piVar5 = (int *)piVar3[1];
        piVar6 = piVar3;
      } while (piVar3 != *(int **)(*(int *)(param_1 + 4) + 4));
    }
    *(undefined1 *)(piVar6 + 4) = 1;
  }
  _free(param_3);
  if (*(int *)(param_1 + 8) != 0) {
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -1;
  }
  *param_2 = param_3;
  return;
}

