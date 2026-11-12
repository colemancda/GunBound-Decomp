/* CameraNode_DtorBody - 0x004e9ba0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Destructor body of the 0x308-byte scene-node subclass whose vtable is
 * 0x557300. Slot 0 of that vtable is 0x4e9b80 (CameraNode_ScalarDtor),
 * which calls this and then frees; the other caller is the CRT atexit
 * stub 0x543290, which loads ECX = 0xe9b1e0, the static instance built by
 * CameraNode_Construct (0x4e9b30). It re-stamps 0x557300 and tail-jumps to
 * the base destructor SceneNode_Destructor (0x4f33b0).
 *
 * Why Camera: the slot-3 override of that vtable,
 * SceneNode_UpdateTransformAndCamera (0x4e9cc0), publishes the node as
 * the current camera, rebuilds the view matrix as the inverse of its
 * world matrix and builds a perspective projection from the fov, near,
 * far and aspect cells at +0x2f4..+0x304. CameraNode_Construct sets those
 * cells (fov constants, near 1.0, far 1000.0, aspect from the
 * DAT_00588f54 / DAT_00588f50 pair), and FUN_004e3810 sets them
 * identically inline (0x4e387f-0x4e38a7) for the stage registry's +0x30
 * member (see Stage_Destruct). The Camera prefix rests on those
 * neighbours, not on this body, so it is LIKELY: the class is a
 * SceneNode that doubles as the scene camera.
 *
 * FIX (2026-11-03): the tail `jmp 0x4f33b0` (0x4e9ba6) keeps ECX = this;
 * FUN_004f33b0 now receives it. Callers: FUN_004e9b80 (this) and the
 * excluded CRT atexit stub 0x543290 (ECX = 0xe9b1e0).
 */
#include "ghidra_types.h"


void __fastcall CameraNode_DtorBody(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_00557300;
  SceneNode_Destructor(param_1); /* FUN_004f33b0 is now SceneNode_Destructor */
  return;
}

