/* SynthesizeMpeg16HalfMixDown - 0x00516c20 in the original binary.
 *
 * Synthesis driver for 16-bit PCM, half band: two-channel stream mixed
 * down to one output channel.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * Slot 7 of the 30-entry table at 0x563a60 (raw bytes confirm 0x516c20).
 * SetupMpegLayerIDecoder, SetupMpegLayerIIIDecoder and
 * DecodeMpegAudioFrame install it as PTR_FUN_005637cc with index col +
 * (downsample + eightBit*3)*5, downsample = param_3 = 1 (subband count
 * 0x20 >> 1 = 16), eightBit = (param_5 & 8) != 0 = 0, and col = 0 when the
 * stream header mode field (ParseMpegFrameHeader param_3[8], offset 0x20)
 * is 3 (single channel), otherwise (param_5 & 3) + 1. DAT_00563ad8[col] =
 * 1,2,1,1,1 gives the output channel count; this is column 2.
 * Column 2 has one output channel but runs on a stereo stream. Its reader
 * 0x51aa00 begins by summing each interleaved float pair and multiplying
 * by the constant at 0x544b00, which holds 0.5f, i.e. it averages left and
 * right.
 * Each iteration synthesises 16 samples through MpegSynthWindow16HalfThunk
 * (0x51aef0), advancing the input by 0x100 and the output by 0x20 = 16
 * samples x 2 bytes, and steps the ring offset DAT_005ae93c by 0x10 under
 * mask 0xff.
 */
#include "ghidra_types.h"


void SynthesizeMpeg16HalfMixDown(int param_1,int param_2,int param_3)

{
  if (0 < param_3) {
    do {
      FUN_0051aa00(param_1,&DAT_005af144 + DAT_005ae93c);
      MpegSynthWindow16HalfThunk(&DAT_005af144,DAT_005ae93c,param_2);
      param_1 = param_1 + 0x100;
      param_2 = param_2 + 0x20;
      DAT_005ae93c = DAT_005ae93c - 0x10 & 0xff;
      param_3 = param_3 + -1;
    } while (param_3 != 0);
  }
  return;
}

