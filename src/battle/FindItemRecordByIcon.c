/* FindItemRecordByIcon - 0x0041eb10 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at the file's one argless PeekPacketChecksumState() call: the item table's icon-id cell at param_1 + 0x58b8e0 + iVar2*0x9bc (param_1 = g_clientContext at every caller; same table GetItemQuantityByIcon walks).  The resolver's PRE-SETTLE flag is the prologue arg read.
 */
#include "ghidra_types.h"


int FindItemRecordByIcon(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = 0;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar1 = PeekPacketChecksumState((void *)(param_1 + 0x58b8e0 + iVar2 * 0x9bc));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (param_2 == uVar1) {
      return (int)&g_abItemRecords + param_1 + iVar2 * 0x9bc;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 100);
  return 0;
}

