/* FUN_0040ce50 - 0x0040ce50 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


undefined4 FUN_0040ce50(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_0040cea0();
  if (iVar1 == 0) {
    return 0;
  }
  if (*(int *)(iVar1 + 0x448) != 1) {
    if (*(int *)(param_1 + 8) != 0) {
      FUN_0040ccf0();
    }
    *(int *)(param_1 + 8) = iVar1;
    FUN_0040cc50();
  }
  return 1;
}

