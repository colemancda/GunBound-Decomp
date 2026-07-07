/* FUN_004f47e0 - 0x004f47e0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004f47e0(int *param_1)

{
  (**(code **)(*param_1 + 8))();
  (**(code **)(*param_1 + 4))();
  (**(code **)(*param_1 + 0xc))();
  __endthread();
  param_1[1] = 0;
  return;
}

