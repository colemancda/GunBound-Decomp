/* RenderReadyRoomChatRow - 0x0050d200 in the original binary.
 *
 * Row renderer (vtable slot 9) for the Ready Room chat-log panel: draws each message with a per-row icon (+0x3f73c) and a message-type byte (+0x3c4d8) that selects one of several RGB565 text colors (white/gray/yellow/red/...) - the same color-coded-chat idiom as the in-battle chat renderer. Indexed via +0x3b97c off g_clientContext. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall RenderReadyRoomChatRow(int param_1)

{
  char cVar1;
  byte bVar2;
  ushort uVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int local_1c;
  undefined4 local_14;
  int local_10;
  int iVar11;
  char *pcVar12;
  int iVar13;
  char *pcVar14;

  if (*(char *)(param_1 + 0x1e) == '\0') {
    Widget_DrawSelf(param_1);
    iVar7 = *(int *)(param_1 + 0x2c) + 0x14;
    local_10 = 0;
    iVar8 = param_1;
    do {
      local_14 = 0x1f;
      iVar10 = (((int)*(uint *)(g_clientContext + 0x3b97c) < 1) - 1 & *(uint *)(g_clientContext + 0x3b97c)
               ) + local_10;
      uVar3 = *(ushort *)(g_clientContext + 0x3f73c + iVar10 * 2);
      iVar13 = iVar10;
      /* BlitRLESprite's dropped 1st arg (this/x-cursor) for the calls
       * below is objdump-confirmed (0x50d40c/0x50d46f/0x50d4e0) to be
       * *(int *)(param_1 + 0x28), offset by 0xb (no icon this row) or
       * 0x19 (icon present) - the same field this block reads as iVar4
       * for the icon blit, plus a small fixed gap for the icon glyph's
       * width. Ghidra folded this into an unnamed stack temp since the
       * icon branch alone doesn't show it live in the decompiled C;
       * recovered here as iVar11. */
      if (uVar3 != 0) {
        iVar4 = *(int *)(param_1 + 0x28);
        iVar11 = iVar4 + 0x19;
        iVar9 = uVar3 - 1;
        if (((DAT_0079352c != 0) && (-1 < iVar9)) && (iVar5 = FindSpriteFrame(), iVar5 != 0)) {
          if (*(char *)(iVar5 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar4 + 0x1a,iVar7);
          }
          else {
            BlitSpriteClipped(iVar9);
          }
        }
      }
      else {
        iVar11 = *(int *)(param_1 + 0x28) + 0xb;
      }
      switch(*(undefined1 *)(g_clientContext + 0x3c4d8 + iVar10)) {
      case 0:
        iVar8 = 0xffff;
        local_1c = 0xffff;
        local_14 = 0x1f;
        break;
      case 1:
        iVar8 = 0xc618;
        goto LAB_0050d3e9;
      case 2:
        iVar8 = 0;
        local_1c = 0xffe0;
        break;
      case 3:
        iVar8 = 0xf800;
        goto LAB_0050d3e9;
      case 4:
        local_1c = 0xafff;
        iVar8 = 0xf0;
        break;
      case 5:
        iVar8 = 0;
        local_1c = 0xc7f8;
        break;
      case 6:
      case 8:
        iVar8 = 0x8000;
        local_1c = 0xf800;
        break;
      case 7:
        local_1c = 0x78e0;
        iVar8 = 0xfdb4;
        local_14 = 0;
        break;
      case 9:
        iVar8 = 0x400;
        local_1c = 0xfff2;
        break;
      case 10:
        local_1c = 0xf800;
        iVar8 = 0xfebf;
        break;
      case 0xb:
        local_1c = 0xfc20;
        iVar8 = 0x4880;
        break;
      case 0xc:
        local_1c = 0x7e0;
        iVar8 = 0x210a;
        break;
      case 0xd:
        local_1c = 0x1f;
        iVar8 = 0xf6bf;
        break;
      case 0xe:
        local_1c = 0xc018;
        iVar8 = 0xfecf;
        break;
      case 0xf:
        local_1c = 0;
        iVar8 = 0xffff;
        break;
      case 0x10:
        iVar8 = 0;
LAB_0050d3e9:
        local_1c = 0xffff;
      }
      pcVar6 = (char *)(iVar10 * 9 + 0x3b984 + g_clientContext);
      DrawFontString(iVar7,local_14);
      /* BlitRLESprite's dropped args (confirmed via objdump at this call
       * site, 0x50d414): ECX (this) = iVar11 (the icon-derived x-cursor
       * recovered above); EAX (rleData) = pcVar6, the sender-name buffer
       * just built above and walked by the strlen loop right after. */
      BlitRLESprite(iVar11,iVar7,iVar8,(byte *)pcVar6);
      pcVar12 = pcVar6;
      do {
        cVar1 = *pcVar6;
        pcVar6 = pcVar6 + 1;
      } while (cVar1 != '\0');
      /* Name-width x-cursor for the calls below: iVar11 advanced past
       * the sender-name buffer's width (strlen(pcVar12)*6, from the
       * strlen loop just above - pcVar6 is about to be reassigned to
       * the message-color field, so the name's end pointer is snapshot
       * into pcVar14 first). */
      pcVar14 = pcVar6;
      bVar2 = *(byte *)(g_clientContext + 0x3c4d8 + iVar10);
      if ((bVar2 < 2) || (bVar2 == 7)) {
        pcVar6 = (char *)(g_clientContext + (iVar10 * 5 + 0xef42) * 4);
        /* BlitRLESprite's dropped args (0x50d4d1): ECX (this) =
         * iVar11 + (name-strlen)*6 + 1 (x-cursor advanced past the name
         * just drawn/measured above, name width from pcVar12/pcVar14's
         * strlen loop); EAX (rleData) = pcVar6, the message-color field
         * just computed above, walked by the strlen loop right after. */
        BlitRLESprite(iVar11 + ((int)pcVar14 - (int)(pcVar12 + 1)) * 6 + 1,iVar7,0,(byte *)pcVar6);
        /* BlitRLESprite's dropped args (0x50d4e2): ECX (this) = same
         * iVar11 + name-strlen*6 x-cursor as the call just above (no +1
         * this time); EAX (rleData) = pcVar6, unchanged since it's the
         * same message-color field, re-read here for a second draw. */
        BlitRLESprite(iVar11 + ((int)pcVar14 - (int)(pcVar12 + 1)) * 6,iVar7,iVar8,(byte *)pcVar6);
        pcVar12 = pcVar6;
        do {
          cVar1 = *pcVar6;
          pcVar6 = pcVar6 + 1;
        } while (cVar1 != '\0');
        /* BlitRLESprite's dropped args (0x50d51f): ECX (this) = the
         * x-cursor advanced past THIS (message-color) field's own
         * strlen*6 width, +1, added on top of iVar11; EAX (rleData) =
         * g_clientContext + iVar13*0x80 + 0x3c53c (iVar13 is this row's
         * index, snapshotted before iVar10 gets reused as the color
         * temp below), the per-row message text field - a new field
         * recovered here, distinct from any pointer already visible in
         * this file's C. */
        BlitRLESprite(iVar11 + ((int)pcVar6 - (int)(pcVar12 + 1)) * 6 + 1,iVar7,0,
                      (byte *)(g_clientContext + iVar13 * 0x80 + 0x3c53c));
        iVar10 = iVar8;
      }
      else {
        pcVar6 = (char *)(g_clientContext + (iVar10 * 5 + 0xef42) * 4);
        DrawFontString(iVar7,iVar8);
        /* BlitRLESprite's dropped args (0x50d471): ECX (this) =
         * iVar11 + name-strlen*6 (same x-cursor formula as the if-branch
         * above, no +1 here); EAX (rleData) = pcVar6, the message-color
         * field just computed above. */
        BlitRLESprite(iVar11 + ((int)pcVar14 - (int)(pcVar12 + 1)) * 6,iVar7,local_1c,(byte *)pcVar6);
        pcVar12 = pcVar6;
        do {
          cVar1 = *pcVar6;
          pcVar6 = pcVar6 + 1;
        } while (cVar1 != '\0');
        DrawFontString(iVar7,iVar8);
        iVar10 = local_1c;
      }
      /* BlitRLESprite's dropped args (0x50d52a, shared by both branches
       * above): ECX (this) = the x-cursor advanced past the
       * message-color field's own strlen*6 width (no +1, matching the
       * DrawFontString call right before this point in each branch);
       * EAX (rleData) = g_clientContext + iVar13*0x80 + 0x3c53c, the
       * same per-row message text field as the if-branch's 3rd call
       * (iVar13 = this row's index, since iVar10 has been repurposed as
       * the shared color temp by this point). */
      BlitRLESprite(iVar11 + ((int)pcVar6 - (int)(pcVar12 + 1)) * 6,iVar7,iVar10,
                    (byte *)(g_clientContext + iVar13 * 0x80 + 0x3c53c));
      iVar7 = iVar7 + 0xe;
      local_10 = local_10 + 1;
    } while (local_10 < 9);
  }
  return;
}

