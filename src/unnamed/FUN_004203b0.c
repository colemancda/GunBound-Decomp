/* FUN_004203b0 - 0x004203b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004203b0(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_14 = 0;
  if (((*(int *)(param_1 + 0x621e0) != 0) && (cVar1 = FUN_004065a0(), cVar1 != '\0')) &&
     (cVar1 = FUN_004065a0(), cVar1 != '\0')) {
    local_14 = FUN_0045d150();
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar2 + local_14);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_c = 1;
  local_8 = 7;
  do {
    if (local_c < 8) {
      local_10 = 8 - local_c;
      do {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar2 = PeekPacketChecksumState();
        iVar3 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar2 < iVar3) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar4 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar5 = PeekPacketChecksumState();
          EncodeOutgoingPacketField(uVar5);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField(uVar4);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        }
        local_10 = local_10 + -1;
      } while (local_10 != 0);
    }
    local_c = local_c + 1;
    local_8 = local_8 + -1;
  } while (local_8 != 0);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar2 - local_14);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return;
}

