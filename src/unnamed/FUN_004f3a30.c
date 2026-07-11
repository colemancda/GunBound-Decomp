/* FUN_004f3a30 - 0x004f3a30 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004f3a30(void)

{
  int iVar1;

  /* Free every block in the 0x400-entry table; the original's hardcoded end
   * address 0x6ba100 (= &DAT_006b9100 + 0x1000 in the original image) no longer
   * matches the relocated table, so iterate by element count. */
  for (iVar1 = 0; iVar1 < 0x400; iVar1 = iVar1 + 1) {
    if ((void *)DAT_006b9100[iVar1] != (void *)0x0) {
      _free((void *)DAT_006b9100[iVar1]);
    }
    DAT_006b9100[iVar1] = 0;
  }
  return;
}

