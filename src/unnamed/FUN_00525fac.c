/* FUN_00525fac - 0x00525fac in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00525fac(char *param_1,char *param_2)

{
  __fsopen(param_1,param_2,0x40);
  return;
}

