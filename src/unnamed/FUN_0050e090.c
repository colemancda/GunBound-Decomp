/* FUN_0050e090 - 0x0050e090 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0050e090(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int local_c;
  
  if (((*(char *)(param_1 + 0x1e) == '\0') && (iVar4 = *(int *)(param_1 + 0x38), 0 < iVar4)) &&
     (*(int *)(param_1 + 0x3c) <= iVar4)) {
    iVar2 = ScrollListWidget_ThumbHeight();
    uVar1 = *(undefined4 *)(param_1 + 0x28);
    iVar4 = *(int *)(param_1 + 0x2c) + (*(int *)(param_1 + 0x40) * *(int *)(param_1 + 0x34)) / iVar4
    ;
    if ((DAT_0079352c != 0) && (iVar3 = FindSpriteFrame(), iVar3 != 0)) {
      if (*(char *)(iVar3 + 0x18) == '\x01') {
        BlitSprite16bpp(uVar1,iVar4);
      }
      else {
        BlitSpriteClipped(0);
      }
    }
    iVar2 = (iVar2 + -10) / 5;
    iVar3 = 0;
    iVar5 = iVar4;
    local_c = iVar2;
    if (0 < iVar2) {
      do {
        uVar1 = *(undefined4 *)(param_1 + 0x28);
        if ((DAT_0079352c != 0) && (iVar3 = FindSpriteFrame(), iVar3 != 0)) {
          if (*(char *)(iVar3 + 0x18) == '\x01') {
            BlitSprite16bpp(uVar1,iVar5 + 5);
          }
          else {
            BlitSpriteClipped(1);
          }
        }
        local_c = local_c + -1;
        iVar3 = iVar2;
        iVar5 = iVar5 + 5;
      } while (local_c != 0);
    }
    uVar1 = *(undefined4 *)(param_1 + 0x28);
    if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame(), iVar2 != 0)) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        BlitSprite16bpp(uVar1,iVar4 + (iVar3 + 1) * 5);
        FUN_0050ecf0();
        return;
      }
      BlitSpriteClipped(2);
    }
    FUN_0050ecf0();
    return;
  }
  FUN_0050ecf0();
  return;
}

