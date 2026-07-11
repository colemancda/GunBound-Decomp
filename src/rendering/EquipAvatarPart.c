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
 */
#include "ghidra_types.h"


void EquipAvatarPart(int param_1)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar2 != -1) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = *(int *)(param_1 + 0x454) + iVar2;
    if (*(uint *)(g_clientContext + 0x44e24) <= uVar4) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (*(uint *)(g_clientContext + 0x44e24) <= uVar4) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    cVar1 = PeekPacketChecksumBool();
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(-(uint)(cVar1 != '\0') & 0x8000 | uVar3 & 0x7fff);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    LoadAvatarSprites(0xffffffff,0xffffffff,0xffffffff,0xffffffff,param_1 + 0x31488,200000,300000);
    FUN_00449250(param_1,1,1);
  }
  return;
}

