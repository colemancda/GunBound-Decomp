/* SynthesizeMpeg16HalfSecondChannel - 0x00516ce0 in the original binary.
 *
 * Synthesis driver for 16-bit PCM, half band: only the second channel of a
 * two-channel stream (input offset by 4 bytes).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * Slot 9 of the 30-entry table at 0x563a60 (raw bytes confirm 0x516ce0).
 * SetupMpegLayerIDecoder, SetupMpegLayerIIIDecoder and
 * DecodeMpegAudioFrame install it as PTR_FUN_005637cc with index col +
 * (downsample + eightBit*3)*5, downsample = param_3 = 1 (subband count
 * 0x20 >> 1 = 16), eightBit = (param_5 & 8) != 0 = 0, and col = 0 when the
 * stream header mode field (ParseMpegFrameHeader param_3[8], offset 0x20)
 * is 3 (single channel), otherwise (param_5 & 3) + 1. DAT_00563ad8[col] =
 * 1,2,1,1,1 gives the output channel count; this is column 4.
 * Column 4 has one output channel but runs on a stereo stream. Its reader
 * 0x51a8b0 is the one the both-channel driver 0x516b70 calls for its
 * second channel, and like that call this driver first adds 4 to the input
 * pointer (the second float of each interleaved pair). Which of the two is
 * the left channel in the source stream is not established by anything
 * outside the body, hence the neutral First/Second wording; the
 * first/second order itself follows the both-channel driver.
 * Each iteration synthesises 16 samples through MpegSynthWindow16HalfThunk
 * (0x51aef0), advancing the input by 0x100 and the output by 0x20 = 16
 * samples x 2 bytes, and steps the ring offset DAT_005ae93c by 0x10 under
 * mask 0xff.
 */
#include "ghidra_types.h"


void SynthesizeMpeg16HalfSecondChannel(int param_1,int param_2,int param_3)

{
  param_1 = param_1 + 4;
  if (0 < param_3) {
    do {
      MpegDct16Interleaved(param_1,&DAT_005af144 + DAT_005ae93c);
      MpegSynthWindow16HalfThunk(&DAT_005af144,DAT_005ae93c,param_2);
      param_1 = param_1 + 0x100;
      param_2 = param_2 + 0x20;
      DAT_005ae93c = DAT_005ae93c - 0x10 & 0xff;
      param_3 = param_3 + -1;
    } while (param_3 != 0);
  }
  return;
}

