/* FUN_004eae60 - 0x004eae60 in the original binary.
 *
 * LoadBitmapFont: loads the game's bitmap font from the "font.fnt" entry
 * of the graphics.xfs archive into the two glyph tables read by
 * BlitFontGlyphClipped/BlitRLESprite - the ASCII table DAT_00673628 (0x600
 * bytes = 128 glyphs x 12) and the full-width/CJK table DAT_005b3628
 * (0xc0000 bytes). Called once from InitGame. Recovered from the original
 * disassembly at 0x4eae60-0x4eaea4 (the two dropped register args are the
 * XFSArchive* &g_graphicsArchive in EDI and the name "font.fnt" in EAX,
 * both set inline right before the OpenXFSEntryStream call; findExisting=1
 * in CL, insertFlag=0 on the stack - the OpenXFSEntryStream shape
 * PreloadTexture.c already uses):
 *   mov eax,0x557408 ("font.fnt"); mov edi,&g_graphicsArchive;
 *   call OpenXFSEntryStream; read 0x600 -> DAT_00673628;
 *   read 0xc0000 -> DAT_005b3628; call CloseSpriteReadState.
 *
 * UN-STUBBED (2026-07-17) for the ASCII font only - this is what renders
 * the ServerSelect world-list server names/numbers (previously blank
 * because this loader was a no-op stub). The full-width read (0xc0000
 * into DAT_005b3628) is skipped: DAT_005b3628 is still a 1-byte global and
 * sizing it to 0xc0000 needs a ~32-global offset-macro reconciliation
 * (like DAT_00e55ce0's) - only needed for CJK text, not the ASCII server
 * list. Do that when CJK rendering is needed.
 */
#include "ghidra_types.h"
#include "xfs.h"


void FUN_004eae60(void)

{
  int stream;

  stream = OpenXFSEntryStream((int)&g_graphicsArchive, "font.fnt", 1, 0);
  if (stream != 0) {
    ReadXFSEntryByte((undefined4 *)stream, (undefined4 *)&DAT_00673628, 0x600);
    /* Full-width font: ReadXFSEntryByte(stream, &DAT_005b3628, 0xc0000) -
     * skipped until DAT_005b3628 is sized (see header). */
    CloseSpriteReadState((void *)stream, (int)&g_graphicsArchive);
  }
  return;
}

