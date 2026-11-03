/* FUN_004f2ea0 - 0x004f2ea0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIX (2026-11-03): sentinel delete passes `this`. 0x4f2eaf-0x4f2eba is
 * `mov ecx,[esi+4] / mov eax,[ecx] / push 1 / call [eax]`, so ECX is the
 * sentinel layer node ActiveObjectRegistry_BaseConstructor (0x4f2e40)
 * hangs at +4, stamped with the layer vtable 0x557530 at 0x4f2e68. That
 * vtable's only slot is 0x4f2e20 (FUN_004f2e20, `mov esi,ecx` ... `ret
 * 4`), a raw-C port of a __thiscall scalar-deleting destructor, so `this`
 * is its first cdecl argument. The port called `(*(code *)slot0)(1)`,
 * dropping the node; it now passes (node, 1) through LayerNodeDeleteFn.
 */
#include "ghidra_types.h"

/* Slot 0 of the layer-node vtable 0x557530: FUN_004f2e20, a raw-C port of
 * a __thiscall scalar-deleting destructor, so `this` is the first arg. */
typedef void *(*LayerNodeDeleteFn)(void *self,int flags);


undefined4 * __thiscall FUN_004f2ea0(undefined4 *param_1,int param_2)

{
  *param_1 = &PTR_FUN_00557534;
  FUN_004f3060(param_1);
  if ((undefined4 *)param_1[1] != (undefined4 *)0x0) {
    (*(LayerNodeDeleteFn *)*(undefined4 **)param_1[1])((void *)param_1[1],1);
  }
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

