/* FUN_004261d0 - 0x004261d0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at the file's one argless PeekPacketChecksumState() call
 * ((void *)(regEsi + 0x3b49c)), from tools/guard_cell_resolve.py.
 */
#include "ghidra_types.h"


void FUN_004261d0(int regEsi)

{
  int iVar1;
  byte unaff_BL;
  
  (&DAT_006aa624)[regEsi] = unaff_BL;
  if (unaff_BL != 0xff) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar1 = PeekPacketChecksumState((void *)(regEsi + 0x3b49c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    (&DAT_006a7670)[regEsi + (uint)unaff_BL * 8 + iVar1] = 1;
  }
  return;
}

