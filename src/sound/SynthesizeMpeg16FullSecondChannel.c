/* SynthesizeMpeg16FullSecondChannel - 0x00516aa0 in the original binary.
 *
 * Synthesis driver for 16-bit PCM, full band: only the second channel of a
 * two-channel stream (input offset by 4 bytes).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * Slot 4 of the 30-entry table at 0x563a60 (raw bytes confirm 0x516aa0).
 * SetupMpegLayerIDecoder, SetupMpegLayerIIIDecoder and
 * DecodeMpegAudioFrame install it as PTR_FUN_005637cc with index col +
 * (downsample + eightBit*3)*5, downsample = param_3 = 0 (subband count
 * 0x20 >> 0 = 32), eightBit = (param_5 & 8) != 0 = 0, and col = 0 when the
 * stream header mode field (ParseMpegFrameHeader param_3[8], offset 0x20)
 * is 3 (single channel), otherwise (param_5 & 3) + 1. DAT_00563ad8[col] =
 * 1,2,1,1,1 gives the output channel count; this is column 4.
 * Column 4 has one output channel but runs on a stereo stream. Its reader
 * 0x51a450 is the one the both-channel driver 0x516930 calls for its
 * second channel, and like that call this driver first adds 4 to the input
 * pointer (the second float of each interleaved pair). Which of the two is
 * the left channel in the source stream is not established by anything
 * outside the body, hence the neutral First/Second wording; the
 * first/second order itself follows the both-channel driver.
 * Each iteration synthesises 32 samples through MpegSynthWindow16FullThunk
 * (0x51aeb0), advancing the input by 0x100 and the output by 0x40 = 32
 * samples x 2 bytes, and steps the ring offset DAT_005ae93c by 0x20 under
 * mask 0x1ff.
 */
#include "ghidra_types.h"


void SynthesizeMpeg16FullSecondChannel(int param_1,int param_2,int param_3)

{
  param_1 = param_1 + 4;
  if (0 < param_3) {
    do {
      MpegDct32InterleavedThunk(param_1,&DAT_005af144 + DAT_005ae93c);
      MpegSynthWindow16FullThunk(&DAT_005af144,DAT_005ae93c,param_2);
      param_1 = param_1 + 0x100;
      param_2 = param_2 + 0x40;
      DAT_005ae93c = DAT_005ae93c - 0x20 & 0x1ff;
      param_3 = param_3 + -1;
    } while (param_3 != 0);
  }
  return;
}

