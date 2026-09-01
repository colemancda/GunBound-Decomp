/* SceneNode_UpdateTransformAndCamera - 0x004e9cc0 in the original binary.
 *
 * Slot 3 of the six-slot vtable at 0x557300 (docs/vtable_census.txt) -
 * the derived-class override of the slot SceneNode_UpdateTransform
 * (0x4f37b0) fills in the base vtable at 0x557538.  The base ctor
 * FUN_004f3150 installs 0x557538 first and the two derived ctors
 * (FUN_004e3810 at 0x4e387b, FUN_004e9b30 at 0x4e9b43) overwrite it
 * with 0x557300, which is what fixes base/derived.  The walk over the
 * child list at +0xd4 (next link +0xd8) re-invokes slot 3 (*vtbl+0xc)
 * on each child - the recursion that makes the slot identity, and the
 * twin relation, observable from outside either body.
 *
 * Per node: refresh the world matrix at +0xe0 - the keyframe-track
 * evaluator EvaluateKeyframeTrack (time = param_2, TRS track at +0xc8) or a 4x4
 * identity when there is no track - then fold in +0x1a0 x parent frame
 * via MultiplyMatrix4x4ToScratch/InPlace, where the parent frame is the
 * +0xd0 node's world matrix, or the node's own placement matrix from
 * SceneNode_BuildLocalTransform when +0xd0 is null.
 *
 * The AndCamera half, gated on the byte at +0xdc: publish this node as
 * the current camera (_DAT_0079361c = this), rebuild the VIEW matrix
 * DAT_005a9250 as the inverse of the node's own world matrix (the
 * FUN_004f2530 call - binary preloads ECX = this+0xe0 via EBP and EDX =
 * 0x5a9250 at 0x4e9d7f; that callee computes 1/det of the 3x3 and takes
 * a transpose fast path when det == 1; both arguments recovered
 * 2026-08-31 - see the note at the call), and rebuild the
 * PROJECTION matrix DAT_005a9290 as a D3D-style left-handed perspective
 * from the node's own fov/near/far/aspect fields at +0x2f8..+0x304:
 * m00 = cot(fov)*aspect, m11 = cot(fov), m22 = zf/(zf-zn), m23 = 1,
 * m32 = -zn*zf/(zf-zn).  Slot 4, SceneNode_UpdateWorldViewProjection
 * (0x4f38a0, shared by both vtables), consumes exactly those two
 * globals.  The base twin never touches them, and reads its time from
 * +0xcc instead of taking param_2.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall SceneNode_UpdateTransformAndCamera(int *param_1,undefined4 param_2)

{
  float fVar1;
  float fVar2;
  int *piVar3;
  float fVar4;
  int iVar5;
  int *piVar6;
  undefined4 *puVar7;
  float10 fVar8;
  float10 fVar9;
  
  piVar3 = param_1 + 0x38;
  if (param_1[0x32] == 0) {
    piVar6 = piVar3;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *piVar6 = 0;
      piVar6 = piVar6 + 1;
    }
    param_1[0x47] = 0x3f800000;
    param_1[0x42] = 0x3f800000;
    param_1[0x3d] = 0x3f800000;
    *piVar3 = 0x3f800000;
  }
  else {
    EvaluateKeyframeTrack(param_2,piVar3,param_1[0x32]);
  }
  if (param_1[0x34] == 0) {
    /* Binary 0x4e9d4d: `mov edx,0x5a9130` feeds BOTH calls - EDX for
     * SceneNode_BuildLocalTransform (which leaves it untouched) and, via
     * `mov eax,edx` at 0x4e9d5d, the second matrix operand of the
     * multiply. ESI is this object throughout; 0 is the dead-ECX slot. */
    SceneNode_BuildLocalTransform(0,(float *)DAT_005a9130,(int)param_1);
    puVar7 = MultiplyMatrix4x4ToScratch((float *)(param_1 + 0x68),(float *)DAT_005a9130);
    MultiplyMatrix4x4InPlace((float *)(param_1 + 0x38),(float *)puVar7);
  }
  else {
    /* Binary 0x4e9d06..0x4e9d22: EAX = param_1[0x34] + 0xe0 (the source
     * node's own matrix slot), ECX = param_1 + 0x1a0, then EBX =
     * param_1 + 0xe0 with EAX = the multiply's returned scratch. */
    puVar7 = MultiplyMatrix4x4ToScratch((float *)(param_1 + 0x68),(float *)(param_1[0x34] + 0xe0));
    MultiplyMatrix4x4InPlace((float *)(param_1 + 0x38),(float *)puVar7);
    param_1[0x26] = param_1[0x44];
    param_1[0x27] = param_1[0x45];
    param_1[0x28] = param_1[0x46];
  }
  if ((char)param_1[0x37] != '\0') {
    fVar8 = (float10)fcos((float10)(float)param_1[0xbe]);
    fVar9 = (float10)fsin((float10)(float)param_1[0xbe]);
    fVar1 = (float)(fVar8 / fVar9);
    fVar2 = (float)((fVar8 / fVar9) * (float10)(float)param_1[0xc1]);
    fVar4 = (float)param_1[0xc0] / ((float)param_1[0xc0] - (float)param_1[0xbf]);
    _DAT_0079361c = param_1;
    /* Binary 0x4e9d7f/0x4e9d86: EDX=0x5a9250, ECX=EBP=param_1+0xe0 - the
     * view matrix is the affine inverse of this camera node's world
     * matrix. Before 2026-08-31 this call was argless and the view
     * rebuild a no-op. */
    FUN_004f2530((float *)(param_1 + 0x38),(float *)DAT_005a9250);
    puVar7 = (undefined4 *)DAT_005a9290;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar7 = 0;
      puVar7 = puVar7 + 1;
    }
    _DAT_005a92bc = 1.0f;
    _DAT_005a92c8 = -(fVar4 * (float)param_1[0xbf]);
    _DAT_00588f68 = param_1[0xbf];
    _DAT_00588f6c = param_1[0xc0];
    _DAT_00588f70 = fVar2;
    _DAT_00588f74 = fVar1;
    *(float *)DAT_005a9290 = fVar2;
    _DAT_005a92a4 = fVar1;
    _DAT_005a92b8 = fVar4;
  }
  (**(code **)(*param_1 + 4))(param_2);
  for (piVar3 = (int *)param_1[0x35]; piVar3 != (int *)0x0; piVar3 = (int *)piVar3[0x36]) {
    (**(code **)(*piVar3 + 0xc))(param_2);
  }
  return;
}

