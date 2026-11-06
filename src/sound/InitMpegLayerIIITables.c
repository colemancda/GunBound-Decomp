/* InitMpegLayerIIITables - 0x00519aa0 in the original binary.
 *
 * Build the Layer III lookup tables: gain, power and antialias
 * coefficients.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * Called only from SetupMpegLayerIIIDecoder. It fills a pow(2, (i-0x9c)*k)
 * gain table (0x106 entries), a 64-entry |x|^(1/3)*x table (x^(4/3), the
 * ISO requantiser), 2^(n*k) tables for subblock gain and scalefactor
 * multipliers, and derives the antialias cs/ca pairs (1/sqrt(1+ci^2) and
 * ci/sqrt(1+ci^2)) from the ISO 11172-3 ci coefficients at 0x544a88. Those
 * cs/ca values are what MpegAntialias reads, so the table identity is
 * corroborated from the consumer side as well.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 InitMpegLayerIIITables(void)

{
  float fVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float *pfVar6;
  float10 fVar7;
  double dVar8;
  double _Y;
  
  pfVar2 = (float *)GetMpegGlobalGainTable();
  iVar4 = 0;
  do {
    dVar8 = _pow(2.0,(double)(iVar4 + -0x9c) * _DAT_00544ac0);
    *pfVar2 = (float)dVar8;
    iVar4 = iVar4 + 1;
    pfVar2 = pfVar2 + 1;
  } while (iVar4 < 0x106);
  pfVar2 = (float *)GetMpegScalefactorGainTable();
  iVar4 = 0;
  do {
    iVar4 = iVar4 + 1;
    iVar3 = 0;
    do {
      iVar5 = 0;
      do {
        dVar8 = _pow(2.0,(double)(iVar5 + iVar3) * (double)iVar4 * _DAT_00544ab8);
        *pfVar2 = (float)dVar8;
        iVar5 = iVar5 + 1;
        pfVar2 = pfVar2 + 1;
      } while (iVar5 < 0x20);
      iVar3 = iVar3 + 1;
    } while (iVar3 < 4);
  } while (iVar4 < 2);
  pfVar2 = (float *)FUN_00518540();
  iVar4 = 0;
  do {
    _Y = 0.3333333333333333;
    dVar8 = _fabs((double)(iVar4 + -0x20));
    dVar8 = _pow(dVar8,_Y);
    *pfVar2 = (float)dVar8 * (float)(iVar4 + -0x20);
    iVar4 = iVar4 + 1;
    pfVar2 = pfVar2 + 1;
  } while (iVar4 < 0x40);
  pfVar2 = (float *)FUN_00518550();
  iVar4 = 0;
  do {
    dVar8 = _pow(2.0,(double)iVar4 * _DAT_00544ab0);
    *pfVar2 = (float)dVar8;
    iVar4 = iVar4 + 1;
    pfVar2 = pfVar2 + 1;
  } while (iVar4 < 8);
  pfVar2 = (float *)GetMpegAntialiasCsCaTable();
  pfVar6 = (float *)&DAT_00544a88;
  do {
    fVar7 = (float10)FUN_00527f34((double)(*pfVar6 * *pfVar6 + (float)_DAT_00544aa8));
    *pfVar2 = (float)((float10)_DAT_00544aa8 / fVar7);
    fVar1 = *pfVar6;
    fVar7 = (float10)FUN_00527f34((double)(*pfVar6 * *pfVar6 + (float)_DAT_00544aa8));
    pfVar6 = pfVar6 + 1;
    pfVar2[1] = (float)((float10)fVar1 / fVar7);
    pfVar2 = pfVar2 + 2;
  } while (pfVar6 < DAT_00544a88 + 8);
  InitMpegIntensityStereoRatios();
  InitMpegIntensityStereoLSFTables();
  FUN_00519ef0();
  FUN_00519c80();
  return 0;
}

