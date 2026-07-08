/* FUN_004e3d60 - 0x004e3d60 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e3d60(int param_1,char *param_2)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *puVar4;
  char *in_EAX;
  char *pcVar5;
  int iVar6;
  void *pvVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  int iVar11;
  bool bVar12;
  char local_100 [4];
  undefined1 local_fc [123];
  undefined4 uStack_81;
  undefined1 local_7c [124];
  
  iVar11 = -(int)in_EAX;
  do {
    cVar1 = *in_EAX;
    in_EAX[(int)(local_100 + iVar11)] = cVar1;
    in_EAX = in_EAX + 1;
  } while (cVar1 != '\0');
  puVar9 = (undefined4 *)&stack0xfffffeff;
  do {
    puVar10 = puVar9;
    puVar9 = (undefined4 *)((int)puVar10 + 1);
  } while (*(char *)((int)puVar10 + 1) != '\0');
  *(undefined4 *)((int)puVar10 + 1) = DAT_005554f8;
  *(undefined1 *)((int)puVar10 + 5) = DAT_005554fc;
  pcVar5 = param_2;
  do {
    cVar1 = *pcVar5;
    pcVar5[(int)&uStack_81 + (1 - (int)param_2)] = cVar1;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  puVar9 = &uStack_81;
  do {
    puVar10 = puVar9;
    puVar9 = (undefined4 *)((int)puVar10 + 1);
  } while (*(char *)((int)puVar10 + 1) != '\0');
  *(undefined4 *)((int)puVar10 + 1) = DAT_005554f8;
  *(undefined1 *)((int)puVar10 + 5) = DAT_005554fc;
  puVar9 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar2 = puVar9[1];
  if (uVar2 < 0xea61) {
LAB_004e3de1:
    if (uVar2 != 60000) goto code_r0x004e3de3;
    puVar10 = (undefined4 *)puVar9[4];
    while (puVar10 != puVar9) {
      puVar4 = (undefined4 *)*puVar10;
      puVar10 = (undefined4 *)puVar10[4];
      (*(code *)*puVar4)(1);
    }
    puVar9[3] = puVar9;
    puVar9[4] = puVar9;
  }
LAB_004e3e15:
  FUN_004f18c0(&DAT_00ea0e18,60000,0);
  if (*(char *)(g_clientContext + 0x45578) == '\0') {
    FUN_004f18c0(&DAT_00ea0e18,60000,1);
  }
  iVar8 = g_clientContext;
  iVar11 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar2 = *(uint *)(iVar11 + 4);
  while (uVar2 < 0xea61) {
    if (uVar2 == 60000) {
      iVar11 = *(int *)(iVar11 + 0x10);
      bVar12 = true;
      if (*(int *)(iVar11 + 8) != 0) goto LAB_004e3e8f;
      goto LAB_004e3e83;
    }
    iVar11 = *(int *)(iVar11 + 0x1c);
    uVar2 = *(uint *)(iVar11 + 4);
  }
  iVar11 = 0;
  goto LAB_004e3e95;
code_r0x004e3de3:
  puVar9 = (undefined4 *)puVar9[7];
  uVar2 = puVar9[1];
  if (60000 < uVar2) goto LAB_004e3e15;
  goto LAB_004e3de1;
  while( true ) {
    iVar11 = *(int *)(iVar11 + 0x10);
    bVar12 = *(int *)(iVar11 + 8) == 0;
    if (!bVar12) break;
LAB_004e3e83:
    if (bVar12) goto LAB_004e3e95;
  }
LAB_004e3e8f:
  iVar11 = 0;
LAB_004e3e95:
  iVar6 = *(int *)(iVar11 + 0x20);
  *(int *)(param_1 + 0x18) = iVar6;
  *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(iVar11 + 0x24);
  iVar6 = iVar6 / 2;
  *(int *)(param_1 + 8) = iVar6;
  *(int *)(param_1 + 0x10) = iVar6;
  iVar6 = *(int *)(param_1 + 0x1c) / 2;
  *(int *)(param_1 + 0xc) = iVar6;
  *(int *)(param_1 + 0x14) = iVar6;
  if (*(byte *)(iVar8 + 0x45578) != 0) {
    _sprintf(local_100,s_event_d1800_img_00557248,(uint)*(byte *)(iVar8 + 0x45578));
    FUN_004f18c0(&DAT_00ea0e18,60000,1);
  }
  pvVar7 = operator_new(*(int *)(iVar11 + 0x3c) << 1);
  iVar11 = g_clientContext;
  *(void **)(param_1 + 0x3c) = pvVar7;
  puVar9 = (undefined4 *)(param_1 + 0x51);
  for (iVar8 = 0x200; iVar8 != 0; iVar8 = iVar8 + -1) {
    *puVar9 = 0;
    puVar9 = puVar9 + 1;
  }
  cVar1 = *(char *)(iVar11 + 0x45578);
  iVar11 = 1;
  while( true ) {
    if (cVar1 != '\0') {
      return;
    }
    puVar9 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar3 = puVar9[1];
    uVar2 = iVar11 + 60000;
    if (uVar3 <= uVar2) break;
LAB_004e3f75:
    _sprintf((char *)((int)&uStack_81 + 1),s__s_d_img_0055723c,param_2,iVar11);
    iVar8 = FUN_004f1790(&DAT_00ea0e18,uVar2);
    if (iVar8 == 0) {
      return;
    }
    _sprintf(local_100,&DAT_00557234,param_2,iVar11);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    FUN_004e4f50(param_1,iVar11,local_100);
    cVar1 = *(char *)(g_clientContext + 0x45578);
    iVar11 = iVar11 + 1;
  }
LAB_004e3f4a:
  if (uVar3 != uVar2) goto code_r0x004e3f4c;
  puVar10 = (undefined4 *)puVar9[4];
  while (puVar10 != puVar9) {
    puVar4 = (undefined4 *)*puVar10;
    puVar10 = (undefined4 *)puVar10[4];
    (*(code *)*puVar4)(1);
  }
  puVar9[3] = puVar9;
  puVar9[4] = puVar9;
  goto LAB_004e3f75;
code_r0x004e3f4c:
  puVar9 = (undefined4 *)puVar9[7];
  uVar3 = puVar9[1];
  if (uVar2 < uVar3) goto LAB_004e3f75;
  goto LAB_004e3f4a;
}

