/* FUN_00504550 - 0x00504550 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-ARGUMENT FIX (2026-09-20). Element-wise array-copy helper for a
 * container of 0x12-byte (18-byte) elements (element layout: a length byte
 * at +0x11, up to 0x11 payload bytes copied then NUL-padded - a short
 * inline string/name slot). include/functions.h had only an empty-paren
 * `undefined4 __fastcall FUN_00504550();` prototype (no param list), so
 * every call in the tree compiled without argument-count checking and
 * silently dropped arguments.
 *
 * TRUE ABI, from disassembling the entry (0x504550: `cmp edx,[esp+4]`,
 * i.e. EDX is read as a register BEFORE any push - a genuine incoming
 * arg) and the body:
 *   - ECX (param_1) is __fastcall's first register slot but is NEVER
 *     read anywhere in the body - dead/"this"-shaped but unused. Kept
 *     as a formal parameter for ABI shape; callers may pass 0.
 *   - EDX (param_2) = the copy-loop's cursor/"begin" pointer.
 *   - ONE stack dword (param_3) = the loop bound/"end" pointer - read at
 *     entry as [esp+4] and reloaded every iteration at [esp+0x14]
 *     (same slot, offset by the four pushed registers).
 *   - EAX arrives as a THIRD, undocumented incoming register (Ghidra
 *     modelled it as a bare local `in_EAX`, not a formal parameter) =
 *     the copy-loop's "dest" pointer. This is the same "EAX-first
 *     convention Ghidra mislabels as __fastcall" class documented in
 *     MEMORY.md's fastcall-decls-missing-from-functions-h note; fixed
 *     the same way, by promoting `in_EAX` to a trailing formal
 *     parameter (param_4) and giving it a real functions.h prototype
 *     (this changes the physical calling convention from the original
 *     binary's raw EAX-register hand-off to a normal trailing arg, same
 *     tradeoff as every prior instance of this fix in this tree).
 *   - The `ret` at 0x504597 pops 0 bytes (bare `ret`), i.e. the ONE real
 *     stack argument is caller-cleaned - callers batch its cleanup
 *     together with an adjacent cdecl call's `add esp,N` rather than the
 *     callee popping it, consistent with only one stack arg existing.
 *   - Every caller in FUN_00502b70 (the only call site, 4 static call
 *     instructions at 0x502ca0/0x502cd0/0x502d7a/0x502dd6) additionally
 *     pushes a SECOND stack dword that the callee's body never reads
 *     (confirmed: only one stack load exists in the whole function) -
 *     that extra push is caller-side dead weight from the original
 *     compiler, not a real parameter, and is dropped in the ported call
 *     sites.
 *   - The function's true return value is the final `param_4` (dest)
 *     after the copy loop - on the original hardware this just falls
 *     out of EAX naturally (EAX is incremented in-place by the loop and
 *     never overwritten again before `ret`). The prior raw port had
 *     `return 0;` (with a comment about Ghidra emitting a bare
 *     `return;`), which was actually WRONG: one caller
 *     (FUN_00502b70 @0x502cd0, the second call) uses the first call's
 *     return value (stored at [ebp+0x10] across the intervening
 *     FUN_00504110 call) as the base of its own `dest` argument, and a
 *     second caller (@0x502dd6) captures the return into `uVar5` and
 *     writes it back into the container's end-of-storage field. Fixed
 *     to `return param_4;`.
 * See src/unnamed/FUN_00502b70.c for the 4 reconstructed call sites.
 */
#include "ghidra_types.h"


undefined4 __fastcall
FUN_00504550(undefined4 param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4)

{
  byte bVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;

  for (; param_2 != param_3; param_2 = (undefined4 *)((int)param_2 + 0x12)) {
    if (param_4 != (undefined4 *)0x0) {
      bVar1 = *(byte *)((int)param_2 + 0x11);
      *(byte *)((int)param_4 + 0x11) = bVar1;
      puVar3 = param_2;
      puVar4 = param_4;
      for (uVar2 = (uint)(bVar1 >> 2); uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
      for (uVar2 = bVar1 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *(undefined1 *)puVar4 = *(undefined1 *)puVar3;
        puVar3 = (undefined4 *)((int)puVar3 + 1);
        puVar4 = (undefined4 *)((int)puVar4 + 1);
      }
      *(undefined1 *)((uint)bVar1 + (int)param_4) = 0;
    }
    param_4 = (undefined4 *)((int)param_4 + 0x12);
  }
  return (undefined4)param_4;
}
