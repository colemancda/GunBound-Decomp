/* FUN_004fedd0 - 0x004fedd0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint FUN_004fedd0(void)

{
  uint uVar1;
  char cVar2;
  int *in_EAX;
  
  uVar1 = in_EAX[1];
  if ((uint)in_EAX[2] <= uVar1) {
    cVar2 = FUN_005001f0();
    if (cVar2 == '\0') {
                    /* WARNING: Subroutine does not return */
      FUN_004010c0(0x8007000e);
    }
  }
  if (uVar1 * 0x1750 + *in_EAX != 0) {
    FUN_004ff2c0();
  }
  in_EAX[1] = in_EAX[1] + 1;
  return uVar1;
}

