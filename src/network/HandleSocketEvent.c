/* HandleSocketEvent - 0x004e57c0 in the original binary.
 *
 * The connection object's socket-event dispatch routine. param_2 selects
 * the operation:
 *   0 - WSAEventSelect(deselect), detach the socket from its event.
 *   1 - drain pending WSA network events (WSAEnumNetworkEvents):
 *       FD_READ  -> ReceiveFramedPackets;
 *       FD_WRITE -> flush the outgoing send() queue;
 *       FD_CLOSE -> CloseConnectionSocket + enqueue failure code 0x65.
 *   2 - perform the connect (ConnectSocketToTarget); on success re-arm
 *       WSAEventSelect for READ|WRITE|CLOSE (0x23) and enqueue success
 *       code 100, otherwise reset state and enqueue failure code 0x65.
 * Status codes 0x65/100 are pushed to the generic event queue (FUN_004f2da0)
 * targeting the connection's owning UI object (conn+0x1c).
 *
 * FUN_004f2da0's 1st arg (the event-queue object, its own dropped
 * EAX) is conn+0x20 - orig 0x4e57fa/0x4e5833: `mov eax,[esi+0x20]`
 * stays live (unclobbered) all the way to each `call 0x4f2da0`. This
 * function already null-checks conn+0x20 before every call site
 * (`if (*(int*)(param_1+0x20) == 0) return;`, etc.) but never actually
 * passed it - promoted to an explicit 1st argument at each call site.
 *
 * The FD_READ/FD_WRITE/FD_CLOSE dispatch in the param_2==1 branch was
 * testing bits of `param_1` (the connection pointer itself) instead of
 * the WSANETWORKEVENTS.lNetworkEvents bitmask - orig 0x4e5876/0x4e58ad/
 * 0x4e596c all `test BYTE PTR [esp+0x1c],<bit>` against the
 * WSAEnumNetworkEvents output buffer (`local_403c`, passed by address
 * to that call at 0x4e5868), never against param_1/ecx. Ghidra also
 * split that same buffer's first two DWORDs into separate pseudo-locals
 * (iStack_4044/iStack_4040) and then misapplied them: the FD_READ inner
 * check (0x4e587d, `[esp+0x20]` = buffer+4, the FD_READ error code) was
 * re-testing the buffer+0 bitmask instead, and the FD_WRITE inner check
 * (0x4e58b8, `[esp+0x24]` = buffer+8, the FD_WRITE error code) was
 * reading buffer+4. Fixed by indexing `local_403c` directly at +0/+4/+8
 * instead of trusting those two aliased locals. Also `unaff_ESI` in the
 * FD_WRITE branch (0x4e591e: `mov esi,[esp+0x10]`, the saved copy of
 * the original this-pointer, restored after the byte-copy loop clobbers
 * esi) is just param_1 - replaced with param_1 directly.
 *
 * FIXED (2026-07-14): the op-2 call site was passing `param_1 + 0x28` to
 * ConnectSocketToTarget, matching the real disassembly's `lea eax,
 * [esi+0x28]; push eax` at the call site (orig 0x4e57ef-0x4e57f3). But
 * angr-disassembling ConnectSocketToTarget's full body (0x4e59b0-
 * 0x4e5a17) shows that pushed argument is read back only ONCE there
 * (`mov edx,[esp+0x14]` at 0x4e59dd), and only to feed its
 * FUN_004e5480(hostname) sub-call - every OTHER field access in that
 * function (`[esi+0x24]` socket, `[esi+0x228]` port, `[esi+0x22a]`
 * connected-flag) instead uses `esi` directly, inherited unchanged
 * across the `call` from THIS caller's own `param_1` (the true,
 * unshifted connection base) - matching every other field access in
 * this file and in SignalConnectRequest.c. In other words the original
 * compiler emitted the same `esi+0x28` value twice: once as an explicit
 * stack argument (for the sub-call only) and once implicitly via the
 * preserved this-pointer register (for everything else). Passing the
 * plain unshifted `param_1` here and having ConnectSocketToTarget
 * re-derive `+0x28` internally for its own sub-call (see that file's
 * header) reproduces the original bit-for-bit with one consistent base
 * pointer instead of two forms of the same offset. Fixed to pass
 * `param_1` directly; see ConnectSocketToTarget.c's own header for the
 * matching fix on that side (this was a two-function, one-bug pair).
 *
 * Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void __thiscall HandleSocketEvent(uint param_1,int param_2)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  char *pcVar5;
  undefined4 uVar6;
  undefined1 local_403c [32];
  char acStack_401c [16384];
  int iStack_1c;
  undefined4 uStack_c;
  
  uStack_c = 0x4e57d0;
  if (param_2 == 0) {
    WSAEventSelect(*(undefined4 *)(param_1 + 0x24),*(undefined4 *)(param_1 + 0xc),0);
    return;
  }
  if (param_2 != 1) {
    if (param_2 != 2) {
      return;
    }
    cVar1 = ConnectSocketToTarget(param_1);
    if (cVar1 == '\0') {
      *(undefined4 *)(param_1 + 0x22c) = 0;
      if (*(int *)(param_1 + 0x20) == 0) {
        return;
      }
      FUN_004f2da0(*(int *)(param_1 + 0x20),0x65,*(undefined4 *)(param_1 + 0x1c),0);
      return;
    }
    *(undefined4 *)(param_1 + 0x22c) = 2;
    if (*(int *)(param_1 + 0x20) != 0) {
      FUN_004f2da0(*(int *)(param_1 + 0x20),100,*(undefined4 *)(param_1 + 0x1c),0);
    }
    WSAEventSelect(*(undefined4 *)(param_1 + 0x24),*(undefined4 *)(param_1 + 0xc),0x23);
    return;
  }
  iVar2 = WSAEnumNetworkEvents
                    (*(undefined4 *)(param_1 + 0x24),*(undefined4 *)(param_1 + 0xc),local_403c);
  if (iVar2 != 0) {
    return;
  }
  if ((*(int *)local_403c & 1) != 0) {
    if (*(int *)(local_403c + 4) == 0) {
      cVar1 = ReceiveFramedPackets(param_1);
      if (cVar1 != '\0') goto LAB_004e58ad;
      uVar6 = *(undefined4 *)(param_1 + 0x1c);
    }
    else {
      uVar6 = *(undefined4 *)(param_1 + 0x1c);
    }
    FUN_004f2da0(*(uint **)(param_1 + 0x20),0x65,uVar6,0);
    CloseConnectionSocket(param_1);
  }
LAB_004e58ad:
  uVar4 = param_1;
  if ((*(int *)local_403c & 2) != 0) {
    if (*(int *)(local_403c + 8) == 0) {
      EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x24a58));
      if (*(int *)(param_1 + 0x24a44) != 0) {
        puVar3 = (undefined4 *)FUN_004e5c50();
        pcVar5 = acStack_401c;
        for (iVar2 = 0x1001; iVar2 != 0; iVar2 = iVar2 + -1) {
          *(undefined4 *)pcVar5 = *puVar3;
          puVar3 = puVar3 + 1;
          pcVar5 = pcVar5 + 4;
        }
        if ((0 < iStack_1c) &&
           (iVar2 = send(*(SOCKET *)(param_1 + 0x24),acStack_401c,iStack_1c,0), iVar2 < 0)) {
          FUN_004f2da0(*(uint **)(param_1 + 0x20),0x65,*(undefined4 *)(param_1 + 0x1c),0);
          CloseConnectionSocket(param_1);
        }
        FUN_004e5cc0();
        uVar4 = param_1;
      }
      LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x24a58));
    }
    else {
      FUN_004f2da0(*(uint **)(param_1 + 0x20),0x65,*(undefined4 *)(param_1 + 0x1c),0);
      CloseConnectionSocket(param_1);
    }
  }
  if ((*(int *)local_403c & 0x20) == 0) {
    return;
  }
  FUN_004f2da0(*(uint **)(uVar4 + 0x20),0x65,*(undefined4 *)(uVar4 + 0x1c),0);
  CloseConnectionSocket(uVar4);
  return;
}

