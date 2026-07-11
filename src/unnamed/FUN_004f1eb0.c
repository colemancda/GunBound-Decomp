/* FUN_004f1eb0 - 0x004f1eb0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004f1eb0(void)

{
  uint uVar1;
  
  uVar1 = 0;
  do {
    DAT_006990c0[uVar1] = (uint)SQRT((float)((uVar1 | 0x3f8000) << 8)) & 0x7fffff;
    DAT_006790c0[uVar1] = (uint)SQRT((float)((uVar1 | 0x400000) << 8)) & 0x7fffff;
    uVar1 = uVar1 + 1;
  } while (uVar1 < 0x8000);
  return;
}

