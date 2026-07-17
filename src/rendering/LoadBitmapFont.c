/* LoadBitmapFont - 0x004eae60 in the original binary.
 *
 * LoadBitmapFont: loads the game's bitmap font from the "font.fnt" entry
 * of the graphics.xfs archive into the two glyph tables read by
 * BlitFontGlyphClipped/BlitRLESprite - the ASCII table DAT_00673628 (0x600
 * bytes = 128 glyphs x 12) and the full-width/CJK table g_fullWidthFontGlyphs
 * (0xc0000 bytes). Called once from InitGame. Recovered from the original
 * disassembly at 0x4eae60-0x4eaea4 (the two dropped register args are the
 * XFSArchive* &g_graphicsArchive in EDI and the name "font.fnt" in EAX,
 * both set inline right before the OpenXFSEntryStream call; findExisting=1
 * in CL, insertFlag=0 on the stack - the OpenXFSEntryStream shape
 * PreloadTexture.c already uses):
 *   mov eax,0x557408 ("font.fnt"); mov edi,&g_graphicsArchive;
 *   call OpenXFSEntryStream; read 0x600 -> DAT_00673628;
 *   read 0xc0000 -> g_fullWidthFontGlyphs; call CloseSpriteReadState.
 *
 * FULLY UN-STUBBED (2026-07-17): both reads are live. The ASCII read
 * (0x600 into DAT_00673628) renders the ServerSelect world-list names; the
 * full-width read (0xc0000 into g_fullWidthFontGlyphs) populates the double-byte/CJK
 * glyph table BlitRLESprite indexes for wide text. g_fullWidthFontGlyphs is now
 * sized to 0xc0000 in globals_sized.c. The earlier worry that this needed a
 * multi-global offset-macro reconciliation was mistaken: the DAT_005f3xxx
 * "globals" whose addresses fall in this buffer's range are actually
 * client-context arena offsets (base = g_clientContext), a separate
 * subsystem that never aliases this buffer's storage (see globals_sized.c).
 */
#include "ghidra_types.h"
#include "xfs.h"


void LoadBitmapFont(void)

{
  int stream;

  stream = OpenXFSEntryStream((int)&g_graphicsArchive, "font.fnt", 1, 0);
  if (stream != 0) {
    ReadXFSEntryByte((undefined4 *)stream, (undefined4 *)&DAT_00673628, 0x600);
    ReadXFSEntryByte((undefined4 *)stream, (undefined4 *)&g_fullWidthFontGlyphs, 0xc0000);
    CloseSpriteReadState((void *)stream, (int)&g_graphicsArchive);
  }
  return;
}

