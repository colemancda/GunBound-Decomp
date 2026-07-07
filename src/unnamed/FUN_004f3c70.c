/* FUN_004f3c70 - 0x004f3c70 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * __thiscall FUN_004f3c70(float *param_1,float param_2)

{
  float *unaff_ESI;
  float10 fVar1;
  float10 fVar2;
  float10 fVar3;
  float local_8;
  float local_4;
  
  local_4 = unaff_ESI[3] * param_1[3] +
            *param_1 * *unaff_ESI + param_1[1] * unaff_ESI[1] + param_1[2] * unaff_ESI[2];
  if (_DAT_00557fb4 <= local_4) {
    _DAT_005a94b0 = *param_1;
    _DAT_005a94b4 = param_1[1];
    _DAT_005a94b8 = param_1[2];
    _DAT_005a94bc = param_1[3];
  }
  else {
    local_4 = -local_4;
    _DAT_005a94b0 = -*param_1;
    _DAT_005a94b4 = -param_1[1];
    _DAT_005a94b8 = -param_1[2];
    _DAT_005a94bc = -param_1[3];
  }
  local_8 = _DAT_00557fb0 - param_2;
  if (_DAT_00557fe4 < _DAT_00557fb0 - local_4) {
    fVar1 = (float10)FUN_005375c0();
    fVar2 = (float10)fsin(fVar1);
    fVar3 = (float10)fsin(fVar1 * (float10)local_8);
    local_8 = (float)(fVar3 * ((float10)_DAT_00557fb0 / fVar2));
    fVar1 = (float10)fsin(fVar1 * (float10)param_2);
    param_2 = (float)(fVar1 * ((float10)_DAT_00557fb0 / fVar2));
  }
  _DAT_005a94b0 = _DAT_005a94b0 * param_2 + local_8 * *unaff_ESI;
  _DAT_005a94b4 = local_8 * unaff_ESI[1] + _DAT_005a94b4 * param_2;
  _DAT_005a94b8 = local_8 * unaff_ESI[2] + _DAT_005a94b8 * param_2;
  _DAT_005a94bc = _DAT_005a94bc * param_2 + local_8 * unaff_ESI[3];
  return &DAT_005a94b0;
}

