/* FUN_0040bae0 - 0x0040bae0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall
FUN_0040bae0(undefined4 *param_1,undefined4 *param_2,char param_3,undefined4 param_4)

{
  char cVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  int unaff_EDI;
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
  if (0x3ffffffd < *(uint *)(unaff_EDI + 8)) {
    local_38 = 0xf;
    local_3c = 0;
    local_4c = 0;
    FUN_0040bee0(s_map_set_T_too_long_00551fec,0x13);
    local_4 = 0;
    FUN_00409fd0(local_50);
    local_34[0] = &PTR_FUN_00544b68;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8(local_34,&DAT_0055841c);
  }
  piVar3 = (int *)FUN_0040bea0(*(undefined4 *)(unaff_EDI + 4),param_1,*(undefined4 *)(unaff_EDI + 4)
                               ,param_4,0);
  *(int *)(unaff_EDI + 8) = *(int *)(unaff_EDI + 8) + 1;
  if (param_1 == *(undefined4 **)(unaff_EDI + 4)) {
    (*(undefined4 **)(unaff_EDI + 4))[1] = piVar3;
    **(undefined4 **)(unaff_EDI + 4) = piVar3;
    *(int **)(*(int *)(unaff_EDI + 4) + 8) = piVar3;
  }
  else if (param_3 == '\0') {
    param_1[2] = piVar3;
    if (param_1 == *(undefined4 **)(*(int *)(unaff_EDI + 4) + 8)) {
      *(int **)(*(int *)(unaff_EDI + 4) + 8) = piVar3;
    }
  }
  else {
    *param_1 = piVar3;
    if (param_1 == (undefined4 *)**(int **)(unaff_EDI + 4)) {
      **(int **)(unaff_EDI + 4) = (int)piVar3;
    }
  }
  cVar1 = *(char *)(piVar3[1] + 0x10);
  piVar6 = piVar3;
  do {
    if (cVar1 != '\0') {
      *(undefined1 *)(*(int *)(*(int *)(unaff_EDI + 4) + 4) + 0x10) = 1;
      *param_2 = piVar3;
      return;
    }
    piVar4 = piVar6 + 1;
    piVar2 = (int *)*piVar4;
    piVar5 = *(int **)piVar2[1];
    if (piVar2 == piVar5) {
      piVar5 = (int *)((undefined4 *)piVar2[1])[2];
      if ((char)piVar5[4] == '\0') {
LAB_0040bbd5:
        *(undefined1 *)(*piVar4 + 0x10) = 1;
        *(undefined1 *)(piVar5 + 4) = 1;
        *(undefined1 *)(*(int *)(*piVar4 + 4) + 0x10) = 0;
        piVar6 = *(int **)(*piVar4 + 4);
      }
      else {
        if (piVar6 == (int *)piVar2[2]) {
          FUN_0040bc80(unaff_EDI);
          piVar6 = piVar2;
        }
        *(undefined1 *)(piVar6[1] + 0x10) = 1;
        *(undefined1 *)(*(int *)(piVar6[1] + 4) + 0x10) = 0;
        FUN_0040bd20(unaff_EDI);
      }
    }
    else {
      if ((char)piVar5[4] == '\0') goto LAB_0040bbd5;
      if (piVar6 == (int *)*piVar2) {
        FUN_0040bd20(unaff_EDI);
        piVar6 = piVar2;
      }
      *(undefined1 *)(piVar6[1] + 0x10) = 1;
      *(undefined1 *)(*(int *)(piVar6[1] + 4) + 0x10) = 0;
      FUN_0040bc80(unaff_EDI);
    }
    cVar1 = *(char *)(piVar6[1] + 0x10);
  } while( true );
}

