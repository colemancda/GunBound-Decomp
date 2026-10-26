/* ReconcileBroadcastAckState - 0x004e7740 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-26), MODERATE. Sole caller is BroadcastRingEvent, which
 * gates its own continuation on this function's return matching the mode
 * it passes in. Scans the 8 per-slot bitsets at +0x140/+0x138/+0x13c for
 * one that is active and was sent (+0x140 && +0x138) but not yet
 * acknowledged (!+0x13c); if it finds one, returns 0 ("still waiting").
 * If the +0x44de0 in-flight flag was already clear on entry, returns -1
 * ("idle, nothing was in flight"). Otherwise the scan reached all 8 slots
 * without finding an unacknowledged one, so it clears both bitsets, drops
 * the +0x44de0 flag and returns 1 ("fully acknowledged, round closed").
 *
 * "Ack" rather than the scoping pass's "retransmit" is read off an
 * external site: ProcessUdpProbeDatagram sets the exact same +0x13c bit
 * for one slot specifically when it matches an incoming reply against a
 * sequence number it had sent - i.e. on receiving a real acknowledgement
 * - and only then calls into this chain. SendBroadcastEventToSlot's own
 * header separately describes +0x13c as "sent via TCP" because that is
 * the only way its own body ever sets it (TCP delivery needs no separate
 * ack); both descriptions are the same bit from two different callers'
 * point of view, and this function's role - finalizing the round once
 * every active, once-sent slot's delivery is settled by either path - is
 * a confirmation gate, not a resend. It performs no send of its own.
 */
#include "ghidra_types.h"


undefined4 ReconcileBroadcastAckState(int regEsi)

{
  LPCRITICAL_SECTION lpCriticalSection;
  int iVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  
  if (*(int *)(regEsi + 0x44de0) == 0) {
    return 0xffffffff;
  }
  lpCriticalSection = (LPCRITICAL_SECTION)(regEsi + 0x17c);
  EnterCriticalSection(lpCriticalSection);
  uVar3 = 0;
  bVar4 = true;
  while( true ) {
    if (!bVar4) {
                    /* WARNING: Subroutine does not return */
      Bitset_ThrowInvalidPosition();
    }
    uVar2 = 1 << ((byte)uVar3 & 0x1f);
    iVar1 = (uVar3 >> 5) * 4;
    if ((((*(uint *)(iVar1 + 0x140 + regEsi) & uVar2) != 0) &&
        ((*(uint *)(iVar1 + 0x138 + regEsi) & uVar2) != 0)) &&
       ((*(uint *)(iVar1 + 0x13c + regEsi) & uVar2) == 0)) break;
    uVar3 = uVar3 + 1;
    bVar4 = uVar3 < 8;
    if (7 < (int)uVar3) {
      *(undefined4 *)(regEsi + 0x13c) = 0;
      *(undefined4 *)(regEsi + 0x138) = 0;
      InterlockedExchange((LONG *)(regEsi + 0x44de0),0);
      LeaveCriticalSection(lpCriticalSection);
      return 1;
    }
  }
  LeaveCriticalSection(lpCriticalSection);
  return 0;
}

