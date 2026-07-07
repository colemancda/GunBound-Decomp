/* FUN_005144e0 - 0x005144e0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
FUN_005144e0(int param_1,undefined4 param_2,int param_3,undefined4 param_4,uint param_5,int param_6)

{
  int iVar1;
  float *pfVar2;
  float *pfVar3;
  byte bVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  
  if (DAT_00563b48 != 0) {
    iVar5 = 4;
    pfVar2 = (float *)&DAT_005ab8e0;
    do {
      iVar1 = iVar5 + -1;
      pfVar3 = pfVar2 + 1;
      iVar5 = iVar5 << 1;
      *pfVar2 = (float)_DAT_00544378 / (float)iVar1;
      pfVar2 = pfVar3;
    } while ((int)pfVar3 < 0x5ab91c);
    DAT_00563b48 = 0;
  }
  uVar6 = (uint)((param_5 & 8) != 0);
  if (param_3 < 0) {
    param_3 = 0;
  }
  else if (2 < param_3) {
    param_3 = 2;
  }
  if (param_6 < 1000) {
    param_6 = 1000;
  }
  DAT_005a9884 = param_2;
  if (*(int *)(param_1 + 8) != 3) {
    return 0;
  }
  DAT_00563b44 = 0x20;
  DAT_005a99e8 = 0x20;
  _DAT_00f25ee8 =
       *(int *)(&DAT_005638ec + (*(int *)(param_1 + 0x14) + *(int *)(param_1 + 4) * 4) * 4);
  DAT_00563770 = (_DAT_00f25ee8 / 2 + param_6 * 0x40) / _DAT_00f25ee8;
  bVar4 = (byte)param_3;
  iVar5 = 0x20 >> (bVar4 & 0x1f);
  if (8 < iVar5) {
    iVar5 = iVar5 + -1;
  }
  if (iVar5 < DAT_00563770) {
    DAT_00563770 = iVar5;
  }
  if (0x20 < DAT_00563770) {
    DAT_00563770 = 0x20;
  }
  if (*(int *)(param_1 + 0x20) != 3) {
    DAT_00563b44 = 0x40;
    DAT_005a99e8 = 0x40;
    DAT_00563770 = DAT_00563770 * 2;
  }
  iVar5 = (param_5 & 3) + 1;
  if (*(int *)(param_1 + 0x20) == 3) {
    iVar5 = 0;
  }
  DAT_00f25ee0 = (&DAT_00563ad8)[iVar5];
  PTR_FUN_005637cc = (&PTR_FUN_00563a60)[iVar5 + (param_3 + uVar6 * 3) * 5];
  _DAT_005ab4f8 = DAT_00f25ee0 * (0x180 >> (bVar4 & 0x1f));
  DAT_005a99f0 = _DAT_005ab4f8;
  if (uVar6 == 0) {
    DAT_005a99f0 = _DAT_005ab4f8 * 2;
  }
  _DAT_00f25ee8 = _DAT_00f25ee8 >> (bVar4 & 0x1f);
  _DAT_00f25ef0 = param_2;
  _DAT_00f25eec = (-(uint)(uVar6 != 0) & 0xfffffff8) + 0x10;
  puVar7 = &DAT_00f25f00;
  DAT_00f25ee4 = _DAT_005ab4f8;
  for (iVar5 = 0x300; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
  _DAT_00f25ef4 = 0;
  FUN_005167c0();
  return 1;
}

