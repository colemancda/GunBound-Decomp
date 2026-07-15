/* State11_InBattle_RenderWeatherHazards - 0x004c1d10 in the original
 * binary.
 *
 * Renamed with confidence: this is vtable_State11_InBattle's slot 12,
 * already identified and documented in ARCHITECTURE.md's "State 11
 * (In-Battle) full vtable map" - "One-line delegate - calls
 * RenderWeatherHazards on a fixed per-connection offset (+0x6a7f88),
 * nothing else." Matches the established State11_InBattle_<Role>
 * naming used for every other named slot in that same table (compare
 * State11_InBattle_ClearEffectTextures.c, slot 13's sibling file).
 *
 * vtable_State11_InBattle itself is still an unpopulated bring-up
 * placeholder (globals.c: `void *vtable_State11_InBattle[32];`, no
 * initializer) - wiring this and the other 17 confirmed slots into it
 * is a separate, larger task, not attempted here.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-
 * verified beyond the above. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void State11_InBattle_RenderWeatherHazards(void)

{
  RenderWeatherHazards(&DAT_006a7f88 + g_clientContext);
  return;
}
