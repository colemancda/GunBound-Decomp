/* FUN_00507660 - 0x00507660 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_00507660(int param_1,int param_2,uint param_3,undefined4 param_4)

{
  int *piVar1;
  int iVar2;
  char cVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  uint uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_005407d8) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  (**(code **)(DAT_005b1444 + 0xc))();
  puVar5 = puVar4 + 4;
  uStack_4 = 0;
  if (param_2 == 0) {
    if ((param_3 < 9) && (*(uint *)(g_clientContext + 0x41340) != param_3)) {
      FUN_00507cc0(0,*(uint *)(g_clientContext + 0x41340));
      iVar2 = DAT_007934e8;
      *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
      *(undefined2 *)(iVar2 + 0x4d4) = 0x2000;
      *(undefined2 *)(iVar2 + 0x4d6) = (undefined2)param_3;
      *(int *)(iVar2 + 0x44d0) = *(int *)(iVar2 + 0x44d0) + 2;
      FUN_004d2680();
    }
  }
  else if (param_2 == 0x1000) {
    uVar6 = FUN_0050e620();
    if (uVar6 != 0xffffffff) {
      cVar3 = PacketChecksumNotEquals(g_clientContext + 0x449c4,1);
      if (cVar3 != '\0') {
        if (*(uint *)(param_1 + 0x10) <= uVar6) {
                    /* WARNING: Subroutine does not return */
          FUN_004010c0(0x80070057);
        }
        FUN_004055b0();
        if ((puVar4[1] != 0) && (cVar3 = FUN_004218c0(g_clientContext,puVar5), cVar3 == '\0')) {
          cVar3 = FUN_00415b00(puVar5);
          if (cVar3 == '\x01') {
            iVar2 = *(int *)g_gameStateVTableArray[3];
            uVar9 = 6;
            uVar8 = 2;
            uVar7 = GetLocalizedString(&DAT_00796eec,0x202);
            (**(code **)(iVar2 + 0x28))(uVar7,uVar8,uVar9);
          }
          else {
            cVar3 = FUN_00415230();
            iVar2 = DAT_007934e8;
            if (cVar3 == '\0') {
              *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
              *(undefined2 *)(iVar2 + 0x4d4) = 0x2010;
              *(char *)(iVar2 + 0x4d6) = (char)puVar4[1];
              *(int *)(iVar2 + 0x44d0) = *(int *)(iVar2 + 0x44d0) + 1;
              FUN_004d2530(puVar5);
              FUN_004d25e0();
              FUN_004d2680();
              FUN_00425700();
            }
            else {
              iVar2 = *(int *)g_gameStateVTableArray[3];
              uVar9 = 6;
              uVar8 = 2;
              uVar7 = GetLocalizedString(&DAT_00796eec,0x205);
              (**(code **)(iVar2 + 0x28))(uVar7,uVar8,uVar9);
            }
          }
        }
      }
      if (*(uint *)(param_1 + 0x10) <= uVar6) {
                    /* WARNING: Subroutine does not return */
        FUN_004010c0(0x80070057);
      }
      FUN_00506f30();
    }
  }
  else if ((param_2 == 0x2000) && (param_3 == 0)) {
    *(undefined4 *)(g_clientContext + 0x3b97c) = param_4;
  }
  FUN_0050eb10(param_2,param_3,param_4);
  uStack_4 = 0xffffffff;
  piVar1 = puVar4 + 3;
  LOCK();
  iVar2 = *piVar1;
  *piVar1 = *piVar1 + -1;
  UNLOCK();
  if (iVar2 == 1 || iVar2 + -1 < 0) {
    (**(code **)(*(int *)*puVar4 + 4))(puVar4);
  }
  return;
}

