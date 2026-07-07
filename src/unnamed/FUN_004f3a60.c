/* FUN_004f3a60 - 0x004f3a60 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * __fastcall FUN_004f3a60(float *param_1)

{
  float *in_EAX;
  
  _DAT_005a94b0 =
       (param_1[3] * *in_EAX + param_1[1] * in_EAX[2] + in_EAX[3] * *param_1) -
       param_1[2] * in_EAX[1];
  _DAT_005a94b4 =
       (param_1[2] * *in_EAX + in_EAX[3] * param_1[1] + param_1[3] * in_EAX[1]) -
       *param_1 * in_EAX[2];
  _DAT_005a94b8 =
       (in_EAX[1] * *param_1 + in_EAX[3] * param_1[2] + param_1[3] * in_EAX[2]) -
       param_1[1] * *in_EAX;
  _DAT_005a94bc =
       ((param_1[3] * in_EAX[3] - *in_EAX * *param_1) - in_EAX[1] * param_1[1]) -
       param_1[2] * in_EAX[2];
  return &DAT_005a94b0;
}

