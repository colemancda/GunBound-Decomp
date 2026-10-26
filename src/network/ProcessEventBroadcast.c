/* ProcessEventBroadcast - 0x004e7de0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-26), LIKELY (verb was left open by the scoping pass;
 * settled on "Process" rather than "Decode" below). Sole caller
 * WriteReplayEventRecord.c:178 hands this the server's opcode-0x4501
 * packet body (`FUN_004e7de0(&g_replayContext,*pbVar22,pbVar22+1,
 * param_1-1)` - a type byte, the rest of the payload, and its length).
 * The body decrypts it via DecryptEventBroadcast (already named; its own
 * header already cites this exact call site, "FUN_004e7de0, ebp = its
 * EAX context arg"), validates a running-sum checksum, and - matching
 * the opcode-0xa001/0xa002-ish type tags checked here - dispatches
 * QueueBroadcastEvent/SendBroadcastEventToSlot (both already named) for
 * one sub-type before appending the decoded record into the 0x206-stride
 * array at g_replayContext+0x454b4/+0x454b8, the same array
 * PopBroadcastBattleAction (named earlier in this batch) drains. This is
 * the same decode-validate-dispatch-enqueue shape as ProcessUdpProbeDatagram
 * (its own header: "recvfrom-first... validates a checksum/magic
 * header... tracks... via EncodeUdpProbeHeader + SendUdpDatagram"), just
 * over the TCP-delivered "event broadcast" packet instead of a UDP probe
 * datagram - "Process", matching that sibling's verb, rather than
 * "Decode", since dispatch and enqueue happen inline, not just decoding.
 *
 * DROPPED-REGISTER NOTE: `regEbx` is the payload length (param_1-1 at the
 * call site, confirmed by the copy loops below stepping by it) - Ghidra's
 * own `unaff`-free rendering here already reads it as a normal parameter,
 * so no fix was needed; carried over unchanged.
 */
#include "ghidra_types.h"


void ProcessEventBroadcast(int param_1,int param_2,undefined4 *param_3,uint regEbx)

