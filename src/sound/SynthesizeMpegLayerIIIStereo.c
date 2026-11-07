/* SynthesizeMpegLayerIIIStereo - 0x00514cc0 in the original binary.
 *
 * Layer III hybrid synthesis for one granule of ALL output channels: for
 * each channel (DAT_005ae7dc of them, 1 or 2) a windowed IMDCT with
 * overlap-add (MpegImdctThunk), frequency inversion
 * (MpegFrequencyInversionThunk) and the stream's polyphase driver
 * (PTR_FUN_00563da0), whose third argument is the channel index so a second
 * channel lands in the interleaved block.
 *
 * Evidence for the name (all from outside the body):
 * Entry 1 of the 5-word table at 0x563ddc (raw words 514b60 514cc0 514de0
 * 514b60 514c10), the column SetupMpegLayerIIIDecoder selects for
 * (param_5 & 3) == 0 on a non-mono stream, matching the Stereo column of
 * the 0x563a60 tables. Columns 0/3 and 4 are the single-channel loop body
 * (0x514b60 / 0x514c10, the same code for channel 0 / channel 1 with a
 * constant 0 as the third argument) and column 2 is the mix down (0x514de0).
 * Called as (output, granule) by DecodeMpegLayerIIIGranule.
 *
 * Bug fixed against the raw port: the band-start lookup
 * `[0xf25d3c + DAT_005aba28 * 4]` was `*(uint *)(&DAT_00f25d3c + idx * 4)`
 * on a uint32_t, a 16-byte stride. The original scales the index by 4
 * BYTES, i.e. element idx - 1 of the band start table at 0xf25d40.
 */
#include "ghidra_types.h"


void SynthesizeMpegLayerIIIStereo(undefined4 param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int *local_8;
  undefined4 *local_4;
  
  iVar2 = 0;
  if (0 < DAT_005ae7dc) {
    local_8 = (int *)(&DAT_005ae7cc + param_2 * 2);
    local_4 = (undefined4 *)(&DAT_005ae7cc + (param_2 ^ 1) * 2);
    piVar3 = &DAT_005ae814 + param_2 * 0x24;
    puVar5 = &DAT_00f25f00 + param_2 * 0x240;
    puVar4 = &DAT_00f25f00 + (param_2 ^ 1) * 0x240;
    do {
      iVar1 = *local_8;
      param_2 = iVar1;
      if ((*piVar3 == 2) && (param_2 = 0, piVar3[1] != 0)) {
        param_2 = g_mpegBandStartTab[DAT_005aba28 - 1];
      }
      if (DAT_00563d8c < (int)param_2) {
        param_2 = DAT_00563d8c;
      }
      if (DAT_00563d8c < iVar1) {
        iVar1 = DAT_00563d8c;
      }
      iVar1 = MpegImdctThunk(puVar5,puVar4,&DAT_005ada3c,*piVar3,param_2,iVar1,*local_4);
      *local_8 = iVar1;
      MpegFrequencyInversionThunk(&DAT_005ada3c,iVar1);
      (*(code *)PTR_FUN_00563da0)(&DAT_005ada3c,param_1,iVar2);
      local_4 = local_4 + 1;
      local_8 = local_8 + 1;
      iVar2 = iVar2 + 1;
      piVar3 = piVar3 + 0x12;
      puVar4 = puVar4 + 0x480;
      puVar5 = puVar5 + 0x480;
    } while (iVar2 < DAT_005ae7dc);
  }
  return;
}

