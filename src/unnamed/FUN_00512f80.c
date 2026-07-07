/* FUN_00512f80 - 0x00512f80 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
FUN_00512f80(int param_1,undefined4 param_2,int param_3,undefined4 param_4,uint param_5,int param_6)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  byte bVar4;
  uint *puVar5;
  uint *puVar6;
  byte *pbVar7;
  int *piVar8;
  int *piVar9;
  int iVar10;
  uint uVar11;
  float *pfVar12;
  short *psVar13;
  short *psVar14;
  undefined *puVar15;
  undefined1 *puVar16;
  undefined4 *puVar17;
  double dVar18;
  int local_c;
  
  iVar10 = 0;
  if (DAT_00563afc != 0) {
    iVar3 = 0;
    do {
      iVar1 = iVar3 + 4;
      *(float *)((int)&DAT_005ab890 + iVar3) =
           _DAT_00544370 / (float)*(int *)((int)&DAT_005637e8 + iVar3);
      iVar3 = iVar1;
    } while (iVar1 < 0x44);
    local_c = 0;
    pfVar12 = (float *)&DAT_005a9888;
    do {
      dVar18 = _pow(2.0,(double)local_c / _DAT_00544368);
      *pfVar12 = (float)((float10)dVar18 * (float10)_DAT_00544360);
      pfVar12 = pfVar12 + 1;
      local_c = local_c + -1;
    } while ((int)pfVar12 < 0x5a9988);
    puVar16 = &DAT_005a9988;
    do {
      iVar1 = 0;
      iVar3 = iVar10;
      do {
        puVar16[iVar1] = (char)(iVar3 % 3) + -1;
        iVar3 = iVar3 / 3;
        iVar1 = iVar1 + 1;
      } while (iVar1 < 3);
      puVar16 = puVar16 + 3;
      iVar10 = iVar10 + 1;
    } while ((int)puVar16 < 0x5a99e8);
    iVar10 = 0;
    puVar16 = &DAT_005ab708;
    do {
      iVar1 = 0;
      iVar3 = iVar10;
      do {
        puVar16[iVar1] = (char)(iVar3 % 5) + -2;
        iVar3 = iVar3 / 5;
        iVar1 = iVar1 + 1;
      } while (iVar1 < 3);
      puVar16 = puVar16 + 3;
      iVar10 = iVar10 + 1;
    } while ((int)puVar16 < 0x5ab888);
    iVar10 = 0;
    psVar13 = &DAT_005a9cf4;
    do {
      iVar1 = 3;
      iVar3 = iVar10;
      psVar14 = psVar13;
      do {
        psVar13 = psVar14 + 1;
        *psVar14 = (short)(iVar3 % 9) + -4;
        iVar3 = iVar3 / 9;
        iVar1 = iVar1 + -1;
        psVar14 = psVar13;
      } while (iVar1 != 0);
      iVar10 = iVar10 + 1;
    } while ((int)psVar13 < 0x5ab4f4);
    DAT_00563afc = 0;
  }
  PTR_FUN_005637d0 = (&PTR_FUN_00563aec)[*(uint *)(param_1 + 8) & 3];
  if (*(int *)(param_1 + 8) == 3) {
    uVar2 = FUN_005144e0(param_1,param_2,param_3,param_4,param_5,param_6);
    return uVar2;
  }
  if (*(int *)(param_1 + 8) == 1) {
    uVar2 = FUN_005163d0(param_1,param_2,param_3,param_4,param_5,param_6);
    return uVar2;
  }
  uVar11 = (uint)((param_5 & 8) != 0);
  if (param_3 < 0) {
    param_3 = 0;
  }
  else if (2 < param_3) {
    param_3 = 2;
  }
  iVar10 = param_6;
  if (param_6 < 1000) {
    iVar10 = 1000;
  }
  DAT_005a9884 = param_2;
  if (*(int *)(param_1 + 8) != 2) {
    return 0;
  }
  if (*(int *)(param_1 + 0x14) == 3) {
    return 0;
  }
  if (*(int *)(param_1 + 4) == 0) {
    param_6 = 4;
  }
  else {
    param_6 = (int)(char)(&DAT_0056382c)
                         [*(int *)(param_1 + 0x10) +
                          (*(int *)(param_1 + 0x20) +
                          *(int *)(param_1 + 0x14) + *(int *)(param_1 + 0x20) * 2) * 0x10];
    if (param_6 < 0) {
      return 0;
    }
  }
  puVar5 = &DAT_005a9784;
  puVar15 = &DAT_0056390c + param_6 * 0x40;
  do {
    iVar3 = 0;
    puVar6 = puVar5;
    do {
      puVar5 = puVar6 + 1;
      pbVar7 = puVar15 + iVar3;
      iVar3 = iVar3 + 1;
      *puVar6 = (uint)*pbVar7;
      puVar6 = puVar5;
    } while (iVar3 < 0x10);
    puVar15 = puVar15 + 0x10;
  } while ((int)puVar5 < 0x5a9884);
  pbVar7 = &DAT_00563a4c + param_6 * 4;
  puVar5 = (uint *)&DAT_005637bc;
  do {
    puVar6 = puVar5 + 1;
    bVar4 = *pbVar7;
    pbVar7 = pbVar7 + 1;
    *puVar5 = (uint)bVar4;
    puVar5 = puVar6;
  } while ((int)puVar6 < 0x5637cc);
  DAT_005a99e8 = DAT_005637c8 + DAT_005637c4 + DAT_005637c0 + DAT_005637bc;
  _DAT_00f25ee8 =
       *(int *)(&DAT_005638ec + (*(int *)(param_1 + 0x14) + *(int *)(param_1 + 4) * 4) * 4);
  DAT_00563770 = (_DAT_00f25ee8 / 2 + iVar10 * 0x40) / _DAT_00f25ee8;
  bVar4 = (byte)param_3;
  iVar10 = 0x20 >> (bVar4 & 0x1f);
  if (8 < iVar10) {
    iVar10 = iVar10 + -1;
  }
  if (iVar10 < DAT_00563770) {
    DAT_00563770 = iVar10;
  }
  if (DAT_005a99e8 < DAT_00563770) {
    DAT_00563770 = DAT_005a99e8;
  }
  if (*(int *)(param_1 + 0x20) != 3) {
    piVar8 = &DAT_005637bc;
    do {
      piVar9 = piVar8 + 1;
      *piVar8 = *piVar8 << 1;
      piVar8 = piVar9;
    } while ((int)piVar9 < 0x5637cc);
    DAT_005a99e8 = DAT_005a99e8 * 2;
    DAT_00563770 = DAT_00563770 * 2;
  }
  iVar10 = (param_5 & 3) + 1;
  if (*(int *)(param_1 + 0x20) == 3) {
    iVar10 = 0;
  }
  DAT_00f25ee0 = (&DAT_00563ad8)[iVar10];
  PTR_FUN_005637cc = (&PTR_FUN_00563a60)[iVar10 + (param_3 + uVar11 * 3) * 5];
  _DAT_005ab4f8 = DAT_00f25ee0 * (0x480 >> (bVar4 & 0x1f));
  DAT_005a99f0 = _DAT_005ab4f8;
  if (uVar11 == 0) {
    DAT_005a99f0 = _DAT_005ab4f8 * 2;
  }
  _DAT_00f25ee8 = _DAT_00f25ee8 >> (bVar4 & 0x1f);
  _DAT_00f25ef0 = param_2;
  _DAT_00f25eec = (-(uint)(uVar11 != 0) & 0xfffffff8) + 0x10;
  puVar17 = &DAT_00f25f00;
  DAT_00f25ee4 = _DAT_005ab4f8;
  for (iVar10 = 0x900; iVar10 != 0; iVar10 = iVar10 + -1) {
    *puVar17 = 0;
    puVar17 = puVar17 + 1;
  }
  _DAT_00f25ef4 = 0;
  FUN_005167c0();
  return 1;
}

