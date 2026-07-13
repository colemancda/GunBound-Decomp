/* ReceiveFramedPackets - 0x004e5610 in the original binary.
 *
 * recv()s into the connection's receive buffer and splits the TCP stream
 * into length-prefixed frames (a 2-byte length header at buffer+0x230),
 * copying each complete frame into a ring of slot descriptors for the
 * packet dispatcher and compacting the residual bytes back to the front.
 * Returns true to keep reading (partial frame or would-block, WSAEWOULDBLOCK
 * 0x2733), false on a fatal framing/overflow/ring-full condition (which also
 * enqueues failure code 0x65 and resets the connection state). Called from
 * HandleSocketEvent's FD_READ branch.
 *
 * FIXED (2026-07-13): the connection object pointer arrives via EBX in the
 * original (a dropped register arg, Ghidra's `unaff_EBX` - was declared but
 * never assigned, meaning every single field access in this function read
 * garbage/uninitialized memory at runtime). HandleSocketEvent already has
 * this pointer as its own `param_1` at its sole call site but wasn't
 * passing it - promoted to an explicit parameter here and at that call
 * site. Same class of bug as HandleSocketEvent's own already-documented
 * fixes (see that file's header) and the parallel bring-up effort's other
 * dropped-register-arg fixes; this one was missed by both passes.
 *
 * Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


bool ReceiveFramedPackets(int conn)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  ushort *puVar7;

  iVar1 = recv(*(SOCKET *)(conn + 0x24),
               (char *)(*(int *)(conn + 0x4230) + 0x230 + conn),
               0x4000 - *(int *)(conn + 0x4230),0);
  if (iVar1 < 0) {
    iVar1 = WSAGetLastError();
    return iVar1 == 0x2733;
  }
  iVar1 = *(int *)(conn + 0x4230) + iVar1;
  uVar2 = (uint)*(ushort *)(conn + 0x230);
  *(int *)(conn + 0x4230) = iVar1;
  if ((int)uVar2 <= iVar1) {
    while (1 < *(int *)(conn + 0x4230)) {
      if (0x20000 < (int)(*(int *)(conn + 0x2423c) + uVar2)) {
        if ((*(int *)(conn + 0x24240 + *(int *)(conn + 0x24238) * 4) <= (int)uVar2) &&
           (*(int *)(conn + 0x24234) != *(int *)(conn + 0x24238))) {
          if ((*(int *)(conn + 0x22c) != 1) && (*(int *)(conn + 0x20) != 0)) {
            FUN_004f2da0(*(undefined4 *)(conn + 0x20),0x65,*(undefined4 *)(conn + 0x1c),0);
          }
          *(undefined4 *)(conn + 0x22c) = 0;
          return false;
        }
        *(undefined4 *)(conn + 0x2423c) = 0;
      }
      uVar4 = *(int *)(conn + 0x24234) + 1U & 0x800000ff;
      if ((int)uVar4 < 0) {
        uVar4 = (uVar4 - 1 | 0xffffff00) + 1;
      }
      if (uVar4 == *(uint *)(conn + 0x24238)) {
        if ((*(int *)(conn + 0x22c) != 1) && (*(int *)(conn + 0x20) != 0)) {
          FUN_004f2da0(*(undefined4 *)(conn + 0x20),0x65,*(undefined4 *)(conn + 0x1c),0);
        }
        *(undefined4 *)(conn + 0x22c) = 0;
        return false;
      }
      puVar5 = (undefined4 *)(conn + 0x232);
      puVar6 = (undefined4 *)(*(int *)(conn + 0x2423c) + 0x4234 + conn);
      for (uVar3 = uVar2 - 2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
      for (uVar3 = uVar2 - 2 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined1 *)puVar6 = *(undefined1 *)puVar5;
        puVar5 = (undefined4 *)((int)puVar5 + 1);
        puVar6 = (undefined4 *)((int)puVar6 + 1);
      }
      *(undefined4 *)(conn + 0x24240 + *(int *)(conn + 0x24234) * 4) =
           *(undefined4 *)(conn + 0x2423c);
      *(uint *)(conn + 0x24640 + *(int *)(conn + 0x24234) * 4) = uVar2 - 2;
      *(uint *)(conn + 0x24234) = uVar4;
      *(uint *)(conn + 0x2423c) = *(int *)(conn + 0x2423c) + (uVar2 - 2);
      puVar5 = (undefined4 *)(uVar2 + 0x230 + conn);
      puVar7 = (ushort *)(conn + 0x230);
      for (uVar4 = 0x4000 - uVar2 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined4 *)puVar7 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar7 = puVar7 + 2;
      }
      for (uVar4 = 0x4000 - uVar2 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined1 *)puVar7 = *(undefined1 *)puVar5;
        puVar5 = (undefined4 *)((int)puVar5 + 1);
        puVar7 = (ushort *)((int)puVar7 + 1);
      }
      iVar1 = *(int *)(conn + 0x4230) - uVar2;
      *(int *)(conn + 0x4230) = iVar1;
      uVar2 = (uint)*(ushort *)(conn + 0x230);
      if (iVar1 < (int)uVar2) {
        return true;
      }
    }
  }
  return true;
}

