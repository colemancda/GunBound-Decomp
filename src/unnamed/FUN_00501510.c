/* FUN_00501510 - 0x00501510 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00501510(void)

{
  undefined4 *puVar1;
  int iVar2;
  int unaff_ESI;
  
  if (*(int *)(unaff_ESI + 0x10) == 0) {
    puVar1 = _malloc(*(int *)(unaff_ESI + 0x14) * 0x38 + 4);
    if (puVar1 == (undefined4 *)0x0) {
                    /* WARNING: Subroutine does not return */
      FUN_004010c0(0x8007000e);
    }
    *puVar1 = *(undefined4 *)(unaff_ESI + 0xc);
    *(undefined4 **)(unaff_ESI + 0xc) = puVar1;
    iVar2 = *(int *)(unaff_ESI + 0x14);
    puVar1 = puVar1 + iVar2 * 0xe + -0xd;
    if (-1 < iVar2 + -1) {
      do {
        *puVar1 = *(undefined4 *)(unaff_ESI + 0x10);
        *(undefined4 **)(unaff_ESI + 0x10) = puVar1;
        puVar1 = puVar1 + -0xe;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
  }
  return;
}

