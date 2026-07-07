/* FUN_0051a120 - 0x0051a120 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0051a120(void)

{
  double dVar1;
  double dVar2;
  int iVar3;
  float *pfVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  double dVar8;
  
  iVar3 = FUN_005180e0();
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
    fVar6 = (float10)FUN_00527f34(0,0x40000000);
    *pfVar4 = (float)(fVar6 * (float10)dVar2);
    fVar6 = (float10)FUN_00527f34(0,0x40000000);
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

