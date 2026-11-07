/* ParseMpegFrameHeader - 0x005146c0 in the original binary.
 *
 * Parse the 4-byte MPEG audio frame header into the struct at param_3 and
 * return the frame length in bytes (0 if no valid sync/layer/bitrate).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * Its only caller, GetMpegFrameSizeAndBitrate (0x514950), passes the
 * stream pointer, a clamp of 10000 bytes and the struct that
 * DecodeSoundBufferChunk keeps at obj+0x58; DecodeMpegAudioFrame then
 * reads that same struct: +4 (ID bit) and +8 (raw ISO layer bits 3=I,
 * 2=II, 1=III) select the decoder. The field extraction is the ISO 11172-3
 * header layout in order: ID, layer, protection, bitrate index, sampling
 * frequency, padding, private, mode, mode extension, copyright, original,
 * emphasis (param_3[1..0xc]); frame length comes from the bitrate and
 * sample-rate tables at 0x563b4c..0x563c6c. Note it only tests for sync
 * (0xff, then 0xf0 or 0xe0 in the next byte) at the pointer it is given;
 * it does not scan forward.
 */
#include "ghidra_types.h"


int ParseMpegFrameHeader(char *param_1,uint param_2,undefined4 *param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  if (10000 < param_2) {
    param_2 = 10000;
  }
  *param_3 = 0;
  if (*param_1 == -1) {
    if ((param_1[1] & 0xf0U) == 0xf0) {
      bVar1 = false;
    }
    else {
      if ((param_1[1] & 0xf0U) != 0xe0) {
        return 0;
      }
      bVar1 = true;
    }
    *param_3 = 1;
    if (bVar1) {
      *param_3 = 2;
    }
    param_3[1] = ((byte)param_1[1] & 8) >> 3;
    param_3[2] = (byte)param_1[1] >> 1 & 3;
    iVar5 = param_3[2];
    param_3[3] = (byte)param_1[1] & 1;
    param_3[4] = (uint)((byte)param_1[2] >> 4);
    param_3[5] = ((byte)param_1[2] & 0xc) >> 2;
    param_3[6] = (byte)param_1[2] >> 1 & 1;
    param_3[7] = (byte)param_1[2] & 1;
    param_3[8] = (uint)((byte)param_1[3] >> 6);
    param_3[9] = ((byte)param_1[3] & 0x30) >> 4;
    param_3[10] = ((byte)param_1[3] & 8) >> 3;
    param_3[0xb] = ((byte)param_1[3] & 4) >> 2;
    param_3[0xc] = (byte)param_1[3] & 3;
    if ((0 < iVar5) && (iVar5 < 4)) {
      iVar2 = param_3[4];
      if (0 < iVar2) {
        if (iVar5 == 3) {
          return (g_mpegBitrateTabL1[param_3[1] * 0x10 + iVar2] * 0xf0) /
                 g_mpegFrameRateTab[param_3[5] + param_3[1] * 4] << 2;
        }
        if (iVar5 == 2) {
          iVar5 = param_3[1];
          iVar2 = g_mpegBitrateTabL2[iVar5 * 0x10 + iVar2];
        }
        else {
          if (iVar5 != 1) {
            return 0;
          }
          iVar5 = param_3[1];
          if (iVar5 == 0) {
            if (!bVar1) {
              return (g_mpegBitrateTabL3[iVar2] * 0x5a0) /
                     g_mpegFrameRateTab[param_3[5]];
            }
            return (g_mpegBitrateTabL3[iVar2] * 0xb40) /
                   g_mpegFrameRateTab[param_3[5]];
          }
          iVar2 = g_mpegBitrateTabL3[iVar5 * 0x10 + iVar2];
        }
        return (iVar2 * 0xb40) / g_mpegFrameRateTab[param_3[5] + iVar5 * 4];
      }
      iVar5 = 0x18;
      param_3 = (undefined4 *)0x1;
      if ((param_1[1] & 6U) == 6) {
        param_3 = (undefined4 *)0x4;
      }
      uVar4 = (byte)param_1[2] >> 1 & 1;
      iVar2 = param_2 - 3;
      do {
        if (iVar5 < iVar2) {
          do {
            if ((*param_1 == param_1[iVar5]) && (iVar6 = iVar5, param_1[1] == param_1[iVar5 + 1]))
            goto LAB_005148dd;
            iVar5 = iVar5 + 1;
          } while (iVar5 < iVar2);
        }
        iVar6 = 0;
LAB_005148dd:
        iVar5 = iVar6 + 1;
        iVar6 = iVar6 - uVar4;
        if (iVar6 < 1) {
          return 0;
        }
        iVar7 = 0;
        iVar3 = uVar4 * (int)param_3 + iVar6;
        if (iVar3 <= iVar2) {
          do {
            if ((*param_1 != param_1[iVar3]) || (param_1[1] != param_1[iVar3 + 1])) {
              iVar7 = -iVar7;
              break;
            }
            iVar7 = iVar7 + 1;
            iVar3 = iVar3 + ((byte)param_1[iVar3 + 2] >> 1 & 1) * (int)param_3 + iVar6;
          } while (iVar3 <= iVar2);
        }
        if (0 < iVar7) {
          return iVar6;
        }
        if (1999 < iVar5) {
          return 0;
        }
      } while( true );
    }
  }
  return 0;
}

