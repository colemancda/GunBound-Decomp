/* FUN_004f3a00 - 0x004f3a00 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004f3a00(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_006b9100;
  for (iVar1 = 0x400; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  _DAT_006b90f8 = FUN_004f3980();
  *(undefined4 *)(_DAT_006b90f8 + 8) = 0;
  return;
}

