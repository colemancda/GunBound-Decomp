/* QuantizeRefreshRate - 0x0040d200 in the original binary.
 *
 * NAMED (batch 36). Takes a display refresh rate in ECX and rounds it down
 * to the nearest supported bucket of the stack table {0, 60, 70, 75, 85,
 * 100} (below 60 -> 0, 60..69 -> 60, 70..74 -> 70, 75..84 -> 75, 85..99 ->
 * 85, 100 and up -> 100).
 *
 * Evidence is in the callers, all three in WinMain. Site 1 (0x40dd47) is
 * `push 0x74 / call GetDeviceCaps / mov ecx,eax` - 0x74 is VREFRESH, so
 * ECX is the monitor's refresh rate in Hz. Site 2 (0x40dd76) is
 * `push 0x10 / call ReadRegistryDword (0x40c470) / mov ecx,eax`, the
 * stored refresh-rate setting. Site 3 (0x40ddf8) is `mov ecx,esi` where
 * ESI is the GetDisplayConfigFromRegistry (0x40c620) result kept live from
 * 0x40dd6a. The result goes to DAT_00588f48 (site 1) and into
 * WriteRegistryDword (site 3).
 *
 * CALL SITES FIXED in the same commit: ECX was dropped at all three (the
 * prototype was a bare `()`).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


int __fastcall QuantizeRefreshRate(int param_1)

{
  uint uVar1;
  int aiStack_1c [7];
  
  aiStack_1c[1] = 0;
  aiStack_1c[2] = 0x3c;
  aiStack_1c[3] = 0x46;
  aiStack_1c[4] = 0x4b;
  aiStack_1c[5] = 0x55;
  aiStack_1c[6] = 100;
  uVar1 = 1;
  do {
    if (param_1 < aiStack_1c[uVar1 + 1]) {
      return aiStack_1c[uVar1];
    }
    uVar1 = uVar1 + 1;
  } while (uVar1 < 6);
  return 100;
}

