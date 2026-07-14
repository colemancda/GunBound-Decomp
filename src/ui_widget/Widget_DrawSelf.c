/* Widget_DrawSelf - 0x005054b0 in the original binary.
 *
 * The base widget/panel draw method - draws this widget's own
 * background sprite (if any), then recurses into its children. Every
 * CWidget/CPanel subclass (buttons, labels, panels like CWorldListPanel)
 * goes through this.
 *
 * Confirmed via objdump at the real entry (0x5054b0):
 *   mov edx,[edi+0x44]   ; outerKey = this->m_unk44 (the sprite-set key,
 *                         ; e.g. CWorldListPanel's 0x2711 "server_list.img")
 *   mov ebx,[edi+0x2c]   ; y
 *   mov ebp,[edi+0x28]   ; x
 *   mov esi,[edi+0x48]   ; frame/innerKey = this->m_unk48
 *   ...
 *   mov eax,0xea0e18     ; container = &DAT_00ea0e18
 *   call 0x4f30c0        ; FindSpriteFrame(container,outerKey,frame)
 *   ; success (byte[+0x18]==1): push ebx; push ebp; mov eax,esi;
 *   ;   call 0x4ed6a0 -> BlitSprite16bpp(frame=esi,x=ebp,y=ebx)
 *   ; else: push esi; mov eax,ebx; mov ecx,ebp;
 *   ;   call 0x4eb9c0 -> BlitSpriteClipped(frame=esi,x=ebp,y=ebx)
 * Two dropped-argument bugs fixed: FindSpriteFrame() was zero-arg (the
 * same project-wide stub - see FindSpriteFrame.c's header), and
 * BlitSprite16bpp(uVar2,uVar1) was passing x/y into the (frame,x) slots
 * of its real (frame,x,y) signature with frame missing entirely -
 * BlitSpriteClipped(iVar3) similarly dropped its x/y. Being the shared
 * base-class draw method, this was the actual reason every panel's own
 * background image (e.g. CWorldListPanel's "server_list.img") rendered
 * as a solid black rectangle instead of its real art.
 *
 * Also fixed both Widget_DrawChildrenDeep() calls, previously zero-arg
 * despite that function's own real (already-declared) `int param_1`
 * signature - the tail call at the very end of this function in the
 * original (`mov ecx,edi; jmp 0x50ecf0`) passes `this` through explicitly.
 */
#include "ghidra_types.h"


void __fastcall Widget_DrawSelf(int param_1)

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
    iVar4 = FindSpriteFrame((int)&DAT_00ea0e18,*(int *)(param_1 + 0x44),iVar3);
    if (iVar4 != 0) {
      if (*(char *)(iVar4 + 0x18) == '\x01') {
        BlitSprite16bpp(iVar3,uVar2,uVar1,*(int *)(param_1 + 0x44));
        Widget_DrawChildrenDeep(param_1);
        return;
      }
      BlitSpriteClipped(iVar3,uVar2,uVar1,*(int *)(param_1 + 0x44));
    }
  }
  Widget_DrawChildrenDeep(param_1);
  return;
}

