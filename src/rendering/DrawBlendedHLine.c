/* DrawBlendedHLine - 0x004eb640 in the original binary.
 *
 * Draws a horizontal run of additively-blended pixels - the blending twin of
 * DrawHLine.
 *
 * The two are the same function bar the final write.  DrawHLine and this share
 * their clip logic exactly, down to which globals bound which axis:
 *
 *   edi <= g_clipMaxY && g_clipMinY <= edi     the row, against the Y clip
 *   eax clamped into [g_clipMinX, g_clipMaxX]  the span, against the X clip
 *
 * and both then write at g_screenSurface + (g_screenPitch * row + col) * 2.
 * DrawHLine passes that to FillPixels16; this passes it to BlendPixels16.
 * DrawBlendedVLine is the vertical member of the same set, with the two axis
 * pairs transposed.
 *
 * DROPPED REGISTER ARGUMENTS RECOVERED.  This is the horizontal half of a
 * crosshair pair with DrawBlendedVLine (the vertical half): this one emits a
 * single run of param_2 pixels, while 0x4eb720 loops the same write down
 * param_2 rows.
 *
 * Ghidra typed this __fastcall, so param_1 occupies the ECX slot -- but the
 * body never reads param_1 (it appears exactly once, in the signature), and
 * the callee loads its own ECX from the stack at `movzx ecx,[esp+8]`.  ECX is
 * therefore a PHANTOM, not an argument, the same shape as RemoveWidget's.
 * The real incoming values are EDI, EAX, EDX and one stack word.
 *
 * From the sole call site, at 0x00458b37:
 *   xor eax,eax / mov ax,[esi+0x48] / push eax  -> param_3 = label (stack)
 *   edi = [esi+0x3c] - camY + 0x12a             -> regEdi  = y1  (the row)
 *   eax = [esi+0x38] - camX + 0x18f             -> regEax  = x1  (the column)
 *   mov edx,3                                   -> param_2 = 3   (run length)
 * The caller pushes for BOTH calls and cleans them with a single `add esp,8`
 * after the second, which is why the stack argument is easy to miss.
 *
 * The port had been passing (3, x1, y1, label) -- four arguments to a
 * three-parameter definition, with the run length first as though it were a
 * mode selector.  functions.h declared it K&R-empty, so nothing diagnosed it.
 */
#include "ghidra_types.h"


void __fastcall DrawBlendedHLine(undefined4 param_1,int param_2,int param_3,int regEax,
                             int regEdi)

{
  
  if (((g_screenSurface != 0) && (regEdi <= g_clipMaxY)) && (g_clipMinY <= regEdi)) {
    if (regEax < g_clipMinX) {
      param_2 = param_2 + (regEax - g_clipMinX);
      regEax = g_clipMinX;
    }
    if (g_clipMaxX < regEax + param_2) {
      param_2 = (g_clipMaxX - regEax) + 1;
    }
    if (0 < param_2) {
      BlendPixels16(g_screenSurface + (g_screenPitch * regEdi + regEax) * 2,param_3,param_2);
    }
  }
  return;
}

