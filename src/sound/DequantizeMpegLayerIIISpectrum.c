/* DequantizeMpegLayerIIISpectrum - 0x00518560 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section. (Previously FUN_00518560.)
 *
 * Evidence for the name (all from outside the body):
 * Called once per channel from DecodeMpegLayerIIIGranule after the Huffman
 * decoders (DecodeMpegHuffmanBigValues / DecodeMpegHuffmanCount1) have
 * filled the integer spectrum row (0xf25f00 + ch * 0x240 words) and before
 * the mid/side, intensity stereo and MpegAntialias steps, as (spectrum row,
 * &band limit, side-info record, scalefactor array, per-channel result
 * record, DAT_005aba28 = the sample-rate band index). It reads exactly the
 * tables InitMpegLayerIIITables builds through the already named accessors:
 * the x^(4/3) table (GetMpegPow43Table, 0x5b12fc, 64 entries 0x20 biased,
 * read at 0x5b137c + value * 4), the global-gain table
 * (GetMpegGlobalGainTable, 0x5b01e4; base 0x5b01fc is entry 0x18), the
 * scalefactor-gain table (GetMpegScalefactorGainTable, 0x5b0efc, addressed by
 * (pretab[band] + scalefac_scale * 4) * 0x20 + scalefactor) and the subblock-gain
 * table (GetMpegSubblockGainTable, 0x5b01c4), plus g_mpegPretab. Values
 * outside the table's -32..31 range are computed with
 * pow(|x|, 1/3) * x, i.e. x^(4/3). Block type 2 (record + 0x14) takes the
 * short-block path (three windows of 0xd-stride scalefactor rows and subblock
 * gain), which then reorders through the scratch at 0x5b05fc with a memmove;
 * otherwise it is the long-block path. The ISO name for the step is
 * requantization; "Dequantize" matches the tree's own use of "dequantised" for the
 * Layer I/II sample readers.
 */
#include "ghidra_types.h"


void DequantizeMpegLayerIIISpectrum(int param_1,int *param_2,int param_3,int param_4,undefined4 *param_5,int param_6)

