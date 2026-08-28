/* DrawHLine - 0x004eb5d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REG FIX (2026-08-28): this is instruction-for-instruction
 * DrawBlendedHLine (0x4eb640) with FillPixels16 where that one calls
 * BlendPixels16, so the sibling's already-landed signature transfers
 * verbatim, and the disassembly confirms it independently:
 *
 * ECX -> param_1  PHANTOM. Its first touch is the WRITE
 *                 `mov ecx,[0x793530]` at 0x4eb5eb, so nothing arrives
 *                 in it.
 * EDX -> param_2  the run length, already correctly slotted: adjusted by
 *                 both clip clamps (0x4eb5f7, 0x4eb60d) and gated by
 *                 `test edx,edx / jle` at 0x4eb60f.
 * [entry+4]
 *     -> param_3  the 16bpp colour, already correctly slotted:
 *                 `movzx ecx,word ptr [esp+8]` at 0x4eb613 with only
 *                 `push esi` outstanding.
 * EAX -> regEax   the starting column x: read at 0x4eb5f1 against
 *                 g_clipMinX before any write.
 * EDI -> regEdi   the row y: read at 0x4eb5db against g_clipMaxY.
 *
 * 0x4eb632 is a bare `ret`, so the caller cleans that one stack word -
 * both real callers push it for BOTH of their calls and retire the pair
 * with a single later `add esp,8`. ret N therefore says nothing about
 * the count here; the count comes from the single [esp+8] read.
 *
 * From the call sites' side this was a RE-SLOT. Two of the four ported
 * sites passed exactly one argument, `DrawHLine(0xf800)`, and 0xf800 is
 * the COLOUR - so it was landing in the phantom ECX slot while the run
 * length, column and row were all absent; the other two passed nothing.
 * The 6-vs-4 gap is 0x40cb67/0x40cb7a, in the unported function at
 * 0x40ca20 inside the PROGRESS.csv gap 0x40ca20..0x40cc50.
 */
#include "ghidra_types.h"


void __fastcall DrawHLine(undefined4 param_1,int param_2,int param_3,int regEax,int regEdi)

{
  int in_EAX = regEax;
  int unaff_EDI = regEdi;
  
  if (((g_screenSurface != 0) && (unaff_EDI <= g_clipMaxY)) && (g_clipMinY <= unaff_EDI)) {
    if (in_EAX < g_clipMinX) {
      param_2 = param_2 + (in_EAX - g_clipMinX);
      in_EAX = g_clipMinX;
    }
    if (g_clipMaxX < in_EAX + param_2) {
      param_2 = (g_clipMaxX - in_EAX) + 1;
    }
    if (0 < param_2) {
      FillPixels16(g_screenSurface + (g_screenPitch * unaff_EDI + in_EAX) * 2,param_3,param_2);
    }
  }
  return;
}

