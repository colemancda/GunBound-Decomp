/* FUN_00502a90 - 0x00502a90 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00502a90(void)

{
  int iVar1;
  int unaff_EBX;
  int iVar2;
  
  iVar2 = *(int *)(unaff_EBX + 4);
  if (iVar2 != 0) {
    iVar1 = *(int *)(unaff_EBX + 8);
    for (; iVar2 != iVar1; iVar2 = iVar2 + 8) {
      FUN_00415890();
    }
    _free(*(void **)(unaff_EBX + 4));
  }
  *(undefined4 *)(unaff_EBX + 4) = 0;
  *(undefined4 *)(unaff_EBX + 8) = 0;
  *(undefined4 *)(unaff_EBX + 0xc) = 0;
  return;
}

