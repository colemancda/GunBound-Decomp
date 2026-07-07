/* FUN_0041c190 - 0x0041c190 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


uint __fastcall FUN_0041c190(undefined4 param_1,int param_2)

{
  uint uVar1;
  int unaff_ESI;
  bool bVar2;
  
  uVar1 = 0;
  bVar2 = true;
  while( true ) {
    if (!bVar2) {
                    /* WARNING: Subroutine does not return */
      FUN_00426460();
    }
    if ((((&DAT_00e55e20)[uVar1 >> 5] & 1 << ((byte)uVar1 & 0x1f)) != 0) &&
       ((&DAT_006a7670)[unaff_ESI + param_2 * 8 + uVar1] == '\0')) break;
    uVar1 = uVar1 + 1;
    bVar2 = uVar1 < 8;
    if (7 < (int)uVar1) {
      return CONCAT31((int3)(uVar1 >> 8),1);
    }
  }
  return uVar1 & 0xffffff00;
}

