/* CommConnectionSendOrQueue - 0x00503840 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-30 (was FUN_00503840).  The write entry point of a comm
 * engine TCP connection: send a frame now, or queue it for the FD_WRITE
 * drain. __fastcall with ECX = length (1..6000, else false), EDX = the
 * frame, one stack word = the connection, `ret 4`, returns bool.
 *
 * The connection layout is pinned by the function that empties what
 * this fills, CommEngineSend (0x4ff550, the FD_WRITE half): socket at
 * conn+8, a pending-send list at conn+0x20 (head +0x20, tail +0x24,
 * count +0x28), each node carrying its bytes at node+8 and their length
 * at node+0x1778 = 8 + 6000. Here: if the count at +0x28 is zero,
 * send() ([0x5442e4] = ws2_32!send) on conn+8 until done, true on
 * completion; any error but WSAEWOULDBLOCK (WSAGetLastError == 0x2733)
 * is false. On WSAEWOULDBLOCK, or when sends are already queued (so
 * order is kept), the frame is copied into a 6000-byte buffer with its
 * length at +0x1770 and appended through FUN_00504420 to the list at
 * conn+0x20 - which copies buffer and length into a node's +8 / +0x1778
 * and increments the count at list+8 = conn+0x28 - with the tail link
 * fixed up at +0x24. The list has the head/tail/count/free-list (+0x10)
 * shape of CommConnectionList_Erase's list.
 *
 * Callers: the CBuddy2 frame writers FUN_00502500 ([len+4][opcode]
 * [payload]) and FUN_005024a0 (a bare 4-byte [4][opcode] frame), both
 * passing the connection pointer at CBuddy2+0x1a74.
 *
 * functions.h keeps an EMPTY parameter list on purpose: FUN_005024a0's
 * port calls this with one argument (the connection), dropping the
 * length and frame it builds in the original - fixing that means giving
 * FUN_005024a0 its opcode parameter and ESI, which is outside this
 * rename. FUN_00502500's call already passes all three correctly.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

bool __fastcall CommConnectionSendOrQueue(uint param_1,char *param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  char local_1780 [6000];
  uint local_10;
  undefined4 uStack_c;
  
  uStack_c = 0x503850;
  if (((int)param_1 < 1) || (6000 < (int)param_1)) {
    return false;
  }
  if (*(int *)(param_3 + 0x28) == 0) {
    while (iVar2 = send(*(SOCKET *)(param_3 + 8),param_2,param_1,0), iVar2 != -1) {
      param_1 = param_1 - iVar2;
      param_2 = param_2 + iVar2;
      if ((int)param_1 < 1) {
        return true;
      }
    }
    iVar2 = WSAGetLastError();
    if (iVar2 != 0x2733) {
      return false;
    }
  }
  uVar1 = *(undefined4 *)(param_3 + 0x24);
  pcVar4 = local_1780;
  for (uVar3 = param_1 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)pcVar4 = *(undefined4 *)param_2;
    param_2 = param_2 + 4;
    pcVar4 = pcVar4 + 4;
  }
  for (uVar3 = param_1 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar4 = *param_2;
    param_2 = param_2 + 1;
    pcVar4 = pcVar4 + 1;
  }
  local_10 = param_1;
  iVar2 = FUN_00504420(local_1780,uVar1,0);
  if (*(int **)(param_3 + 0x24) != (int *)0x0) {
    **(int **)(param_3 + 0x24) = iVar2;
    *(int *)(param_3 + 0x24) = iVar2;
    return iVar2 != 0;
  }
  *(int *)(param_3 + 0x20) = iVar2;
  *(int *)(param_3 + 0x24) = iVar2;
  return iVar2 != 0;
}

