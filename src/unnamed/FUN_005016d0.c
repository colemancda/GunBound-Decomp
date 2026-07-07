/* FUN_005016d0 - 0x005016d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_005016d0(int param_1)

{
  *(undefined1 *)(param_1 + 0x1a6c) = 0;
  *(undefined1 *)(param_1 + 0x1a6d) = 0;
  *(undefined4 *)(param_1 + 0x1a70) = 0;
  if (*(UINT_PTR *)(param_1 + 0x1ab4) != 0) {
    KillTimer(*(HWND *)(param_1 + 0x1ab0),*(UINT_PTR *)(param_1 + 0x1ab4));
    *(undefined4 *)(param_1 + 0x1ab4) = 0;
  }
  if (*(void **)(param_1 + 0x1d98) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x1d98));
    *(undefined4 *)(param_1 + 0x1d98) = 0;
  }
  if (*(void **)(param_1 + 0x201c) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x201c));
    *(undefined4 *)(param_1 + 0x201c) = 0;
  }
  (**(code **)(**(int **)(param_1 + 0x1aac) + 4))();
  return;
}

