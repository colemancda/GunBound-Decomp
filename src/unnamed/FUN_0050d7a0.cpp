/* FUN_0050d7a0 - 0x0050d7a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * Ported to C++ (2026-07-11) to call CWidget::OnDragMove directly instead
 * of through the now-removed Widget_OnDragMove shim - see src/cxx/PLAN.md's
 * "deduplicate C++-promoted functions" section. Note: the raw C version of
 * this call site was passing only 2 of Widget_OnDragMove's 3 arguments
 * (dropping `this` entirely, tolerated only because C's unprototyped calls
 * don't check argument counts) - an existing bug in the raw port, not
 * something introduced here; passing `this_` explicitly is the correct
 * behavior. WorldListRowHitTest is still raw C (its own register-passed-
 * argument reconstruction is separate, not-yet-done work), so that call
 * stays as a plain extern "C" call into the existing .c tree.
 */
#include "../cxx/Widget.h"

extern "C" unsigned int WorldListRowHitTest(int param_1);
extern "C" int g_gameStateVTableArray[16];

extern "C" int FUN_0050d7a0(CWidget *this_, int x, int y)

{
  unsigned int uVar2;

  uVar2 = WorldListRowHitTest(y);
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

