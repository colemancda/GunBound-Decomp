/* FindFreeItemSlot - 0x004dc140 in the original binary.
 *
 * RENAMED (2026-08-13, from FUN_004dc140). Finds the first free slot in
 * the local player's item loadout and returns its index, or -1 when
 * the loadout is full.  param_1 is the item's WIDTH: 1 = a single-slot
 * item (a free slot is one whose ctx+0x39f30 cell is 0), 2 = a two-slot
 * item (needs BOTH the ctx+0x39f30 cell and its +0x3a154 partner to be
 * 0, and cannot start in the last slot - the `iVar2 == 0xab4` early
 * -1).  Six slots, stride 0x224.
 *
 * Sole caller is State09_ReadyRoom_HandleChatInput's item-grid click:
 * it looks the clicked icon up in g_awItemIconTable, calls this with
 * width = 1 + (icon & 0xff00 != 0), bails on -1, and otherwise queues
 * the pick (0xff + low byte for two-slot items).  ResetItemSlotCounters
 * clears the same two arrays with the same width distinction.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at both argless PeekPacketChecksumState() calls: the item array at g_clientContext+0x39f30 and its parallel
 * partner at +0x3a154 (the ResetItemSlotCounters pair), indexed by the
 * C's own byte cursor iVar2 (0x224 per slot, six slots).
 */
#include "ghidra_types.h"


int FindFreeItemSlot(int param_1)

{
  int iVar1;
  int iVar2;
  int local_4;
  
  iVar2 = 0;
  local_4 = 0;
  do {
    if ((param_1 == 2) && (iVar2 == 0xab4)) {
      return -1;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState((void *)(g_clientContext + 0x39f30 + iVar2));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar1 == 0) {
      if (param_1 == 1) {
        return local_4;
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar1 = PeekPacketChecksumState((void *)(g_clientContext + 0x3a154 + iVar2));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar1 == 0) {
        return local_4;
      }
    }
    local_4 = local_4 + 1;
    iVar2 = iVar2 + 0x224;
    if (0xcd7 < iVar2) {
      return -1;
    }
  } while( true );
}

