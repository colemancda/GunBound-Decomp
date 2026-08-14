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
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at both argless Peeks and both 1-arg Encodes, from a full disasm
 * of 0x44b330-0x44b45f.  Exact sibling of EquipAvatarPart with the same
 * severed data flow: the first Peek is the selected-row cell
 * (param_1+0x228), the second reads the selected catalog record's part
 * code (catalog at *(ctx+0x44e20), stride 0x450, field +0x22c) and its
 * bits 16-19 - `sar ebx,0x10 / and bl,0xf` at 0x44b3b1 - are the
 * CATEGORY that indexes both Encode cells (the per-category equipped
 * part-code array at ctx+0x3ac08 and the equipped-index array at
 * ctx+0x5f4ab8, both stride 0x224).  Captured in a new uVar3.  The
 * values differ from Equip only in meaning: code = gender<<15 | 0
 * ("Standard/none") and index = 0xffffffff.
 */
#include "ghidra_types.h"


void UnequipAvatarSlot(int param_1)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState((void *)(param_1 + 0x228));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (*(uint *)(g_clientContext + 0x44e24) <= (uint)(*(int *)(param_1 + 0x454) + iVar2)) {
                    /* WARNING: Subroutine does not return */
    ThrowCxxException(0x80070057);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState((void *)(*(int *)(g_clientContext + 0x44e20) + (*(int *)(param_1 + 0x454) + iVar2) * 0x450 + 0x22c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  cVar1 = PeekPacketChecksumBool();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((void *)(g_clientContext + 0x3ac08 + (uVar3 >> 0x10 & 0xf) * 0x224), -(uint)(cVar1 != '\0') & 0x8000);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((void *)(g_clientContext + 0x5f4ab8 + (uVar3 >> 0x10 & 0xf) * 0x224), 0xffffffff);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  LoadAvatarSprites(0xffffffff,0xffffffff,0xffffffff,0xffffffff,param_1 + 0x31488,200000,300000);
  FUN_00449250(param_1,1,1);
  return;
}

