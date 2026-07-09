/* FUN_00518e30 - 0x00518e30 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_00518e30(int param_1,int param_2,int param_3,uint param_4)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int local_14;
  uint *local_10;
  int local_c;
  uint local_8;
  uint *local_4;
  
  param_2 = param_2 >> 2;
  local_8 = 0xf;
  SUBFIELD(local_8,0,undefined1) = 0xf;
  local_c = -1;
  if (param_4 == 0) {
    local_14 = 0;
    iVar9 = 0;
    if (0 < param_2) {
      local_4 = (uint *)(param_1 + 8);
      do {
        iVar9 = local_14;
        if (param_3 < 1) break;
        if (DAT_00f25e04 < 10) {
          for (; DAT_00f25e04 < 0x19; DAT_00f25e04 = DAT_00f25e04 + 8) {
            DAT_00f25e00 = DAT_00f25e00 << 8 | (uint)*DAT_00f25e08;
            DAT_00f25e08 = DAT_00f25e08 + 1;
          }
        }
        uVar4 = DAT_00f25e00 >> ((char)DAT_00f25e04 - 6U & 0x1f);
        DAT_00f25e04 = DAT_00f25e04 - (uint)(byte)(&DAT_00568100)[uVar4 * 2];
        param_3 = param_3 - (uint)(byte)(&DAT_00568100)[uVar4 * 2];
        uVar6 = (uint)(byte)(&DAT_00568101)[uVar4 * 2];
        DAT_00f25e00 = DAT_00f25e00 -
                       ((DAT_00f25e00 >> ((byte)DAT_00f25e04 & 0x1f)) << ((byte)DAT_00f25e04 & 0x1f)
                       );
        if (uVar6 != 0) {
          local_c = local_14;
          local_8 = uVar6;
        }
        param_4 = uVar6 & 1;
        uVar7 = (int)uVar6 >> 3 & 1;
        uVar5 = (int)uVar6 >> 2 & 1;
        uVar6 = (int)uVar6 >> 1 & 1;
        if (uVar7 != 0) {
          DAT_00f25e04 = DAT_00f25e04 + -1;
          uVar8 = DAT_00f25e00 >> ((byte)DAT_00f25e04 & 0x1f);
          DAT_00f25e00 = DAT_00f25e00 - (uVar8 << ((byte)DAT_00f25e04 & 0x1f));
          if (uVar8 != 0) {
            uVar7 = -uVar7;
          }
          param_3 = param_3 + -1;
        }
        if (uVar5 != 0) {
          DAT_00f25e04 = DAT_00f25e04 + -1;
          uVar8 = DAT_00f25e00 >> ((byte)DAT_00f25e04 & 0x1f);
          DAT_00f25e00 = DAT_00f25e00 - (uVar8 << ((byte)DAT_00f25e04 & 0x1f));
          if (uVar8 != 0) {
            uVar5 = -uVar5;
          }
          param_3 = param_3 + -1;
        }
        if (uVar6 != 0) {
          DAT_00f25e04 = DAT_00f25e04 + -1;
          uVar8 = DAT_00f25e00 >> ((byte)DAT_00f25e04 & 0x1f);
          DAT_00f25e00 = DAT_00f25e00 - (uVar8 << ((byte)DAT_00f25e04 & 0x1f));
          if (uVar8 != 0) {
            uVar6 = -uVar6;
          }
          param_3 = param_3 + -1;
        }
        if (((&DAT_00568101)[uVar4 * 2] & 1) != 0) {
          DAT_00f25e04 = DAT_00f25e04 + -1;
          uVar4 = DAT_00f25e00 >> ((byte)DAT_00f25e04 & 0x1f);
          DAT_00f25e00 = DAT_00f25e00 - (uVar4 << ((byte)DAT_00f25e04 & 0x1f));
          if (uVar4 != 0) {
            param_4 = -param_4;
          }
          param_3 = param_3 + -1;
        }
        local_4[-2] = uVar7;
        local_4[-1] = uVar5;
        *local_4 = uVar6;
        local_4[1] = param_4;
        if (DAT_00f25e10 < DAT_00f25e08) break;
        local_4 = local_4 + 4;
        iVar9 = local_14 + 1;
        local_14 = iVar9;
      } while (iVar9 < param_2);
    }
    if (param_3 < 0) {
      puVar2 = (undefined4 *)(param_1 + (iVar9 + -1) * 0x10);
      *puVar2 = 0;
      puVar2[1] = 0;
      puVar2[2] = 0;
      puVar2[3] = 0;
    }
    iVar9 = local_c * 4 + 4;
    if (((byte)local_8 & 3) == 0) {
      iVar9 = local_c * 4 + 2;
    }
  }
  else {
    local_14 = 0;
    iVar9 = 0;
    if (0 < param_2) {
      local_10 = (uint *)(param_1 + 8);
      do {
        iVar9 = local_14;
        if (param_3 < 4) break;
        if (DAT_00f25e04 < 8) {
          for (; DAT_00f25e04 < 0x19; DAT_00f25e04 = DAT_00f25e04 + 8) {
            DAT_00f25e00 = DAT_00f25e00 << 8 | (uint)*DAT_00f25e08;
            DAT_00f25e08 = DAT_00f25e08 + 1;
          }
        }
        iVar3 = DAT_00f25e04 + -4;
        uVar6 = DAT_00f25e00 >> ((byte)iVar3 & 0x1f);
        DAT_00f25e00 = DAT_00f25e00 - (uVar6 << ((byte)iVar3 & 0x1f));
        uVar6 = uVar6 ^ 0xf;
        if (uVar6 != 0) {
          local_c = local_14;
          local_8 = uVar6;
        }
        param_4 = uVar6 & 1;
        uVar4 = (int)uVar6 >> 3 & 1;
        uVar5 = (int)uVar6 >> 2 & 1;
        uVar6 = (int)uVar6 >> 1 & 1;
        iVar1 = param_3 + -4;
        if (uVar4 != 0) {
          iVar3 = DAT_00f25e04 + -5;
          uVar7 = DAT_00f25e00 >> ((byte)iVar3 & 0x1f);
          DAT_00f25e00 = DAT_00f25e00 - (uVar7 << ((byte)iVar3 & 0x1f));
          if (uVar7 != 0) {
            uVar4 = -uVar4;
          }
          iVar1 = param_3 + -5;
        }
        param_3 = iVar1;
        DAT_00f25e04 = iVar3;
        if (uVar5 != 0) {
          DAT_00f25e04 = iVar3 + -1;
          uVar7 = DAT_00f25e00 >> ((byte)DAT_00f25e04 & 0x1f);
          DAT_00f25e00 = DAT_00f25e00 - (uVar7 << ((byte)DAT_00f25e04 & 0x1f));
          if (uVar7 != 0) {
            uVar5 = -uVar5;
          }
          param_3 = param_3 + -1;
        }
        if (uVar6 != 0) {
          DAT_00f25e04 = DAT_00f25e04 + -1;
          uVar7 = DAT_00f25e00 >> ((byte)DAT_00f25e04 & 0x1f);
          DAT_00f25e00 = DAT_00f25e00 - (uVar7 << ((byte)DAT_00f25e04 & 0x1f));
          if (uVar7 != 0) {
            uVar6 = -uVar6;
          }
          param_3 = param_3 + -1;
        }
        if (param_4 != 0) {
          DAT_00f25e04 = DAT_00f25e04 + -1;
          uVar7 = DAT_00f25e00 >> ((byte)DAT_00f25e04 & 0x1f);
          DAT_00f25e00 = DAT_00f25e00 - (uVar7 << ((byte)DAT_00f25e04 & 0x1f));
          if (uVar7 != 0) {
            param_4 = -param_4;
          }
          param_3 = param_3 + -1;
        }
        local_10[-2] = uVar4;
        local_10[-1] = uVar5;
        *local_10 = uVar6;
        local_10[1] = param_4;
        if (DAT_00f25e10 < DAT_00f25e08) break;
        local_10 = local_10 + 4;
        iVar9 = local_14 + 1;
        local_14 = iVar9;
      } while (iVar9 < param_2);
    }
    if (param_3 < 0) {
      puVar2 = (undefined4 *)((iVar9 + -1) * 0x10 + param_1);
      *puVar2 = 0;
      puVar2[1] = 0;
      puVar2[2] = 0;
      puVar2[3] = 0;
    }
    iVar9 = local_c * 4 + 4;
    if (((byte)local_8 & 3) == 0) {
      return local_c * 4 + 2;
    }
  }
  return iVar9;
}

