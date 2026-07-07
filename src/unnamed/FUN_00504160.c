/* FUN_00504160 - 0x00504160 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00504160(int param_1)

{
  int in_EAX;
  
  for (; in_EAX != 0; in_EAX = in_EAX + -1) {
    if (param_1 != 0) {
      FUN_00503680();
    }
    param_1 = param_1 + 0x34;
  }
  return;
}

