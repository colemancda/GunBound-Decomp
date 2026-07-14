/* SweepActiveObjectRegistry - 0x004f3020 in the original binary.
 *
 * PROMOTED (2026-07-13): the CButtonWidget vtable cross-reference
 * (src/cxx/ButtonWidget.h) confirms the real behavior: walks the
 * active-object registry's outer (layer) list, and for each layer's
 * inner (button) list calls every button's own vtable slot 0 -
 * `Delete(1)` - i.e. destroys every registered active object, then
 * resets that layer's now-empty inner-list links to self and advances
 * to the next layer via its own outer-list link. The layer nodes
 * themselves are NOT freed - only their button contents are torn down.
 * Called twice per ChangeGameState (once per registry, see
 * ChangeGameState.c/GameStateMachine.cpp), matching that file's own
 * "active-object sweeps" comment.
 *
 * STILL BRING-UP BYPASSED (stubbed to a no-op): `registry` (orig
 * unaff_EBX, a dropped register whose value differs per call site -
 * orig 0x41231f: `mov ebx,0xe9be90` before ChangeGameState's first
 * call, orig 0x41232b: `mov ebx,0xe9c0fc` before its second) is kept as
 * an explicit parameter here, but the body itself is left a no-op. The
 * ORIGINAL blocker - DAT_00e9be90/DAT_00e9c0fc were 1-byte placeholders
 * while this function indexes them as a real 32-byte struct - is now
 * resolved (see globals.c/crt_shims_msvc.c: both are sized to 0x20
 * bytes with a self-referencing empty-sentinel init), so restoring the
 * real body below is safe whenever it's next picked up; not done in
 * this pass since nothing yet populates either registry with real
 * buttons in the bring-up build, so the no-op and the real body are
 * behaviorally identical for now:
 *
 *   void SweepActiveObjectRegistry(int registry)
 *   {
 *     undefined4 *puVar1, *puVar3;
 *     puVar3 = (undefined4 *)(*(undefined4 **)(registry + 4))[7];
 *     if (puVar3 != *(undefined4 **)(registry + 4)) {
 *       do {
 *         puVar1 = (undefined4 *)puVar3[4];
 *         while (puVar1 != puVar3) {
 *           undefined4 *next = (undefined4 *)puVar1[4];
 *           (**(code **)*puVar1)(1);   // vtable slot 0: Delete(1)
 *           puVar1 = next;
 *         }
 *         puVar3[3] = (undefined4)puVar3;
 *         puVar3[4] = (undefined4)puVar3;
 *         puVar3 = (undefined4 *)puVar3[7];
 *       } while (puVar3 != *(undefined4 **)(registry + 4));
 *     }
 *   }
 *
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-
 * verified. See src/README.md's "Raw/verbatim ports" section for status.
 */
#include "ghidra_types.h"


void SweepActiveObjectRegistry(int registry)

{
  (void)registry;
  return;
}

