/* UdpProbeWorkerThread - 0x004e6770 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (FUN_004e7140 below is SendBroadcastEventToSlot's old symbol.)
 *
 * NAMED (2026-10-26). This function has NO direct call anywhere in the
 * image - FUN_004e7140's own header already notes that its single
 * reference is a pointer at .data 0x5572f4, inside a vtable. That
 * vtable is 0x5572f0 (docs/vtable_census.txt: slot 0
 * FUN_004e6030/the scalar-deleting destructor, slot 1 this function,
 * slots 2/3 NoOpMethod), and it is installed at `param_1`'s offset 0 by
 * the constructor at 0x4e5e00, whose own sole caller constructs it at
 * the literal address 0xe55ce0 - g_replayContext (the same global this
 * subsystem's other context-taking helpers, e.g.
 * EncryptEventBroadcast/DecryptEventBroadcast/QueueBroadcastEvent,
 * already key off).
 *
 * The thread itself is started by this object's own "start" method
 * (FUN_004e6b50, a bring-up neuter - see its own header), which calls
 * `__beginthread(0x4f47e0, 0, this)`. 0x4f47e0 is a generic three-phase
 * thread-runner thunk shared by more than one class: it dispatches
 * `this`'s own vtable slots +8, then +4, then +0xc (each `call
 * [slot](this)`) before calling `_endthread`. For this object slots +8
 * and +0xc are both NoOpMethod, so the dispatch at +4 - this function -
 * is the entire thread body. The body itself is a UDP socket bind
 * (port 0x20ab) plus a `WaitForMultipleObjects` event loop that calls
 * the already-named ProcessUdpProbeDatagram on FD_READ, re-sends the
 * pending login probe datagram (BeginUdpSessionProbe's own header
 * documents this exact worker loop by this address) every 2s, and
 * periodically fires the 25-second keepalive broadcast events
 * (0x4fff/0x8fff) - i.e. the UDP probe subsystem's own dedicated
 * worker thread, not a generic helper.
 */
#include "ghidra_types.h"


void __fastcall UdpProbeWorkerThread(int param_1)

