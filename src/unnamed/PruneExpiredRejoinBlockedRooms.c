/* PruneExpiredRejoinBlockedRooms - 0x00422f70 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00422f70 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. Evidence from outside the body: Called once
 * per GameTick under the main lock. It walks the list built by
 * AddRejoinBlockedRoom (0x422f10; three parallel 0x40 entry arrays at ctx
 * + 0x5f2f58/+0x5f3058/+0x5f3158, count at +0x5f3258) and for each entry
 * whose two keys are not -1 and whose expiry in the third array is older
 * than GetTickCount() / 1000 shifts the remaining entries of all three
 * arrays down one slot and decrements the count. LIKELY: the pairing with
 * the adder and the readers SendJoinRoomChecked /
 * EnterRoomNumberDialog_SubmitRoomNumber is solid, the purpose of the list
 * is inferred from those.
 */
#include "ghidra_types.h"


void PruneExpiredRejoinBlockedRooms(int param_1)

{
  int iVar1;
  DWORD DVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  int *piVar8;
  
  iVar1 = param_1;
  DVar2 = GetTickCount();
  piVar6 = (int *)(&DAT_005f3258 + param_1);
  param_1 = 0;
  if (0 < *piVar6) {
    piVar6 = (int *)(&DAT_005f2f58 + iVar1);
    do {
      if (((*piVar6 != -1) && (piVar6[0x40] != -1)) && (piVar6[0x80] < (int)(DVar2 / 1000))) {
        uVar3 = 0x3f - param_1;
        piVar8 = piVar6;
        piVar7 = piVar6;
        for (uVar4 = uVar3 & 0x3fffffff; piVar7 = piVar7 + 1, uVar4 != 0; uVar4 = uVar4 - 1) {
          *piVar8 = *piVar7;
          piVar8 = piVar8 + 1;
        }
        for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
          *(char *)piVar8 = (char)*piVar7;
          piVar7 = (int *)((int)piVar7 + 1);
          piVar8 = (int *)((int)piVar8 + 1);
        }
        piVar7 = piVar6 + 0x41;
        piVar8 = piVar6 + 0x40;
        for (uVar4 = uVar3 & 0x3fffffff; uVar4 != 0; uVar4 = uVar4 - 1) {
          *piVar8 = *piVar7;
          piVar7 = piVar7 + 1;
          piVar8 = piVar8 + 1;
        }
        for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
          *(char *)piVar8 = (char)*piVar7;
          piVar7 = (int *)((int)piVar7 + 1);
          piVar8 = (int *)((int)piVar8 + 1);
        }
        piVar7 = piVar6 + 0x81;
        piVar8 = piVar6 + 0x80;
        for (uVar3 = uVar3 & 0x3fffffff; uVar3 != 0; uVar3 = uVar3 - 1) {
          *piVar8 = *piVar7;
          piVar7 = piVar7 + 1;
          piVar8 = piVar8 + 1;
        }
        for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
          *(char *)piVar8 = (char)*piVar7;
          piVar7 = (int *)((int)piVar7 + 1);
          piVar8 = (int *)((int)piVar8 + 1);
        }
        *(int *)(&DAT_005f3258 + iVar1) = *(int *)(&DAT_005f3258 + iVar1) + -1;
      }
      param_1 = param_1 + 1;
      piVar6 = piVar6 + 1;
    } while (param_1 < *(int *)(&DAT_005f3258 + iVar1));
  }
  return;
}

