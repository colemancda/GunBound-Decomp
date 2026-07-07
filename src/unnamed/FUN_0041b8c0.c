/* FUN_0041b8c0 - 0x0041b8c0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_0041b8c0(int param_1,char param_2,char *param_3,char *param_4,char *param_5,
                 undefined2 param_6,char param_7)

{
  char cVar1;
  undefined2 *puVar2;
  uint in_EAX;
  char *pcVar3;
  char *pcVar4;
  char *pcVar5;
  int iVar6;
  int *piVar7;
  uint uVar8;
  int iVar9;
  int extraout_EDX;
  undefined4 *puVar10;
  char *pcVar11;
  undefined2 *puVar12;
  bool bVar13;
  undefined1 local_98 [4];
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined1 local_88;
  undefined4 uStack_81;
  
  if ((param_2 == '\0') || (param_2 == '\a')) {
    pcVar3 = param_4;
    do {
      cVar1 = *pcVar3;
      pcVar3[(int)&uStack_81 + (1 - (int)param_4)] = cVar1;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    puVar10 = &uStack_81;
    do {
      pcVar3 = (char *)((int)puVar10 + 1);
      puVar10 = (undefined4 *)((int)puVar10 + 1);
    } while (*pcVar3 != '\0');
    *puVar10 = DAT_00553628;
    pcVar3 = (char *)((int)&uStack_81 + 1);
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    pcVar4 = param_5;
    pcVar11 = pcVar3 + (int)&uStack_81 + (1 - ((int)&uStack_81 + 2));
    for (uVar8 = in_EAX >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar11 = *(undefined4 *)pcVar4;
      pcVar4 = pcVar4 + 4;
      pcVar11 = pcVar11 + 4;
    }
    for (uVar8 = in_EAX & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
      *pcVar11 = *pcVar4;
      pcVar4 = pcVar4 + 1;
      pcVar11 = pcVar11 + 1;
    }
    pcVar3[(int)&uStack_81 + (in_EAX - ((int)&uStack_81 + 2)) + 1] = '\0';
    FUN_00426120((int)&uStack_81 + 1);
  }
  if (99 < *(int *)(param_1 + 0x3b980)) {
    FUN_0041b840();
  }
  if (param_3 == (char *)0x0) {
    *(undefined1 *)(*(int *)(param_1 + 0x3b980) * 9 + 0x3b984 + param_1) = 0;
  }
  else {
    puVar10 = (undefined4 *)(*(int *)(param_1 + 0x3b980) * 9 + 0x3b984 + param_1);
    *puVar10 = *(undefined4 *)param_3;
    puVar10[1] = *(undefined4 *)(param_3 + 4);
    *(char *)(puVar10 + 2) = param_3[8];
  }
  if (param_4 == (char *)0x0) {
    *(undefined1 *)(param_1 + (*(int *)(param_1 + 0x3b980) + 0x2fda) * 0x14) = 0;
  }
  else {
    iVar9 = (int)&local_94 - (int)param_4;
    do {
      cVar1 = *param_4;
      param_4[iVar9] = cVar1;
      param_4 = param_4 + 1;
    } while (cVar1 != '\0');
    puVar2 = (undefined2 *)(local_98 + 3);
    do {
      puVar12 = puVar2;
      puVar2 = (undefined2 *)((int)puVar12 + 1);
    } while (*(char *)((int)puVar12 + 1) != '\0');
    *(undefined2 *)((int)puVar12 + 1) = DAT_00553624;
    iVar9 = *(int *)(param_1 + 0x3b980);
    *(undefined1 *)((int)puVar12 + 3) = DAT_00553626;
    puVar10 = (undefined4 *)(param_1 + (iVar9 + 0x2fda) * 0x14);
    *puVar10 = local_94;
    puVar10[1] = local_90;
    puVar10[2] = local_8c;
    *(undefined1 *)(puVar10 + 3) = local_88;
  }
  if (param_3 != (char *)0x0) {
    iVar9 = 7;
    bVar13 = true;
    pcVar3 = &DAT_00551e24;
    do {
      if (iVar9 == 0) break;
      iVar9 = iVar9 + -1;
      bVar13 = *param_3 == *pcVar3;
      param_3 = param_3 + 1;
      pcVar3 = pcVar3 + 1;
    } while (bVar13);
    if (bVar13) {
      param_2 = '\x05';
      goto LAB_0041bac3;
    }
  }
  if (param_2 == '\x02') {
    cVar1 = *param_5;
    if (cVar1 == '!') {
      param_2 = '\x02';
    }
    else if (cVar1 == '@') {
      param_2 = '\n';
    }
    else if (cVar1 == '#') {
      param_2 = '\v';
    }
    else if (cVar1 == '$') {
      param_2 = '\f';
    }
    else if (cVar1 == '%') {
      param_2 = '\r';
    }
    else if (cVar1 == '^') {
      param_2 = '\x0e';
    }
    else if (cVar1 == '&') {
      param_2 = '\x0f';
    }
    else {
      if (cVar1 != '*') goto LAB_0041bac3;
      param_2 = '\x10';
    }
    in_EAX = in_EAX - 1;
  }
LAB_0041bac3:
  *(char *)(*(int *)(param_1 + 0x3b980) + 0x3c4d8 + param_1) = param_2;
  *(undefined2 *)(param_1 + 0x3f73c + *(int *)(param_1 + 0x3b980) * 2) = param_6;
  pcVar4 = (char *)(*(int *)(param_1 + 0x3b980) * 9 + 0x3b984 + param_1);
  pcVar3 = pcVar4 + 1;
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  pcVar5 = (char *)(param_1 + (*(int *)(param_1 + 0x3b980) * 5 + 0xef42) * 4);
  pcVar11 = pcVar5 + 1;
  do {
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  cVar1 = (param_7 == '\0') * '\b' + 'H';
  local_98 = (undefined1  [4])((uint)(param_7 == '\0') * 4 + 9);
  iVar6 = FUN_0041b410(pcVar4 + (int)(pcVar5 + ((2 - (int)pcVar11) - (int)pcVar3)),in_EAX,cVar1);
  iVar9 = *(int *)(param_1 + 0x3b980) + 1;
  *(int *)(param_1 + 0x3b980) = iVar9;
  if (0 < iVar6) {
    if (99 < iVar9) {
      FUN_0041b840();
      iVar6 = extraout_EDX;
    }
    *(undefined1 *)(*(int *)(param_1 + 0x3b980) * 9 + 0x3b984 + param_1) = 0;
    *(undefined1 *)(param_1 + (*(int *)(param_1 + 0x3b980) + 0x2fda) * 0x14) = 0;
    *(undefined2 *)(param_1 + 0x3f73c + *(int *)(param_1 + 0x3b980) * 2) = 0;
    *(char *)(*(int *)(param_1 + 0x3b980) + 0x3c4d8 + param_1) = param_2;
    FUN_0041b410(pcVar4 + (int)(pcVar5 + ((2 - (int)pcVar11) - (int)pcVar3)),in_EAX - iVar6,cVar1);
    if (*(int *)(param_1 + 0x3b97c) == *(int *)(param_1 + 0x3b980) - (int)local_98) {
      *(int *)(param_1 + 0x3b97c) = *(int *)(param_1 + 0x3b97c) + 1;
    }
    iVar9 = *(int *)(param_1 + 0x3b980) + 1;
    *(int *)(param_1 + 0x3b980) = iVar9;
  }
  if (*(int *)(param_1 + 0x3b97c) == (iVar9 - (int)local_98) + -1) {
    *(int *)(param_1 + 0x3b97c) = *(int *)(param_1 + 0x3b97c) + 1;
  }
  piVar7 = DAT_00e53c44;
  if (DAT_00e53c44 != (int *)0x0) {
    while( true ) {
      iVar6 = piVar7[2];
      piVar7 = (int *)*piVar7;
      if ((*(int *)(iVar6 + 0x20) == 0) &&
         (*(int *)(iVar6 + 0x24) == (-(uint)(param_7 != '\0') & 0xffffe4a7) + 0x2329)) break;
      if (piVar7 == (int *)0x0) {
        return;
      }
    }
    FUN_00505520(iVar9,local_98);
    uVar8 = FUN_0050e620();
    if (uVar8 != 0xffffffff) {
      if (*(uint *)(iVar6 + 0x10) <= uVar8) {
                    /* WARNING: Subroutine does not return */
        FUN_004010c0(0x80070057);
      }
      *(undefined4 *)(*(int *)(*(int *)(iVar6 + 0xc) + uVar8 * 4) + 0x40) =
           *(undefined4 *)(param_1 + 0x3b97c);
    }
  }
  return;
}

