/* SceneNode_ScalarDtor - 0x004f3390 in the original binary.
 *
 * NAMING (batch 22, was FUN_004f3390): Slot 0 of the SceneNode base vtable
 * 0x557538 (whose slots 3/4 are SceneNode_UpdateTransform /
 * SceneNode_UpdateWorldViewProjection); calls SceneNode_Destructor
 * (0x4f33b0) then frees on the delete flag.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIX (2026-11-03): 0x4f3391-0x4f3393 is `mov esi,ecx / call 0x4f33b0` with
 * ECX still `this`; the call dropped it. Now SceneNode_Destructor(this) (was FUN_004f33b0).
 */
#include "ghidra_types.h"


void * __thiscall SceneNode_ScalarDtor(void *param_1,int param_2)

{
  SceneNode_Destructor((undefined4 *)param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

