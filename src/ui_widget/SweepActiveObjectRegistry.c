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
 * RESTORED (2026-07-19): this was a bring-up no-op stub, bypassed because
 * "nothing yet populates either registry with real buttons". That stopped
 * holding once State02's buttons started registering: with no sweep they
 * survived the state change and State03's lobby buttons - which reuse the
 * same (layer,id) keys (0,0),(0,1),... - collided in RegisterActiveObject,
 * whose duplicate-id branch DESTROYS the newly created node, handing
 * CreateButtonWidget back a freed object. Body verified instruction by
 * instruction against orig 0x4f3020-0x4f3056 AND emulated in angr (walks a
 * synthetic 1-layer/2-node list, calls both dtors in order with ECX=this,
 * resets the layer links to self, returns cleanly).
 * Restoring it also required fixing the registry ROOT init: the container
 * cannot be its own sentinel because registry+0x10 is the input-event ring
 * pointer - see gb_init_widget_registry in src/cxx/crt_shims_msvc.c.
 * (historical note) `registry` (orig
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


/* Nodes are destroyed through vtable slot 0, which is __thiscall(this,
 * freeFlag) = __fastcall(this, edxDummy, freeFlag): orig 0x4f3037-0x4f303e
 * (`mov eax,[ecx]` / `push 1` / `call dword ptr [eax]` with ECX still holding
 * the node). Same typedef/call form as RegisterActiveObject.c. */
typedef void *(__fastcall *ScalarDeletingDtorFn)(void *thisPtr,int edxDummy,int freeFlag);

void SweepActiveObjectRegistry(int registry)

{
  undefined4 *puVar1;
  undefined4 *puVar3;
  undefined4 *next;

  puVar3 = (undefined4 *)(*(undefined4 **)(registry + 4))[7];
  if (puVar3 != *(undefined4 **)(registry + 4)) {
    do {
      puVar1 = (undefined4 *)puVar3[4];
      while (puVar1 != puVar3) {
        next = (undefined4 *)puVar1[4];
        (*(ScalarDeletingDtorFn *)*puVar1)(puVar1,0,1);   /* vtable[0] Delete(1) */
        puVar1 = next;
      }
      puVar3[3] = (undefined4)puVar3;
      puVar3[4] = (undefined4)puVar3;
      puVar3 = (undefined4 *)puVar3[7];
    } while (puVar3 != *(undefined4 **)(registry + 4));
  }
  return;
}

