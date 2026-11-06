/* GetMpegScalefactorGainTable - 0x00518530 in the original binary.
 *
 * Return the address of the Layer III scalefactor gain table (0x5b0efc).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * Disassembly of 0x518530: mov eax,0x5b0efc; ret. The only caller,
 * InitMpegLayerIIITables, fills 256 floats there (0x5b0efc..0x5b12fb, two
 * scale settings x 4 x 32) with pow(2, (n+m)*s*-0.5), the ISO
 * scalefactor_scale gain 2^(-0.5 or -1 times scalefactor). The dequantiser
 * at 0x518560 reads it directly as [eax*4+0x5b0efc] with eax = (row << 5)
 * + scalefactor (disasm 0x518600-0x518614, and again at 0x5187bb), so the
 * consumer indexes it per scalefactor band.
 */
#include "ghidra_types.h"


undefined * GetMpegScalefactorGainTable(void)

{
  return &DAT_005b0efc;
}

