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


/* The list-walk below calls each node's vtable slot 0 with the node
 * itself as `this` and a literal 1 as a second argument. Ghidra emitted
 * this as (*(code *)*puVar3)(1), a plain-cdecl call that only pushes the
 * literal 1 and never passes puVar3 - dropping the object pointer
 * entirely. Disassembly at 0x4e53e0-0x4e53e7 confirms the real call:
 *   mov edx,[ecx]      ; edx = vtable ptr (ecx = puVar3, the node/this)
 *   mov edi,[ecx+0x10]
 *   push 0x1
 *   call [edx]
 * ecx (puVar3) is left untouched to serve as `this`, matching this
 * codebase's established __fastcall-with-thisPtr idiom for these
 * implicit-this virtual calls (see ChangeGameState.c's
 * GameStateVirtualFn / GameTick.c's GameStateVirtualFn3). */
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
      puVar3 = (undefined4 *)*puVar2;
      puVar2 = (undefined4 *)puVar2[4];
      (*(ListNodeVirtualFn *)*puVar3)(puVar3, 1);
    }
    puVar4[3] = puVar4;
    puVar4[4] = puVar4;
  }
  return;
}

