/* GetMpegFrameSizeAndBitrate - 0x00514950 in the original binary.
 *
 * Return the MPEG frame length and store the stream bitrate (bps) through
 * param_4.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * LIKELY. Calls ParseMpegFrameHeader and returns its frame length; the
 * sole caller, DecodeSoundBufferChunk, stores the result at obj+0x54 and
 * passes it as the byte count to DecodeMpegAudioFrame(obj+0x58, size,
 * ...), and passes obj+0x8c as param_4. param_4 receives the table kbps
 * value times 1000 (or a value derived from the frame length when the
 * bitrate index is 0, free format), so it is bits per second. The role of
 * obj+0x8c downstream was not traced further, hence LIKELY.
 */
#include "ghidra_types.h"


int GetMpegFrameSizeAndBitrate(undefined4 param_1,undefined4 param_2,byte *param_3,int *param_4)

{
  int iVar1;
  int iVar2;
  
  *param_4 = 0;
  iVar1 = ParseMpegFrameHeader(param_1,param_2,param_3);
  if (iVar1 == 0) {
    return 0;
  }
  if (*(int *)(param_3 + 8) == 1) {
    if (*(int *)(param_3 + 0x10) < 1) {
      if (*(int *)(param_3 + 4) == 0) {
        if ((*param_3 & 1) == 0) {
          iVar2 = g_mpegFrameRateTab[*(int *)(param_3 + 0x14)] * iVar1 * 500;
        }
        else {
          iVar2 = g_mpegFrameRateTab[*(int *)(param_3 + 0x14)] * iVar1 * 1000;
        }
        iVar2 = iVar2 / 0x5a0 + (iVar2 >> 0x1f);
      }
      else {
        iVar2 = g_mpegFrameRateTab[*(int *)(param_3 + 0x14) + *(int *)(param_3 + 4) * 4]
                * iVar1 * 1000;
        iVar2 = iVar2 / 0xb40 + (iVar2 >> 0x1f);
      }
      *param_4 = iVar2 - (iVar2 >> 0x1f);
    }
    else {
      *param_4 = g_mpegBitrateTabL3[*(int *)(param_3 + 4) * 0x10 + *(int *)(param_3 + 0x10)] * 1000;
    }
  }
  if (*(int *)(param_3 + 8) == 2) {
    if (*(int *)(param_3 + 0x10) < 1) {
      iVar2 = (g_mpegFrameRateTab[*(int *)(param_3 + 0x14) + *(int *)(param_3 + 4) * 4]
               * iVar1 * 1000) / 0xb40;
    }
    else {
      iVar2 = g_mpegBitrateTabL2[*(int *)(param_3 + 4) * 0x10 + *(int *)(param_3 + 0x10)] * 1000;
    }
    *param_4 = iVar2;
  }
  if (*(int *)(param_3 + 8) == 3) {
    if (0 < *(int *)(param_3 + 0x10)) {
      *param_4 = g_mpegBitrateTabL1[*(int *)(param_3 + 4) * 0x10 + *(int *)(param_3 + 0x10)] * 1000;
      return iVar1;
    }
    *param_4 = (g_mpegFrameRateTab[*(int *)(param_3 + 0x14) + *(int *)(param_3 + 4) * 4]
                * iVar1 * 1000) / 0x3c0;
  }
  return iVar1;
}

