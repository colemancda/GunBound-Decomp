/* FUN_0043c820 - 0x0043c820 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint FUN_0043c820(void)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *(uint *)(*(int *)(&DAT_006a7f8c + DAT_005b3484) + 0x1c);
  uVar2 = *(uint *)(uVar1 + 4);
  while( true ) {
    if (0x186a2 < uVar2) {
      return uVar1 & 0xffffff00;
    }
    if (uVar2 == 0x186a2) break;
    uVar1 = *(uint *)(uVar1 + 0x1c);
    uVar2 = *(uint *)(uVar1 + 4);
  }
  return CONCAT31((int3)(uVar1 >> 8),*(uint *)(uVar1 + 0x10) != uVar1);
}

