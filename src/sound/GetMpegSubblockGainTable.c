/* GetMpegSubblockGainTable - 0x00518550 in the original binary.
 *
 * Return the address of the Layer III subblock-gain table (0x5b01c4).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * Disassembly of 0x518550: mov eax,0x5b01c4; ret. The only caller,
 * InitMpegLayerIIITables, fills 8 floats there with pow(2, i*-2.0)
 * (constant at 0x544ab0 read from the binary), the ISO window-switching
 * gain 2^(-2*subblock_gain) for subblock_gain 0..7. The dequantiser at
 * 0x518560 loads three per-window values from the granule and multiplies
 * by [ebx*4+0x5b01c4] for each (disasm 0x518728-0x518731, loop count 3,
 * one per short window).
 */
#include "ghidra_types.h"


undefined * GetMpegSubblockGainTable(void)

{
  return &DAT_005b01c4;
}

