/* FUN_00519ef0 - 0x00519ef0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00519ef0(void)

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
  
  puVar3 = (undefined4 *)FUN_0051c660();
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
  puVar3 = (undefined4 *)FUN_0051c670();
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

