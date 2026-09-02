/* ScrollListWidget_DrawThumb - 0x0050e090 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-ARG FIX (2026-09-02, render-chain sweep): recovered the
 * register args at all 3 argless FindSpriteFrame() calls and their
 * sibling blits.  Every site loads EAX=&g_spriteRegistry and
 * EDX = *(this+0x54) (the widget's own sprite-set key - the one
 * non-immediate outerKey in this sweep, reloaded from [edi+0x54]
 * before each call); ESI/frame is 0 / 1 / 2 (thumb top cap / body
 * segment / bottom cap) at 0x50e0ec / 0x50e159 / 0x50e1bb.  The blits
 * share frame/key, x = *(this+0x28) and the running y the C already
 * carried (B16 0x50e0ff/0x50e16c/0x50e1ce, CLP 0x50e10f/0x50e17c/
 * 0x50e1ea).
 */
#include "ghidra_types.h"


void __fastcall ScrollListWidget_DrawThumb(int param_1)

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
    if ((g_screenSurface != 0) &&
       (iVar3 = FindSpriteFrame((int)&g_spriteRegistry,*(int *)(param_1 + 0x54),0), iVar3 != 0)) {
      if (*(char *)(iVar3 + 0x18) == '\x01') {
        BlitSprite16bpp(0,uVar1,iVar4,*(int *)(param_1 + 0x54));
      }
      else {
        BlitSpriteClipped(0,uVar1,iVar4,*(int *)(param_1 + 0x54));
      }
    }
    iVar2 = (iVar2 + -10) / 5;
    iVar3 = 0;
    iVar5 = iVar4;
    local_c = iVar2;
    if (0 < iVar2) {
      do {
        uVar1 = *(undefined4 *)(param_1 + 0x28);
        if ((g_screenSurface != 0) &&
           (iVar3 = FindSpriteFrame((int)&g_spriteRegistry,*(int *)(param_1 + 0x54),1), iVar3 != 0)) {
          if (*(char *)(iVar3 + 0x18) == '\x01') {
            BlitSprite16bpp(1,uVar1,iVar5 + 5,*(int *)(param_1 + 0x54));
          }
          else {
            BlitSpriteClipped(1,uVar1,iVar5 + 5,*(int *)(param_1 + 0x54));
          }
        }
        local_c = local_c + -1;
        iVar3 = iVar2;
        iVar5 = iVar5 + 5;
      } while (local_c != 0);
    }
    uVar1 = *(undefined4 *)(param_1 + 0x28);
    if ((g_screenSurface != 0) &&
       (iVar2 = FindSpriteFrame((int)&g_spriteRegistry,*(int *)(param_1 + 0x54),2), iVar2 != 0)) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        BlitSprite16bpp(2,uVar1,iVar4 + (iVar3 + 1) * 5,*(int *)(param_1 + 0x54));
        Widget_DrawChildrenDeep();
        return;
      }
      BlitSpriteClipped(2,uVar1,iVar4 + (iVar3 + 1) * 5,*(int *)(param_1 + 0x54));
    }
    Widget_DrawChildrenDeep();
    return;
  }
  Widget_DrawChildrenDeep();
  return;
}

