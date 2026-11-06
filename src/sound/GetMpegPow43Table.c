/* GetMpegPow43Table - 0x00518540 in the original binary.
 *
 * Return the address of the Layer III x^(4/3) requantisation table
 * (0x5b12fc).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * Disassembly of 0x518540: mov eax,0x5b12fc; ret. The only caller,
 * InitMpegLayerIIITables, fills 64 floats there with |x|^(1/3)*x for x =
 * i-32, i.e. the signed x^(4/3) of the ISO Layer III requantiser. The
 * dequantiser at 0x518560 reads it as [eax*4+0x5b137c] (disasm 0x518665,
 * 0x51881c): the base plus 0x80 is entry 32 (x = 0), so the decoded
 * integer value indexes it signed.
 */
#include "ghidra_types.h"


undefined * GetMpegPow43Table(void)

{
  return &DAT_005b12fc;
}

