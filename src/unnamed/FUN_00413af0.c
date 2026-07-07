/* FUN_00413af0 - 0x00413af0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00413af0(void)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  char *unaff_EDI;
  undefined4 uVar6;
  char local_400 [1024];
  
  iVar3 = 0;
  iVar5 = 0;
  bVar2 = true;
  cVar1 = *unaff_EDI;
  while (cVar1 != '\0') {
    cVar1 = unaff_EDI[iVar5];
    if ((cVar1 == '\\') && (unaff_EDI[iVar5 + 1] == 'n')) {
      local_400[iVar3] = '\0';
      if (bVar2) {
        piVar4 = (int *)g_gameStateVTableArray[g_currentGameState];
        uVar6 = 6;
      }
      else {
        piVar4 = (int *)g_gameStateVTableArray[g_currentGameState];
        uVar6 = 0;
      }
      (**(code **)(*piVar4 + 0x28))(local_400,2,uVar6);
      iVar3 = 0;
      iVar5 = iVar5 + 2;
      bVar2 = false;
    }
    else if (cVar1 == '\n') {
      piVar4 = (int *)g_gameStateVTableArray[g_currentGameState];
      local_400[iVar3] = '\0';
      if (bVar2) {
        (**(code **)(*piVar4 + 0x28))(local_400,2,6);
        iVar3 = 0;
        iVar5 = iVar5 + 1;
        bVar2 = false;
      }
      else {
        (**(code **)(*piVar4 + 0x28))(local_400,2,0);
        iVar3 = 0;
        iVar5 = iVar5 + 1;
        bVar2 = false;
      }
    }
    else {
      local_400[iVar3] = cVar1;
      iVar3 = iVar3 + 1;
      iVar5 = iVar5 + 1;
    }
    cVar1 = unaff_EDI[iVar5];
  }
  piVar4 = (int *)g_gameStateVTableArray[g_currentGameState];
  local_400[iVar3] = '\0';
  if (bVar2) {
    (**(code **)(*piVar4 + 0x28))(local_400,2,6);
    return;
  }
  (**(code **)(*piVar4 + 0x28))(local_400,2,0);
  return;
}

