/* ComputeTurnDelay - 0x0045d150 in the original binary.
 *
 * RENAMED (2026-08-13, from FUN_0045d150). Computes a player's turn
 * delay from the mobile's guarded stats and its item loadout.  The
 * mobile object arrives in EAX (modelled here as `in_EAX`).
 *
 * Identified from its two callers, which agree:
 *   - SortTurnOrderByDelay adds this value to the local player's cell in
 *     the per-player delay array at g_clientContext+0xebef4 before
 *     sorting the turn order by that array, and subtracts it after.
 *   - State11_InBattle_RenderPlayerRoster divides it by 10 and sprintf's
 *     it into the roster row: "%5d" (0x551ed0) for the row that matches
 *     the current slot and "%+5d" (0x551ec4) for the others - the
 *     absolute-then-relative pair GunBound's player list shows for
 *     delay.  Both call sites gate it on the room object's flag at
 *     +0xae68.
 *
 * The item term is what makes it a loadout-sensitive value: it calls
 * GetItemQuantityByIcon with the icon id at in_EAX+0xbfbc and folds the
 * count against a cell drawn from the per-slot BLOCK at
 * g_clientContext + 0x50cf4 + slot*0x1120 (0x1120 == 8*0x224, eight
 * guard cells per slot).
 *
 * Body is a raw/near-verbatim Ghidra port, not hand-verified. See
 * src/README.md's "Raw/verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-12, CValueGuard sweep): recovered the guard
 * cell at all 9 argless PeekPacketChecksumState() calls (peek status
 * "clean", 9 C : 9 orig), from tools/guard_cell_resolve.py over
 * 0x45d150-0x45d37b.
 *
 * The object arrives in EAX (`mov esi,eax` at 0x45d162), which this
 * decompile already models as `in_EAX` and dereferences elsewhere
 * (`*(undefined2 *)(in_EAX + 0xbfbc)`), so six cells are in_EAX+N and
 * two are globals.
 *
 * The remaining two (0x45d29f, 0x45d2fe) index a per-slot BLOCK, not a
 * single cell: `and eax,7 / imul eax,0x1120 / lea [eax + ctx +
 * 0x50cf4]` at 0x45d27e and 0x45d2df.  0x1120 is 8*0x224, i.e. eight
 * guard cells per slot, and the index is *(int *)(in_EAX + 8) & 7 -
 * recomputed identically at both sites, so it is written inline rather
 * than captured.
 *
 * CORRECTION (2026-08-13, same day): the site at 0x45d22d is a THREE-WAY
 * folded select, not a single cell.  Ghidra rendered two nested
 * PeekPacketChecksumBool tests as an if/else tree whose three arms all
 * just call EnterCriticalSection, followed by one shared Peek - but each
 * arm loads a DIFFERENT cell first: +0x9678 (first bool set), +0x9454
 * (second set), +0x9230 (neither).  The first pass passed only the
 * fall-through +0x9230.  Now each arm sets pvVar7 and the shared Peek
 * reads it.  Found by grepping for the if/else-EnterCriticalSection
 * idiom after the same bug surfaced in FUN_0047c040/FUN_0047fad0.
 */
#include "ghidra_types.h"


int ComputeTurnDelay(void)

{
  char cVar1;
  int in_EAX;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  void *pvVar7;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState((void *)(in_EAX + 0x8de8));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState((void *)(in_EAX + 0x8bc4));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState((void *)&DAT_00e55ab8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState((void *)(in_EAX + 0x900c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 == '\0') {
    cVar1 = PeekPacketChecksumBool();
    if (cVar1 == '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      pvVar7 = (void *)(in_EAX + 0x9230);
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      pvVar7 = (void *)(in_EAX + 0x9454);
    }
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    pvVar7 = (void *)(in_EAX + 0x9678);
  }
  iVar6 = PeekPacketChecksumState(pvVar7);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = ((400 - iVar3) / iVar4) * iVar5 + iVar6;
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 == '\x01') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState((void *)(in_EAX + 0x989c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState((void *)(g_clientContext + 0x50cf4 + (*(int *)(in_EAX + 8) & 7U) * 0x1120));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = GetItemQuantityByIcon(g_clientContext,*(undefined2 *)(in_EAX + 0xbfbc));
    if (iVar5 + iVar4 * -3 < 0) {
      iVar5 = 0;
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = PeekPacketChecksumState((void *)(g_clientContext + 0x50cf4 + (*(int *)(in_EAX + 8) & 7U) * 0x1120));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = GetItemQuantityByIcon(g_clientContext,*(undefined2 *)(in_EAX + 0xbfbc));
      iVar5 = iVar5 + iVar4 * -3;
    }
    iVar6 = iVar6 + iVar3 + iVar5;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return (iVar2 + iVar6) * iVar3;
}

