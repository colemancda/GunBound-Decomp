/* QuaternionFromEulerAngles - 0x004f3af0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004f3af0 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. Evidence from outside the body: Leaf maths
 * routine, so the identity is read off the arithmetic with operand shapes
 * corroborated from outside. The result is four floats written through
 * EAX, and the only caller, EvaluateKeyframeTrack, calls it with (0, 0, 0)
 * into DAT_005a90e0 - the identity quaternion (0,0,0,1) - on the branch
 * where a track has fewer than two keys or the time is before the first
 * key; that same DAT_005a90e0 is the quaternion slot that
 * SlerpQuaternionsToScratch writes on the other branch and that
 * QuaternionToRotationMatrix (0x4f3ba0, reads x,y,z,w at [0..3]) consumes.
 * The arithmetic is half-angle sin/cos of the three arguments (the
 * multiplier _DAT_00557fb8 is the 0.5 constant) combined as sin*sin*sin +
 * cos*cos*cos for w - the expansion of D3DXQuaternionRotationYawPitchRoll
 * with (param_1, param_2, param_3) = (yaw, pitch, roll), except that the
 * first two result components are stored swapped (y, x, z, w). The Euler-
 * angle form is certain; the yaw/pitch/roll labels and the engine's axis
 * convention are not, so the name stops at EulerAngles. LIKELY.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void QuaternionFromEulerAngles(double param_1,double param_2,double param_3,float *regEax)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
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
  regEax[3] = (float)((float10)fVar1 * fVar5 * (float10)fVar2 +
                     (float10)fVar4 * (float10)fVar3 * fVar6);
  *regEax = (float)((float10)fVar4 * (float10)fVar3 * (float10)fVar2 -
                   (float10)fVar1 * fVar5 * fVar6);
  regEax[1] = (float)((float10)fVar3 * (float10)fVar2 * (float10)fVar1 +
                     (float10)fVar4 * fVar6 * fVar5);
  regEax[2] = (float)(fVar6 * (float10)fVar3 * (float10)fVar1 -
                     (float10)fVar4 * (float10)fVar2 * fVar5);
  return;
}

