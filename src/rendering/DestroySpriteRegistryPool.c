/* DestroySpriteRegistryPool - 0x004f3a30 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004f3a30 mean this function.)
 *
 * NAMED (2026-11-05), HIGH. Evidence from outside the body: It frees and
 * zeroes every entry of the 0x400-entry block table DAT_006b9100, the
 * table InitSpriteRegistryPool (0x4f3a00) zeroes and
 * AllocSpriteRegistryNode fills. Sole caller is ShutdownDirectDraw
 * (0x4eff90), called back to back with DestroyTextureCachePool, the
 * teardown mirror of the Init pair.
 */
#include "ghidra_types.h"


void DestroySpriteRegistryPool(void)

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

