/* TickWeatherHazardFrame - 0x0046e010 in the original binary.
 *
 * NAMED (2026-07-16): the per-frame animation tick SHARED by the Firewall
 * and Lightning hazards - vtable slot 2 (+0x8) of both PTR_FUN_00555edc
 * (Firewall) and PTR_FUN_00555e74 (Lightning). Increments the animation
 * frame counter at this+0x484 (the +4-shifted layout those two hazards
 * use vs the Tornado's +0x480); RenderFirewallHazard/RenderLightningHazard
 * read it to drive the flame/bolt animation. Tornado has its own +0x480
 * copy (TickTornadoHazardFrame). See InitTornadoHazard.c for the field
 * map. Raw port of the 2-instruction original (`inc [ecx+0x484]; ret`).
 */
#include "ghidra_types.h"


void __fastcall TickWeatherHazardFrame(int param_1)

{
  *(int *)(param_1 + 0x484) = *(int *)(param_1 + 0x484) + 1;
  return;
}
