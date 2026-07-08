/* FUN_004fe8d0 - 0x004fe8d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall
FUN_004fe8d0(undefined4 *param_1,int param_2,int param_3,short param_4,int param_5,short param_6)

{
  char cVar1;
  byte bVar2;
  uint uVar3;
  int iVar5;
  undefined4 uVar6;
  UINT_PTR UVar7;
  int *piVar8;
  int *local_b8;
  uint local_b4;
  char local_ae [17];
  undefined1 local_9d;
  void *local_1c;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  uint uVar4;
  
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00537aeb) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  cVar1 = FUN_004fe860(param_1,&local_b8);
  piVar8 = local_b8;
  if (cVar1 == '\0') {
    FUN_004ff1a0();
    local_4 = 0;
    uVar3 = 0;
    do {
      uVar4 = uVar3;
      if (*(char *)(uVar3 + param_2) == '\0') break;
      bVar2 = (char)uVar3 + 1;
      uVar4 = (uint)bVar2;
      local_ae[uVar3] = *(char *)(uVar3 + param_2);
      uVar3 = uVar4;
    } while (bVar2 < 0x10);
    local_9d = (undefined1)uVar4;
    local_ae[uVar4] = '\0';
    FUN_005000e0();
    *(int *)(iVar5 + 0x14) = 0;
    *(undefined2 *)(iVar5 + 0x18) = 0;
    uVar6 = FUN_00504e90();
    *(undefined4 *)(iVar5 + 0x2c) = uVar6;
    local_4 = 0xffffffff;
    if (local_1c != (void *)0x0) {
      _free(local_1c);
    }
    FUN_00500790();
    FUN_00500a20();
    piVar8 = (int *)(iVar5 + 0x14);
  }
  piVar8[2] = param_3;
  *(short *)(piVar8 + 3) = param_4;
  piVar8[4] = param_5;
  *(short *)(piVar8 + 5) = param_6;
  *(undefined1 *)(piVar8 + 7) = 0;
  if ((param_3 == param_5) && (param_4 == param_6)) {
    *piVar8 = param_3;
    *(short *)(piVar8 + 1) = param_4;
  }
  else {
    *piVar8 = 0;
    *(undefined2 *)(piVar8 + 1) = 0;
  }
  local_b4 = 0;
  if (piVar8[0x21] != 0) {
    local_b8 = (int *)0x0;
    do {
      if ((uint)piVar8[0x21] <= local_b4) {
                    /* WARNING: Subroutine does not return */
        FUN_004010c0(0x80070057);
      }
      iVar5 = piVar8[0x20] + (int)local_b8;
      cVar1 = FUN_004fe110(param_1,param_2,*(undefined2 *)(iVar5 + 0xc),iVar5 + 0x10,
                           *(undefined2 *)(iVar5 + 0xe));
      if (cVar1 == '\0') {
        (**(code **)*param_1)
                  (0,param_2,*(undefined2 *)(iVar5 + 0xc),iVar5 + 0x10,*(undefined2 *)(iVar5 + 0xe),
                   iVar5);
      }
      local_b4 = local_b4 + 1;
      local_b8 = local_b8 + 0x5d4;
    } while (local_b4 < (uint)piVar8[0x21]);
  }
  if ((void *)piVar8[0x20] != (void *)0x0) {
    _free((void *)piVar8[0x20]);
    piVar8[0x20] = 0;
  }
  piVar8[0x21] = 0;
  piVar8[0x22] = 0;
  if (param_1[0xb1] == 0) {
    UVar7 = SetTimer((HWND)param_1[0xa3],0x14b,50000,(TIMERPROC)0x0);
    param_1[0xb1] = UVar7;
  }
  return;
}

