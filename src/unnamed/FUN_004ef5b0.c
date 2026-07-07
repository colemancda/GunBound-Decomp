/* FUN_004ef5b0 - 0x004ef5b0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004ef5b0(int param_1)

{
  int *piVar1;
  
  EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x20));
  if (*(int *)(param_1 + 0x14) != 0) {
    piVar1 = *(int **)(DAT_00793558 + *(int *)(param_1 + 0x38) * 4);
    (**(code **)(*piVar1 + 0x48))(piVar1);
    FUN_004f1460();
    *(undefined4 *)(param_1 + 0x14) = 0;
    *(undefined1 *)(param_1 + 0x4c) = 0;
  }
  *(undefined4 *)(param_1 + 0x38) = 0xffffffff;
  LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x20));
  return;
}

