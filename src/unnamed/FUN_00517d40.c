/* FUN_00517d40 - 0x00517d40 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_00517d40(int param_1,float *param_2,float *param_3,float *param_4,int param_5,int param_6)

{
  float fVar1;
  float fVar2;
  float *pfVar3;
  float *pfVar4;
  float *pfVar5;
  int iVar6;
  float *pfVar7;
  int iVar8;
  float *pfVar9;
  int iVar10;
  int iVar11;
  float *local_14;
  int local_10;
  int local_8;
  
  pfVar4 = param_2;
  if (param_4 == (float *)0x2) {
    param_4 = (float *)0x0;
  }
  iVar10 = (param_5 + 0x11) / 0x12;
  iVar6 = 0;
  pfVar3 = param_2;
  iVar11 = param_1;
  if (0 < iVar10) {
    param_2 = param_3;
    local_8 = iVar10;
    do {
      FUN_0051c680(param_1);
      local_10 = 9;
      pfVar3 = (float *)(param_1 + 0x24);
      pfVar5 = param_2;
      pfVar7 = (float *)(&DAT_00f25b24 + (int)param_4 * 0x24);
      local_14 = (float *)(param_1 + 0x44);
      do {
        fVar1 = *pfVar3;
        pfVar3 = pfVar3 + 1;
        *pfVar5 = pfVar7[-9] * fVar1 + *pfVar5;
        local_10 = local_10 + -1;
        pfVar5[0x120] = *local_14 * *pfVar7 + pfVar5[0x120];
        pfVar5 = pfVar5 + 0x20;
        pfVar7 = pfVar7 + 1;
        local_14 = local_14 + -1;
      } while (local_10 != 0);
      local_14 = (float *)0x4;
      pfVar3 = pfVar4;
      pfVar5 = pfVar4 + 8;
      pfVar7 = (float *)(&DAT_00f25b6c + (int)param_4 * 0x24);
      pfVar9 = (float *)(&DAT_00f25b8c + (int)param_4 * 0x24);
      do {
        fVar1 = *(float *)((int)pfVar3 + (param_1 - (int)pfVar4));
        fVar2 = *(float *)((int)pfVar5 + (param_1 - (int)pfVar4));
        local_14 = (float *)((int)local_14 + -1);
        *pfVar3 = fVar2 * pfVar7[-9] + *pfVar3;
        *pfVar5 = fVar1 * pfVar9[-9] + *pfVar5;
        pfVar3[9] = fVar1 * *pfVar7 + pfVar3[9];
        pfVar5[9] = fVar2 * *pfVar9 + pfVar5[9];
        pfVar3 = pfVar3 + 1;
        pfVar5 = pfVar5 + -1;
        pfVar7 = pfVar7 + 1;
        pfVar9 = pfVar9 + -1;
      } while (local_14 != (float *)0x0);
      fVar1 = *(float *)(param_1 + 0x10);
      param_1 = param_1 + 0x48;
      pfVar3 = pfVar4 + 0x12;
      param_2 = param_2 + 1;
      pfVar4[4] = fVar1 * (float)(&DAT_00f25b58)[(int)param_4 * 0x24] + pfVar4[4];
      local_8 = local_8 + -1;
      pfVar4[0xd] = fVar1 * (float)(&DAT_00f25b7c)[(int)param_4 * 0x24] + pfVar4[0xd];
      iVar6 = iVar10;
      pfVar4 = pfVar3;
      iVar11 = param_1;
    } while (local_8 != 0);
  }
  iVar10 = (param_6 + 0x11) / 0x12;
  if (iVar6 < iVar10) {
    param_1 = (int)&DAT_00f25c20 - (int)pfVar3;
    param_2 = (float *)(iVar10 - iVar6);
    iVar10 = (int)&DAT_00f25c20 - iVar11;
    param_4 = param_3 + iVar6 + 0x120;
    iVar6 = iVar6 + (int)param_2;
    do {
      FUN_0051c690(iVar11);
      iVar8 = 3;
      pfVar4 = (float *)(iVar11 + 0x24);
      pfVar5 = param_4;
      pfVar7 = (float *)(iVar11 + 8);
      do {
        pfVar9 = pfVar4 + 1;
        iVar8 = iVar8 + -1;
        pfVar5[-0x60] = pfVar4[-6] * *(float *)(iVar10 + -0x24 + (int)pfVar4) + pfVar5[-0x60];
        *pfVar5 = pfVar7[3] * *(float *)(iVar10 + -0x1c + (int)pfVar9) + *pfVar5;
        pfVar5[0x60] = *(float *)(iVar10 + -0x28 + (int)pfVar9) * *pfVar4 +
                       *(float *)(iVar10 + -0x10 + (int)pfVar9) * *pfVar7 + pfVar5[0x60];
        pfVar5[0xc0] = pfVar7[9] * *(float *)(iVar10 + -0x1c + (int)pfVar9) +
                       *(float *)(iVar10 + -4 + (int)pfVar9) * pfVar4[-9] + pfVar5[0xc0];
        pfVar4 = pfVar9;
        pfVar5 = pfVar5 + 0x20;
        pfVar7 = pfVar7 + -1;
      } while (iVar8 != 0);
      iVar8 = 3;
      pfVar4 = (float *)(iVar11 + 0x18);
      pfVar5 = pfVar3;
      pfVar7 = (float *)(iVar11 + 0x44);
      do {
        iVar8 = iVar8 + -1;
        *pfVar5 = *(float *)((int)pfVar4 + iVar10 + -0x18) * pfVar4[9] +
                  *(float *)((int)pfVar4 + iVar10) * pfVar7[-9] + *pfVar5;
        pfVar5[3] = *(float *)((int)pfVar4 + iVar10 + -0xc) * *pfVar7 +
                    *(float *)(iVar10 + 8 + (int)(pfVar4 + 1)) * *pfVar4 + pfVar5[3];
        pfVar4 = pfVar4 + 1;
        pfVar5 = pfVar5 + 1;
        pfVar7 = pfVar7 + -1;
      } while (iVar8 != 0);
      pfVar4 = (float *)(iVar11 + 0x38);
      param_3 = (float *)0x3;
      pfVar5 = pfVar3 + 9;
      pfVar7 = (float *)(iVar11 + 0x30);
      do {
        fVar1 = *pfVar4;
        pfVar4 = pfVar4 + -1;
        pfVar5[-3] = *(float *)(param_1 + -0xc + (int)pfVar5) * fVar1 + pfVar5[-3];
        param_3 = (float *)((int)param_3 + -1);
        *pfVar5 = *(float *)(param_1 + -4 + (int)(pfVar5 + 1)) * *pfVar7 + *pfVar5;
        pfVar5 = pfVar5 + 1;
        pfVar7 = pfVar7 + 1;
      } while (param_3 != (float *)0x0);
      param_1 = param_1 + -0x48;
      iVar11 = iVar11 + 0x48;
      iVar10 = iVar10 + -0x48;
      pfVar3 = pfVar3 + 0x12;
      param_4 = param_4 + 1;
      param_2 = (float *)((int)param_2 + -1);
    } while (param_2 != (float *)0x0);
  }
  return iVar6 * 0x12;
}

