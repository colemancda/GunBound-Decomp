/* RegisterActiveObject - 0x004f2fb0 in the original binary.
 *
 * DROPPED REGISTER ARGUMENT (unaff_EDI): Ghidra's raw output read the
 * to-be-registered node/object pointer as `unaff_EDI` - an uninitialized
 * local - instead of resolving it to a real parameter, silently dropping
 * it at every call site. Confirmed via
 *   objdump -d -Mintel --start-address=0x4f2fb0 --stop-address=0x4f3010 \
 *     orig/GunBound.gme
 * The callee never sets up EDI itself (no push/pop edi anywhere in the
 * body), and every caller loads it immediately before the `call
 * 0x4f2fb0`:
 *   - 0x401e1b: `mov edi,eax` / `mov edx,ebp`      (edi = freshly built node)
 *   - 0x40610c: edi already holds the caller's `this` / `mov edx,[esp+8]`
 *   - 0x42baa8: `mov edx,[0x5b3484]+0x6a7f88` (global ctx) / `mov edi,ebp`
 *   - 0x4f1878 (inside LoadSpriteSet, 0x4f1790): `mov edx,[esp+0x20]`
 *     (LoadSpriteSet's own forwarded param_2) / `mov edi,esi` where esi
 *     is the sprite object just built - i.e. this function's node arg.
 * In every case EDX is the container/context (this file's existing
 * `param_2`) and EDI is a distinct third value - the node being linked
 * into the sorted list. Promoted here to a real `node` parameter; ECX
 * (`param_1`) is never touched by any caller and stays a true dead/
 * unused argument, matching the original ABI slot.
 *
 * Only src/rendering/LoadSpriteSet.c's call site is fixed to the new
 * 3-arg form here (its own original address confirmed the exact
 * registers above). The ~70 other `RegisterActiveObject();` call sites
 * across src/unnamed/*.c and src/cxx/ButtonWidget.cpp are each inside a
 * different unverified/raw-ported function with its own distinct
 * call-site registers (per-function EDX/EDI contents aren't recoverable
 * from this file alone) - those still use the old argless form and need
 * the same per-site disassembly treatment, same as FUN_004f2da0's call
 * sites were split across commits.
 *
 * CALLING-CONVENTION CAST MISMATCH: the duplicate-node early-out at
 * 0x4f300a is a scalar-deleting-destructor-shaped vtable call -
 * `mov ecx,edi` / `push 1` / `call [edx]` - i.e. __thiscall (this in
 * ECX, the free-flag pushed on the stack), the same shape already fixed
 * in LoadSpriteSet.c's `ScalarDeletingDtorFn`. The raw `(**(code
 * **)*node)(1)` cdecl-cast would instead push `node` on the stack
 * alongside the `1`, corrupting the call; fixed with an explicit
 * __thiscall typedef through the same idiom.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output otherwise - not
 * hand-verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>

typedef void *(__thiscall *ScalarDeletingDtorFn)(void *thisPtr,int freeFlag);

undefined4 __fastcall RegisterActiveObject(undefined4 param_1,int param_2,undefined4 *node)

{
  uint uVar1;
  int iVar2;
  uint uVar3;

  iVar2 = *(int *)(*(int *)(param_2 + 4) + 0x1c);
  uVar1 = *(uint *)(iVar2 + 4);
  while (uVar1 <= (uint)node[1]) {
    if (uVar1 == node[1]) goto LAB_004f2fd3;
    iVar2 = *(int *)(iVar2 + 0x1c);
    uVar1 = *(uint *)(iVar2 + 4);
  }
  iVar2 = FUN_004f2f00(param_2);
LAB_004f2fd3:
  uVar1 = node[2];
  if (uVar1 != 0xffffffff) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar3 = *(uint *)(iVar2 + 8);
    if (uVar3 <= uVar1) {
      do {
        if (uVar3 == uVar1) {
          (*(ScalarDeletingDtorFn *)*node)(node,1);
          return 0;
        }
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar3 = *(uint *)(iVar2 + 8);
      } while (uVar3 <= (uint)node[2]);
    }
  }
  node[4] = iVar2;
  node[3] = *(undefined4 *)(iVar2 + 0xc);
  *(undefined4 **)(*(int *)(iVar2 + 0xc) + 0x10) = node;
  *(undefined4 **)(iVar2 + 0xc) = node;
  return 1;
}

