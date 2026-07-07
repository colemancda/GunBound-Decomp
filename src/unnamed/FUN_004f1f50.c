/* FUN_004f1f50 - 0x004f1f50 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * __fastcall FUN_004f1f50(float *param_1)

{
  char cVar1;
  float *in_EAX;
  int iVar2;
  float *pfVar3;
  float *pfVar4;
  float local_40 [4];
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  local_40[0] = param_1[3] * in_EAX[0xc] +
                *in_EAX * *param_1 + in_EAX[4] * param_1[1] + in_EAX[8] * param_1[2];
  local_40[1] = in_EAX[1] * *param_1 +
                in_EAX[9] * param_1[2] + in_EAX[5] * param_1[1] + in_EAX[0xd] * param_1[3];
  local_40[2] = in_EAX[10] * param_1[2] +
                in_EAX[6] * param_1[1] + param_1[3] * in_EAX[0xe] + in_EAX[2] * *param_1;
  local_30 = in_EAX[8] * param_1[6] +
             param_1[7] * in_EAX[0xc] + param_1[4] * *in_EAX + in_EAX[4] * param_1[5];
  local_2c = in_EAX[1] * param_1[4] +
             param_1[6] * in_EAX[9] + param_1[7] * in_EAX[0xd] + in_EAX[5] * param_1[5];
  local_28 = in_EAX[2] * param_1[4] +
             in_EAX[6] * param_1[5] + param_1[6] * in_EAX[10] + param_1[7] * in_EAX[0xe];
  local_20 = param_1[8] * *in_EAX +
             in_EAX[0xc] * param_1[0xb] + in_EAX[4] * param_1[9] + in_EAX[8] * param_1[10];
  local_1c = in_EAX[5] * param_1[9] +
             in_EAX[9] * param_1[10] + in_EAX[0xd] * param_1[0xb] + in_EAX[1] * param_1[8];
  local_18 = in_EAX[10] * param_1[10] +
             in_EAX[0xe] * param_1[0xb] + param_1[8] * in_EAX[2] + in_EAX[6] * param_1[9];
  local_10 = param_1[0xc] * *in_EAX +
             param_1[0xf] * in_EAX[0xc] + in_EAX[8] * param_1[0xe] + in_EAX[4] * param_1[0xd];
  local_c = param_1[0xc] * in_EAX[1] +
            param_1[0xd] * in_EAX[5] + param_1[0xe] * in_EAX[9] + in_EAX[0xd] * param_1[0xf];
  local_8 = param_1[0xd] * in_EAX[6] +
            param_1[0xe] * in_EAX[10] + param_1[0xf] * in_EAX[0xe] + param_1[0xc] * in_EAX[2];
  if (ABS(in_EAX[0xb]) < _DAT_0054c870) {
    if (ABS(in_EAX[0xf] - _DAT_00557fb0) < _DAT_0054c870) {
      if (ABS(in_EAX[3]) < _DAT_0054c870) {
        cVar1 = FUN_004e9490(in_EAX[7]);
        if (cVar1 != '\0') {
          local_40[3] = param_1[3];
          local_24 = param_1[7];
          local_14 = param_1[0xb];
          local_4 = param_1[0xf];
          goto LAB_004f221b;
        }
      }
    }
  }
  local_40[3] = in_EAX[3] * *param_1 +
                in_EAX[7] * param_1[1] + param_1[3] * in_EAX[0xf] + in_EAX[0xb] * param_1[2];
  local_24 = in_EAX[3] * param_1[4] +
             in_EAX[7] * param_1[5] + param_1[6] * in_EAX[0xb] + param_1[7] * in_EAX[0xf];
  local_14 = in_EAX[0xf] * param_1[0xb] +
             in_EAX[0xb] * param_1[10] + in_EAX[3] * param_1[8] + in_EAX[7] * param_1[9];
  local_4 = param_1[0xd] * in_EAX[7] +
            in_EAX[0xb] * param_1[0xe] + param_1[0xc] * in_EAX[3] + param_1[0xf] * in_EAX[0xf];
LAB_004f221b:
  pfVar3 = local_40;
  pfVar4 = (float *)&DAT_005a9350;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar4 = *pfVar3;
    pfVar3 = pfVar3 + 1;
    pfVar4 = pfVar4 + 1;
  }
  return &DAT_005a9350;
}

