/* State01_Title_OnExit - 0x004e53b0 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>


/* TWO bugs in the list-walk below, found together (2026-07-14, see
 * sibling State06_Logo2_OnExit.c for the full writeup):
 *
 * (1) The vtable call dropped the node/this pointer entirely. Ghidra
 * emitted (*(code *)*puVar3)(1), a plain-cdecl call that only pushes the
 * literal 1 and never passes puVar3 - dropping the object pointer
 * entirely. Disassembly at 0x4e53e0-0x4e53e7 confirms the real call:
 *   mov edx,[ecx]      ; edx = vtable ptr (ecx = the node/this)
 *   mov edi,[ecx+0x10]
 *   push 0x1
 *   call [edx]
 * matching this codebase's established __fastcall-with-thisPtr idiom
 * for these implicit-this virtual calls (see ChangeGameState.c's
 * GameStateVirtualFn / GameTick.c's GameStateVirtualFn3).
 *
 * (2) This file's OWN earlier fix (still) used `puVar3 = *puVar2`,
 * reading puVar2's vtable-pointer VALUE instead of using puVar2 (the
 * real node) as `this` - the disassembly says `ecx = the node`, not
 * `ecx = the node's vtable value`. Live-confirmed: without this fix,
 * the "destructor" (FUN_004f14c0, which does `_free(this)`) frees the
 * ADDRESS OF A GLOBAL (e.g. &PTR_FUN_00557524 - see LoadSpriteSet.c)
 * instead of the real heap node - undefined behavior that corrupts the
 * heap allocator's internal state, surfacing later as garbage
 * code-segment pointers in unrelated heap reads. */
typedef void (__fastcall *ListNodeVirtualFn)(void *thisPtr, undefined4 a1);

void State01_Title_OnExit(void)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;

  puVar4 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar1 = puVar4[1];
  if (uVar1 < 0x2711) {
    while (uVar1 != 10000) {
      puVar4 = (undefined4 *)puVar4[7];
      uVar1 = puVar4[1];
      if (10000 < uVar1) {
        return;
      }
    }
    puVar2 = (undefined4 *)puVar4[4];
    while (puVar2 != puVar4) {
      puVar3 = puVar2;
      puVar2 = (undefined4 *)puVar2[4];
      (*(ListNodeVirtualFn *)*puVar3)(puVar3, 1);
    }
    puVar4[3] = puVar4;
    puVar4[4] = puVar4;
  }
  return;
}

