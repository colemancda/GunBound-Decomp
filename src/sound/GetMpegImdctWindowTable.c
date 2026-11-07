/* GetMpegImdctWindowTable - 0x00517d00 in the original binary.
 *
 * Return the address of the Layer III IMDCT window table (0xf25b00).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * Disassembly of 0x517d00: mov eax,0xf25b00; ret. The only caller is
 * InitMpegImdctWindows (0x519c80, called from InitMpegLayerIIITables),
 * which fills 4 x 36 floats there: sin((i+0.5)*pi/36) for the long window,
 * the 12-point short sine, and the start/stop shapes with 1.0 and 0.0
 * runs. The consumer is the windowed overlap-add body at 0x51b667 (reached
 * through the 0x517d10 wrapper), which reads the table as [0xf25b00 +
 * block_type*0x24 + k] (disasm 0x51b683 and the 0x24-float stride per
 * block type), so the table identity is corroborated from the consumer
 * side.
 */
#include "ghidra_types.h"


undefined4 * GetMpegImdctWindowTable(void)

{
  return (undefined4 *)g_mpegImdctWinTab;
}

