/* MpegDct16 - 0x0051a750 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section. (Previously FUN_0051a750.)
 *
 * Evidence for the name (all from outside the body):
 * Called directly (no thunk) by the half-band drivers that take a single
 * channel of non-interleaved float data: SynthesizeMpeg16HalfMono,
 * SynthesizeMpeg8HalfMono, MpegPolyphase16Half, MpegPolyphase16HalfInterleaved
 * (both rings) and the 8-bit pair, as (source, ring slot), followed by the
 * half-band window thunk. Those drivers are selected by SetupMpegLayerIIIDecoder
 * with downsample shift 1, i.e. 0x20 >> 1 = 16 subbands per slot, and the
 * synthesis-table builder InitMpegSynthesisTables lays g_mpegCosTab out as
 * rows of 16, 8, 4, 2 and 1 factors; this function starts at the second row
 * (8 entries, 0xf25a80), which is the recursion step for a 16-point input.
 * Verified in the binary: in[0] is handled alone and in[1..7] are paired
 * with in[14..8] (stride 4), so in[15] is never read (open item: the
 * top subband of the 16 is dropped, which is consistent with the half-band
 * decimation but is not independently confirmed).
 * Same "Dct" justification as MpegDct32; siblings MpegDct16Interleaved and
 * MpegDct16MixDown.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void MpegDct16(float *param_1,undefined4 param_2)

{
  float *pfVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  float *pfVar5;
  int iVar6;
  float local_80 [7];
  float local_64 [9];
  float local_40 [16];
  
  local_64[1] = DAT_00f25a80 * *param_1;
  local_80[0] = *param_1;
  iVar4 = 7;
  pfVar1 = param_1 + 1;
  pfVar5 = param_1 + 0xe;
  do {
    pfVar2 = pfVar1 + 1;
    iVar4 = iVar4 + -1;
    *(float *)((int)local_64 + (-0x20 - (int)param_1) + (int)pfVar2) = *pfVar1 + *pfVar5;
    *(float *)(((int)local_64 - (int)param_1) + (int)pfVar2) =
         (*pfVar1 - *pfVar5) * *(float *)(((int)&DAT_00f25a7c - (int)param_1) + (int)pfVar2);
    pfVar1 = pfVar2;
    pfVar5 = pfVar5 + -1;
  } while (iVar4 != 0);
  iVar4 = 0;
  iVar6 = 2;
  do {
    iVar3 = iVar4;
    pfVar1 = (float *)((int)local_64 + iVar4);
    pfVar5 = (float *)&DAT_00f25aa0;
    do {
      pfVar2 = pfVar5 + 1;
      *(float *)((int)local_40 + iVar3) = *pfVar1 + *(float *)((int)local_80 + iVar3);
      *(float *)((int)local_40 + iVar3 + 0x10) =
           (*(float *)((int)local_80 + iVar3) - *pfVar1) * *pfVar5;
      iVar3 = iVar3 + 4;
      pfVar1 = pfVar1 + -1;
      pfVar5 = pfVar2;
    } while (pfVar2 < &DAT_00f25ab0);
    iVar4 = iVar4 + 0x20;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  iVar4 = 0;
  iVar6 = 4;
  do {
    iVar3 = iVar4;
    pfVar1 = (float *)((int)local_40 + iVar4 + 0xc);
    pfVar5 = (float *)&DAT_00f25ab0;
    do {
      pfVar2 = pfVar5 + 1;
      *(float *)((int)local_80 + iVar3) = *pfVar1 + *(float *)((int)local_40 + iVar3);
      *(float *)((int)local_80 + iVar3 + 8) =
           (*(float *)((int)local_40 + iVar3) - *pfVar1) * *pfVar5;
      iVar3 = iVar3 + 4;
      pfVar1 = pfVar1 + -1;
      pfVar5 = pfVar2;
    } while (pfVar2 < &DAT_00f25ab8);
    iVar4 = iVar4 + 0x10;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  iVar6 = 8;
  iVar4 = 0;
  do {
    iVar6 = iVar6 + -1;
    *(float *)((int)local_40 + iVar4) =
         *(float *)((int)local_80 + iVar4 + 4) + *(float *)((int)local_80 + iVar4);
    *(float *)((int)local_40 + iVar4 + 4) =
         (*(float *)((int)local_80 + iVar4) - *(float *)((int)local_80 + iVar4 + 4)) * _DAT_00f25ab8
    ;
    iVar4 = iVar4 + 8;
  } while (iVar6 != 0);
  FUN_0051a650(4,4,local_40,local_80);
  FUN_0051a650(2,8,local_80,local_40);
  FUN_0051a650(1,0x10,local_40,param_2);
  return;
}

