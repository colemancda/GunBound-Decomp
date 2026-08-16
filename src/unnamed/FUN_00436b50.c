/* FUN_00436b50 - 0x00436b50 in the original binary.
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


void FUN_00436b50(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  void *pvVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 == '\0') {
    pvVar2 = operator_new(0x50);
    if (pvVar2 == (void *)0x0) {
      iVar3 = 0;
    }
    else {
      FUN_0049e420();
    }
    *(undefined4 *)(iVar3 + 0x38) = param_1;
    *(undefined4 *)(iVar3 + 0x3c) = param_2;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState((void *)&DAT_00e9bed8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = _rand();
    *(int *)(iVar3 + 0x44) = iVar5 % iVar4;
    RegisterActiveObject(0, 0, (undefined4 *)0);
  }
  return;
}

