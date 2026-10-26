/* DrainDirectLinkActionRing - 0x00405a40 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-26), HIGH. Drains the pending battle-action/packet ring on
 * the direct-link connection context (g_directLinkConnection): walks the
 * queue between the read cursor at +0x24238 and the write cursor at
 * +0x24234, dispatching each entry by its opcode word. "Ring" is not a
 * guess: ReceiveFramedPackets.c (src/network/) - the function that fills
 * this same +0x24234/+0x24238/+0x24240 structure on the connection object -
 * already describes it in its own header as "a ring of slot descriptors
 * for the packet dispatcher", and its index arithmetic (`+1U & 0x800000ff`)
 * matches the wraparound this function's own read-side advance uses. Sole
 * caller PumpBattleActions.c:50 guards it on `g_directLinkConnection != 0`
 * and is itself the top-level per-tick drain of the battle-action queues
 * this ring feeds alongside PopDirectBattleAction/PopBroadcastBattleAction.
 *
 * DROPPED-`this` FIX (2026-07-16): the context pointer arrives in EDI (a
 * custom register convention Ghidra dropped as an uninitialised
 * `int unaff_EDI`). Recovered from disassembly: the prologue reads
 * [edi+0x2008] without ever setting EDI, and the function's single call
 * site (PumpBattleActions / FUN_004129c0 at 0x412a0a) does
 * `mov edi,[0x7934f4]` immediately before the call - i.e. EDI is
 * g_directLinkConnection, exactly the object Shutdown.c already drives through the
 * same +0x2004 -> +0x22c connection-object field. That call site already
 * guards on `g_directLinkConnection != 0`; it simply never passed the pointer.
 * Left unfixed this read a garbage EDI, so [garbage+0x2004] yielded NULL
 * and the `+0x22c` deref faulted (read of 0x22d at rebuilt 0x44b086)
 * under the stricter (Lutris) wine.
 */
#include "ghidra_types.h"


void DrainDirectLinkActionRing(int param_1)

{
  ushort *puVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  bool bVar6;

  if ((*(char *)(param_1 + 0x2008) != '\0') &&
     (*(int *)(*(int *)(param_1 + 0x2004) + 0x22c) != 3)) {
    *(undefined1 *)(param_1 + 0x2008) = 0;
    *(bool *)(param_1 + 0x2009) = *(int *)(*(int *)(param_1 + 0x2004) + 0x22c) == 2;
  }
  do {
    while( true ) {
      iVar3 = *(int *)(param_1 + 0x2004);
      iVar4 = *(int *)(iVar3 + 0x24238);
      if (iVar4 == *(int *)(iVar3 + 0x24234)) {
        return;
      }
      uVar5 = iVar4 + 1U & 0x800000ff;
      puVar1 = (ushort *)(*(int *)(iVar3 + 0x24240 + iVar4 * 4) + 0x4234 + iVar3);
      if ((int)uVar5 < 0) {
        uVar5 = (uVar5 - 1 | 0xffffff00) + 1;
      }
      *(uint *)(iVar3 + 0x24238) = uVar5;
      uVar2 = *puVar1;
      if (uVar2 < 0xa212) break;
      if ((uVar2 != 0xa221) && (uVar2 != 0xa231)) {
        bVar6 = uVar2 == 0xa241;
        goto LAB_00405af0;
      }
LAB_00405aff:
      if (puVar1[1] == 0) {
        DispatchDirectLinkMessengerPacket();
      }
    }
    if (((uVar2 == 0xa211) || (uVar2 == 0xa001)) || (uVar2 == 0xa111)) goto LAB_00405aff;
    bVar6 = uVar2 == 0xa201;
LAB_00405af0:
    if (bVar6) goto LAB_00405aff;
    DispatchDirectLinkMessengerPacket();
  } while( true );
}
