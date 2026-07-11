/* FUN_00505ad0 - 0x00505ad0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00505ad0(int param_1)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 uVar8;
  
  uVar2 = Widget_FindChildIndex();
  if (uVar2 != 0xffffffff) {
    if (*(uint *)(param_1 + 0x10) <= uVar2) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    pcVar5 = (char *)(*(int *)(*(int *)(param_1 + 0xc) + uVar2 * 4) + 0x38);
    pcVar3 = pcVar5;
    if (pcVar5 != (char *)0x0) {
      do {
        cVar1 = *pcVar3;
        pcVar3 = pcVar3 + 1;
      } while (cVar1 != '\0');
    }
    FUN_004056c0(param_1 + 0x50,pcVar5);
  }
  if (*(int *)(*(int *)(param_1 + 0x50) + -0xc) != 0) {
    cVar1 = CheckChatWordFilter(*(int *)(param_1 + 0x50));
    if (cVar1 == '\x01') {
      pcVar5 = (char *)GetLocalizedString(&g_localizedStringTable,0x202);
      pcVar3 = pcVar5 + 1;
      do {
        cVar1 = *pcVar5;
        pcVar5 = pcVar5 + 1;
      } while (cVar1 != '\0');
      iVar4 = (int)pcVar5 - (int)pcVar3;
      uVar8 = 0x202;
    }
    else {
      cVar1 = FUN_00415230();
      if (cVar1 == '\0') {
        FUN_00402720(&DAT_00e53e88,param_1 + 0x90,*(undefined4 *)(param_1 + 0x50));
        goto LAB_00505bbe;
      }
      pcVar5 = (char *)GetLocalizedString(&g_localizedStringTable,0x205);
      pcVar3 = pcVar5 + 1;
      do {
        cVar1 = *pcVar5;
        pcVar5 = pcVar5 + 1;
      } while (cVar1 != '\0');
      iVar4 = (int)pcVar5 - (int)pcVar3;
      uVar8 = 0x205;
    }
    uVar8 = GetLocalizedString(&g_localizedStringTable,uVar8);
    FUN_00505900(uVar8,iVar4);
  }
LAB_00505bbe:
  if (uVar2 < *(uint *)(param_1 + 0x10)) {
    iVar4 = *(int *)(*(int *)(param_1 + 0xc) + uVar2 * 4);
    if (*(char *)(iVar4 + 4) != '\0') {
      SetWindowTextA(*(HWND *)(DAT_007934e4 + 4),&DAT_00551cb1);
    }
    puVar7 = (undefined4 *)(iVar4 + 0x38);
    for (iVar6 = 0x40; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar7 = 0;
      puVar7 = puVar7 + 1;
    }
    *(undefined4 *)(iVar4 + 0x13c) = 0;
    return;
  }
                    /* WARNING: Subroutine does not return */
  ThrowCxxException(0x80070057);
}

