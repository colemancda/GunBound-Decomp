/* CreateCommEngineNotifyWindow - 0x004fdc80 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_004fdc80).  One CreateWindowExA call making a
 * hidden "STATIC" window titled "CCommEngine_Notify_Window" - the message-only
 * window the comm engine uses as its notification sink (the usual WSAAsyncSelect
 * pattern).  109 bytes, one caller.
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


void CreateCommEngineNotifyWindow(undefined4 *regEsi)

{
  HWND hWnd;
  
  *regEsi = &PTR_LAB_00557598;
  regEsi[1] = 0;
  regEsi[2] = 0;
  regEsi[3] = 0;
  regEsi[4] = 0;
  regEsi[5] = 0;
  regEsi[6] = 10;
  regEsi[7] = 0xffffffff;
  *(undefined1 *)(regEsi + 9) = 0;
  hWnd = CreateWindowExA(0,s_STATIC_00557b50,s_CCommEngine_Notify_Window_00557b58,0x80000000,0,0,0,0
                         ,(HWND)0x0,(HMENU)0x0,(HINSTANCE)0x0,(LPVOID)0x0);
  regEsi[8] = hWnd;
  if (hWnd != (HWND)0x0) {
    SetWindowLongA(hWnd,-0x15,(LONG)regEsi);
    SetWindowLongA((HWND)regEsi[8],-4,(LONG)CommEngineNotifyWndProc);
  }
  return;
}

