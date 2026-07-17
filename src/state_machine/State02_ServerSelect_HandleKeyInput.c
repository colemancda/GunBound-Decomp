/* State02_ServerSelect_HandleKeyInput - 0x004e1430 in the original binary.
 *
 * State02_ServerSelect vtable slot 6 - keydown handler. On Enter
 * (param_2==0x100, param_3==0xd/VK_RETURN): if nothing is highlighted yet,
 * auto-selects the first online server slot; then, same validation as
 * State02_ServerSelect_OnCommand's connect path (online, SERVER button enabled, slot not
 * full), calls ConnectToSelectedServer. No confirmed real name/purpose
 * beyond that. Raw/near-verbatim port of Ghidra's decompiler output, not
 * hand-verified. See src/README.md's "Raw/verbatim ports" section for
 * status.
 *
 * ConnectToSelectedServer takes an explicit `serverIndex` 2nd parameter
 * (see that file's own header - a dropped-register-argument fix from
 * earlier this session); passes the highlighted slot (`iVar2`) here.
 *
 * CALLING-CONVENTION FIX (2026-07-17): WndProc dispatches this vtable
 * slot 6 via StateSlot6DispatchFn, a __fastcall(this, dummyEDX, msg,
 * wParam, lParam) - `this` in ECX, a dead EDX slot, then the three
 * message dwords on the stack, callee-cleaned (`ret 0xc`). This port was
 * declared __thiscall, which ghidra_types.h erases to plain cdecl under
 * MSVC (`this` read off the stack, caller-cleaned, `ret 0`) - the wrong
 * convention AND the wrong cleanup. The result was a live crash: a
 * keypress at ServerSelect dispatched here with `this`=msg (0x100) and a
 * 0xc-byte stack-cleanup mismatch that smashed EBP/the return address
 * and jumped to garbage (EIP landed on the stack, frame 0x3f3f3f3f).
 * Declared __fastcall + dummy-EDX to match, exactly like the working
 * State01_Title_HandleKeyInput / State06_Logo2_HandleKeyInput. The
 * original's `ret 0xc` now matches (3 stack args, callee-cleaned).
 */
#include "ghidra_types.h"


void __fastcall State02_ServerSelect_HandleKeyInput(int param_1,int dummyEDX,uint msg,uint wParam,
                                                    uint lParam)

{
  int iVar1;
  int iVar2;

  (void)dummyEDX;
  (void)lParam;
  iVar1 = g_clientContext;
  if ((msg == 0x100) && (wParam == 0xd)) {
    if ((*(int *)(param_1 + 8) == -1) && (DAT_007933b8 == '\x01')) {
      iVar2 = 0;
      do {
        if (*(char *)(g_clientContext + 0x3f809 + iVar2) != '\0') {
          *(int *)(param_1 + 8) = iVar2;
          break;
        }
        iVar2 = iVar2 + 1;
      } while (iVar2 < 0x10);
    }
    iVar2 = *(int *)(param_1 + 8);
    if ((((iVar2 != -1) && (DAT_00e55a46 == '\0')) && (*(char *)(param_1 + 0x24) != '\0')) &&
       (*(ushort *)(iVar1 + 0x410ca + iVar2 * 2) <= *(ushort *)(iVar1 + 0x410ea + iVar2 * 2))) {
      ConnectToSelectedServer(param_1,iVar2);
      *(undefined1 *)(param_1 + 6) = 0;
    }
  }
  return;
}
