/* FUN_004f3ea0 - 0x004f3ea0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004f3ea0(void)

{
  *(undefined4 *)(DAT_00792190 + 0x7c) = 0;
  DAT_00793660 = 1;
  if (DAT_00793611 != '\0') {
    (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x1b,0);
  }
  DAT_00793611 = 0;
  return;
}

