/* FUN_00464320 - 0x00464320 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at the file's one argless PeekPacketChecksumState() call
 * ((void *)&DAT_00e9bed8), from tools/guard_cell_resolve.py.
 */
#include "ghidra_types.h"


void __fastcall FUN_00464320(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x40) + 1;
  *(int *)(param_1 + 0x40) = iVar1;
  if (0x1f < iVar1) {
    *(undefined1 *)(param_1 + 0x14) = 1;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState((void *)&DAT_00e9bed8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(int *)(param_1 + 0x38) = *(int *)(param_1 + 0x38) + *(int *)(param_1 + 0x50);
  *(int *)(param_1 + 0x44) = (*(int *)(param_1 + 0x44) + 6) % iVar1;
  *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + *(int *)(param_1 + 0x54);
  if (8 < *(int *)(param_1 + 0x40)) {
    *(int *)(param_1 + 0x54) = *(int *)(param_1 + 0x54) + 2;
  }
  return;
}

