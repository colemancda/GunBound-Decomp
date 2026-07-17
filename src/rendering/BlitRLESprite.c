/* BlitRLESprite - 0x004eb450 in the original binary.
 *
 * DROPPED REGISTER ARGUMENT: Ghidra read the RLE glyph-stream pointer as
 * `in_EAX` - an uninitialized local - instead of resolving it as a real
 * parameter. Confirmed via objdump at two real call sites inside
 * State03_GameRoomList_RenderRoomLabel (0x429937 and 0x429957), e.g.:
 *   push 0xfd0f            ; -> stack arg (param_3, color)
 *   push 0x9                ; -> stack arg (param_2)
 *   lea  eax,[esp+0x30]    ; EAX = &local sprintf'd string buffer  <-- dropped
 *   mov  ecx,0xbe           ; ECX -> param_1 (this file's own body already
 *                           ;   uses param_1 as the advancing x-cursor)
 *   call BlitRLESprite
 * Only the EAX-borne string/glyph-stream pointer is in this fix's scope:
 * param_1/param_2/param_3 already round-trip through Ghidra's existing
 * parameter list and this file's body already consumes them exactly as
 * declared, so they're left untouched. (Whether the *callers'* 2-argument
 * call-site text is itself also silently dropping param_1/ECX is a
 * separate, pre-existing question about those caller files, out of scope
 * here - not touched, and not worsened: this fix only appends a new
 * trailing argument, it doesn't reinterpret the existing two.) This EAX
 * drop matches the sibling function DrawFontString (0x4eb510, identical
 * in_EAX bug, identical call shape) and is corroborated by every raw
 * caller: a string pointer is computed (via `_sprintf`+scan-to-nul, or a
 * plain field pointer) immediately before the call and re-read
 * immediately after (a `do { c = *p; p++; } while (c != 0)` strlen loop),
 * with nothing in between that could clobber EAX - so it was genuinely
 * loaded right before this call, not surviving from an earlier one.
 * Promoted to a real 4th parameter (`rleData`).
 *
 * Scope note: BlitRLESprite has ~119 call sites across ~32 raw/
 * unverified files under src/ (none of which link yet - see below), each
 * carrying its own dropped EAX value. The two call sites analyzed above
 * (State03_GameRoomList_RenderRoomLabel.c, 0x429937/0x429957) have been
 * fixed as part of this pass, passing the pointer that's already visible
 * in that file's own source (the `_sprintf`'d local buffer, and the
 * g_clientContext+0x23330 server-name field respectively). The remaining
 * call sites still pass only (x, color) and need the same per-site
 * objdump recovery before they'll compile against this signature - most
 * expose the missing pointer as an adjacent local (the same one a
 * following `do { c = *p; p++; } while (c != 0)` strlen loop walks, or
 * DrawFontString's own just-loaded argument), but at least one traced
 * example (RenderReadyRoomChatRow.c's `else` branch, 0x50d445-0x50d471)
 * shows the DrawFontString and BlitRLESprite calls in the same statement
 * pair reading *different* stack-spilled pointers, so this cannot be
 * done safely by pattern-matching alone - each site needs its own
 * disassembly check. Calls to unnamed FUN_<address> helpers and
 * DAT_<address>/_DAT_<address> globals are left as-is (undeclared) -
 * this file won't link standalone yet. See src/README.md's "Raw/
 * verbatim ports" section for status and how these get promoted to
 * verified.
 */
#include "ghidra_types.h"
#include <windows.h>


undefined4 __thiscall BlitRLESprite(int param_1,undefined4 param_2,undefined4 param_3,
                                     byte *rleData)

{
  byte bVar1;
  byte bVar2;
  byte *in_EAX = rleData;
  int iVar3;
  byte *pbVar4;
  int local_4;

  bVar1 = *in_EAX;
  if (bVar1 != 0) {
    local_4 = param_1 + 6;
    iVar3 = param_1 + 0xc;
    do {
      pbVar4 = in_EAX + 1;
      if ((char)bVar1 < '\0') {
        bVar2 = *pbVar4;
        pbVar4 = in_EAX + 2;
        if (DAT_00793530 <= iVar3) {
          FUN_004eaeb0(param_1,param_3,&DAT_005b3628 + ((bVar1 & 0x7f) << 8 | (uint)bVar2) * 0x18);
        }
        param_1 = param_1 + 0xc;
        iVar3 = iVar3 + 0xc;
        local_4 = local_4 + 0xc;
      }
      else {
        if ((bVar1 != 0x20) && (DAT_00793530 <= local_4)) {
          BlitFontGlyphClipped(param_1,param_3);
        }
        param_1 = param_1 + 6;
        iVar3 = iVar3 + 6;
        local_4 = local_4 + 6;
      }
    } while ((param_1 <= DAT_0056df30) && (bVar1 = *pbVar4, in_EAX = pbVar4, bVar1 != 0));
  }
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

