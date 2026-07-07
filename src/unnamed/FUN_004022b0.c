/* FUN_004022b0 - 0x004022b0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004022b0(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int unaff_ESI;
  
  iVar4 = 0;
  for (iVar2 = *(int *)(*(int *)(unaff_ESI + 4) + 0x1c); iVar2 != *(int *)(unaff_ESI + 4);
      iVar2 = *(int *)(iVar2 + 0x1c)) {
    iVar3 = *(int *)(iVar2 + 0x10);
    cVar1 = *(char *)(iVar3 + 0x15);
    while (cVar1 == '\0') {
      if (*(char *)(iVar3 + 0x30) != '\0') {
        iVar4 = iVar4 + 1;
      }
      iVar3 = *(int *)(iVar3 + 0x10);
      cVar1 = *(char *)(iVar3 + 0x15);
    }
  }
  *(int *)(unaff_ESI + 0xf24) = iVar4;
  return;
}

