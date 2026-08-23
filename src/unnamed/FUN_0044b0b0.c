/* FUN_0044b0b0 - 0x0044b0b0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at the file's one argless PeekPacketChecksumState() call: the selected catalog record's part-code field - *(ctx+0x44e20) + (pageBase + i)*0x450 + 0x22c, the exact expression Equip/UnequipAvatarSlot use, here walked over every visible row (uVar1 = param_1+0x454 page base + iVar2).
 */
#include "ghidra_types.h"


void FUN_0044b0b0(int param_1)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = 0;
  while( true ) {
    uVar1 = *(int *)(param_1 + 0x454) + iVar2;
    if (*(uint *)(g_clientContext + 0x44e24) <= uVar1) {
      return;
    }
    if (*(uint *)(g_clientContext + 0x44e24) <= uVar1) break;
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar1 = PeekPacketChecksumState((void *)(*(int *)(g_clientContext + 0x44e20) + uVar1 * 0x450 + 0x22c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    /* FIXED (2026-08-11): dropped outRecord (ESI) - orig 0x44b0b9-0x44b0c0
     * `mov esi,[esp+0x10]` (= param_1) / `add esi,0xdb5c`, loop-invariant
     * up to the call at 0x44b146. */
    FUN_004240c0(g_clientContext,(uVar1 & 0x8000) == 0x8000,uVar1 >> 0x10,uVar1 & 0x7fff,
                 param_1 + 0xdb5c);
    iVar2 = iVar2 + 1;
    if (0x14 < iVar2) {
      return;
    }
  }
                    /* WARNING: Subroutine does not return */
  ThrowCxxException(0x80070057);
}

