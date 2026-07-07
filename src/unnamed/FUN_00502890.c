/* FUN_00502890 - 0x00502890 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00502890(undefined4 param_1)

{
  int iVar1;
  int unaff_ESI;
  
  iVar1 = *(int *)(unaff_ESI + 4);
  if ((iVar1 != 0) &&
     ((uint)(*(int *)(unaff_ESI + 8) - iVar1 >> 3) < (uint)(*(int *)(unaff_ESI + 0xc) - iVar1 >> 3))
     ) {
    iVar1 = *(int *)(unaff_ESI + 8);
    FUN_00504190(iVar1,param_1);
    *(int *)(unaff_ESI + 8) = iVar1 + 8;
    return;
  }
  FUN_00503130(unaff_ESI,*(undefined4 *)(unaff_ESI + 8),1);
  return;
}

