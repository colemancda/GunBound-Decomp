/* PumpBattleActions - 0x004129c0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void PumpBattleActions(int param_1)

{
  int iVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  size_t local_40c;
  undefined1 local_405;
  int iStack_404;
  undefined1 local_400 [1024];
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9084);
  ProcessIncomingPackets(DAT_005b2b58,0);
  ProcessIncomingPackets(DAT_005b2b5c,0);
  ProcessIncomingPackets(DAT_005b2b60,0);
  if (DAT_007934f4 != 0) {
    FUN_00405a40();
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00e9af44);
  FUN_004e84c0(&DAT_00e55ce0);
  cVar2 = FUN_004e7b60(&DAT_00e55ce0,local_400,&local_40c);
  while (cVar2 != '\0') {
    if (*(FILE **)(&g_replayFileHandle + g_clientContext) != (FILE *)0x0) {
      local_405 = 1;
      _fwrite(&local_405,1,1,*(FILE **)(&g_replayFileHandle + g_clientContext));
      _fwrite(g_gameStateVTableArray[0xb] + 4,1,4,*(FILE **)(&g_replayFileHandle + g_clientContext));
      _fwrite(&local_40c,1,4,*(FILE **)(&g_replayFileHandle + g_clientContext));
      _fwrite(local_400,1,local_40c,*(FILE **)(&g_replayFileHandle + g_clientContext));
    }
    ApplyBattleActionToContext(g_clientContext,local_400,local_40c);
    if ((int *)g_gameStateVTableArray[g_currentGameState] != (int *)0x0) {
      (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 8))(local_400,local_40c);
    }
    cVar2 = FUN_004e7b60(&DAT_00e55ce0,local_400,&local_40c);
  }
  if (DAT_00e9b188 == 0) {
LAB_00412baa:
    DAT_0056d3dc = -1;
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar3 != -1) goto LAB_00412baa;
    if (DAT_0056d3dc == -1) {
      DAT_0056d3dc = 0;
    }
    else {
      DAT_0056d3dc = DAT_0056d3dc + param_1;
      if (200 < DAT_0056d3dc) {
        FUN_004e8ad0(*(undefined4 *)(DAT_00e9af14 + 4));
        *(int *)(DAT_00e9af14 + 4) = DAT_00e9af14;
        _DAT_00e9af18 = 0;
        *(int *)DAT_00e9af14 = DAT_00e9af14;
        *(int *)(DAT_00e9af14 + 8) = DAT_00e9af14;
        goto LAB_00412baa;
      }
    }
  }
  cVar2 = FUN_004e80d0(&DAT_00e55ce0,local_400,&local_40c);
  while (cVar2 != '\0') {
    ApplyBattleActionToContext(g_clientContext,local_400,local_40c);
    if ((int *)g_gameStateVTableArray[g_currentGameState] != (int *)0x0) {
      (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 8))(local_400,local_40c);
    }
    cVar2 = FUN_004e80d0(&DAT_00e55ce0,local_400,&local_40c);
  }
  if (DAT_00e9b198 != 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar3 == -1) {
      if (DAT_0056d3d8 == -1) {
        DAT_0056d3d8 = 0;
        goto LAB_00412cb3;
      }
      DAT_0056d3d8 = DAT_0056d3d8 + 1;
      if (DAT_0056d3d8 < 0xc9) goto LAB_00412cb3;
      FUN_004e8ad0(*(undefined4 *)(DAT_00e9af14 + 4));
      *(int *)(DAT_00e9af14 + 4) = DAT_00e9af14;
      _DAT_00e9af18 = 0;
      *(int *)DAT_00e9af14 = DAT_00e9af14;
      *(int *)(DAT_00e9af14 + 8) = DAT_00e9af14;
    }
  }
  DAT_0056d3d8 = -1;
LAB_00412cb3:
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00e9af44);
  while (iVar3 = DAT_007934e8, DAT_0079379c != DAT_00793798) {
    iVar4 = *(int *)(&DAT_00793fa0 + DAT_0079379c * 4);
    iVar1 = *(int *)(&DAT_007937a0 + DAT_0079379c * 4);
    DAT_0079379c = DAT_0079379c + 1 & 0x800001ff;
    if ((int)DAT_0079379c < 0) {
      DAT_0079379c = (DAT_0079379c - 1 | 0xfffffe00) + 1;
    }
    iStack_404 = iVar4;
    if (iVar1 == 2) {
      Replay_AppendEvent(3);
      (&g_replayEventBuffer)[g_replayEventCursor] = (char)iVar4;
      g_replayEventCursor = g_replayEventCursor + 1;
      Replay_FlushEvent();
    }
    else if (iVar1 == 5) {
      *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
      if (iVar4 == -1) {
        *(undefined2 *)(iVar3 + 0x4d4) = 0x2000;
        *(undefined2 *)(iVar3 + 0x4d6) = 0xffff;
        *(int *)(iVar3 + 0x44d0) = *(int *)(iVar3 + 0x44d0) + 2;
        SendOutgoingPacket();
      }
      else {
        *(undefined2 *)(iVar3 + 0x4d4) = 0x4000;
        *(char *)(iVar3 + 0x4d6) = (char)iVar4;
        *(int *)(iVar3 + 0x44d0) = *(int *)(iVar3 + 0x44d0) + 1;
        EncodePacketBody();
        SendOutgoingPacket();
        Replay_AppendEvent(0xf007);
        (&g_replayEventBuffer)[g_replayEventCursor] = (undefined1)iStack_404;
        g_replayEventCursor = g_replayEventCursor + 1;
        Replay_FlushEvent();
        iVar4 = iStack_404;
      }
    }
    if ((int *)g_gameStateVTableArray[g_currentGameState] != (int *)0x0) {
      (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0xc))(iVar1,iVar4);
    }
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9084);
  return;
}

