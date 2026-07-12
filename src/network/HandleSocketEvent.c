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
  uint unaff_ESI;
  uint uVar4;
  char *pcVar5;
  undefined4 uVar6;
  int iStack_4044;
  int iStack_4040;
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
    cVar1 = ConnectSocketToTarget(param_1 + 0x28);
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
  if ((param_1 & 1) != 0) {
    if (iStack_4044 == 0) {
      cVar1 = ReceiveFramedPackets();
      if (cVar1 != '\0') goto LAB_004e58ad;
      uVar6 = *(undefined4 *)(param_1 + 0x1c);
    }
    else {
      uVar6 = *(undefined4 *)(param_1 + 0x1c);
    }
    FUN_004f2da0(*(uint **)(param_1 + 0x20),0x65,uVar6,0);
    CloseConnectionSocket();
  }
LAB_004e58ad:
  uVar4 = param_1;
  if ((param_1 & 2) != 0) {
    if (iStack_4040 == 0) {
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
           (iVar2 = send(*(SOCKET *)(unaff_ESI + 0x24),acStack_401c,iStack_1c,0), iVar2 < 0)) {
          FUN_004f2da0(*(uint **)(unaff_ESI + 0x20),0x65,*(undefined4 *)(unaff_ESI + 0x1c),0);
          CloseConnectionSocket();
        }
        FUN_004e5cc0();
        uVar4 = unaff_ESI;
      }
      LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x24a58));
    }
    else {
      FUN_004f2da0(*(uint **)(param_1 + 0x20),0x65,*(undefined4 *)(param_1 + 0x1c),0);
      CloseConnectionSocket();
    }
  }
  if ((param_1 & 0x20) == 0) {
    return;
  }
  FUN_004f2da0(*(uint **)(uVar4 + 0x20),0x65,*(undefined4 *)(uVar4 + 0x1c),0);
  CloseConnectionSocket();
  return;
}

