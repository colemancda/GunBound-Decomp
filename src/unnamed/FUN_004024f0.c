/* FUN_004024f0 - 0x004024f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004024f0(undefined4 param_1,char *param_2)

{
  char cVar1;
  undefined2 *puVar2;
  undefined4 in_EAX;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  char *pcVar6;
  undefined2 *puVar7;
  char *pcVar8;
  char local_80 [128];
  
  pcVar4 = (char *)(DAT_005b3484 + 0x23330);
  iVar3 = -(int)pcVar4;
  do {
    cVar1 = *pcVar4;
    pcVar4[(int)(local_80 + iVar3)] = cVar1;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  puVar2 = (undefined2 *)&stack0xffffff7f;
  do {
    puVar7 = puVar2;
    puVar2 = (undefined2 *)((int)puVar7 + 1);
  } while (*(char *)((int)puVar7 + 1) != '\0');
  *(undefined2 *)((int)puVar7 + 1) = DAT_00551e34;
  *(undefined1 *)((int)puVar7 + 3) = DAT_00551e36;
  pcVar4 = param_2;
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  pcVar8 = &stack0xffffff7f;
  do {
    pcVar6 = pcVar8 + 1;
    pcVar8 = pcVar8 + 1;
  } while (*pcVar6 != '\0');
  pcVar6 = param_2;
  for (uVar5 = (uint)((int)pcVar4 - (int)param_2) >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = (int)pcVar4 - (int)param_2 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar8 = pcVar8 + 1;
  }
  FUN_00426120(local_80);
  iVar3 = FUN_00509730();
  if (iVar3 == 0) {
    FUN_004025e0(param_1,in_EAX);
    iVar3 = FUN_00509730();
    if (iVar3 == 0) {
      return;
    }
    pcVar4 = param_2;
    do {
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    iVar3 = (int)pcVar4 - (int)(param_2 + 1);
  }
  else {
    pcVar4 = param_2;
    do {
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    iVar3 = (int)pcVar4 - (int)(param_2 + 1);
  }
  FUN_00505900(param_2,iVar3);
  return;
}

