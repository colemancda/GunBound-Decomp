/* FUN_005054b0 - 0x005054b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_005054b0(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  if (*(char *)(param_1 + 0x1e) != '\0') {
    return;
  }
  uVar1 = *(undefined4 *)(param_1 + 0x2c);
  uVar2 = *(undefined4 *)(param_1 + 0x28);
  iVar3 = *(int *)(param_1 + 0x48);
  if ((DAT_0079352c != 0) && (-1 < iVar3)) {
    iVar4 = FUN_004f30c0();
    if (iVar4 != 0) {
      if (*(char *)(iVar4 + 0x18) == '\x01') {
        BlitSprite16bpp(uVar2,uVar1);
        FUN_0050ecf0();
        return;
      }
      BlitSpriteClipped(iVar3);
    }
  }
  FUN_0050ecf0();
  return;
}

