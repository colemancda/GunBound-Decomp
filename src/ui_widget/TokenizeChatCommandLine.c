/* FUN_00421820 - 0x00421820 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_00421820(char *param_1)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  
  cVar4 = '\0';
  iVar6 = 0;
  iVar2 = 1;
  pcVar3 = param_1;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  iVar5 = 1;
  if (1 < (int)pcVar3 - (int)(param_1 + 1)) {
    do {
      if (param_1[iVar5] == ' ') {
        param_1[iVar6] = cVar4;
        cVar4 = '\0';
        iVar2 = iVar2 + 1;
        iVar6 = iVar5;
      }
      else {
        cVar4 = cVar4 + '\x01';
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < (int)pcVar3 - (int)(param_1 + 1));
  }
  param_1[iVar6] = cVar4;
  return iVar2;
}