{
  LPCRITICAL_SECTION lpCriticalSection;
  uint *puVar1;
  byte bVar2;
  undefined2 uVar3;
  char cVar4;
  DWORD DVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;

  if (7 < param_2) {
                    /* WARNING: Subroutine does not return */
    Bitset_ThrowInvalidPosition();
  }
  uVar6 = (uint)param_2;
  if (7 < uVar6) {
                    /* WARNING: Subroutine does not return */
    Bitset_ThrowInvalidPosition();
  }
  puVar1 = (uint *)(param_1 + 0x148 + (uint)(param_2 >> 5) * 4);
  *puVar1 = *puVar1 | 1 << (param_2 & 0x1f);
  lpCriticalSection = (LPCRITICAL_SECTION)(param_1 + 0x45264);
  EnterCriticalSection(lpCriticalSection);
  uVar3 = *(undefined2 *)((int)param_3 + 2);
  *(byte *)(param_1 + 0x452a0) = param_2;
  *(undefined2 *)(param_1 + 0x4529c) = uVar3;
  *(short *)(param_1 + 0x4529e) = (short)regEbx;
  puVar10 = (undefined4 *)(param_1 + 0x452a1);
  puVar11 = param_3;
  puVar9 = puVar10;
  for (uVar7 = regEbx >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *puVar9 = *puVar11;
    puVar11 = puVar11 + 1;
    puVar9 = puVar9 + 1;
  }
  for (uVar7 = regEbx & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined1 *)puVar9 = *(undefined1 *)puVar11;
    puVar11 = (undefined4 *)((int)puVar11 + 1);
    puVar9 = (undefined4 *)((int)puVar9 + 1);
  }
  DAT_0056dca7 = *(undefined1 *)(param_1 + 0x452a9);
  DAT_0056dca5 = *(undefined1 *)(param_1 + 0x452a3);
  DAT_0056dcaa = *(undefined1 *)(param_1 + 0x452a4);
  /* orig 0x4e7e9b `mov eax, ebp` (EBP = this function's param_1) -
   * DecryptEventBroadcast's recovered EAX context argument. */
  DecryptEventBroadcast((undefined4 *)(param_1 + 0x452c2),regEbx,param_1);
  iVar8 = 0x21;
  cVar4 = *(char *)(param_1 + 0x452a9) + *(char *)(param_1 + 0x452a3) + *(char *)(param_1 + 0x452a4)
          + -0x34;
  if (0x21 < (int)regEbx) {
    do {
      cVar4 = cVar4 + *(char *)((int)puVar10 + iVar8);
      iVar8 = iVar8 + 1;
    } while (iVar8 < (int)regEbx);
  }
  if (cVar4 != *(char *)(param_1 + 0x452a5)) {
    if (*(uint *)(param_1 + 0x14c) == uVar6) {
      ShowErrorDialog(1);
    }
    LeaveCriticalSection(lpCriticalSection);
    return;
  }
  if ((*(byte *)(param_1 + 0x4529d) & 0x80) != 0) {
    cVar4 = *(char *)(uVar6 + 0x3c0 + param_1);
    if (*(char *)((int)param_3 + 7) != cVar4) {
      *(undefined1 *)(param_1 + 0x4527c) = 9;
      LeaveCriticalSection(lpCriticalSection);
      return;
    }
    DAT_0056d3d8 = 0xffffffff;
    *(char *)(uVar6 + 0x3c0 + param_1) = cVar4 + '\x01';
  }
  if (*(short *)(param_1 + 0x4529c) == -0x6000) {
    QueueBroadcastEvent(0xa001);
    SendBroadcastEventToSlot(*(undefined1 *)((int)param_3 + 5),param_1);
  }
  if (*(short *)(param_1 + 0x4529c) == -0x5fff) {
    bVar2 = *(byte *)((int)param_3 + 5);
    DVar5 = timeGetTime();
    *(DWORD *)(param_1 + 0x454c4 + (uint)bVar2 * 4) =
         DVar5 - *(int *)(param_1 + 0x45240 + (uint)bVar2 * 4) >> 1;
  }
  uVar7 = *(uint *)(param_1 + 0x454b8);
  if ((*(uint *)(param_1 + 0x454bc) <= uVar7) && (cVar4 = CArray_Grow_206(uVar7 + 1,(int *)(param_1 + 0x454b4)), cVar4 == '\0')) {
                    /* WARNING: Subroutine does not return */
    ThrowCxxException(0x8007000e);
  }
  puVar11 = (undefined4 *)(uVar7 * 0x206 + *(int *)(param_1 + 0x454b4));
  if (puVar11 != (undefined4 *)0x0) {
    puVar9 = (undefined4 *)(param_1 + 0x4529c);
    for (iVar8 = 0x81; iVar8 != 0; iVar8 = iVar8 + -1) {
      *puVar11 = *puVar9;
      puVar9 = puVar9 + 1;
      puVar11 = puVar11 + 1;
    }
    *(undefined2 *)puVar11 = *(undefined2 *)puVar9;
  }
  *(int *)(param_1 + 0x454b8) = *(int *)(param_1 + 0x454b8) + 1;
  LeaveCriticalSection(lpCriticalSection);
  puVar11 = (undefined4 *)(uVar6 * 0x200 + 0x41bd8 + param_1);
  puVar9 = puVar11;
  for (iVar8 = 0x80; iVar8 != 0; iVar8 = iVar8 + -1) {
    *puVar9 = 0;
    puVar9 = puVar9 + 1;
  }
  for (uVar6 = regEbx >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *puVar11 = *puVar10;
    puVar10 = puVar10 + 1;
    puVar11 = puVar11 + 1;
  }
  for (uVar6 = regEbx & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined1 *)puVar11 = *(undefined1 *)puVar10;
    puVar10 = (undefined4 *)((int)puVar10 + 1);
    puVar11 = (undefined4 *)((int)puVar11 + 1);
  }
  return;
}
