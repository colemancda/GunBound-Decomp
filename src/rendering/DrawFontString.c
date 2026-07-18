/* DrawFontString - 0x004eb510 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED REGISTER ARGUMENT (pattern #1) - investigated, NOT fixed here:
 * `in_EAX` is the RLE glyph-stream/string pointer, dropped by Ghidra with
 * no corresponding parameter - identical bug shape to the sibling
 * BlitRLESprite.c (0x4eb450, see that file's header for the full
 * disassembly proof: EAX is loaded right before the call by every real
 * caller, immediately followed by a `do { c = *p; p++; } while (c != 0)`
 * strlen scan on return, with nothing in between that could clobber it).
 * DrawFontString has ~30+ call sites across ~15 files (BlitSpriteText.c,
 * DrawButtonWidget.c, DrawSprite.c, GameTick.c, and a dozen+ render/
 * State* files) - fixing this correctly requires the same per-site
 * disassembly recovery as BlitRLESprite's remaining call sites, deferred
 * as the same class of undertaking (see BlitRLESprite.c's and
 * FindSpriteFrame.c's own header comments).
 */
#include "ghidra_types.h"


void __thiscall DrawFontString(int param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  char *in_EAX;
  int iVar2;
  char *pcVar3;
  int local_4;

  /* SAFE NO-OP (2026-07-18): this is the bitmap-font *shadow* pass over a
   * string (RenderWorldListRow uses it for the world-list name shadow; the
   * main glyphs come from BlitRLESprite / the "1" row index from
   * BlitSpriteText). Two problems make it a large deferred reconstruction,
   * not a quick fix:
   *   1. its string arrives in EAX (`in_EAX`) - a dropped register that is
   *      UNRELIABLE at all 31 call sites (relied on register luck); a real
   *      value flowing in (e.g. once the row index "%d" formats to "1")
   *      faults `*in_EAX` here.
   *   2. even given a valid string, the glyph blit itself is missing: the
   *      per-pixel write in DrawNarrowGlyph (0x4eb290) is an EMPTY
   *      `if(...){}` block - Ghidra dropped the actual screen store - so
   *      this pass produces NO visible output today regardless.
   * Because it draws nothing now anyway, returning immediately is visually
   * identical AND removes the fault, unblocking the "1" prefix
   * (g_rowIndexFormat="%d" + BlitSpriteText). Reconstructing the real shadow
   * (DrawFontString this=X/string=EAX + the DrawNarrowGlyph/DrawWideGlyph
   * pixel-write loops) is the deferred bitmap-font fan-out (session-15 notes). */
  return;

  cVar1 = *in_EAX;
  if (cVar1 != '\0') {
    local_4 = param_1 + 6;
    iVar2 = param_1 + 0xc;
    do {
      pcVar3 = in_EAX + 1;
      if (cVar1 < '\0') {
        pcVar3 = in_EAX + 2;
        if (DAT_00793530 <= iVar2) {
          DrawWideGlyph(param_1,param_2,param_3);
        }
        param_1 = param_1 + 0xc;
        iVar2 = iVar2 + 0xc;
        local_4 = local_4 + 0xc;
      }
      else {
        if ((cVar1 != ' ') && (DAT_00793530 <= local_4)) {
          DrawNarrowGlyph(param_1,param_2,param_3);
        }
        param_1 = param_1 + 6;
        iVar2 = iVar2 + 6;
        local_4 = local_4 + 6;
      }
    } while ((param_1 <= DAT_0056df30) && (cVar1 = *pcVar3, in_EAX = pcVar3, cVar1 != '\0'));
  }
  return;
}

