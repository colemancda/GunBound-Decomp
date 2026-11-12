/* MpegDct16MixDown - 0x0051aa00 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section. (Previously FUN_0051aa00.)
 *
 * Evidence for the name (all from outside the body):
 * Its only callers are SynthesizeMpeg16HalfMixDown and
 * SynthesizeMpeg8HalfMixDown, the half-band drivers for a two-channel stream
 * mixed down to one output channel (their notes: reader 0x51aa00 averages
 * each interleaved float pair with the 0.5f constant at 0x544b00; confirmed
 * there, the constant reads 0.5 in the binary). Verified in the body: the
 * pairs taken from both ends of the input are (in[2k] + in[2k+1]) * 0.5
 * (the first pair and the pairs down from in[28], in[29]; the last pair,
 * in[30], in[31], is never read, matching MpegDct16's unread in[15]) before the same second-row (0xf25a80) factor step as MpegDct16.
 * It is to MpegDct16 what MpegDct32MixDown is to MpegDct32.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void MpegDct16MixDown(float *param_1,undefined4 param_2)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  float *pfVar5;
  float *pfVar6;
  float *pfVar7;
  int iVar8;
  /* ONE contiguous 128-byte stack frame (the original's single sub-esp frame); Ghidra's separate
   * locals are views of it, and the code indexes across them (split-stack-struct rule), so they
   * must not be separate objects whose relative placement the compiler chooses. */
  float frame[32];
  float *local_80 = frame + 0;
  float *local_40 = frame + 16;
  
  local_80[0] = (param_1[1] + *param_1) * _DAT_00544b00;
  local_80[8] = DAT_00f25a80 * local_80[0];
  iVar8 = 0;
  pfVar5 = param_1 + 0x1c;
  do {
    iVar3 = iVar8 + 4;
    fVar1 = (param_1[3] + param_1[2]) * _DAT_00544b00;
    fVar2 = (pfVar5[1] + *pfVar5) * _DAT_00544b00;
    *(float *)((int)local_80 + iVar8 + 4) = fVar2 + fVar1;
    *(float *)((int)local_80 + iVar8 + 0x24) =
         (fVar1 - fVar2) * *(float *)((int)&DAT_00f25a84 + iVar8);
    iVar8 = iVar3;
    pfVar5 = pfVar5 + -2;
    param_1 = param_1 + 2;
  } while (iVar3 < 0x1c);
  iVar8 = 0;
  iVar3 = 2;
  do {
    iVar4 = iVar8;
    pfVar5 = (float *)((int)local_80 + iVar8 + 0x1c);
    pfVar7 = (float *)&DAT_00f25aa0;
    do {
      pfVar6 = pfVar7 + 1;
      *(float *)((int)local_40 + iVar4) = *pfVar5 + *(float *)((int)local_80 + iVar4);
      *(float *)((int)local_40 + iVar4 + 0x10) =
           (*(float *)((int)local_80 + iVar4) - *pfVar5) * *pfVar7;
      iVar4 = iVar4 + 4;
      pfVar5 = pfVar5 + -1;
      pfVar7 = pfVar6;
    } while (pfVar6 < &DAT_00f25ab0);
    iVar8 = iVar8 + 0x20;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar8 = 0;
  iVar3 = 4;
  do {
    iVar4 = iVar8;
    pfVar5 = (float *)((int)local_40 + iVar8 + 0xc);
    pfVar7 = (float *)&DAT_00f25ab0;
    do {
      pfVar6 = pfVar7 + 1;
      *(float *)((int)local_80 + iVar4) = *(float *)((int)local_40 + iVar4) + *pfVar5;
      *(float *)((int)local_80 + iVar4 + 8) =
           (*(float *)((int)local_40 + iVar4) - *pfVar5) * *pfVar7;
      iVar4 = iVar4 + 4;
      pfVar5 = pfVar5 + -1;
      pfVar7 = pfVar6;
    } while (pfVar6 < &DAT_00f25ab8);
    iVar8 = iVar8 + 0x10;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar3 = 8;
  iVar8 = 0;
  do {
    iVar3 = iVar3 + -1;
    *(float *)((int)local_40 + iVar8) =
         *(float *)((int)local_80 + iVar8) + *(float *)((int)local_80 + iVar8 + 4);
    *(float *)((int)local_40 + iVar8 + 4) =
         (*(float *)((int)local_80 + iVar8) - *(float *)((int)local_80 + iVar8 + 4)) * _DAT_00f25ab8
    ;
    iVar8 = iVar8 + 8;
  } while (iVar3 != 0);
  FUN_0051a650(4,4,local_40,local_80);
  FUN_0051a650(2,8,local_80,local_40);
  FUN_0051a650(1,0x10,local_40,param_2);
  return;
}

