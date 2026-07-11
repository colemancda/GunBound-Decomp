/* FUN_00515b90 - 0x00515b90 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00515b90(int param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  byte bVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  byte *pbVar10;
  bool bVar11;
  undefined4 local_c;
  
  if (DAT_00f25e04 < 1) {
    for (; DAT_00f25e04 < 0x19; DAT_00f25e04 = DAT_00f25e04 + 8) {
      DAT_00f25e00 = DAT_00f25e00 << 8 | (uint)*DAT_00f25e08;
      DAT_00f25e08 = DAT_00f25e08 + 1;
    }
  }
  iVar7 = DAT_00f25e04 + -1;
  DAT_005ae34c = DAT_00f25e00 >> ((byte)iVar7 & 0x1f);
  uVar9 = DAT_00f25e00 - (DAT_005ae34c << ((byte)iVar7 & 0x1f));
  if (iVar7 < 2) {
    for (; iVar7 < 0x19; iVar7 = iVar7 + 8) {
      uVar9 = uVar9 << 8 | (uint)*DAT_00f25e08;
      DAT_00f25e08 = DAT_00f25e08 + 1;
    }
  }
  iVar7 = iVar7 + -2;
  uVar9 = uVar9 - ((uVar9 >> ((byte)iVar7 & 0x1f)) << ((byte)iVar7 & 0x1f));
  if (iVar7 < 1) {
    for (; iVar7 < 0x19; iVar7 = iVar7 + 8) {
      uVar9 = uVar9 << 8 | (uint)*DAT_00f25e08;
      DAT_00f25e08 = DAT_00f25e08 + 1;
    }
  }
  iVar7 = iVar7 + -1;
  uVar1 = uVar9 >> ((byte)iVar7 & 0x1f);
  uVar9 = uVar9 - (uVar1 << ((byte)iVar7 & 0x1f));
  if (iVar7 < 4) {
    for (; iVar7 < 0x19; iVar7 = iVar7 + 8) {
      uVar9 = uVar9 << 8 | (uint)*DAT_00f25e08;
      DAT_00f25e08 = DAT_00f25e08 + 1;
    }
  }
  iVar7 = iVar7 + -4;
  uVar2 = uVar9 >> ((byte)iVar7 & 0x1f);
  uVar9 = uVar9 - (uVar2 << ((byte)iVar7 & 0x1f));
  if (iVar7 < 2) {
    for (; iVar7 < 0x19; iVar7 = iVar7 + 8) {
      uVar9 = uVar9 << 8 | (uint)*DAT_00f25e08;
      DAT_00f25e08 = DAT_00f25e08 + 1;
    }
  }
  iVar7 = iVar7 + -2;
  DAT_005ae924 = uVar9 >> ((byte)iVar7 & 0x1f);
  uVar9 = uVar9 - (DAT_005ae924 << ((byte)iVar7 & 0x1f));
  if (iVar7 < 1) {
    for (; iVar7 < 0x19; iVar7 = iVar7 + 8) {
      uVar9 = uVar9 << 8 | (uint)*DAT_00f25e08;
      DAT_00f25e08 = DAT_00f25e08 + 1;
    }
  }
  iVar7 = iVar7 + -1;
  DAT_005ae33c = uVar9 >> ((byte)iVar7 & 0x1f);
  uVar9 = uVar9 - (DAT_005ae33c << ((byte)iVar7 & 0x1f));
  if (iVar7 < 1) {
    for (; iVar7 < 0x19; iVar7 = iVar7 + 8) {
      uVar9 = uVar9 << 8 | (uint)*DAT_00f25e08;
      DAT_00f25e08 = DAT_00f25e08 + 1;
    }
  }
  iVar7 = iVar7 + -1;
  uVar9 = uVar9 - ((uVar9 >> ((byte)iVar7 & 0x1f)) << ((byte)iVar7 & 0x1f));
  if (iVar7 < 2) {
    for (; iVar7 < 0x19; iVar7 = iVar7 + 8) {
      uVar9 = uVar9 << 8 | (uint)*DAT_00f25e08;
      DAT_00f25e08 = DAT_00f25e08 + 1;
    }
  }
  iVar7 = iVar7 + -2;
  DAT_005ae7e8 = uVar9 >> ((byte)iVar7 & 0x1f);
  uVar9 = uVar9 - (DAT_005ae7e8 << ((byte)iVar7 & 0x1f));
  if (iVar7 < 2) {
    for (; iVar7 < 0x19; iVar7 = iVar7 + 8) {
      uVar9 = uVar9 << 8 | (uint)*DAT_00f25e08;
      DAT_00f25e08 = DAT_00f25e08 + 1;
    }
  }
  iVar7 = iVar7 + -2;
  DAT_005ae7ec = uVar9 >> ((byte)iVar7 & 0x1f);
  uVar9 = uVar9 - (DAT_005ae7ec << ((byte)iVar7 & 0x1f));
  if (DAT_005ae7e8 != 1) {
    DAT_005ae7ec = 0;
  }
  DAT_005aba2c = DAT_005ae7ec & 1;
  DAT_005ae348 = (int)DAT_005ae7ec >> 1;
  DAT_005ada38 = 0;
  if (uVar1 == 0) {
    if (iVar7 < 0x14) {
      for (; iVar7 < 0x19; iVar7 = iVar7 + 8) {
        uVar9 = uVar9 << 8 | (uint)*DAT_00f25e08;
        DAT_00f25e08 = DAT_00f25e08 + 1;
      }
    }
    iVar7 = iVar7 + -0x14;
    DAT_005ada38 = 2;
    uVar9 = uVar9 - ((uVar9 >> ((byte)iVar7 & 0x1f)) << ((byte)iVar7 & 0x1f));
  }
  else {
    if (iVar7 < 4) {
      for (; iVar7 < 0x19; iVar7 = iVar7 + 8) {
        uVar9 = uVar9 << 8 | (uint)*DAT_00f25e08;
        DAT_00f25e08 = DAT_00f25e08 + 1;
      }
    }
    iVar7 = iVar7 + -4;
    uVar9 = uVar9 - ((uVar9 >> ((byte)iVar7 & 0x1f)) << ((byte)iVar7 & 0x1f));
  }
  if (0 < (int)uVar2) {
    if (DAT_005aba34 == 0) {
      iVar3 = *(int *)(&DAT_00563d0c + (DAT_005ae34c * 0x10 + uVar2) * 4) * 0x5a0;
    }
    else {
      iVar3 = *(int *)(&DAT_00563d0c + (DAT_005ae34c * 0x10 + uVar2) * 4) * 0xb40;
    }
    DAT_005aba30 = iVar3 / *(int *)(&DAT_00563cec + (DAT_005ae924 + DAT_005ae34c * 4) * 4);
  }
  if (iVar7 < 8) {
    for (; iVar7 < 0x19; iVar7 = iVar7 + 8) {
      uVar9 = uVar9 << 8 | (uint)*DAT_00f25e08;
      DAT_00f25e08 = DAT_00f25e08 + 1;
    }
  }
  iVar7 = iVar7 + -8;
  DAT_005ae7f0 = uVar9 >> ((byte)iVar7 & 0x1f);
  uVar9 = uVar9 - (DAT_005ae7f0 << ((byte)iVar7 & 0x1f));
  if (DAT_005ae7e8 == 3) {
    if (iVar7 < 1) {
      for (; iVar7 < 0x19; iVar7 = iVar7 + 8) {
        uVar9 = uVar9 << 8 | (uint)*DAT_00f25e08;
        DAT_00f25e08 = DAT_00f25e08 + 1;
      }
    }
    DAT_00f25e04 = iVar7 + -1;
    _DAT_005ae7f4 = uVar9 >> ((byte)DAT_00f25e04 & 0x1f);
    _DAT_005ae340 = 0;
    local_c = 0xd;
    iVar7 = 1;
    DAT_005ae7dc = 1;
    DAT_00f25e00 = uVar9 - (_DAT_005ae7f4 << ((byte)DAT_00f25e04 & 0x1f));
  }
  else {
    if (iVar7 < 2) {
      for (; iVar7 < 0x19; iVar7 = iVar7 + 8) {
        uVar9 = uVar9 << 8 | (uint)*DAT_00f25e08;
        DAT_00f25e08 = DAT_00f25e08 + 1;
      }
    }
    DAT_00f25e04 = iVar7 + -2;
    _DAT_005ae7f4 = uVar9 >> ((byte)DAT_00f25e04 & 0x1f);
    _DAT_005ae340 = 1;
    local_c = 0x15;
    iVar7 = 2;
    DAT_005ae7dc = 2;
    DAT_00f25e00 = uVar9 - (_DAT_005ae7f4 << ((byte)DAT_00f25e04 & 0x1f));
  }
  iVar3 = 0;
  DAT_005ae7f8 = 0;
  _DAT_005ae7fc = 0;
  if (iVar7 != 0) {
    do {
      if (DAT_00f25e04 < 0xc) {
        for (; DAT_00f25e04 < 0x19; DAT_00f25e04 = DAT_00f25e04 + 8) {
          DAT_00f25e00 = DAT_00f25e00 << 8 | (uint)*DAT_00f25e08;
          DAT_00f25e08 = DAT_00f25e08 + 1;
        }
      }
      pbVar10 = DAT_00f25e08;
      iVar8 = DAT_00f25e04 + -0xc;
      uVar1 = DAT_00f25e00 >> ((byte)iVar8 & 0x1f);
      uVar9 = DAT_00f25e00 - (uVar1 << ((byte)iVar8 & 0x1f));
      iVar7 = iVar3 + param_1 * 2;
      (&DAT_005ae800)[iVar7 * 0x12] = uVar1;
      if (iVar8 < 9) {
        for (; iVar8 < 0x19; iVar8 = iVar8 + 8) {
          uVar9 = uVar9 << 8 | (uint)*pbVar10;
          DAT_00f25e08 = pbVar10 + 1;
          pbVar10 = DAT_00f25e08;
        }
      }
      iVar8 = iVar8 + -9;
      uVar1 = uVar9 >> ((byte)iVar8 & 0x1f);
      (&DAT_005ae804)[iVar7 * 0x12] = uVar1;
      uVar9 = uVar9 - (uVar1 << ((byte)iVar8 & 0x1f));
      if (iVar8 < 8) {
        for (; iVar8 < 0x19; iVar8 = iVar8 + 8) {
          uVar9 = uVar9 << 8 | (uint)*pbVar10;
          pbVar10 = pbVar10 + 1;
          DAT_00f25e08 = pbVar10;
        }
      }
      iVar8 = iVar8 + -8;
      uVar1 = uVar9 >> ((byte)iVar8 & 0x1f);
      uVar9 = uVar9 - (uVar1 << ((byte)iVar8 & 0x1f));
      iVar4 = uVar1 + DAT_005ae928;
      bVar11 = DAT_005ae348 != 0;
      (&DAT_005ae808)[iVar7 * 0x12] = iVar4;
      if (bVar11) {
        (&DAT_005ae808)[iVar7 * 0x12] = iVar4 + -2;
      }
      if (iVar8 < 9) {
        for (; iVar8 < 0x19; iVar8 = iVar8 + 8) {
          uVar9 = uVar9 << 8 | (uint)*pbVar10;
          pbVar10 = pbVar10 + 1;
          DAT_00f25e08 = pbVar10;
        }
      }
      iVar8 = iVar8 + -9;
      uVar1 = uVar9 >> ((byte)iVar8 & 0x1f);
      (&DAT_005ae80c)[iVar7 * 0x12] = uVar1;
      uVar9 = uVar9 - (uVar1 << ((byte)iVar8 & 0x1f));
      if (iVar8 < 1) {
        for (; iVar8 < 0x19; iVar8 = iVar8 + 8) {
          uVar9 = uVar9 << 8 | (uint)*pbVar10;
          pbVar10 = pbVar10 + 1;
          DAT_00f25e08 = pbVar10;
        }
      }
      iVar8 = iVar8 + -1;
      uVar1 = uVar9 >> ((byte)iVar8 & 0x1f);
      DAT_00f25e04 = iVar8;
      (&DAT_005ae810)[iVar7 * 0x12] = uVar1;
      DAT_00f25e00 = uVar9 - (uVar1 << ((byte)iVar8 & 0x1f));
      if (uVar1 == 0) {
        (&DAT_005ae818)[iVar7 * 0x12] = 0;
        (&DAT_005ae814)[iVar7 * 0x12] = 0;
        uVar5 = ConsumeMpegBits(5);
        (&DAT_005ae81c)[iVar7 * 0x12] = uVar5;
        uVar5 = ConsumeMpegBits(5);
        (&DAT_005ae820)[iVar7 * 0x12] = uVar5;
        uVar5 = ConsumeMpegBits(5);
        (&DAT_005ae824)[iVar7 * 0x12] = uVar5;
        uVar5 = ConsumeMpegBits(4);
        (&DAT_005ae834)[iVar7 * 0x12] = uVar5;
        uVar5 = ConsumeMpegBits(3);
        (&DAT_005ae838)[iVar7 * 0x12] = uVar5;
      }
      else {
        if (iVar8 < 2) {
          for (; iVar8 < 0x19; iVar8 = iVar8 + 8) {
            DAT_00f25e00 = DAT_00f25e00 << 8 | (uint)*pbVar10;
            pbVar10 = pbVar10 + 1;
            DAT_00f25e08 = pbVar10;
          }
        }
        DAT_00f25e04 = iVar8 + -2;
        bVar6 = (byte)DAT_00f25e04;
        uVar9 = DAT_00f25e00 >> (bVar6 & 0x1f);
        (&DAT_005ae814)[iVar7 * 0x12] = uVar9;
        DAT_00f25e00 = DAT_00f25e00 - (uVar9 << (bVar6 & 0x1f));
        uVar5 = ConsumeMpegBits(1);
        (&DAT_005ae818)[iVar7 * 0x12] = uVar5;
        uVar5 = ConsumeMpegBits(5);
        (&DAT_005ae81c)[iVar7 * 0x12] = uVar5;
        uVar5 = ConsumeMpegBits(5);
        (&DAT_005ae820)[iVar7 * 0x12] = uVar5;
        uVar5 = ConsumeMpegBits(3);
        (&DAT_005ae828)[iVar7 * 0x12] = uVar5;
        uVar5 = ConsumeMpegBits(3);
        (&DAT_005ae82c)[iVar7 * 0x12] = uVar5;
        uVar5 = ConsumeMpegBits(3);
        (&DAT_005ae830)[iVar7 * 0x12] = uVar5;
        if ((&DAT_005ae814)[iVar7 * 0x12] == 2) {
          (&DAT_005ae834)[iVar7 * 0x12] = 5;
          (&DAT_005ae838)[iVar7 * 0x12] = 0xf;
        }
        else {
          (&DAT_005ae834)[iVar7 * 0x12] = 7;
          (&DAT_005ae838)[iVar7 * 0x12] = 0xd;
        }
      }
      (&DAT_005ae83c)[iVar7 * 0x12] = 0;
      uVar5 = ConsumeMpegBits(1);
      (&DAT_005ae840)[iVar7 * 0x12] = uVar5;
      uVar5 = ConsumeMpegBits(1);
      (&DAT_005ae844)[iVar7 * 0x12] = uVar5;
      iVar3 = iVar3 + 1;
    } while (iVar3 < DAT_005ae7dc);
  }
  return local_c;
}

