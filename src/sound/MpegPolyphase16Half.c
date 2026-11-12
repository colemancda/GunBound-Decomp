/* MpegPolyphase16Half - 0x00517760 in the original binary.
 *
 * Layer III polyphase synthesis driver: 16-bit PCM, half band,
 * single output channel. Runs 18 time slots of 32 subband samples through the
 * dequantised-spectrum filter MpegDct16 and the window/output thunk
 * MpegSynthWindow16HalfThunk.
 *
 * Evidence for the name (all from outside the body):
 * It is entry 3 of the 13-word table at 0x563da8 (entry 0 is the
 * runtime variable the Layer III sample decoder is parked in). The raw
 * table words are 514fc0 517630 517690 517760 5177c0 517880 5178e0 5179a0
 * 517a00 517ac0 517b20 517be0 517c40 (then 0x563ddc starts). In
 * SetupMpegLayerIIIDecoder (0x5163d0) PTR_FUN_00563da0 =
 * table[DAT_00f25ee0 + (param_3 + eightBit*3)*2], where DAT_00f25ee0 is
 * the output channel count (1, or 2 for an interleaved stereo stream),
 * param_3 is the downsample shift (0 full, 1 half, 2 quarter) and eightBit
 * = (param_5 & 8) != 0. Entry 3 is therefore channels=1,
 * shift=1, eightBit=0. The window thunk it calls is the
 * 16-bit half one (the same one the already named
 * SynthesizeMpeg16Half* drivers use), and the per-slot advance below is
 * the output step for that geometry: 0x20 bytes of 2-byte samples.
 * Ring position DAT_005ae93c steps by -0x10 under mask 0xff.
 * Only two stack arguments are read (src, dst); callers pass a third word
 * that this variant ignores (cdecl). Always uses the first ring.
 */
#include "ghidra_types.h"


void MpegPolyphase16Half(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = 0x12;
  do {
    MpegDct16(param_1,&DAT_005af144 + DAT_005ae93c);
    MpegSynthWindow16HalfThunk(&DAT_005af144,DAT_005ae93c,param_2);
    param_1 = param_1 + 0x80;
    param_2 = param_2 + 0x20;
    DAT_005ae93c = DAT_005ae93c - 0x10 & 0xff;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}
