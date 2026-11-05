/* LoadAvatarStorePagePartRecords - 0x0044b0b0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_0044b0b0 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. Evidence from outside the body: Called by
 * every path that changes which avatar catalog rows are visible:
 * State07_AvatarStore_OnEnter, State07_AvatarStore_ProcessPacket (x5),
 * AvatarStorePanel_OnCommand (right after it stores the page base at state
 * + 0x454 from the 0x2000 scroll command) and AvatarStorePanel_OnMouseUp
 * (after AtlArray_InsertAt_450 rebuilds the catalog). For up to 0x15 (21)
 * rows starting at the page base state + 0x454 it peeks each catalog
 * record's packed part code (ctx + 0x44e20 + row * 0x450 + 0x22c) and
 * unpacks it as gender bit 15, category bits 16.. and index bits 0-14 into
 * LoadAvatarPartRecordByIndex, which fills one output record per row at
 * state + 0xdb5c. OPEN BUG, not fixed by this rename: the original
 * advances the output pointer ESI by 0x17e4 per row (disasm 0x44b14c add
 * esi,0x17e4), but the port passes param_1 + 0xdb5c for every row, so all
 * 21 loads land in the first record.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at the file's one argless PeekPacketChecksumState() call: the selected catalog record's part-code field - *(ctx+0x44e20) + (pageBase + i)*0x450 + 0x22c, the exact expression Equip/UnequipAvatarSlot use, here walked over every visible row (uVar1 = param_1+0x454 page base + iVar2).
 */
#include "ghidra_types.h"


void LoadAvatarStorePagePartRecords(int param_1)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = 0;
  while( true ) {
    uVar1 = *(int *)(param_1 + 0x454) + iVar2;
    if (*(uint *)(g_clientContext + 0x44e24) <= uVar1) {
      return;
    }
    if (*(uint *)(g_clientContext + 0x44e24) <= uVar1) break;
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar1 = PeekPacketChecksumState((void *)(*(int *)(g_clientContext + 0x44e20) + uVar1 * 0x450 + 0x22c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    /* FIXED (2026-08-11): dropped outRecord (ESI) - orig 0x44b0b9-0x44b0c0
     * `mov esi,[esp+0x10]` (= param_1) / `add esi,0xdb5c`, loop-invariant
     * up to the call at 0x44b146. */
    LoadAvatarPartRecordByIndex(g_clientContext,(uVar1 & 0x8000) == 0x8000,uVar1 >> 0x10,uVar1 & 0x7fff,
                 param_1 + 0xdb5c);
    iVar2 = iVar2 + 1;
    if (0x14 < iVar2) {
      return;
    }
  }
                    /* WARNING: Subroutine does not return */
  ThrowCxxException(0x80070057);
}

