/* SynthesizeMpegLayerIIISecondChannel - 0x00514c10 in the original binary.
 *
 * Layer III hybrid synthesis for ONE granule of the SECOND channel
 * only: windowed IMDCT with overlap-add, frequency inversion, then the
 * polyphase driver selected for this stream. Used for the "right channel
 * only" output mode.
 *
 * Evidence for the name (all from outside the body):
 * Entry 4 of the 5-word table at 0x563ddc (raw words 514b60 514cc0
 * 514de0 514b60 514c10). SetupMpegLayerIIIDecoder stores
 * PTR_FUN_00563da4 = table[col], col = 0 when the stream header mode field
 * (+0x20) is 3 (single channel) and (param_5 & 3) + 1 otherwise; that is
 * the same column scheme SetupMpegLayerIDecoder uses for the 0x563a60
 * Mono / Stereo / MixDown / SecondChannel / SecondChannel drivers, so
 * columns 0 and 3 (mono, first channel) both take this single-channel
 * routine, column 4 (second channel) is 0x514c10, column 2 (mix down) is
 * 0x514de0 and column 1 (both channels) is 0x514cc0. DecodeMpegLayerIIIGranule
 * calls it as (output, granule) through PTR_FUN_00563da4.
 *
 * Body: it is exactly one iteration (channel 1) of the loop in 0x514cc0
 * (limits and side-info records at the channel-1 offsets, spectrum row at
 * 0xf27100 + granule * 0x900), with a constant 0 as the polyphase driver's
 * third argument so the single output stays in the first block. Per-granule
 * arrays are indexed [granule * 2 + channel] (limits at 0x5ae7cc), the
 * 0x90-byte side-info records at 0x5ae814 are one per granule (0x48 per
 * channel), and the spectrum rows at 0xf25f00 are 0x900 bytes per granule
 * with channel 1 at +0x1200. The IMDCT overlaps with the other granule's
 * row (granule ^ 1).
 */
#include "ghidra_types.h"


void SynthesizeMpegLayerIIISecondChannel(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = (&DAT_005ae7d0)[param_2 * 2];
  iVar2 = iVar1;
  iVar4 = (&DAT_005ae814)[param_2 * 0x24 + 0x12];
  if ((iVar4 == 2) && (iVar2 = 0, (&DAT_005ae818)[param_2 * 0x24 + 0x12] != 0)) {
    iVar2 = g_mpegBandStartTab[DAT_005aba28 - 1];
  }
  if ((int)DAT_00563d8c < iVar2) {
    iVar2 = DAT_00563d8c;
  }
  if ((int)DAT_00563d8c < iVar1) {
    iVar1 = DAT_00563d8c;
  }
  iVar3 = MpegImdctThunk(&DAT_00f25f00 + 0x480 + param_2 * 0x240,
                         &DAT_00f25f00 + 0x480 + (param_2 ^ 1) * 0x240,
                         &DAT_005ada3c,iVar4,iVar2,iVar1,(&DAT_005ae7d0)[(param_2 ^ 1) * 2]);
  (&DAT_005ae7d0)[param_2 * 2] = iVar3;
  MpegFrequencyInversionThunk(&DAT_005ada3c,iVar3);
  (*(code *)PTR_FUN_00563da0)(&DAT_005ada3c,param_1,0);
  return;
}

