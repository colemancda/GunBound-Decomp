/* MpegDct32MixDown - 0x0051a470 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section. (Previously FUN_0051a470.)
 *
 * Evidence for the name (all from outside the body):
 * Its only two callers are SynthesizeMpeg16FullMixDown and
 * SynthesizeMpeg8FullMixDown, the full-band drivers for a two-channel stream
 * mixed down to one output channel; each calls it as (interleaved L/R floats,
 * ring slot) in the position where the mono drivers call MpegDct32Thunk,
 * followed by the same full-band window thunk. Those drivers' own notes
 * identify the 0x544b00 constant as 0.5f (confirmed here by reading the bytes
 * in the binary: 0.5), and the body begins by averaging each interleaved pair,
 * (in[2k] + in[2k+1]) * 0.5, from both ends of the 64-float input. That
 * produces the 32 mixed samples, which it then runs through the same
 * butterfly stages against the same g_mpegCosTab rows as MpegDct32 (first row
 * at 0xf25a40, then 0xf25a80, 0xf25aa0, 0xf25ab0, 0xf25ab8), ending in four
 * calls to the not yet named helper 0x51a650 (left alone; not part of this
 * batch). Same "Dct" justification as MpegDct32.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void MpegDct32MixDown(float *param_1,undefined4 param_2)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  float *pfVar5;
  float *pfVar6;
  float *pfVar7;
  int iVar8;
  float local_100 [32];
  float local_80 [7];
  float local_64 [25];
  
  iVar8 = 0;
  pfVar5 = param_1 + 0x3e;
  do {
    pfVar7 = param_1 + 1;
    fVar1 = *param_1;
    iVar3 = iVar8 + 4;
    param_1 = param_1 + 2;
    fVar1 = (*pfVar7 + fVar1) * _DAT_00544b00;
    fVar2 = (pfVar5[1] + *pfVar5) * _DAT_00544b00;
    *(float *)((int)local_100 + iVar8) = fVar2 + fVar1;
    *(float *)((int)local_100 + iVar8 + 0x40) =
         (fVar1 - fVar2) * *(float *)((int)&DAT_00f25a40 + iVar8);
    iVar8 = iVar3;
    pfVar5 = pfVar5 + -2;
  } while (iVar3 < 0x40);
  iVar8 = 0;
  iVar3 = 2;
  do {
    iVar4 = iVar8;
    pfVar5 = (float *)((int)local_100 + iVar8 + 0x3c);
    pfVar7 = (float *)&DAT_00f25a80;
    do {
      pfVar6 = pfVar7 + 1;
      *(float *)((int)local_80 + iVar4) = *pfVar5 + *(float *)((int)local_100 + iVar4);
      *(float *)((int)local_64 + iVar4 + 4) =
           (*(float *)((int)local_100 + iVar4) - *pfVar5) * *pfVar7;
      iVar4 = iVar4 + 4;
      pfVar5 = pfVar5 + -1;
      pfVar7 = pfVar6;
    } while (pfVar6 < &DAT_00f25aa0);
    iVar8 = iVar8 + 0x40;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar8 = 0;
  iVar3 = 4;
  do {
    iVar4 = iVar8;
    pfVar5 = (float *)((int)local_64 + iVar8);
    pfVar7 = (float *)&DAT_00f25aa0;
    do {
      pfVar6 = pfVar7 + 1;
      *(float *)((int)local_100 + iVar4) = *pfVar5 + *(float *)((int)local_80 + iVar4);
      *(float *)((int)local_100 + iVar4 + 0x10) =
           (*(float *)((int)local_80 + iVar4) - *pfVar5) * *pfVar7;
      iVar4 = iVar4 + 4;
      pfVar5 = pfVar5 + -1;
      pfVar7 = pfVar6;
    } while (pfVar6 < &DAT_00f25ab0);
    iVar8 = iVar8 + 0x20;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar8 = 0;
  iVar3 = 8;
  do {
    iVar4 = iVar8;
    pfVar5 = (float *)((int)local_100 + iVar8 + 0xc);
    pfVar7 = (float *)&DAT_00f25ab0;
    do {
      pfVar6 = pfVar7 + 1;
      *(float *)((int)local_80 + iVar4) = *(float *)((int)local_100 + iVar4) + *pfVar5;
      *(float *)((int)local_80 + iVar4 + 8) =
           (*(float *)((int)local_100 + iVar4) - *pfVar5) * *pfVar7;
      iVar4 = iVar4 + 4;
      pfVar5 = pfVar5 + -1;
      pfVar7 = pfVar6;
    } while (pfVar6 < &DAT_00f25ab8);
    iVar8 = iVar8 + 0x10;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar3 = 0x10;
  iVar8 = 0;
  do {
    iVar3 = iVar3 + -1;
    *(float *)((int)local_100 + iVar8) =
         *(float *)((int)local_80 + iVar8) + *(float *)((int)local_80 + iVar8 + 4);
    *(float *)((int)local_100 + iVar8 + 4) =
         (*(float *)((int)local_80 + iVar8) - *(float *)((int)local_80 + iVar8 + 4)) * _DAT_00f25ab8
    ;
    iVar8 = iVar8 + 8;
  } while (iVar3 != 0);
  FUN_0051a650(8,4,local_100,local_80);
  FUN_0051a650(4,8,local_80,local_100);
  FUN_0051a650(2,0x10,local_100,local_80);
  FUN_0051a650(1,0x20,local_80,param_2);
  return;
}

