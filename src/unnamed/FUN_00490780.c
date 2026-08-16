/* FUN_00490780 - 0x00490780 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at the file's one argless PeekPacketChecksumState() call
 * ((void *)&DAT_00e55ab8), from tools/guard_cell_resolve.py.
 */
#include "ghidra_types.h"


void __fastcall FUN_00490780(int param_1)

{
  char cVar1;
  int iVar2;
  
  cVar1 = FUN_0048f300(param_1);
  if (cVar1 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState((void *)&DAT_00e55ab8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (*(int *)(param_1 + 0x3f9c) <= iVar2) goto LAB_004907bd;
  }
  *(undefined1 *)(param_1 + 0x14) = 1;
LAB_004907bd:
  *(int *)(param_1 + 0x3f9c) = *(int *)(param_1 + 0x3f9c) + 1;
  return;
}

