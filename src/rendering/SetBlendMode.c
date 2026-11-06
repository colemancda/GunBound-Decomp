/* SetBlendMode - 0x004f01d0 in the original binary.
 *
 * NAMED (batch 36). Selects the D3D7 alpha-blend mode, cached in
 * g_currentBlendMode (0x793614, see globals.h) so SetRenderState is only
 * re-issued on a change. The mode arrives in EAX (`cmp [0x793614],eax`).
 * Mode 0 or 1 sets D3DRENDERSTATE_SRCBLEND (0x13) = SRCALPHA (5) and
 * DESTBLEND (0x14) = INVSRCALPHA (6) through vtable offset +0x50
 * (SetRenderState); mode 2 sets SRCBLEND = SRCALPHA and DESTBLEND = ONE (2),
 * the additive blend.
 *
 * Callers: RenderWeatherHazards passes `(flag != 0) + 1` (so 1 or 2) before
 * drawing the layer-100 water effect, and FUN_004f3ee0 passes a byte it
 * loaded from its stack just before the DrawPrimitive. GameTick inlines the
 * mode-1 half of the same sequence (SetRenderState 0x13/0x14 with 5/6)
 * rather than calling this.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void SetBlendMode(int regEax)

{
  
  if (g_currentBlendMode != regEax) {
    _DAT_00792194 = regEax;
    g_currentBlendMode = regEax;
    if ((regEax == 0) || (regEax == 1)) {
      (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x13,5);
      (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x14,6);
    }
    else if (regEax == 2) {
      (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x13,5);
      (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x14,2);
      return;
    }
  }
  return;
}

