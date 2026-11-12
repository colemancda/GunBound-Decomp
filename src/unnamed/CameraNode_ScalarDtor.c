/* CameraNode_ScalarDtor - 0x004e9b80 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Slot 0 of the 0x308-byte scene-node subclass vtable 0x557300
 * (globals.c PTR_FUN_00557300). It calls CameraNode_DtorBody and frees the
 * block when the flag word has bit 0 set, the scalar-deleting form, and
 * Stage_Destruct deletes the stage registry's +0x30 member through this
 * slot (mov ecx,[esi+0x30] / call [eax] with push 1 at 0x4e3911). For the
 * Camera prefix see CameraNode_DtorBody (LIKELY: it rests on the sibling
 * SceneNode_UpdateTransformAndCamera, which builds the projection from the
 * fov, near, far and aspect cells this class initialises).
 *
 * FIX (2026-11-03): ECX was dropped at the inner call. 0x4e9b81-0x4e9b83 is
 * `mov esi,ecx / call 0x4e9ba0` with ECX still `this`; slot 0 of vtable
 * 0x557300 (the 0x308-byte scene-node subclass). Now CameraNode_DtorBody(this).
 */
#include "ghidra_types.h"


void * __thiscall CameraNode_ScalarDtor(void *param_1,int param_2)

{
  CameraNode_DtorBody((undefined4 *)param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

