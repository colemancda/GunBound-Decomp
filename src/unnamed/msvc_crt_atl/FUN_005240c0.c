/* FUN_005240c0 - 0x005240c0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_005240c0(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  
  if (((DAT_005b1638 == param_1) && (DAT_005b163c == param_2)) && (DAT_005b1640 == param_3)) {
    DAT_005b1644 = DAT_005b1644 + 1;
    if (2 < DAT_005b1644) {
      return 1;
    }
  }
  else {
    DAT_005b1644 = 0;
  }
  DAT_005b1638 = param_1;
  DAT_005b163c = param_2;
  DAT_005b1640 = param_3;
  uVar1 = FUN_00523fc0(param_1,param_2,param_3);
  return uVar1;
}

