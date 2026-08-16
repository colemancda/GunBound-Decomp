/* FUN_0045d360 - 0x0045d360 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 10 argless PeekPacketChecksumState() calls.  EAX is the
 * caller's object for the whole function (the file's in_EAX), so the
 * cells are in_EAX + 0x8de8/0x8bc4/0x900c/0x9678/0x989c/0x9ac0 plus the
 * globals 0xe55ab8 / 0xe9ba40.  The two remaining peeks (0x45d506 and
 * 0x45d5b6) read frame[0x20], loaded at 0x45d4fc / 0x45d5ac from
 * `(*(uint *)(in_EAX + 8) & 7) * 0x1120 + g_clientContext + 0x50cf4` -
 * the per-player battle stat array this file already indexes the same way
 * at its PeekChecksumStateUnderLock a few lines above (ApplyAvatarStat-
 * Bonuses writes that array; ComputeTurnDelay reads cell 3 of it).
 */
#include "ghidra_types.h"


int FUN_0045d360(int param_1)

{
  char cVar1;
  int in_EAX;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState((void *)(in_EAX + 0x8de8));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState((void *)(in_EAX + 0x8bc4));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState((void *)(&DAT_00e55ab8));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState((void *)(in_EAX + 0x900c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = ((400 - iVar3) / iVar4) * iVar5;
  cVar1 = DecodeGuardedBool();
  if (cVar1 != '\0') {
    cVar1 = PeekPacketChecksumBool((byte *)(param_1 + 0x8bba));
    if (cVar1 == '\0') {
      cVar1 = PeekPacketChecksumBool((byte *)(param_1 + 0x8bb7));
      if (cVar1 == '\0') {
        iVar3 = in_EAX + 0x9230;
      }
      else {
        iVar3 = in_EAX + 0x9454;
      }
      iVar3 = PeekChecksumStateUnderLock(iVar3);
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState((void *)(in_EAX + 0x9678));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    iVar5 = iVar5 + iVar3;
  }
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 == '\x01') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState((void *)(in_EAX + 0x989c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = iVar5 + iVar3;
    if (param_1 != '\0') {
      iVar3 = GetItemQuantityByIcon(g_clientContext,*(undefined2 *)(in_EAX + 0xbfbc));
      iVar5 = iVar5 + iVar3;
      goto LAB_0045d4b9;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState((void *)(in_EAX + 0x9ac0));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = GetItemQuantityByIcon(g_clientContext,*(undefined2 *)(in_EAX + 0xbfbc));
    if (iVar4 + iVar3 * -3 < 0) {
      iVar3 = 0;
    }
    else {
      iVar4 = PeekChecksumStateUnderLock((*(uint *)(in_EAX + 8) & 7) * 0x1120 + 0x50cf4 + g_clientContext);
      iVar3 = GetItemQuantityByIcon(g_clientContext,*(undefined2 *)(in_EAX + 0xbfbc));
      iVar3 = iVar3 + iVar4 * -3;
    }
  }
  else {
LAB_0045d4b9:
    if (param_1 == '\0') goto LAB_0045d527;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState((void *)((*(uint *)(in_EAX + 8) & 7) * 0x1120 + g_clientContext + 0x50cf4));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState((void *)(&DAT_00e9ba40));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = iVar3 + iVar4 * -3;
  }
  iVar5 = iVar5 + iVar3;
LAB_0045d527:
  *(undefined1 *)(in_EAX + 0xae68) = 1;
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x45d555
     * (`lea edi,[esi+0xae6c]`). Objdump of orig/GunBound.gme confirms
     * esi = eax at function entry (`mov esi,eax` at 0x45d372), i.e. esi is
     * this file's own `in_EAX`; the cell is in_EAX+0xae6c. See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField(in_EAX + 0xae6c, iVar5 + iVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState((void *)((*(uint *)(in_EAX + 8) & 7) * 0x1120 + g_clientContext + 0x50cf4));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return iVar3 * (iVar5 + iVar2);
}

