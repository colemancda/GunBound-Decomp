/* SceneNode_UpdateWorldViewProjection - 0x004f38a0 in the original
 * binary.
 *
 * Slot 4 of BOTH scene-node vtables (0x557548 in the base vtable at
 * 0x557538, 0x557310 in the derived one at 0x557300 - see
 * docs/vtable_census.txt), and its own child walk over +0xd4/+0xd8
 * re-invokes slot 4 (*vtbl+0x10), the recursive-slot signature this
 * cluster's slot-3 twins share.
 *
 * When the byte at +0xdc is 1 it bakes the two camera globals into
 * per-node composites: this+0x120 = world (+0xe0) x DAT_005a9250, and
 * this+0x160 = (+0x120) x DAT_005a9290.  Both right-hand operands are
 * produced by SceneNode_UpdateTransformAndCamera's camera branch:
 * DAT_005a9250 is the view matrix (inverse of the camera node's world
 * matrix, written by its FUN_004f2530 call with EDX = 0x5a9250 preloaded
 * at 0x4e9d7f) and DAT_005a9290 is the D3D-style perspective projection
 * it builds from fov/near/far/aspect.  So +0x120 is the node's
 * world-view and +0x160 its world-view-projection matrix.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void __fastcall SceneNode_UpdateWorldViewProjection(int param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  
  if (*(char *)(param_1 + 0xdc) == '\x01') {
    /* Binary 0x4f38ae/0x4f38b4: ECX = param_1 + 0xe0, EAX = 0x5a9250. */
    puVar2 = MultiplyMatrix4x4ToScratch((float *)(param_1 + 0xe0),(float *)DAT_005a9250);
    puVar4 = (undefined4 *)(param_1 + 0x120);
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar4 = puVar4 + 1;
    }
    /* Binary 0x4f38cf/0x4f38d6: ECX = the +0x120 slot just filled (EDX
     * kept from the lea at 0x4f38be), EAX = 0x5a9290 - the projection. */
    puVar2 = MultiplyMatrix4x4ToScratch((float *)(param_1 + 0x120),(float *)DAT_005a9290);
    puVar4 = (undefined4 *)(param_1 + 0x160);
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar4 = puVar4 + 1;
    }
  }
  for (piVar1 = *(int **)(param_1 + 0xd4); piVar1 != (int *)0x0; piVar1 = (int *)piVar1[0x36]) {
    (**(code **)(*piVar1 + 0x10))();
  }
  return;
}

