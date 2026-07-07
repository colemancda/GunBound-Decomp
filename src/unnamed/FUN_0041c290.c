/* FUN_0041c290 - 0x0041c290 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


int __fastcall FUN_0041c290(int param_1)

{
  int iVar1;
  uint *puVar2;
  uint unaff_ESI;
  
  iVar1 = 0;
  if (*(byte *)(param_1 + 0x44648) != 0) {
    puVar2 = (uint *)(param_1 + 0x44664);
    do {
      if (*puVar2 == (unaff_ESI & 0xffff)) {
        return iVar1;
      }
      iVar1 = iVar1 + 1;
      puVar2 = puVar2 + 1;
    } while (iVar1 < (int)(uint)*(byte *)(param_1 + 0x44648));
  }
  return -1;
}

