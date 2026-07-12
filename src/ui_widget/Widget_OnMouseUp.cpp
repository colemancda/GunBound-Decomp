/* Widget_OnMouseUp - 0x0050e4c0 in the original binary.
 *
 * No confirmed real name/purpose - some CWidget-derived class's own
 * OnMouseUp override (clears its drag-armed flag at +0x39 before the
 * usual child broadcast + rect test); not yet attributed to a specific
 * promoted C++ class. Raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Ported to C++ (2026-07-11) to call CWidget::MouseUpChildren directly
 * instead of through the now-removed Widget_MouseUpChildren shim - see
 * src/cxx/PLAN.md's "deduplicate C++-promoted functions" section. Same
 * pre-existing bug as the other ports in this batch: the raw C call site
 * was passing only 2 of the 3 real arguments (dropping `this`), tolerated
 * only because C's unprototyped calls don't check argument counts -
 * passing `this_` explicitly here is the correct behavior. This function
 * has no callers of its own in the raw C tree (only reachable via vtable
 * dispatch in the original), so this port only had to touch itself.
 */
#include "../cxx/Widget.h"

extern "C" int Widget_OnMouseUp(CWidget *this_, int x, int y)

{
  *((unsigned char *)this_ + 0x39) = 0;
  bool consumed = this_->MouseUpChildren(x, y);
  if (!consumed &&
      (this_->m_hidden != '\0' || x <= this_->m_x ||
       this_->m_width + this_->m_x <= x ||
       y <= this_->m_y || this_->m_height + this_->m_y <= y)) {
    return 0;
  }
  return 1;
}
