/* SyncOutgoingChecksumField - 0x004262d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void SyncOutgoingChecksumField(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  code *pcVar5;
  ushort local_8 [2];
  uint local_4;
  
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 == '\x01') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    InsertChecksumStateRecord(uVar3,uVar2);
    return;
  }
  cVar1 = FindChecksumStateRecord(local_8,&param_1);
  if (cVar1 == '\x01') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = PeekPacketChecksumState();
    pcVar5 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((local_8[0] == local_4) && (uVar4 = PeekChecksumStateUnderLock(param_2), param_1 == uVar4)) {
      return;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4263ae/
     * 0x4263cc/0x4263e9 all 3 calls in this function use the same cell,
     * param_2 (already used as a cell pointer at this function's
     * PeekChecksumStateUnderLock(param_2) call above; register-resident
     * as EAX for the first two, stack-spilled to [esp+0x24] for the third
     * after the intervening critical-section calls). See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField(param_2, (uint)local_8[0]);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = (uint)param_1;
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(param_2, 0xffffff9c);
    pcVar5 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = 0xffffff9c;
  }
  EncodeOutgoingPacketField(param_2, uVar4);
  (*pcVar5)(&DAT_005a9068);
  return;
}

