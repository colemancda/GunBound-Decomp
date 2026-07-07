/* FUN_004dffb0 - 0x004dffb0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004dffb0(int param_1)

{
  int in_EAX;
  int iVar1;
  
  iVar1 = in_EAX - param_1 >> 2;
  if (1 < iVar1) {
    iVar1 = iVar1 - (in_EAX - param_1 >> 0x1f) >> 1;
    while (0 < iVar1) {
      iVar1 = iVar1 + -1;
      FUN_004e01b0(iVar1);
    }
  }
  return;
}

