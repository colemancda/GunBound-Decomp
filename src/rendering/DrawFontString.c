/* DrawFontString - 0x004eb510 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED REGISTER ARGUMENT - RESOLVED 2026-08-28. An earlier note here
 * deferred this as the same class of undertaking as BlitRLESprite's
 * remaining sites; the per-site recovery it called for has now been done,
 * and `in_EAX` - the string pointer, loaded right before the call by
 * every caller and walked by a `do { c = *p; p++; } while (c != 0)` scan
 * on return - is the trailing regEax parameter below, and it is a RE-SLOT, not an
 * append.  The callee takes its x cursor in ECX (param_1), y at
 * [entry_esp+4] (param_2) and colour at [entry_esp+8] (param_3), plus the
 * string in EAX; but 23 of the 30 call sites passed only two arguments
 * and one (0x44a1f0) passed none, so y was landing in param_1 and colour
 * in param_2 while param_3 read whatever was above the frame.  Only the
 * remaining 6 sites were already correctly 3-slotted.  The recovered
 * form is (x, y, colour, regEax = string).
 *
 * The register, from the prologue at 0x4eb510:
 * push ecx / push ebp / mov ebp,[esp+0x10]  ; ebp = [entry_esp+8]
 * push esi / push edi
 * mov  edi,eax                              ; EAX read before written
 * mov  al,byte ptr [edi]                    ; first byte of the string
 * mov  esi,ecx                              ; ECX = param_1, the x cursor
 * The frame model is pinned by the callee's own named local: at 0x4eb52a
 * `mov [esp+0x10],ecx` with esp = entry-0x14 reaches entry-4, which the C
 * calls local_4 = param_1 + 6.
 *
 * The slot roles, from the DrawNarrowGlyph call at 0x4eb586:
 * mov edx,[esp+0x18] (= [entry_esp+4]) / push ebp / push edx / push esi
 * i.e. DrawNarrowGlyph(x=esi, y=[entry_esp+4], colour=[entry_esp+8],
 * glyph=EAX), whose body clips param_1 against g_clipMinX/g_clipMaxX,
 * param_2 against g_clipMinY/g_clipMaxY and stores param_3 as the pixel.
 *
 * 0x4eb5ca is a bare `ret` with no immediate, so the two stack arguments
 * are cleaned by the caller and the argument count cannot be read off it;
 * the count comes from the callee's own two frame reads above.
 *
 * Every call site pairs this 1-pixel outline pass with a BlitRLESprite
 * glyph pass at the same x/y over the same string - immediately after it
 * everywhere except 0x4c8eb5, where the glyph pass comes first - and that
 * neighbouring call, already argument-recovered in most callers, is the
 * witness that pairs each binary site to its source statement.
 *
 * STILL A NO-OP: the early `return` below is unchanged.  Note that the
 * old text here claiming DrawNarrowGlyph's pixel write is an empty
 * `if(...){}` block is now stale - that store has since been recovered -
 * so dropping the `return` is a real, separate follow-up rather than a
 * cosmetic one.
 */
#include "ghidra_types.h"


void __thiscall DrawFontString(int param_1,undefined4 param_2,undefined4 param_3,char *regEax)

{
  char cVar1;
  char *in_EAX = regEax;
  int iVar2;
  char *pcVar3;
  int local_4;

  /* SAFE NO-OP (2026-07-18): this is the bitmap-font *shadow* pass over a
   * string (RenderWorldListRow uses it for the world-list name shadow; the
   * main glyphs come from BlitRLESprite / the "1" row index from
   * BlitSpriteText). Two problems make it a large deferred reconstruction,
   * not a quick fix:
   *   1. its string arrived in EAX (`in_EAX`) - a dropped register that was
   *      UNRELIABLE at every call site (it relied on register luck); a real
   *      value flowing in (e.g. once the row index "%d" formats to "1")
   *      faulted `*in_EAX` here.  RETIRED 2026-08-28: all 30 sites now pass
   *      the string explicitly as regEax, so this reason no longer holds.
   *   2. even given a valid string, the glyph blit itself is missing: the
   *      per-pixel write in DrawNarrowGlyph (0x4eb290) is an EMPTY
   *      `if(...){}` block - Ghidra dropped the actual screen store - so
   *      this pass produces NO visible output today regardless.
   * Reason 2 has since been retired as well - see the header - so the
   * `return` is kept only because dropping it is a behaviour change that
   * wants its own verified pass, not because either original reason still
   * stands.  It draws nothing today, so returning immediately stays
   * visually identical AND removed the fault, unblocking the "1" prefix
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
        if (g_clipMinX <= iVar2) {
          DrawWideGlyph(param_1,param_2,param_3);
        }
        param_1 = param_1 + 0xc;
        iVar2 = iVar2 + 0xc;
        local_4 = local_4 + 0xc;
      }
      else {
        if ((cVar1 != ' ') && (g_clipMinX <= local_4)) {
          DrawNarrowGlyph(param_1,param_2,param_3,&DAT_00673628 + (uint)(byte)cVar1 * 0xc);
        }
        param_1 = param_1 + 6;
        iVar2 = iVar2 + 6;
        local_4 = local_4 + 6;
      }
    } while ((param_1 <= g_clipMaxX) && (cVar1 = *pcVar3, in_EAX = pcVar3, cVar1 != '\0'));
  }
  return;
}

