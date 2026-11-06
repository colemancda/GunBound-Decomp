/* FindDirectLinkBuddyGroupIndex - 0x00401ce0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (LIKELY on the noun "group", see AddDirectLinkBuddyGroupName):
 * it is a linear search of the table AddDirectLinkBuddyGroupName appends
 * to - 0x18-byte records from container + 0xc, count at +0xc0c - returning
 * the matching slot or -1 (`or eax,-1`, ret 4). Its only caller is the
 * 0xa2f0 arm of DispatchDirectLinkMessengerPacket (call at 0x4120f2), which
 * passes ECX = &DAT_00e53e88 and the 18-char name from the payload, and
 * feeds the result straight into UpsertDirectLinkBuddyNode as its 4th
 * argument, the same slot the 0xa001 bulk-fill passes its outer loop
 * counter for. The compare is case-sensitive (byte-pair strcmp inlined).
 * The port's stack/ECX placement is as described above and unchanged.
 *
 * ARGUMENTS RE-SLOTTED.  `ret 4` gives one stack argument, so param_1 is ECX
 * and param_2 is the push.  ECX is &DAT_00e53e88 at the sole call site, and
 * the body reads it as `[param_1 + 0xc0c]` -- inside that object's confirmed
 * 0xf28 extent, so the placement is corroborated by the size someone else
 * established for a different reason.
 *
 * The port passed its one argument (&local_120) as param_1, which is the
 * right value in the wrong slot: it belongs in param_2.
 */
#include "ghidra_types.h"


int __thiscall FindDirectLinkBuddyGroupIndex(int param_1,byte *param_2)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  byte *pbVar5;
  int iVar6;
  bool bVar7;
  
  iVar6 = 0;
  if (0 < *(int *)(param_1 + 0xc0c)) {
    pbVar2 = (byte *)(param_1 + 0xc);
    pbVar5 = param_2;
    pbVar4 = pbVar2;
LAB_00401d00:
    do {
      bVar1 = *pbVar2;
      bVar7 = bVar1 < *pbVar5;
      if (bVar1 == *pbVar5) {
        if (bVar1 != 0) {
          bVar1 = pbVar2[1];
          bVar7 = bVar1 < pbVar5[1];
          if (bVar1 != pbVar5[1]) goto LAB_00401d24;
          pbVar2 = pbVar2 + 2;
          pbVar5 = pbVar5 + 2;
          if (bVar1 != 0) goto LAB_00401d00;
        }
        iVar3 = 0;
      }
      else {
LAB_00401d24:
        iVar3 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
      }
      if (iVar3 == 0) {
        return iVar6;
      }
      iVar6 = iVar6 + 1;
      pbVar2 = pbVar4 + 0x18;
      pbVar5 = param_2;
      pbVar4 = pbVar2;
    } while (iVar6 < *(int *)(param_1 + 0xc0c));
  }
  return -1;
}

