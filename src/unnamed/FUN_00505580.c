/* FUN_00505580 - 0x00505580 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00505580(int param_1)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 uVar8;
  char local_100 [256];
  
  uVar2 = FUN_0050e620();
  if (uVar2 != 0xffffffff) {
    if (*(uint *)(param_1 + 0x10) <= uVar2) {
                    /* WARNING: Subroutine does not return */
      FUN_004010c0(0x80070057);
    }
    pcVar5 = (char *)(*(int *)(*(int *)(param_1 + 0xc) + uVar2 * 4) + 0x38);
    pcVar4 = pcVar5;
    if (pcVar5 != (char *)0x0) {
      do {
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
    }
    FUN_004056c0(param_1 + 0x50,pcVar5);
  }
  if (*(int *)(*(int *)(param_1 + 0x50) + -0xc) != 0) {
    iVar3 = FUN_00401bb0(&DAT_00e53e88);
    if (iVar3 == 0) {
      iVar3 = __mbsicmp(*(uchar **)(param_1 + 0x50),(uchar *)(g_clientContext + 0x23330));
      if (iVar3 != 0) {
        FUN_00402ad0(&DAT_00e53e88,&DAT_0054b460);
        goto LAB_0050566b;
      }
      pcVar4 = (char *)FUN_0043dc70(&DAT_00796eec,0xfa7);
    }
    else {
      uVar8 = *(undefined4 *)(param_1 + 0x50);
      pcVar4 = (char *)FUN_0043dc70(&DAT_00796eec,0xfa4);
      _sprintf(local_100,pcVar4,uVar8);
      pcVar4 = local_100;
    }
    FUN_00509030(&DAT_00e53c40,pcVar4);
  }
LAB_0050566b:
  if (uVar2 < *(uint *)(param_1 + 0x10)) {
    iVar3 = *(int *)(*(int *)(param_1 + 0xc) + uVar2 * 4);
    if (*(char *)(iVar3 + 4) != '\0') {
      SetWindowTextA(*(HWND *)(DAT_007934e4 + 4),&DAT_00551cb1);
    }
    puVar7 = (undefined4 *)(iVar3 + 0x38);
    for (iVar6 = 0x40; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar7 = 0;
      puVar7 = puVar7 + 1;
    }
    *(undefined4 *)(iVar3 + 0x13c) = 0;
    return;
  }
                    /* WARNING: Subroutine does not return */
  FUN_004010c0(0x80070057);
}

