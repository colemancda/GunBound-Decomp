/* FUN_00401ce0 - 0x00401ce0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
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


int __thiscall FUN_00401ce0(int param_1,byte *param_2)

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

