/* PumpBattleActions - 0x004129c0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at both argless PeekPacketChecksumState() calls - each reads
 * g_clientContext + 0x621e8, the outgoing-packet cursor cell
 * (0x412b2d / 0x412c3e).
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* CGameState's +0x8 (buffer,len replay-action handler) and +0xc
 * (event-code,value) virtuals both take `this` via ECX - orig
 * 0x412ad5-0x412aec, 0x412bea-0x412c01 and 0x412dc8-0x412ddb all show
 * `mov ecx, [eax*4+0x5b33f8]` (the state object) loaded before
 * `call [edx+0x8]`/`call [edx+0xc]` with no other load of ecx in
 * between.  The generic `code()` cast this file once used dropped
 * `this` entirely.
 *
 * CONVENTION CORRECTED (2026-10-30): these typedefs were __fastcall,
 * which puts `this` in ECX and the FIRST explicit argument in EDX - but
 * every target is a raw-C port of an erased __thiscall, i.e. cdecl with
 * `this` as the first stack argument (ghidra_types.h erases __thiscall).
 * The targets, from the vtables in globals.c:
 *   slot 2: State09_ReadyRoom_ProcessBattleAction(this, buf, len),
 *           State10_Loading_ProcessBattleAction(this, buf),
 *           State11_InBattle_ProcessBattleAction(this, buf, len);
 *   slot 3: State02_ServerSelect_OnTopButton(this, code, value),
 *           State09_ReadyRoom_OnActivate(this, code),
 *           State10_Loading_OnGameEvent(this, code);
 *   the rest are the CGameState_NoOpVirtual_A/B no-ops (void).
 * Each reads its object from ECX in the original (`mov edi,ecx` at
 * 0x4d4ebf, `mov esi,ecx` at 0x43e467, `mov edi,ecx` at 0x4b549f; `push
 * ecx` at 0x4d54cb, `[ecx+0x14c]` at 0x43e707, `mov edi,ecx` at 0x4e1209),
 * so the ports take it first on the stack.  Under __fastcall they got
 * buf/code in their `this` slot.  Now plain cdecl, `this` first. */
