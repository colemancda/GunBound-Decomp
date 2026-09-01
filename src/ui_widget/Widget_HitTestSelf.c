/* Widget_HitTestSelf - 0x005052b0 in the original binary.
 *
 * The widget's own-rect half of Widget_HitTest (0x50e9c0): the offsets
 * this reads are exactly the CWidget fields confirmed in docs/widgets.md
 * and src/cxx/Widget.h - m_hidden at +0x1e ("short-circuits HitTest and
 * Draw"), m_x/m_y at +0x28/+0x2c, m_width/m_height at +0x30/+0x34 - and
 * the test is the same strict-inequality rect check Widget_HitTest and
 * CLabel::OnMouseDown (src/cxx/Label.cpp) apply, minus Widget_HitTest's
 * child broadcast.  Named on the Draw / Widget_DrawSelf pattern already
 * in the tree.  The one call site, 0x50a283 in FUN_0050a1b0 (the Avatar
 * Store panel's mouse-down handler), uses it as "did the click land on
 * this panel at all" alongside the row-level AvatarListRowHitTest.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


undefined1 __fastcall Widget_HitTestSelf(int param_1,int regEsi,int regEdi)

{
  undefined1 uVar1;
  
  uVar1 = 0;
  if ((((*(char *)(param_1 + 0x1e) == '\0') && (*(int *)(param_1 + 0x28) < regEsi)) &&
      (regEsi < *(int *)(param_1 + 0x30) + *(int *)(param_1 + 0x28))) &&
     ((*(int *)(param_1 + 0x2c) < regEdi &&
      (regEdi < *(int *)(param_1 + 0x34) + *(int *)(param_1 + 0x2c))))) {
    uVar1 = 1;
  }
  return uVar1;
}

