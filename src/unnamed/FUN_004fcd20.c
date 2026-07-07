/* FUN_004fcd20 - 0x004fcd20 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_004fcd20(int param_1,undefined4 param_2)

{
  int in_EAX;
  
  if (0 < in_EAX) {
    do {
      FUN_004f4d10(param_1,param_2);
      param_1 = param_1 + 0x10;
      in_EAX = in_EAX + -1;
    } while (in_EAX != 0);
  }
  return;
}

