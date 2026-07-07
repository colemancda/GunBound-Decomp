/* FUN_004dbf30 - 0x004dbf30 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004dbf30(uint param_1)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  int local_c;
  
  bVar4 = (param_1 & 0xff00) == 0xff00;
  iVar3 = 6 - (uint)bVar4;
  local_c = 0;
  if (0 < iVar3) {
    do {
      if (bVar4) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        cVar1 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (cVar1 == -1) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          cVar1 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (cVar1 == (char)param_1) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField(0);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField(0);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_c = local_c + 1;
          }
        }
      }
      else {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        cVar1 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (cVar1 == -1) {
          local_c = local_c + 1;
        }
        else {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar2 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (uVar2 == (param_1 & 0xff)) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField(0);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
        }
      }
      local_c = local_c + 1;
    } while (local_c < iVar3);
  }
  return;
}

