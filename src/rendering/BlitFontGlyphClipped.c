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
 * param_2 = x (left column), param_3 = 16bpp colour. The glyph bitmap
 * pointer arrives in EAX (a dropped register argument Ghidra emitted as
 * an uninitialised `byte *in_EAX`) - NOT fixed here: BlitRLESprite's own
 * call site drops both it and param_2 (calls `FUN_004eafa0(param_1,
 * param_3)`), part of the same still-unrecovered bitmap-font/sprite
 * fan-out FindSpriteFrame.c's header describes. Clip rect: x in
 * [DAT_00793530, DAT_0056df30], y in [DAT_00793534, DAT_0056df34].
 */
#include "ghidra_types.h"


void __thiscall BlitFontGlyphClipped(int param_1,int param_2,int param_3)

{
  byte *in_EAX;
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
