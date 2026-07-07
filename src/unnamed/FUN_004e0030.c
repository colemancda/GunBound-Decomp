/* FUN_004e0030 - 0x004e0030 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e0030(int *param_1)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  int *unaff_EDI;
  
  if ((unaff_EDI != param_1) && (piVar5 = unaff_EDI + 1, piVar5 != param_1)) {
    piVar4 = unaff_EDI + 2;
    do {
      iVar1 = *piVar5;
      piVar2 = unaff_EDI;
      if (iVar1 < *unaff_EDI) {
joined_r0x004e006b:
        if ((piVar2 != piVar5) && (piVar5 != piVar4)) {
          FUN_004e0210();
        }
      }
      else {
        piVar3 = piVar4 + -2;
        if (iVar1 < piVar4[-2]) {
          do {
            piVar2 = piVar3;
            piVar3 = piVar2 + -1;
          } while (iVar1 < *piVar3);
          goto joined_r0x004e006b;
        }
      }
      piVar5 = piVar5 + 1;
      piVar4 = piVar4 + 1;
    } while (piVar5 != param_1);
  }
  return;
}

