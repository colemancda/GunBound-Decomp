/* FUN_00518160 - 0x00518160 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00518160(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  undefined4 uVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  float *pfVar6;
  int iVar7;
  int *piVar8;
  int *piVar9;
  int *piVar10;
  int iVar11;
  float local_18 [6];
  
  piVar10 = (int *)(param_3 + 0x1c);
  iVar4 = *(int *)(param_3 + 0x20) + 1;
  iVar11 = (&DAT_00f25d40)[*(int *)(param_3 + 0x20) + *piVar10 * 0x16];
  param_3 = param_4 - iVar11;
  if (*piVar10 == 0) {
    if (iVar4 < 0x15) {
      piVar10 = &DAT_00f25e20 + iVar4;
      do {
        iVar4 = *piVar10;
        iVar5 = (*(int *)(param_2 + -0xf25e20 + (int)piVar10) + param_5 * 8) * 8;
        fVar2 = *(float *)(&DAT_005b0144 + iVar5);
        fVar3 = *(float *)(&DAT_005b0148 + iVar5);
        iVar5 = 0;
        if (0 < iVar4) {
          pfVar6 = (float *)(param_1 + iVar11 * 4);
          do {
            param_3 = param_3 + -1;
            if (param_3 < 0) {
              return;
            }
            iVar5 = iVar5 + 1;
            iVar11 = iVar11 + 1;
            pfVar6[0x480] = fVar3 * *pfVar6;
            *pfVar6 = fVar2 * *pfVar6;
            pfVar6 = pfVar6 + 1;
          } while (iVar5 < iVar4);
        }
        piVar10 = piVar10 + 1;
      } while ((int)piVar10 < 0xf25e74);
    }
  }
  else if (iVar4 < 0xc) {
    piVar10 = &DAT_00f25e78 + iVar4;
    piVar8 = (int *)(param_2 + 0x5c + iVar4 * 4);
    do {
      iVar4 = 0;
      piVar9 = piVar8;
      do {
        iVar5 = *piVar9;
        iVar7 = iVar4 + 4;
        piVar9 = piVar9 + 0xd;
        iVar5 = (iVar5 + param_5 * 8) * 8;
        uVar1 = *(undefined4 *)(&DAT_005b0148 + iVar5);
        *(undefined4 *)((int)local_18 + iVar4 + 0xc) = *(undefined4 *)(&DAT_005b0144 + iVar5);
        *(undefined4 *)((int)local_18 + iVar4) = uVar1;
        iVar4 = iVar7;
      } while (iVar7 < 0xc);
      iVar4 = *piVar10;
      iVar5 = 0;
      if (0 < iVar4) {
        pfVar6 = (float *)(param_1 + 4 + iVar11 * 4);
        do {
          param_3 = param_3 + -3;
          if (param_3 < 0) {
            return;
          }
          iVar11 = iVar11 + 3;
          iVar5 = iVar5 + 1;
          pfVar6[0x47f] = local_18[0] * pfVar6[-1];
          pfVar6[-1] = local_18[3] * pfVar6[-1];
          pfVar6[0x480] = local_18[1] * *pfVar6;
          *pfVar6 = local_18[4] * *pfVar6;
          pfVar6[0x481] = local_18[2] * pfVar6[1];
          pfVar6[1] = local_18[5] * pfVar6[1];
          pfVar6 = pfVar6 + 3;
        } while (iVar5 < iVar4);
      }
      piVar10 = piVar10 + 1;
      piVar8 = piVar8 + 1;
    } while ((int)piVar10 < 0xf25ea8);
    return;
  }
  return;
}

