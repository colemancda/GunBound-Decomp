/* QuaternionToRotationMatrix - 0x004f3ba0 in the original binary.
 *
 * Expands the quaternion at regEax ((x,y,z,w) at [0..3]) into the 3x3
 * rotation block of the 4x4 float matrix param_1 points at: the textbook
 * identity m00 = 1 - 2(y*y + z*z), m01 = 2(x*y + w*z), m02 = 2(x*z - w*y)
 * and so on, written at float indices 0,1,2 / 4,5,6 / 8,9,10 - a
 * four-float row stride, i.e. the upper-left of a 4x4.  _DAT_00557fb0 is
 * the constant 1.0f (verified in .data).
 *
 * The operand shapes are corroborated outside the body at both binary
 * call sites:
 *   - 0x4f347b in SceneNode_BuildLocalTransform (0x4f3440): the target is
 *     the 0x40-byte matrix its own caller preloads in EDX (DAT_005a9130 /
 *     DAT_005a93f0), whose rows 0xc-0xe then receive the node translation
 *     and whose 3x3 block gets the uniform scale - and which then feeds
 *     MultiplyMatrix4x4ToScratch as a matrix operand.
 *   - 0x4e99f5 in EvaluateKeyframeTrack, the keyframe-track evaluator: the source
 *     quaternion there is DAT_005a90e0, the output of the quaternion
 *     keyframe interpolation (SlerpQuaternionsToScratch's product), and
 *     the target is the node matrix slot the evaluator fills.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall QuaternionToRotationMatrix(float *param_1,float *regEax)

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
  
  fVar8 = *regEax + *regEax;
  fVar10 = regEax[1] + regEax[1];
  fVar11 = regEax[2] + regEax[2];
  fVar9 = fVar8 * *regEax;
  fVar1 = regEax[1];
  fVar2 = regEax[2];
  fVar3 = *regEax;
  fVar4 = *regEax;
  fVar5 = regEax[1];
  fVar8 = fVar8 * regEax[3];
  fVar6 = regEax[3];
  fVar7 = regEax[3];
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

