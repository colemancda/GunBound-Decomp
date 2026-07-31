/* FetchActiveTextInputText - 0x0040c880 in the original binary.
 *
 * RENAMED (2026-07-30): given the shared overlay EDIT-control singleton's
 * VALUE (same DAT_007934e4-style pointer CommitActiveTextInput/
 * SyncActiveTextInput read: +0x04 HWND, +0x08 live/visible flag) and a
 * caller-owned destination buffer, pulls the control's current text into
 * the buffer, or clears the buffer's first byte if the control isn't live
 * or the read comes back empty. The read/fetch counterpart of
 * CommitActiveTextInput (which pushes INTO an object's own field and resets
 * the control) - this one just snapshots the control's text OUT into
 * whatever buffer the caller hands it, without touching the control itself.
 *
 * DROPPED-ARGUMENT FIX (2026-07-30): both `unaff_ESI`'s buffer and the
 * struct pointer this function actually only reads via EAX were true
 * arguments Ghidra dropped entirely. Confirmed via objdump (orig
 * 0x40c880-0x40c8a6): `mov cl,[eax+8]` is the very first instruction, EAX
 * live-in with no prior write; `esi` is used as the destination (`push
 * esi` before the GetWindowTextA call, `mov byte ptr [esi],0` on both
 * clear paths) with no prior write either - cdecl, no stack cleanup, two
 * register args. All 4 real call sites (`State09_ReadyRoom_
 * HandleChatInput.c` x2, `State10_Loading_HandleChatInput.c`,
 * `State11_InBattle_HandleMouseInput.c`) load `eax = DAT_007934e4`
 * (confirmed identical at every site via objdump) and `esi = &<local text
 * buffer>` right before the call - promoted to explicit parameters and all
 * 4 sites wired with `DAT_007934e4` and each site's own destination buffer
 * (`acStack_80` in all 4 - State09's second call site's destination isn't
 * re-read until several lines later, but IS re-read there, confirming it's
 * the same local and not a separate/dropped one).
 */
#include "ghidra_types.h"


void FetchActiveTextInputText(int editState,LPSTR dest)

{
  int iVar1;

  if (*(char *)(editState + 8) == '\0') {
    *dest = '\0';
  }
  else {
    iVar1 = GetWindowTextA(*(HWND *)(editState + 4),dest,0x80);
    if (iVar1 == 0) {
      *dest = '\0';
      return;
    }
  }
  return;
}
