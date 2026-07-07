/* FUN_005182f0 - 0x005182f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_005182f0(int param_1,int param_2,int param_3,int *param_4,int param_5,int param_6)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float *pfVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int *piVar12;
  int local_5c;
  int local_54 [21];
  
  piVar6 = param_4;
  iVar11 = (param_6 + param_4[6] * 2) * 0x200;
  if (*(int *)(param_3 + 0x1c) != 0) {
    iVar8 = 0;
    param_4 = (int *)0x3;
    do {
      iVar9 = piVar6[3];
      iVar10 = *piVar6;
      if (0 < iVar10) {
        piVar12 = local_54 + iVar8;
        for (iVar5 = iVar10; iVar5 != 0; iVar5 = iVar5 + -1) {
          *piVar12 = (1 << ((byte)iVar9 & 0x1f)) + -1;
          piVar12 = piVar12 + 1;
        }
        iVar8 = iVar8 + iVar10;
      }
      piVar6 = piVar6 + 1;
      param_4 = (int *)((int)param_4 + -1);
    } while (param_4 != (int *)0x0);
    piVar6 = (int *)(param_3 + 0x10);
    param_4 = (int *)0x0;
    local_5c = 0;
    do {
      iVar9 = *piVar6;
      iVar10 = (&DAT_00f25d98)[piVar6[7]] + (int)param_4;
      iVar8 = piVar6[7] + 1;
      if (iVar8 <= iVar9) {
        piVar12 = (int *)(param_2 + 0x5c + (local_5c + iVar8) * 4);
        do {
          fVar2 = *(float *)(&DAT_005af944 + (local_54[iVar8] + *piVar12) * 8 + iVar11);
          fVar3 = *(float *)(iVar11 + 0x5af948 + (local_54[iVar8] + *piVar12) * 8);
          iVar5 = (&DAT_00f25e78)[iVar8];
          if (0 < iVar5) {
            iVar1 = iVar10 * 4;
            iVar10 = iVar10 + iVar5 * 3;
            pfVar4 = (float *)(param_1 + iVar1);
            do {
              iVar5 = iVar5 + -1;
              pfVar4[0x480] = fVar3 * *pfVar4;
              *pfVar4 = fVar2 * *pfVar4;
              pfVar4 = pfVar4 + 3;
            } while (iVar5 != 0);
          }
          iVar8 = iVar8 + 1;
          piVar12 = piVar12 + 1;
        } while (iVar8 <= iVar9);
      }
      local_5c = local_5c + 0xd;
      param_4 = (int *)((int)param_4 + 1);
      piVar6 = piVar6 + 1;
    } while (local_5c < 0x27);
    return;
  }
  iVar8 = *(int *)(param_3 + 0x20);
  param_4 = (int *)0x3;
  iVar9 = (&DAT_00f25d40)[iVar8];
  param_5 = param_5 - iVar9;
  iVar10 = 0;
  do {
    iVar5 = piVar6[3];
    iVar1 = *piVar6;
    if (0 < iVar1) {
      piVar12 = local_54 + iVar10;
      for (iVar7 = iVar1; iVar7 != 0; iVar7 = iVar7 + -1) {
        *piVar12 = (1 << ((byte)iVar5 & 0x1f)) + -1;
        piVar12 = piVar12 + 1;
      }
      iVar10 = iVar10 + iVar1;
    }
    piVar6 = piVar6 + 1;
    param_4 = (int *)((int)param_4 + -1);
  } while (param_4 != (int *)0x0);
  iVar8 = iVar8 + 1;
  if (iVar8 < 0x15) {
    iVar8 = iVar8 * 4;
    do {
      iVar10 = *(int *)(param_2 + iVar8) + *(int *)((int)local_54 + iVar8);
      fVar2 = *(float *)(iVar11 + 0x5af948 + iVar10 * 8);
      fVar3 = *(float *)(&DAT_005af944 + iVar10 * 8 + iVar11);
      iVar10 = *(int *)((int)&DAT_00f25e20 + iVar8);
      iVar5 = 0;
      if (0 < iVar10) {
        pfVar4 = (float *)(param_1 + iVar9 * 4);
        do {
          param_5 = param_5 + -1;
          if (param_5 < 0) {
            return;
          }
          iVar5 = iVar5 + 1;
          iVar9 = iVar9 + 1;
          pfVar4[0x480] = fVar2 * *pfVar4;
          *pfVar4 = fVar3 * *pfVar4;
          pfVar4 = pfVar4 + 1;
        } while (iVar5 < iVar10);
      }
      iVar8 = iVar8 + 4;
    } while (iVar8 < 0x54);
  }
  return;
}

