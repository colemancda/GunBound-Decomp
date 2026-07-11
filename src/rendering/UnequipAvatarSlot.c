/* UnequipAvatarSlot - 0x0044b330 in the original binary.
 *
 * Avatar Store "unequip / clear slot" action: transmits the id=0 "Standard/none"
 * equip code (EncodeOutgoingPacketField: gender bit only, part id 0) plus a
 * 0xffffffff index, then refreshes the local preview via LoadAvatarSprites.
 * Peer of EquipAvatarPart (0x44b170, which sends a real part code + index) and
 * PreviewAvatarPart (0x44b460, local try-on with no send). Dispatched from the
 * store item-action handler (FUN_0050a640).
 *
 * Function IDENTITY is confirmed (Avatar-Store unequip, transmits); the BODY is
 * a raw/near-verbatim Ghidra port, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void UnequipAvatarSlot(int param_1)

{
  char cVar1;
  int iVar2;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (*(uint *)(g_clientContext + 0x44e24) <= (uint)(*(int *)(param_1 + 0x454) + iVar2)) {
                    /* WARNING: Subroutine does not return */
    ThrowCxxException(0x80070057);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  cVar1 = PeekPacketChecksumBool();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(-(uint)(cVar1 != '\0') & 0x8000);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0xffffffff);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  LoadAvatarSprites(0xffffffff,0xffffffff,0xffffffff,0xffffffff,param_1 + 0x31488,200000,300000);
  FUN_00449250(param_1,1,1);
  return;
}

