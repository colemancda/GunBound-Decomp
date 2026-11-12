/* MpegPolyphase8HalfInterleaved - 0x00517b20 in the original binary.
 *
 * Layer III polyphase synthesis driver: 8-bit PCM, half band,
 * interleaved stereo. Runs 18 time slots of 32 subband samples through the
 * dequantised-spectrum filter MpegDct16 and the window/output thunk
 * MpegSynthWindow8HalfInterleavedThunk.
 *
 * Evidence for the name (all from outside the body):
 * It is entry 10 of the 13-word table at 0x563da8 (entry 0 is the
 * runtime variable the Layer III sample decoder is parked in). The raw
 * table words are 514fc0 517630 517690 517760 5177c0 517880 5178e0 5179a0
 * 517a00 517ac0 517b20 517be0 517c40 (then 0x563ddc starts). In
 * SetupMpegLayerIIIDecoder (0x5163d0) PTR_FUN_00563da0 =
 * table[DAT_00f25ee0 + (param_3 + eightBit*3)*2], where DAT_00f25ee0 is
 * the output channel count (1, or 2 for an interleaved stereo stream),
 * param_3 is the downsample shift (0 full, 1 half, 2 quarter) and eightBit
 * = (param_5 & 8) != 0. Entry 10 is therefore channels=2,
 * shift=1, eightBit=1. The window thunk it calls is the
 * 8-bit half one with the Interleaved flavour (the same one the already named
 * SynthesizeMpeg8Half* drivers use), and the per-slot advance below is
 * the output step for that geometry: 0x20 bytes of 1-byte samples.
 * Ring position DAT_005ae93c steps by -0x10 under mask 0xff.
 * param_3 (the third word the caller passes: 0 for the first block, the
 * channel/granule index for the second) selects the first ring
 * (DAT_005af144 / DAT_005ae93c, dst as given) or the second ring
 * (DAT_005ae940 / DAT_005af140, dst + 1 bytes so the two blocks interleave).
 * Called from the Layer III stereo/first/second/mix-down drivers
 * (0x514cc0, 0x514b60, 0x514c10, 0x514de0) as (spectrum, out, index).
 */
#include "ghidra_types.h"


void MpegPolyphase8HalfInterleaved(int param_1,int param_2,int param_3)

{
  int iVar1;
  
  if (param_3 == 0) {
    iVar1 = 0x12;
    do {
      MpegDct16(param_1,&DAT_005af144 + DAT_005ae93c);
      MpegSynthWindow8HalfInterleavedThunk(&DAT_005af144,DAT_005ae93c,param_2);
      param_1 = param_1 + 0x80;
      param_2 = param_2 + 0x20;
      DAT_005ae93c = DAT_005ae93c - 0x10 & 0xff;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    return;
  }
  iVar1 = 0x12;
  param_2 = param_2 + 1;
  do {
    MpegDct16(param_1,&DAT_005ae940 + DAT_005af140);
    MpegSynthWindow8HalfInterleavedThunk(&DAT_005ae940,DAT_005af140,param_2);
    param_1 = param_1 + 0x80;
    DAT_005af140 = DAT_005af140 - 0x10 & 0xff;
    param_2 = param_2 + 0x20;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}
