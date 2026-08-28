/* FUN_0041bce0 - 0x0041bce0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0041bce0(int param_1)

{
  char cVar1;
  byte bVar2;
  ushort uVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined4 local_14;
  int local_10;
  /* RECOVERED: the row's glyph x-cursor.  It lives in the frame slot
   * [esp+0x18], sitting inside Ghidra's own naming ladder for this frame
   * ([esp+0x10]=local_14, [esp+0x14]=local_10, [esp+0x1c]=local_8,
   * [esp+0x20]=local_4, all four confirmed by their initialisers at
   * 0x41bcf0/0x41bcf8/0x41bd17), yet Ghidra dropped it: its ONLY two
   * stores in the whole function are `mov [esp+0x18],0x24` at 0x41bd33
   * (row has no icon) and `mov [esp+0x18],0x32` at 0x41bd49 (row has an
   * icon), and it is reloaded as the this/x of every text call below.
   * Same drop, same role as FUN_005078f0.c's xCursor and
   * RenderReadyRoomChatRow.c's iVar11. */
  int xCursor;
  /* RECOVERED: the running glyph-width advance (EBP), 6 px per character,
   * accumulated across the row's strings at 0x41bf07-0x41bf13 and
   * 0x41bf6d-0x41bf76.  Ghidra kept the strlen walks and discarded their
   * results - the same drop as FUN_005078f0.c's xAdvance. */
  int xAdvance;
  undefined4 local_8;
  int local_4;
  
  local_4 = 0;
  local_10 = 0x13a;
  iVar9 = param_1;
LAB_0041bd02:
  local_8 = 0x1f;
  iVar8 = (((int)*(uint *)(param_1 + 0x3b97c) < 1) - 1 & *(uint *)(param_1 + 0x3b97c)) + local_4;
  uVar3 = *(ushort *)(param_1 + 0x3f73c + iVar8 * 2);
  /* orig 0x41bd2e-0x41bd49: the icon test writes the row's x-cursor into
   * the dropped [esp+0x18] slot on BOTH paths before the sprite lookup
   * runs - `test ax,ax / jne` then 0x24 (no icon) or 0x32 (icon). */
  xCursor = 0x24;
  if (uVar3 != 0) {
    xCursor = 0x32;
  }
  if (((uVar3 != 0) && (uVar5 = uVar3 - 1, g_screenSurface != 0)) && (-1 < (int)uVar5)) {
    iVar7 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar4 = *(uint *)(iVar7 + 4);
    while (uVar4 < 0x35) {
      if (uVar4 == 0x34) {
        iVar7 = *(int *)(iVar7 + 0x10);
        uVar4 = *(uint *)(iVar7 + 8);
        if (uVar4 <= uVar5) goto LAB_0041bd81;
        break;
      }
      iVar7 = *(int *)(iVar7 + 0x1c);
      uVar4 = *(uint *)(iVar7 + 4);
    }
  }
  goto LAB_0041bdb7;
  while( true ) {
    iVar7 = *(int *)(iVar7 + 0x10);
    uVar4 = *(uint *)(iVar7 + 8);
    if (uVar5 < uVar4) break;
LAB_0041bd81:
    if (uVar4 == uVar5) {
      if (*(char *)(iVar7 + 0x18) == '\x01') {
        BlitSprite16bpp(uVar5,0x24,local_10,0x34);
      }
      else {
        BlitSpriteClipped(uVar5,0x24,local_10,0x34);
      }
      break;
    }
  }
