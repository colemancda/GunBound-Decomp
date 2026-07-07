/* FUN_004f4810 - 0x004f4810 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * __fastcall FUN_004f4810(float *param_1)

{
  float *in_EAX;
  
  _DAT_005a955c =
       _DAT_00557fb0 /
       (in_EAX[7] * param_1[1] + in_EAX[3] * *param_1 + in_EAX[0xb] * param_1[2] + in_EAX[0xf]);
  _DAT_005a9550 =
       (*in_EAX * *param_1 + in_EAX[4] * param_1[1] + in_EAX[8] * param_1[2] + in_EAX[0xc]) *
       _DAT_005a955c;
  _DAT_005a9554 =
       _DAT_005a955c *
       (in_EAX[5] * param_1[1] + in_EAX[1] * *param_1 + in_EAX[9] * param_1[2] + in_EAX[0xd]);
  _DAT_005a9558 =
       (in_EAX[6] * param_1[1] + in_EAX[2] * *param_1 + in_EAX[10] * param_1[2] + in_EAX[0xe]) *
       _DAT_005a955c;
  return &DAT_005a9550;
}

