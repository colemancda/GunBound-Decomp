/* TickTornadoHazardFrame - 0x004ac750 in the original binary.
 *
 * NAMED (2026-07-16): the Tornado hazard's per-frame animation tick -
 * vtable slot 2 (+0x8) of PTR_FUN_005565e4. Literally increments the
 * animation frame counter at this+0x480; RenderTornadoHazard reads that
 * counter to drive the swirl rotation. Appears only in the Tornado
 * vtable (Firewall/Lightning share their own +0x484 copy,
 * TickWeatherHazardFrame). See InitTornadoHazard.c for the field map.
 * Raw port of the 2-instruction original (`inc [ecx+0x480]; ret`).
 */
#include "ghidra_types.h"


void __fastcall TickTornadoHazardFrame(int param_1)

{
  *(int *)(param_1 + 0x480) = *(int *)(param_1 + 0x480) + 1;
  return;
}
