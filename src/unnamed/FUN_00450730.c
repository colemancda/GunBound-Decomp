/* FUN_00450730 - 0x00450730 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_00450730(void)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  int in_EAX;
  int iVar4;
  
  if (((*(char *)(in_EAX + 0x20) != '\0') &&
      (piVar2 = *(int **)(in_EAX + 0x1c), piVar2 != (int *)0x0)) &&
     (iVar3 = *(int *)(in_EAX + 0x24), -1 < iVar3)) {
    if (*piVar2 == 0) {
      *(undefined4 *)(in_EAX + 0x2c) = 0;
      *(undefined4 *)(in_EAX + 0x28) = 0;
      *(undefined4 *)(in_EAX + 0x30) = 0;
      *(undefined1 *)(in_EAX + 0x34) = 1;
      return;
    }
    iVar4 = *(int *)(in_EAX + 0x28) + 1;
    *(int *)(in_EAX + 0x28) = iVar4;
    if (*(int *)(*(int *)(piVar2[5] + iVar3 * 4) + *(int *)(in_EAX + 0x2c) * 4) <= iVar4) {
      *(undefined4 *)(in_EAX + 0x28) = 0;
      *(int *)(in_EAX + 0x2c) = *(int *)(in_EAX + 0x2c) + 1;
    }
    iVar4 = *(int *)(piVar2[3] + iVar3 * 4);
    if (iVar4 <= *(int *)(in_EAX + 0x2c)) {
      cVar1 = *(char *)(iVar3 + piVar2[2]);
      *(undefined4 *)(in_EAX + 0x28) = 0;
      if (cVar1 != '\0') {
        *(undefined4 *)(in_EAX + 0x2c) = 0;
        *(undefined4 *)(in_EAX + 0x30) = **(undefined4 **)(piVar2[4] + iVar3 * 4);
        return;
      }
      *(int *)(in_EAX + 0x2c) = iVar4 + -1;
      *(undefined1 *)(in_EAX + 0x34) = 1;
    }
    *(undefined4 *)(in_EAX + 0x30) =
         *(undefined4 *)(*(int *)(piVar2[4] + iVar3 * 4) + *(int *)(in_EAX + 0x2c) * 4);
  }
  return;
}

