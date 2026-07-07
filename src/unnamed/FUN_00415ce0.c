/* FUN_00415ce0 - 0x00415ce0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00415ce0(int param_1)

{
  int iVar1;
  int iVar2;
  int unaff_EBX;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  iVar2 = *(int *)(unaff_EBX + 0x20) + -1;
  iVar1 = 0;
  do {
    if (*(int *)(unaff_EBX + iVar1 * 4) == param_1) goto LAB_00415cfe;
    iVar1 = iVar1 + 1;
  } while (iVar1 < 8);
  iVar1 = -1;
LAB_00415cfe:
  if ((iVar1 != iVar2) && (iVar1 != -1)) {
    if (iVar1 < iVar2) {
      puVar3 = (undefined4 *)(unaff_EBX + iVar1 * 4);
      puVar4 = puVar3;
      for (iVar1 = iVar2 - iVar1; puVar3 = puVar3 + 1, iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar4 = *puVar3;
        puVar4 = puVar4 + 1;
      }
      *(int *)(unaff_EBX + iVar2 * 4) = param_1;
      return;
    }
    for (; iVar2 < iVar1; iVar1 = iVar1 + -1) {
      *(undefined4 *)(unaff_EBX + iVar1 * 4) = *(undefined4 *)(unaff_EBX + -4 + iVar1 * 4);
    }
    *(int *)(unaff_EBX + iVar2 * 4) = param_1;
  }
  return;
}

