/* FUN_00401bb0 - 0x00401bb0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_00401bb0(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  char *unaff_EBX;
  int iVar4;
  
  iVar4 = *(int *)(*(int *)(param_1 + 4) + 0x1c);
  if (iVar4 != *(int *)(param_1 + 4)) {
    do {
      iVar2 = *(int *)(iVar4 + 0x10);
      cVar1 = *(char *)(iVar2 + 0x15);
      while (cVar1 == '\0') {
        iVar3 = __stricmp((char *)(iVar2 + 0x21),unaff_EBX);
        if (iVar3 == 0) {
          return iVar2;
        }
        iVar2 = *(int *)(iVar2 + 0x10);
        cVar1 = *(char *)(iVar2 + 0x15);
      }
      iVar4 = *(int *)(iVar4 + 0x1c);
    } while (iVar4 != *(int *)(param_1 + 4));
  }
  return 0;
}

