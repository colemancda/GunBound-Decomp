/* FUN_004f3e70 - 0x004f3e70 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004f3e70(void)

{
  int iVar1;

  /* Free every block in the 0x400-entry table. The original's loop bound was
   * the hardcoded end address 0x7931b0 (= &DAT_007921b0 + 0x1000 in the
   * original image); with the table relocated by the linker that constant is
   * meaningless, so iterate by element count instead. */
  for (iVar1 = 0; iVar1 < 0x400; iVar1 = iVar1 + 1) {
    if ((void *)DAT_007921b0[iVar1] != (void *)0x0) {
      _free((void *)DAT_007921b0[iVar1]);
    }
    DAT_007921b0[iVar1] = 0;
  }
  return;
}

