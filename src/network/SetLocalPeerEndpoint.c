/* SetLocalPeerEndpoint - 0x004e73e0 in the original binary.
 *
 * RENAMED (2026-07-19) from FUN_004e73e0. Fills in the LOCAL player's peer
 * endpoint inside the broadcast/replay context: the loopback address
 * 127.0.0.1 at ctx+0x150 (stored as the network-order dword 0x0100007f), the
 * UDP port htons(0x20ab) at +0x158, `slot` at +0x15a, a -1 handle at +0x154,
 * and the player's display name copied to +0x15d. This is the entry the
 * peer-to-peer battle transport later sends to; the loopback address is what
 * the original writes for the local player specifically.
 */
/* DROPPED-REGISTER FIX (2026-07-19): TWO dropped register args - ESI (the
 * context object, all writes are ESI-relative) and EDI (the source name
 * string copied to ESI+0x15d). The port read both uninitialised and faulted
 * writing ESI+0x150 on the join->lobby path. From the sole caller
 * (WriteReplayEventRecord/0x4104f0 at 0x410e46/0x410f42): ESI = &g_replayContext
 * (`mov esi,0xe55ce0`), and EDI = the processed slot's 13-byte name record
 * inside it, `lea ecx,[edx+esi+0x41445]` with edx = slot*0xd (so
 * &g_replayContext + slot*0xd + 0x41445). Sets up the local player's own P2P
 * address (127.0.0.1:0x20ab) + name. Promoted to explicit parameters. */
#include "ghidra_types.h"


void SetLocalPeerEndpoint(int slot,int ctx,char *nameRec)

{
  char cVar1;
  u_short uVar2;
  int iVar3;
  int unaff_ESI = ctx;
  char *unaff_EDI = nameRec;
  
  *(undefined4 *)(unaff_ESI + 0x150) = 0x100007f;
  uVar2 = htons(0x20ab);
  *(u_short *)(unaff_ESI + 0x158) = uVar2;
  *(undefined2 *)(unaff_ESI + 0x15a) = slot;
  *(undefined4 *)(unaff_ESI + 0x154) = 0xffffffff;
  iVar3 = (unaff_ESI + 0x15d) - (int)unaff_EDI;
  do {
    cVar1 = *unaff_EDI;
    unaff_EDI[iVar3] = cVar1;
    unaff_EDI = unaff_EDI + 1;
  } while (cVar1 != '\0');
  return;
}

