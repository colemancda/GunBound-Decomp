/* ResendUnackedBroadcastDatagrams - 0x004e6b90 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (batch 40), MODERATE. Re-sends the last datagram of each slot.
 * Under the context's critical section (+0x17c) it walks the eight slots;
 * for a slot whose bitsets mark it active (+0x140) and already sent (+0x138)
 * but not yet acknowledged (+0x13c clear) and whose byte at +0x454e4 is not
 * 1, it re-issues SendUdpDatagram on the saved datagram at
 * +0x40bd8 + slot * 0x200 (first short = length) to the slot's address and,
 * when present, its second address. A zero-length saved entry just sets the
 * +0x13c bit instead.
 *
 * External evidence: the saved datagrams are written by BroadcastRingEvent
 * (0x4e77e0: a 0x80-dword copy of the packet it just sent into
 * +0x40bd8 + slot * 0x200, right after the SendUdpDatagram fan-out), and the
 * +0x13c bit is the acknowledgement bit ProcessUdpProbeDatagram sets on a
 * matching reply (see ReconcileBroadcastAckState). The sole caller,
 * UdpProbeWorkerThread (call at 0x4e6ade), invokes it on a timer whose
 * interval is the value at +0x4523c, while the +0x44de0 in-flight flag is
 * 1, after bumping the round
 * counter +0x44de4 and only while that counter is below 0xb. Those are
 * BROADCAST-round datagrams, not the login probe datagram (which
 * UdpProbeWorkerThread re-sends separately from +0x4520c).
 *
 * ESI RECOVERED: the context arrives in ESI, which the caller sets once
 * (mov esi,ecx at 0x4e677d, never reassigned) and is its param_1; it is now
 * the explicit parameter unaff_ESI.
 */
#include "ghidra_types.h"


void ResendUnackedBroadcastDatagrams(int unaff_ESI)

{
  uint *puVar1;
  undefined1 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  short *psVar7;
  bool bVar8;
  int *local_8;
  
  EnterCriticalSection((LPCRITICAL_SECTION)(unaff_ESI + 0x17c));
  uVar6 = 0;
  local_8 = (int *)(unaff_ESI + 0x38);
  psVar7 = (short *)(unaff_ESI + 0x40bd8);
  iVar5 = unaff_ESI + 0x58;
  bVar8 = true;
  do {
    if (!bVar8) {
                    /* WARNING: Subroutine does not return */
      Bitset_ThrowInvalidPosition();
    }
    uVar4 = 1 << ((byte)uVar6 & 0x1f);
    iVar3 = (uVar6 >> 5) * 4;
    if (((((*(uint *)(iVar3 + 0x13c + unaff_ESI) & uVar4) == 0) &&
         ((*(uint *)(iVar3 + 0x140 + unaff_ESI) & uVar4) != 0)) &&
        ((*(uint *)(iVar3 + 0x138 + unaff_ESI) & uVar4) != 0)) &&
       (*(char *)(unaff_ESI + 0x454e4 + uVar6) != '\x01')) {
      if (*psVar7 == 0) {
        puVar1 = (uint *)(iVar3 + 0x13c + unaff_ESI);
        *puVar1 = *puVar1 | uVar4;
      }
      else {
        uVar2 = *(undefined1 *)((int)psVar7 + 7);
        *(short *)(iVar5 + 0x4522c) = psVar7[1];
        *(undefined1 *)(unaff_ESI + 0x45294 + uVar6) = uVar2;
        SendUdpDatagram(*(int *)(unaff_ESI + 0x18 + uVar6 * 4),(int)*(short *)iVar5,(char *)psVar7,
                        (int)*psVar7,unaff_ESI);
        if (*local_8 != -1) {
          SendUdpDatagram(*local_8,(int)*(short *)(iVar5 + 0x10),(char *)psVar7,(int)*psVar7,
                          unaff_ESI);
        }
      }
    }
    uVar6 = uVar6 + 1;
    local_8 = local_8 + 1;
    iVar5 = iVar5 + 2;
    psVar7 = psVar7 + 0x100;
    bVar8 = uVar6 < 8;
  } while ((int)uVar6 < 8);
  LeaveCriticalSection((LPCRITICAL_SECTION)(unaff_ESI + 0x17c));
  return;
}

