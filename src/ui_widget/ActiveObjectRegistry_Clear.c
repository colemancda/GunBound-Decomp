/* ActiveObjectRegistry_Clear - 0x004f3060 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004f3060 mean this function.)
 *
 * NAMED (batch 48), HIGH. The destroy-all-layers member of the
 * ActiveObjectRegistry class, so named in
 * ActiveObjectRegistry_BaseConstructor's header, which lists it with the
 * constructor, CreateActiveObjectLayer, RegisterActiveObject and
 * SweepActiveObjectRegistry as one contiguous class block. Both base
 * destructors (ActiveObjectRegistry_BaseScalarDtor and 0x4f2ee0) call it
 * first and then delete the sentinel, and it ends by re-pointing the
 * sentinel's +0x18/+0x1c outer links at itself, the empty state the
 * constructor builds. It is also called outside any destructor, on a live
 * registry: State09_ReadyRoom_OnCommand and
 * State09_ReadyRoom_ProcessPacket call it on g_activeObjectRegistry2, and
 * State11_InBattle_OnExit on the client-context registry at +0x6a7f88,
 * which is why it is Clear rather than a Dtor.
 *
 * FIX (2026-11-03), the per-layer delete only: 0x4f308f-0x4f3095 is `mov
 * edx,[esi] / push 1 / mov ecx,esi / call [edx]`, ESI = a layer node off
 * the outer list (+0x1c). Every layer is built by CreateActiveObjectLayer
 * (0x4f2f00, vtable 0x557530 stamped at 0x4f2f23) and the sentinel is
 * skipped, so slot 0 is always FUN_004f2e20, a raw-C port of a __thiscall
 * scalar-deleting destructor. It now gets (node, 1) instead of (1). The
 * inner per-object delete at 0x4f3080-0x4f3087 (`mov ecx,obj / push 1 /
 * call [eax]`) is NOT fixed: those objects come from many classes, some
 * raw-C (cdecl, this first) and some genuine C++ (__fastcall), so no
 * single port signature is right for every one.
 */
#include "ghidra_types.h"

/* Slot 0 of the layer-node vtable 0x557530: FUN_004f2e20, a raw-C port of
 * a __thiscall scalar-deleting destructor, so `this` is the first arg. */
typedef void *(*LayerNodeDeleteFn)(void *self,int flags);


void ActiveObjectRegistry_Clear(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  puVar4 = (undefined4 *)(*(undefined4 **)(param_1 + 4))[7];
  if (puVar4 != *(undefined4 **)(param_1 + 4)) {
    do {
      puVar1 = (undefined4 *)puVar4[4];
      puVar2 = (undefined4 *)puVar4[7];
      while (puVar1 != puVar4) {
        puVar3 = (undefined4 *)*puVar1;
        puVar1 = (undefined4 *)puVar1[4];
        (*(code *)*puVar3)(1);
      }
      (*(LayerNodeDeleteFn *)*puVar4)(puVar4,1);
      puVar4 = puVar2;
    } while (puVar2 != *(undefined4 **)(param_1 + 4));
  }
  *(int *)(*(int *)(param_1 + 4) + 0x18) = *(int *)(param_1 + 4);
  *(int *)(*(int *)(param_1 + 4) + 0x1c) = *(int *)(param_1 + 4);
  return;
}

