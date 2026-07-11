/* FUN_005163d0 - 0x005163d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_005163d0(byte *param_1,undefined4 param_2,int param_3,undefined4 param_4,uint param_5,
                 int param_6)

{
  int iVar1;
  undefined4 *puVar2;
  byte bVar3;
  int iVar4;
  undefined4 *puVar5;
  int *piVar6;
  int *piVar7;
  uint uVar8;
  int iVar9;
  
  DAT_005ae930 = 0;
  DAT_005ae934 = 0;
  if (*(int *)(param_1 + 8) != 1) {
    return;
  }
  DAT_005aba28 = (-(uint)(*(int *)(param_1 + 4) != 0) & 2) + 6;
  DAT_005aba30 = param_2;
  uVar8 = (uint)((param_5 & 8) != 0);
  param_5 = param_5 & 3;
  if (param_3 < 0) {
    param_3 = 0;
  }
  else if (2 < param_3) {
    param_3 = 2;
  }
  if (param_6 < 1000) {
    param_6 = 1000;
  }
  _DAT_00f25ee8 =
       *(int *)(&DAT_00544380 + (*(int *)(param_1 + 0x14) + *(int *)(param_1 + 4) * 4) * 4);
  if ((*param_1 & 1) == 0) {
    _DAT_00f25ee8 = _DAT_00f25ee8 / 2;
  }
  _DAT_00563d9c = (_DAT_00f25ee8 / 2 + param_6 * 0x40) / _DAT_00f25ee8;
  bVar3 = (byte)param_3;
  iVar4 = 0x20 >> (bVar3 & 0x1f);
  if (8 < iVar4) {
    iVar4 = iVar4 + -1;
  }
  if (iVar4 < _DAT_00563d9c) {
    _DAT_00563d9c = iVar4;
  }
  iVar4 = *(int *)(param_1 + 4);
  if ((*param_1 & 1) == 0) {
    iVar4 = 2;
  }
  else if (iVar4 == 1) {
    iVar9 = *(int *)(&DAT_005445ec + *(int *)(param_1 + 0x14) * 0x94);
    DAT_00563d90 = *(int *)(&DAT_005445b4 + *(int *)(param_1 + 0x14) * 0x94);
    goto LAB_005164e7;
  }
  iVar9 = *(int *)(&DAT_0054442c + (*(int *)(param_1 + 0x14) + iVar4 * 3) * 0x94);
  DAT_00563d90 = *(int *)(&DAT_005443f4 + (*(int *)(param_1 + 0x14) + iVar4 * 3) * 0x94);
LAB_005164e7:
  DAT_00563d94 = iVar9 * 3;
  DAT_00563d8c = DAT_00563d90 + 8;
  if (_DAT_00563d9c * 0x12 < DAT_00563d90 + 8) {
    DAT_00563d8c = _DAT_00563d9c * 0x12;
  }
  if (DAT_00563d8c < DAT_00563d90) {
    DAT_00563d90 = DAT_00563d8c;
  }
  if (DAT_00563d8c < DAT_00563d94) {
    DAT_00563d94 = DAT_00563d8c;
  }
  DAT_00563d98 = (DAT_00563d8c + 0x11) / 0x12;
  DAT_005ae928 = 0;
  if ((*(int *)(param_1 + 0x20) != 3) && (param_5 == 1)) {
    DAT_005ae928 = 0xfffffffc;
  }
  _DAT_005ae738 = 0x480 >> (bVar3 & 0x1f);
  if (*(int *)(param_1 + 4) == 0) {
    _DAT_005ae738 = _DAT_005ae738 / 2;
  }
  DAT_00f25ee0 = 2;
  if (*(int *)(param_1 + 0x20) == 3) {
    DAT_00f25ee0 = 1;
  }
  if (param_5 != 0) {
    DAT_00f25ee0 = 1;
  }
  PTR_FUN_00563da0 = (&PTR_FUN_00563da8)[DAT_00f25ee0 + (param_3 + uVar8 * 3) * 2];
  iVar4 = param_5 + 1;
  if (*(int *)(param_1 + 0x20) == 3) {
    iVar4 = 0;
  }
  _DAT_005ae738 = _DAT_005ae738 * DAT_00f25ee0;
  PTR_FUN_00563da4 = (&PTR_LAB_00563ddc)[iVar4];
  if (uVar8 == 0) {
    DAT_005ae344 = _DAT_005ae738 * 2;
    _DAT_005ae92c = 0;
  }
  else {
    _DAT_005ae92c = 0x80;
    DAT_005ae344 = _DAT_005ae738;
  }
  _DAT_00f25ee8 = _DAT_00f25ee8 >> (bVar3 & 0x1f);
  _DAT_00f25ef0 = param_2;
  _DAT_00f25eec = (-(uint)(uVar8 != 0) & 0xfffffff8) + 0x10;
  _DAT_00f25ef4 = 0;
  DAT_005ae7e0 = DAT_005ae344 / 2;
  iVar4 = *(int *)(param_1 + 4);
  if ((*param_1 & 1) == 0) {
    iVar4 = 2;
  }
  iVar9 = 0;
  iVar4 = iVar4 * 3;
  puVar2 = &DAT_00f25d40;
  DAT_00f25ee4 = _DAT_005ae738;
  do {
    puVar5 = puVar2 + 1;
    iVar1 = (*(int *)(param_1 + 0x14) + iVar4) * 0x25 + iVar9;
    iVar9 = iVar9 + 1;
    *puVar2 = *(undefined4 *)(&DAT_005443a4 + iVar1 * 4);
    puVar2 = puVar5;
  } while ((int)puVar5 < 0xf25d98);
  iVar9 = 0;
  piVar7 = &DAT_00f25d98;
  do {
    piVar6 = piVar7 + 1;
    iVar1 = (*(int *)(param_1 + 0x14) + iVar4) * 0x25 + iVar9;
    iVar9 = iVar9 + 1;
    *piVar7 = *(int *)(&DAT_00544400 + iVar1 * 4) * 3;
    piVar7 = piVar6;
  } while ((int)piVar6 < 0xf25dcc);
  iVar9 = 0;
  piVar7 = &DAT_00f25e20;
  do {
    piVar6 = piVar7 + 1;
    iVar1 = ((*(int *)(param_1 + 0x14) + iVar4) * 0x25 + iVar9) * 4;
    iVar9 = iVar9 + 1;
    *piVar7 = *(int *)(&DAT_005443a4 + iVar1) - *(int *)(&DAT_005443a0 + iVar1);
    piVar7 = piVar6;
  } while ((int)piVar6 < 0xf25e78);
  iVar9 = 0;
  piVar7 = &DAT_00f25e78;
  do {
    piVar6 = piVar7 + 1;
    iVar1 = ((*(int *)(param_1 + 0x14) + iVar4) * 0x25 + iVar9) * 4;
    iVar9 = iVar9 + 1;
    *piVar7 = *(int *)(&DAT_00544400 + iVar1) - *(int *)(&DAT_005443fc + iVar1);
    piVar7 = piVar6;
  } while ((int)piVar6 < 0xf25eac);
  FUN_00519aa0();
  FUN_0051a120();
  InitMpegSynthesisTables();
  puVar2 = &DAT_005ada3c;
  for (iVar4 = 0x240; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = &DAT_00f25f00;
  do {
    iVar4 = 2;
    do {
      iVar9 = 0x240;
      do {
        *puVar2 = 0;
        *puVar2 = 0;
        puVar2 = puVar2 + 1;
        iVar9 = iVar9 + -1;
      } while (iVar9 != 0);
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  } while ((int)puVar2 < 0xf28300);
  PTR_FUN_00563da8 = FUN_00514fc0;
  if (*(int *)(param_1 + 4) != 1) {
    PTR_FUN_00563da8 = &LAB_005159d0;
  }
  return;
}

