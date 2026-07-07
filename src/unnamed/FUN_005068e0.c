/* FUN_005068e0 - 0x005068e0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_005068e0(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (*(char *)(param_1 + 0x1e) == '\0') {
    FUN_005054b0();
    iVar1 = *(int *)(param_1 + 0x2c);
    iVar2 = *(int *)(param_1 + 0x28);
    iVar3 = *(int *)(param_1 + 0x90);
    if (((DAT_0079352c != 0) && (-1 < iVar3)) && (iVar4 = FUN_004f30c0(), iVar4 != 0)) {
      if (*(char *)(iVar4 + 0x18) == '\x01') {
        BlitSprite16bpp(iVar2 + 0x7c,iVar1 + 0x5c);
        return;
      }
      BlitSpriteClipped(iVar3);
    }
  }
  return;
}

