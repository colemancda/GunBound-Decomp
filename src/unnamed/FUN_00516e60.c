/* FUN_00516e60 - 0x00516e60 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00516e60(int param_1,int param_2,int param_3)

{
  if (0 < param_3) {
    do {
      FUN_0051ad70(param_1,&DAT_005af144 + DAT_005ae93c);
      FUN_0051af30(&DAT_005af144,DAT_005ae93c,param_2);
      param_1 = param_1 + 0x100;
      param_2 = param_2 + 0x10;
      DAT_005ae93c = DAT_005ae93c - 8 & 0x7f;
      param_3 = param_3 + -1;
    } while (param_3 != 0);
  }
  return;
}

