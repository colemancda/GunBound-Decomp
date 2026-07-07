/* FUN_00519aa0 - 0x00519aa0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00519aa0(void)

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
  
  pfVar2 = (float *)FUN_00518520();
  iVar4 = 0;
  do {
    dVar8 = _pow(2.0,(double)(iVar4 + -0x9c) * _DAT_00544ac0);
    *pfVar2 = (float)dVar8;
    iVar4 = iVar4 + 1;
    pfVar2 = pfVar2 + 1;
  } while (iVar4 < 0x106);
  pfVar2 = (float *)FUN_00518530();
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
  pfVar2 = (float *)FUN_005180d0();
  pfVar6 = (float *)&DAT_00544a88;
  do {
    fVar7 = (float10)FUN_00527f34((double)(*pfVar6 * *pfVar6 + (float)_DAT_00544aa8));
    *pfVar2 = (float)((float10)_DAT_00544aa8 / fVar7);
    fVar1 = *pfVar6;
    fVar7 = (float10)FUN_00527f34((double)(*pfVar6 * *pfVar6 + (float)_DAT_00544aa8));
    pfVar6 = pfVar6 + 1;
    pfVar2[1] = (float)((float10)fVar1 / fVar7);
    pfVar2 = pfVar2 + 2;
  } while ((int)pfVar6 < 0x544aa8);
  FUN_0051a120();
  FUN_0051a230();
  FUN_00519ef0();
  FUN_00519c80();
  return 0;
}

