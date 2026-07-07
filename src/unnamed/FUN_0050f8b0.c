/* FUN_0050f8b0 - 0x0050f8b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_0050f8b0(byte *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  byte *pbVar7;
  uint uVar8;
  uint uVar9;
  int *piVar10;
  undefined4 *local_24;
  int *local_20;
  int local_1c;
  int *local_18;
  undefined4 *local_14;
  int local_10;
  int local_c;
  int local_8;
  
  iVar2 = 0;
  uVar8 = 0;
  iVar5 = 0;
  do {
    iVar4 = iVar5;
    iVar5 = iVar4 + 8;
    uVar8 = uVar8 << 8 | (uint)*param_1;
    param_1 = param_1 + 1;
  } while (iVar5 < 0x19);
  DAT_005ab704 = iVar4 + -4;
  uVar9 = uVar8 >> ((byte)DAT_005ab704 & 0x1f);
  DAT_005ab4f4 = uVar8 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
  uVar6 = 0;
  DAT_005a9680 = param_1;
  if (uVar9 == 0xfff) {
    if (DAT_005ab704 < 3) {
      for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
        DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
        DAT_005a9680 = DAT_005a9680 + 1;
      }
    }
    iVar5 = DAT_005ab704 + -3;
    uVar8 = DAT_005ab4f4 - ((DAT_005ab4f4 >> ((byte)iVar5 & 0x1f)) << ((byte)iVar5 & 0x1f));
    if (iVar5 < 1) {
      for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
        uVar8 = uVar8 << 8 | (uint)*DAT_005a9680;
        DAT_005a9680 = DAT_005a9680 + 1;
      }
    }
    iVar5 = iVar5 + -1;
    uVar9 = uVar8 >> ((byte)iVar5 & 0x1f);
    uVar8 = uVar8 - (uVar9 << ((byte)iVar5 & 0x1f));
    if (iVar5 < 6) {
      for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
        uVar8 = uVar8 << 8 | (uint)*DAT_005a9680;
        DAT_005a9680 = DAT_005a9680 + 1;
      }
    }
    iVar5 = iVar5 + -6;
    uVar8 = uVar8 - ((uVar8 >> ((byte)iVar5 & 0x1f)) << ((byte)iVar5 & 0x1f));
    if (iVar5 < 1) {
      for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
        uVar8 = uVar8 << 8 | (uint)*DAT_005a9680;
        DAT_005a9680 = DAT_005a9680 + 1;
      }
    }
    iVar5 = iVar5 + -1;
    DAT_005a99ec = uVar8 >> ((byte)iVar5 & 0x1f);
    uVar8 = uVar8 - (DAT_005a99ec << ((byte)iVar5 & 0x1f));
    if (iVar5 < 1) {
      for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
        uVar8 = uVar8 << 8 | (uint)*DAT_005a9680;
        DAT_005a9680 = DAT_005a9680 + 1;
      }
    }
    iVar5 = iVar5 + -1;
    uVar8 = uVar8 - ((uVar8 >> ((byte)iVar5 & 0x1f)) << ((byte)iVar5 & 0x1f));
    if (iVar5 < 4) {
      for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
        uVar8 = uVar8 << 8 | (uint)*DAT_005a9680;
        DAT_005a9680 = DAT_005a9680 + 1;
      }
    }
    iVar5 = iVar5 + -4;
    uVar3 = uVar8 >> ((byte)iVar5 & 0x1f);
    _DAT_005ab8d8 = *(int *)(&DAT_00563730 + uVar3 * 4);
    uVar8 = uVar8 - (uVar3 << ((byte)iVar5 & 0x1f));
    if (uVar9 == 0) {
      if (iVar5 < 0x14) {
        for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
          uVar8 = uVar8 << 8 | (uint)*DAT_005a9680;
          DAT_005a9680 = DAT_005a9680 + 1;
        }
      }
      iVar5 = iVar5 + -0x14;
    }
    else {
      if (iVar5 < 4) {
        for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
          uVar8 = uVar8 << 8 | (uint)*DAT_005a9680;
          DAT_005a9680 = DAT_005a9680 + 1;
        }
      }
      iVar5 = iVar5 + -4;
    }
    DAT_005ab8d4 = 0;
    local_c = 0;
    uVar8 = uVar8 - ((uVar8 >> ((byte)iVar5 & 0x1f)) << ((byte)iVar5 & 0x1f));
    iVar2 = 0;
    local_10 = 0;
    pbVar7 = DAT_005a9680;
    DAT_005ab4f4 = uVar8;
    DAT_005ab704 = iVar5;
    local_8 = _DAT_005ab8d8;
    do {
      iVar4 = *(int *)((int)&DAT_005637bc + local_10);
      local_1c = 0;
      if (0 < iVar4) {
        local_20 = &DAT_005ab608 + iVar2;
        local_14 = &DAT_005a9688 + iVar2;
        local_24 = &DAT_005a9684 + iVar2;
        local_18 = &DAT_005ab920 + iVar2;
        param_1 = (byte *)(&DAT_005ab604 + iVar2);
        piVar10 = &DAT_005ab91c + iVar2;
        do {
          if (iVar5 < 4) {
            for (; iVar5 < 0x19; iVar5 = iVar5 + 8) {
              uVar8 = uVar8 << 8 | (uint)*pbVar7;
              pbVar7 = pbVar7 + 1;
              DAT_005a9680 = pbVar7;
            }
          }
          iVar5 = iVar5 - *(int *)((int)&DAT_005637d4 + local_10);
          _DAT_005ab888 = uVar8 >> ((byte)iVar5 & 0x1f);
          uVar8 = uVar8 - (_DAT_005ab888 << ((byte)iVar5 & 0x1f));
          iVar1 = (&DAT_005a9784)[local_c + _DAT_005ab888];
          DAT_005ab4f4 = uVar8;
          DAT_005ab704 = iVar5;
          *piVar10 = iVar1;
          *(int *)param_1 = iVar1;
          if (DAT_00563770 <= iVar2) {
            DAT_005ab8d4 = DAT_005ab8d4 + *(int *)(&DAT_00563774 + iVar1 * 4);
          }
          uVar6 = *(undefined4 *)(&DAT_005ab88c + iVar1 * 4);
          *local_24 = uVar6;
          local_8 = local_8 + -1;
          if (local_8 < 0) {
            *local_20 = iVar1;
            iVar2 = iVar2 + 1;
            *piVar10 = iVar1 + 0x12;
            *local_18 = iVar1 + 0x12;
            *local_14 = uVar6;
            param_1 = (byte *)((int)param_1 + 4);
            local_24 = local_24 + 1;
            local_20 = local_20 + 1;
            local_14 = local_14 + 1;
            piVar10 = piVar10 + 1;
            local_18 = local_18 + 1;
            local_1c = local_1c + 1;
          }
          param_1 = (byte *)((int)param_1 + 4);
          local_1c = local_1c + 1;
          local_24 = local_24 + 1;
          iVar2 = iVar2 + 1;
          local_20 = local_20 + 1;
          piVar10 = piVar10 + 1;
          local_18 = local_18 + 1;
          local_14 = local_14 + 1;
          pbVar7 = DAT_005a9680;
        } while (local_1c < iVar4);
      }
      local_10 = local_10 + 4;
      local_c = local_c + 0x10;
    } while (local_10 < 0x10);
    (&DAT_005ab91c)[DAT_00563770] = 0x25;
    (&DAT_005ab91c)[iVar2] = 0x24;
    FUN_0050fd90();
    FUN_0050fe50();
    FUN_005100a0();
    (*(code *)PTR_FUN_005637cc)(&DAT_00f25f00,param_2,0x24);
    iVar2 = DAT_005a9884 + DAT_005a99ec;
    uVar6 = DAT_005a99f0;
  }
  return CONCAT44(uVar6,iVar2);
}

