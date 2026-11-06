/* GetMpegGlobalGainTable - 0x00518520 in the original binary.
 *
 * Return the address of the Layer III global-gain table (0x5b01e4).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * Disassembly of 0x518520: mov eax,0x5b01e4; ret. The only caller,
 * InitMpegLayerIIITables, fills 0x106 floats there with pow(2,
 * (i-0x9c)*0.25) (constant at 0x544ac0 read from the binary): a
 * quarter-step exponential, the shape of the ISO global_gain scale
 * (offset differs from the ISO -210 by a fixed output scaling). The
 * dequantiser at 0x518560 reads it as [side_info[+8]*4 + 0x5b01fc], i.e.
 * table base + 0x18, indexed by the granule's field at +8 (disasm 0x5185b5
 * and 0x5185c2). The 0x5b01e4 base itself has no direct reader; the
 * consumer uses the +6 biased address.
 */
#include "ghidra_types.h"


undefined * GetMpegGlobalGainTable(void)

{
  return &DAT_005b01e4;
}

