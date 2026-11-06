/* SortPlayerSpawnEntries - 0x004ccc60 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (CERTAIN on the arm, LIKELY on the sort's purpose). Its only caller
 * is the GB_ACT_PLAYER_SPAWN (0x8408) arm of State11_InBattle_ProcessBattleAction,
 * which appends one record to four parallel int arrays (param_1+0x8a0,
 * +0xaa0, +0xca0, +0xea0; count at param_1+0x89c, Ghidra index 0x227) and
 * then calls this function before incrementing the count. The array bases
 * and the count cell are exactly the arm's stores (index 0x228, 0x2a8,
 * 0x328, 0x3a8 times 4), so this sorts the spawn table the arm builds. Same
 * body as SortHitLogEntries at different offsets: exchange sort ascending
 * on the first array, swapping the other three in lockstep. Original ends
 * in ret 4, so it is declared __stdcall here to match.
 */
#include "ghidra_types.h"


void __stdcall SortPlayerSpawnEntries(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int iVar6;
  
  iVar3 = param_1;
  iVar6 = *(int *)(param_1 + 0x89c);
  param_1 = 0;
  if (iVar6 != 1 && -1 < iVar6 + -1) {
    piVar5 = (int *)(iVar3 + 0xaa0);
    do {
      if (param_1 < iVar6) {
        piVar1 = piVar5 + -0x80;
        piVar4 = piVar1;
        iVar6 = param_1;
        do {
          iVar2 = *piVar1;
          if (*piVar4 < iVar2) {
            *piVar1 = *piVar4;
            *piVar4 = iVar2;
            iVar2 = *piVar5;
            *piVar5 = piVar4[0x80];
            piVar4[0x80] = iVar2;
            iVar2 = piVar5[0x80];
            piVar5[0x80] = piVar4[0x100];
            piVar4[0x100] = iVar2;
            iVar2 = piVar5[0x100];
            piVar5[0x100] = piVar4[0x180];
            piVar4[0x180] = iVar2;
          }
          iVar6 = iVar6 + 1;
          piVar4 = piVar4 + 1;
        } while (iVar6 < *(int *)(iVar3 + 0x89c));
      }
      iVar6 = *(int *)(iVar3 + 0x89c);
      param_1 = param_1 + 1;
      piVar5 = piVar5 + 1;
    } while (param_1 < iVar6 + -1);
  }
  return;
}

