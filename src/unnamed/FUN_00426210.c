/* FUN_00426210 - 0x00426210 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_00426210(void)

{
  int iVar1;
  
  iVar1 = DAT_005b3484;
  *(undefined4 *)(&DAT_006aa662 + DAT_005b3484) = 0xffffffff;
  *(undefined4 *)(&DAT_006aa666 + iVar1) = 0xffffffff;
  *(undefined4 *)(&DAT_006aa66a + iVar1) = 0xffffffff;
  *(undefined4 *)(&DAT_006aa66e + iVar1) = 0xffffffff;
  return;
}

