/* SortHitLogEntries - 0x004ccbb0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (CERTAIN on the arm, LIKELY on the sort's purpose). Its only caller
 * is the GB_ACT_HIT_LOG (0x8404) arm of State11_InBattle_ProcessBattleAction,
 * which appends one record to four parallel int arrays of 128 entries
 * (param_1+0x9c, +0x29c, +0x49c, +0x69c; the count is param_1+0x98, the
 * Ghidra index 0x26) and then calls this function before incrementing the
 * count. The four array bases here are exactly the arm's stores (index 0x27,
 * 0xa7, 0x127, 0x1a7 times 4) and the count cell is the arm's [0x26], so the
 * sort works on the hit-log table the arm builds. It is an exchange sort on
 * the first array (ascending), swapping the other three arrays in lockstep.
 * The sort loop covers the count as it stood before the new record is
 * counted. Original ends in ret 4 (callee pops its one stack argument), so
 * it is declared __stdcall here to match.
 */
#include "ghidra_types.h"


void __stdcall SortHitLogEntries(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int iVar6;
  
  iVar3 = param_1;
  iVar6 = *(int *)(param_1 + 0x98);
  param_1 = 0;
  if (iVar6 != 1 && -1 < iVar6 + -1) {
    piVar5 = (int *)(iVar3 + 0x29c);
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
        } while (iVar6 < *(int *)(iVar3 + 0x98));
      }
      iVar6 = *(int *)(iVar3 + 0x98);
      param_1 = param_1 + 1;
      piVar5 = piVar5 + 1;
    } while (param_1 < iVar6 + -1);
  }
  return;
}

