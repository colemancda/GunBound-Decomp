/* SinDegrees - 0x004ead70 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004ead70 mean this function.)
 *
 * NAMED (2026-11-05), HIGH. Evidence from outside the body: Disasm
 * 0x4ead70-0x4ead85: angle in EAX, cdq/idiv 0x168 (360), a negative
 * remainder wrapped by adding 360, then fld dword ptr [edx*4 + 0x54c240]
 * leaves the float in ST0. 0x54c240 is g_sineTable360, the same table
 * BuildRotatedSpriteQuad128, BuildScaledSpriteQuad, BuildSizedSpriteQuad
 * and BuildSquareSpriteQuad index with angle%0x168, so it is sine over
 * whole degrees. Every binary caller (State11_InBattle_HandleFireInput x3,
 * State11_InBattle_HandleMouseInput x3, RenderMobile; callsite_regs shows
 * eax set at 6 of 7) loads an angle into EAX, calls this, hands the x87
 * result straight to FloatToInt64 and adds or subtracts the integer on a
 * position cell, always right after the +0x5a twin CosDegrees (0x4ead90,
 * cos a = sin(a+90)). FIXED (2026-11-05): the old port declared int f(void)
 * and returned in_EAX / 0x168, wrong on three counts (the angle is a register
 * argument, the operation is a wrapped modulus used as a table index, and the
 * result is a float in ST0). It is now float SinDegrees(int angle); the EAX
 * register argument is promoted to a real parameter because MSVC cannot
 * express EAX. Every call site now passes the angle: the wrapped sum
 * (peek A + peek B, or 180 - peek B - peek A) built just before the call.
 */
#include "ghidra_types.h"
#include "globals.h"

float SinDegrees(int angle)
{
  int idx = angle % 0x168;

  if (idx < 0) {
    idx += 0x168;
  }
  return g_sineTable360[idx];
}
