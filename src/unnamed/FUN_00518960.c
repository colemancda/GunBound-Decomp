/* FUN_00518960 - 0x00518960 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00518960(uint *param_1,int param_2,int param_3)

{
  byte *pbVar1;
  int iVar2;
  int iVar3;
  byte bVar4;
  byte *pbVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  byte *pbVar9;
  uint *local_4;
  
  if (0 < param_2) {
    param_2 = param_2 >> 1;
    pbVar1 = (&PTR_DAT_00568180)[param_3 * 3];
    iVar3 = *(int *)(&DAT_00568184 + param_3 * 0xc);
    iVar2 = *(int *)(&DAT_00568188 + param_3 * 0xc);
    if (iVar2 == 1) {
      param_3 = 0;
      if (0 < param_2) {
        do {
          if (DAT_00f25e04 < 0xb) {
            for (; DAT_00f25e04 < 0x19; DAT_00f25e04 = DAT_00f25e04 + 8) {
              DAT_00f25e00 = DAT_00f25e00 << 8 | (uint)*DAT_00f25e08;
              DAT_00f25e08 = DAT_00f25e08 + 1;
            }
          }
          uVar8 = DAT_00f25e00 >> ((char)DAT_00f25e04 - *pbVar1 & 0x1f);
          DAT_00f25e04 = DAT_00f25e04 - (uint)pbVar1[uVar8 * 4 + 7];
          DAT_00f25e00 = DAT_00f25e00 -
                         ((DAT_00f25e00 >> ((byte)DAT_00f25e04 & 0x1f)) <<
                         ((byte)DAT_00f25e04 & 0x1f));
          uVar6 = (uint)pbVar1[uVar8 * 4 + 5];
          uVar8 = (uint)pbVar1[uVar8 * 4 + 6];
          if (uVar6 != 0) {
            DAT_00f25e04 = DAT_00f25e04 + -1;
            uVar7 = DAT_00f25e00 >> ((byte)DAT_00f25e04 & 0x1f);
            DAT_00f25e00 = DAT_00f25e00 - (uVar7 << ((byte)DAT_00f25e04 & 0x1f));
            if (uVar7 != 0) {
              uVar6 = -uVar6;
            }
          }
          if (uVar8 != 0) {
            DAT_00f25e04 = DAT_00f25e04 + -1;
            uVar7 = DAT_00f25e00 >> ((byte)DAT_00f25e04 & 0x1f);
            DAT_00f25e00 = DAT_00f25e00 - (uVar7 << ((byte)DAT_00f25e04 & 0x1f));
            if (uVar7 != 0) {
              uVar8 = -uVar8;
            }
          }
          *param_1 = uVar6;
          param_1[1] = uVar8;
          if (DAT_00f25e10 < DAT_00f25e08) {
            return;
          }
          param_1 = param_1 + 2;
          param_3 = param_3 + 1;
        } while (param_3 < param_2);
      }
    }
    else if (iVar2 == 2) {
      param_3 = 0;
      pbVar5 = DAT_00f25e08;
      pbVar9 = pbVar1;
      if (0 < param_2) {
        while( true ) {
          while( true ) {
            iVar3 = DAT_00f25e04;
            if (DAT_00f25e04 < 0xb) {
              for (; iVar3 < 0x19; iVar3 = iVar3 + 8) {
                DAT_00f25e00 = DAT_00f25e00 << 8 | (uint)*pbVar5;
                pbVar5 = pbVar5 + 1;
                DAT_00f25e08 = pbVar5;
              }
            }
            DAT_00f25e04 = iVar3 - (uint)*pbVar9;
            bVar4 = (byte)DAT_00f25e04;
            uVar6 = DAT_00f25e00 >> (bVar4 & 0x1f);
            if (pbVar9[uVar6 * 4 + 7] != 0) break;
            DAT_00f25e00 = DAT_00f25e00 - ((DAT_00f25e00 >> (bVar4 & 0x1f)) << (bVar4 & 0x1f));
            pbVar9 = pbVar9 + *(int *)(pbVar9 + uVar6 * 4 + 4) * 4;
          }
          DAT_00f25e04 = iVar3 - (uint)pbVar9[uVar6 * 4 + 7];
          DAT_00f25e00 = DAT_00f25e00 -
                         ((DAT_00f25e00 >> ((byte)DAT_00f25e04 & 0x1f)) <<
                         ((byte)DAT_00f25e04 & 0x1f));
          uVar8 = (uint)pbVar9[uVar6 * 4 + 5];
          uVar6 = (uint)pbVar9[uVar6 * 4 + 6];
          if (uVar8 != 0) {
            DAT_00f25e04 = DAT_00f25e04 + -1;
            uVar7 = DAT_00f25e00 >> ((byte)DAT_00f25e04 & 0x1f);
            DAT_00f25e00 = DAT_00f25e00 - (uVar7 << ((byte)DAT_00f25e04 & 0x1f));
            if (uVar7 != 0) {
              uVar8 = -uVar8;
            }
          }
          if (uVar6 != 0) {
            DAT_00f25e04 = DAT_00f25e04 + -1;
            uVar7 = DAT_00f25e00 >> ((byte)DAT_00f25e04 & 0x1f);
            DAT_00f25e00 = DAT_00f25e00 - (uVar7 << ((byte)DAT_00f25e04 & 0x1f));
            if (uVar7 != 0) {
              uVar6 = -uVar6;
            }
          }
          *param_1 = uVar8;
          param_1[1] = uVar6;
          if (DAT_00f25e10 < DAT_00f25e08) break;
          param_1 = param_1 + 2;
          param_3 = param_3 + 1;
          pbVar5 = DAT_00f25e08;
          pbVar9 = pbVar1;
          if (param_2 <= param_3) {
            return;
          }
        }
      }
    }
    else if (iVar2 == 3) {
      param_3 = 0;
      if (0 < param_2) {
        local_4 = param_1;
        pbVar5 = DAT_00f25e08;
        pbVar9 = pbVar1;
        while( true ) {
          while( true ) {
            iVar2 = DAT_00f25e04;
            if (DAT_00f25e04 < 0xb) {
              for (; iVar2 < 0x19; iVar2 = iVar2 + 8) {
                DAT_00f25e00 = DAT_00f25e00 << 8 | (uint)*pbVar5;
                pbVar5 = pbVar5 + 1;
                DAT_00f25e08 = pbVar5;
              }
            }
            DAT_00f25e04 = iVar2 - (uint)*pbVar9;
            bVar4 = (byte)DAT_00f25e04;
            uVar6 = DAT_00f25e00 >> (bVar4 & 0x1f);
            if (pbVar9[uVar6 * 4 + 7] != 0) break;
            DAT_00f25e00 = DAT_00f25e00 - ((DAT_00f25e00 >> (bVar4 & 0x1f)) << (bVar4 & 0x1f));
            pbVar9 = pbVar9 + *(int *)(pbVar9 + uVar6 * 4 + 4) * 4;
          }
          DAT_00f25e04 = iVar2 - (uint)pbVar9[uVar6 * 4 + 7];
          DAT_00f25e00 = DAT_00f25e00 -
                         ((DAT_00f25e00 >> ((byte)DAT_00f25e04 & 0x1f)) <<
                         ((byte)DAT_00f25e04 & 0x1f));
          uVar8 = (uint)pbVar9[uVar6 * 4 + 6];
          uVar6 = (uint)pbVar9[uVar6 * 4 + 5];
          if (uVar6 == 0xf) {
            if (DAT_00f25e04 < iVar3 + 2) {
              for (; DAT_00f25e04 < 0x19; DAT_00f25e04 = DAT_00f25e04 + 8) {
                DAT_00f25e00 = DAT_00f25e00 << 8 | (uint)*pbVar5;
                pbVar5 = pbVar5 + 1;
                DAT_00f25e08 = pbVar5;
              }
            }
            DAT_00f25e04 = DAT_00f25e04 - iVar3;
            uVar6 = DAT_00f25e00 >> ((byte)DAT_00f25e04 & 0x1f);
            DAT_00f25e00 = DAT_00f25e00 - (uVar6 << ((byte)DAT_00f25e04 & 0x1f));
            uVar6 = uVar6 + 0xf;
          }
          if (uVar6 != 0) {
            DAT_00f25e04 = DAT_00f25e04 + -1;
            uVar7 = DAT_00f25e00 >> ((byte)DAT_00f25e04 & 0x1f);
            DAT_00f25e00 = DAT_00f25e00 - (uVar7 << ((byte)DAT_00f25e04 & 0x1f));
            if (uVar7 != 0) {
              uVar6 = -uVar6;
            }
          }
          if (uVar8 == 0xf) {
            if (DAT_00f25e04 < iVar3 + 2) {
              for (; DAT_00f25e04 < 0x19; DAT_00f25e04 = DAT_00f25e04 + 8) {
                DAT_00f25e00 = DAT_00f25e00 << 8 | (uint)*pbVar5;
                pbVar5 = pbVar5 + 1;
                DAT_00f25e08 = pbVar5;
              }
            }
            DAT_00f25e04 = DAT_00f25e04 - iVar3;
            uVar8 = DAT_00f25e00 >> ((byte)DAT_00f25e04 & 0x1f);
            DAT_00f25e00 = DAT_00f25e00 - (uVar8 << ((byte)DAT_00f25e04 & 0x1f));
            uVar8 = uVar8 + 0xf;
          }
          if (uVar8 != 0) {
            DAT_00f25e04 = DAT_00f25e04 + -1;
            uVar7 = DAT_00f25e00 >> ((byte)DAT_00f25e04 & 0x1f);
            DAT_00f25e00 = DAT_00f25e00 - (uVar7 << ((byte)DAT_00f25e04 & 0x1f));
            if (uVar7 != 0) {
              uVar8 = -uVar8;
            }
          }
          *local_4 = uVar6;
          local_4[1] = uVar8;
          if (DAT_00f25e10 < DAT_00f25e08) break;
          local_4 = local_4 + 2;
          param_3 = param_3 + 1;
          pbVar5 = DAT_00f25e08;
          pbVar9 = pbVar1;
          if (param_2 <= param_3) {
            return;
          }
        }
      }
    }
    else if (0 < param_2) {
      do {
        *param_1 = 0;
        param_1[1] = 0;
        param_1 = param_1 + 2;
        param_2 = param_2 + -1;
      } while (param_2 != 0);
      return;
    }
  }
  return;
}

