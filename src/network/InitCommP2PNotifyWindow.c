/* InitCommP2PNotifyWindow - 0x004fdf00 in the original binary.
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


void InitCommP2PNotifyWindow(void)

{
  HWND hWnd;
  undefined4 *unaff_EDI;
  WSADATA local_190;
  
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
    SetWindowLongA((HWND)unaff_EDI[0xa3],-4,0x4fecb0);
  }
  return;
}

