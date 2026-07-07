/* FUN_004f2240 - 0x004f2240 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004f2240(void)

{
  char cVar1;
  float *in_EAX;
  int iVar2;
  float *unaff_EBX;
  float *pfVar3;
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
  
  local_40[0] = unaff_EBX[3] * in_EAX[0xc] +
                *in_EAX * *unaff_EBX + in_EAX[4] * unaff_EBX[1] + in_EAX[8] * unaff_EBX[2];
  local_40[1] = in_EAX[1] * *unaff_EBX +
                in_EAX[9] * unaff_EBX[2] + in_EAX[5] * unaff_EBX[1] + in_EAX[0xd] * unaff_EBX[3];
  local_40[2] = in_EAX[10] * unaff_EBX[2] +
                in_EAX[6] * unaff_EBX[1] + unaff_EBX[3] * in_EAX[0xe] + in_EAX[2] * *unaff_EBX;
  local_30 = in_EAX[8] * unaff_EBX[6] +
             unaff_EBX[7] * in_EAX[0xc] + unaff_EBX[4] * *in_EAX + in_EAX[4] * unaff_EBX[5];
  local_2c = in_EAX[1] * unaff_EBX[4] +
             unaff_EBX[6] * in_EAX[9] + unaff_EBX[7] * in_EAX[0xd] + in_EAX[5] * unaff_EBX[5];
  local_28 = in_EAX[2] * unaff_EBX[4] +
             in_EAX[6] * unaff_EBX[5] + unaff_EBX[6] * in_EAX[10] + unaff_EBX[7] * in_EAX[0xe];
  local_20 = unaff_EBX[8] * *in_EAX +
             in_EAX[0xc] * unaff_EBX[0xb] + in_EAX[4] * unaff_EBX[9] + in_EAX[8] * unaff_EBX[10];
  local_1c = in_EAX[5] * unaff_EBX[9] +
             in_EAX[9] * unaff_EBX[10] + in_EAX[0xd] * unaff_EBX[0xb] + in_EAX[1] * unaff_EBX[8];
  local_18 = in_EAX[10] * unaff_EBX[10] +
             in_EAX[0xe] * unaff_EBX[0xb] + unaff_EBX[8] * in_EAX[2] + in_EAX[6] * unaff_EBX[9];
  local_10 = unaff_EBX[0xc] * *in_EAX +
             unaff_EBX[0xf] * in_EAX[0xc] + in_EAX[8] * unaff_EBX[0xe] + in_EAX[4] * unaff_EBX[0xd];
  local_c = unaff_EBX[0xc] * in_EAX[1] +
            unaff_EBX[0xd] * in_EAX[5] + unaff_EBX[0xe] * in_EAX[9] + in_EAX[0xd] * unaff_EBX[0xf];
  local_8 = unaff_EBX[0xd] * in_EAX[6] +
            unaff_EBX[0xe] * in_EAX[10] + unaff_EBX[0xf] * in_EAX[0xe] + unaff_EBX[0xc] * in_EAX[2];
  if (ABS(in_EAX[0xb]) < _DAT_0054c870) {
    if (ABS(in_EAX[0xf] - _DAT_00557fb0) < _DAT_0054c870) {
      if (ABS(in_EAX[3]) < _DAT_0054c870) {
        cVar1 = FUN_004e9490(in_EAX[7]);
        if (cVar1 != '\0') {
          local_40[3] = unaff_EBX[3];
          local_24 = unaff_EBX[7];
          local_4 = unaff_EBX[0xf];
          local_14 = unaff_EBX[0xb];
          pfVar3 = local_40;
          for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
            *unaff_EBX = *pfVar3;
            pfVar3 = pfVar3 + 1;
            unaff_EBX = unaff_EBX + 1;
          }
          return;
        }
      }
    }
  }
  local_40[3] = in_EAX[3] * *unaff_EBX +
                in_EAX[7] * unaff_EBX[1] + unaff_EBX[3] * in_EAX[0xf] + in_EAX[0xb] * unaff_EBX[2];
  local_24 = in_EAX[3] * unaff_EBX[4] +
             in_EAX[7] * unaff_EBX[5] + unaff_EBX[6] * in_EAX[0xb] + unaff_EBX[7] * in_EAX[0xf];
  local_14 = in_EAX[0xf] * unaff_EBX[0xb] +
             in_EAX[0xb] * unaff_EBX[10] + in_EAX[3] * unaff_EBX[8] + in_EAX[7] * unaff_EBX[9];
  local_4 = unaff_EBX[0xd] * in_EAX[7] +
            in_EAX[0xb] * unaff_EBX[0xe] + unaff_EBX[0xc] * in_EAX[3] + unaff_EBX[0xf] * in_EAX[0xf]
  ;
  pfVar3 = local_40;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *unaff_EBX = *pfVar3;
    pfVar3 = pfVar3 + 1;
    unaff_EBX = unaff_EBX + 1;
  }
  return;
}