typedef void (*GameStateVirtualFn2)(void *thisPtr, void *buf, size_t len);
typedef void (*GameStateVirtualFn2i)(void *thisPtr, int a1, int a2);

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
  if (g_directLinkConnection != 0) {
    /* Context passed in EDI by the original (`mov edi,[0x7934f4]`
     * immediately before the call) - see DrainDirectLinkActionRing.c's
     * header. */
    DrainDirectLinkActionRing(g_directLinkConnection);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_00e9af44);
  DedupPendingBattleActionQueues(&g_replayContext);
  cVar2 = PopDirectBattleAction(&g_replayContext,local_400,&local_40c);
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
      (*(GameStateVirtualFn2 *)(*(int *)g_gameStateVTableArray[g_currentGameState] + 8))
                (g_gameStateVTableArray[g_currentGameState],local_400,local_40c);
    }
    cVar2 = PopDirectBattleAction(&g_replayContext,local_400,&local_40c);
  }
  if (DAT_00e9b188 == 0) {
LAB_00412baa:
    DAT_0056d3dc = -1;
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar3 = PeekPacketChecksumState((void *)(g_clientContext + 0x621e8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (iVar3 != -1) goto LAB_00412baa;
    if (DAT_0056d3dc == -1) {
      DAT_0056d3dc = 0;
    }
    else {
      DAT_0056d3dc = DAT_0056d3dc + param_1;
      if (200 < DAT_0056d3dc) {
        TurnEventSet_EraseSubtree((int *)*(undefined4 *)(DAT_00e9af14 + 4));
        *(int *)(DAT_00e9af14 + 4) = DAT_00e9af14;
        _DAT_00e9af18 = 0;
        *(int *)DAT_00e9af14 = DAT_00e9af14;
        *(int *)(DAT_00e9af14 + 8) = DAT_00e9af14;
        goto LAB_00412baa;
      }
    }
  }
  cVar2 = PopBroadcastBattleAction(&g_replayContext,local_400,&local_40c);
  while (cVar2 != '\0') {
    ApplyBattleActionToContext(g_clientContext,local_400,local_40c);
    if ((int *)g_gameStateVTableArray[g_currentGameState] != (int *)0x0) {
      (*(GameStateVirtualFn2 *)(*(int *)g_gameStateVTableArray[g_currentGameState] + 8))
                (g_gameStateVTableArray[g_currentGameState],local_400,local_40c);
    }
    cVar2 = PopBroadcastBattleAction(&g_replayContext,local_400,&local_40c);
  }
  if (DAT_00e9b198 != 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar3 = PeekPacketChecksumState((void *)(g_clientContext + 0x621e8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (iVar3 == -1) {
      if (DAT_0056d3d8 == -1) {
        DAT_0056d3d8 = 0;
        goto LAB_00412cb3;
      }
      DAT_0056d3d8 = DAT_0056d3d8 + 1;
      if (DAT_0056d3d8 < 0xc9) goto LAB_00412cb3;
      TurnEventSet_EraseSubtree((int *)*(undefined4 *)(DAT_00e9af14 + 4));
      *(int *)(DAT_00e9af14 + 4) = DAT_00e9af14;
      _DAT_00e9af18 = 0;
      *(int *)DAT_00e9af14 = DAT_00e9af14;
      *(int *)(DAT_00e9af14 + 8) = DAT_00e9af14;
    }
  }
  DAT_0056d3d8 = -1;
LAB_00412cb3:
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_00e9af44);
  while (iVar3 = g_connectionContextA, g_gameEventRingReadIndex != g_gameEventRingWriteIndex) {
    iVar4 = *(int *)(&g_gameEventDataRing + g_gameEventRingReadIndex * 4);
    iVar1 = *(int *)(&g_gameEventTypeRing + g_gameEventRingReadIndex * 4);
    g_gameEventRingReadIndex = g_gameEventRingReadIndex + 1 & 0x800001ff;
    if ((int)g_gameEventRingReadIndex < 0) {
      g_gameEventRingReadIndex = (g_gameEventRingReadIndex - 1 | 0xfffffe00) + 1;
    }
    iStack_404 = iVar4;
    if (iVar1 == 2) {
      QueueBroadcastEvent(3,(int)&g_replayContext);
      (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = (char)iVar4;
      g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
      BroadcastQueuedEvent();
    }
    else if (iVar1 == 5) {
      *(undefined4 *)(g_connectionContextA + 0x44d0) = 6;
      if (iVar4 == -1) {
        *(undefined2 *)(iVar3 + 0x4d4) = 0x2000;
        *(undefined2 *)(iVar3 + 0x4d6) = 0xffff;
        *(int *)(iVar3 + 0x44d0) = *(int *)(iVar3 + 0x44d0) + 2;
        SendOutgoingPacket(iVar3);
      }
      else {
        *(undefined2 *)(iVar3 + 0x4d4) = 0x4000;
        *(char *)(iVar3 + 0x4d6) = (char)iVar4;
        *(int *)(iVar3 + 0x44d0) = *(int *)(iVar3 + 0x44d0) + 1;
        EncodePacketBody(0,iVar3);
        SendOutgoingPacket(iVar3);
        QueueBroadcastEvent(0xf007,(int)&g_replayContext);
        (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = (undefined1)iStack_404;
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
        BroadcastQueuedEvent();
        iVar4 = iStack_404;
      }
    }
    if ((int *)g_gameStateVTableArray[g_currentGameState] != (int *)0x0) {
      (*(GameStateVirtualFn2i *)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0xc))
                (g_gameStateVTableArray[g_currentGameState],iVar1,iVar4);
    }
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9084);
  return;
}

