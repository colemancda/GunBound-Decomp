/* BlitFullWidthGlyphClipped - 0x004eaeb0 in the original binary.
 *
 * NAMED (batch 36). Plots one 12x12 monochrome full-width (double-byte)
 * font glyph into the 16bpp framebuffer, rect-clipped: 12 rows, each a
 * 2-byte bitmask (8 bits from the first byte, the top 4 bits of the
 * second), set bits writing the colour as a u16 pixel at
 * g_screenSurface[y*g_screenPitch + x]. The twin of BlitFontGlyphClipped
 * (0x4eafa0), which plots the 6x12 half-width glyph from 12 one-byte rows.
 *
 * Evidence is the sole caller. BlitRLESprite, the bitmap-font string
 * renderer, takes the double-byte branch when a lead byte has bit 7 set,
 * indexes g_fullWidthFontGlyphs at ((lead & 0x7f) << 8 | trail) * 0x18
 * (12 rows * 2 bytes), calls this, then advances x by 0xc, where the
 * half-width branch calls BlitFontGlyphClipped and advances by 6. The
 * arguments are x, the 16bpp colour and the glyph pointer on the stack
 * (0x4eb49c-0x4eb49f, caller cleanup `add esp,0xc`) and the y row in EAX
 * (0x4eb498), with the glyph table at 0x5b3628.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void BlitFullWidthGlyphClipped(int param_1,int param_2,byte *param_3,int regEax)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int local_4;
  
  local_4 = 0xc;
  do {
    if (*param_3 != 0) {
      uVar3 = 7;
      iVar2 = param_1;
      do {
        if (((((*param_3 >> ((byte)uVar3 & 0x1f) & 1) != 0) && (iVar2 <= g_clipMaxX)) &&
            (g_clipMinX <= iVar2)) && ((regEax <= g_clipMaxY && (g_clipMinY <= regEax)))) {
          *(undefined2 *)(g_screenSurface + (regEax * g_screenPitch + iVar2) * 2) = param_2;
        }
        uVar3 = uVar3 - 1;
        iVar2 = iVar2 + 1;
      } while (uVar3 < 0x80000000);
    }
    if (param_3[1] != 0) {
      iVar4 = 0;
      iVar2 = 7;
      do {
        if ((((param_3[1] >> ((byte)iVar2 & 0x1f) & 1) != 0) &&
            (iVar1 = iVar4 + 8 + param_1, iVar1 <= g_clipMaxX)) &&
           ((g_clipMinX <= iVar1 && ((regEax <= g_clipMaxY && (g_clipMinY <= regEax)))))) {
          *(undefined2 *)(g_screenSurface + (regEax * g_screenPitch + iVar1) * 2) = param_2;
        }
        iVar4 = iVar4 + 1;
        iVar2 = iVar2 + -1;
      } while (3 < iVar2);
    }
    param_3 = param_3 + 2;
    regEax = regEax + 1;
    local_4 = local_4 + -1;
  } while (local_4 != 0);
  return;
}

