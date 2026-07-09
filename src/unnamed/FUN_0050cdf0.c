/* FUN_0050cdf0 - 0x0050cdf0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0050cdf0(int param_1)

{
  uint uVar1;
  undefined1 uVar2;
  char unaff_BL;
  int iVar3;
  
  iVar3 = 0;
  do {
    uVar1 = Widget_FindChildIndex();
    if (uVar1 != 0xffffffff) {
      if (((*(char *)(param_1 + 0x91) == '\0') && (unaff_BL != '\0')) && (iVar3 != 1)) {
        uVar2 = 1;
      }
      else {
        uVar2 = 0;
      }
      if (*(uint *)(param_1 + 0x10) <= uVar1) {
                    /* WARNING: Subroutine does not return */
        FUN_004010c0(0x80070057);
      }
      FUN_0050e7d0(uVar2);
    }
    iVar3 = iVar3 + 1;
    if (3 < iVar3) {
      return;
    }
  } while( true );
}

