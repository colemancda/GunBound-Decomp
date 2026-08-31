/* FUN_004f3a60 - 0x004f3a60 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * __fastcall FUN_004f3a60(float *param_1,float *regEax)

{
  
  _DAT_005a94b0 =
       (param_1[3] * *regEax + param_1[1] * regEax[2] + regEax[3] * *param_1) -
       param_1[2] * regEax[1];
  _DAT_005a94b4 =
       (param_1[2] * *regEax + regEax[3] * param_1[1] + param_1[3] * regEax[1]) -
       *param_1 * regEax[2];
  _DAT_005a94b8 =
       (regEax[1] * *param_1 + regEax[3] * param_1[2] + param_1[3] * regEax[2]) -
       param_1[1] * *regEax;
  _DAT_005a94bc =
       ((param_1[3] * regEax[3] - *regEax * *param_1) - regEax[1] * param_1[1]) -
       param_1[2] * regEax[2];
  return (undefined *)DAT_005a94b0;
}

