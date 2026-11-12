/* InitMpegImdctKernelTables - 0x00519ef0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section. (Previously FUN_00519ef0.)
 *
 * Evidence for the name (all from outside the body):
 * Called once, from InitMpegLayerIIITables, right before InitMpegImdctWindows
 * and after the other Layer III table builders (Pow43, SubblockGain,
 * antialias, intensity stereo). It obtains its destinations through
 * GetMpegImdctLongTables (0x568800 record: 0xf25900, 0xf25960, 0xf259a0) and
 * GetMpegImdctShortTables (0x568810 record: 0xf258c0, 0xf258e0, 0xf25a30).
 * It writes, for the long set, 18 values 2cos((2k+1)pi/72), 9 values
 * 2cos((2k+1)pi/36) and 36 values cos(i*j*pi/36) (i even 0..16, j in 1,3,5,7),
 * and for the short set 6 values cos((2k+1)pi/24), 3 values
 * 2cos((2k+1)pi/12) and the scalar sqrt(3); the divisors 72, 36, 24 and 12
 * were read from the constants at 0x544af0, 0x544ae0, 0x544ae8 and 0x544ad8
 * and the pi comes from atan(1.0)*4.0 (0x527d50 and 0x5448e0). The consumers
 * are the 36-point and 12-point IMDCT kernels (MpegImdct36, MpegImdct12) which
 * read exactly these addresses. "Kernel tables" distinguishes it from
 * InitMpegImdctWindows (the 0xf25b00 window set).
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void InitMpegImdctKernelTables(void)

{
  double dVar1;
  double dVar2;
  undefined4 *puVar3;
  float *pfVar4;
  float *pfVar5;
  int iVar6;
  float *pfVar7;
  float *pfVar8;
  float10 fVar9;
  double dVar10;
  int local_28;
  
  puVar3 = (undefined4 *)GetMpegImdctLongTables();
  pfVar4 = (float *)*puVar3;
  pfVar8 = (float *)puVar3[1];
  pfVar5 = (float *)puVar3[2];
  dVar10 = FID_conflict__cos(1.0);
  dVar10 = dVar10 * _DAT_005448e0;
  local_28 = 1;
  dVar2 = dVar10 / _DAT_00544af0;
  do {
    fVar9 = (float10)FUN_00527cb4((double)local_28 * dVar2);
    *pfVar4 = (float)(fVar9 + fVar9);
    local_28 = local_28 + 2;
    pfVar4 = pfVar4 + 1;
  } while (local_28 < 0x25);
  local_28 = 1;
  do {
    dVar1 = (double)local_28 * dVar2;
    fVar9 = (float10)FUN_00527cb4(dVar1 + dVar1);
    local_28 = local_28 + 2;
    *pfVar8 = (float)(fVar9 + fVar9);
    pfVar8 = pfVar8 + 1;
  } while (local_28 < 0x13);
  dVar10 = dVar10 / _DAT_00544ae0;
  local_28 = 0;
  do {
    iVar6 = local_28;
    dVar2 = (double)local_28;
    local_28 = 1;
    do {
      fVar9 = (float10)FUN_00527cb4((double)local_28 * dVar2 * dVar10);
      *pfVar5 = (float)fVar9;
      local_28 = local_28 + 2;
      pfVar5 = pfVar5 + 1;
    } while (local_28 < 9);
    local_28 = iVar6 + 2;
  } while (local_28 < 0x12);
  puVar3 = (undefined4 *)GetMpegImdctShortTables();
  pfVar4 = (float *)*puVar3;
  pfVar8 = (float *)puVar3[1];
  pfVar5 = (float *)puVar3[2];
  dVar10 = FID_conflict__cos(1.0);
  dVar10 = dVar10 * _DAT_005448e0;
  iVar6 = 1;
  dVar2 = dVar10 / _DAT_00544ae8;
  pfVar7 = pfVar4;
  do {
    fVar9 = (float10)FUN_00527cb4((double)iVar6 * dVar2);
    iVar6 = iVar6 + 2;
    *pfVar7 = (float)(fVar9 + fVar9);
    pfVar7 = pfVar7 + 1;
  } while (iVar6 < 0xd);
  iVar6 = 1;
  do {
    dVar1 = (double)iVar6 * dVar2;
    fVar9 = (float10)FUN_00527cb4(dVar1 + dVar1);
    iVar6 = iVar6 + 2;
    *pfVar8 = (float)(fVar9 + fVar9);
    pfVar8 = pfVar8 + 1;
  } while (iVar6 < 7);
  dVar10 = dVar10 / _DAT_00544ad8;
  fVar9 = (float10)FUN_00527cb4(dVar10 + dVar10);
  iVar6 = 6;
  *pfVar5 = (float)fVar9;
  do {
    iVar6 = iVar6 + -1;
    *pfVar4 = *pfVar4 / _DAT_00544370;
    pfVar4 = pfVar4 + 1;
  } while (iVar6 != 0);
  *pfVar5 = *pfVar5 + *pfVar5;
  return;
}

