/* FUN_004dfe70 - 0x004dfe70 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_004dfe70(undefined4 *param_1,int *param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  
  piVar4 = param_2 + (((int)param_3 - (int)param_2 >> 2) - ((int)param_3 - (int)param_2 >> 0x1f) >>
                     1);
  FUN_004e0090(param_3 + -1);
  piVar5 = piVar4 + 1;
  for (; param_2 < piVar4; piVar4 = piVar4 + -1) {
    if ((piVar4[-1] < *piVar4) || (*piVar4 < piVar4[-1])) break;
  }
  piVar6 = piVar5;
  piVar3 = piVar4;
  if (piVar5 < param_3) {
    do {
      piVar6 = piVar5;
      if ((*piVar5 < *piVar4) || (*piVar4 < *piVar5)) break;
      piVar5 = piVar5 + 1;
      piVar6 = piVar5;
    } while (piVar5 < param_3);
  }
joined_r0x004dfed5:
  do {
    if (param_3 <= piVar5) {
joined_r0x004dfefb:
      for (; param_2 < piVar4; piVar4 = piVar4 + -1) {
        if (*piVar3 <= piVar4[-1]) {
          if (*piVar3 < piVar4[-1]) break;
          iVar1 = piVar3[-1];
          piVar3 = piVar3 + -1;
          *piVar3 = piVar4[-1];
          piVar4[-1] = iVar1;
        }
      }
      if (piVar4 == param_2) {
        if (piVar5 == param_3) {
          param_1[1] = piVar6;
          *param_1 = piVar3;
          return param_1;
        }
        if (piVar6 != piVar5) {
          iVar1 = *piVar3;
          *piVar3 = *piVar6;
          *piVar6 = iVar1;
        }
        iVar1 = *piVar3;
        *piVar3 = *piVar5;
        *piVar5 = iVar1;
        piVar5 = piVar5 + 1;
        piVar6 = piVar6 + 1;
        piVar3 = piVar3 + 1;
      }
      else {
        piVar4 = piVar4 + -1;
        if (piVar5 == param_3) {
          piVar3 = piVar3 + -1;
          if (piVar4 != piVar3) {
            iVar1 = *piVar4;
            *piVar4 = *piVar3;
            *piVar3 = iVar1;
          }
          iVar1 = *piVar3;
          *piVar3 = piVar6[-1];
          piVar6[-1] = iVar1;
          piVar6 = piVar6 + -1;
        }
        else {
          iVar1 = *piVar5;
          *piVar5 = *piVar4;
          *piVar4 = iVar1;
          piVar5 = piVar5 + 1;
        }
      }
      goto joined_r0x004dfed5;
    }
    iVar1 = *piVar5;
    if (iVar1 <= *piVar3) {
      if (iVar1 < *piVar3) goto joined_r0x004dfefb;
      iVar2 = *piVar6;
      *piVar6 = iVar1;
      *piVar5 = iVar2;
      piVar6 = piVar6 + 1;
    }
    piVar5 = piVar5 + 1;
  } while( true );
}

