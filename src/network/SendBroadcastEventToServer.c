/* SendBroadcastEventToServer - 0x004e8040 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-26), HIGH. The TCP fallback for the broadcast-event
 * pipeline: builds opcode 0x4500 (one byte param_1 - the slot - plus the
 * caller's EAX-pointed payload) into the connection's own outgoing-packet
 * buffer and sends it via SendOutgoingPacket, the counterpart to
 * ProcessEventBroadcast's incoming 0x4501. SendBroadcastEventToSlot's own
 * already-committed header already names this exact function and address
 * as "a TCP fallback through FUN_004e8040 for specific opcode types", and
 * all 4 of its call sites (SendBroadcastEventToSlot, BroadcastQueuedEvent,
 * UdpProbeWorkerThread and BroadcastRingEvent) already pass a single int
 * argument matching this declared signature, so functions.h's prior
 * K&R-empty prototype is promoted to the real one here.
 */
#include "ghidra_types.h"


void SendBroadcastEventToServer(int param_1)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  ushort *in_EAX;
  uint uVar4;
  undefined4 *puVar5;
  
  iVar3 = g_connectionContextA;
  *(undefined4 *)(g_connectionContextA + 0x44d0) = 6;
  *(undefined2 *)(iVar3 + 0x4d4) = 0x4500;
  *(undefined2 *)(iVar3 + 0x4d6) = 1;
  iVar2 = *(int *)(iVar3 + 0x44d0);
  *(int *)(iVar3 + 0x44d0) = iVar2 + 2;
  *(undefined1 *)(iVar2 + 0x4d2 + iVar3) = param_1;
  iVar2 = *(int *)(iVar3 + 0x44d0);
  *(int *)(iVar3 + 0x44d0) = iVar2 + 1;
  uVar1 = *in_EAX;
  puVar5 = (undefined4 *)(iVar2 + 0x4d1 + iVar3);
  for (uVar4 = (uint)(uVar1 >> 2); uVar4 != 0; uVar4 = uVar4 - 1) {
    *puVar5 = *(undefined4 *)in_EAX;
    in_EAX = in_EAX + 2;
    puVar5 = puVar5 + 1;
  }
  for (uVar4 = uVar1 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(char *)puVar5 = (char)*in_EAX;
    in_EAX = (ushort *)((int)in_EAX + 1);
    puVar5 = (undefined4 *)((int)puVar5 + 1);
  }
  *(uint *)(iVar3 + 0x44d0) = *(int *)(iVar3 + 0x44d0) + (uint)uVar1;
  SendOutgoingPacket(iVar3);
  return;
}

