/* FUN_00514af0 - 0x00514af0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00514af0(int param_1)

{
  byte bVar1;
  
  if (DAT_00f25e04 < param_1) {
    for (; DAT_00f25e04 < 0x19; DAT_00f25e04 = DAT_00f25e04 + 8) {
      DAT_00f25e00 = DAT_00f25e00 << 8 | (uint)*DAT_00f25e08;
      DAT_00f25e08 = DAT_00f25e08 + 1;
    }
  }
  bVar1 = (byte)(DAT_00f25e04 - param_1);
  DAT_00f25e04 = DAT_00f25e04 - param_1;
  DAT_00f25e00 = DAT_00f25e00 - ((DAT_00f25e00 >> (bVar1 & 0x1f)) << (bVar1 & 0x1f));
  return;
}

