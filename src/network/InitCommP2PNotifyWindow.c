/* InitCommP2PNotifyWindow - 0x004fdf00 in the original binary.
 *
 * Constructs the CCommP2P sub-object: stamps its vtable, zeroes the
 * peer/socket fields, starts Winsock and creates the hidden STATIC
 * "CCommP2P Notify Window" whose WndProc (0x4fecb0, installed via
 * SetWindowLongA GWL_WNDPROC) receives the async socket notifications.
 * The object pointer is stashed in GWL_USERDATA so that WndProc can
 * find it.
 *
 * RECOVERED (2026-07-19), verified with angr/capstone against the
 * original: the object pointer arrives in EDI. It is read before any
 * write - the third instruction of the function is
 *   0x4fdf08  mov dword ptr [edi], 0x557654    ; = &PTR_LAB_00557654
 * followed by 0x4fdf10 `lea esi,[edi+0x210]` and 0x4fdf16
 * `mov byte ptr [edi+0x20c], bl`, all before EDI is ever assigned.
 * Ghidra emitted it as an uninitialised `unaff_EDI`, so the port wrote
 * the vtable and the created HWND through a garbage pointer.
 * Promoted to the trailing `self` parameter (the repo's established
 * idiom - see src/network/AllocCipherSchedule.c).
 *
 * The sole call site is the CCommP2P owner's constructor at 0x4fd0f0
 * (ported as FUN_004fd0f0), which sets up EDI immediately before the
 * call:
 *   0x4fd107  mov ebp, dword ptr [esp + 0x18]   ; = param_1, the owner
 *   0x4fd11c  lea edi, [ebp + 0x2c]             ; the CCommP2P sub-object
 *   0x4fd11f  call 0x4fdf00
 * i.e. the sub-object lives at owner+0x2c == &param_1[0xb], which is
 * consistent with that constructor's own `param_1[0xb] =
 * &PTR_LAB_005575ac` vtable store just after the call.
 */
#include "ghidra_types.h"
#include <windows.h>


void InitCommP2PNotifyWindow(undefined4 *self)

{
  HWND hWnd;
  undefined4 *unaff_EDI;
  WSADATA local_190;

  unaff_EDI = self;
  *unaff_EDI = &PTR_LAB_00557654;
  *(undefined1 *)(unaff_EDI + 0x83) = 0;
  FUN_00504c10();
  unaff_EDI[0xa0] = 0;
  unaff_EDI[0xa1] = 0;
  unaff_EDI[0xa2] = 0xffffffff;
  unaff_EDI[0xa3] = 0;
  FUN_004fe420(0x3f400000,0x3e800000,0x40100000);
  unaff_EDI[0xb0] = 0;
  unaff_EDI[0xb1] = 0;
  WSAStartup(0x202,&local_190);
  hWnd = CreateWindowExA(0,s_STATIC_00557b50,s_CCommP2P_Notify_Window_00557b34,0x80000000,0,0,0,0,
                         (HWND)0x0,(HMENU)0x0,(HINSTANCE)0x0,(LPVOID)0x0);
  unaff_EDI[0xa3] = hWnd;
  if (hWnd != (HWND)0x0) {
    SetWindowLongA(hWnd,-0x15,(LONG)unaff_EDI);
    /* FIXED (2026-07-20): was the literal original-binary address 0x4fecb0,
     * which is meaningless in our relinked image - user32 jumped into
     * whatever the linker placed there (observed as an access violation at
     * eip=0x0000000e on the audio/message thread). Use the real symbol. */
    SetWindowLongA((HWND)unaff_EDI[0xa3],-4,(LONG)FUN_004fecb0);
  }
  return;
}

