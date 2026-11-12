/* HeartbeatWorker_OnTimeout - 0x00401200 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00401200 mean this function.)
 *
 * NAMED (batch 48), LIKELY. Slot 1 of vtable 0x54b458, the derived vtable
 * HeartbeatWorker_Construct installs (slot 0 is NoOpMethodStdcall1), and
 * WorkerThread2EventLoop calls slot 1 on a 10 s wait timeout, so this is
 * the periodic tick of the 0x7a767c block. The role evidence is outside
 * the body: the counter it bumps at connection +0x84ec is zeroed by
 * SendOutgoingPacket and FlushEncodedSocketBuffer (both write 0 there
 * after a real send), so it counts idle ticks; after 30 of them (about 5
 * minutes) it sends a header-only packet (length 6 at +0x44d0, opcode word
 * 0 at +0x4d4) on g_connectionContextA, which is a keepalive. Every 12th
 * tick, while the byte at this+0x10 is set, it also queues broadcast event
 * 0x9001, and while the UDP flag is set it re-sends a 1-byte datagram.
 * LIKELY, not CERTAIN: the Heartbeat label rests on the idle-counter
 * reading and no server-side keepalive handler corroborates it.
 */
#include "ghidra_types.h"


void __fastcall HeartbeatWorker_OnTimeout(int param_1)

{
  int iVar1;
  int iVar2;
  sockaddr local_40 [2];
  undefined1 local_20 [32];
  /* BuildSystemInfoBlob's 2nd output (orig ESI, dropped) - NOT verified
   * against this call site's original disassembly; added only to satisfy
   * the now-2-parameter signature (see BuildSystemInfoBlob.c). Revisit if
   * this code path is ever exercised. */
  undefined4 systemInfoBlob2 [6];


  iVar1 = g_connectionContextA;
  if (g_connectionContextA != 0) {
    iVar2 = *(int *)(g_connectionContextA + 0x84ec) + 1;
    *(int *)(g_connectionContextA + 0x84ec) = iVar2;
    if (0x1d < iVar2) {
      *(undefined2 *)(iVar1 + 0x4d4) = 0;
      *(undefined4 *)(iVar1 + 0x44d0) = 6;
      SendOutgoingPacket(iVar1);
      *(undefined4 *)(g_connectionContextA + 0x84ec) = 0;
    }
    if ((*(char *)(param_1 + 0x10) != '\0') && (DAT_00e9af60 = DAT_00e9af60 + 1, 0xb < DAT_00e9af60)
       ) {
      QueueBroadcastEvent(0x9001,(int)&g_replayContext);
      BroadcastQueuedEvent();
      DAT_00e9af60 = 0;
    }
  }
  if ((DAT_00e55a54 != '\0') && (DAT_00e55a58 < 0x1e)) {
    BuildSystemInfoBlob(local_20, systemInfoBlob2);
    if (DAT_00e55a64 != (int *)0x0) {
      (**(code **)(*DAT_00e55a64 + 0xc))(&DAT_005b1c70,DAT_005b33f4,local_20,local_40);
    }
    DAT_00e55a58 = DAT_00e55a58 + 1;
  }
  if (DAT_007934f8 != '\0') {
    while (DAT_00e55cf4 != 0xffffffff) {
      local_40[0].sa_family = 2;
      local_40[0].sa_data[2] = (undefined1)DAT_005b2b54;
      local_40[0].sa_data[3] = SUBFIELD(DAT_005b2b54,1,undefined1);
      local_40[0].sa_data[4] = SUBFIELD(DAT_005b2b54,2,undefined1);
      local_40[0].sa_data[5] = SUBFIELD(DAT_005b2b54,3,undefined1);
      local_40[0].sa_data[0] = (undefined1)DAT_005b343c;
      local_40[0].sa_data[1] = SUBFIELD(DAT_005b343c,1,undefined1);
      if (DAT_005b2b54 == -1) {
        return;
      }
      if (DAT_005b343c == -1) {
        return;
      }
      iVar1 = sendto(DAT_00e55cf4,&DAT_0054b460,1,0,local_40,0x10);
      if (iVar1 != -1) {
        return;
      }
      ShowErrorDialog(1);
      WSAGetLastError();
    }
  }
  return;
}

