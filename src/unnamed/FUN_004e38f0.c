/* FUN_004e38f0 - 0x004e38f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIX (2026-11-03): the +0x85c registry's sentinel delete passes `this`.
 * 0x4e3987-0x4e3992 is `mov ecx,[esi+4] / mov edx,[ecx] / push 1 / call
 * [edx]` (ESI = this+0x85c), so ECX is the sentinel layer node
 * ActiveObjectRegistry_BaseConstructor (0x4f2e40) hangs at +4, stamped
 * with the layer vtable 0x557530 at 0x4f2e68. That vtable's only slot is
 * 0x4f2e20 (FUN_004f2e20, `mov esi,ecx` ... `ret 4`), a raw-C port of a
 * __thiscall scalar-deleting destructor, so `this` is its first cdecl
 * argument. The port called `(*(code *)slot0)(1)`, dropping the node; it
 * now passes (node, 1) through LayerNodeDeleteFn. The +0x30 member delete
 * at 0x4e3911-0x4e391c drops `this` the same way, but its class is not
 * identified, so it is left alone.
  *
 * FIX (2026-11-03, second pass): the +0x30 member delete is now resolved.
 * The member is the 0x308-byte object FUN_004e3810 allocates and stamps
 * with vtable 0x557300 (`mov [edx],0x557300` at 0x4e3879; stored to
 * [edi+0x30] at 0x4e38d6), whose slot 0 (.data 0x557300) is 0x4e9b80, the
 * scalar deleting destructor (`mov esi,ecx`, `test byte [esp+8],1`, `ret 4`),
 * a raw-C port. 0x4e3911-0x4e391c is `mov ecx,[esi+0x30] / mov eax,[ecx] /
 * push 1 / call [eax]`, so it is (member, 1) through the same cdecl
 * LayerNodeDeleteFn form. PTR_FUN_00557300 had been a NULL placeholder; its
 * slot 0 is now wired.
 */
#include "ghidra_types.h"

/* Slot 0 of the layer-node vtable 0x557530: FUN_004f2e20, a raw-C port of
 * a __thiscall scalar-deleting destructor, so `this` is the first arg. */
typedef void *(*LayerNodeDeleteFn)(void *self,int flags);


void FUN_004e38f0(int param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  uStack_c = *unaff_FS_OFFSET;
  puStack_8 = &LAB_0053776e;
  *unaff_FS_OFFSET = &uStack_c;
  local_4 = 0;
  if (*(undefined4 **)(param_1 + 0x30) != (undefined4 *)0x0) {
    (*(LayerNodeDeleteFn *)**(undefined4 **)(param_1 + 0x30))
        (*(void **)(param_1 + 0x30),1);
    *(undefined4 *)(param_1 + 0x30) = 0;
  }
  if (*(void **)(param_1 + 0x34) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x34));
    *(undefined4 *)(param_1 + 0x34) = 0;
  }
  if (*(void **)(param_1 + 0x38) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x38));
    *(undefined4 *)(param_1 + 0x38) = 0;
  }
  if (*(void **)(param_1 + 0x3c) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x3c));
    *(undefined4 *)(param_1 + 0x3c) = 0;
  }
  if (*(void **)(param_1 + 0x44) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x44));
    *(undefined4 *)(param_1 + 0x44) = 0;
  }
  local_4 = 0xffffffff;
  *(undefined4 *)(param_1 + 0x85c) = &PTR_FUN_00557534;
  FUN_004f3060((undefined4 *)(param_1 + 0x85c));
  if (*(undefined4 **)(param_1 + 0x860) != (undefined4 *)0x0) {
    (*(LayerNodeDeleteFn *)**(undefined4 **)(param_1 + 0x860))
        (*(void **)(param_1 + 0x860),1);
  }
  *unaff_FS_OFFSET = uStack_c;
  return;
}

