/* FUN_005045a0 - 0x005045a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __fastcall FUN_005045a0(int param_1)

{
  int in_EAX;
  int unaff_EBX;
  
  for (; param_1 != unaff_EBX; param_1 = param_1 + 0x34) {
    if (in_EAX != 0) {
      FUN_00503680();
    }
    in_EAX = in_EAX + 0x34;
  }
  return in_EAX;
}

