/* CommEngineNotifyWndProc - 0x004fe6f0 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_004fe6f0).  The window procedure of the comm
 * engine's message-only window: `LRESULT __stdcall (HWND, UINT, WPARAM, uint)`,
 * installed by CreateCommEngineNotifyWindow with
 * SetWindowLongA(hwnd, GWL_WNDPROC, ...).  It handles exactly one message,
 * 0x478 - the custom notification code the WSAAsyncSelect registrations ask
 * for - and hands everything else to DefWindowProcA.  Inside it retrieves the
 * connection through GetWindowLongA(hwnd, GWL_USERDATA) and dispatches the
 * socket event: accept() for a pending connection, CommEngineRecv for FD_READ
 * and CommEngineSend for FD_WRITE.
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


/* FIXED (2026-07-20): a WNDPROC installed via SetWindowLongA(GWL_WNDPROC);
 * __stdcall, confirmed by `ret 0x10` at every return in the original.
 * Ghidra emitted __cdecl, and the install site passed the literal
 * original-binary address instead of this symbol. Same bug class as
 * FUN_004fecb0. */
LRESULT __stdcall CommEngineNotifyWndProc(HWND param_1,UINT param_2,WPARAM param_3,uint param_4)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  LONG LVar3;
  SOCKET SVar4;
  LRESULT LVar5;
  sockaddr local_10;
  
  LVar3 = GetWindowLongA(param_1,-0x15);
  if (param_2 != 0x478) {
    LVar5 = DefWindowProcA(param_1,param_2,param_3,param_4);
    return LVar5;
  }
  puVar2 = *(undefined4 **)(LVar3 + 4);
  do {
    puVar1 = puVar2;
    if (puVar1 == (undefined4 *)0x0) goto LAB_004fe749;
    puVar2 = (undefined4 *)*puVar1;
  } while (puVar1[2] != param_3);
  if (puVar1 == (undefined4 *)0x0) {
LAB_004fe749:
    if ((param_4 & 0xffff) != 8) {
      return -5;
    }
  }
  switch(param_4 & 0xffff) {
  case 1:
    /* DROPPED-REG FIX 2026-08-28: MIS-SLOTTED, not just short - the one
       argument passed was the error code, and it was landing in the
       __thiscall receiver. The binary at 0x4fe777: `push ecx` (the error,
       WSAGETSELECTERROR = param_4 >> 0x10, from `shr ecx,0x10` at
       0x4fe725), `mov ecx,eax` (the node - `mov eax,edi` at 0x4fe745
       holds the dispatch walk's puVar1 in EAX for every arm),
       `mov edi,esi` (the engine). */
    CommEngineRecv((int *)puVar1,param_4 >> 0x10,(undefined4 *)LVar3);
    return 0;
  case 2:
    /* DROPPED-REG FIX 2026-08-28: orig 0x4fe78d `mov ebx,eax` (the
       node), `push esi` (the engine, the declared stack argument),
       `mov eax,ecx` (the error code). */
    CommEngineSend(LVar3,param_4 >> 0x10,(int)puVar1);
    return 0;
  case 8:
    if (*(SOCKET *)(LVar3 + 0x1c) == param_3) {
      param_4 = 0x10;
      SVar4 = accept(*(SOCKET *)(LVar3 + 0x1c),&local_10,(int *)&param_4);
      if (SVar4 != 0xffffffff) {
        FUN_004ff690(&local_10,(int)param_4);
      }
    }
    break;
  case 0x10:
    /* DROPPED-REG FIX 2026-08-28: the node, in EAX at every arm. */
    FUN_004ff640((int *)LVar3,param_4 >> 0x10,(int *)puVar1);
    return 0;
  case 0x20:
    /* DROPPED-REG FIX 2026-08-28: orig 0x4fe7b8 `mov edx,esi` (the
       engine) with the node still in EAX. ECX is STALE in the original
       on this arm - no write reaches it - so 0 is passed to match the
       other five sites rather than reproduce an uninitialised read. */
    FUN_004fe6a0(0,(int *)LVar3,(int *)puVar1);
    return 0;
  }
  return 0;
}

