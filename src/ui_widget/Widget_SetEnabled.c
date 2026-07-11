/* Widget_SetEnabled - 0x0050e7d0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall Widget_SetEnabled(int param_1,undefined4 param_2)

{
  uint uVar1;
  
  *(char *)(param_1 + 0x1c) = (char)param_2;
  if (*(char *)(param_1 + 4) != '\0') {
    *(undefined1 *)(param_1 + 4) = 0;
  }
  uVar1 = 0;
  if (*(int *)(param_1 + 0x10) != 0) {
    if (*(int *)(param_1 + 0x10) == 0) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    do {
      /* Ghidra dropped the recursive call's `this` (child pointer) arg;
       * broadcasts the enabled flag to the uVar1-th child at param_1+0xc
       * (matches CWidget::SetEnabled -> m_children[i]->SetEnabled() in
       * src/cxx/Widget.cpp). */
      Widget_SetEnabled(*(int *)(*(int *)(param_1 + 0xc) + uVar1 * 4),param_2);
      uVar1 = uVar1 + 1;
    } while (uVar1 < *(uint *)(param_1 + 0x10));
  }
  return;
}

