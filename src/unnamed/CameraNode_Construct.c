/* CameraNode_Construct - 0x004e9b30 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Constructor of the 0x308-byte scene-node subclass with vtable 0x557300.
 * The only caller is an uncarved static initialiser at 0x540e49, and the
 * object is the static at 0xe9b1e0 that the CRT atexit stub 0x543290 later
 * destroys through CameraNode_DtorBody. It runs the base constructor
 * FUN_004f3150 first, then overwrites the vtable with 0x557300, the
 * overwrite SceneNode_UpdateTransformAndCamera's header cites as what fixes
 * base versus derived, and sets the cells +0x2f4..+0x304 (fov pair 0x3fa4bc6a
 * and 0x3f24bc6a, near 1.0, far 1000.0, aspect = DAT_00588f54 divided by
 * DAT_00588f50). Those are the fov, near, far and aspect fields that
 * SceneNode_UpdateTransformAndCamera (slot 3 of the same vtable) feeds into
 * the perspective projection it publishes for the current camera. The Camera
 * prefix rests on that consumer, not on this body, so it is LIKELY. The
 * inline copy of these stores in FUN_004e3810 (0x4e387f-0x4e38a7) builds the
 * stage registry's +0x30 member.
 *
 * REGISTERS PROMOTED (2026-08-25): the whole function is one forwarded call --
 * `call 0x4f3150` is its first instruction -- so ECX, EDX and EAX all pass
 * straight through from its caller, which is an uncarved function at
 * 0x540e49.  EDX is an INPUT here (the object being constructed); Ghidra had
 * named it `regEdx` as though the callee produced it.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * CameraNode_Construct(undefined4 regEcx,undefined4 *regEdx,undefined4 regEax)

{
  float fVar1;
  
  FUN_004f3150(regEcx,regEdx,regEax);
  fVar1 = _DAT_00588f54 / _DAT_00588f50;
  *regEdx = &PTR_FUN_00557300;
  regEdx[0xbd] = 0x3fa4bc6a;
  regEdx[0xbf] = 0x3f800000;
  regEdx[0xc0] = 0x447a0000;
  regEdx[0xbe] = 0x3f24bc6a;
  regEdx[0xc1] = fVar1;
  return regEdx;
}

