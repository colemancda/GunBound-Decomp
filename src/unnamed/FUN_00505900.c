/* FUN_00505900 - 0x00505900 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Type propagation algorithm not settling */

void __fastcall FUN_00505900(int param_1,char *param_2,char *param_3,uint param_4)

{
  char cVar1;
  undefined2 *puVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  undefined4 *puVar8;
  undefined2 *puVar9;
  undefined4 *puVar10;
  undefined1 local_2fa8 [3];
  undefined1 auStack_2fa5 [3996];
  undefined2 uStack_2009;
  char local_2006 [8186];
  undefined4 uStack_c;
  
  uStack_c = 0x505910;
  local_2fa8[0] = 0;
  puVar8 = (undefined4 *)((int)local_2fa8 + 1);
  for (iVar5 = 999; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar8 = 0;
    puVar8 = puVar8 + 1;
  }
  *(undefined2 *)puVar8 = 0;
  *(undefined1 *)((int)puVar8 + 2) = 0;
  pcVar3 = param_2;
  do {
    cVar1 = *pcVar3;
    pcVar3[(int)&uStack_2009 + (1 - (int)param_2)] = cVar1;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  puVar2 = &uStack_2009;
  do {
    puVar9 = puVar2;
    puVar2 = (undefined2 *)((int)puVar9 + 1);
  } while (*(char *)((int)puVar9 + 1) != '\0');
  *(undefined2 *)((int)puVar9 + 1) = DAT_00553624;
  *(undefined1 *)((int)puVar9 + 3) = DAT_00553626;
  pcVar3 = param_2;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  uVar6 = ((int)param_4 < 0) - 1 & param_4;
  pcVar3 = pcVar3 + (int)(local_2006 + -(int)(param_2 + 1));
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar3 = *(undefined4 *)param_3;
    param_3 = param_3 + 4;
    pcVar3 = pcVar3 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar3 = *param_3;
    param_3 = param_3 + 1;
    pcVar3 = pcVar3 + 1;
  }
  pcVar3 = param_2 + 1;
  do {
    cVar1 = *param_2;
    param_2 = param_2 + 1;
  } while (cVar1 != '\0');
  param_2[(int)(local_2006 + (param_4 - (int)pcVar3))] = '\0';
  iVar4 = RenderWrappedText(local_2fa8,(int)&uStack_2009 + 1,0x28,0x22,4000,0);
  iVar5 = *(int *)(param_1 + 0x104c) + iVar4;
  if (100 < iVar5) {
    iVar5 = iVar5 + -100;
    uVar7 = (100 - iVar5) * 0x28;
    puVar8 = (undefined4 *)(param_1 + 0xa8 + iVar5 * 0x28);
    puVar10 = (undefined4 *)(param_1 + 0xa8);
    for (uVar7 = (((int)uVar7 < 0) - 1 & uVar7) >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *puVar10 = *puVar8;
      puVar8 = puVar8 + 1;
      puVar10 = puVar10 + 1;
    }
    for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
      *(undefined1 *)puVar10 = *(undefined1 *)puVar8;
      puVar8 = (undefined4 *)((int)puVar8 + 1);
      puVar10 = (undefined4 *)((int)puVar10 + 1);
    }
    *(int *)(param_1 + 0x104c) = 100 - iVar4;
  }
  puVar8 = (undefined4 *)local_2fa8;
  puVar10 = (undefined4 *)(param_1 + 0xa8 + *(int *)(param_1 + 0x104c) * 0x28);
  for (uVar7 = ((iVar4 * 0x28 < 0) - 1 & iVar4 * 0x28) >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *puVar10 = *puVar8;
    puVar8 = puVar8 + 1;
    puVar10 = puVar10 + 1;
  }
  for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
    *(undefined1 *)puVar10 = *(undefined1 *)puVar8;
    puVar8 = (undefined4 *)((int)puVar8 + 1);
    puVar10 = (undefined4 *)((int)puVar10 + 1);
  }
  iVar5 = *(int *)(param_1 + 0x104c) + iVar4;
  *(int *)(param_1 + 0x104c) = iVar5;
  if (*(int *)(param_1 + 0x1048) == (iVar5 - iVar4) + -0xf) {
    *(int *)(param_1 + 0x1048) = *(int *)(param_1 + 0x1048) + iVar4;
  }
  Widget_SetChildRange(iVar5,0xe);
  uVar7 = Widget_FindChildIndex();
  if (uVar7 != 0xffffffff) {
    if (*(uint *)(param_1 + 0x10) <= uVar7) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    *(undefined4 *)(*(int *)(*(int *)(param_1 + 0xc) + uVar7 * 4) + 0x40) =
         *(undefined4 *)(param_1 + 0x1048);
  }
  return;
}

