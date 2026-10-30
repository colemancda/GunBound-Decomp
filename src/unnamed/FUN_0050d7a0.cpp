/* FUN_0050d7a0 - 0x0050d7a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * Ported to C++ (2026-07-11) to call CWidget::OnDragMove and
 * CWorldListPanel::RowHitTest directly instead of through the now-removed
 * Widget_OnDragMove/WorldListRowHitTest shims - see src/cxx/PLAN.md's
 * "deduplicate C++-promoted functions" section. Note: the raw C version of
 * the OnDragMove call site was passing only 2 of its 3 real arguments
 * (dropping `this` entirely, tolerated only because C's unprototyped calls
 * don't check argument counts) - an existing bug in the raw port, not
 * something introduced here; passing `this_` explicitly is the correct
 * behavior. The RowHitTest call site was similarly relying on `this`/`x`
 * already sitting in specific registers (EAX/EDI) rather than being
 * passed normally - since `this_` here IS the CWorldListPanel instance
 * (this function stores into State02's own highlighted-slot field,
 * `g_gameStateVTableArray[2]+0xc`, confirming identity), passing all
 * three arguments explicitly sidesteps that register-convention issue
 * entirely rather than needing an inline-asm capture.
 *
 * 2026-10-30: this is CWorldListPanel's slot 1 (word at 0x557f0c), now
 * wired as CWorldListPanel::OnMouseMove in Panel.cpp. OnDragMove is
 * non-virtual now, so the call below is the direct `call 0x50e3a0` at
 * 0x50d7c2. It does not go back through slot 1 into this function.
 */
#include "../cxx/Widget.h"

extern "C" int g_gameStateVTableArray[16];

extern "C" int FUN_0050d7a0(CWorldListPanel *this_, int x, int y)

{
  unsigned int uVar2;

  uVar2 = (unsigned int)this_->RowHitTest(x, y);
  *(unsigned int *)((char *)g_gameStateVTableArray[2] + 0xc) = uVar2;
  bool consumed = this_->OnDragMove(x, y);
  if (!consumed &&
      (this_->m_hidden != '\0' || x <= this_->m_x ||
       this_->m_width + this_->m_x <= x ||
       y <= this_->m_y || this_->m_height + this_->m_y <= y)) {
    return 0;
  }
  return 1;
}

