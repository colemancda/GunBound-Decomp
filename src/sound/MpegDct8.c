/* MpegDct8 - 0x0051ab80 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section. (Previously FUN_0051ab80.)
 *
 * Evidence for the name (all from outside the body):
 * Called directly by the quarter-band drivers that take a single channel of
 * non-interleaved float data: SynthesizeMpeg16QuarterMono,
 * SynthesizeMpeg8QuarterMono, MpegPolyphase16Quarter,
 * MpegPolyphase16QuarterInterleaved (both rings) and the 8-bit pair, as
 * (source, ring slot), followed by the quarter-band window thunk.
 * SetupMpegLayerIIIDecoder selects those drivers with downsample shift 2,
 * 0x20 >> 2 = 8 subbands per slot, and the quarter-band step uses the
 * 4-entry third row of g_mpegCosTab (0xf25aa0) that InitMpegSynthesisTables
 * builds. Verified in the binary: in[0] pairs with in[7] and in[1..3] with
 * in[6..4], so all eight inputs are read at stride 4.
 * Same "Dct" justification as MpegDct32; siblings MpegDct8Interleaved and
 * MpegDct8MixDown.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void MpegDct8(float *param_1,undefined4 param_2)

{
  float *pfVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  float *pfVar5;
  int iVar6;
  /* ONE contiguous 64-byte stack frame (the original's single sub-esp frame); Ghidra's separate
   * locals are views of it, and the code indexes across them (split-stack-struct rule), so they
   * must not be separate objects whose relative placement the compiler chooses. */
  float frame[16];
  float *local_40 = frame + 0;
  float *local_20 = frame + 8;
  
  local_40[0] = *param_1 + param_1[7];
  iVar4 = 3;
  local_40[4] = (*param_1 - param_1[7]) * DAT_00f25aa0;
  pfVar1 = param_1 + 1;
  pfVar5 = param_1 + 6;
  do {
    pfVar2 = pfVar1 + 1;
    iVar4 = iVar4 + -1;
    *(float *)((int)local_40 + (-4 - (int)param_1) + (int)pfVar2) = *pfVar5 + *pfVar1;
    *(float *)((int)local_40 + (0xc - (int)param_1) + (int)pfVar2) =
         (*pfVar1 - *pfVar5) * *(float *)(((int)&DAT_00f25a9c - (int)param_1) + (int)pfVar2);
    pfVar1 = pfVar2;
    pfVar5 = pfVar5 + -1;
  } while (iVar4 != 0);
  iVar4 = 0;
  iVar6 = 2;
  do {
    iVar3 = iVar4;
    pfVar1 = (float *)((int)local_40 + iVar4 + 0xc);
    pfVar5 = (float *)&DAT_00f25ab0;
    do {
      pfVar2 = pfVar5 + 1;
      *(float *)((int)local_20 + iVar3) = *pfVar1 + *(float *)((int)local_40 + iVar3);
      *(float *)((int)local_20 + iVar3 + 8) =
           (*(float *)((int)local_40 + iVar3) - *pfVar1) * *pfVar5;
      iVar3 = iVar3 + 4;
      pfVar1 = pfVar1 + -1;
      pfVar5 = pfVar2;
    } while (pfVar2 < &DAT_00f25ab8);
    iVar4 = iVar4 + 0x10;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  iVar6 = 4;
  iVar4 = 0;
  do {
    iVar6 = iVar6 + -1;
    *(float *)((int)local_40 + iVar4) =
         *(float *)((int)local_20 + iVar4 + 4) + *(float *)((int)local_20 + iVar4);
    *(float *)((int)local_40 + iVar4 + 4) =
         (*(float *)((int)local_20 + iVar4) - *(float *)((int)local_20 + iVar4 + 4)) * _DAT_00f25ab8
    ;
    iVar4 = iVar4 + 8;
  } while (iVar6 != 0);
  FUN_0051a650(2,4,local_40,local_20);
  FUN_0051a650(1,8,local_20,param_2);
  return;
}

