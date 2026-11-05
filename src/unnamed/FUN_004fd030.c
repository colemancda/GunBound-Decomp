/* FUN_004fd030 - 0x004fd030 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * ABI (2026-11-05): the message type arrives in AX (0x4fd030 `movzx eax,ax`,
 * then add 0xffff3fef / cmp 0x32 / ja and a byte-indexed jump table at
 * 0x4fd05c). Decoding the table, exactly 0xc011, 0xc018, 0xc041, 0xc042 and
 * 0xc043 select the `mov al,1` arm; everything else returns 0 in AL. The port
 * read an uninitialised in_AX; it is now the trailing parameter regAx. Its
 * result is the CL byte of FUN_00502650's frame header (callers do
 * `mov cl,al`).
 */
#include "ghidra_types.h"


undefined4 FUN_004fd030(unsigned short regAx)

{
  switch(regAx) {
  case 0xc011:
  case 0xc018:
  case 0xc041:
  case 0xc042:
  case 0xc043:
    return 1;
  default:
    return 0;
  }
}

