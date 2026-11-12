/* SynthesizeMpegLayerIIIMixDown - 0x00514de0 in the original binary.
 *
 * Layer III hybrid synthesis for one granule of a two-channel stream that
 * is mixed down to a single output channel: the two channels' spectra are
 * summed, then one windowed IMDCT / frequency inversion / polyphase pass is
 * run over the result.
 *
 * Evidence for the name (all from outside the body):
 * Entry 2 of the 5-word table at 0x563ddc (raw words 514b60 514cc0 514de0
 * 514b60 514c10). SetupMpegLayerIIIDecoder stores PTR_FUN_00563da4 =
 * table[col] with col = (param_5 & 3) + 1 for a non-mono stream, and the
 * same column scheme picks SynthesizeMpeg*MixDown in the 0x563a60 table
 * (column 2 = mix down; its reader averages the two channels). Here
 * AccumulateFloatArray(ch0, ch1, n) adds the channel 1 spectrum row (0xf27100 + granule *
 * 0x900) into the channel 0 row (0xf25f00 + granule * 0x900), n =
 * the larger of the two channels' limits clamped to DAT_00563d8c.
 *
 * Two paths. When both channels have the same block type and neither has
 * the mixed-block flag (+4 of the side-info record) the sum above is done
 * and a single IMDCT of the channel 0 row follows; otherwise channel 0 is
 * transformed by MpegImdctThunk and channel 1 by MpegImdctViaKernels (which
 * accumulates into the same output scratch 0x5ada3c), each with its own
 * block type and limit (this path does not clamp the limits to
 * DAT_00563d8c). Both then call MpegFrequencyInversionThunk and the
 * polyphase driver PTR_FUN_00563da0 with a constant 0 third argument.
 * Called as (output, granule) by DecodeMpegLayerIIIGranule.
 */
#include "ghidra_types.h"


void SynthesizeMpegLayerIIIMixDown(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  uVar5 = param_2 ^ 1;
  iVar4 = (&DAT_005ae814)[param_2 * 0x24];
  if (((iVar4 == (&DAT_005ae814)[param_2 * 0x24 + 0x12]) &&
      ((&DAT_005ae818)[param_2 * 0x24] == 0)) && ((&DAT_005ae818)[param_2 * 0x24 + 0x12] == 0)) {
    iVar1 = (&DAT_005ae7cc)[param_2 * 2];
    if (iVar1 < (int)(&DAT_005ae7cc)[param_2 * 2 + 1]) {
      iVar1 = (&DAT_005ae7cc)[param_2 * 2 + 1];
    }
    if ((int)DAT_00563d8c < iVar1) {
      iVar1 = DAT_00563d8c;
    }
    iVar2 = iVar1;
    if (iVar4 == 2) {
      iVar2 = 0;
    }
    AccumulateFloatArray(&DAT_00f25f00 + param_2 * 0x240,&DAT_00f25f00 + 0x480 + param_2 * 0x240,iVar1);
    iVar3 = MpegImdctThunk(&DAT_00f25f00 + param_2 * 0x240,&DAT_00f25f00 + uVar5 * 0x240,
                           &DAT_005ada3c,iVar4,iVar2,iVar1,(&DAT_005ae7cc)[uVar5 * 2]);
    (&DAT_005ae7cc)[param_2 * 2] = iVar3;
  }
  else {
    iVar1 = (&DAT_005ae7cc)[param_2 * 2];
    if ((iVar4 == 2) && (iVar1 = 0, (&DAT_005ae818)[param_2 * 0x24] != 0)) {
      iVar1 = g_mpegBandStartTab[DAT_005aba28 - 1];
    }
    iVar3 = MpegImdctThunk(&DAT_00f25f00 + param_2 * 0x240,&DAT_00f25f00 + uVar5 * 0x240,
                           &DAT_005ada3c,iVar4,iVar1,(&DAT_005ae7cc)[param_2 * 2],
                           (&DAT_005ae7cc)[uVar5 * 2]);
    (&DAT_005ae7cc)[param_2 * 2] = iVar3;
    iVar4 = (&DAT_005ae814)[param_2 * 0x24 + 0x12];
    iVar1 = (&DAT_005ae7d0)[param_2 * 2];
    iVar2 = iVar1;
    if ((iVar4 == 2) && (iVar2 = 0, (&DAT_005ae818)[param_2 * 0x24 + 0x12] != 0)) {
      iVar2 = g_mpegBandStartTab[DAT_005aba28 - 1];
    }
    (&DAT_005ae7d0)[param_2 * 2] =
         MpegImdctViaKernels(&DAT_00f25f00 + 0x480 + param_2 * 0x240,&DAT_00f25f00 + param_2 * 0x240,
                      &DAT_005ada3c,iVar4,iVar2,iVar1);
  }
  MpegFrequencyInversionThunk(&DAT_005ada3c,iVar3);
  (*(code *)PTR_FUN_00563da0)(&DAT_005ada3c,param_1,0);
  return;
}
