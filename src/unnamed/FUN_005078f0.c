/* FUN_005078f0 - 0x005078f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_005078f0(int param_1)

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
  int iVar10;
  int local_14;
  undefined4 local_c;
  int local_8;
  /* Ghidra's `iVar9` is reused below (line ~182/196) to carry the
   * if/else branch's merge-color value, clobbering its original
   * row-index meaning before the final BlitRLESprite call at the end
   * of the loop reads it - objdump confirms that call's EAX still uses
   * the ORIGINAL row index (esi, unclobbered), not the reassigned
   * value. Recovered by snapshotting it here under a new name. */
  int iVar9RowIndex;
  /* RECOVERED (2026-07-27): the row's glyph x-cursor. It lives in the stack
   * local [esp+0x14] (base frame), written on BOTH paths through the
   * sprite-lookup block below (0x507969: m_x+0x1a when the room has no icon;
   * 0x507984: m_x+0x28 when it does) and reloaded before every DrawFontString/
   * BlitRLESprite below (0x507b05/0x507b19/0x507b54/0x507b74/0x507ba6/
   * 0x507bc9/0x507be7/0x507c18). Ghidra dropped both the assignments and the
   * uses, which is why every text call in this function was missing its
   * leading `this`/x argument. */
  int xCursor;
  /* RECOVERED (2026-07-27): the running glyph-width advance, EBP. Each strlen
   * scan below is followed by `lea r,[len+len*2] / shl r,1` (0x507b37-0x507b48,
   * 0x507b97-0x507ba2, 0x507c09-0x507c14) - i.e. 6 pixels per character,
   * accumulated across the two strings so the second/third draws land after the
   * first. Ghidra kept the strlen loops but discarded their results. */
  int xAdvance;
  char *pcStart;

  if (*(char *)(param_1 + 0x1e) != '\0') {
    return;
  }
  Widget_DrawSelf(param_1);
  iVar8 = *(int *)(param_1 + 0x2c) + 0x2b;
  local_8 = 0;
  iVar10 = param_1;
LAB_00507930:
  local_c = 0x1f;
  iVar9 = (((int)*(uint *)(g_clientContext + 0x3b97c) < 1) - 1 & *(uint *)(g_clientContext + 0x3b97c)) +
          local_8;
  iVar9RowIndex = iVar9;
  uVar3 = *(ushort *)(g_clientContext + 0x3f73c + iVar9 * 2);
  if (uVar3 == 0) {
    /* 0x507963: mov ebp,[ebp+0x28] / add ebp,0x1a / mov [esp+0x14],ebp */
    xCursor = *(int *)(param_1 + 0x28) + 0x1a;
  }
  else {
    uVar5 = uVar3 - 1;
    /* 0x50796f-0x507984: mov ecx,[ebp+0x28] / lea edx,[ecx+0x28] /
     * lea ebp,[ecx+0x1a] / mov [esp+0x14],edx - the cursor is m_x+0x28 here
     * (the icon column shifts the text right), while EBP (m_x+0x1a) is the
     * icon's own x used by the two blits below. */
    xCursor = *(int *)(param_1 + 0x28) + 0x28;
    if ((g_screenSurface != 0) && (-1 < (int)uVar5)) {
      iVar7 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar4 = *(uint *)(iVar7 + 4);
      while (uVar4 < 0x35) {
        if (uVar4 == 0x34) {
          iVar7 = *(int *)(iVar7 + 0x10);
          uVar4 = *(uint *)(iVar7 + 8);
          if (uVar4 <= uVar5) goto LAB_005079b8;
          break;
        }
        iVar7 = *(int *)(iVar7 + 0x1c);
        uVar4 = *(uint *)(iVar7 + 4);
      }
    }
  }
  goto LAB_005079ea;
  while( true ) {
    iVar7 = *(int *)(iVar7 + 0x10);
    uVar4 = *(uint *)(iVar7 + 8);
    if (uVar5 < uVar4) break;
LAB_005079b8:
    if (uVar4 == uVar5) {
      /* RECOVERED (2026-07-27), orig 0x5079c6-0x5079e2. FindSpriteFrame is
       * INLINED here (the tree walk above), so the outer key is visible as the
       * literal the walk compares against and as `mov edx,0x34` at 0x5079ca -
       * outerKey = 0x34, innerKey/frame = EAX = uVar5. x is EBP = m_x+0x1a
       * (0x507978), y is EBX = iVar8.
       *   16bpp:   push ebx / push ebp / mov eax(=uVar5) -> (frame,x,y,key)
       *   clipped: push eax / mov eax,ebx / mov ecx,ebp  -> frame on stack,
       *            x=ECX, y=EAX
       * The raw port's args had slid LEFT: the frame (EAX) and the key were
       * dropped, so the x was being passed as the frame handle. */
      if (*(char *)(iVar7 + 0x18) == '\x01') {
        BlitSprite16bpp(uVar5,*(int *)(param_1 + 0x28) + 0x1a,iVar8,0x34);
      }
      else {
        BlitSpriteClipped(uVar5,*(int *)(param_1 + 0x28) + 0x1a,iVar8,0x34);
      }
      break;
    }
  }
