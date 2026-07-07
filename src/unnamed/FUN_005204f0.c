/* FUN_005204f0 - 0x005204f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


uint FUN_005204f0(undefined4 param_1)

{
  uint in_EAX;
  uint uVar1;
  
  if (DAT_005b15ac == 0) {
    return in_EAX & 0xffffff00;
  }
  uVar1 = FUN_00521d70(param_1);
  return uVar1;
}

