/* FUN_00426430 - 0x00426430 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __fastcall FUN_00426430(int *param_1)

{
  uint uVar1;
  
  uVar1 = param_1[1];
  if (7 < uVar1) {
                    /* WARNING: Subroutine does not return */
    FUN_00426460();
  }
  return CONCAT31((uint3)(uVar1 >> 0xd),
                  (*(uint *)(*param_1 + (uVar1 >> 5) * 4) & 1 << ((byte)uVar1 & 0x1f)) != 0);
}

