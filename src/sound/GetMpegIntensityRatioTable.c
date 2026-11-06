/* GetMpegIntensityRatioTable - 0x005180e0 in the original binary.
 *
 * Return the address of the MPEG-1 intensity-stereo ratio table
 * (0x5b0144).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * Disassembly of 0x5180e0: mov eax,0x5b0144; ret. The only caller is the
 * table builder at 0x51a120, which fills 0x5b0144 with tan-derived l/r
 * position ratios (angles i*pi/12, l = tan/(1+tan), r = 1/(1+tan)). The
 * consumer is ApplyMpegIntensityStereo, which indexes the same table at
 * +0x5b0144/+0x5b0148 (disasm 0x5181c7, 0x5181cd, 0x518295, 0x51829b), so
 * the table's role is corroborated from the consumer side.
 */
#include "ghidra_types.h"


undefined * GetMpegIntensityRatioTable(void)

{
  return &DAT_005b0144;
}

