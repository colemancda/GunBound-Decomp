/* FUN_00401a70 - 0x00401a70 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIX (2026-11-03): sentinel delete passes `this`. 0x401b8e-0x401b99 is
 * `mov ecx,[ebp+4] / mov edx,[ecx] / push 1 / call [edx]`, so ECX is the
 * sentinel layer node ActiveObjectRegistry_BaseConstructor (0x4f2e40)
 * hangs at +4, stamped with the layer vtable 0x557530 at 0x4f2e68. That
 * vtable's only slot is 0x4f2e20 (FUN_004f2e20, `mov esi,ecx` ... `ret
 * 4`), a raw-C port of a __thiscall scalar-deleting destructor, so `this`
 * is its first cdecl argument. The port called `(*(code *)slot0)(1)`,
 * dropping the node; it now passes (node, 1) through LayerNodeDeleteFn.
  *
 * FIX (2026-11-03): the SEH frame artifacts are stripped. `unaff_FS_OFFSET` was
 * an unassigned pointer (the decompiler's stand-in for fs:[0]) that the
 * prologue/epilogue dereferenced and wrote through - a certain crash.
 * Prologue `mov eax,fs:0` / `push handler` / `mov fs:0,esp` is the MSVC
 * try-frame and is dropped here as in PanelManager_BaseDestructor and
 * WidgetChildArray_Destroy.
 */
#include "ghidra_types.h"

/* Slot 0 of the layer-node vtable 0x557530: FUN_004f2e20, a raw-C port of
 * a __thiscall scalar-deleting destructor, so `this` is the first arg. */
typedef void *(*LayerNodeDeleteFn)(void *self,int flags);


void FUN_00401a70(undefined4 *param_1)

{
  int *piVar1;
  int *piVar2;
  undefined4 *puVar3;
  void *_Memory;
  undefined4 *puVar4;
  int iVar5;
  
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00537922) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  *param_1 = &PTR_FUN_00551cf0;
  param_1[2] = &PTR_LAB_00551cb8;
  puVar4 = param_1 + 0x56b;
  iVar5 = 0x80;
  do {
    if ((void *)*puVar4 != (void *)0x0) {
      _free((void *)*puVar4);
    }
    puVar4 = puVar4 + 1;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  if ((int *)param_1[0x6f7] != (int *)0x0) {
    (**(code **)(*(int *)param_1[0x6f7] + 4))();
  }
  param_1[0x6f7] = 0;
  HashMap_RemoveAll_2c((int *)(param_1 + 0x6ff));
  piVar2 = (int *)param_1[0x6f9];
  if (piVar2 != (int *)param_1[0x6fe]) {
    RBTree_EraseSubtree(piVar2[0x42]);
    RBTree_EraseSubtree(piVar2[0x43]);
    puVar4 = (undefined4 *)(*piVar2 + -0x10);
    piVar1 = (int *)(*piVar2 + -4);
    LOCK();
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 == 1 || iVar5 + -1 < 0) {
      (**(code **)(*(int *)*puVar4 + 4))(puVar4);
    }
    piVar2[0x42] = param_1[0x6fb];
    param_1[0x6fb] = piVar2;
    param_1[0x6fa] = param_1[0x6fa] + -1;
  }
  param_1[0x6fa] = 0;
  puVar4 = (undefined4 *)param_1[0x6fc];
  while (puVar4 != (undefined4 *)0x0) {
    puVar3 = (undefined4 *)*puVar4;
    _free(puVar4);
    puVar4 = puVar3;
  }
  _Memory = (void *)param_1[0x6fe];
  param_1[0x6fc] = 0;
  param_1[0x6fb] = 0;
  param_1[0x6f9] = _Memory;
  if (_Memory != (void *)0x0) {
    _free(_Memory);
  }
  *param_1 = &PTR_FUN_00557534;
  FUN_004f3060(param_1);
  if ((undefined4 *)param_1[1] != (undefined4 *)0x0) {
    (*(LayerNodeDeleteFn *)*(undefined4 **)param_1[1])((void *)param_1[1],1);
  }
  return;
}

