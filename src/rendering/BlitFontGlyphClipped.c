/* BlitFontGlyphClipped - 0x004eafa0 in the original binary.
 *
 * NAMED (2026-07-17): plots one monochrome bitmap-font glyph into the
 * 16bpp framebuffer, rect-clipped. The glyph is a 6x12 cell: 12 rows
 * (the `local_4 = 0xc` outer loop), each row a 1-byte bitmask in the
 * glyph bitmap whose top 6 bits (7..2) select the 6 columns. Set bits
 * write the solid text colour `param_3` as a u16 pixel at
 * `g_screenSurface[y*pitch + x]` (DAT_0079352c = surface base,
 * DAT_005b3620 = pixel pitch); clear bits and out-of-clip pixels are
 * skipped. Called per character by the bitmap-font string renderer
 * BlitRLESprite (0x4eb450), which steps x by 6 (half-width) or 12
 * (full-width) between glyphs.
 *
 * Args: param_1 = y (top row, walked down one per bitmap byte),
 * param_2 = x (left column), param_3 = 16bpp colour, glyphBitmap = the
 * 12-byte 1bpp glyph.
 *
 * DROPPED-EAX FIX (2026-07-17): the glyph bitmap arrived in EAX, which
 * Ghidra emitted as an uninitialised `byte *in_EAX`. Recovered from
 * BlitRLESprite's own disassembly at 0x4eb4ca-0x4eb4d9: `movzx eax,al;
 * lea eax,[eax+eax*2]; lea eax,[eax*4+0x673628]` = &DAT_00673628 +
 * char*0xc (the ASCII font table). Promoted to an explicit trailing
 * `glyphBitmap` parameter and the sole caller (BlitRLESprite) fixed to
 * pass it - it previously passed only (param_1,param_3), leaving in_EAX
 * garbage (a charsetKey 0x32 leaked in and `*in_EAX` faulted). Clip
 * rect: x in [DAT_00793530, DAT_0056df30], y in [DAT_00793534,
 * DAT_0056df34].
 */
#include "ghidra_types.h"


void __thiscall BlitFontGlyphClipped(int param_1,int param_2,int param_3,byte *glyphBitmap)

{
  byte *in_EAX = glyphBitmap;
  int iVar1;
  int iVar2;
  int local_4;

  local_4 = 0xc;
  do {
    if (*in_EAX != 0) {
      iVar2 = 7;
      iVar1 = param_2;
      do {
        if (((((*in_EAX >> ((byte)iVar2 & 0x1f) & 1) != 0) && (iVar1 <= DAT_0056df30)) &&
            (DAT_00793530 <= iVar1)) && ((param_1 <= DAT_0056df34 && (DAT_00793534 <= param_1)))) {
          *(undefined2 *)(DAT_0079352c + (param_1 * DAT_005b3620 + iVar1) * 2) = param_3;
        }
        iVar2 = iVar2 + -1;
        iVar1 = iVar1 + 1;
      } while (1 < iVar2);
    }
    in_EAX = in_EAX + 1;
    param_1 = param_1 + 1;
    local_4 = local_4 + -1;
  } while (local_4 != 0);
  return;
}
