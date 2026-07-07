/* FUN_00518560 - 0x00518560 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00518560(int param_1,int *param_2,int param_3,int param_4,undefined4 *param_5,int param_6)

{
  int iVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  float fVar5;
  bool bVar6;
  int iVar7;
  int *piVar8;
  float *pfVar9;
  int iVar10;
  uint uVar11;
  float *pfVar12;
  uint uVar13;
  double dVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  int local_68;
  int *local_5c;
  int *local_58;
  float *local_54;
  int *local_50;
  int *local_4c;
  int *local_48;
  int local_44;
  int local_40;
  uint local_20 [3];
  float local_14 [4];
  
  iVar1 = *param_2;
  local_5c = (int *)0x16;
  uVar13 = 0xc;
  if (*(int *)(param_4 + 0x14) == 2) {
    uVar13 = 0;
    local_5c = (int *)0x0;
    if (*(int *)(param_4 + 0x18) != 0) {
      uVar13 = 3;
      local_5c = (int *)param_6;
    }
  }
  uVar11 = 0;
  param_5[2] = uVar13;
  param_5[3] = local_5c;
  local_20[0] = 0;
  local_68 = 0;
  fVar2 = *(float *)(&DAT_005b01fc + *(int *)(param_4 + 8) * 4);
  if (0 < (int)local_5c) {
    local_50 = &DAT_00f25e20;
    do {
      bVar6 = false;
      fVar5 = fVar2 * *(float *)(&DAT_005b0efc +
                                ((*(int *)(&DAT_00563df4 +
                                          (uVar11 + *(int *)(param_4 + 0x3c) * 0x16) * 4) +
                                 *(int *)(param_4 + 0x40) * 4) * 0x20 +
                                *(int *)(param_3 + -0xf25e20 + (int)local_50)) * 4);
      local_4c = (int *)*local_50;
      if (0 < (int)local_4c) {
        pfVar9 = (float *)(param_1 + local_68 * 4);
        local_68 = local_68 + (int)local_4c;
        do {
          fVar3 = *pfVar9;
          if (fVar3 == 0.0) {
            *pfVar9 = 0.0;
          }
          else {
            bVar6 = true;
            if (((int)fVar3 < -0x20) || (0x1f < (int)fVar3)) {
              uVar16 = 0x3fd55555;
              uVar15 = 0x60000000;
              dVar14 = _fabs((double)(int)fVar3);
              dVar14 = _pow(dVar14,(double)CONCAT44(uVar16,uVar15));
              *pfVar9 = (float)dVar14 * fVar5 * (float)(int)fVar3;
            }
            else {
              *pfVar9 = fVar5 * *(float *)(&DAT_005b137c + (int)fVar3 * 4);
            }
          }
          pfVar9 = pfVar9 + 1;
          local_4c = (int *)((int)local_4c + -1);
        } while (local_4c != (int *)0x0);
        if (bVar6) {
          local_20[0] = uVar11;
        }
      }
      if (iVar1 <= local_68) break;
      uVar11 = uVar11 + 1;
      local_50 = local_50 + 1;
    } while ((int)uVar11 < (int)local_5c);
  }
  iVar7 = local_68;
  param_5[1] = local_20[0];
  *param_5 = 0;
  if (uVar13 < 0xc) {
    piVar8 = (int *)(param_4 + 0x28);
    local_54 = (float *)&DAT_005b05fc;
    iVar10 = 3;
    pfVar9 = local_14;
    do {
      iVar4 = *piVar8;
      piVar8 = piVar8 + 1;
      iVar10 = iVar10 + -1;
      *pfVar9 = fVar2 * *(float *)(&DAT_005b01c4 + iVar4 * 4);
      pfVar9 = pfVar9 + 1;
    } while (iVar10 != 0);
    local_20[0] = uVar13;
    local_20[1] = uVar13;
    local_20[2] = uVar13;
    if (uVar13 < 0xd) {
      piVar8 = &DAT_00f25e78 + uVar13;
      local_4c = (int *)(param_3 + 0x5c + uVar13 * 4);
      local_50 = (int *)uVar13;
      do {
        iVar10 = *piVar8;
        local_40 = 3;
        local_48 = (int *)(param_1 + local_68 * 4);
        local_58 = local_4c;
        pfVar9 = local_54;
        do {
          bVar6 = false;
          fVar2 = *(float *)(&DAT_005b0efc + (*(int *)(param_4 + 0x40) * 0x80 + *local_58) * 4) *
                  *(float *)((int)local_14 + -(int)local_54 + (int)pfVar9);
          if (0 < iVar10) {
            local_68 = local_68 + iVar10;
            local_5c = local_48;
            local_48 = local_48 + iVar10;
            pfVar12 = pfVar9;
            local_44 = iVar10;
            do {
              iVar4 = *local_5c;
              if (iVar4 == 0) {
                *pfVar12 = 0.0;
              }
              else {
                bVar6 = true;
                if ((iVar4 < -0x20) || (0x1f < iVar4)) {
                  uVar16 = 0x3fd55555;
                  uVar15 = 0x60000000;
                  dVar14 = _fabs((double)iVar4);
                  dVar14 = _pow(dVar14,(double)CONCAT44(uVar16,uVar15));
                  fVar5 = (float)dVar14 * fVar2 * (float)iVar4;
                }
                else {
                  fVar5 = fVar2 * *(float *)(&DAT_005b137c + iVar4 * 4);
                }
                *pfVar12 = fVar5;
              }
              pfVar12 = pfVar12 + 3;
              local_5c = local_5c + 1;
              local_44 = local_44 + -1;
            } while (local_44 != 0);
            if (bVar6) {
              *(int **)((int)local_20 + -(int)local_54 + (int)pfVar9) = local_50;
            }
          }
          local_58 = local_58 + 0xd;
          pfVar9 = pfVar9 + 1;
          local_40 = local_40 + -1;
        } while (local_40 != 0);
        if (iVar1 <= local_68) break;
        local_54 = local_54 + iVar10 * 3;
        piVar8 = piVar8 + 1;
        local_50 = (int *)((int)local_50 + 1);
        local_4c = local_4c + 1;
      } while ((int)piVar8 < 0xf25eac);
    }
    _memmove((void *)(param_1 + iVar7 * 4),&DAT_005b05fc,(iVar7 * 0x3fffffff + local_68) * 4);
    *param_2 = local_68;
    param_5[4] = local_20[0];
    param_5[5] = local_20[1];
    param_5[6] = local_20[2];
    if ((int)local_20[0] < (int)local_20[1]) {
      local_20[0] = local_20[1];
    }
    if ((int)local_20[0] < (int)local_20[2]) {
      local_20[0] = local_20[2];
    }
    param_5[1] = local_20[0];
    *param_5 = 1;
  }
  return;
}

