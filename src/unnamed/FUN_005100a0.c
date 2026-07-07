/* FUN_005100a0 - 0x005100a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_005100a0(void)

{
  float *pfVar1;
  uint *puVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 *puVar8;
  uint uVar9;
  byte *pbVar10;
  int local_c;
  int local_8;
  
  puVar8 = &DAT_00f25f00;
  local_c = 0;
  iVar6 = DAT_005ab704;
  uVar7 = DAT_005ab4f4;
  pbVar10 = DAT_005a9680;
  do {
    local_8 = 0;
    do {
      iVar4 = 0;
      uVar9 = DAT_005ab91c;
      while (uVar9 < 0x26) {
        switch(uVar9) {
        case 0:
          puVar8[iVar4] = 0;
          puVar8[iVar4 + 0x40] = 0;
          puVar8[iVar4 + 0x80] = 0;
          break;
        case 1:
          if (iVar6 < 5) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -5;
          _DAT_005ab888 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          iVar6 = _DAT_005ab888 * 3;
          DAT_005ab4f4 = uVar7 - (_DAT_005ab888 << ((byte)DAT_005ab704 & 0x1f));
          pfVar1 = (float *)(&DAT_005a99f4 + local_c * 0x40 + iVar4);
          puVar8[iVar4] = (float)(int)(char)(&DAT_005a9988)[iVar6] * *pfVar1;
          puVar8[iVar4 + 0x40] = (float)(int)(char)(&DAT_005a9989)[iVar6] * *pfVar1;
          puVar8[iVar4 + 0x80] = (float)(int)(char)(&DAT_005a998a)[iVar6] * *pfVar1;
          break;
        case 2:
          if (iVar6 < 7) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -7;
          _DAT_005ab888 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          iVar6 = _DAT_005ab888 * 3;
          DAT_005ab4f4 = uVar7 - (_DAT_005ab888 << ((byte)DAT_005ab704 & 0x1f));
          pfVar1 = (float *)(&DAT_005a99f4 + local_c * 0x40 + iVar4);
          puVar8[iVar4] = (float)(int)(char)(&DAT_005ab708)[iVar6] * *pfVar1;
          puVar8[iVar4 + 0x40] = (float)(int)(char)(&DAT_005ab709)[iVar6] * *pfVar1;
          puVar8[iVar4 + 0x80] = (float)(int)(char)(&DAT_005ab70a)[iVar6] * *pfVar1;
          break;
        case 3:
          if (iVar6 < 9) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -3;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          iVar6 = local_c * 0x40 + iVar4;
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4] = (float)(int)(uVar9 - 3) * (float)(&DAT_005a99f4)[iVar6];
          DAT_005ab704 = DAT_005ab704 + -3;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x40] = (float)(int)(uVar7 - 3) * (float)(&DAT_005a99f4)[iVar6];
          DAT_005ab704 = DAT_005ab704 + -3;
          _DAT_005ab888 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (_DAT_005ab888 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x80] = (float)(int)(_DAT_005ab888 - 3) * (float)(&DAT_005a99f4)[iVar6];
          break;
        case 4:
          if (iVar6 < 10) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -10;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          pfVar1 = (float *)(&DAT_005a99f4 + local_c * 0x40 + iVar4);
          _DAT_005ab888 = uVar9;
          puVar8[iVar4] = (float)(int)(short)(&DAT_005a9cf4)[uVar9 * 3] * *pfVar1;
          puVar8[iVar4 + 0x40] = (float)(int)(short)(&DAT_005a9cf6)[uVar9 * 3] * *pfVar1;
          puVar8[iVar4 + 0x80] = (float)(int)(short)(&DAT_005a9cf8)[uVar9 * 3] * *pfVar1;
          break;
        case 5:
          if (iVar6 < 0xc) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -4;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = local_c * 0x40 + iVar4;
          puVar8[iVar4] = (float)(int)(uVar9 - 7) * (float)(&DAT_005a99f4)[iVar6];
          DAT_005ab704 = DAT_005ab704 + -4;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x40] = (float)(int)(uVar7 - 7) * (float)(&DAT_005a99f4)[iVar6];
          DAT_005ab704 = DAT_005ab704 + -4;
          _DAT_005ab888 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (_DAT_005ab888 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x80] = (float)(int)(_DAT_005ab888 - 7) * (float)(&DAT_005a99f4)[iVar6];
          break;
        case 6:
          if (iVar6 < 0xf) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -5;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          iVar6 = local_c * 0x40 + iVar4;
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4] = (float)(int)(uVar9 - 0xf) * (float)(&DAT_005a99f4)[iVar6];
          DAT_005ab704 = DAT_005ab704 + -5;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x40] = (float)(int)(uVar7 - 0xf) * (float)(&DAT_005a99f4)[iVar6];
          DAT_005ab704 = DAT_005ab704 + -5;
          _DAT_005ab888 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (_DAT_005ab888 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x80] = (float)(int)(_DAT_005ab888 - 0xf) * (float)(&DAT_005a99f4)[iVar6];
          break;
        case 7:
          if (iVar6 < 0x12) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -6;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          iVar6 = local_c * 0x40 + iVar4;
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4] = (float)(int)(uVar9 - 0x1f) * (float)(&DAT_005a99f4)[iVar6];
          DAT_005ab704 = DAT_005ab704 + -6;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x40] = (float)(int)(uVar7 - 0x1f) * (float)(&DAT_005a99f4)[iVar6];
          DAT_005ab704 = DAT_005ab704 + -6;
          _DAT_005ab888 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (_DAT_005ab888 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x80] = (float)(int)(_DAT_005ab888 - 0x1f) * (float)(&DAT_005a99f4)[iVar6];
          break;
        case 8:
          if (iVar6 < 0x15) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -7;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          iVar6 = local_c * 0x40 + iVar4;
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4] = (float)(int)(uVar9 - 0x3f) * (float)(&DAT_005a99f4)[iVar6];
          DAT_005ab704 = DAT_005ab704 + -7;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x40] = (float)(int)(uVar7 - 0x3f) * (float)(&DAT_005a99f4)[iVar6];
          DAT_005ab704 = DAT_005ab704 + -7;
          _DAT_005ab888 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (_DAT_005ab888 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x80] = (float)(int)(_DAT_005ab888 - 0x3f) * (float)(&DAT_005a99f4)[iVar6];
          break;
        case 9:
          if (iVar6 < 0x18) {
            do {
              iVar6 = iVar6 + 8;
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            } while (iVar6 < 0x19);
          }
          DAT_005ab704 = iVar6 + -8;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          iVar6 = local_c * 0x40 + iVar4;
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4] = (float)(int)(uVar9 - 0x7f) * (float)(&DAT_005a99f4)[iVar6];
          DAT_005ab704 = DAT_005ab704 + -8;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x40] = (float)(int)(uVar7 - 0x7f) * (float)(&DAT_005a99f4)[iVar6];
          DAT_005ab704 = DAT_005ab704 + -8;
          _DAT_005ab888 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (_DAT_005ab888 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x80] = (float)(int)(_DAT_005ab888 - 0x7f) * (float)(&DAT_005a99f4)[iVar6];
          break;
        case 10:
          if (iVar6 < 0x12) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -9;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = local_c * 0x40 + iVar4;
          puVar8[iVar4] = (float)(int)(uVar9 - 0xff) * (float)(&DAT_005a99f4)[iVar6];
          DAT_005ab704 = DAT_005ab704 + -9;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x40] = (float)(int)(uVar7 - 0xff) * (float)(&DAT_005a99f4)[iVar6];
          if (DAT_005ab704 < 9) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -9;
          _DAT_005ab888 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (_DAT_005ab888 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x80] = (float)(int)(_DAT_005ab888 - 0xff) * (float)(&DAT_005a99f4)[iVar6];
          break;
        case 0xb:
          if (iVar6 < 0x14) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -10;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          iVar6 = local_c * 0x40 + iVar4;
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4] = (float)(int)(uVar9 - 0x1ff) * (float)(&DAT_005a99f4)[iVar6];
          DAT_005ab704 = DAT_005ab704 + -10;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x40] = (float)(int)(uVar7 - 0x1ff) * (float)(&DAT_005a99f4)[iVar6];
          if (DAT_005ab704 < 10) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -10;
          _DAT_005ab888 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (_DAT_005ab888 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x80] = (float)(int)(_DAT_005ab888 - 0x1ff) * (float)(&DAT_005a99f4)[iVar6]
          ;
          break;
        case 0xc:
          if (iVar6 < 0x16) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -0xb;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = local_c * 0x40 + iVar4;
          puVar8[iVar4] = (float)(int)(uVar9 - 0x3ff) * (float)(&DAT_005a99f4)[iVar6];
          DAT_005ab704 = DAT_005ab704 + -0xb;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x40] = (float)(int)(uVar7 - 0x3ff) * (float)(&DAT_005a99f4)[iVar6];
          if (DAT_005ab704 < 0xb) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -0xb;
          _DAT_005ab888 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (_DAT_005ab888 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x80] = (float)(int)(_DAT_005ab888 - 0x3ff) * (float)(&DAT_005a99f4)[iVar6]
          ;
          break;
        case 0xd:
          if (iVar6 < 0x18) {
            do {
              iVar6 = iVar6 + 8;
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            } while (iVar6 < 0x19);
          }
          DAT_005ab704 = iVar6 + -0xc;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          iVar6 = local_c * 0x40 + iVar4;
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4] = (float)(int)(uVar9 - 0x7ff) * (float)(&DAT_005a99f4)[iVar6];
          DAT_005ab704 = DAT_005ab704 + -0xc;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x40] = (float)(int)(uVar7 - 0x7ff) * (float)(&DAT_005a99f4)[iVar6];
          if (DAT_005ab704 < 0xc) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -0xc;
          _DAT_005ab888 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (_DAT_005ab888 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x80] = (float)(int)(_DAT_005ab888 - 0x7ff) * (float)(&DAT_005a99f4)[iVar6]
          ;
          break;
        case 0xe:
          if (iVar6 < 0xd) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -0xd;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = local_c * 0x40 + iVar4;
          puVar8[iVar4] = (float)(int)(uVar9 - 0xfff) * (float)(&DAT_005a99f4)[iVar6];
          if (DAT_005ab704 < 0xd) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -0xd;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x40] = (float)(int)(uVar7 - 0xfff) * (float)(&DAT_005a99f4)[iVar6];
          if (DAT_005ab704 < 0xd) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -0xd;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x80] = (float)(int)(uVar7 - 0xfff) * (float)(&DAT_005a99f4)[iVar6];
          break;
        case 0xf:
          if (iVar6 < 0xe) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -0xe;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          iVar6 = local_c * 0x40 + iVar4;
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4] = (float)(int)(uVar9 - 0x1fff) * (float)(&DAT_005a99f4)[iVar6];
          if (DAT_005ab704 < 0xe) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -0xe;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x40] = (float)(int)(uVar7 - 0x1fff) * (float)(&DAT_005a99f4)[iVar6];
          if (DAT_005ab704 < 0xe) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -0xe;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x80] = (float)(int)(uVar7 - 0x1fff) * (float)(&DAT_005a99f4)[iVar6];
          break;
        case 0x10:
          if (iVar6 < 0xf) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -0xf;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = local_c * 0x40 + iVar4;
          puVar8[iVar4] = (float)(int)(uVar9 - 0x3fff) * (float)(&DAT_005a99f4)[iVar6];
          if (DAT_005ab704 < 0xf) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -0xf;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x40] = (float)(int)(uVar7 - 0x3fff) * (float)(&DAT_005a99f4)[iVar6];
          if (DAT_005ab704 < 0xf) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -0xf;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x80] = (float)(int)(uVar7 - 0x3fff) * (float)(&DAT_005a99f4)[iVar6];
          break;
        case 0x11:
          if (iVar6 < 0x10) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -0x10;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          iVar6 = local_c * 0x40 + iVar4;
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4] = (float)(int)(uVar9 - 0x7fff) * (float)(&DAT_005a99f4)[iVar6];
          if (DAT_005ab704 < 0x10) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -0x10;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x40] = (float)(int)(uVar7 - 0x7fff) * (float)(&DAT_005a99f4)[iVar6];
          if (DAT_005ab704 < 0x10) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -0x10;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x80] = (float)(int)(uVar7 - 0x7fff) * (float)(&DAT_005a99f4)[iVar6];
          break;
        case 0x12:
          puVar8[iVar4] = 0;
          puVar8[iVar4 + 1] = 0;
          puVar8[iVar4 + 0x40] = 0;
          puVar8[iVar4 + 0x41] = 0;
          puVar8[iVar4 + 0x80] = 0;
          puVar8[iVar4 + 0x81] = 0;
          iVar4 = iVar4 + 1;
          break;
        case 0x13:
          if (iVar6 < 5) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -5;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          iVar6 = local_c * 0x40 + iVar4;
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4] =
               (float)(int)(char)(&DAT_005a9988)[uVar9 * 3] * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 1] =
               (float)(int)(char)(&DAT_005a9988)[uVar9 * 3] * (float)(&DAT_005a99f8)[iVar6];
          puVar8[iVar4 + 0x40] =
               (float)(int)(char)(&DAT_005a9989)[uVar9 * 3] * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 0x41] =
               (float)(int)(char)(&DAT_005a9989)[uVar9 * 3] * (float)(&DAT_005a99f8)[iVar6];
          puVar8[iVar4 + 0x80] =
               (float)(int)(char)(&DAT_005a998a)[uVar9 * 3] * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 0x81] =
               (float)(int)(char)(&DAT_005a998a)[uVar9 * 3] * (float)(&DAT_005a99f8)[iVar6];
          iVar4 = iVar4 + 1;
          break;
        case 0x14:
          if (iVar6 < 7) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -7;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          iVar6 = local_c * 0x40 + iVar4;
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4] =
               (float)(int)(char)(&DAT_005ab708)[uVar9 * 3] * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 1] =
               (float)(int)(char)(&DAT_005ab708)[uVar9 * 3] * (float)(&DAT_005a99f8)[iVar6];
          puVar8[iVar4 + 0x40] =
               (float)(int)(char)(&DAT_005ab709)[uVar9 * 3] * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 0x41] =
               (float)(int)(char)(&DAT_005ab709)[uVar9 * 3] * (float)(&DAT_005a99f8)[iVar6];
          puVar8[iVar4 + 0x80] =
               (float)(int)(char)(&DAT_005ab70a)[uVar9 * 3] * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 0x81] =
               (float)(int)(char)(&DAT_005ab70a)[uVar9 * 3] * (float)(&DAT_005a99f8)[iVar6];
          iVar4 = iVar4 + 1;
          break;
        case 0x15:
          if (iVar6 < 3) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -3;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          fVar3 = (float)(int)(uVar9 - 3);
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = local_c * 0x40 + iVar4;
          iVar5 = iVar6 * 4;
          puVar8[iVar4] = fVar3 * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 1] = fVar3 * (float)(&DAT_005a99f8)[iVar6];
          if (DAT_005ab704 < 3) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -3;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          fVar3 = (float)(int)(uVar7 - 3);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x40] = fVar3 * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 0x41] = fVar3 * (float)(&DAT_005a99f8)[iVar6];
          if (DAT_005ab704 < 3) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -3;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = uVar7 - 3;
          goto LAB_00512e10;
        case 0x16:
          if (iVar6 < 10) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -10;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          iVar6 = local_c * 0x40 + iVar4;
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4] =
               (float)(int)(short)(&DAT_005a9cf4)[uVar9 * 3] * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 1] =
               (float)(int)(short)(&DAT_005a9cf4)[uVar9 * 3] * (float)(&DAT_005a99f8)[iVar6];
          puVar8[iVar4 + 0x40] =
               (float)(int)(short)(&DAT_005a9cf6)[uVar9 * 3] * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 0x41] =
               (float)(int)(short)(&DAT_005a9cf6)[uVar9 * 3] * (float)(&DAT_005a99f8)[iVar6];
          puVar8[iVar4 + 0x80] =
               (float)(int)(short)(&DAT_005a9cf8)[uVar9 * 3] * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 0x81] =
               (float)(int)(short)(&DAT_005a9cf8)[uVar9 * 3] * (float)(&DAT_005a99f8)[iVar6];
          iVar4 = iVar4 + 1;
          break;
        case 0x17:
          if (iVar6 < 4) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -4;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          fVar3 = (float)(int)(uVar9 - 7);
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = local_c * 0x40 + iVar4;
          iVar5 = iVar6 * 4;
          puVar8[iVar4] = fVar3 * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 1] = fVar3 * (float)(&DAT_005a99f8)[iVar6];
          if (DAT_005ab704 < 4) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -4;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          fVar3 = (float)(int)(uVar7 - 7);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x40] = fVar3 * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 0x41] = fVar3 * (float)(&DAT_005a99f8)[iVar6];
          if (DAT_005ab704 < 4) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -4;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = uVar7 - 7;
          goto LAB_00512e10;
        case 0x18:
          if (iVar6 < 5) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -5;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          fVar3 = (float)(int)(uVar9 - 0xf);
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = local_c * 0x40 + iVar4;
          iVar5 = iVar6 * 4;
          puVar8[iVar4] = fVar3 * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 1] = fVar3 * (float)(&DAT_005a99f8)[iVar6];
          if (DAT_005ab704 < 5) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -5;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          fVar3 = (float)(int)(uVar7 - 0xf);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x40] = fVar3 * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 0x41] = fVar3 * (float)(&DAT_005a99f8)[iVar6];
          if (DAT_005ab704 < 5) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -5;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = uVar7 - 0xf;
          goto LAB_00512e10;
        case 0x19:
          if (iVar6 < 6) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -6;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          fVar3 = (float)(int)(uVar9 - 0x1f);
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = local_c * 0x40 + iVar4;
          iVar5 = iVar6 * 4;
          puVar8[iVar4] = fVar3 * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 1] = fVar3 * (float)(&DAT_005a99f8)[iVar6];
          if (DAT_005ab704 < 6) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -6;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          fVar3 = (float)(int)(uVar7 - 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x40] = fVar3 * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 0x41] = fVar3 * (float)(&DAT_005a99f8)[iVar6];
          if (DAT_005ab704 < 6) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -6;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = uVar7 - 0x1f;
          goto LAB_00512e10;
        case 0x1a:
          if (iVar6 < 7) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -7;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          fVar3 = (float)(int)(uVar9 - 0x3f);
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = local_c * 0x40 + iVar4;
          iVar5 = iVar6 * 4;
          puVar8[iVar4] = fVar3 * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 1] = fVar3 * (float)(&DAT_005a99f8)[iVar6];
          if (DAT_005ab704 < 7) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -7;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          fVar3 = (float)(int)(uVar7 - 0x3f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x40] = fVar3 * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 0x41] = fVar3 * (float)(&DAT_005a99f8)[iVar6];
          if (DAT_005ab704 < 7) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -7;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = uVar7 - 0x3f;
          goto LAB_00512e10;
        case 0x1b:
          if (iVar6 < 8) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -8;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          fVar3 = (float)(int)(uVar9 - 0x7f);
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = local_c * 0x40 + iVar4;
          iVar5 = iVar6 * 4;
          puVar8[iVar4] = fVar3 * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 1] = fVar3 * (float)(&DAT_005a99f8)[iVar6];
          if (DAT_005ab704 < 8) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -8;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          fVar3 = (float)(int)(uVar7 - 0x7f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x40] = fVar3 * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 0x41] = fVar3 * (float)(&DAT_005a99f8)[iVar6];
          if (DAT_005ab704 < 8) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -8;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = uVar7 - 0x7f;
          goto LAB_00512e10;
        case 0x1c:
          if (iVar6 < 9) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -9;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          fVar3 = (float)(int)(uVar9 - 0xff);
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = local_c * 0x40 + iVar4;
          iVar5 = iVar6 * 4;
          puVar8[iVar4] = fVar3 * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 1] = fVar3 * (float)(&DAT_005a99f8)[iVar6];
          if (DAT_005ab704 < 9) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -9;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          fVar3 = (float)(int)(uVar7 - 0xff);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x40] = fVar3 * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 0x41] = fVar3 * (float)(&DAT_005a99f8)[iVar6];
          if (DAT_005ab704 < 9) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -9;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = uVar7 - 0xff;
          goto LAB_00512e10;
        case 0x1d:
          if (iVar6 < 10) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -10;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          fVar3 = (float)(int)(uVar9 - 0x1ff);
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = local_c * 0x40 + iVar4;
          iVar5 = iVar6 * 4;
          puVar8[iVar4] = fVar3 * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 1] = fVar3 * (float)(&DAT_005a99f8)[iVar6];
          if (DAT_005ab704 < 10) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -10;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          fVar3 = (float)(int)(uVar7 - 0x1ff);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x40] = fVar3 * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 0x41] = fVar3 * (float)(&DAT_005a99f8)[iVar6];
          if (DAT_005ab704 < 10) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -10;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = uVar7 - 0x1ff;
          goto LAB_00512e10;
        case 0x1e:
          if (iVar6 < 0xb) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -0xb;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          fVar3 = (float)(int)(uVar9 - 0x3ff);
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = local_c * 0x40 + iVar4;
          iVar5 = iVar6 * 4;
          puVar8[iVar4] = fVar3 * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 1] = fVar3 * (float)(&DAT_005a99f8)[iVar6];
          if (DAT_005ab704 < 0xb) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -0xb;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          fVar3 = (float)(int)(uVar7 - 0x3ff);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x40] = fVar3 * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 0x41] = fVar3 * (float)(&DAT_005a99f8)[iVar6];
          if (DAT_005ab704 < 0xb) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -0xb;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = uVar7 - 0x3ff;
          goto LAB_00512e10;
        case 0x1f:
          if (iVar6 < 0xc) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -0xc;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          fVar3 = (float)(int)(uVar9 - 0x7ff);
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = local_c * 0x40 + iVar4;
          iVar5 = iVar6 * 4;
          puVar8[iVar4] = fVar3 * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 1] = fVar3 * (float)(&DAT_005a99f8)[iVar6];
          if (DAT_005ab704 < 0xc) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -0xc;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          fVar3 = (float)(int)(uVar7 - 0x7ff);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x40] = fVar3 * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 0x41] = fVar3 * (float)(&DAT_005a99f8)[iVar6];
          if (DAT_005ab704 < 0xc) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -0xc;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = uVar7 - 0x7ff;
          goto LAB_00512e10;
        case 0x20:
          if (iVar6 < 0xd) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -0xd;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          fVar3 = (float)(int)(uVar9 - 0xfff);
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = local_c * 0x40 + iVar4;
          iVar5 = iVar6 * 4;
          puVar8[iVar4] = fVar3 * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 1] = fVar3 * (float)(&DAT_005a99f8)[iVar6];
          if (DAT_005ab704 < 0xd) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -0xd;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          fVar3 = (float)(int)(uVar7 - 0xfff);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x40] = fVar3 * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 0x41] = fVar3 * (float)(&DAT_005a99f8)[iVar6];
          if (DAT_005ab704 < 0xd) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -0xd;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = uVar7 - 0xfff;
          goto LAB_00512e10;
        case 0x21:
          if (iVar6 < 0xe) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -0xe;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          fVar3 = (float)(int)(uVar9 - 0x1fff);
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = local_c * 0x40 + iVar4;
          iVar5 = iVar6 * 4;
          puVar8[iVar4] = fVar3 * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 1] = fVar3 * (float)(&DAT_005a99f8)[iVar6];
          if (DAT_005ab704 < 0xe) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -0xe;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          fVar3 = (float)(int)(uVar7 - 0x1fff);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x40] = fVar3 * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 0x41] = fVar3 * (float)(&DAT_005a99f8)[iVar6];
          if (DAT_005ab704 < 0xe) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -0xe;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = uVar7 - 0x1fff;
          goto LAB_00512e10;
        case 0x22:
          if (iVar6 < 0xf) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -0xf;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          fVar3 = (float)(int)(uVar9 - 0x3fff);
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = local_c * 0x40 + iVar4;
          iVar5 = iVar6 * 4;
          puVar8[iVar4] = fVar3 * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 1] = fVar3 * (float)(&DAT_005a99f8)[iVar6];
          if (DAT_005ab704 < 0xf) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -0xf;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          fVar3 = (float)(int)(uVar7 - 0x3fff);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x40] = fVar3 * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 0x41] = fVar3 * (float)(&DAT_005a99f8)[iVar6];
          if (DAT_005ab704 < 0xf) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -0xf;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = uVar7 - 0x3fff;
          goto LAB_00512e10;
        case 0x23:
          if (iVar6 < 0x10) {
            for (; iVar6 < 0x19; iVar6 = iVar6 + 8) {
              uVar7 = uVar7 << 8 | (uint)*pbVar10;
              pbVar10 = pbVar10 + 1;
              DAT_005a9680 = pbVar10;
            }
          }
          DAT_005ab704 = iVar6 + -0x10;
          uVar9 = uVar7 >> ((byte)DAT_005ab704 & 0x1f);
          fVar3 = (float)(int)(uVar9 - 0x7fff);
          DAT_005ab4f4 = uVar7 - (uVar9 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = local_c * 0x40 + iVar4;
          iVar5 = iVar6 * 4;
          puVar8[iVar4] = fVar3 * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 1] = fVar3 * (float)(&DAT_005a99f8)[iVar6];
          if (DAT_005ab704 < 0x10) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -0x10;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          fVar3 = (float)(int)(uVar7 - 0x7fff);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          puVar8[iVar4 + 0x40] = fVar3 * (float)(&DAT_005a99f4)[iVar6];
          puVar8[iVar4 + 0x41] = fVar3 * (float)(&DAT_005a99f8)[iVar6];
          if (DAT_005ab704 < 0x10) {
            for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
              DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
              DAT_005a9680 = DAT_005a9680 + 1;
            }
          }
          DAT_005ab704 = DAT_005ab704 + -0x10;
          uVar7 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
          DAT_005ab4f4 = DAT_005ab4f4 - (uVar7 << ((byte)DAT_005ab704 & 0x1f));
          iVar6 = uVar7 - 0x7fff;
LAB_00512e10:
          puVar8[iVar4 + 0x80] = (float)iVar6 * *(float *)((int)&DAT_005a99f4 + iVar5);
          puVar8[iVar4 + 0x81] = (float)iVar6 * *(float *)((int)&DAT_005a99f8 + iVar5);
          iVar4 = iVar4 + 1;
          break;
        case 0x25:
          iVar4 = DAT_005ab8d4;
          if (iVar6 < DAT_005ab8d4) {
            iVar5 = DAT_005ab8d4 - iVar6 >> 3;
            uVar7 = (uint)pbVar10[iVar5];
            iVar4 = (DAT_005ab8d4 - iVar6) + iVar5 * -8;
            pbVar10 = pbVar10 + iVar5 + 1;
            iVar6 = 8;
            DAT_005a9680 = pbVar10;
          }
          iVar6 = iVar6 - iVar4;
          uVar7 = uVar7 - ((uVar7 >> ((byte)iVar6 & 0x1f)) << ((byte)iVar6 & 0x1f));
          DAT_005ab4f4 = uVar7;
          DAT_005ab704 = iVar6;
        case 0x24:
          puVar8 = puVar8 + 0xc0;
          goto LAB_00512eb1;
        }
        puVar2 = &DAT_005ab920 + iVar4;
        iVar4 = iVar4 + 1;
        iVar6 = DAT_005ab704;
        uVar7 = DAT_005ab4f4;
        pbVar10 = DAT_005a9680;
        uVar9 = *puVar2;
      }
LAB_00512eb1:
      local_8 = local_8 + 1;
    } while (local_8 < 4);
    local_c = local_c + 1;
    if (2 < local_c) {
      return;
    }
  } while( true );
}

