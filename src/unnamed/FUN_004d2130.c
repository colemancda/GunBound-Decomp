/* FUN_004d2130 - 0x004d2130 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint FUN_004d2130(undefined4 param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  char cVar3;
  int *in_EAX;
  
  uVar2 = in_EAX[1];
  if ((uint)in_EAX[2] <= uVar2) {
    cVar3 = AtlArray_GrowBuffer();
    if (cVar3 == '\0') {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x8007000e);
    }
  }
  puVar1 = (undefined4 *)(*in_EAX + uVar2 * 4);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = param_1;
  }
  in_EAX[1] = in_EAX[1] + 1;
  return uVar2;
}

