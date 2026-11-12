/* GetMpegImdctLongTables - 0x0051c660 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section. (Previously FUN_0051c660.)
 *
 * Evidence for the name (all from outside the body):
 * Disassembly of 0x51c660: mov eax,0x568800; ret. 0x568800 is a 16-byte
 * record of pointers whose raw bytes in the binary are 0xf25900, 0xf25960,
 * 0xf259a0, 0 (read from the image). Its sole caller, InitMpegImdctKernelTables
 * (0x519ef0), takes elements 0..2 and fills them with 18, 9 and 36 cosine
 * factors built from the divisors 72.0 and 36.0 (constants at 0x544af0 and
 * 0x544ae0), i.e. 36-point IMDCT constants. The consumers are the long-block
 * IMDCT bodies (MpegImdct36 at 0x51b030 loads edi=0xf25900, esi=0xf25960,
 * ecx=0xf259a0 at its entry, and the inlined copy in the function at
 * 0x51b667 uses the same constants), so the record is the long-block (36
 * point) table set, as opposed to the 12-point set at 0x568810 returned by
 * GetMpegImdctShortTables. The accessor shape matches GetMpegImdctWindowTable.
 */
#include "ghidra_types.h"


undefined ** GetMpegImdctLongTables(void)

{
  return &PTR_DAT_00568800;
}

