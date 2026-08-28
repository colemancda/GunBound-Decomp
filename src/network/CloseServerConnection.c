/* CloseServerConnection - 0x004d24f0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED REGISTER RECOVERED (2026-08-27): unaff_EDI is the CONNECTION
 * CONTEXT.  The body reads `*(int *)(unaff_EDI + 0x84e0)` -- the connection
 * object pointer this tree already documents at that offset -- then marks it
 * +0x22c = 1, closesocket()s its +0x24 handle and clears +0x22a, i.e. it tears
 * down whichever connection the context owns.
 *
 * Each of the four callers holds exactly one site, so nothing rests on
 * ordering, and three of them load the value straight from an already-named
 * global: `mov edi,[0x7934e8]` = g_connectionContextA at 0x4e0b87, and
 * `mov edi,[0x7934ec]` = g_connectionContextB at 0x4e138f and 0x4e1aac.
 * These are LOADS, not addresses -- the globals are declared uint32_t and the
 * surrounding code already uses their VALUE as a base
 * (`g_connectionContextB + 0x4d4`), so the value is what gets passed.
 *
 * ProcessIncomingPackets passes its own param_1.  Its frame: the SEH triple
 * (12) plus a 0x24dc __chkstk puts esp at E-0x24e8, and four register saves
 * at 0x4d2836-0x4d2839 take it to E-0x24f8, so the site's [esp+0x24fc] is
 * E+4.  Cross-checked against that function's own prologue, where
 * [esp+0x24ec] before any save is the same E+4 and is immediately used as
 * `[ecx + 0x84e4]` / `[ecx + 0x84e0]` -- the very fields this callee reads.
 *
 * The connection context's "drop the server connection" entry, and the
 * counterpart to BeginServerConnect (0x4d2480) -- the function
 * immediately before it in the binary (0x4d2480 + 102 = 0x4d24e6, then
 * int3 padding to 0x4d24f0). Both act on the same 0x84f0-byte context,
 * of which WinMain builds three (operator_new(0x84f0) ->
 * InitConnectionObject with selector 0/1/2 -> DAT_005b2b58 /
 * DAT_005b2b5c / DAT_005b2b60). BeginServerConnect arms one
 * (SignalConnectRequest plus the connect-requested flag ctx+0x84e4 = 1);
 * this tears it back down. Nothing is freed and the socket worker thread
 * is left running, so the context is immediately reusable and a second
 * BeginServerConnect reconnects it. Freeing the connection object is
 * FUN_004d22d0's job; joining the worker is ShutdownConnectionThread's
 * (0x4e5c00).
 *
 * The body is CloseConnectionSocket (0x4e5a20) applied to the connection
 * object at ctx+0x84e0 -- state conn+0x22c = 1 (idle/reset), closesocket()
 * the conn+0x24 handle via the ws2_32 thunk at [0x54432c] (resolved from
 * the import directory), handle = INVALID_SOCKET, connected flag
 * conn+0x22a = 0 -- plus the one thing that inner helper cannot do: it
 * clears the CONTEXT's own connected flag ctx+0x84e5. That is the flag
 * ProcessIncomingPackets latches from the connection state
 * (ctx+0x84e5 = (state == 2) at 0x4d2826-0x4d2830; state 2 = connected,
 * per ARCHITECTURE.md's connection-state list).
 *
 * The same sequence appears INLINED wherever the compiler could see the
 * context: FUN_004d22d0 runs it immediately before freeing the object and
 * nulling ctx+0x84e0, and ShowErrorDialog / ShowErrorDialogFmt /
 * ShowMessageDialog / Shutdown run it over all three contexts under their
 * closeSockets flag -- ShowErrorDialog.c's header already glosses that
 * sequence as "tears down all three connection objects".
 *
 * All four out-of-line call sites drop a server connection; none is
 * object teardown:
 * 0x4d2b5e  ProcessIncomingPackets -- opcode 0x1fff (`cmp ebp,0x1fff`
 * at 0x4d2b4f), closed before the localized 0x199/0x19a/0x19b
 * MessageBoxA is raised.
 * 0x4e0b8d  State02_ServerSelect_ProcessPacket -- opcode 0x2001,
 * GB_OP_JOIN_CHANNEL_RESPONSE, accepted (payload word 0): closes
 * g_connectionContextA, then swaps 0x7934e8/0x7934ec at
 * 0x4e0b92-0x4e0bb0, so the channel handoff retires the connection it
 * is leaving.
 * 0x4e1395  State02_ServerSelect_OnTopButton -- the param_2 == 4
 * branch, after g_serverWaitTicks = -1 (which drops the PLEASE WAIT
 * overlay), the connect button's state-name revert,
 * ShowErrorDialog(0), and the nonce re-scramble. That branch's UI
 * purpose is still unconfirmed in-tree (see that file's header), so
 * it is described by what it does rather than as "the cancel button".
 * 0x4e1ab2  State02_ServerSelect_OnTick -- the connect attempt has
 * resolved and FAILED (ctx+0x84e4 already cleared, ctx+0x84e5 still
 * 0). src/cxx/State02_ServerSelect.cpp declares this function at file
 * scope as "the connection context to tear down".
 *
 * ctx+0x84e5 is per-context, so read the callers carefully: OnTick's
 * initial 0x1100 GB_OP_SERVER_DIRECTORY_REQUEST is gated on
 * DAT_007934f0's copy of the flag, not on the g_connectionContextB copy
 * that OnTick's call to this function clears.
 *
 * Named by role. No user-class RTTI survives in this build -- the only
 * eight .?AV records are CRT/ATL (CAtlException, _com_error, bad_alloc,
 * exception, length_error, logic_error, out_of_range, type_info) -- so no
 * original symbol is recoverable.
 */
#include "ghidra_types.h"


void CloseServerConnection(int regEdi)

{
  int iVar1;
  int unaff_EDI = regEdi;
  
  iVar1 = *(int *)(unaff_EDI + 0x84e0);
  if (iVar1 != 0) {
    *(undefined4 *)(iVar1 + 0x22c) = 1;
    if (*(SOCKET *)(iVar1 + 0x24) != 0xffffffff) {
      closesocket(*(SOCKET *)(iVar1 + 0x24));
    }
    *(undefined4 *)(iVar1 + 0x24) = 0xffffffff;
    *(undefined1 *)(iVar1 + 0x22a) = 0;
    *(undefined1 *)(unaff_EDI + 0x84e5) = 0;
  }
  return;
}

