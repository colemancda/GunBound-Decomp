/* SortTurnOrderByDelay - 0x004203b0 in the original binary.
 *
 * RENAMED (2026-08-13, from FUN_004203b0). Sorts the battle turn order
 * by each player's accumulated delay, once per tick from
 * State11_InBattle_OnTick.
 *
 * Two parallel guard arrays in the client context, both 8 entries of
 * stride 0x224, drive this:
 *   g_clientContext + 0xebef4  per-player DELAY cells
 *   g_clientContext + 0xef254  the ORDER array - each entry holds a
 *                              player slot number
 * The nested loop is a plain selection sort: it reads two order entries,
 * uses them to index the delay array, and swaps the ORDER entries (not
 * the delays) when the inner player's delay is the smaller - i.e. it
 * sorts the order array ascending by delay, which is turn order.
 *
 * Around the sort it biases the local player: it Peeks the current-slot
 * index at g_clientContext+0x3b49c, ADDS ComputeTurnDelay's result to
 * that player's delay cell before sorting and SUBTRACTS it after, so the
 * ordering previews where the pending shot would place them.  That bias
 * is skipped unless the room object at g_clientContext+0x621e0 exists
 * and both of its guarded bools are set.
 *
 * The delay array and the +0x3b49c current-slot index are corroborated
 * by AdvanceTurnQueue, which writes 0xffffffff into the same
 * +0xebef4 + slot*0x224 cell when a turn is consumed and compares the
 * queue head against the same +0x3b49c value.
 *
 * Body is a raw/near-verbatim Ghidra port, not hand-verified. See
 * src/README.md's "Raw/verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-12, CValueGuard sweep): recovered the guard
 * cell at all 10 argless PeekPacketChecksumState() and all 4 one-arg
 * EncodeOutgoingPacketField() calls (both lists "clean"), from
 * tools/guard_cell_resolve.py plus a full read of 0x4203b0-0x4205f4.
 *
 * The function is a selection sort over the per-player CValueGuard
 * array at param_1+0xebef4, stride 0x224, and NOTHING here is a plain
 * cell address - every cell is either indexed by another cell's VALUE
 * or is a loop-carried pointer, and Ghidra dropped both.
 *
 * (1) Indexed cells.  Four Peeks read a slot number and the next access
 * uses it: `imul <result>,0x224 / lea [<result> + ebx + 0xebef4]` at
 * 0x420425, 0x4204cb, 0x4204e1 and 0x4205c1.  Those four results are
 * discarded by the decompile and are now captured into iVar6/iVar7/
 * iVar8.  Note the crossover at 0x4204cb/0x4204e1: the INNER cursor's
 * value indexes the first slot and the OUTER cursor's value the second,
 * matching `if (iVar2 < iVar3)` against 0x4204f9's `cmp ebx,eax`.
 *
 * (2) Loop-carried cursors.  frame[0x10] and frame[0x14] hold two
 * walking cell pointers that Ghidra folded away entirely (no local was
 * emitted for either).  frame[0x10] starts at param_1+0xef254 when
 * local_c is 1 and advances 0x224 per outer iteration, so it is
 * param_1 + 0xef254 + (local_c - 1)*0x224.  frame[0x14] is reloaded to
 * frame[0x10]+0x224 at each inner-loop entry and advances 0x224 per
 * inner iteration while local_10 counts down from 8-local_c, so it is
 * param_1 + 0xef254 + (8 - local_10)*0x224.  Both are written as
 * expressions over the C's existing locals rather than by adding
 * cursor variables and their updates.
 *
 * The 0x420509-0x420558 block is a SWAP: the inner cell is written with
 * the outer cell's value and vice versa, so the two Encode cells there
 * are crossed relative to the Peeks directly above them.
 *
 * ebx is param_1 for most of the function (loaded at 0x4203b4; this is
 * __stdcall, `ret 4`), but the inner loop clobbers it at 0x4204c0 and
 * 0x42052d and restores it from frame[0x30] at 0x42057c - so the two
 * param_1+0x3b49c cells at the head and tail are the same address
 * despite reaching it by different routes.
 */
#include "ghidra_types.h"


void SortTurnOrderByDelay(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_14 = 0;
  if (((*(int *)(param_1 + 0x621e0) != 0) && (cVar1 = PeekPacketChecksumBool((byte *)(*(int *)(param_1 + 0x621e0) + 0x8bbd)), cVar1 != '\0')) &&
     (cVar1 = PeekPacketChecksumBool((byte *)(*(int *)(param_1 + 0x621e0) + 0x8ba8)), cVar1 != '\0')) {
    local_14 = ComputeTurnDelay(*(int *)(param_1 + 0x621e0));
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x3b49c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = PeekPacketChecksumState((void *)(param_1 + 0xebef4 + iVar6 * 0x224));
  EncodeOutgoingPacketField((void *)(param_1 + 0xebef4 + iVar6 * 0x224), iVar2 + local_14);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_c = 1;
  local_8 = 7;
  do {
    if (local_c < 8) {
      local_10 = 8 - local_c;
      do {
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        iVar7 = PeekPacketChecksumState((void *)(param_1 + 0xef254 + (local_c + -1) * 0x224));
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        iVar8 = PeekPacketChecksumState((void *)(param_1 + 0xef254 + (8 - local_10) * 0x224));
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        iVar2 = PeekPacketChecksumState((void *)(param_1 + 0xebef4 + iVar8 * 0x224));
        iVar3 = PeekPacketChecksumState((void *)(param_1 + 0xebef4 + iVar7 * 0x224));
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        if (iVar2 < iVar3) {
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          uVar4 = PeekPacketChecksumState((void *)(param_1 + 0xef254 + (8 - local_10) * 0x224));
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          uVar5 = PeekPacketChecksumState((void *)(param_1 + 0xef254 + (local_c + -1) * 0x224));
          EncodeOutgoingPacketField((void *)(param_1 + 0xef254 + (8 - local_10) * 0x224), uVar5);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          EncodeOutgoingPacketField((void *)(param_1 + 0xef254 + (local_c + -1) * 0x224), uVar4);
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        }
        local_10 = local_10 + -1;
      } while (local_10 != 0);
    }
    local_c = local_c + 1;
    local_8 = local_8 + -1;
  } while (local_8 != 0);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x3b49c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = PeekPacketChecksumState((void *)(param_1 + 0xebef4 + iVar6 * 0x224));
  EncodeOutgoingPacketField((void *)(param_1 + 0xebef4 + iVar6 * 0x224), iVar2 - local_14);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  return;
}

