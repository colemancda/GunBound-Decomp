/* FUN_004eef00 - 0x004eef00 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004eef00(int param_1)

{
  int *piVar1;
  
  EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x20));
  if (*(int *)(param_1 + 0x50) != 0) {
    piVar1 = *(int **)(DAT_00793558 + *(int *)(param_1 + 0x38) * 4);
    (**(code **)(*piVar1 + 0x48))(piVar1);
    _free(*(void **)(param_1 + 0x98));
    _free(*(void **)(param_1 + 0xa8));
    *(undefined4 *)(param_1 + 0x98) = 0;
    *(undefined4 *)(param_1 + 0xa4) = 0;
    *(undefined4 *)(param_1 + 0xa8) = 0;
    *(undefined4 *)(param_1 + 0xac) = 0;
    CloseSpriteReadState();
    *(undefined4 *)(param_1 + 0x50) = 0;
    *(undefined1 *)(param_1 + 0x4c) = 0;
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x20));
  return;
}

