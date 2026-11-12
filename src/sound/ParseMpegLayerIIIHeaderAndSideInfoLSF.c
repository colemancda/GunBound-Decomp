/* ParseMpegLayerIIIHeaderAndSideInfoLSF - 0x00515b90 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section. (Previously FUN_00515b90.)
 *
 * Evidence for the name (all from outside the body):
 * Its sole caller is DecodeMpegLayerIIISamplesLSF (0x5159d0), the MPEG-2 /
 * 2.5 one-granule-per-frame Layer III decoder that SetupMpegLayerIIIDecoder
 * installs when the stream ID field is not 1. That caller consumes the 12-bit
 * sync word itself and then calls this as (granule parity DAT_005ae938); it
 * uses the return value as the number of header plus side-info bytes consumed
 * (added to the frame start before copying the main data into the bit
 * reservoir) and reads the fields this function stores (DAT_005ae7f0
 * main_data_begin, DAT_005ae33c padding, DAT_005aba30 frame size,
 * DAT_005ae7dc channel count, DAT_005ada38 CRC bytes).
 * Verified in the body, with the bit reader state DAT_00f25e00..DAT_00f25e10
 * shared with ConsumeMpegBits (0x514af0): after the sync it reads ID (1 bit,
 * stored in DAT_005ae34c, which DecodeMpegLayerIIIGranule tests to choose
 * ReadMpegLayerIIIScalefactorsLSF when 0), layer (2), protection (1),
 * bitrate index (4), sampling frequency (2, DAT_005ae924), padding (1),
 * private (1), mode (2, DAT_005ae7e8), mode extension (2, DAT_005ae7ec;
 * split into DAT_005aba2c and DAT_005ae348), the 16-bit CRC when the protection
 * bit is 0, then main_data_begin (8 bits), the 1 or 2 private bits (mono
 * mode value 3 selects 1 bit) and, per channel, part2_3_length (12),
 * big_values (9), global_gain (8), scalefac_compress (9) and the block-type
 * and table-select fields through ConsumeMpegBits. That is the ISO
 * 13818-3 (LSF) side-info layout: one granule, 9-bit scalefac_compress, and the
 * returned byte counts are 13 (mono) and 21 (stereo) = 4 header bytes plus the 9 or
 * 17 byte LSF side information (MPEG-1 would be 17 or 32). The LSF suffix
 * follows ReadMpegLayerIIIScalefactorsLSF.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 ParseMpegLayerIIIHeaderAndSideInfoLSF(int param_1)

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
      iVar3 = g_mpegL3BitrateTab[DAT_005ae34c * 0x10 + uVar2] * 0x5a0;
    }
    else {
      iVar3 = g_mpegL3BitrateTab[DAT_005ae34c * 0x10 + uVar2] * 0xb40;
    }
    DAT_005aba30 = iVar3 / g_mpegL3RateTab[DAT_005ae924 + DAT_005ae34c * 4];
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

