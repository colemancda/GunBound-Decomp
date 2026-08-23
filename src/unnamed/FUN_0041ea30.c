/* FUN_0041ea30 - 0x0041ea30 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at the file's one argless PeekPacketChecksumState() call: the item table's icon-id cell at param_1 + 0x58b8e0 + iVar2*0x9bc - FindItemRecordByIcon's walk.
 */
#include "ghidra_types.h"


uint FUN_0041ea30(undefined4 param_1,int param_2)

{
  uint uVar1;
  uint extraout_EAX;
  int iVar2;
  
  iVar2 = 0;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar1 = PeekPacketChecksumState((void *)(param_1 + 0x58b8e0 + iVar2 * 0x9bc));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (param_2 == uVar1) {
      uVar1 = PeekPacketChecksumBool();
      return uVar1;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 100);
  return extraout_EAX & 0xffffff00;
}

