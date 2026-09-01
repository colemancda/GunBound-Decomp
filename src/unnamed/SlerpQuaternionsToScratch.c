/* SlerpQuaternionsToScratch - 0x004f3c70 in the original binary.
 *
 * Spherical-linear quaternion interpolation, slerp(regEsi -> param_1,
 * t = param_2), into the shared DAT_005a94b0 scratch it returns - the
 * same four-float scratch MultiplyQuaternionsToScratch (0x4f3a60) uses.
 * The structure is exactly D3DXQuaternionSlerp's: dot = param_1 . regEsi;
 * if dot < 0 (_DAT_00557fb4 = 0.0f) the param_1 copy is negated to take
 * the short arc; then, when 1 - dot exceeds _DAT_00557fe4 (= 0.001f,
 * verified in .data), the weights are the SIN-BASED slerp pair
 * sin(t*theta)/sin(theta) and sin((1-t)*theta)/sin(theta) with theta from
 * the CRT st(0)-argument inverse-trig thunk at 0x5375c0 (acos of the dot,
 * by the identity); for near-parallel inputs it falls back to the linear
 * weights t / 1-t.  So this is slerp proper, not nlerp - the linear path
 * is only the standard small-angle fallback.
 *
 * What settles the operand shapes from outside: the single binary call
 * site, 0x4e97e5 in EvaluateKeyframeTrack (the keyframe-track evaluator), passes
 * two ADJACENT elements of a 0x10-byte-stride key array (track+0x11c,
 * elements i and i-1) with t = (time - times[i-1]) / (times[i] -
 * times[i-1]) from the parallel time array at track+0x118, and copies the
 * returned quaternion to DAT_005a90e0, which it hands straight to
 * QuaternionToRotationMatrix (0x4f3ba0).  Quaternion keyframe sampling,
 * textbook.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * __thiscall SlerpQuaternionsToScratch(float *param_1,double param_2,float *regEsi)

{
  float10 fVar1;
  float10 fVar2;
  float10 fVar3;
  float local_8;
  float local_4;
  
  local_4 = regEsi[3] * param_1[3] +
            *param_1 * *regEsi + param_1[1] * regEsi[1] + param_1[2] * regEsi[2];
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
    fVar1 = (float10)FUN_005375c0();  /* acos(dot) - CRT st(0) thunk */
    fVar2 = (float10)fsin(fVar1);
    fVar3 = (float10)fsin(fVar1 * (float10)local_8);
    local_8 = (float)(fVar3 * ((float10)_DAT_00557fb0 / fVar2));
    fVar1 = (float10)fsin(fVar1 * (float10)param_2);
    param_2 = (float)(fVar1 * ((float10)_DAT_00557fb0 / fVar2));
  }
  _DAT_005a94b0 = _DAT_005a94b0 * param_2 + local_8 * *regEsi;
  _DAT_005a94b4 = local_8 * regEsi[1] + _DAT_005a94b4 * param_2;
  _DAT_005a94b8 = local_8 * regEsi[2] + _DAT_005a94b8 * param_2;
  _DAT_005a94bc = _DAT_005a94bc * param_2 + local_8 * regEsi[3];
  return (undefined *)DAT_005a94b0;
}

