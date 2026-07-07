/* FUN_00422f10 - 0x00422f10 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void __thiscall FUN_00422f10(undefined4 param_1,undefined4 param_2)

{
  DWORD DVar1;
  int unaff_ESI;
  
  if (*(int *)(&DAT_005f3258 + unaff_ESI) < 0x40) {
    *(undefined4 *)(&DAT_005f2f58 + *(int *)(&DAT_005f3258 + unaff_ESI) * 4 + unaff_ESI) = param_1;
    *(undefined4 *)(&DAT_005f3058 + *(int *)(&DAT_005f3258 + unaff_ESI) * 4 + unaff_ESI) = param_2;
    DVar1 = GetTickCount();
    *(uint *)(&DAT_005f3158 + *(int *)(&DAT_005f3258 + unaff_ESI) * 4 + unaff_ESI) =
         DVar1 / 1000 + 300;
    *(int *)(&DAT_005f3258 + unaff_ESI) = *(int *)(&DAT_005f3258 + unaff_ESI) + 1;
  }
  return;
}

