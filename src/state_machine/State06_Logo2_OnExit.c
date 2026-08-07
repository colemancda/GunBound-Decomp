/* State06_Logo2_OnExit - 0x004432c0 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 *
 * FIXED (2026-07-14), TWO bugs in the list-walk below, found together:
 *
 * (1) The vtable call dropped the node/this pointer entirely. Ghidra
 * emitted `(*(code *)*puVar3)(1)`, a plain-cdecl call that only pushes
 * the literal 1 and never passes puVar3. Disassembly at 0x4432f0-0x4432f7
 * confirms the real call:
 *   mov edx,[ecx]      ; edx = vtable ptr (ecx = the node/this)
 *   mov edi,[ecx+0x10]
 *   push 0x1
 *   call [edx]
 * matching this codebase's established __fastcall-with-thisPtr idiom
 * for these implicit-this virtual calls (see ChangeGameState.c's
 * GameStateVirtualFn / GameTick.c's GameStateVirtualFn3).
 *
 * (2) A SEPARATE, more subtle bug in what gets used as `this`: the
 * decompiled `puVar3 = *puVar2;` reads puVar2's own vtable-pointer
 * VALUE (e.g. `&PTR_FUN_00557524`, a GLOBAL slot - see LoadSpriteSet.c)
 * instead of using puVar2 (the real node) itself. The disassembly
 * above says `ecx = the node`, not `ecx = the node's vtable value` -
 * `this` must be the node (puVar2), with `*puVar2` used only to fetch
 * the vtable pointer for the CALL, not reassigned into what gets
 * passed as `this`. Live-confirmed: without this fix, the "destructor"
 * (FUN_004f14c0, which does `_free(this)`) frees the ADDRESS OF A
 * GLOBAL instead of the real heap node - undefined behavior that
 * corrupts the heap allocator's internal state, surfacing later as
 * garbage code-segment pointers appearing in unrelated heap reads
 * (reached via State01_Title_OnExit, which inherits sprite-set 10000's
 * layer from whatever this function's own corruption left behind).
 * This exact two-bug pattern (dropped-this AND wrong-this-value)
 * likely recurs at the ~150+ other call sites across this codebase
 * using the same `(*(code *)*puVarN)(1)` shape - not audited here.
 *
 * CALLING-CONVENTION FIX (2026-08-06): the `__fastcall(thisPtr, a1)`
 * typedef above was wrong in BOTH directions and crashed live. The
 * ORIGINAL is a plain __thiscall - `this` in ECX and the flag PUSHED
 * (see the 0x4432f0 disassembly quoted above: `push 0x1; call [edx]`) -
 * so a 2-arg __fastcall, which passes the flag in EDX and pushes
 * nothing, does not match the original either. More decisively, it does
 * not match OUR CALLEE: the target here is FUN_004f14c0, a raw C port,
 * and ghidra_types.h erases `__thiscall` to cdecl for those - so the
 * ported destructor reads BOTH `this` and the flag off the stack. With
 * the __fastcall typedef it received neither (ecx/edx ignored, zero
 * stack args) and read whatever the caller's frame happened to hold:
 * live crash, `this` = 1, page fault at [1+0x34] reading 0x35 inside
 * DestroySpriteFrame. Fixed to plain cdecl, matching the project rule that
 * erased-__thiscall = cdecl is correct for raw-C-port callees (the
 * `__fastcall`+dummy-EDX idiom is only for genuine C++ vtable methods,
 * where `this` really does arrive in ECX). Same fix as the sibling
 * State03_GameRoomList_OnExit.c. */
#include "ghidra_types.h"
#include <windows.h>

typedef void (*ListNodeVirtualFn)(void *thisPtr, undefined4 a1);

void State06_Logo2_OnExit(void)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined1 auStack_28 [40];
  /* BuildSystemInfoBlob's 2nd output (orig ESI, dropped) - NOT verified
   * against this call site's original disassembly; added only to satisfy
   * the now-2-parameter signature (see BuildSystemInfoBlob.c). Revisit if
   * this code path is ever exercised. */
  undefined4 systemInfoBlob2[6];

  puVar4 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar1 = puVar4[1];
  if (uVar1 < 0x2711) {
    while (uVar1 != 10000) {
      puVar4 = (undefined4 *)puVar4[7];
      uVar1 = puVar4[1];
      if (10000 < uVar1) {
        BuildSystemInfoBlob(auStack_28, systemInfoBlob2);
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
  BuildSystemInfoBlob(auStack_28, systemInfoBlob2);
  return;
}

