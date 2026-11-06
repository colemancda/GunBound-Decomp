/* InitMpegImdctWindows - 0x00519c80 in the original binary.
 *
 * Fill the Layer III IMDCT window table (0xf25b00).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * Fetches its destination from GetMpegImdctWindowTable (0x517d00, the
 * accessor for 0xf25b00) and writes four 36-float windows back to back
 * (0x90 floats): type 0 is sin((i+0.5)*pi/36); type 1 (start) is the first
 * 18 long-sine samples, 6 ones, 6 falling short-sine samples and 6 zeros;
 * type 2 is one 12-point short sine followed by zeros; type 3 (stop) is 6
 * zeros, 6 rising short-sine samples, 6 ones and 18 falling long-sine
 * samples. That is the ISO 11172-3 block type 0..3 window set (the code
 * then sign-flips parts of the tables, not analysed further). The
 * consumer, the windowed overlap-add body at 0x51b667 (via the 0x517d10
 * wrapper), reads the table at block_type*0x24 floats. Its only caller is
 * InitMpegLayerIIITables (0x519c65), which calls it last, after the
 * intensity-stereo builders.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void InitMpegImdctWindows(void)

{
  double dVar1;
  float *pfVar2;
  float *pfVar3;
  int iVar4;
  float *pfVar5;
  int iVar6;
  float10 fVar7;
  double dVar8;
  int local_20;
  
  pfVar2 = (float *)GetMpegImdctWindowTable();
  dVar8 = FID_conflict__cos(1.0);
  dVar8 = dVar8 * _DAT_005448e0;
  iVar6 = 0;
  dVar1 = dVar8 / _DAT_00544ae0;
  pfVar5 = pfVar2;
  do {
    fVar7 = (float10)FUN_00527ff4(((double)iVar6 + _DAT_005448d8) * dVar1);
    *pfVar5 = (float)fVar7;
    iVar6 = iVar6 + 1;
    pfVar5 = pfVar5 + 1;
  } while (iVar6 < 0x24);
  iVar6 = 0;
  pfVar5 = pfVar2 + 0x24;
  do {
    fVar7 = (float10)FUN_00527ff4(((double)iVar6 + _DAT_005448d8) * dVar1);
    *pfVar5 = (float)fVar7;
    iVar6 = iVar6 + 1;
    pfVar5 = pfVar5 + 1;
  } while (iVar6 < 0x12);
  dVar8 = dVar8 / _DAT_00544ad8;
  pfVar5 = pfVar2 + 0x3c;
  pfVar3 = pfVar2 + 0x36;
  for (iVar6 = 6; iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar3 = 1.0;
    pfVar3 = pfVar3 + 1;
  }
  iVar6 = 0x18;
  do {
    fVar7 = (float10)FUN_00527ff4((((double)iVar6 + _DAT_005448d8) - _DAT_00544ad0) * dVar8);
    *pfVar5 = (float)fVar7;
    iVar6 = iVar6 + 1;
    pfVar5 = pfVar5 + 1;
  } while (iVar6 < 0x1e);
  pfVar5 = pfVar2 + 0x72;
  pfVar3 = pfVar2 + 0x42;
  for (iVar6 = 6; iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar3 = 0.0;
    pfVar3 = pfVar3 + 1;
  }
  pfVar3 = pfVar2 + 0x6c;
  for (iVar6 = 6; iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar3 = 0.0;
    pfVar3 = pfVar3 + 1;
  }
  iVar6 = 6;
  do {
    fVar7 = (float10)FUN_00527ff4((((double)iVar6 + _DAT_005448d8) - _DAT_00544ac8) * dVar8);
    *pfVar5 = (float)fVar7;
    iVar6 = iVar6 + 1;
    pfVar5 = pfVar5 + 1;
  } while (iVar6 < 0xc);
  pfVar5 = pfVar2 + 0x7e;
  pfVar3 = pfVar2 + 0x78;
  for (iVar6 = 6; iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar3 = 1.0;
    pfVar3 = pfVar3 + 1;
  }
  iVar6 = 0x12;
  do {
    fVar7 = (float10)FUN_00527ff4(((double)iVar6 + _DAT_005448d8) * dVar1);
    *pfVar5 = (float)fVar7;
    iVar6 = iVar6 + 1;
    pfVar5 = pfVar5 + 1;
  } while (iVar6 < 0x24);
  pfVar5 = pfVar2 + 0x48;
  local_20 = 0;
  do {
    fVar7 = (float10)FUN_00527ff4(((double)local_20 + _DAT_005448d8) * dVar8);
    *pfVar5 = (float)fVar7;
    local_20 = local_20 + 1;
    pfVar5 = pfVar5 + 1;
  } while (local_20 < 0xc);
  iVar4 = 0;
  pfVar5 = pfVar2 + 0x54;
  for (iVar6 = 0x18; iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar5 = 0.0;
    pfVar5 = pfVar5 + 1;
  }
  pfVar5 = pfVar2 + 9;
  do {
    if (iVar4 != 2) {
      iVar6 = 0x1b;
      pfVar3 = pfVar5;
      do {
        *pfVar3 = -*pfVar3;
        pfVar3 = pfVar3 + 1;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
    iVar4 = iVar4 + 1;
    pfVar5 = pfVar5 + 0x24;
  } while (iVar4 < 4);
  pfVar2 = pfVar2 + 0x4b;
  iVar6 = 9;
  do {
    *pfVar2 = -*pfVar2;
    pfVar2 = pfVar2 + 1;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  return;
}

