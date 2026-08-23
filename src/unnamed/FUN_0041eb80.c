/* FUN_0041eb80 - 0x0041eb80 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at the file's one argless PeekPacketChecksumState() call: the item table's icon-id cell - FindItemRecordByIcon's walk (this one returns the +0x58bb04 field of the hit).
 */
#include "ghidra_types.h"


undefined * FUN_0041eb80(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = 0;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar1 = PeekPacketChecksumState((void *)(param_1 + 0x58b8e0 + iVar2 * 0x9bc));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (param_2 == uVar1) {
      return &DAT_0058bb04 + param_1 + iVar2 * 0x9bc;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 100);
  return (undefined *)0x0;
}

