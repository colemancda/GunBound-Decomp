/* FUN_00426120 - 0x00426120 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00426120(char *param_1)

{
  char cVar1;
  int in_EAX;
  char *pcVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  
  pcVar2 = param_1;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  pcVar2 = pcVar2 + (1 - (int)(param_1 + 1));
  pcVar3 = pcVar2 + *(int *)(&DAT_006aa5fc + in_EAX);
  if (0x180 < (int)pcVar3) {
    uVar4 = 0x180 - (int)(pcVar3 + -0x180);
    pcVar6 = pcVar3 + in_EAX + 0x6aa2fc;
    pcVar7 = &DAT_006aa47c + in_EAX;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar7 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar7 = pcVar7 + 1;
    }
    *(int *)(&DAT_006aa5fc + in_EAX) = *(int *)(&DAT_006aa5fc + in_EAX) - (int)(pcVar3 + -0x180);
  }
  pcVar3 = &DAT_006aa47c + in_EAX + *(int *)(&DAT_006aa5fc + in_EAX);
  for (uVar5 = (uint)pcVar2 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar3 = *(undefined4 *)param_1;
    param_1 = param_1 + 4;
    pcVar3 = pcVar3 + 4;
  }
  for (uVar5 = (uint)pcVar2 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar3 = *param_1;
    param_1 = param_1 + 1;
    pcVar3 = pcVar3 + 1;
  }
  (&DAT_006aa47b)[(int)(pcVar2 + in_EAX + *(int *)(&DAT_006aa5fc + in_EAX))] = 10;
  *(char **)(&DAT_006aa5fc + in_EAX) = pcVar2 + *(int *)(&DAT_006aa5fc + in_EAX);
  return;
}

