/* FUN_004507d0 - 0x004507d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004507d0(void)

{
  char cVar1;
  int *piVar2;
  int unaff_EBX;
  int iVar3;
  
  iVar3 = *(int *)(*(int *)(unaff_EBX + 4) + 0x1c);
  if (iVar3 != *(int *)(unaff_EBX + 4)) {
    do {
      piVar2 = *(int **)(iVar3 + 0x10);
      cVar1 = *(char *)((int)piVar2 + 0x15);
      while (cVar1 == '\0') {
        (**(code **)(*piVar2 + 8))();
        piVar2 = (int *)piVar2[4];
        cVar1 = *(char *)((int)piVar2 + 0x15);
      }
      iVar3 = *(int *)(iVar3 + 0x1c);
    } while (iVar3 != *(int *)(unaff_EBX + 4));
  }
  return;
}

