/* FUN_00507ea0 - 0x00507ea0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


char FUN_00507ea0(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  
  cVar1 = FUN_0050f060(param_1,param_2);
  if (cVar1 == '\0') {
    FUN_00507e30();
  }
  return cVar1;
}

