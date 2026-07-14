/* SyncActiveTextInput - 0x0040cf00 in the original binary.
 *
 * PROMOTED (2026-07-14): the per-frame chat/text-input sync pass. `param_1`
 * is the second active-object registry (&DAT_00e9c0fc); its +8 slot holds the
 * currently-focused text-input object (0 when none - the same value ChangeGameState
 * zeroes and State09_ReadyRoom tracks via the separately-declared DAT_00e9c104).
 * When an input object is focused, this copies the live text out of the Win32
 * edit control (DAT_007934e4: the CreateWindowExA edit box built by
 * FUN_0040c670, HWND at +4, active-flag at +8) into that object's +0x48 text
 * buffer via GetWindowTextA; if the edit control is inactive or the read
 * returns nothing, it clears the buffer instead.
 *
 * DROPPED-ARGUMENT FIX: Ghidra typed the function void and read the registry
 * base as unaff_EAX (`in_EAX`), so the raw port dereferenced a garbage EAX at
 * `*(int *)(in_EAX + 8)`. When that garbage happened to be non-zero it fell
 * through to `*(char *)(DAT_007934e4 + 8)` - and DAT_007934e4 is NULL on the
 * bring-up path - faulting at 0x0040cf10. Recovered from GameTick's sole call
 * site (orig 0x4132ae: `mov eax, 0xe9c0fc` immediately before `call 0x40cf00`
 * at 0x4132b3). With the real argument, registry+8 reads the (zeroed) focus
 * slot, the whole body short-circuits, and DAT_007934e4 is never touched.
 *
 * KNOWN DIVERGENCE (pre-existing, out of scope for bring-up, same class as
 * the DAT_00e9c104 note in globals.c): DAT_007934e4 is read but never written
 * anywhere in .text - the real binary constructs the edit-control block via a
 * path (FUN_0040c670, whose own struct pointer arrives in a dropped ESI) that
 * is not yet reconstructed. Harmless while no text-input object is ever
 * focused (registry+8 stays 0); would need FUN_0040c670/InitGame wired up
 * before real chat input works.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-
 * verified. See src/README.md's "Raw/verbatim ports" section for status.
 */
#include "ghidra_types.h"
#include <windows.h>


void SyncActiveTextInput(int param_1)

{
  LPSTR lpString;
  int iVar1;

  if ((*(int *)(param_1 + 8) != 0) &&
     ((lpString = (LPSTR)(*(int *)(param_1 + 8) + 0x48), *(char *)(DAT_007934e4 + 8) == '\0' ||
      (iVar1 = GetWindowTextA(*(HWND *)(DAT_007934e4 + 4),lpString,0x80), iVar1 == 0)))) {
    *lpString = '\0';
  }
  return;
}
