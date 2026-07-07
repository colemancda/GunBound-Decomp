/* FUN_004f3ba0 - 0x004f3ba0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_004f3ba0(float *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float *in_EAX;
  
  fVar8 = *in_EAX + *in_EAX;
  fVar10 = in_EAX[1] + in_EAX[1];
  fVar11 = in_EAX[2] + in_EAX[2];
  fVar9 = fVar8 * *in_EAX;
  fVar1 = in_EAX[1];
  fVar2 = in_EAX[2];
  fVar3 = *in_EAX;
  fVar4 = *in_EAX;
  fVar5 = in_EAX[1];
  fVar8 = fVar8 * in_EAX[3];
  fVar6 = in_EAX[3];
  fVar7 = in_EAX[3];
  *param_1 = _DAT_00557fb0 - (fVar11 * fVar2 + fVar10 * fVar1);
  param_1[4] = fVar10 * fVar3 - fVar11 * fVar7;
  param_1[8] = fVar10 * fVar6 + fVar11 * fVar4;
  param_1[1] = fVar11 * fVar7 + fVar10 * fVar3;
  param_1[5] = _DAT_00557fb0 - (fVar11 * fVar2 + fVar9);
  param_1[9] = fVar11 * fVar5 - fVar8;
  param_1[2] = fVar11 * fVar4 - fVar10 * fVar6;
  param_1[6] = fVar8 + fVar11 * fVar5;
  param_1[10] = _DAT_00557fb0 - (fVar10 * fVar1 + fVar9);
  return;
}

