/* MultiplyQuaternionsToScratch - 0x004f3a60 in the original binary.
 *
 * The Grassmann quaternion product param_1 * regEax, components stored
 * (x,y,z,w) at [0..3]: out.x = a.w*b.x + a.x*b.w + a.y*b.z - a.z*b.y and
 * so on, with out.w = a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z.  The result
 * goes into the shared static scratch DAT_005a94b0 (which it returns) -
 * the same fixed-global-return pattern, and the same naming, as
 * MultiplyMatrix4x4ToScratch (0x4f1f50); SlerpQuaternionsToScratch
 * (0x4f3c70) writes the very same scratch.
 *
 * The algebraic identity alone would just describe the body; what settles
 * that the operands are rotation quaternions is the caller chain: the
 * sole binary call site, 0x4f344d in SceneNode_BuildLocalTransform
 * (0x4f3440), feeds it the scene-node fields this+0xa8 and this+0x1e0
 * and hands the returned four floats (via the DAT_005a93e0 staging copy)
 * straight to QuaternionToRotationMatrix (0x4f3ba0), which expands them
 * into the 3x3 rotation block of the 4x4 transform matrix that
 * SceneNode_UpdateTransform* then concatenate with MultiplyMatrix4x4*.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * __fastcall MultiplyQuaternionsToScratch(float *param_1,float *regEax)

{
  
  _DAT_005a94b0 =
       (param_1[3] * *regEax + param_1[1] * regEax[2] + regEax[3] * *param_1) -
       param_1[2] * regEax[1];
  _DAT_005a94b4 =
       (param_1[2] * *regEax + regEax[3] * param_1[1] + param_1[3] * regEax[1]) -
       *param_1 * regEax[2];
  _DAT_005a94b8 =
       (regEax[1] * *param_1 + regEax[3] * param_1[2] + param_1[3] * regEax[2]) -
       param_1[1] * *regEax;
  _DAT_005a94bc =
       ((param_1[3] * regEax[3] - *regEax * *param_1) - regEax[1] * param_1[1]) -
       param_1[2] * regEax[2];
  return (undefined *)DAT_005a94b0;
}

