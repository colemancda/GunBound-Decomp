/* FUN_00514fc0 - 0x00514fc0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_00514fc0(byte *param_1,undefined4 *param_2)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  size_t _Size;
  int iVar4;
  uint uVar5;
  undefined2 uVar6;
  uint uVar7;
  int iVar8;
  int *piVar9;
  undefined4 *puVar10;
  bool bVar11;
  int *local_8;
  int local_4;
  
  DAT_00f25ed0 = DAT_00f25ed0 + 1;
  uVar5 = 0;
  DAT_00f25e0c = param_1;
  iVar4 = 0;
  DAT_00f25e08 = param_1;
  do {
    iVar2 = iVar4;
    iVar4 = iVar2 + 8;
    uVar5 = (uint)*DAT_00f25e08 | uVar5 << 8;
    DAT_00f25e08 = DAT_00f25e08 + 1;
  } while (iVar4 < 0x19);
  DAT_00f25e04 = iVar2 + -4;
  uVar7 = uVar5 >> ((byte)DAT_00f25e04 & 0x1f);
  DAT_00f25e00 = uVar5 - (uVar7 << ((byte)DAT_00f25e04 & 0x1f));
  if (uVar7 == 0xfff) {
    DAT_005ae34c = FUN_00514af0(1);
    FUN_00514af0(2);
    iVar4 = FUN_00514af0(1);
    iVar2 = FUN_00514af0(4);
    DAT_005ae924 = FUN_00514af0(2);
    DAT_005ae33c = FUN_00514af0(1);
    FUN_00514af0(1);
    DAT_005ae7e8 = FUN_00514af0(2);
    DAT_005ae7ec = FUN_00514af0(2);
    if (DAT_005ae7e8 != 1) {
      DAT_005ae7ec = 0;
    }
    DAT_005aba2c = DAT_005ae7ec & 1;
    DAT_005ae348 = (int)DAT_005ae7ec >> 1;
    DAT_005ada38 = 0;
    if (iVar4 == 0) {
      FUN_00514af0(0x14);
      DAT_005ada38 = 2;
    }
    else {
      FUN_00514af0(4);
    }
    if (0 < iVar2) {
      DAT_005aba30 = (*(int *)(&DAT_00563d0c + (DAT_005ae34c * 0x10 + iVar2) * 4) * 0xb40) /
                     *(int *)(&DAT_00563cec + (DAT_005ae924 + DAT_005ae34c * 4) * 4);
    }
    DAT_005ae7f0 = FUN_00514af0(9);
    bVar11 = DAT_005ae7e8 != 3;
    if (bVar11) {
      _DAT_005ae7f4 = FUN_00514af0(3);
      iVar4 = 2;
      DAT_005ae7dc = 2;
      local_4 = 0x24;
    }
    else {
      _DAT_005ae7f4 = FUN_00514af0(5);
      iVar4 = 1;
      DAT_005ae7dc = 1;
      local_4 = 0x15;
    }
    _DAT_005ae340 = (uint)bVar11;
    iVar8 = 0;
    iVar2 = 0;
    if (iVar4 != 0) {
      puVar10 = &DAT_005ae7f8;
      do {
        uVar3 = FUN_00514af0(4);
        *puVar10 = uVar3;
        iVar8 = iVar8 + 1;
        puVar10 = puVar10 + 1;
        iVar2 = DAT_005ae7dc;
      } while (iVar8 < DAT_005ae7dc);
    }
    local_8 = &DAT_005ae808;
    do {
      iVar4 = 0;
      piVar9 = local_8;
      if (0 < iVar2) {
        do {
          iVar2 = FUN_00514af0(0xc);
          piVar9[-2] = iVar2;
          iVar2 = FUN_00514af0(9);
          piVar9[-1] = iVar2;
          iVar2 = FUN_00514af0(8);
          iVar2 = iVar2 + DAT_005ae928;
          bVar11 = DAT_005ae348 != 0;
          *piVar9 = iVar2;
          if (bVar11) {
            *piVar9 = iVar2 + -2;
          }
          iVar2 = FUN_00514af0(4);
          piVar9[1] = iVar2;
          iVar2 = FUN_00514af0(1);
          piVar9[2] = iVar2;
          if (iVar2 == 0) {
            piVar9[4] = 0;
            piVar9[3] = 0;
            iVar2 = FUN_00514af0(5);
            piVar9[5] = iVar2;
            iVar2 = FUN_00514af0(5);
            piVar9[6] = iVar2;
            iVar2 = FUN_00514af0(5);
            piVar9[7] = iVar2;
            iVar2 = FUN_00514af0(4);
            piVar9[0xb] = iVar2;
            iVar2 = FUN_00514af0(3);
            piVar9[0xc] = iVar2;
          }
          else {
            iVar2 = FUN_00514af0(2);
            piVar9[3] = iVar2;
            iVar2 = FUN_00514af0(1);
            piVar9[4] = iVar2;
            iVar2 = FUN_00514af0(5);
            piVar9[5] = iVar2;
            iVar2 = FUN_00514af0(5);
            piVar9[6] = iVar2;
            iVar2 = FUN_00514af0(3);
            piVar9[8] = iVar2;
            iVar2 = FUN_00514af0(3);
            piVar9[9] = iVar2;
            iVar2 = FUN_00514af0(3);
            piVar9[10] = iVar2;
            piVar9[0xb] = 7;
            piVar9[0xc] = 0xd;
          }
          iVar2 = FUN_00514af0(1);
          piVar9[0xd] = iVar2;
          iVar2 = FUN_00514af0(1);
          piVar9[0xe] = iVar2;
          iVar2 = FUN_00514af0(1);
          piVar9[0xf] = iVar2;
          iVar4 = iVar4 + 1;
          piVar9 = piVar9 + 0x12;
          iVar2 = DAT_005ae7dc;
        } while (iVar4 < DAT_005ae7dc);
      }
      local_8 = local_8 + 0x24;
    } while ((int)local_8 < 0x5ae928);
    iVar4 = DAT_005aba30 + DAT_005ae33c;
    DAT_005ae930 = DAT_005ae934 - DAT_005ae7f0;
    DAT_005ae350 = iVar4;
    if (0x1a24 < (int)DAT_005ae934) {
      _memmove(&DAT_005aba38,&DAT_005aba38 + DAT_005ae930,DAT_005ae7f0);
      DAT_005ae930 = 0;
      DAT_005ae934 = DAT_005ae7f0;
    }
    _Size = (DAT_005ae350 - DAT_005ada38) - local_4;
    if ((-1 < (int)_Size) && ((int)_Size < 0x2001)) {
      _memmove(&DAT_005aba38 + DAT_005ae934,param_1 + DAT_005ada38 + local_4,_Size);
      uVar1 = DAT_005ae92c;
      uVar5 = DAT_005ae344;
      DAT_005ae934 = DAT_005ae934 + _Size;
      if (DAT_005ae930 < 0) {
        uVar6 = CONCAT11(DAT_005ae92c,DAT_005ae92c);
        for (uVar7 = DAT_005ae344 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
          *param_2 = CONCAT22(uVar6,uVar6);
          param_2 = param_2 + 1;
        }
        for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined1 *)param_2 = uVar1;
          param_2 = (undefined4 *)((int)param_2 + 1);
        }
        return CONCAT44(DAT_005ae344,iVar4);
      }
      DAT_005ae920 = DAT_005ae930 * 8;
      FUN_00515420(param_2,0);
      FUN_00515420((undefined1 *)(DAT_005ae7e0 + (int)param_2),1);
      return CONCAT44(DAT_005ae344,iVar4);
    }
  }
  return 0;
}

