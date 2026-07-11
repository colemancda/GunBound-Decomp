/* FUN_004d7b20 - 0x004d7b20 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004d7b20(int param_1)

{
  short sVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  
  FUN_004db720();
  if (-1 < *(int *)(param_1 + 0x628)) {
    *(int *)(param_1 + 0x628) = *(int *)(param_1 + 0x628) + -1;
  }
  if (-1 < *(int *)(param_1 + 0x4d4)) {
    *(int *)(param_1 + 0x4d4) = *(int *)(param_1 + 0x4d4) + -1;
  }
  iVar3 = FUN_004dc570();
  if ((iVar3 == -1) || (DAT_00793522 != '\0')) {
    FUN_00509700();
    *(undefined2 *)(param_1 + 0x6b4) = 0;
    *(undefined4 *)(param_1 + 0x6b8) = 0xffffffff;
  }
  else {
    iVar3 = iVar3 + *(int *)(param_1 + 0x620) * 9;
    if (iVar3 < *(int *)(param_1 + 0x61c)) {
      sVar1 = g_awItemIconTable[*(int *)(param_1 + 0x518 + iVar3 * 4)];
      if ((sVar1 != 0) && (*(short *)(param_1 + 0x6b4) != sVar1)) {
        if (*(int *)(param_1 + 0x6b8) == -1) {
          *(undefined4 *)(param_1 + 0x6b8) = 5;
          *(short *)(param_1 + 0x6b4) = sVar1;
        }
        else if (*(int *)(param_1 + 0x6b8) == 0) {
          FUN_005095d0(&g_uiPanelManager,sVar1);
          *(short *)(param_1 + 0x6b4) = sVar1;
        }
      }
    }
  }
  iVar3 = *(int *)(param_1 + 0x6b8);
  if (((iVar3 != -1) && (0 < iVar3)) && (*(int *)(param_1 + 0x6b8) = iVar3 + -1, iVar3 + -1 == 0)) {
    FUN_005095d0(&g_uiPanelManager,*(undefined2 *)(param_1 + 0x6b4));
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar3 == iVar4) {
    cVar2 = FUN_004db4b0();
    if (cVar2 != '\0') {
      if (*(int *)(param_1 + 0x6b0) == -1) {
        *(undefined4 *)(param_1 + 0x6b0) = 300;
      }
      else {
        iVar3 = *(int *)(param_1 + 0x6b0) + -1;
        *(int *)(param_1 + 0x6b0) = iVar3;
        if (iVar3 == 0) {
          QueueOutgoingPacketField(0xffffffff);
          iVar3 = DAT_007934e8;
          *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
          *(undefined2 *)(iVar3 + 0x4d4) = 0x2000;
          *(undefined2 *)(iVar3 + 0x4d6) = 0xffff;
          *(int *)(iVar3 + 0x44d0) = *(int *)(iVar3 + 0x44d0) + 2;
          FUN_004d2680();
        }
      }
      goto LAB_004d7cd2;
    }
  }
  *(undefined4 *)(param_1 + 0x6b0) = 0xffffffff;
LAB_004d7cd2:
  FUN_004507d0();
  FUN_004f3100();
  piVar5 = (int *)(param_1 + 0x6fc);
  iVar3 = 8;
  do {
    iVar4 = 2;
    do {
      if ((int *)*piVar5 != (int *)0x0) {
        (**(code **)(*(int *)*piVar5 + 8))();
      }
      piVar5 = piVar5 + 1;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  if (DAT_00793522 == '\0') {
    iVar3 = *(int *)(param_1 + 0x73c) + 1;
    *(int *)(param_1 + 0x73c) = iVar3;
    if (200 < iVar3) {
      *(undefined4 *)(param_1 + 0x73c) = 0;
      Replay_AppendEvent(0xa000);
      Replay_FlushEvent();
      return;
    }
  }
  else {
    FUN_004dcbe0(param_1);
  }
  return;
}

