/* DrawVLine - 0x004eb6b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REG FIX (2026-08-28): every input to this function is a
 * register. 0x4eb715 is a bare `ret` and the body contains no [esp+N]
 * read at all - contrast the twin DrawHLine, whose `movzx ecx,word ptr
 * [esp+8]` at 0x4eb613 does take its colour on the stack - so the
 * declared one-parameter __fastcall list is arity-correct and the three
 * recovered registers APPEND after it rather than displacing anything.
 *
 * ECX -> param_1  the run length: the loop counter (`dec ecx` 0x4eb705,
 *                 `jne` 0x4eb712), the value both clip clamps adjust
 *                 (`add ecx,eax` 0x4eb6d7, `mov ecx,edx` 0x4eb6ed), and
 *                 the subject of the `test ecx,ecx / jle` gate.
 * EAX -> regEax   the start row y: first touched at 0x4eb6d1 by
 *                 `cmp eax,edx` against g_clipMinY.
 * BX  -> regEbx   the 16bpp pixel: read at 0x4eb706 by
 *                 `mov word ptr [eax],bx`, never written in the body.
 *                 The parameter is a full int so that call sites can
 *                 hand over a 32-bit colour without a cast under an
 *                 unprototyped declaration; the body keeps the 16-bit
 *                 truncation Ghidra modelled.
 * EDI -> regEdi   the column x: first touched at 0x4eb6bb by
 *                 `cmp edi,[0x56df30]` against g_clipMaxX.
 *
 * None of the three is written anywhere in 0x4eb6b0..0x4eb715; the only
 * register traffic is the balanced `push ebp`/`pop ebp` around the
 * overflow test and the `push esi`/`pop esi` frame pair, so there are no
 * phantoms here.
 *
 * All 6 ported sites pass all four arguments. The 8 binary sites are
 * four PAIRS, each drawing the two vertical sides of a rectangle
 * outline right after two DrawHLine calls draw the horizontals; EBX is
 * loaded once per pair and stays live across both calls, which is why
 * callsite_regs.py sees it set at only some rows. The 8-vs-6 gap is the
 * 0x40cb92/0x40cba8 pair, which lives in an unported function at
 * 0x40ca20 inside the PROGRESS.csv gap 0x40ca20..0x40cc50.
 */
#include "ghidra_types.h"


void __fastcall DrawVLine(int param_1,int regEax,int regEbx,int regEdi)

{
  int in_EAX = regEax;
  undefined2 *puVar1;
  undefined2 unaff_BX = (undefined2)regEbx;
  int unaff_EDI = regEdi;
  
  if (((g_screenSurface != 0) && (unaff_EDI <= g_clipMaxX)) && (g_clipMinX <= unaff_EDI)) {
    if (in_EAX < g_clipMinY) {
      param_1 = param_1 + (in_EAX - g_clipMinY);
      in_EAX = g_clipMinY;
    }
    if (g_clipMaxY < in_EAX + param_1) {
      param_1 = (g_clipMaxY - in_EAX) + 1;
    }
    if ((0 < param_1) &&
       (puVar1 = (undefined2 *)(g_screenSurface + (g_screenPitch * in_EAX + unaff_EDI) * 2), 0 < param_1
       )) {
      do {
        param_1 = param_1 + -1;
        *puVar1 = unaff_BX;
        puVar1 = puVar1 + g_screenPitch;
      } while (param_1 != 0);
    }
  }
  return;
}

