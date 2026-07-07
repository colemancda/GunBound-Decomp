/* FUN_00515420 - 0x00515420 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00515420(undefined4 param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined *puVar9;
  int iVar10;
  undefined4 *puVar11;
  int *piVar12;
  uint local_18;
  undefined4 *local_14;
  int local_c;
  undefined4 *local_8;
  
  iVar1 = (int)param_2;
  local_18 = 0;
  if (0 < DAT_005ae7dc) {
    local_8 = &DAT_005ae7f8;
    local_14 = &DAT_00f25f00 + (int)param_2 * 0x240;
    param_2 = (int *)((int)param_2 * 0x240);
    do {
      iVar8 = 0;
      DAT_00f25e0c = &DAT_005aba38 + ((int)DAT_005ae920 >> 3);
      uVar5 = 0;
      uVar6 = DAT_005ae920 & 7;
      DAT_00f25e04 = 0;
      DAT_00f25e00 = 0;
      DAT_00f25e08 = DAT_00f25e0c;
      if (uVar6 != 0) {
        if (uVar6 != 0) {
          do {
            iVar8 = iVar8 + 8;
            uVar5 = uVar5 << 8 | (uint)*DAT_00f25e08;
            DAT_00f25e08 = DAT_00f25e08 + 1;
          } while (iVar8 < 0x19);
        }
        DAT_00f25e04 = iVar8 - uVar6;
        DAT_00f25e00 = uVar5 - ((uVar5 >> ((byte)DAT_00f25e04 & 0x1f)) <<
                               ((byte)DAT_00f25e04 & 0x1f));
      }
      iVar8 = local_18 + iVar1 * 2;
      DAT_005ae920 = DAT_005ae920 + (&DAT_005ae800)[iVar8 * 0x12];
      DAT_00f25e10 = &DAT_005aba38 + ((int)(DAT_005ae920 + 0x27) >> 3);
      if (DAT_005ae34c == 0) {
        FUN_005194f0(&DAT_005ae358 + iVar8 * 0xf8,&DAT_005ae800 + iVar8 * 0x12,
                     DAT_005aba2c & local_18,&DAT_005ae7b0);
      }
      else {
        FUN_00519260(&DAT_005ae358 + iVar8 * 0xf8,&DAT_005ae800 + iVar8 * 0x12,*local_8,iVar1);
      }
      iVar10 = (&DAT_005ae804)[iVar8 * 0x12] * 2;
      if (iVar10 - DAT_00563d8c != 0 && DAT_00563d8c <= iVar10) {
        iVar10 = DAT_00563d8c;
      }
      local_c = (&DAT_00f25d44)[(&DAT_005ae838)[iVar8 * 0x12] + (&DAT_005ae834)[iVar8 * 0x12]];
      if (iVar10 < (int)(&DAT_00f25d44)
                        [(&DAT_005ae838)[iVar8 * 0x12] + (&DAT_005ae834)[iVar8 * 0x12]]) {
        local_c = iVar10;
      }
      iVar4 = (&DAT_00f25d40)[(&DAT_005ae834)[iVar8 * 0x12]];
      if (iVar10 < (int)(&DAT_00f25d40)[(&DAT_005ae834)[iVar8 * 0x12]]) {
        iVar4 = iVar10;
      }
      FUN_00518960(local_14,iVar4,(&DAT_005ae81c)[iVar8 * 0x12]);
      FUN_00518960(&DAT_00f25f00 + (int)param_2 + iVar4,local_c - iVar4,
                   (&DAT_005ae820)[iVar8 * 0x12]);
      FUN_00518960(&DAT_00f25f00 + (int)param_2 + local_c,iVar10 - local_c,
                   (&DAT_005ae824)[iVar8 * 0x12]);
      iVar2 = FUN_00518e30(&DAT_00f25f00 + (int)param_2 + iVar10,DAT_00563d8c - iVar10,
                           (&DAT_005ae800)[iVar8 * 0x12] +
                           ((int)DAT_00f25e0c - (int)DAT_00f25e08) * 8 + DAT_00f25e04 + uVar6,
                           (&DAT_005ae844)[iVar8 * 0x12]);
      iVar4 = (&DAT_005ae814)[iVar8 * 0x12];
      iVar2 = iVar2 + iVar10;
      *(int *)(&DAT_005ae7cc + iVar8 * 4) = iVar2;
      iVar8 = DAT_00563d90;
      if (iVar4 == 2) {
        iVar8 = DAT_00563d94;
      }
      if (iVar8 <= iVar2) {
        iVar2 = iVar8;
      }
      if (iVar2 < 0x240) {
        puVar7 = &DAT_00f25f00 + (int)param_2 + iVar2;
        for (uVar5 = 0x240U - iVar2 & 0x3fffffff; uVar5 != 0; uVar5 = uVar5 - 1) {
          *puVar7 = 0;
          puVar7 = puVar7 + 1;
        }
        for (iVar8 = 0; iVar8 != 0; iVar8 = iVar8 + -1) {
          *(undefined1 *)puVar7 = 0;
          puVar7 = (undefined4 *)((int)puVar7 + 1);
        }
      }
      if (DAT_00f25e10 < DAT_00f25e08) {
        puVar7 = local_14;
        for (iVar8 = 0x240; iVar8 != 0; iVar8 = iVar8 + -1) {
          *puVar7 = 0;
          puVar7 = puVar7 + 1;
        }
      }
      local_18 = local_18 + 1;
      local_8 = local_8 + 1;
      param_2 = (int *)((int)param_2 + 0x480);
      local_14 = local_14 + 0x480;
    } while ((int)local_18 < DAT_005ae7dc);
  }
  local_18 = 0;
  if (0 < DAT_005ae7dc) {
    local_8 = (undefined4 *)(&DAT_005ae7cc + iVar1 * 8);
    param_2 = (int *)(&DAT_005ae740 + iVar1 * 0x38);
    puVar9 = &DAT_005ae358 + iVar1 * 0x1f0;
    puVar11 = &DAT_005ae800 + iVar1 * 0x24;
    puVar7 = &DAT_00f25f00 + iVar1 * 0x240;
    do {
      FUN_00518560(puVar7,local_8,puVar9,puVar11,param_2,DAT_005aba28);
      local_8 = (undefined4 *)((int)local_8 + 4);
      local_18 = local_18 + 1;
      param_2 = (int *)((int)param_2 + 0x1c);
      puVar11 = puVar11 + 0x12;
      puVar9 = puVar9 + 0xf8;
      puVar7 = puVar7 + 0x480;
    } while ((int)local_18 < DAT_005ae7dc);
  }
  if (DAT_005ae348 != 0) {
    if (DAT_005aba2c == 0) {
      iVar8 = *(int *)(&DAT_005ae7cc + iVar1 * 8);
      if (*(int *)(&DAT_005ae7cc + iVar1 * 8) < *(int *)(&DAT_005ae7d0 + iVar1 * 8)) {
        iVar8 = *(int *)(&DAT_005ae7d0 + iVar1 * 8);
      }
    }
    else {
      iVar8 = (&DAT_00f25d40)
              [*(int *)(&DAT_005ae760 + iVar1 * 0x38) +
               *(int *)(&DAT_005ae75c + iVar1 * 0x38) * 0x16];
    }
    FUN_00518120(&DAT_00f25f00 + iVar1 * 0x240,iVar8);
  }
  if (DAT_005aba2c != 0) {
    if (DAT_005ae34c == 0) {
      FUN_005182f0(&DAT_00f25f00 + iVar1 * 0x240,&DAT_005ae450 + iVar1 * 0x1f0,
                   &DAT_005ae740 + iVar1 * 0x38,&DAT_005ae7b0,
                   *(undefined4 *)(&DAT_005ae7cc + iVar1 * 8),DAT_005ae348);
    }
    else {
      FUN_00518160(&DAT_00f25f00 + iVar1 * 0x240,&DAT_005ae450 + iVar1 * 0x1f0,
                   &DAT_005ae740 + iVar1 * 0x38,*(undefined4 *)(&DAT_005ae7cc + iVar1 * 8));
    }
  }
  if (DAT_005ae7ec != 0) {
    if (*(int *)(&DAT_005ae7cc + iVar1 * 8) < *(int *)(&DAT_005ae7d0 + iVar1 * 8)) {
      *(int *)(&DAT_005ae7cc + iVar1 * 8) = *(int *)(&DAT_005ae7d0 + iVar1 * 8);
    }
    else {
      *(int *)(&DAT_005ae7d0 + iVar1 * 8) = *(int *)(&DAT_005ae7cc + iVar1 * 8);
    }
  }
  local_18 = 0;
  if (0 < DAT_005ae7dc) {
    piVar3 = &DAT_005ae818 + iVar1 * 0x24;
    param_2 = (int *)(&DAT_005ae74c + iVar1 * 0x38);
    piVar12 = (int *)(&DAT_005ae7cc + iVar1 * 8);
    puVar7 = &DAT_00f25f00 + iVar1 * 0x240;
    do {
      if (*param_2 != 0) {
        if (*piVar3 == 0) {
          iVar8 = (*piVar12 + 7) / 0x12;
          if (0x1f < iVar8) {
            iVar8 = 0x1f;
          }
        }
        else {
          iVar8 = 1;
        }
        FUN_00518100(puVar7,iVar8);
        iVar8 = iVar8 * 0x12 + 8;
        if (*piVar12 < iVar8) {
          *piVar12 = iVar8;
        }
      }
      param_2 = param_2 + 7;
      local_18 = local_18 + 1;
      piVar3 = piVar3 + 0x12;
      piVar12 = piVar12 + 1;
      puVar7 = puVar7 + 0x480;
    } while ((int)local_18 < DAT_005ae7dc);
  }
  (*(code *)PTR_FUN_00563da4)(param_1,iVar1);
  return;
}