LAB_0041bdb7:
  switch(*(undefined1 *)(param_1 + 0x3c4d8 + iVar8)) {
  case 0:
    iVar9 = 0xffff;
    local_14 = 0xffff;
    local_8 = 0x1f;
    break;
  case 1:
    iVar9 = 0xc618;
    goto LAB_0041bebd;
  case 2:
    iVar9 = 0;
    local_14 = 0xffe0;
    break;
  case 3:
    iVar9 = 0xf800;
    goto LAB_0041bebd;
  case 4:
    local_14 = 0xafff;
    iVar9 = 0xf0;
    break;
  case 5:
    iVar9 = 0;
    local_14 = 0xc7f8;
    break;
  case 6:
  case 8:
    iVar9 = 0x8000;
    local_14 = 0xf800;
    break;
  case 7:
    local_14 = 0x78e0;
    iVar9 = 0xfdb4;
    local_8 = 0;
    break;
  case 9:
    iVar9 = 0x400;
    local_14 = 0xfff2;
    break;
  case 10:
    local_14 = 0xf800;
    iVar9 = 0xfebf;
    break;
  case 0xb:
    local_14 = 0xfc20;
    iVar9 = 0x4880;
    break;
  case 0xc:
    local_14 = 0x7e0;
    iVar9 = 0x210a;
    break;
  case 0xd:
    local_14 = 0x1f;
    iVar9 = 0xf6bf;
    break;
  case 0xe:
    local_14 = 0xc018;
    iVar9 = 0xfecf;
    break;
  case 0xf:
    local_14 = 0;
    iVar9 = 0xffff;
    break;
  case 0x10:
    iVar9 = 0;
LAB_0041bebd:
    local_14 = 0xffff;
  }
  pcVar6 = (char *)(iVar8 * 9 + 0x3b984 + param_1);
  /* RE-SLOT + dropped EAX (objdump @0x41bec5-0x41bedf): x/ECX =
   * `mov ecx,[esp+0x20]` taken at esp-8, i.e. the [esp+0x18] slot
   * recovered above as xCursor; y = ecx = [esp+0x14] = local_10; colour =
   * eax = [esp+0x1c] = local_8; string = EAX = ebp =
   * `lea edx,[ebx+esi*8] / lea ebp,[esi+edx+0x3b984]` = pcVar6. */
  DrawFontString(xCursor,local_10,local_8,pcVar6);
  /* CORRECTED 2026-08-28: ECX is NOT local_4. `mov ecx,[esp+0x20]` at
   * 0x41bee8 runs with the two DrawFontString pushes still pending, so
   * it reaches [esp+0x18] - the xCursor slot recovered above, not the
   * [esp+0x20] slot that name belongs to. The earlier reading counted at
   * the wrong depth. EAX = pcVar6 stands. */
  BlitRLESprite(xCursor,local_10,iVar9,(byte *)pcVar6);
  do {
    cVar1 = *pcVar6;
    pcVar6 = pcVar6 + 1;
  } while (cVar1 != '\0');
  /* orig 0x41bf07-0x41bf13: `sub eax,ebp / lea ebp,[eax+eax*2] / shl
   * ebp,1` - the name's pixel width at 6 px per character.  Ghidra kept
   * the walk above and discarded its result. */
  xAdvance = ((int)pcVar6 - (int)(iVar8 * 9 + 0x3b984 + param_1) - 1) * 6;
  bVar2 = *(byte *)(param_1 + 0x3c4d8 + iVar8);
  if ((bVar2 < 2) || (bVar2 == 7)) {
    pcVar6 = (char *)(param_1 + (iVar8 * 5 + 0xef42) * 4);
    /* RECOVERED 2026-08-28: the "dead stack slot" is xCursor and the
     * "accumulated pixel-width" is xAdvance, both now named above.
     * objdump 0x41bfaa-0x41bfc6: `lea ecx,[edx+ebp]` with edx = [esp+0x18]
     * then `inc ecx`, so ECX = xCursor + xAdvance + 1; EAX = ebx =
     * pcVar6. */
    BlitRLESprite(xCursor + xAdvance + 1,local_10 + 1,0,(byte *)pcVar6);
    /* RECOVERED 2026-08-28: `mov ecx,[esp+0x20]` at 0x41bfcf runs two
     * pushes deep, so it reaches [esp+0x18] = xCursor - not local_4, the
     * same off-by-one-slot the first call in this function had. `add
     * ecx,ebp` then adds xAdvance; EAX = ebx = pcVar6. */
    BlitRLESprite(xCursor + xAdvance,local_10,iVar9,(byte *)pcVar6);
    do {
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    /* RECOVERED 2026-08-28: the second field pointer stands, and the
     * "mystery constant + ebp" is xCursor + xAdvance. objdump
     * 0x41bfe3-0x41c016: the strlen walk's own result is folded in on top
     * (`sub eax,ecx / lea eax,[eax+eax*2] / lea ecx,[ebp+eax*2]`) and then
     * `lea ecx,[ecx+ebx+1]` with ebx = [esp+0x18], so ECX = xCursor +
     * xAdvance + this field's width + 1. This branch computes that total
     * into ECX without storing it back to ebp, which is why xAdvance
     * itself is not advanced here. */
    BlitRLESprite(xCursor + xAdvance +
                  ((int)pcVar6 - (int)(param_1 + (iVar8 * 5 + 0xef42) * 4) - 1) * 6 + 1,
                  local_10 + 1,0,(byte *)(param_1 + iVar8 * 0x80 + 0x3c53c));
    /* RECOVERED 2026-08-28: ECX = ebx = xCursor alone (`mov ecx,ebx` at
     * 0x41c023, ebx loaded from [esp+0x18] at 0x41bff1 and not advanced),
     * EAX = the same second field pointer as the call directly above. */
    BlitRLESprite(xCursor,local_10,iVar9,(byte *)(param_1 + iVar8 * 0x80 + 0x3c53c));
  }
  else {
    pcVar6 = (char *)(param_1 + (iVar8 * 5 + 0xef42) * 4);
    /* RE-SLOT + dropped EAX (objdump @0x41bf25-0x41bf3d): x/ECX =
     * `mov ecx,[esp+0x18] / add ecx,ebp` = xCursor + xAdvance; y = edx =
     * [esp+0x14] = local_10; colour = edi = iVar9; string = EAX = ebx =
     * `lea eax,[esi+esi*4+0xef42] / lea ebx,[ebx+eax*4]` = pcVar6. */
    DrawFontString(xCursor + xAdvance,local_10,iVar9,pcVar6);
    /* RECOVERED 2026-08-28: ECX = xCursor + xAdvance (`mov edx,[esp+0x20]`
     * at 0x41bf4a, two pushes deep, so [esp+0x18]; then `lea ecx,[edx+ebp]`
     * at 0x41bf52), EAX = ebx = pcVar6 as already noted. */
    BlitRLESprite(xCursor + xAdvance,local_10,local_14,(byte *)pcVar6);
    do {
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    /* orig 0x41bf6d-0x41bf76: the colour field's own width is added into
     * the running advance (`sub eax,ecx / lea eax,[eax+eax*2] / lea
     * ebp,[ebp+eax*2]`) - another dropped strlen result. */
    xAdvance = xAdvance + ((int)pcVar6 - (int)(param_1 + (iVar8 * 5 + 0xef42) * 4) - 1) * 6;
    /* RE-SLOT + dropped EAX (objdump @0x41bf69-0x41bf91): x/ECX = ebx =
     * `mov edx,[esp+0x18] / lea ebx,[edx+ebp]` = xCursor + xAdvance;
     * y = ebp = [esp+0x14] = local_10; colour = edi = iVar9; string = EAX
     * = esi = `shl esi,7 / lea esi,[esi+ecx+0x3c53c]` = param_1 +
     * iVar8*0x80 + 0x3c53c, the per-row message-text field Ghidra dropped
     * entirely (the same second pointer this file's BlitRLESprite notes
     * flag at 0x41bfa0). */
    DrawFontString(xCursor + xAdvance,local_10,iVar9,
                   (char *)(param_1 + iVar8 * 0x80 + 0x3c53c));
    /* RECOVERED 2026-08-28: the second field pointer stands; ECX = ebx,
     * built at 0x41bf7a as `lea ebx,[edx+ebp]` from [esp+0x18] and the
     * already-advanced ebp, i.e. xCursor + xAdvance with this field's own
     * width folded in by the DrawFontString line above. */
    BlitRLESprite(xCursor + xAdvance,local_10,local_14,
                  (byte *)(param_1 + iVar8 * 0x80 + 0x3c53c));
  }
  local_10 = local_10 + 0xf;
  local_4 = local_4 + 1;
  if (0x1fc < local_10) {
    return;
  }
  goto LAB_0041bd02;
}

