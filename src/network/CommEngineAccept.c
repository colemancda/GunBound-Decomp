/* CommEngineAccept - 0x004ff690 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004ff690 mean this function.)
 *
 * NAMED (2026-11-05), HIGH. Evidence from outside the body: The sole
 * caller, CommEngineNotifyWndProc, reaches it from case 8 (FD_ACCEPT):
 * once accept() on the engine's listen socket (engine + 0x1c) returns a
 * socket, it hands over the peer sockaddr and the addrlen accept() wrote
 * back (EAX). The addrlen must be 0x10 (sizeof sockaddr_in) or the
 * accepted socket is closed; otherwise ConfigureAsyncSocket(engine,
 * sockaddr) wraps the socket in a connection node (closesocket on failure)
 * and the engine's vtable slot +0xc is fired with that node. It is the
 * FD_ACCEPT counterpart of the sibling per-event handlers CommEngineRecv
 * (case 1), CommEngineSend (case 2) and CommEngineConnectComplete (case
 * 0x10).
 *
 * FIXED (2026-11-05): the accepted SOCKET (EDI) and the engine (ESI) were
 * dropped registers (sock/engine, so closesocket read an
 * uninitialised value) and the caller never passed accept()'s result.
 * Disasm at the sole call site 0x4fe7eb-0x4fe7fb: `mov edi,eax` (accept()
 * result, tested against -1), esi = engine (the same register
 * `mov eax,[esi+0x1c]` reads the listen socket from), `push lea [esp+0x10]`
 * (the sockaddr), `mov eax,[esp+0x34]` (the addrlen). In the callee,
 * `mov ecx,edi` + `push esi` feed ConfigureAsyncSocket and the two
 * `mov [esp+4],edi; jmp closesocket` tails close edi. They are now the
 * trailing promoted parameters sock and engine, and the ConfigureAsyncSocket
 * call passes (socket, engine, sockaddr) as the callee defines them (the old
 * call passed the engine as the socket and left the third argument off).
 */
#include "ghidra_types.h"


void CommEngineAccept(undefined4 param_1,int regEax,SOCKET sock,int *engine)

{
  int iVar1;
  
  if (regEax != 0x10) {
                    /* WARNING: Could not recover jumptable at 0x004ff699. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    closesocket(sock);
    return;
  }
  iVar1 = ConfigureAsyncSocket(sock,(u_long)engine,param_1);
  if (iVar1 == 0) {
                    /* WARNING: Could not recover jumptable at 0x004ff6b4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    closesocket(sock);
    return;
  }
  (**(code **)(*engine + 0xc))(0,iVar1);
  return;
}

