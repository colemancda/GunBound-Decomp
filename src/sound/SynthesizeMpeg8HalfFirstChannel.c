/* SynthesizeMpeg8HalfFirstChannel - 0x00517330 in the original binary.
 *
 * Synthesis driver for 8-bit PCM, half band: only the first channel of a
 * two-channel stream (input at offset 0).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * Slot 23 of the 30-entry table at 0x563a60 (raw bytes confirm 0x517330).
 * SetupMpegLayerIDecoder, SetupMpegLayerIIIDecoder and
 * DecodeMpegAudioFrame install it as PTR_FUN_005637cc with index col +
 * (downsample + eightBit*3)*5, downsample = param_3 = 1 (subband count
 * 0x20 >> 1 = 16), eightBit = (param_5 & 8) != 0 = 1, and col = 0 when the
 * stream header mode field (ParseMpegFrameHeader param_3[8], offset 0x20)
 * is 3 (single channel), otherwise (param_5 & 3) + 1. DAT_00563ad8[col] =
 * 1,2,1,1,1 gives the output channel count; this is column 3.
 * Column 3 has one output channel but runs on a stereo stream. Its reader
 * 0x51a8b0 is the same one the both-channel driver 0x517220 calls for its
 * first channel (input pointer unmodified); this driver passes the input
 * pointer straight through. Which of the two is the left channel in the
 * source stream is not established by anything outside the body, hence the
 * neutral First/Second wording; the first/second order itself follows the
 * both-channel driver.
 * Each iteration synthesises 16 samples through MpegSynthWindow8HalfThunk
 * (0x51afb0), advancing the input by 0x100 and the output by 0x10 = 16
 * samples x 1 bytes, and steps the ring offset DAT_005ae93c by 0x10 under
 * mask 0xff.
 */
#include "ghidra_types.h"


void SynthesizeMpeg8HalfFirstChannel(int param_1,int param_2,int param_3)

{
  if (0 < param_3) {
    do {
      MpegDct16Interleaved(param_1,&DAT_005af144 + DAT_005ae93c);
      MpegSynthWindow8HalfThunk(&DAT_005af144,DAT_005ae93c,param_2);
      param_1 = param_1 + 0x100;
      param_2 = param_2 + 0x10;
      DAT_005ae93c = DAT_005ae93c - 0x10 & 0xff;
      param_3 = param_3 + -1;
    } while (param_3 != 0);
  }
  return;
}