LAB_005079ea:
  switch(*(undefined1 *)(g_clientContext + 0x3c4d8 + iVar9)) {
  case 0:
    iVar10 = 0xffff;
    local_14 = 0xffff;
    local_c = 0x1f;
    break;
  case 1:
    iVar10 = 0xc618;
    goto LAB_00507af6;
  case 2:
    iVar10 = 0;
    local_14 = 0xffe0;
    break;
  case 3:
    iVar10 = 0xf800;
    goto LAB_00507af6;
  case 4:
    local_14 = 0xafff;
    iVar10 = 0xf0;
    break;
  case 5:
    iVar10 = 0;
    local_14 = 0xc7f8;
    break;
  case 6:
  case 8:
    iVar10 = 0x8000;
    local_14 = 0xf800;
    break;
  case 7:
    local_14 = 0x78e0;
    iVar10 = 0xfdb4;
    local_c = 0;
    break;
  case 9:
    iVar10 = 0x400;
    local_14 = 0xfff2;
    break;
  case 10:
    local_14 = 0xf800;
    iVar10 = 0xfebf;
    break;
  case 0xb:
    local_14 = 0xfc20;
    iVar10 = 0x4880;
    break;
  case 0xc:
    local_14 = 0x7e0;
    iVar10 = 0x210a;
    break;
  case 0xd:
    local_14 = 0x1f;
    iVar10 = 0xf6bf;
    break;
  case 0xe:
    local_14 = 0xc018;
    iVar10 = 0xfecf;
    break;
  case 0xf:
    local_14 = 0;
    iVar10 = 0xffff;
    break;
  case 0x10:
    iVar10 = 0;
LAB_00507af6:
    local_14 = 0xffff;
  }
  pcVar6 = (char *)(iVar9 * 9 + 0x3b984 + g_clientContext);
  /* RECOVERED (2026-07-27), orig 0x507afe-0x507b21. The x-cursor (the dropped
   * ECX `this`) is the [esp+0x14] local recovered above:
   *   mov eax,[esp+0x18](local_c) / mov ecx,[esp+0x14](xCursor) / push eax /
   *   lea ebp,[esi+edx+0x3b984](pcVar6) / push ebx(y) / mov eax,ebp / call
   *     DrawFontString                  -> (x=ECX, y=EBX, color=local_c)
   *   mov ecx,[esp+0x1c](xCursor) / push edi(color) / push ebx(y) /
   *   mov eax,ebp(rleData) / call BlitRLESprite -> (x, y, color, rleData)
   * Both draw at the bare cursor (no advance yet). DrawFontString's own EAX
   * (the same pcVar6 string) stays dropped - the port's 3-arg __thiscall
   * signature has no such parameter, and it is a deliberate no-op today. */
  DrawFontString(xCursor,iVar8,local_c);
  BlitRLESprite(xCursor,iVar8,iVar10,(byte *)pcVar6);
  pcStart = pcVar6;
  do {
    cVar1 = *pcVar6;
    pcVar6 = pcVar6 + 1;
  } while (cVar1 != '\0');
  /* 0x507b37-0x507b48: sub eax,ebp / lea ebp,[eax+eax*2] / shl ebp,1 */
  xAdvance = ((int)pcVar6 - (int)pcStart + -1) * 6;
  bVar2 = *(byte *)(g_clientContext + 0x3c4d8 + iVar9);
  if ((bVar2 < 2) || (bVar2 == 7)) {
    pcVar6 = (char *)(g_clientContext + (iVar9 * 5 + 0xef42) * 4);
    /* RECOVERED (2026-07-27), orig 0x507bc9-0x507bf3. rleData = EAX = pcVar6
     * (spilled to [esp+0x20] at 0x507bde and reloaded at 0x507beb, so both
     * calls take the same, unadvanced string). x is the cursor PLUS the label's
     * width: `mov edx,[esp+0x14] / lea ecx,[edx+ebp]` with EBP = xAdvance, and
     * `inc ecx` on the first call - i.e. the usual +1 black shadow pass
     * (color 0, pushed as `push 0`) followed by the real glyphs at the true x
     * with color EDI. */
    BlitRLESprite(xCursor + xAdvance + 1,iVar8,0,(byte *)pcVar6);
    BlitRLESprite(xCursor + xAdvance,iVar8,iVar10,(byte *)pcVar6);
    pcStart = pcVar6;
    do {
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    /* 0x507c09-0x507c14: the second string's width is ADDED to the first's
     * (`lea eax,[ebp+edx*2]`, ebp = the running advance). */
    xAdvance = xAdvance + ((int)pcVar6 - (int)pcStart + -1) * 6;
    /* RECOVERED (2026-07-27), orig 0x507c18-0x507c31: `mov edx,[esp+0x14] /
     * shl esi,7 / lea esi,[esi+ecx+0x3c53c] / lea ebp,[eax+edx] / push 0 /
     * push ebx / lea ecx,[ebp+1] / mov eax,esi` - EAX is the per-row
     * 128-byte-strided field (Ghidra dropped the computation entirely, not
     * just the argument), x = xCursor + xAdvance + 1 (the shadow pass again),
     * color 0. NOTE `shl esi,7` clobbers the row index here, hence
     * iVar9RowIndex. */
    BlitRLESprite(xCursor + xAdvance + 1,iVar8,0,
                  (byte *)(g_clientContext + 0x3c53c + (iVar9RowIndex << 7)));
    iVar9 = iVar10;
  }
  else {
    pcVar6 = (char *)(g_clientContext + (iVar9 * 5 + 0xef42) * 4);
    /* RECOVERED (2026-07-27), orig 0x507b54-0x507b80: `mov edx,[esp+0x14] /
     * lea ecx,[edx+ebp]` -> x = xCursor + xAdvance for the DrawFontString
     * shadow (color EDI, y EBX); then `mov eax,[esp+0x18](local_14) /
     * mov ecx,[esp+0x1c](xCursor) / push eax / mov eax,[esp+0x24](pcVar6) /
     * push ebx / add ecx,ebp` -> the glyph pass at the same x with color
     * local_14. rleData = pcVar6 via the spill `mov [esp+0x20],eax` at
     * 0x507b67, reloaded as `mov eax,[esp+0x24]` at 0x507b79. */
    DrawFontString(xCursor + xAdvance,iVar8,iVar10);
    BlitRLESprite(xCursor + xAdvance,iVar8,local_14,(byte *)pcVar6);
    pcStart = pcVar6;
    do {
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    /* 0x507b97-0x507ba2: same cumulative 6-px-per-char advance. */
    xAdvance = xAdvance + ((int)pcVar6 - (int)pcStart + -1) * 6;
    /* orig 0x507ba6-0x507bbd: `mov edx,[esp+0x14] / lea ebp,[eax+edx] /
     * push edi / push ebx / mov ecx,ebp` -> x = xCursor + xAdvance. (EAX here
     * is the same per-row field the merge call below draws - dropped, since
     * DrawFontString's port has no string parameter.) */
    DrawFontString(xCursor + xAdvance,iVar8,iVar10);
    iVar9 = local_14;
  }
  /* Merge point, orig 0x507c37: `mov ecx,ebp / mov eax,esi / push ebx` with the
   * color pushed by each branch just before the jump (0x507c36 push edi /
   * 0x507bc6 push local_14 - what the port models as iVar9). EBP is
   * xCursor + xAdvance and ESI the same per-row field as the if-branch's last
   * call, both computed identically in the two branches. */
  BlitRLESprite(xCursor + xAdvance,iVar8,iVar9,
                (byte *)(g_clientContext + 0x3c53c + (iVar9RowIndex << 7)));
  iVar8 = iVar8 + 0xe;
  local_8 = local_8 + 1;
  if (0xc < local_8) {
    if (*(int *)(g_gameStateVTableArray[3] + 0x124) == -1) {
      return;
    }
    FUN_0042a680(g_gameStateVTableArray[3]);
    return;
  }
  goto LAB_00507930;
}

