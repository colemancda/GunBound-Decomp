/* EnqueueTurnSlot - 0x004cf050 in the original binary.
 *
 * RENAMED (2026-08-13, from FUN_004cf050). Appends a slot to the battle
 * turn queue (the byte array at battle+0x10a8, length at +0x10b0, cap
 * 8) - the same queue AdvanceTurnQueue pops.  After appending it scans
 * the per-player delay array at g_clientContext+0xebef4 for players
 * whose cell is not the retired-turn sentinel (-1, which
 * AdvanceTurnQueue writes) and who are not yet queued, counting
 * survivors per team - the all-queued / one-team-left checks that end a
 * round.  Called from the 0x3020 packet handler and two battle-action
 * paths.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at all 7 argless PeekPacketChecksumState() calls (7 C : 7 orig,
 * goto-free zip), from tools/guard_cell_resolve.py over
 * 0x4cf050-0x4cf310.
 *
 * The loop cell walks the per-player delay array: `lea esi,[edx + esi +
 * 0xebef4]` at 0x4cf0b9, where edx is frame[0x14] - the C's own local_c
 * byte cursor (steps 0x224 per iteration, bound 0x1120, i.e. all 8
 * player cells) - so the cell is g_clientContext + 0xebef4 + local_c.
 * The `iVar3 != -1` check right after is the retired-turn sentinel that
 * AdvanceTurnQueue writes (0xffffffff), and param_2+0x10a8/+0x10b0 are
 * the same turn queue it pops - this function is the queue's feeder,
 * scanning for players not yet queued.  The other six cells are fixed
 * g_clientContext offsets.
 */
#include "ghidra_types.h"


void __thiscall EnqueueTurnSlot(int param_1,int param_2)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  byte bVar5;
  byte *pbVar6;
  uint local_10;
  int local_c;
  int local_8;
  int local_4;
  
  if (*(int *)(param_2 + 0x10b0) < 8) {
    *(undefined1 *)(*(int *)(param_2 + 0x10b0) + 0x10a8 + param_2) = param_1;
    *(int *)(param_2 + 0x10b0) = *(int *)(param_2 + 0x10b0) + 1;
    local_8 = 0;
    local_4 = 0;
    local_10 = 0;
    local_c = 0;
    do {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar3 = PeekPacketChecksumState((void *)(g_clientContext + 0xebef4 + local_c));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      if (iVar3 != -1) {
        iVar3 = 0;
        if (0 < *(int *)(param_2 + 0x10b0)) {
          do {
            if (*(byte *)(param_2 + 0x10a8 + iVar3) == local_10) break;
            iVar3 = iVar3 + 1;
          } while (iVar3 < *(int *)(param_2 + 0x10b0));
        }
        if (iVar3 == *(int *)(param_2 + 0x10b0)) {
          cVar2 = *(char *)(g_clientContext + 0x4590c + local_10);
          if (cVar2 == '\0') {
            local_8 = local_8 + 1;
          }
          else if (cVar2 == '\x01') {
            local_4 = local_4 + 1;
          }
        }
      }
      local_10 = local_10 + 1;
      local_c = local_c + 0x224;
    } while (local_c < 0x1120);
    if ((local_8 != 0) && (local_4 != 0)) {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar3 = PeekPacketChecksumState((void *)(g_clientContext + 0x45354));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      if (iVar3 != 1) {
        return;
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar3 = PeekPacketChecksumState((void *)(g_clientContext + 0x67e3d0));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      if (iVar3 != 0) {
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        iVar3 = PeekPacketChecksumState((void *)(g_clientContext + 0x67e5f4));
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        if (iVar3 != 0) {
          return;
        }
      }
    }
    iVar3 = g_clientContext;
    pbVar6 = (byte *)(g_clientContext + 0x6214c);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar4 = _rand();
    *pbVar6 = (byte)iVar4;
    iVar4 = _rand();
    bVar1 = *pbVar6;
    *(byte *)(iVar3 + 0x6214d) = (byte)iVar4;
    bVar5 = '\x01' << (bVar1 & 7);
    bVar5 = ~bVar5 & (byte)iVar4 | bVar5;
    *(byte *)(iVar3 + 0x6214d) = bVar5;
    *(byte *)(iVar3 + 0x6214e) = bVar5 + bVar1 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    cVar2 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x62149));
    if (cVar2 == '\x01') {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar3 = PeekPacketChecksumState((void *)(g_clientContext + 0x3b49c));
      iVar4 = PeekPacketChecksumState((void *)(g_clientContext + 0x3b6c4));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      if (iVar3 == iVar4) {
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        iVar3 = PeekPacketChecksumState((void *)(g_clientContext + 0x45354));
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        if ((((iVar3 == 3) || (cVar2 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6214c)), cVar2 == '\x01')) &&
            (cVar2 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x62152)), cVar2 == '\0')) && (cVar2 = DecodeGuardedBool(), cVar2 == '\0')) {
          SendPlayResult();
        }
      }
    }
  }
  return;
}

