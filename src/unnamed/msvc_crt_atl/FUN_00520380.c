/* FUN_00520380 - 0x00520380 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00520380(undefined4 param_1)

{
  undefined4 uVar1;
  
  if (DAT_005b15ac == 0) {
    return 0;
  }
  uVar1 = FUN_00520700(param_1);
  return uVar1;
}

