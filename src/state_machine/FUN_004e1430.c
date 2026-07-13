/* FUN_004e1430 - 0x004e1430 in the original binary.
 *
 * State02_ServerSelect vtable slot 6 - keydown handler. On Enter
 * (param_2==0x100, param_3==0xd/VK_RETURN): if nothing is highlighted yet,
 * auto-selects the first online server slot; then, same validation as
 * FUN_004e1170's connect path (online, SERVER button enabled, slot not
 * full), calls ConnectToSelectedServer. No confirmed real name/purpose
 * beyond that. Raw/near-verbatim port of Ghidra's decompiler output, not
 * hand-verified. See src/README.md's "Raw/verbatim ports" section for
 * status.
 *
 * ConnectToSelectedServer takes an explicit `serverIndex` 2nd parameter
 * (see that file's own header - a dropped-register-argument fix from
 * earlier this session); passes the highlighted slot (`iVar2`) here.
 *
 * FIXED (2026-07-13): `RET 0xc` at 0x4e1430 (3 stack dwords beyond
 * `this`, confirmed via objdump) but Ghidra's decompile only showed 2
 * (`param_2`, `param_3` - the WM_KEYDOWN message and VK code). This is
 * WndProc's slot-6 keydown dispatch, called as (this, msg, wParam,
 * lParam) - `lParam` is pushed/popped by every caller but genuinely
 * never read here. Added as `param_4` (unused) so the generated `ret N`
 * matches what WndProc actually pushes (see WndProc.c's own header for
 * the matching fix at that call site).
 */
#include "ghidra_types.h"


void __thiscall FUN_004e1430(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;

  iVar1 = g_clientContext;
  if ((param_2 == 0x100) && (param_3 == 0xd)) {
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
