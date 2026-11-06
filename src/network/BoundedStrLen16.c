/* BoundedStrLen16 - 0x004f7360 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004f7360 mean this function.)
 *
 * Evidence (HIGH on behaviour). ECX is a char pointer; the result is the
 * count of leading nonzero bytes, capped at 0x10 (orig 0x4f7360-0x4f7373:
 * scan, return 0x10 if the 16th byte is still nonzero). Both callers are
 * in CommP2PReceiveDatagram (orig 0x4ffa66 and 0x4ffa87, ECX = a stack
 * buffer inside the received datagram) and use the AL result,
 * zero-extended, as the length argument of Sha1Absorb (0x4f7380) on that
 * same buffer. The port has no call sites: it inlines the loop as
 * gb_capped16_len. Behaves as strnlen(s, 0x10); the name states only
 * that, not what the field is.
 */
#include "ghidra_types.h"


byte __fastcall BoundedStrLen16(int param_1)

{
  byte bVar1;
  
  bVar1 = 0;
  do {
    if (*(char *)((uint)bVar1 + param_1) == '\0') {
      return bVar1;
    }
    bVar1 = bVar1 + 1;
  } while (bVar1 < 0x10);
  return 0x10;
}

