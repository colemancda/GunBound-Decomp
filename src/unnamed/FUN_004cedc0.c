/* FUN_004cedc0 - 0x004cedc0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


bool FUN_004cedc0(void)

{
  int iVar1;
  uint uVar2;
  char cVar3;
  int *piVar4;
  uint uVar5;
  
  uVar5 = 0;
  do {
    iVar1 = *(int *)(*(int *)(&DAT_006a7f8c + DAT_005b3484) + 0x1c);
    uVar2 = *(uint *)(iVar1 + 4);
    while (uVar2 < 0x186a4) {
      if (uVar2 == 0x186a3) {
        piVar4 = *(int **)(iVar1 + 0x10);
        uVar2 = piVar4[2];
        if (uVar2 <= uVar5) goto LAB_004cee05;
        break;
      }
      iVar1 = *(int *)(iVar1 + 0x1c);
      uVar2 = *(uint *)(iVar1 + 4);
    }
LAB_004cee1e:
    uVar5 = uVar5 + 1;
    if (0x3f < (int)uVar5) {
LAB_004cee24:
      return uVar5 != 0x40;
    }
  } while( true );
  while( true ) {
    piVar4 = (int *)piVar4[4];
    uVar2 = piVar4[2];
    if (uVar5 < uVar2) break;
LAB_004cee05:
    if (uVar2 == uVar5) {
      cVar3 = (**(code **)(*piVar4 + 0x24))(0xffffffff);
      if (cVar3 != '\0') goto LAB_004cee24;
      break;
    }
  }
  goto LAB_004cee1e;
}

