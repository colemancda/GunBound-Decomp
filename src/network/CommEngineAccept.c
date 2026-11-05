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
 * The accepted SOCKET (EDI) and the engine (ESI) are dropped registers in
 * this port (unaff_EDI/unaff_ESI), and the caller's accept() result is not
 * passed; left as found, not fixed here.
 */
#include "ghidra_types.h"


void CommEngineAccept(undefined4 param_1,int regEax)

{
  int iVar1;
  int *unaff_ESI;
  SOCKET unaff_EDI;
  
  if (regEax != 0x10) {
                    /* WARNING: Could not recover jumptable at 0x004ff699. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    closesocket(unaff_EDI);
    return;
  }
  iVar1 = ConfigureAsyncSocket(unaff_ESI,param_1);
  if (iVar1 == 0) {
                    /* WARNING: Could not recover jumptable at 0x004ff6b4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    closesocket(unaff_EDI);
    return;
  }
  (**(code **)(*unaff_ESI + 0xc))(0,iVar1);
  return;
}

