/* FUN_00426700 - 0x00426700 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00426700(int param_1)

{
  int in_EAX;
  
  for (; in_EAX != 0; in_EAX = in_EAX + -1) {
    FUN_00426810(param_1);
    param_1 = param_1 + 0x450;
  }
  return;
}

