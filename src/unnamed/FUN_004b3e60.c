/* FUN_004b3e60 - 0x004b3e60 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004b3e60(undefined2 *param_1)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x191) != '\0') {
    iVar3 = *(int *)(param_1 + 0x194);
    if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame(), iVar2 != 0)) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        BlitSprite16bpp(iVar3,0x17d);
      }
      else {
        BlitSpriteClipped(0);
      }
    }
    uVar1 = *param_1;
    if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame(), iVar2 != 0)) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        BlitSprite16bpp(iVar3 + 0x13,0x18c);
      }
      else {
        BlitSpriteClipped(uVar1);
      }
    }
    FUN_004eb510(0x18b,0x1f);
    BlitRLESprite(0x18b,0xffff);
    BlitRLESprite(0x199,0xffff);
    iVar2 = 0x1b0;
    iVar3 = 6;
    do {
      BlitRLESprite(iVar2,0xffff);
      iVar2 = iVar2 + 0xf;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  return;
}

