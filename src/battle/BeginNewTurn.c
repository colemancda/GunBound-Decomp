/* BeginNewTurn - 0x004d0a10 in the original binary.
 *
 * RENAMED (2026-08-13, from FUN_004d0a10). Handles the battle's
 * turn-transition packet and starts the next turn.
 *
 * Sole caller is State11_InBattle_ProcessBattleAction's `case 0xc300`,
 * which passes the battle object and `param_2 + 0x22` - the packet
 * payload - and follows it with three PostTurnEvent replay records
 * (0xc300 / 0xc306 / 0xc40b).
 *
 * What it does, in order: stamps the acting slot into param_1[0x428];
 * seeds the turn counter at g_clientContext+0xeba98 from the packet's
 * leading u16; on counter 0 runs the first-turn path; raises a
 * localized notice (string 0x261) when the counter is 10 from the limit
 * at +0x4512c; calls SpawnWeatherHazards; bumps +0xeb854 by 3 on every
 * +0x473a0-th turn; increments the turn counter; seeds two per-turn
 * values from packet bytes 1 and 3 into g_clientContext+0x5af88 and
 * +0x5b1ac; sets the battle phase in param_1[0x42e] to 1; and finally
 * calls AdvanceTurnQueue to retire the head of the turn queue.
 *
 * The two per-turn values it seeds are the ones every projectile
 * spawner reads back (SpawnPrimaryShot, SpawnItemProjectile,
 * SpawnDropBombProjectile, FUN_004aa520) and that the shot broadcast re-sends as a
 * u16 pair (Mobile.cpp, State11_InBattle_HandleFireInput) - i.e. they
 * are per-turn shot parameters assigned by the server, not client
 * state.  Their exact meaning is NOT confirmed here, so they are left
 * as raw g_clientContext offsets.
 *
 * Body is a raw/near-verbatim Ghidra port, not hand-verified. See
 * src/README.md's "Raw/verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-12, CValueGuard sweep): recovered the guard
 * cell at all 13 argless PeekPacketChecksumState() and all 6 one-arg
 * EncodeOutgoingPacketField() calls (both lists "clean").  Cells from
 * tools/guard_cell_resolve.py over 0x4d0a10-0x4d0dd7; the two families
 * interleave 1:1 with the original in address order (19 C : 19 orig).
 * All cells are g_clientContext-relative globals.
 *
 * One site needed reconstruction rather than just an argument.  The
 * Peek at 0x4d0c7c reads a cell out of the per-category array at
 * g_clientContext+0x595d8, stride 0x224, and the index is computed at
 * 0x4d0c42-0x4d0c5d as `(a / b) % 8` from the results of the two Peeks
 * immediately above it - both of which the decompile DISCARDED
 * (0x4d0c09 -> EDI, 0x4d0c32 -> frame[0x10], consumed by the `idiv` at
 * 0x4d0c45).  Those results are now captured into iVar7/iVar8 so the
 * index can be written out.  MSVC's truncating `%` matches the
 * `and 0x80000007 / jns / dec / or 0xfffffff8 / inc` sequence exactly.
 *
 * frame[0x10] is a one-slot scratch that is REWRITTEN before nearly
 * every use (0x4d0b3c, 0x4d0b95, 0x4d0c28, 0x4d0c74, 0x4d0cc6,
 * 0x4d0d68), and it alternates between holding a cell pointer and
 * holding a Peek RESULT, so each read was matched to its own most
 * recent writer.
 */
#include "ghidra_types.h"


void BeginNewTurn(int *param_1,undefined2 *param_2)

{
  undefined1 uVar1;
  undefined2 uVar2;
  short sVar3;
  uint in_EAX;
  int iVar4;
  int iVar5;
  char *_Format;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  int local_90 [4];
  char local_80 [128];
  
  param_1[0x428] = in_EAX & 0xff;
  uVar2 = *param_2;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EncodeOutgoingPacketField((void *)(g_clientContext + 0xeba98), uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar4 = PeekPacketChecksumState((void *)(g_clientContext + 0xeba98));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar4 == 0) {
    /* dropped-register recovery: MSVC materialises this 4-entry table in
       the frame at 0x004d0aa8-0x004d0ac0 and indexes it with the peek
       result at 0x004d0ae5 (`mov esi,[esp+esi*4+0x18]`); Ghidra dropped
       both the table and the peek's return value. */
    local_90[0] = 1;
    local_90[1] = 3;
    local_90[2] = 2;
    local_90[3] = 4;
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar5 = PeekPacketChecksumState((void *)(g_clientContext + 0x45354));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    FUN_00438360(local_90[iVar5]);
  }
  if (*(char *)(g_clientContext + 0x45127) != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar4 = PeekPacketChecksumState((void *)(g_clientContext + 0x4512c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar5 = PeekPacketChecksumState((void *)(g_clientContext + 0xeba98));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (iVar4 - iVar5 == 10) {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar4 = PeekPacketChecksumState((void *)(g_clientContext + 0x4512c));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar5 = PeekPacketChecksumState((void *)(g_clientContext + 0xeba98));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar4 = iVar4 - iVar5;
      _Format = (char *)GetLocalizedString(&g_localizedStringTable,0x261);
      _sprintf(local_80,_Format,iVar4);
      (**(code **)(*param_1 + 0x28))(local_80,2,6);
    }
  }
  SpawnWeatherHazards(g_clientContext,(char *)(param_2 + 1));
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar7 = PeekPacketChecksumState((void *)(g_clientContext + 0xeba98));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar8 = PeekPacketChecksumState((void *)(g_clientContext + 0x473a0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar6 = PeekPacketChecksumState((void *)(g_clientContext + 0x595d8 + (iVar7 / iVar8) % 8 * 0x224));
  EncodeOutgoingPacketField((void *)(g_clientContext + 0xebcbc), uVar6);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar4 = PeekPacketChecksumState((void *)(g_clientContext + 0xeba98));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar5 = PeekPacketChecksumState((void *)(g_clientContext + 0x473a0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar4 % iVar5 == 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar4 = PeekPacketChecksumState((void *)(g_clientContext + 0xeb854));
    EncodeOutgoingPacketField((void *)(g_clientContext + 0xeb854), iVar4 + 3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  iVar4 = *(int *)(g_clientContext + 0x621e0);
  if ((iVar4 != 0) && (*(int *)(iVar4 + 0x24) != 0xd)) {
    *(undefined4 *)(iVar4 + 0xb0b0) = 4;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar4 = PeekPacketChecksumState((void *)(g_clientContext + 0xeba98));
  EncodeOutgoingPacketField((void *)(g_clientContext + 0xeba98), iVar4 + 1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = *(undefined1 *)(param_2 + 1);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EncodeOutgoingPacketField((void *)(g_clientContext + 0x5af88), uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  sVar3 = *(short *)((int)param_2 + 3);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EncodeOutgoingPacketField((void *)(g_clientContext + 0x5b1ac), (int)sVar3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  param_1[0x42e] = 1;
  AdvanceTurnQueue();
  return;
}

