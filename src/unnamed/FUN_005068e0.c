/* FUN_005068e0 - 0x005068e0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * 2026-09-02: FindSpriteFrame/BlitSprite16bpp/BlitSpriteClipped register
 * args recovered from orig 0x506910-0x50693e - see the site comment.
 */
#include "ghidra_types.h"


void __fastcall FUN_005068e0(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (*(char *)(param_1 + 0x1e) == '\0') {
    Widget_DrawSelf(param_1);
    iVar1 = *(int *)(param_1 + 0x2c);
    iVar2 = *(int *)(param_1 + 0x28);
    iVar3 = *(int *)(param_1 + 0x90);
    /* RECOVERED (2026-09-02), orig 0x506910-0x50693e.
     * FindSpriteFrame @0x50691a: EAX = 0xea0e18 (&g_spriteRegistry),
     * EDX = 0x2713 (outer key, immediate @0x506910), ESI =
     * *(param_1+0x90) = iVar3 (frame, loaded @0x5068fc; the same value
     * guarded by `-1 < iVar3`).  Cached scan: tools/
     * findspriteframe_sites.json call_addr 0x50691a.
     * BlitSprite16bpp @0x50692d: EAX=esi=iVar3 (frame), push ebx =
     * iVar2+0x7c (x, @0x506905), push edi = iVar1+0x5c (y, @0x506902),
     * EDX=0x2713 inherited live through FindSpriteFrame.
     * BlitSpriteClipped @0x50693e: push esi=iVar3 (frame), ECX=ebx=
     * iVar2+0x7c (x), EAX=edi=iVar1+0x5c (y), EDX=0x2713. */
    if (((g_screenSurface != 0) && (-1 < iVar3)) &&
       (iVar4 = FindSpriteFrame((int)&g_spriteRegistry,0x2713,iVar3), iVar4 != 0)) {
      if (*(char *)(iVar4 + 0x18) == '\x01') {
        BlitSprite16bpp(iVar3,iVar2 + 0x7c,iVar1 + 0x5c,0x2713);
        return;
      }
      BlitSpriteClipped(iVar3,iVar2 + 0x7c,iVar1 + 0x5c,0x2713);
    }
  }
  return;
}

