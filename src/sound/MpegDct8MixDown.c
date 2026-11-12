/* MpegDct8MixDown - 0x0051ad70 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section. (Previously FUN_0051ad70.)
 *
 * Evidence for the name (all from outside the body):
 * Its only callers are SynthesizeMpeg16QuarterMixDown and
 * SynthesizeMpeg8QuarterMixDown, the quarter-band drivers for a two-channel
 * stream mixed down to one output channel (the same slot where the mono
 * drivers call MpegDct8). Verified in the body: the first and last input
 * pairs are averaged, (in[2k] + in[2k+1]) * 0.5 with the constant at
 * 0x544b00 (0.5 in the binary), over the 16-float input, before the same
 * third-row (0xf25aa0) factor step as MpegDct8.
 * It is to MpegDct8 what MpegDct32MixDown is to MpegDct32.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void MpegDct8MixDown(float *param_1,undefined4 param_2)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  float *pfVar5;
  float *pfVar6;
  float *pfVar7;
  int iVar8;
  float local_40 [16];
  
  fVar1 = (param_1[1] + *param_1) * _DAT_00544b00;
  fVar2 = (param_1[0xf] + param_1[0xe]) * _DAT_00544b00;
  local_40[0] = fVar2 + fVar1;
  local_40[4] = (fVar1 - fVar2) * DAT_00f25aa0;
  iVar8 = 0;
  pfVar5 = param_1 + 0xc;
  do {
    iVar3 = iVar8 + 4;
    fVar1 = (param_1[3] + param_1[2]) * _DAT_00544b00;
    fVar2 = (pfVar5[1] + *pfVar5) * _DAT_00544b00;
    *(float *)((int)local_40 + iVar8 + 4) = fVar2 + fVar1;
    *(float *)((int)local_40 + iVar8 + 0x14) =
         (fVar1 - fVar2) * *(float *)((int)&DAT_00f25aa4 + iVar8);
    iVar8 = iVar3;
    pfVar5 = pfVar5 + -2;
    param_1 = param_1 + 2;
  } while (iVar3 < 0xc);
  iVar8 = 0;
  iVar3 = 2;
  do {
    iVar4 = iVar8;
    pfVar5 = (float *)((int)local_40 + iVar8 + 0xc);
    pfVar6 = (float *)&DAT_00f25ab0;
    do {
      pfVar7 = pfVar6 + 1;
      *(float *)((int)local_40 + iVar4 + 0x20) = *(float *)((int)local_40 + iVar4) + *pfVar5;
      *(float *)((int)local_40 + iVar4 + 0x28) =
           (*(float *)((int)local_40 + iVar4) - *pfVar5) * *pfVar6;
      iVar4 = iVar4 + 4;
      pfVar5 = pfVar5 + -1;
      pfVar6 = pfVar7;
    } while (pfVar7 < &DAT_00f25ab8);
    iVar8 = iVar8 + 0x10;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar3 = 4;
  iVar8 = 0;
  do {
    iVar3 = iVar3 + -1;
    *(float *)((int)local_40 + iVar8) =
         *(float *)((int)local_40 + iVar8 + 0x20) + *(float *)((int)local_40 + iVar8 + 0x24);
    *(float *)((int)local_40 + iVar8 + 4) =
         (*(float *)((int)local_40 + iVar8 + 0x20) - *(float *)((int)local_40 + iVar8 + 0x24)) *
         _DAT_00f25ab8;
    iVar8 = iVar8 + 8;
  } while (iVar3 != 0);
  FUN_0051a650(2,4,local_40,local_40 + 8);
  FUN_0051a650(1,8,local_40 + 8,param_2);
  return;
}

