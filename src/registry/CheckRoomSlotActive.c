/* CheckRoomSlotActive - 0x0041c2c0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at both argless PeekPacketChecksumState() calls: ESI walks param_1+0x47a10 in steps of 0x448 (two guard cells per slot, 8 slots), and each iteration compares the previous slot's second cell (esi-0x224) and then this slot's first cell against param_2 - matching the C's local_4 cursor.
 */
#include "ghidra_types.h"


undefined4 CheckRoomSlotActive(int param_1,int param_2)

{
  int iVar1;
  int local_4;
  
  local_4 = 0;
  do {
    if (*(char *)(param_1 + 0x45914 + local_4) != '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar1 = PeekPacketChecksumState((void *)(param_1 + 0x47a10 + local_4 * 0x448 - 0x224));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar1 == param_2) {
        return 1;
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar1 = PeekPacketChecksumState((void *)(param_1 + 0x47a10 + local_4 * 0x448));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar1 == param_2) {
        return 1;
      }
    }
    local_4 = local_4 + 1;
    if (7 < local_4) {
      return 0;
    }
  } while( true );
}

