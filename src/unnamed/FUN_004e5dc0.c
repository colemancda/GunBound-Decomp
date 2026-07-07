/* FUN_004e5dc0 - 0x004e5dc0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e5dc0(uint param_1,uint param_2)

{
  uint *in_EAX;
  uint uVar1;
  
  uVar1 = *in_EAX + 1 & 0x800001ff;
  if ((int)uVar1 < 0) {
    uVar1 = (uVar1 - 1 | 0xfffffe00) + 1;
  }
  if (uVar1 != in_EAX[1]) {
    in_EAX[*in_EAX + 2] = param_1;
    in_EAX[*in_EAX + 0x202] = param_2;
    *in_EAX = uVar1;
  }
  return;
}