{
  byte bVar1;
  char cVar2;
  SOCKET SVar3;
  int iVar4;
  DWORD DVar5;
  DWORD DVar6;
  uint uVar7;
  uint uVar8;
  bool bVar9;
  int iStack_4c;
  DWORD DStack_48;
  DWORD DStack_40;
  sockaddr local_3c;
  byte abStack_2c [4];
  int iStack_28;

  SVar3 = socket(2,2,0);
  *(SOCKET *)(param_1 + 0x14) = SVar3;
  if (SVar3 != 0xffffffff) {
    local_3c.sa_family = 2;
    SUBFIELD(local_3c.sa_data,0,undefined2) = htons(0x20ab);
    local_3c.sa_data[2] = '\0';
    local_3c.sa_data[3] = '\0';
    local_3c.sa_data[4] = '\0';
    local_3c.sa_data[5] = '\0';
    iVar4 = bind(*(SOCKET *)(param_1 + 0x14),&local_3c,0x10);
    if (iVar4 == 0) {
      WSAEventSelect(*(undefined4 *)(param_1 + 0x14),*(undefined4 *)(param_1 + 0xc),1);
      DStack_40 = timeGetTime();
      *(DWORD *)(param_1 + 0x4522c) = DStack_40;
      DStack_48 = DStack_40;
      while( true ) {
        DVar5 = WaitForMultipleObjects(3,(HANDLE *)(param_1 + 8),0,0x32);
        DVar6 = timeGetTime();
        if (DVar5 == 0) break;
        if (DVar5 == 1) {
          WSAEnumNetworkEvents
                    (*(undefined4 *)(param_1 + 0x14),*(undefined4 *)(param_1 + 0xc),abStack_2c);
          if ((abStack_2c[0] & 1) != 0) {
            if (iStack_28 != 0) {
              ShowErrorDialog(1);
              goto LAB_004e6b2c;
            }
            cVar2 = ProcessUdpProbeDatagram(param_1);
            if (cVar2 == '\0') {
              ShowErrorDialog(1);
              goto LAB_004e6b2c;
            }
          }
        }
        else if ((DVar5 == 0x102) && (25000 < DVar6 - *(int *)(param_1 + 0x4522c))) {
          bVar9 = g_currentGameState == 0xb;
          *(DWORD *)(param_1 + 0x4522c) = DVar6;
          if (bVar9) {
            QueueBroadcastEvent(0x8fff);
            BroadcastQueuedEvent();
          }
          else {
            QueueBroadcastEvent(0x4fff);
            BroadcastQueuedEvent();
          }
        }
        if (2000 < DVar6 - DStack_40) {
          if (0 < *(int *)(param_1 + 0x45208)) {
            *(int *)(param_1 + 0x45208) = *(int *)(param_1 + 0x45208) + -1;
            EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x17c));
            SendUdpDatagram(*(int *)(param_1 + 0x4520c),(int)*(short *)(param_1 + 0x45210),
                            (char *)(param_1 + 0x45212),4,param_1);
            LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x17c));
          }
          DStack_40 = DVar6;
          if (*(int *)(param_1 + 0x45208) == 0) {
            if (*(int *)(param_1 + 0x44ff0) != 0) {
              FUN_004e5dc0(4,0);
            }
            *(undefined4 *)(param_1 + 0x45208) = 0xffffffff;
          }
        }
        if ((*(uint *)(param_1 + 0x4523c) < DVar6 - DStack_48) &&
           (DStack_48 = DVar6, *(int *)(param_1 + 0x44de0) == 1)) {
          iVar4 = *(int *)(param_1 + 0x44de4) + 1;
          *(int *)(param_1 + 0x44de4) = iVar4;
          if (iVar4 < 0xb) {
            FUN_004e6b90();
            goto LAB_004e6ae3;
          }
          uVar8 = 0;
          iStack_4c = 0;
          bVar9 = true;
          do {
            if (!bVar9) goto LAB_004e6b17;
            uVar7 = 1 << ((byte)uVar8 & 0x1f);
            iVar4 = (uVar8 >> 5) * 4;
            if ((((*(uint *)(iVar4 + 0x140 + param_1) & uVar7) != 0) &&
                ((*(uint *)(iVar4 + 0x13c + param_1) & uVar7) == 0)) &&
               ((*(uint *)(iVar4 + 0x138 + param_1) & uVar7) != 0)) {
              iStack_4c = iStack_4c + 1;
            }
            uVar8 = uVar8 + 1;
            bVar9 = uVar8 < 8;
          } while ((int)uVar8 < 8);
          uVar8 = 0;
          bVar9 = true;
          do {
            if (!bVar9) {
LAB_004e6b17:
                    /* WARNING: Subroutine does not return */
              Bitset_ThrowInvalidPosition();
            }
            bVar1 = (byte)uVar8;
            uVar7 = 1 << (bVar1 & 0x1f);
            iVar4 = (uVar8 >> 5) * 4;
            if ((((*(uint *)(iVar4 + 0x140 + param_1) & uVar7) != 0) &&
                ((*(uint *)(iVar4 + 0x13c + param_1) & uVar7) == 0)) &&
               ((*(uint *)(iVar4 + 0x138 + param_1) & uVar7) != 0)) {
              if (*(char *)(uVar8 + 0x454e4 + param_1) == '\0') {
                *(undefined1 *)(uVar8 + 0x454e4 + param_1) = 1;
                *(byte *)(*(int *)(param_1 + 0x454f4) + 0x454ec + param_1) = bVar1;
                *(int *)(param_1 + 0x454f4) = *(int *)(param_1 + 0x454f4) + 1;
                FUN_004e8040(uVar8);
                *(uint *)(iVar4 + 0x13c + param_1) = *(uint *)(iVar4 + 0x13c + param_1) | uVar7;
                QueueBroadcastEvent(0xf00c);
                *(byte *)(param_1 + 0x44dec + *(int *)(param_1 + 0x44fec)) = bVar1;
                *(int *)(param_1 + 0x44fec) = *(int *)(param_1 + 0x44fec) + 1;
                SendBroadcastEventToSlot(0xffffffff,param_1);
              }
              else if (*(int *)(param_1 + 0x44ff0) != 0) {
                if (2 < *(int *)(param_1 + 0x44de8)) {
                  if (1 < iStack_4c) {
                    FUN_004e5dc0(5,0xffffffff);
                    break;
                  }
                  FUN_004e5dc0(5,uVar8);
                }
                FUN_004e5dc0(2,uVar8);
              }
            }
            uVar8 = uVar8 + 1;
            bVar9 = uVar8 < 8;
          } while ((int)uVar8 < 8);
          *(int *)(param_1 + 0x44de8) = *(int *)(param_1 + 0x44de8) + 1;
          *(undefined4 *)(param_1 + 0x44de4) = 0;
          FUN_004e77e0(param_1,-1);
        }
        else {
LAB_004e6ae3:
          FUN_004e77e0(param_1,-1);
        }
      }
      WSAEventSelect(*(undefined4 *)(param_1 + 0x14),*(undefined4 *)(param_1 + 0xc),0);
    }
  }
LAB_004e6b2c:
  if (*(SOCKET *)(param_1 + 0x14) != 0xffffffff) {
    closesocket(*(SOCKET *)(param_1 + 0x14));
  }
  *(undefined4 *)(param_1 + 0x14) = 0xffffffff;
  return;
}
