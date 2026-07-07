/* FUN_004ccbb0 - 0x004ccbb0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004ccbb0(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int iVar6;
  
  iVar3 = param_1;
  iVar6 = *(int *)(param_1 + 0x98);
  param_1 = 0;
  if (iVar6 != 1 && -1 < iVar6 + -1) {
    piVar5 = (int *)(iVar3 + 0x29c);
    do {
      if (param_1 < iVar6) {
        piVar1 = piVar5 + -0x80;
        piVar4 = piVar1;
        iVar6 = param_1;
        do {
          iVar2 = *piVar1;
          if (*piVar4 < iVar2) {
            *piVar1 = *piVar4;
            *piVar4 = iVar2;
            iVar2 = *piVar5;
            *piVar5 = piVar4[0x80];
            piVar4[0x80] = iVar2;
            iVar2 = piVar5[0x80];
            piVar5[0x80] = piVar4[0x100];
            piVar4[0x100] = iVar2;
            iVar2 = piVar5[0x100];
            piVar5[0x100] = piVar4[0x180];
            piVar4[0x180] = iVar2;
          }
          iVar6 = iVar6 + 1;
          piVar4 = piVar4 + 1;
        } while (iVar6 < *(int *)(iVar3 + 0x98));
      }
      iVar6 = *(int *)(iVar3 + 0x98);
      param_1 = param_1 + 1;
      piVar5 = piVar5 + 1;
    } while (param_1 < iVar6 + -1);
  }
  return;
}

