/* FUN_00500e30 - 0x00500e30 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x00500e4e) */

uint FUN_00500e30(void)

{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  
  uVar2 = FloatToInt64();
  iVar3 = 0;
  if (0x11 < uVar2) {
    do {
      puVar1 = &DAT_00557854 + iVar3;
      iVar3 = iVar3 + 1;
    } while (*puVar1 < uVar2);
  }
  if ((&DAT_00557850)[iVar3] != 0xffffffff) {
    uVar2 = (&DAT_00557850)[iVar3];
  }
  return uVar2;
}

