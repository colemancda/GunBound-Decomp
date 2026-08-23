/* GetItemQuantityByIcon - 0x0041e9a0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at both argless PeekPacketChecksumState() calls: the loop walks the item table at param_1 (= g_clientContext at
 * every caller) - icon-id cell at +0x58b8e0 and quantity cell at
 * +0x58b48c, record stride 0x9bc, both indexed by the C's own loop
 * counter iVar3 (EBX steps 0x9bc per iteration; the hit path
 * recomputes esi*0x9bc).  The resolver's PRE-SETTLE flag on the first
 * is the prologue arg read of param_1.
 */
#include "ghidra_types.h"


undefined4 GetItemQuantityByIcon(undefined4 param_1,int param_2)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = 0;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar1 = PeekPacketChecksumState((void *)(param_1 + 0x58b8e0 + iVar3 * 0x9bc));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (param_2 == uVar1) {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar2 = PeekPacketChecksumState((void *)(param_1 + 0x58b48c + iVar3 * 0x9bc));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      return uVar2;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 < 100);
  return 0;
}

