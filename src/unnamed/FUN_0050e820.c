/* FUN_0050e820 - 0x0050e820 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0050e820(void)

{
  int unaff_EBX;
  uint uVar1;
  int unaff_EDI;
  
  uVar1 = 0;
  if (*(int *)(unaff_EDI + 0x10) != 0) {
    if (*(int *)(unaff_EDI + 0x10) == 0) {
LAB_0050e851:
                    /* WARNING: Subroutine does not return */
      FUN_004010c0(0x80070057);
    }
    do {
      if (*(int *)(*(int *)(unaff_EDI + 0xc) + uVar1 * 4) != unaff_EBX) {
        if (*(uint *)(unaff_EDI + 0x10) <= uVar1) goto LAB_0050e851;
        (**(code **)**(undefined4 **)(*(int *)(unaff_EDI + 0xc) + uVar1 * 4))(0);
      }
      uVar1 = uVar1 + 1;
    } while (uVar1 < *(uint *)(unaff_EDI + 0x10));
  }
  return;
}

