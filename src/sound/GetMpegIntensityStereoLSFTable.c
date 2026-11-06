/* GetMpegIntensityStereoLSFTable - 0x005180f0 in the original binary.
 *
 * Return the address of the LSF intensity-stereo ratio table (0x5af944).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * Disassembly of 0x5180f0: mov eax,0x5af944; ret. The only caller is the
 * builder at 0x51a230, which fills 0x800 bytes there (0x5af944..0x5b0143,
 * directly below the MPEG-1 table at 0x5b0144) with pairs scaled by
 * powers of 2^-0.25 and 2^-0.5 (pow(2, -(i+1)*0.25), constant at 0x544af8
 * read from the binary), the ISO 13818-3 LSF intensity scales. The
 * consumer is ApplyMpegIntensityStereoLSF, which indexes 0x5af944 in
 * 8-byte pairs (disasm 0x51830f), so the table's role is corroborated
 * from the consumer side.
 */
#include "ghidra_types.h"


undefined * GetMpegIntensityStereoLSFTable(void)

{
  return &DAT_005af944;
}

