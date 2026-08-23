/* PreviewAvatarPart - 0x0044b460 in the original binary.
 *
 * Avatar Store "try-on / preview" action: composites the selected part into the
 * LOCAL avatar preview only - it does NOT call EncodeOutgoingPacketField, so
 * nothing is transmitted. A switch on the selected category ([esi+0x44c]:
 * 0=body, 1=head, 2=glasses, 3=flag) sets that one part code and passes the rest
 * as 0xffffffff to the compositor LoadAvatarSprites. Peer of EquipAvatarPart
 * (0x44b170) / UnequipAvatarSlot (0x44b330), which both transmit. Dispatched
 * from FUN_00445450.
 *
 * Function IDENTITY is confirmed (Avatar-Store try-on preview, local only); the
 * BODY is a raw/near-verbatim Ghidra port, not hand-verified. See src/README.md's
 * "Raw/verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at all 4 argless PeekPacketChecksumState() calls, from a full
 * disasm of 0x44b460-0x44b53a.  Three read the panel's selected-row
 * cell at unaff_ESI+4; the second one's result is the INDEX for the
 * third site - `imul eax,eax,0x17e4 / lea eax,[eax+esi+0x458]` at
 * 0x44b4ac - i.e. the row's preview record in the 0x17e4-stride array
 * at panel+0x458.  The decompile had discarded that result; captured
 * in a new iVar5.
 */
#include "ghidra_types.h"


void PreviewAvatarPart(void)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int unaff_ESI;
  int iVar5;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  PeekPacketChecksumState((void *)(unaff_ESI + 4));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar5 = PeekPacketChecksumState((void *)(unaff_ESI + 4));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = PeekPacketChecksumState((void *)(unaff_ESI + 0x458 + iVar5 * 0x17e4));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = PeekPacketChecksumState((void *)(unaff_ESI + 4));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar4 = (*(char *)(iVar2 + *(int *)(unaff_ESI + 0x450) * 9 + 0x2d54c + unaff_ESI) != '\x01') - 1 &
          0x8000;
  switch(*(undefined4 *)(unaff_ESI + 0x44c)) {
  case 0:
    uVar3 = 0xffffffff;
    uVar1 = uVar4 | uVar1 & 0xffff;
    uVar4 = 0xffffffff;
    goto LAB_0044b59d;
  case 1:
    LoadAvatarSprites(uVar4 | uVar1 & 0xffff,0xffffffff,0xffffffff,0xffffffff,unaff_ESI + 0x31488,200000,
                 300000);
    FUN_00449250(unaff_ESI,1,1);
    return;
  case 2:
    uVar4 = uVar4 | uVar1 & 0xffff;
    uVar3 = 0xffffffff;
    break;
  case 3:
    uVar3 = uVar4 | uVar1 & 0xffff;
    uVar4 = 0xffffffff;
    break;
  default:
    goto switchD_0044b51a_default;
  }
  uVar1 = 0xffffffff;
LAB_0044b59d:
  LoadAvatarSprites(0xffffffff,uVar1,uVar4,uVar3,unaff_ESI + 0x31488,200000,300000);
switchD_0044b51a_default:
  FUN_00449250(unaff_ESI,1,1);
  return;
}

