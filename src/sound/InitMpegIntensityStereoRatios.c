/* InitMpegIntensityStereoRatios - 0x0051a120 in the original binary.
 *
 * Fill the MPEG-1 intensity-stereo ratio table (0x5b0144).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * Fetches its destination from GetMpegIntensityRatioTable (0x5180e0, the
 * accessor for 0x5b0144) and writes eight (left, right) float pairs for
 * is_pos 0..7: l = sin/(sin+cos), r = cos/(sin+cos) of is_pos*pi/12, i.e.
 * tan/(1+tan) and 1/(1+tan), with pair 7 set to the (1.0, 0.0) escape
 * value. A second eight pairs at +0x40 hold the same ratios scaled by
 * sqrt(2) (sqrt via the CRT routine at 0x527f34 with 2.0). The consumer
 * ApplyMpegIntensityStereo reads (l, r) at ((is_pos + flag*8)*8) from
 * +0x5b0144/+0x5b0148, its trailing flag argument selecting the half.
 * Called from InitMpegLayerIIITables (0x519c56) and
 * again from SetupMpegLayerIIIDecoder (0x516752), both Layer III setup
 * paths.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void InitMpegIntensityStereoRatios(void)

{
  double dVar1;
  double dVar2;
  int iVar3;
  float *pfVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  double dVar8;
  
  iVar3 = GetMpegIntensityRatioTable();
  dVar8 = FID_conflict__cos(1.0);
  iVar5 = 0;
  pfVar4 = (float *)(iVar3 + 0x40);
  dVar8 = (dVar8 * _DAT_005448e0) / _DAT_00544ad8;
  do {
    dVar1 = (double)iVar5 * dVar8;
    fVar6 = (float10)FUN_00527ff4(dVar1);
    fVar7 = (float10)FUN_00527cb4(dVar1);
    dVar1 = (double)fVar7 + (double)fVar6;
    dVar2 = (double)fVar6 / dVar1;
    pfVar4[-0x10] = (float)dVar2;
    dVar1 = (double)fVar7 / dVar1;
    pfVar4[-0xf] = (float)dVar1;
    fVar6 = (float10)FUN_00527f34(2.0);
    *pfVar4 = (float)(fVar6 * (float10)dVar2);
    fVar6 = (float10)FUN_00527f34(2.0);
    pfVar4[1] = (float)(fVar6 * (float10)dVar1);
    iVar5 = iVar5 + 1;
    pfVar4 = pfVar4 + 2;
  } while (iVar5 < 7);
  *(undefined4 *)(iVar3 + iVar5 * 8) = 0x3f800000;
  *(undefined4 *)(iVar3 + 4 + iVar5 * 8) = 0;
  *(undefined4 *)(iVar3 + 0x40 + iVar5 * 8) = 0x3f800000;
  *(undefined4 *)(iVar3 + 0x44 + iVar5 * 8) = 0x3f800000;
  return;
}

