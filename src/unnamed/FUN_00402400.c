/* FUN_00402400 - 0x00402400 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00402400(undefined4 param_1,char *param_2,uint param_3)

{
  char cVar1;
  undefined2 *puVar2;
  char *in_EAX;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  char *pcVar6;
  undefined2 *puVar7;
  char *pcVar8;
  char local_200 [512];
  
  iVar3 = FUN_004259d0(in_EAX);
  if (iVar3 == -1) {
    pcVar4 = in_EAX;
    do {
      cVar1 = *pcVar4;
      pcVar4[(int)(local_200 + -(int)in_EAX)] = cVar1;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    puVar2 = (undefined2 *)&stack0xfffffdff;
    do {
      puVar7 = puVar2;
      puVar2 = (undefined2 *)((int)puVar7 + 1);
    } while (*(char *)((int)puVar7 + 1) != '\0');
    *(undefined2 *)((int)puVar7 + 1) = DAT_00551e34;
    pcVar4 = local_200;
    *(undefined1 *)((int)puVar7 + 3) = DAT_00551e36;
    do {
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    pcVar6 = param_2;
    pcVar8 = pcVar4 + (int)(local_200 + -(int)(local_200 + 1));
    for (uVar5 = param_3 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar8 = pcVar8 + 4;
    }
    for (uVar5 = param_3 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar8 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar8 = pcVar8 + 1;
    }
    pcVar4[(int)(local_200 + (param_3 - (int)(local_200 + 1)))] = '\0';
    FUN_00426120(local_200);
    iVar3 = FUN_00509730();
    if (iVar3 == 0) {
      FUN_004025e0(param_1,in_EAX);
      iVar3 = FUN_00509730();
      if (iVar3 == 0) {
        return;
      }
    }
    FUN_00505900(param_2,param_3);
  }
  return;
}

