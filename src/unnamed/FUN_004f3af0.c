/* FUN_004f3af0 - 0x004f3af0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004f3af0(double param_1,double param_2,double param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float *in_EAX;
  float10 fVar5;
  float10 fVar6;
  
  fVar5 = (float10)fsin((float10)param_2 * (float10)_DAT_00557fb8);
  fVar6 = (float10)fsin((float10)param_3 * (float10)_DAT_00557fb8);
  fVar1 = (float)fVar6;
  fVar6 = (float10)fsin((float10)param_1 * (float10)_DAT_00557fb8);
  fVar2 = (float)fVar6;
  fVar6 = (float10)fcos((float10)param_2 * (float10)_DAT_00557fb8);
  fVar3 = (float)fVar6;
  fVar6 = (float10)fcos((float10)param_3 * (float10)_DAT_00557fb8);
  fVar4 = (float)fVar6;
  fVar6 = (float10)fcos((float10)param_1 * (float10)_DAT_00557fb8);
  in_EAX[3] = (float)((float10)fVar1 * fVar5 * (float10)fVar2 +
                     (float10)fVar4 * (float10)fVar3 * fVar6);
  *in_EAX = (float)((float10)fVar4 * (float10)fVar3 * (float10)fVar2 -
                   (float10)fVar1 * fVar5 * fVar6);
  in_EAX[1] = (float)((float10)fVar3 * (float10)fVar2 * (float10)fVar1 +
                     (float10)fVar4 * fVar6 * fVar5);
  in_EAX[2] = (float)(fVar6 * (float10)fVar3 * (float10)fVar1 -
                     (float10)fVar4 * (float10)fVar2 * fVar5);
  return;
}

