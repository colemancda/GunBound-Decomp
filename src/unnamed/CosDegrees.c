/* CosDegrees - 0x004ead90 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004ead90 mean this function.)
 *
 * NAMED (2026-11-05), HIGH. Evidence from outside the body: Disasm
 * 0x4ead90-0x4eada8: identical to SinDegrees (0x4ead70) except add
 * eax,0x5a comes first, i.e. cos a = sin(a + 90) read from g_sineTable360
 * (0x54c240), result in ST0. Callers (RenderMobile,
 * State11_InBattle_HandleFireInput x3, State11_InBattle_HandleMouseInput
 * x3, FUN_0045cb50, Mobile.cpp) call this and then SinDegrees back to
 * back, each followed by FloatToInt64. FIXED (2026-11-05): was int f(void)
 * returning (in_EAX + 0x5a) / 0x168, dropping the EAX angle argument and the
 * float ST0 result; now float CosDegrees(int angle), see SinDegrees.
 */
#include "ghidra_types.h"
#include "globals.h"

float CosDegrees(int angle)
{
  int idx = (angle + 0x5a) % 0x168;

  if (idx < 0) {
    idx += 0x168;
  }
  return g_sineTable360[idx];
}
