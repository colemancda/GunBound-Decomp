/* FUN_004f2530 - 0x004f2530 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_004f2530(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  fVar1 = _DAT_00557fb0 /
          ((param_1[9] * param_1[4] - param_1[8] * param_1[5]) * param_1[2] +
          ((param_1[5] * param_1[10] - param_1[9] * param_1[6]) * *param_1 -
          (param_1[4] * param_1[10] - param_1[8] * param_1[6]) * param_1[1]));
  if (_DAT_0054c870 <= ABS(fVar1 - _DAT_00557fb0)) {
    *param_2 = (param_1[5] * param_1[10] - param_1[9] * param_1[6]) * fVar1;
    param_2[1] = -((param_1[1] * param_1[10] - param_1[9] * param_1[2]) * fVar1);
    param_2[2] = (param_1[1] * param_1[6] - param_1[2] * param_1[5]) * fVar1;
    param_2[4] = -((param_1[4] * param_1[10] - param_1[8] * param_1[6]) * fVar1);
    param_2[5] = (*param_1 * param_1[10] - param_1[8] * param_1[2]) * fVar1;
    param_2[6] = -((*param_1 * param_1[6] - param_1[4] * param_1[2]) * fVar1);
    param_2[8] = (param_1[9] * param_1[4] - param_1[8] * param_1[5]) * fVar1;
    param_2[9] = -((param_1[9] * *param_1 - param_1[8] * param_1[1]) * fVar1);
    param_2[10] = (param_1[5] * *param_1 - param_1[4] * param_1[1]) * fVar1;
  }
  else {
    *param_2 = *param_1;
    param_2[1] = param_1[4];
    param_2[2] = param_1[8];
    param_2[4] = param_1[1];
    param_2[5] = param_1[5];
    param_2[6] = param_1[9];
    param_2[8] = param_1[2];
    param_2[9] = param_1[6];
    param_2[10] = param_1[10];
  }
  param_2[0xb] = 0.0;
  param_2[7] = 0.0;
  param_2[3] = 0.0;
  param_2[0xc] = -(param_1[0xe] * param_2[8] + *param_2 * param_1[0xc] + param_1[0xd] * param_2[4]);
  param_2[0xd] = -(param_2[9] * param_1[0xe] + param_2[1] * param_1[0xc] + param_1[0xd] * param_2[5]
                  );
  fVar1 = param_1[0xd];
  fVar2 = param_1[0xc];
  fVar3 = param_1[0xe];
  param_2[0xf] = 1.0;
  param_2[0xe] = -(param_2[10] * fVar3 + param_2[2] * fVar2 + fVar1 * param_2[6]);
  return;
}