{
  int iVar1;
  float fVar2;
  int iVal;
  int iVar4;
  float fVar5;
  bool bVar6;
  int iVar7;
  int *piVar8;
  float *pfVar9;
  int iVar10;
  uint uVar11;
  float *pfVar12;
  uint uVar13;
  double dVar14;
  int local_68;
  int *local_5c;
  int *local_58;
  float *local_54;
  int *local_50;
  int *local_4c;
  int *local_48;
  int local_44;
  int local_40;
  uint local_20 [3];
  float local_14 [4];
  
  iVar1 = *param_2;
  local_5c = (int *)0x16;
  uVar13 = 0xc;
  if (*(int *)(param_4 + 0x14) == 2) {
    uVar13 = 0;
    local_5c = (int *)0x0;
    if (*(int *)(param_4 + 0x18) != 0) {
      uVar13 = 3;
      local_5c = (int *)param_6;
    }
  }
  uVar11 = 0;
  param_5[2] = uVar13;
  param_5[3] = local_5c;
  local_20[0] = 0;
  local_68 = 0;
  fVar2 = *(float *)(&DAT_005b01fc + *(int *)(param_4 + 8) * 4);
  if (0 < (int)local_5c) {
    local_50 = &DAT_00f25e20;
    do {
      bVar6 = false;
      fVar5 = fVar2 * *(float *)(&DAT_005b0efc +
                                ((g_mpegPretab[uVar11 + *(int *)(param_4 + 0x3c) * 0x16] +
                                 *(int *)(param_4 + 0x40) * 4) * 0x20 +
                                *(int *)(param_3 + ((int)local_50 - (int)&DAT_00f25e20))) * 4);
      local_4c = (int *)*local_50;
      if (0 < (int)local_4c) {
        pfVar9 = (float *)(param_1 + local_68 * 4);
        local_68 = local_68 + (int)local_4c;
        do {
          /* The quantised value is an INTEGER (5186 41: `mov eax,[esi] / test
           * eax,eax`, then `cmp eax,-0x20` / `cmp eax,0x20`); the decompile
           * typed the walking pointer as float and read it as one. */
          iVal = *(int *)pfVar9;
          if (iVal == 0) {
            *pfVar9 = 0.0;
          }
          else {
            bVar6 = true;
            if ((iVal < -0x20) || (0x1f < iVal)) {
              /* the exponent is the double 0x3fd5555560000000 (= (double)
               * (float)(1/3), 0.3333333432674408) pushed as two dwords; the
               * decompile's (double)CONCAT44() converted that 64-bit integer
               * to a double (4.6e18) instead of reinterpreting its bits. */
              dVar14 = _fabs((double)iVal);
              dVar14 = _pow(dVar14,0.3333333432674408);
              *pfVar9 = (float)(dVar14 * (double)fVar5 * (double)iVal);
            }
            else {
              *pfVar9 = fVar5 * *(float *)(&DAT_005b137c + iVal * 4);
            }
          }
          pfVar9 = pfVar9 + 1;
          local_4c = (int *)((int)local_4c + -1);
        } while (local_4c != (int *)0x0);
        if (bVar6) {
          local_20[0] = uVar11;
        }
      }
      if (iVar1 <= local_68) break;
      uVar11 = uVar11 + 1;
      local_50 = local_50 + 1;
    } while ((int)uVar11 < (int)local_5c);
  }
  iVar7 = local_68;
  param_5[1] = local_20[0];
  *param_5 = 0;
  if (uVar13 < 0xc) {
    piVar8 = (int *)(param_4 + 0x28);
    local_54 = &DAT_005b05fc;
    iVar10 = 3;
    pfVar9 = local_14;
    do {
      iVar4 = *piVar8;
      piVar8 = piVar8 + 1;
      iVar10 = iVar10 + -1;
      *pfVar9 = fVar2 * *(float *)(&DAT_005b01c4 + iVar4 * 4);
      pfVar9 = pfVar9 + 1;
    } while (iVar10 != 0);
    local_20[0] = uVar13;
    local_20[1] = uVar13;
    local_20[2] = uVar13;
    if (uVar13 < 0xd) {
      piVar8 = &DAT_00f25e78 + uVar13;
      local_4c = (int *)(param_3 + 0x5c + uVar13 * 4);
      local_50 = (int *)uVar13;
      do {
        iVar10 = *piVar8;
        local_40 = 3;
        local_48 = (int *)(param_1 + local_68 * 4);
        local_58 = local_4c;
        pfVar9 = local_54;
        do {
          bVar6 = false;
          fVar2 = *(float *)(&DAT_005b0efc + (*(int *)(param_4 + 0x40) * 0x80 + *local_58) * 4) *
                  *(float *)((int)local_14 + -(int)local_54 + (int)pfVar9);
          if (0 < iVar10) {
            local_68 = local_68 + iVar10;
            local_5c = local_48;
            local_48 = local_48 + iVar10;
            pfVar12 = pfVar9;
            local_44 = iVar10;
            do {
              iVar4 = *local_5c;
              if (iVar4 == 0) {
                *pfVar12 = 0.0;
              }
              else {
                bVar6 = true;
                if ((iVar4 < -0x20) || (0x1f < iVar4)) {
                  dVar14 = _fabs((double)iVar4);
                  dVar14 = _pow(dVar14,0.3333333432674408);
                  fVar5 = (float)(dVar14 * (double)fVar2 * (double)iVar4);
                }
                else {
                  fVar5 = fVar2 * *(float *)(&DAT_005b137c + iVar4 * 4);
                }
                *pfVar12 = fVar5;
              }
              pfVar12 = pfVar12 + 3;
              local_5c = local_5c + 1;
              local_44 = local_44 + -1;
            } while (local_44 != 0);
            if (bVar6) {
              *(int **)((int)local_20 + -(int)local_54 + (int)pfVar9) = local_50;
            }
          }
          local_58 = local_58 + 0xd;
          pfVar9 = pfVar9 + 1;
          local_40 = local_40 + -1;
        } while (local_40 != 0);
        if (iVar1 <= local_68) break;
        local_54 = local_54 + iVar10 * 3;
        piVar8 = piVar8 + 1;
        local_50 = (int *)((int)local_50 + 1);
        local_4c = local_4c + 1;
      } while ((uint *)piVar8 < &DAT_00f25e78 + 13);
    }
    _memmove((void *)(param_1 + iVar7 * 4),&DAT_005b05fc,(iVar7 * 0x3fffffff + local_68) * 4);
    *param_2 = local_68;
    param_5[4] = local_20[0];
    param_5[5] = local_20[1];
    param_5[6] = local_20[2];
    if ((int)local_20[0] < (int)local_20[1]) {
      local_20[0] = local_20[1];
    }
    if ((int)local_20[0] < (int)local_20[2]) {
      local_20[0] = local_20[2];
    }
    param_5[1] = local_20[0];
    *param_5 = 1;
  }
  return;
}

