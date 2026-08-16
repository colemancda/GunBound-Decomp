/* FUN_004261d0 - 0x004261d0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at the file's one argless PeekPacketChecksumState() call
 * ((void *)(unaff_ESI + 0x3b49c)), from tools/guard_cell_resolve.py.
 */
#include "ghidra_types.h"


void FUN_004261d0(void)

{
  int iVar1;
  byte unaff_BL;
  int unaff_ESI;
  
  (&DAT_006aa624)[unaff_ESI] = unaff_BL;
  if (unaff_BL != 0xff) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState((void *)(unaff_ESI + 0x3b49c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    (&DAT_006a7670)[unaff_ESI + (uint)unaff_BL * 8 + iVar1] = 1;
  }
  return;
}

