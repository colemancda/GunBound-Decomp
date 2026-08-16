/* EquipAvatarPart - 0x0044b170 in the original binary.
 *
 * Avatar Store "equip" action: transmits the selected part's equip code via
 * EncodeOutgoingPacketField (bit15 = gender | bits0-14 = part id) followed by
 * its inventory index, then refreshes the local preview via LoadAvatarSprites.
 * Peer of UnequipAvatarSlot (0x44b330, which sends the id=0 "Standard/none"
 * clear) and PreviewAvatarPart (0x44b460, a local try-on that does NOT send).
 * Dispatched from the store item-action handler (FUN_0050a640).
 *
 * Function IDENTITY is confirmed (Avatar-Store equip, transmits); the BODY is a
 * raw/near-verbatim Ghidra port, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at all 4 argless PeekPacketChecksumState() calls AND both 1-arg
 * EncodeOutgoingPacketField() calls (this was the deferred
 * encode-MISMATCH file; the mismatch was these two never-fixed sites).
 * Derived from a full disasm of 0x44b170-0x44b323.
 *
 * The data flow, which the decompile had severed in the middle:
 *   - param_1+0x228 (peeked twice) is the store's SELECTED-ROW cell
 *     (-1 = nothing selected); uVar4 = row + the page base at
 *     param_1+0x454 = the catalog index.
 *   - The catalog lives at *(g_clientContext+0x44e20), count at
 *     +0x44e24 (the bounds checks), record stride 0x450, and the
 *     guarded field at record+0x22c holds the PART CODE.  Both middle
 *     Peeks read that same field of the selected record - the C
 *     discarded the first one's result, but its bits 16-19 are the
 *     part's CATEGORY nibble (`sar eax,0x10 / and al,0xf` at
 *     0x44b22e), which selects BOTH Encode cells below.  Captured in
 *     uVar5.
 *   - Encode #1 writes gender<<15 | code to the per-category equipped
 *     part-code array at g_clientContext + 0x3ac08 + cat*0x224 (gender
 *     from the +0x3b498 GuardedBool); Encode #2 writes the catalog
 *     index to the parallel array at +0x5f4ab8 + cat*0x224 - which is
 *     cell 9+cat of the 0x5f3774 avatar-part cell family FUN_00423bf0
 *     already documents (0x5f4ab8 == 0x5f3774 + 9*0x224).
 */
#include "ghidra_types.h"


void EquipAvatarPart(int param_1)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState((void *)(param_1 + 0x228));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar2 != -1) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState((void *)(param_1 + 0x228));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = *(int *)(param_1 + 0x454) + iVar2;
    if (*(uint *)(g_clientContext + 0x44e24) <= uVar4) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState((void *)(*(int *)(g_clientContext + 0x44e20) + uVar4 * 0x450 + 0x22c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (*(uint *)(g_clientContext + 0x44e24) <= uVar4) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState((void *)(*(int *)(g_clientContext + 0x44e20) + uVar4 * 0x450 + 0x22c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    cVar1 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x3b498));
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(g_clientContext + 0x3ac08 + (uVar5 >> 0x10 & 0xf) * 0x224), -(uint)(cVar1 != '\0') & 0x8000 | uVar3 & 0x7fff);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(g_clientContext + 0x5f4ab8 + (uVar5 >> 0x10 & 0xf) * 0x224), uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    LoadAvatarSprites(0xffffffff,0xffffffff,0xffffffff,0xffffffff,param_1 + 0x31488,200000,300000);
    FUN_00449250(param_1,1,1);
  }
  return;
}

