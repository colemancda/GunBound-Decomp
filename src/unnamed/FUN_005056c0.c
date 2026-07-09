/* FUN_005056c0 - 0x005056c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_005056c0(void)

{
  uint uVar1;
  int unaff_EBX;
  
  uVar1 = Widget_FindChildIndex();
  if (uVar1 != 0xffffffff) {
    if (*(uint *)(unaff_EBX + 0x10) <= uVar1) {
                    /* WARNING: Subroutine does not return */
      FUN_004010c0(0x80070057);
    }
    FUN_00506f60();
  }
  return;
}

