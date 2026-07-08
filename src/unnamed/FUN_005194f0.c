/* FUN_005194f0 - 0x005194f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_005194f0(undefined4 *param_1,undefined4 *param_2,int param_3,int *param_4)

{
  uint uVar1;
  int iVar2;
  ulonglong uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  uint local_20;
  uint local_c;
  undefined4 local_8;
  
  iVar14 = *(int *)((int)param_2 + 0x14);
  uVar1 = *(uint *)((int)param_2 + 0x18);
  uVar13 = *(uint *)((int)param_2 + 0xc);
  local_8 = 0;
  local_c = 0;
  if (param_3 == 0) {
    if ((int)uVar13 < 400) {
      uVar7 = ((int)uVar13 >> 4) / 5;
      uVar9 = ((int)uVar13 >> 4) % 5;
      local_20 = uVar13 & 3;
      uVar13 = (int)(uVar13 & 0xf) >> 2;
      iVar4 = 0;
    }
    else if ((int)uVar13 < 500) {
      iVar4 = (int)(uVar13 - 400) >> 2;
      uVar7 = iVar4 / 5;
      uVar13 = uVar13 - 400 & 3;
      uVar9 = iVar4 % 5;
      iVar4 = 1;
      local_20 = 0;
    }
    else {
      uVar7 = (int)(uVar13 - 500) / 3;
      uVar10 = (int)(uVar13 - 500) % 3;
      local_20 = 0;
      uVar9 = uVar10;
      uVar13 = 0;
      if (uVar1 != 0) {
        uVar9 = uVar7;
        uVar13 = uVar10;
      }
      local_8 = 1;
      iVar4 = 2;
    }
  }
  else {
    iVar4 = (int)uVar13 >> 1;
    local_c = uVar13 & 1;
    if (iVar4 < 0xb4) {
      uVar7 = iVar4 / 0x24;
      uVar3 = CONCAT44((int)uVar13 >> 0x1f,iVar4) % 0x24;
      iVar4 = (int)uVar3;
      uVar13 = (uint)((longlong)((ulonglong)(uint)(iVar4 >> 0x1f) << 0x20 | uVar3 & 0xffffffff) % 6)
      ;
      uVar9 = iVar4 / 6;
      local_20 = 0;
      iVar4 = 3;
    }
    else if (iVar4 < 0xf4) {
      uVar7 = iVar4 - 0xb4;
      local_20 = 0;
      iVar4 = 4;
      uVar13 = uVar7 & 3;
      uVar9 = (int)uVar7 >> 2 & 3;
      uVar7 = (int)uVar7 >> 4;
    }
    else {
      uVar7 = (iVar4 + -0xf4) / 3;
      uVar9 = (iVar4 + -0xf4) % 3;
      local_20 = 0;
      uVar13 = 0;
      iVar4 = 5;
    }
  }
  iVar8 = 0;
  if (iVar14 == 2) {
    iVar8 = (uVar1 & 1) + 1;
  }
  iVar8 = iVar8 + iVar4 * 3;
  iVar4 = (&DAT_0054496c)[iVar8 * 4];
  iVar2 = (&DAT_00544968)[iVar8 * 4];
  iVar12 = (&DAT_00544970)[iVar8 * 4];
  iVar8 = (&DAT_00544974)[iVar8 * 4];
  if (param_3 != 0) {
    param_4[1] = iVar4;
    param_4[2] = iVar12;
    *param_4 = iVar2;
    param_4[3] = uVar7;
    param_4[4] = uVar9;
    param_4[5] = uVar13;
    param_4[6] = local_c;
  }
  *(undefined4 *)((int)param_2 + 0x3c) = local_8;
  if (iVar14 == 2) {
    if (uVar1 == 0) {
      iVar14 = 0;
      if (uVar7 == 0) {
        if (0 < iVar2) {
          puVar6 = param_1 + 0x24;
          iVar11 = iVar2;
          do {
            puVar6[-0xd] = 0;
            *puVar6 = 0;
            puVar6[0xd] = 0;
            puVar6 = puVar6 + 1;
            iVar11 = iVar11 + -1;
            iVar14 = iVar2;
          } while (iVar11 != 0);
        }
      }
      else if (0 < iVar2) {
        puVar6 = param_1 + 0x24;
        param_2 = (undefined4 *)iVar2;
        do {
          FUN_00514af0(uVar7);
          puVar6[-0xd] = uVar5;
          FUN_00514af0(uVar7);
          *puVar6 = uVar5;
          FUN_00514af0(uVar7);
          puVar6[0xd] = uVar5;
          puVar6 = puVar6 + 1;
          param_2 = (undefined4 *)((int)param_2 + -1);
          iVar14 = iVar2;
        } while (param_2 != (undefined4 *)0x0);
      }
    }
    else if (uVar7 == 0) {
      puVar6 = param_1;
      for (iVar14 = 6; iVar14 != 0; iVar14 = iVar14 + -1) {
        *puVar6 = 0;
        puVar6 = puVar6 + 1;
      }
      iVar14 = 3;
    }
    else {
      param_3 = 6;
      puVar6 = param_1;
      do {
        FUN_00514af0(uVar7);
        *puVar6 = uVar5;
        puVar6 = puVar6 + 1;
        param_3 = param_3 + -1;
      } while (param_3 != 0);
      iVar14 = 3;
    }
    if (uVar9 == 0) {
      if (0 < iVar4) {
        puVar6 = param_1 + iVar14 + 0x24;
        iVar14 = iVar14 + iVar4;
        do {
          puVar6[-0xd] = 0;
          *puVar6 = 0;
          puVar6[0xd] = 0;
          puVar6 = puVar6 + 1;
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
      }
    }
    else if (0 < iVar4) {
      puVar6 = param_1 + iVar14 + 0x24;
      iVar14 = iVar14 + iVar4;
      param_3 = iVar4;
      do {
        FUN_00514af0(uVar9);
        puVar6[-0xd] = uVar5;
        FUN_00514af0(uVar9);
        *puVar6 = uVar5;
        FUN_00514af0(uVar9);
        puVar6[0xd] = uVar5;
        puVar6 = puVar6 + 1;
        param_3 = param_3 + -1;
      } while (param_3 != 0);
    }
    if (uVar13 == 0) {
      if (0 < iVar12) {
        puVar6 = param_1 + iVar14 + 0x24;
        iVar14 = iVar14 + iVar12;
        do {
          puVar6[-0xd] = 0;
          *puVar6 = 0;
          puVar6[0xd] = 0;
          puVar6 = puVar6 + 1;
          iVar12 = iVar12 + -1;
        } while (iVar12 != 0);
      }
    }
    else if (0 < iVar12) {
      puVar6 = param_1 + iVar14 + 0x24;
      iVar14 = iVar14 + iVar12;
      do {
        FUN_00514af0(uVar13);
        puVar6[-0xd] = uVar5;
        FUN_00514af0(uVar13);
        *puVar6 = uVar5;
        FUN_00514af0(uVar13);
        puVar6[0xd] = uVar5;
        puVar6 = puVar6 + 1;
        iVar12 = iVar12 + -1;
      } while (iVar12 != 0);
    }
    if (local_20 == 0) {
      if (0 < iVar8) {
        param_1 = param_1 + iVar14 + 0x24;
        do {
          param_1[-0xd] = 0;
          *param_1 = 0;
          param_1[0xd] = 0;
          param_1 = param_1 + 1;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
        return;
      }
    }
    else if (0 < iVar8) {
      param_1 = param_1 + iVar14 + 0x24;
      do {
        FUN_00514af0(local_20);
        param_1[-0xd] = uVar5;
        FUN_00514af0(local_20);
        *param_1 = uVar5;
        FUN_00514af0(local_20);
        param_1[0xd] = uVar5;
        param_1 = param_1 + 1;
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
      return;
    }
  }
  else {
    param_3 = 0;
    if (uVar7 == 0) {
      iVar14 = iVar2;
      puVar6 = param_1;
      if (0 < iVar2) {
        for (; param_3 = iVar2, iVar14 != 0; iVar14 = iVar14 + -1) {
          *puVar6 = 0;
          puVar6 = puVar6 + 1;
        }
      }
    }
    else if (0 < iVar2) {
      param_2 = param_1;
      param_4 = (int *)iVar2;
      do {
        FUN_00514af0(uVar7);
        *param_2 = uVar5;
        param_2 = param_2 + 1;
        param_4 = (int *)((int)param_4 + -1);
        param_3 = iVar2;
      } while (param_4 != (int *)0x0);
    }
    if (uVar9 == 0) {
      if (0 < iVar4) {
        puVar6 = param_1 + param_3;
        param_3 = param_3 + iVar4;
        for (; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar6 = 0;
          puVar6 = puVar6 + 1;
        }
      }
    }
    else if (0 < iVar4) {
      puVar6 = param_1 + param_3;
      param_3 = param_3 + iVar4;
      param_2 = (undefined4 *)iVar4;
      do {
        FUN_00514af0(uVar9);
        *puVar6 = uVar5;
        puVar6 = puVar6 + 1;
        param_2 = (undefined4 *)((int)param_2 + -1);
      } while (param_2 != (undefined4 *)0x0);
    }
    if (uVar13 == 0) {
      if (0 < iVar12) {
        puVar6 = param_1 + param_3;
        param_3 = param_3 + iVar12;
        for (; iVar12 != 0; iVar12 = iVar12 + -1) {
          *puVar6 = 0;
          puVar6 = puVar6 + 1;
        }
      }
    }
    else if (0 < iVar12) {
      puVar6 = param_1 + param_3;
      param_3 = param_3 + iVar12;
      do {
        FUN_00514af0(uVar13);
        *puVar6 = uVar5;
        puVar6 = puVar6 + 1;
        iVar12 = iVar12 + -1;
      } while (iVar12 != 0);
    }
    if (local_20 == 0) {
      if (0 < iVar8) {
        puVar6 = param_1 + param_3;
        for (; iVar8 != 0; iVar8 = iVar8 + -1) {
          *puVar6 = 0;
          puVar6 = puVar6 + 1;
        }
      }
    }
    else if (0 < iVar8) {
      param_1 = param_1 + param_3;
      do {
        FUN_00514af0(local_20);
        *param_1 = uVar5;
        param_1 = param_1 + 1;
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
      return;
    }
  }
  return;
}

