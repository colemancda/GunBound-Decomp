/* ConsumeMpegBits - 0x00514af0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 ConsumeMpegBits(int param_1)

{
  uint uVar1;
  
  if (DAT_00f25e04 < param_1) {
    for (; DAT_00f25e04 < 0x19; DAT_00f25e04 = DAT_00f25e04 + 8) {
      DAT_00f25e00 = DAT_00f25e00 << 8 | (uint)*DAT_00f25e08;
      DAT_00f25e08 = DAT_00f25e08 + 1;
    }
  }
  DAT_00f25e04 = DAT_00f25e04 - param_1;
  /* 0x514b3e-0x514b4f: eax = bits >> cnt is the returned value (the next
   * param_1 bits); the remainder bits - (eax << cnt) stay in the buffer.
   * The port used to `return 0` here on the claim that no caller used the
   * result; every Layer III header and side-info reader does. */
  uVar1 = DAT_00f25e00 >> ((byte)DAT_00f25e04 & 0x1f);
  DAT_00f25e00 = DAT_00f25e00 - (uVar1 << ((byte)DAT_00f25e04 & 0x1f));
  return uVar1;
}
