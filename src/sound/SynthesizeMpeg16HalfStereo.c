/* SynthesizeMpeg16HalfStereo - 0x00516b70 in the original binary.
 *
 * Synthesis driver for 16-bit PCM, half band, two-channel stream written
 * as interleaved stereo: for each of param_3 slots both channels are
 * filtered (MpegDct16Interleaved on the source and on the source + 4) into the two
 * synthesis FIFOs and written through MpegSynthWindow16HalfInterleavedThunk, the
 * second channel at output + 2 so the samples interleave.
 *
 * Evidence for the name (all from outside the body):
 * Slot 6 of the 30-entry table at 0x563a60 (raw bytes confirm 0x516b70),
 * column 1 of the five-column layout SetupMpegLayerIDecoder / DecodeMpegAudioFrame use:
 * index col + (downsample + eightBit*3)*5 with col = (param_5 & 3) + 1 for a
 * non-mono stream, so col 1 is the plain two-channel (Stereo) one, next to
 * the already named Mono / MixDown / FirstChannel / SecondChannel drivers
 * of the same bit depth and band. DAT_00563ad8[1] = 2 output channels.
 * The window thunk is the Interleaved one of this 16-bit half family (shared
 * with the Layer III polyphase drivers MpegPolyphase16HalfInterleaved).
 * Per slot: input advances 0x100, output 0x40 = 32 samples (shifted by the
 * band) x 2 channels x 2 byte(s), ring offset DAT_005ae93c steps by -0x10
 * under mask 0xff. Unlike the Layer III drivers both channels share the one
 * ring offset (DAT_005af140 is not used).
 */
#include "ghidra_types.h"


void SynthesizeMpeg16HalfStereo(int param_1,int param_2,int param_3)

{
  if (0 < param_3) {
    do {
      MpegDct16Interleaved(param_1,&DAT_005af144 + DAT_005ae93c);
      MpegDct16Interleaved(param_1 + 4,&DAT_005ae940 + DAT_005ae93c);
      MpegSynthWindow16HalfInterleavedThunk(&DAT_005af144,DAT_005ae93c,param_2);
      MpegSynthWindow16HalfInterleavedThunk(&DAT_005ae940,DAT_005ae93c,param_2 + 2);
      param_1 = param_1 + 0x100;
      param_2 = param_2 + 0x40;
      DAT_005ae93c = DAT_005ae93c - 0x10 & 0xff;
      param_3 = param_3 + -1;
    } while (param_3 != 0);
  }
  return;
}
