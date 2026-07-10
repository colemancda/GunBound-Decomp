/* Widget_MoveBy - 0x0050e730 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall Widget_MoveBy(int param_1,int param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = 0;
  *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + param_2;
  *(int *)(param_1 + 0x2c) = *(int *)(param_1 + 0x2c) + param_3;
  if (*(int *)(param_1 + 0x10) != 0) {
    if (*(int *)(param_1 + 0x10) == 0) {
                    /* WARNING: Subroutine does not return */
      FUN_004010c0(0x80070057);
    }
    do {
      /* Ghidra dropped the recursive call's `this` (child pointer) arg;
       * this __thiscall function needs it. The child is the uVar1-th
       * entry of the children array at param_1+0xc (matches the C++
       * promotion CWidget::MoveBy -> m_children[i]->MoveBy(dx,dy) in
       * src/cxx/Widget.cpp). */
      Widget_MoveBy(*(int *)(*(int *)(param_1 + 0xc) + uVar1 * 4),param_2,param_3);
      uVar1 = uVar1 + 1;
    } while (uVar1 < *(uint *)(param_1 + 0x10));
  }
  return;
}

