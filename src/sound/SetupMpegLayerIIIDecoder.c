/* SetupMpegLayerIIIDecoder - 0x005163d0 in the original binary.
 *
 * Per-stream setup for Layer III: scalefactor band tables, MPEG-1/LSF
 * choice and frame-decoder installation.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * DecodeMpegAudioFrame calls it only when header field +8 == 1, which is
 * Layer III in the ISO layer bits (01). It fills the 22 long-block and 13
 * short-block scalefactor band tables (0xf25d40, 0xf25d98, 0xf25e20,
 * 0xf25e78) from the table at 0x5443a4, calls InitMpegLayerIIITables and
 * InitMpegSynthesisTables, zeroes the synthesis overlap buffer, and sets
 * PTR_FUN_00563da8 = DecodeMpegLayerIIISamples when header ID (+4) == 1
 * (MPEG-1) and DecodeMpegLayerIIISamplesLSF (0x5159d0, one granule per
 * frame) otherwise. The Layer III dispatch trampoline
 * DecodeMpegLayerIIIDispatch at 0x514fa0 (slot 1 of the 0x563aec table) calls
 * through word 0 of 0x563da8; words 1..12 of that 13-word table are the
 * polyphase drivers indexed at the PTR_FUN_00563da0 assignment, and
 * PTR_FUN_00563da4 comes from the 5-word table at 0x563ddc.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void SetupMpegLayerIIIDecoder(byte *param_1,undefined4 param_2,int param_3,undefined4 param_4,uint param_5,
                 int param_6)

{
  int iVar1;
  undefined4 *puVar2;
  byte bVar3;
  int iVar4;
  undefined4 *puVar5;
  int *piVar6;
  int *piVar7;
  uint uVar8;
  int iVar9;
  
  DAT_005ae930 = 0;
  DAT_005ae934 = 0;
  if (*(int *)(param_1 + 8) != 1) {
    return;
  }
  DAT_005aba28 = (-(uint)(*(int *)(param_1 + 4) != 0) & 2) + 6;
  DAT_005aba30 = param_2;
  uVar8 = (uint)((param_5 & 8) != 0);
  param_5 = param_5 & 3;
  if (param_3 < 0) {
    param_3 = 0;
  }
  else if (2 < param_3) {
    param_3 = 2;
  }
  if (param_6 < 1000) {
    param_6 = 1000;
  }
  _DAT_00f25ee8 =
       g_mpegLayer3SampleRateTab[*(int *)(param_1 + 0x14) + *(int *)(param_1 + 4) * 4];
  if ((*param_1 & 1) == 0) {
    _DAT_00f25ee8 = _DAT_00f25ee8 / 2;
  }
  _DAT_00563d9c = (_DAT_00f25ee8 / 2 + param_6 * 0x40) / _DAT_00f25ee8;
  bVar3 = (byte)param_3;
  iVar4 = 0x20 >> (bVar3 & 0x1f);
  if (8 < iVar4) {
    iVar4 = iVar4 + -1;
  }
  if (iVar4 < _DAT_00563d9c) {
    _DAT_00563d9c = iVar4;
  }
  iVar4 = *(int *)(param_1 + 4);
  if ((*param_1 & 1) == 0) {
    iVar4 = 2;
  }
  else if (iVar4 == 1) {
    iVar9 = g_mpegSfBandTab[(*(int *)(param_1 + 0x14) + 3) * 0x25 + 0x24];
    DAT_00563d90 = g_mpegSfBandTab[(*(int *)(param_1 + 0x14) + 3) * 0x25 + 0x16];
    goto LAB_005164e7;
  }
  iVar9 = g_mpegSfBandTab[(*(int *)(param_1 + 0x14) + iVar4 * 3) * 0x25 + 0x23];
  DAT_00563d90 = g_mpegSfBandTab[(*(int *)(param_1 + 0x14) + iVar4 * 3) * 0x25 + 0x15];
LAB_005164e7:
  DAT_00563d94 = iVar9 * 3;
  DAT_00563d8c = DAT_00563d90 + 8;
  if (_DAT_00563d9c * 0x12 < DAT_00563d90 + 8) {
    DAT_00563d8c = _DAT_00563d9c * 0x12;
  }
  if (DAT_00563d8c < DAT_00563d90) {
    DAT_00563d90 = DAT_00563d8c;
  }
  if (DAT_00563d8c < DAT_00563d94) {
    DAT_00563d94 = DAT_00563d8c;
  }
  DAT_00563d98 = (DAT_00563d8c + 0x11) / 0x12;
  DAT_005ae928 = 0;
  if ((*(int *)(param_1 + 0x20) != 3) && (param_5 == 1)) {
    DAT_005ae928 = 0xfffffffc;
  }
  _DAT_005ae738 = 0x480 >> (bVar3 & 0x1f);
  if (*(int *)(param_1 + 4) == 0) {
    _DAT_005ae738 = _DAT_005ae738 / 2;
  }
  DAT_00f25ee0 = 2;
  if (*(int *)(param_1 + 0x20) == 3) {
    DAT_00f25ee0 = 1;
  }
  if (param_5 != 0) {
    DAT_00f25ee0 = 1;
  }
  PTR_FUN_00563da0 = PTR_FUN_00563da8[DAT_00f25ee0 + (param_3 + uVar8 * 3) * 2];
  iVar4 = param_5 + 1;
  if (*(int *)(param_1 + 0x20) == 3) {
    iVar4 = 0;
  }
  _DAT_005ae738 = _DAT_005ae738 * DAT_00f25ee0;
  PTR_FUN_00563da4 = PTR_LAB_00563ddc[iVar4];
  if (uVar8 == 0) {
    DAT_005ae344 = _DAT_005ae738 * 2;
    _DAT_005ae92c = 0;
  }
  else {
    _DAT_005ae92c = 0x80;
    DAT_005ae344 = _DAT_005ae738;
  }
  _DAT_00f25ee8 = _DAT_00f25ee8 >> (bVar3 & 0x1f);
  _DAT_00f25ef0 = param_2;
  _DAT_00f25eec = (-(uint)(uVar8 != 0) & 0xfffffff8) + 0x10;
  _DAT_00f25ef4 = 0;
  DAT_005ae7e0 = DAT_005ae344 / 2;
  iVar4 = *(int *)(param_1 + 4);
  if ((*param_1 & 1) == 0) {
    iVar4 = 2;
  }
  iVar9 = 0;
  iVar4 = iVar4 * 3;
  puVar2 = &DAT_00f25d40;
  DAT_00f25ee4 = _DAT_005ae738;
  do {
    puVar5 = puVar2 + 1;
    iVar1 = (*(int *)(param_1 + 0x14) + iVar4) * 0x25 + iVar9;
    iVar9 = iVar9 + 1;
    *puVar2 = g_mpegSfBandTab[iVar1 + 1];
    puVar2 = puVar5;
  } while (puVar5 < &DAT_00f25d40 + 22);
  iVar9 = 0;
  piVar7 = &DAT_00f25d98;
  do {
    piVar6 = piVar7 + 1;
    iVar1 = (*(int *)(param_1 + 0x14) + iVar4) * 0x25 + iVar9;
    iVar9 = iVar9 + 1;
    *piVar7 = g_mpegSfBandTab[iVar1 + 0x18] * 3;
    piVar7 = piVar6;
  } while ((uint *)piVar6 < &DAT_00f25d98 + 13);
  iVar9 = 0;
  piVar7 = &DAT_00f25e20;
  do {
    piVar6 = piVar7 + 1;
    iVar1 = (*(int *)(param_1 + 0x14) + iVar4) * 0x25 + iVar9;
    iVar9 = iVar9 + 1;
    *piVar7 = g_mpegSfBandTab[iVar1 + 1] - g_mpegSfBandTab[iVar1];
    piVar7 = piVar6;
  } while ((uint *)piVar6 < &DAT_00f25e20 + 22);
  iVar9 = 0;
  piVar7 = &DAT_00f25e78;
  do {
    piVar6 = piVar7 + 1;
    iVar1 = (*(int *)(param_1 + 0x14) + iVar4) * 0x25 + iVar9;
    iVar9 = iVar9 + 1;
    *piVar7 = g_mpegSfBandTab[iVar1 + 0x18] - g_mpegSfBandTab[iVar1 + 0x17];
    piVar7 = piVar6;
  } while ((uint *)piVar6 < &DAT_00f25e78 + 13);
  InitMpegLayerIIITables();
  InitMpegIntensityStereoRatios();
  InitMpegSynthesisTables();
  puVar2 = &DAT_005ada3c;
  for (iVar4 = 0x240; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = &DAT_00f25f00;
  do {
    iVar4 = 2;
    do {
      iVar9 = 0x240;
      do {
        *puVar2 = 0;
        *puVar2 = 0;
        puVar2 = puVar2 + 1;
        iVar9 = iVar9 + -1;
      } while (iVar9 != 0);
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  } while (puVar2 < &DAT_00f25f00 + 2304);
  PTR_FUN_00563da8[0] = DecodeMpegLayerIIISamples;
  if (*(int *)(param_1 + 4) != 1) {
    PTR_FUN_00563da8[0] = DecodeMpegLayerIIISamplesLSF;
  }
  return;
}

