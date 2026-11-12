/* GetMpegImdctShortTables - 0x0051c670 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section. (Previously FUN_0051c670.)
 *
 * Evidence for the name (all from outside the body):
 * Disassembly of 0x51c670: mov eax,0x568810; ret. The record at 0x568810
 * holds, in the binary image, 0xf258c0, 0xf258e0 and 0xf25a30. Its sole
 * caller, InitMpegImdctKernelTables (0x519ef0), fills the first two with
 * 6 and 3 cosine factors built from the divisors 24.0 and 12.0 (constants at
 * 0x544ae8 and 0x544ad8) and the third with one scalar, i.e. 12-point
 * IMDCT constants. The short-block kernel MpegImdct12 (0x51b436) loads
 * edi=0xf258c0 and esi=0xf258e0 at its entry and multiplies by the scalar at
 * 0xf25a30, so the record is the short-block (12 point) table set, the
 * counterpart of GetMpegImdctLongTables.
 */
#include "ghidra_types.h"


undefined ** GetMpegImdctShortTables(void)

{
  return &PTR_DAT_00568810;
}

