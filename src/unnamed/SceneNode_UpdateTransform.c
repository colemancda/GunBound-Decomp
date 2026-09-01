/* SceneNode_UpdateTransform - 0x004f37b0 in the original binary.
 *
 * Slot 3 of the six-slot BASE vtable at 0x557538 (docs/vtable_census.txt)
 * - the base-class half of the twin whose derived override is
 * SceneNode_UpdateTransformAndCamera (0x4e9cc0, slot 3 of 0x557300; the
 * base ctor FUN_004f3150 installs 0x557538 first, then the derived ctors
 * FUN_004e3810/FUN_004e9b30 overwrite with 0x557300).  Both twins walk
 * the child list at +0xd4 (next link +0xd8) re-invoking slot 3
 * (*vtbl+0xc) on each child, and both share slot 4
 * (SceneNode_UpdateWorldViewProjection, 0x4f38a0) and slot 5 (0x4f3910,
 * uncarved).
 *
 * Same per-node transform refresh as the derived twin: world at +0xe0
 * from the keyframe-track evaluator EvaluateKeyframeTrack (track at +0xc8) or a
 * 4x4 identity, then world x= (+0x1a0 x parent frame) via
 * MultiplyMatrix4x4ToScratch/InPlace, the parent frame being the +0xd0
 * node's +0xe0 world matrix or, when unparented, the placement matrix
 * SceneNode_BuildLocalTransform builds into DAT_005a93f0 (binary
 * 0x4f3838 preloads EDX with it for both calls).  The differences from
 * the derived twin: the time comes from the node's own +0xcc field
 * (this[0x33]) instead of a parameter, FUN_004f3540 runs when the flag
 * at +0xc4 (this[0x31]) is set, and there is no camera/projection
 * rebuild at all.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void __fastcall SceneNode_UpdateTransform(int *param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  undefined4 unaff_retaddr;
  
  piVar1 = param_1 + 0x38;
  if (param_1[0x32] == 0) {
    piVar3 = piVar1;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *piVar3 = 0;
      piVar3 = piVar3 + 1;
    }
    param_1[0x47] = 0x3f800000;
    param_1[0x42] = 0x3f800000;
    param_1[0x3d] = 0x3f800000;
    *piVar1 = 0x3f800000;
  }
  else {
    EvaluateKeyframeTrack(param_1[0x33],piVar1,param_1[0x32]);
  }
  if (param_1[0x34] == 0) {
    /* Binary 0x4f3838: `mov edx,0x5a93f0` feeds BOTH calls - EDX for
     * SceneNode_BuildLocalTransform (which leaves it untouched) and, via
     * `mov eax,edx` at 0x4f3848, the second matrix operand of the
     * multiply. ESI is this object throughout; 0 is the dead-ECX slot. */
    SceneNode_BuildLocalTransform(0,(float *)DAT_005a93f0,(int)param_1);
    puVar4 = MultiplyMatrix4x4ToScratch((float *)(param_1 + 0x68),(float *)DAT_005a93f0);
    MultiplyMatrix4x4InPlace((float *)(param_1 + 0x38),(float *)puVar4);
  }
  else {
    /* Binary 0x4f37f1..0x4f380d: EAX = param_1[0x34] + 0xe0, ECX =
     * param_1 + 0x1a0, then EBX = param_1 + 0xe0 with EAX = the
     * multiply's returned scratch. */
    puVar4 = MultiplyMatrix4x4ToScratch((float *)(param_1 + 0x68),(float *)(param_1[0x34] + 0xe0));
    MultiplyMatrix4x4InPlace((float *)(param_1 + 0x38),(float *)puVar4);
    param_1[0x26] = param_1[0x44];
    param_1[0x27] = param_1[0x45];
    param_1[0x28] = param_1[0x46];
  }
  if (param_1[0x31] != 0) {
    FUN_004f3540();
  }
  (**(code **)(*param_1 + 4))(param_1[0x33]);
  for (piVar1 = (int *)param_1[0x35]; piVar1 != (int *)0x0; piVar1 = (int *)piVar1[0x36]) {
    (**(code **)(*piVar1 + 0xc))(unaff_retaddr);
  }
  return;
}

