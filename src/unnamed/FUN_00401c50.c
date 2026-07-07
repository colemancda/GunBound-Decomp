/* FUN_00401c50 - 0x00401c50 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_00401c50(int param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = *(int *)(*(int *)(param_1 + 4) + 0x1c);
  iVar4 = 0;
  if (iVar5 != *(int *)(param_1 + 4)) {
    do {
      iVar2 = *(int *)(iVar5 + 0x10);
      cVar1 = *(char *)(iVar2 + 0x15);
      while (cVar1 == '\0') {
        iVar3 = __stricmp((char *)(iVar2 + 0x21),param_2);
        if (iVar3 == 0) {
          return iVar4;
        }
        iVar2 = *(int *)(iVar2 + 0x10);
        iVar4 = iVar4 + 1;
        cVar1 = *(char *)(iVar2 + 0x15);
      }
      iVar5 = *(int *)(iVar5 + 0x1c);
    } while (iVar5 != *(int *)(param_1 + 4));
  }
  return -1;
}

